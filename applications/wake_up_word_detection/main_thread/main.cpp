#include <stdio.h>
#include <inttypes.h>
#include <math.h>
#include <new>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/adc.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/util.h>

#include <tensorflow/lite/micro/micro_log.h>
#include <tensorflow/lite/micro/micro_interpreter.h>
#include <tensorflow/lite/micro/micro_mutable_op_resolver.h>
#include <tensorflow/lite/schema/schema_generated.h>
#include <micro_speech_quantized_model_data.h>
#include <audio_preprocessor_int8_model_data.h>
#include <tensorflow/lite/micro/examples/micro_speech/micro_model_settings.h>

#include <arm_math.h>

#define LED_NODE DT_NODELABEL(led_a)

#define ADC_NODE DT_NODELABEL(adc)
#define ADC_CH0_NODE DT_CHILD(ADC_NODE, channel_0)

/*
 * Channels taken straight from the children of the board's &adc node. The
 * second argument is the child's reg address, so channel@0 -> 0. Gain,
 * reference, acquisition time, resolution and input pin all come from the dts.
 */
static const struct adc_dt_spec g_str_adc_channel(ADC_DT_SPEC_STRUCT(ADC_NODE, 0)); /* AIN1 / P0.03 */

#define SAMPLE_RATE_HZ 16000U
#define SAMPLE_INTERVAL_US (1000000U / SAMPLE_RATE_HZ)
#define SAMPLES_PER_BLOCK 2048U

BUILD_ASSERT(SAMPLE_INTERVAL_US > 0, "Sample rate too high to express as an integer interval");

/*
 * SAADC results are 16-bit words. This channel is single-ended 12-bit, and the
 * nRF driver clamps negative single-ended readings to zero (see
 * drivers/adc/adc_nrfx_saadc.c), so a raw block is 0..4095 riding on the
 * microphone's DC bias. adc_block_to_pcm() rewrites it in place as the signed,
 * zero-centred 16-bit PCM that the audio preprocessor expects.
 *
 * Two blocks, used as a ping-pong pair: the driver fills one while the
 * previous one is converted and pushed through the model, so acquisition and
 * compute overlap instead of taking turns.
 */
#define BLOCK_COUNT 2U
static int16_t g_sample_buf[BLOCK_COUNT][SAMPLES_PER_BLOCK];

/* Completion handshake for adc_read_async(). */
static struct k_poll_signal g_adc_signal;
static struct k_poll_event g_adc_event;

#define ADC_RESOLUTION_BITS DT_PROP(ADC_CH0_NODE, zephyr_resolution)
/* Left-align the converter's result in the 16-bit sample: 12-bit -> x16. */
#define PCM_SHIFT (16 - ADC_RESOLUTION_BITS)

BUILD_ASSERT(ADC_RESOLUTION_BITS > 0 && ADC_RESOLUTION_BITS <= 16,
			 "PCM_SHIFT assumes a resolution that fits in an int16_t sample");

static const struct adc_sequence_options g_str_adc_opts = {
	.interval_us = SAMPLE_INTERVAL_US,
	/* Must stay null: a non-null callback forces the driver off the
	 * hardware-timer path and onto the k_timer fallback. */
	.callback = nullptr,
	.user_data = nullptr,
	.extra_samplings = SAMPLES_PER_BLOCK - 1U,
};

using MicroSpeechOpResolver = tflite::MicroMutableOpResolver<4>;
using AudioPreprocessorOpResolver = tflite::MicroMutableOpResolver<18>;

static constexpr size_t gsz_audio_preproc_arena = 12 * 1024;
static uint8_t gau8_audio_preproc_arena[gsz_audio_preproc_arena] alignas(16);

static constexpr size_t gsz_speech_arena = 10 * 1024;
static uint8_t gau8_speech_arena[gsz_speech_arena] alignas(16);

using Features = int8_t[kFeatureCount][kFeatureSize];

constexpr int kAudioSampleDurationCount =
	kFeatureDurationMs * kAudioSampleFrequency / 1000;
