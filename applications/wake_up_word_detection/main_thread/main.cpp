#include <stdio.h>
#include <inttypes.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/adc.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/util.h>

#include <tensorflow/lite/micro/micro_log.h>
#include <tensorflow/lite/micro/micro_interpreter.h>
#include <tensorflow/lite/micro/micro_mutable_op_resolver.h>
#include <tensorflow/lite/schema/schema_generated.h>
#include <arm_math.h>

#define ADC_NODE DT_NODELABEL(adc)
#define ADC_CH0_NODE DT_CHILD(ADC_NODE, channel_0)

/*
 * Channels taken straight from the children of the board's &adc node. The
 * second argument is the child's reg address, so channel@0 -> 0. Gain,
 * reference, acquisition time, resolution and input pin all come from the dts.
 */
static const struct adc_dt_spec g_str_adc_channel(ADC_DT_SPEC_STRUCT(ADC_NODE, 0)); /* AIN1 / P0.03 */

/*
 * Sampling rate.
 * Note the integer division: 16000 Hz wants 62.5 us, which is not expressible,
 * so 62 us gives an actual rate of ~16129 Hz (+0.8%).
 */
#define SAMPLE_RATE_HZ	   16000U
#define SAMPLE_INTERVAL_US (1000000U / SAMPLE_RATE_HZ)
#define SAMPLES_PER_BLOCK  1024U

BUILD_ASSERT(SAMPLE_INTERVAL_US > 0, "Sample rate too high to express as an integer interval");

/* 12-bit single-ended results are written as 16-bit words, one per sample. */
static uint16_t g_sample_buf[SAMPLES_PER_BLOCK];

static const struct adc_sequence_options g_str_adc_opts = {
	.interval_us = SAMPLE_INTERVAL_US,
	/* Must stay null: a non-null callback forces the driver off the
	 * hardware-timer path and onto the k_timer fallback. */
	.callback = nullptr,
	.user_data = nullptr,
	.extra_samplings = SAMPLES_PER_BLOCK - 1U,
};

/* One-off SAADC offset calibration, kept out of the timed sequence. */
static int adc_calibrate(void)
{
	uint16_t dummy;
	struct adc_sequence seq;

	int err = adc_sequence_init_dt(&g_str_adc_channel, &seq);
	if (err < 0) {
		return err;
	}

	seq.options = nullptr;
	seq.buffer = &dummy;
	seq.buffer_size = sizeof(dummy);
	seq.calibrate = true;

	return adc_read_dt(&g_str_adc_channel, &seq);
}

extern "C" int main(void)
{
	int err;
	uint32_t count = 0;
	struct adc_sequence sequence;

	if (!adc_is_ready_dt(&g_str_adc_channel)) {
		printk("ADC controller %s not ready\n", g_str_adc_channel.dev->name);
		return -ENODEV;
	}

	err = adc_channel_setup_dt(&g_str_adc_channel);
	if (err < 0) {
		printk("Could not setup ADC channel %d (%d)\n", g_str_adc_channel.channel_id, err);
		return err;
	}

	err = adc_calibrate();
	if (err < 0) {
		printk("SAADC calibration failed (%d)\n", err);
		return err;
	}

	err = adc_sequence_init_dt(&g_str_adc_channel, &sequence);
	if (err < 0) {
		printk("Could not init sequence (%d)\n", err);
		return err;
	}

	sequence.options = &g_str_adc_opts;
	sequence.buffer = g_sample_buf;
	sequence.buffer_size = sizeof(g_sample_buf); /* bytes, not samples */
	sequence.calibrate = false;

	printk("ADC channel %d on %s: %u samples @ %u us (%u Hz)\n", g_str_adc_channel.channel_id,
	       g_str_adc_channel.dev->name, SAMPLES_PER_BLOCK, SAMPLE_INTERVAL_US,
	       1000000U / SAMPLE_INTERVAL_US);

	while (true) {
		/* Blocks until the whole block has been sampled: the driver
		 * paces the samples, so there is no k_sleep and no drift. */
		err = adc_read_dt(&g_str_adc_channel, &sequence);
		if (err < 0) {
			printk("Could not read (%d)\n", err);
			continue;
		}

		/* Far too fast to print per sample at 115200 baud, so summarise
		 * the block instead. Replace this with the feature extractor. */
		uint16_t min = g_sample_buf[0];
		uint16_t max = g_sample_buf[0];
		uint32_t sum = 0;

		for (size_t i = 0U; i < SAMPLES_PER_BLOCK; i++) {
			min = MIN(min, g_sample_buf[i]);
			max = MAX(max, g_sample_buf[i]);
			sum += g_sample_buf[i];
		}

		int32_t mean_mv = (int32_t)(sum / SAMPLES_PER_BLOCK);

		if (adc_raw_to_millivolts_dt(&g_str_adc_channel, &mean_mv) < 0) {
			printk("block[%u] min=%u max=%u mean=%" PRId32 " raw\n", count++, min, max,
			       mean_mv);
		} else {
			printk("block[%u] min=%u max=%u mean=%" PRId32 " mV\n", count++, min, max,
			       mean_mv);
		}
	}

	return 0;
}
