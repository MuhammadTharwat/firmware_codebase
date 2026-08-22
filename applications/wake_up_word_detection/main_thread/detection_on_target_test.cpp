#include <stdio.h>
#include <inttypes.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/util.h>

#include <tensorflow/lite/micro/micro_log.h>
#include <tensorflow/lite/micro/micro_interpreter.h>
#include <tensorflow/lite/micro/micro_mutable_op_resolver.h>
#include <tensorflow/lite/schema/schema_generated.h>
#include <micro_speech_quantized_model_data.h>
#include <audio_preprocessor_int8_model_data.h>
#include <tensorflow/lite/micro/examples/micro_speech/micro_model_settings.h>
#include <no_30ms_audio_data.h>
#include "yes_1000ms_audio_data.h"

#include <arm_math.h>

constexpr size_t kArenaSize = 16 * 1024;
alignas(16) uint8_t g_arena[kArenaSize];

using Features = int8_t[kFeatureCount][kFeatureSize];


constexpr int kAudioSampleDurationCount =
	kFeatureDurationMs * kAudioSampleFrequency / 1000;
constexpr int kAudioSampleStrideCount =
	kFeatureStrideMs * kAudioSampleFrequency / 1000;

using MicroSpeechOpResolver = tflite::MicroMutableOpResolver<4>;
using AudioPreprocessorOpResolver = tflite::MicroMutableOpResolver<18>;

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
	const Features &features, const char *expected_label)
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

	tflite::MicroInterpreter interpreter(model, op_resolver, g_arena, kArenaSize);

	TF_LITE_ENSURE_STATUS(interpreter.AllocateTensors());

	MicroPrintf("MicroSpeech model arena size = %u",
				interpreter.arena_used_bytes());

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

	float output_scale = output->params.scale;
	int output_zero_point = output->params.zero_point;

	std::copy_n(&features[0][0], kFeatureElementCount,
				tflite::GetTensorData<int8_t>(input));
	TF_LITE_ENSURE_STATUS(interpreter.Invoke());

	// Dequantize output values
	float category_predictions[kCategoryCount];
	MicroPrintf("MicroSpeech category predictions for <%s>", expected_label);
	for (int i = 0; i < kCategoryCount; i++)
	{
		category_predictions[i] =
			(tflite::GetTensorData<int8_t>(output)[i] - output_zero_point) *
			output_scale;
		MicroPrintf("  %.4f %s", static_cast<double>(category_predictions[i]),
					kCategoryLabels[i]);
	}
	int prediction_index =
		std::distance(std::begin(category_predictions),
					  std::max_element(std::begin(category_predictions),
									   std::end(category_predictions)));
	if (strcmp(expected_label, kCategoryLabels[prediction_index]) != 0)
	{
		MicroPrintf("Expected label mismatch!");
		return kTfLiteError;
	}

	return kTfLiteOk;
}

static TfLiteStatus GenerateFeatures(const int16_t *audio_data,
									 const size_t audio_data_size,
									 Features *features_output)
{
	// Map the model into a usable data structure. This doesn't involve any
	// copying or parsing, it's a very lightweight operation.
	const tflite::Model *model =
		tflite::GetModel(g_audio_preprocessor_int8_model_data);
	if (model->version() != TFLITE_SCHEMA_VERSION)
	{
		MicroPrintf("Model version mismatch in GenerateFeatures!");
		return kTfLiteError;
	}

	AudioPreprocessorOpResolver op_resolver;
	TF_LITE_ENSURE_STATUS(RegisterOps(op_resolver));

	tflite::MicroInterpreter interpreter(model, op_resolver, g_arena, kArenaSize);

	TF_LITE_ENSURE_STATUS(interpreter.AllocateTensors());

	MicroPrintf("AudioPreprocessor model arena size = %u",
				interpreter.arena_used_bytes());

	size_t remaining_samples = audio_data_size;
	size_t feature_index = 0;
	while (remaining_samples >= kAudioSampleDurationCount &&
		   feature_index < kFeatureCount)
	{
		TF_LITE_ENSURE_STATUS(
			GenerateSingleFeature(audio_data, kAudioSampleDurationCount,
								  (*features_output)[feature_index], &interpreter));
		feature_index++;
		audio_data += kAudioSampleStrideCount;
		remaining_samples -= kAudioSampleStrideCount;
	}

	return kTfLiteOk;
}


static TfLiteStatus TestAudioSample(const char *label, const int16_t *audio_data,
									const size_t audio_data_size)
{
	static Features astr_features;
	TF_LITE_ENSURE_STATUS(GenerateFeatures(audio_data, audio_data_size, &astr_features));
	TF_LITE_ENSURE_STATUS(LoadMicroSpeechModelAndPerformInference(astr_features, label));
	return kTfLiteOk;
}

extern "C" int main(void)
{
	if (kTfLiteOk == TestAudioSample("no", g_no_30ms_audio_data,
									 g_no_30ms_audio_data_size))
	{
		printf("Wake-up word Detected\n");
	}
	else
	{
		printf("Not Detected\n");
	}


	if (kTfLiteOk == TestAudioSample("yes", g_yes_1000ms_audio_data,
									 g_yes_1000ms_audio_data_size))
	{
		printf("Wake-up word Detected\n");
	}
	else
	{
		printf("Not Detected\n");
	}

	return 0;
}