constexpr int kAudioSampleStrideCount =
	kFeatureStrideMs * kAudioSampleFrequency / 1000;


static size_t g_feature_fill;

/* One-off SAADC offset calibration, kept out of the timed sequence. */
static int adc_calibrate(void)
{
	uint16_t dummy;
	struct adc_sequence seq;

	int err = adc_sequence_init_dt(&g_str_adc_channel, &seq);
	if (err < 0)
	{
		return err;
	}

	seq.options = nullptr;
	seq.buffer = &dummy;
	seq.buffer_size = sizeof(dummy);
	seq.calibrate = true;

	return adc_read_dt(&g_str_adc_channel, &seq);
}

/*
 * Rewrites a block of raw SAADC samples in place as signed 16-bit PCM:
 * subtract the tracked DC bias, then left-align the result.
 */
static void adc_block_to_pcm(int16_t *buf, size_t n)
{
	static int32_t s32_dc_q16 = 0;
	/* Seed from this block's mean, otherwise the first block is
	 * one long settling ramp of the exponential average. */
	int32_t sum = 0;

	for (size_t i = 0U; i < n; i++)
	{
		sum += buf[i];
	}

	s32_dc_q16 = (sum / (int32_t)n) << 16;

	for (size_t i = 0U; i < n; i++)
	{
		int32_t raw = buf[i];
		int32_t centred = raw - (s32_dc_q16 >> 16);

		/* Clamp: while the bias estimate is still far off, centred can
		 * reach the full +-4095, and 4095 << 4 overflows an int16_t. */
		buf[i] = (int16_t)CLAMP(centred << PCM_SHIFT, INT16_MIN, INT16_MAX);
	}
}

TfLiteStatus RegisterOps(MicroSpeechOpResolver &op_resolver)
{
	TF_LITE_ENSURE_STATUS(op_resolver.AddReshape());
	TF_LITE_ENSURE_STATUS(op_resolver.AddFullyConnected());
	TF_LITE_ENSURE_STATUS(op_resolver.AddDepthwiseConv2D());
	TF_LITE_ENSURE_STATUS(op_resolver.AddSoftmax());
	return kTfLiteOk;
}

TfLiteStatus RegisterOps(AudioPreprocessorOpResolver &op_resolver)
{
	TF_LITE_ENSURE_STATUS(op_resolver.AddReshape());
	TF_LITE_ENSURE_STATUS(op_resolver.AddCast());
	TF_LITE_ENSURE_STATUS(op_resolver.AddStridedSlice());
	TF_LITE_ENSURE_STATUS(op_resolver.AddConcatenation());
	TF_LITE_ENSURE_STATUS(op_resolver.AddMul());
	TF_LITE_ENSURE_STATUS(op_resolver.AddAdd());
	TF_LITE_ENSURE_STATUS(op_resolver.AddDiv());
	TF_LITE_ENSURE_STATUS(op_resolver.AddMinimum());
	TF_LITE_ENSURE_STATUS(op_resolver.AddMaximum());
	TF_LITE_ENSURE_STATUS(op_resolver.AddWindow());
	TF_LITE_ENSURE_STATUS(op_resolver.AddFftAutoScale());
	TF_LITE_ENSURE_STATUS(op_resolver.AddRfft());
	TF_LITE_ENSURE_STATUS(op_resolver.AddEnergy());
	TF_LITE_ENSURE_STATUS(op_resolver.AddFilterBank());
	TF_LITE_ENSURE_STATUS(op_resolver.AddFilterBankSquareRoot());
	TF_LITE_ENSURE_STATUS(op_resolver.AddFilterBankSpectralSubtraction());
	TF_LITE_ENSURE_STATUS(op_resolver.AddPCAN());
	TF_LITE_ENSURE_STATUS(op_resolver.AddFilterBankLog());
	return kTfLiteOk;
}

