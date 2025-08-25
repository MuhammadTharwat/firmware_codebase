/**
 ******************************************************************************
 * @file			bsp_led.cpp
 * @description
 * @author			Muhammad Tharwat
 * @version		V0.0
 * @date
 ******************************************************************************
 */
#include "bsp_led.hpp"
#include <altera_avalon_pio_regs.h>
#include "system.h"
#include "general_includes.hpp"

/******************************************   Macros **********************************************************/
#define MAX_NUM_LEDs 4
#define LED_0 UINT32_C(1)
#define LED_1 UINT32_C(2)
#define LED_2 UINT32_C(4)
#define LED_3 UINT32_C(8)
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

        uint32_t u32_pio_data = IORD_ALTERA_AVALON_PIO_DATA(PIO_0_BASE);
        u32_pio_data |= rled_dev.u32_idx;
        IOWR_ALTERA_AVALON_PIO_DATA(PIO_0_BASE, u32_pio_data);
        return GENERIC_SUCCESS;
    }

    std::int16_t led::on(void) const
    {
        uint32_t u32_pio_data = IORD_ALTERA_AVALON_PIO_DATA(PIO_0_BASE);
        u32_pio_data &= ~rled_dev.u32_idx;
        IOWR_ALTERA_AVALON_PIO_DATA(PIO_0_BASE, u32_pio_data);
        return GENERIC_SUCCESS;
    }

    std::int16_t led::off(void) const
    {
        uint32_t u32_pio_data = IORD_ALTERA_AVALON_PIO_DATA(PIO_0_BASE);
        u32_pio_data |= rled_dev.u32_idx;
        IOWR_ALTERA_AVALON_PIO_DATA(PIO_0_BASE, u32_pio_data);
        return GENERIC_SUCCESS;
    }

    std::int16_t led::toggle(void) const
    {
        uint32_t u32_pio_data = IORD_ALTERA_AVALON_PIO_DATA(PIO_0_BASE);
        u32_pio_data ^= rled_dev.u32_idx;
        IOWR_ALTERA_AVALON_PIO_DATA(PIO_0_BASE, u32_pio_data);
        return GENERIC_SUCCESS;
    }

    led_dev &get_led_dev(std::uintmax_t uint_dev)
    {
        static led_dev led_devs[MAX_NUM_LEDs] = {{LED_0}, {LED_1}, {LED_2}, {LED_3}};
        return led_devs[uint_dev];
    }
}