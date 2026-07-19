#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

#define UI_THREAD_STACK_SIZE 2048

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   1000

#define LED_NODE DT_NODELABEL(led_b)

K_THREAD_STACK_DEFINE(a_ui_thread_stack, UI_THREAD_STACK_SIZE);

static void ui_thread(void *p1, void *p2, void *p3)
{
    ARG_UNUSED(p1);
    ARG_UNUSED(p2);
    ARG_UNUSED(p3);
    int ret;
    static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED_NODE, gpios);

    if (!gpio_is_ready_dt(&led))
    {
        return;
    }

    ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
    if (ret < 0)
    {
        return;
    }

    while (true)
    {
        ret = gpio_pin_toggle_dt(&led);
        if (ret < 0)
        {
            return;
        }

        printf("HeartBeat\n");
        k_msleep(SLEEP_TIME_MS);
    }
}

void ui_thread_init(void)
{
    static struct k_thread str_threat;
    k_tid_t thread_hdl = k_thread_create(&str_threat, a_ui_thread_stack, K_THREAD_STACK_SIZEOF(a_ui_thread_stack),
                                         ui_thread, NULL, NULL, NULL, 1, K_USER, K_NO_WAIT);
    if (NULL == thread_hdl)
    {
        printf("ERR : UI Thread Init\n");
    }
    else
    {
        /*Do nothing*/
    }
}