static TfLiteStatus GenerateSingleFeature(const int16_t *audio_data,
										  const int audio_data_size,
										  int8_t *feature_output,
										  tflite::MicroInterpreter *interpreter)
{
	TfLiteTensor *input = interpreter->input(0);
	if (input == nullptr)
	{
		MicroPrintf("Input tensor is null in GenerateSingleFeature!");
		return kTfLiteError;
	}
	// check input shape is compatible with our audio sample size
	if (kAudioSampleDurationCount != audio_data_size)
	{
		MicroPrintf("Audio data size mismatch!");
		return kTfLiteError;
	}
	if (kAudioSampleDurationCount != input->dims->data[input->dims->size - 1])
	{
		MicroPrintf("Input dims mismatch!");
		return kTfLiteError;
	}

	TfLiteTensor *output = interpreter->output(0);
	if (output == nullptr)
	{
		MicroPrintf("Output tensor is null in GenerateSingleFeature!");
		return kTfLiteError;
	}
	// check output shape is compatible with our feature size
	if (kFeatureSize != output->dims->data[output->dims->size - 1])
	{
		MicroPrintf("Feature size mismatch!");
		return kTfLiteError;
	}

	std::copy_n(audio_data, audio_data_size,
				tflite::GetTensorData<int16_t>(input));
	TF_LITE_ENSURE_STATUS(interpreter->Invoke());
	std::copy_n(tflite::GetTensorData<int8_t>(output), kFeatureSize,
				feature_output);

	return kTfLiteOk;
}

static TfLiteStatus LoadMicroSpeechModelAndPerformInference(
	const Features &features, uint8_t *pu8_index, float *pflt_score)
{
	// Map the model into a usable data structure. This doesn't involve any
	// copying or parsing, it's a very lightweight operation.
	const tflite::Model *model =
		tflite::GetModel(g_micro_speech_quantized_model_data);
	if (model->version() != TFLITE_SCHEMA_VERSION)
	{
		MicroPrintf("Model version mismatch!");
		return kTfLiteError;
	}

	MicroSpeechOpResolver op_resolver;
	TF_LITE_ENSURE_STATUS(RegisterOps(op_resolver));

	tflite::MicroInterpreter interpreter(model, op_resolver, gau8_speech_arena, gsz_speech_arena);

	TF_LITE_ENSURE_STATUS(interpreter.AllocateTensors());

	TfLiteTensor *input = interpreter.input(0);
	if (input == nullptr)
	{
		MicroPrintf("Input tensor is null!");
		return kTfLiteError;
	}

	// check input shape is compatible with our feature data size
	if (kFeatureElementCount != input->dims->data[input->dims->size - 1])
	{
		MicroPrintf("Feature element count mismatch!");
		return kTfLiteError;
	}

	TfLiteTensor *output = interpreter.output(0);
	if (output == nullptr)
	{
		MicroPrintf("Output tensor is null!");
		return kTfLiteError;
	}
	// check output shape is compatible with our number of prediction categories
	if (kCategoryCount != output->dims->data[output->dims->size - 1])
	{
		MicroPrintf("Category count mismatch!");
		return kTfLiteError;
	}

	float flt_output_scale = output->params.scale;
	int32_t s32_output_zero_point = output->params.zero_point;

	std::copy_n(&features[0][0], kFeatureElementCount,
				tflite::GetTensorData<int8_t>(input));
	TF_LITE_ENSURE_STATUS(interpreter.Invoke());

	// Dequantize output values
	float category_predictions[kCategoryCount];

	for (int i = 0; i < kCategoryCount; i++)
	{
		category_predictions[i] =
			(tflite::GetTensorData<int8_t>(output)[i] - s32_output_zero_point) *
			flt_output_scale;
	}
	uint8_t u8_predi_index =
		std::distance(std::begin(category_predictions),
					  std::max_element(std::begin(category_predictions),
									   std::end(category_predictions)));
	*pu8_index = u8_predi_index;
	*pflt_score = category_predictions[u8_predi_index];
	return kTfLiteOk;
}

