/**
 ******************************************************************************
 * @file			bsp_led.cpp
 * @description
 * @author			Muhammad Tharwat
 * @version		    V0.0
 * @date            4-May-2026
 ******************************************************************************
 */
#include "bsp_led.hpp"
#include "general_includes.hpp"
#include "device.h"
/******************************************   Macros **********************************************************/
#define MAX_NUM_LEDs 2
#define LED_0 UINT32_C(20)
#define LED_1 UINT32_C(21)

#define LED_0_CFG UINT32_C(GPIO_20_GPIO20)
#define LED_1_CFG UINT32_C(GPIO_21_GPIO21)

/***********************************************  Constants   *************************************************/

/*********************************************** Enumeration	***********************************************/

/*********************************************** Data types  **************************************************/

/*********************************************** APIs  **************************************************/

namespace bsp
{

    led::led(led_dev &rled_dev_in) : rled_dev(rled_dev_in)
    {
        /*Do nothing*/
    }

    int16_t led::init(void) const
    {
        GPIO_setPinConfig(rled_dev.u32_pin_config);
        GPIO_setPadConfig(rled_dev.u32_pin_idx, GPIO_PIN_TYPE_STD);
        GPIO_setDirectionMode(rled_dev.u32_pin_idx, GPIO_DIR_MODE_OUT);
        GPIO_writePin(rled_dev.u32_pin_idx, 1);
        return GENERIC_SUCCESS;
    }

    int16_t led::on(void) const
    {
        GPIO_writePin(rled_dev.u32_pin_idx, 0);
        return GENERIC_SUCCESS;
    }

    int16_t led::off(void) const
    {
        GPIO_writePin(rled_dev.u32_pin_idx, 1);
        return GENERIC_SUCCESS;
    }

    int16_t led::toggle(void) const
    {
        GPIO_togglePin(rled_dev.u32_pin_idx);
        return GENERIC_SUCCESS;
    }

    led_dev &get_led_dev(uintmax_t uint_dev)
    {
        static led_dev led_devs[MAX_NUM_LEDs] = {
                                                    led_dev(LED_0, LED_0_CFG), 
                                                    led_dev(LED_1, LED_1_CFG)
                                                };
        return led_devs[uint_dev];
    }
}
