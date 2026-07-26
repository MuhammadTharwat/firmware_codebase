#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

#define UI_THREAD_STACK_SIZE 512

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   1000

#define LED_NODE DT_NODELABEL(led_a)

K_THREAD_STACK_DEFINE(a_ui_thread_stack, UI_THREAD_STACK_SIZE);

K_WORK_DEFINE(gstr_butn_a_work, [](struct k_work* work)
{
    ARG_UNUSED(work);
    printf("Butn A Pressed\n");
}); 

K_WORK_DEFINE(gstr_butn_b_work, [](struct k_work* work)
{
    ARG_UNUSED(work);
    printf("Butn B Pressed\n");
}); 

K_WORK_DEFINE(gstr_butn_c_work, [](struct k_work* work)
{
    ARG_UNUSED(work);
    printf("Butn C Pressed\n");
}); 

static void button_a_pressed_cb(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
{
    ARG_UNUSED(dev);
    ARG_UNUSED(cb);
    ARG_UNUSED(pins);
    k_work_submit(&gstr_butn_a_work);
}

static void button_b_pressed_cb(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
{
    ARG_UNUSED(dev);
    ARG_UNUSED(cb);
    ARG_UNUSED(pins);
    k_work_submit(&gstr_butn_b_work);
}

static void button_c_pressed_cb(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
{
    ARG_UNUSED(dev);
    ARG_UNUSED(cb);
    ARG_UNUSED(pins);
    k_work_submit(&gstr_butn_c_work);
}



static int configure_buttons(void)
{
    int ret = -1;

    static const struct gpio_dt_spec button_a = GPIO_DT_SPEC_GET(DT_NODELABEL(button_a), gpios);
    static const struct gpio_dt_spec button_b = GPIO_DT_SPEC_GET(DT_NODELABEL(button_b), gpios);
    static const struct gpio_dt_spec button_c = GPIO_DT_SPEC_GET(DT_NODELABEL(button_c), gpios);

    static struct gpio_callback button_a_cb_data;
    static struct gpio_callback button_b_cb_data;
    static struct gpio_callback button_c_cb_data;
    if (gpio_is_ready_dt(&button_a))
    {
        ret = 0;
    }
    else
    {
        ret = -1;
    }

    if (0 == ret)
    {
        ret = gpio_pin_configure_dt(&button_a, GPIO_INPUT);
    }
    else
    {
    }

    if (0 == ret)
    {
        ret = gpio_pin_interrupt_configure_dt(&button_a, GPIO_INT_EDGE_TO_ACTIVE);
    }
    else
    {
    }

    if (0 == ret)
    {
        gpio_init_callback(&button_a_cb_data, button_a_pressed_cb, BIT(button_a.pin));
        gpio_add_callback(button_a.port, &button_a_cb_data);
    }
    else
    {
    }

    if (gpio_is_ready_dt(&button_b))
    {
        ret = 0;
    }
    else
    {
        ret = -1;
    }

    if (0 == ret)
    {
        ret = gpio_pin_configure_dt(&button_b, GPIO_INPUT);
    }
    else
    {
    }

    if (0 == ret)
    {
        ret = gpio_pin_interrupt_configure_dt(&button_b, GPIO_INT_EDGE_TO_ACTIVE);
    }
    else
    {
    }

    if (0 == ret)
    {
        gpio_init_callback(&button_b_cb_data, button_b_pressed_cb, BIT(button_b.pin));
        gpio_add_callback(button_b.port, &button_b_cb_data);
    }
    else
    {
    }

    if (gpio_is_ready_dt(&button_c))
    {
        ret = 0;
    }
    else
    {
        ret = -1;
    }

    if (0 == ret)
    {
        ret = gpio_pin_configure_dt(&button_c, GPIO_INPUT);
    }
    else
    {
    }

    if (0 == ret)
    {
        ret = gpio_pin_interrupt_configure_dt(&button_c, GPIO_INT_EDGE_TO_ACTIVE);
    }
    else
    {
    }

    if (0 == ret)
    {
        gpio_init_callback(&button_c_cb_data, button_c_pressed_cb, BIT(button_c.pin));
        gpio_add_callback(button_c.port, &button_c_cb_data);
    }
    else
    {
    }

    return ret;
}

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

    ret = configure_buttons();
    if (0 != ret)
    {
        printf("Err Button Cfg %d\n", ret);
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