static TfLiteStatus GenerateFeatures(tflite::MicroInterpreter &ref_feat_interp, const int16_t *audio_data,
									 const size_t audio_data_size,
									 Features *p_str_features_output)
{
	/*
	 * A full feature set is kFeatureCount frames of kAudioSampleDurationCount
	 * samples advancing kAudioSampleStrideCount at a time -- 15840 samples, far
	 * more than one ADC block, and neither length divides SAMPLES_PER_BLOCK. So
	 * carry each block's unconsumed tail here to keep frames contiguous, and slide
	 * the feature rows instead of restarting at row 0. Worst case held is one
	 * frame short of complete plus a whole fresh block.
	 */
	static int16_t as16_pcm_acc[kAudioSampleDurationCount + SAMPLES_PER_BLOCK];
	static size_t sz_pcm_acc_len = 0;
	if (audio_data_size > ARRAY_SIZE(as16_pcm_acc) - sz_pcm_acc_len)
	{
		MicroPrintf("PCM accumulator overflow!");
		sz_pcm_acc_len = 0;
		return kTfLiteError;
	}

	std::copy_n(audio_data, audio_data_size, &as16_pcm_acc[sz_pcm_acc_len]);
	sz_pcm_acc_len += audio_data_size;

	while (sz_pcm_acc_len >= (size_t)kAudioSampleDurationCount)
	{
		if (g_feature_fill < kFeatureCount)
		{
			g_feature_fill++;
		}
		else
		{
			/* Window full: drop the oldest row, shift the rest down. */
			std::copy(&(*p_str_features_output)[1][0], &(*p_str_features_output)[kFeatureCount][0],
					  &(*p_str_features_output)[0][0]);
		}

		TF_LITE_ENSURE_STATUS(
			GenerateSingleFeature(as16_pcm_acc, kAudioSampleDurationCount,
								  (*p_str_features_output)[g_feature_fill - 1], &ref_feat_interp));

		sz_pcm_acc_len -= kAudioSampleStrideCount;
		std::copy_n(&as16_pcm_acc[kAudioSampleStrideCount], sz_pcm_acc_len, as16_pcm_acc);
	}

	return kTfLiteOk;
}

