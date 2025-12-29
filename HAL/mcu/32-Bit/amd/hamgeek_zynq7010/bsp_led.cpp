/**
 ******************************************************************************
 * @file			bsp_led.cpp
 * @description
 * @author			Muhammad Tharwat
 * @version		V0.0
 * @date			28-December-2025
 ******************************************************************************
 */
#include "bsp_led.hpp"
#include "general_includes.hpp"

/******************************************   Macros **********************************************************/
#define MAX_NUM_LEDs 1
#define LED_0 UINT32_C(1)

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

    std::int16_t led::init(void) const
    {
        /*Set output direction*/
        return GENERIC_SUCCESS;
    }

    std::int16_t led::on(void) const
    {
        return GENERIC_SUCCESS;
    }

    std::int16_t led::off(void) const
    {
        return GENERIC_SUCCESS;
    }

    std::int16_t led::toggle(void) const
    {
        return GENERIC_SUCCESS;
    }

    led_dev &get_led_dev(std::uintmax_t uint_dev)
    {
        static led_dev led_devs[MAX_NUM_LEDs] = {LED_0};
        return led_devs[uint_dev];
    }
}