extern "C" int main(void)
{
	int err;
	struct adc_sequence sequence;

	static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED_NODE, gpios);

	if (!gpio_is_ready_dt(&led))
	{
		return -1;
	}

	if (gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE) < 0)
	{
		return -1;
	}

	if (gpio_pin_set_dt(&led, 0) < 0)
	{
		return -1;
	}

	static AudioPreprocessorOpResolver str_feature_resolver;
	// Map the model into a usable data structure. This doesn't involve any
	// copying or parsing, it's a very lightweight operation.
	static const tflite::Model *model =
		tflite::GetModel(g_audio_preprocessor_int8_model_data);
	if (model->version() != TFLITE_SCHEMA_VERSION)
	{
		MicroPrintf("Model version mismatch in GenerateFeatures!");
		return -1;
	}

	TF_LITE_ENSURE_STATUS(RegisterOps(str_feature_resolver));

	static tflite::MicroInterpreter str_feature_interp(model, str_feature_resolver, gau8_audio_preproc_arena, gsz_audio_preproc_arena);

	TF_LITE_ENSURE_STATUS(str_feature_interp.AllocateTensors());
	MicroPrintf("preprocessor arena %u/%u bytes",
				str_feature_interp.arena_used_bytes(), gsz_audio_preproc_arena);

	if (!adc_is_ready_dt(&g_str_adc_channel))
	{
		printk("ADC controller %s not ready\n", g_str_adc_channel.dev->name);
		return -ENODEV;
	}

	err = adc_channel_setup_dt(&g_str_adc_channel);
	if (err < 0)
	{
		printk("Could not setup ADC channel %d (%d)\n", g_str_adc_channel.channel_id, err);
		return err;
	}

	err = adc_calibrate();
	if (err < 0)
	{
		printk("SAADC calibration failed (%d)\n", err);
		return err;
	}

	err = adc_sequence_init_dt(&g_str_adc_channel, &sequence);
	if (err < 0)
	{
		printk("Could not init sequence (%d)\n", err);
		return err;
	}

	sequence.options = &g_str_adc_opts;
	/* adc_calibrate() already ran once; calibrating per sequence would insert
	 * a fresh calibration into every block of the stream. */
	sequence.calibrate = false;

	k_poll_signal_init(&g_adc_signal);
	g_adc_event.type = K_POLL_TYPE_SIGNAL;
	g_adc_event.mode = K_POLL_MODE_NOTIFY_ONLY;
	g_adc_event.state = K_POLL_STATE_NOT_READY;
	g_adc_event.signal = &g_adc_signal;

	printk("ADC channel %d on %s: streaming %u-sample blocks @ %u us (%u Hz)\n",
		   g_str_adc_channel.channel_id, g_str_adc_channel.dev->name, SAMPLES_PER_BLOCK,
		   SAMPLE_INTERVAL_US, 1000000U / SAMPLE_INTERVAL_US);

	size_t filling = 0U;

	sequence.buffer = g_sample_buf[filling];
	sequence.buffer_size = sizeof(g_sample_buf[filling]); /* bytes, not samples */

	err = adc_read_async_dt(&g_str_adc_channel, &sequence, &g_adc_signal);
	if (err < 0)
	{
		printk("Could not start the stream (%d)\n", err);
		return err;
	}

	while (true)
	{
		static Features astr_features;
		unsigned int signaled;
		int result;

		/* Sleeps until the block in flight lands. The SAADC paces itself
		 * off its own internal timer, so there is no drift here. */
		err = k_poll(&g_adc_event, 1, K_FOREVER);
		if (err < 0)
		{
			printk("k_poll failed (%d)\n", err);
			continue;
		}

		k_poll_signal_check(&g_adc_signal, &signaled, &result);
		k_poll_signal_reset(&g_adc_signal);
		g_adc_event.state = K_POLL_STATE_NOT_READY;

		size_t ready = filling;
		filling = (filling + 1U) % BLOCK_COUNT;

		/*
		 * Re-arm before touching the finished block, so the next one is
		 * already being captured while this one is processed. Safe to
		 * re-point sequence.buffer here: adc_context copies the whole
		 * sequence on submit (drivers/adc/adc_context.h), so the
		 * transfer in flight never reads this struct again.
		 */
		sequence.buffer = g_sample_buf[filling];
		sequence.buffer_size = sizeof(g_sample_buf[filling]);

		err = adc_read_async_dt(&g_str_adc_channel, &sequence, &g_adc_signal);
		if (err < 0)
		{
			printk("Could not re-arm the stream (%d)\n", err);
			return err;
		}

		if (result < 0)
		{
			printk("Block dropped (%d)\n", result);
			continue;
		}

		adc_block_to_pcm(g_sample_buf[ready], SAMPLES_PER_BLOCK);

		(void)(GenerateFeatures(str_feature_interp, g_sample_buf[ready], SAMPLES_PER_BLOCK, &astr_features));
		/* Rows 2..48 are still zero until ~1 s of audio has been seen, and a
		 * zero-filled window classifies as "no" with 0.94 confidence. */
		if (g_feature_fill == kFeatureCount)
		{
			static uint8_t u8_prev_index = 0xFF;
			uint8_t u8_curr_index;
			const float flt_min_score = 0.8f;
			float flt_score;
			static uint8_t u8_run_len = 0;
			const uint8_t u8_detection_cnt = 3;

			if (kTfLiteOk == LoadMicroSpeechModelAndPerformInference(astr_features, &u8_curr_index, &flt_score))
			{

				if (flt_score < flt_min_score)
				{
					u8_prev_index = 0xFF;
					u8_run_len = 0;
				}
				else if (u8_curr_index == u8_prev_index)
				{
					u8_run_len++;
					if (u8_run_len == u8_detection_cnt)
					{
						if (std::strcmp("yes", kCategoryLabels[u8_curr_index]) == 0)
						{
							printk("Detected Yes\n");
							if (gpio_pin_toggle_dt(&led) < 0)
							{
								return -1;
							}
						}
						else
						{
							/*Do nothing*/
						}
					}
				}
				else
				{
					u8_prev_index = u8_curr_index;
					u8_run_len = 1;
				}
			}
			else
			{
			}
		}
	}

	return 0;
}
