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

#define GPIO_BASE 0x10000000

#define IORD_GPIO_DIRECTION_REG IORD(GPIO_BASE, 0)
#define IOWR_GPIO_DIRECTION_REG(data) IOWR(GPIO_BASE, 0, data)

#define IORD_GPIO_INPUT_REG IORD(GPIO_BASE, 1)
#define IOWR_GPIO_INPUT_REG(data) IOWR(GPIO_BASE, 1, data)

#define IORD_GPIO_OUTPUT_REG IORD(GPIO_BASE, 2)
#define IOWR_GPIO_OUTPUT_REG(data) IOWR(GPIO_BASE, 2, data)

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
        uint32_t u32_reg = IORD_GPIO_DIRECTION_REG;
        u32_reg |= rled_dev.u32_idx;
        IOWR_GPIO_DIRECTION_REG(u32_reg);
        u32_reg = IORD_GPIO_OUTPUT_REG;
        u32_reg |= rled_dev.u32_idx;
        IOWR_GPIO_OUTPUT_REG(u32_reg);
        return GENERIC_SUCCESS;
    }

    std::int16_t led::on(void) const
    {
        uint32_t u32_reg = IORD_GPIO_OUTPUT_REG;
        u32_reg &= ~rled_dev.u32_idx;
        IOWR_GPIO_OUTPUT_REG(u32_reg);
        return GENERIC_SUCCESS;
    }

    std::int16_t led::off(void) const
    {
        uint32_t u32_reg = IORD_GPIO_OUTPUT_REG;
        u32_reg |= rled_dev.u32_idx;
        IOWR_GPIO_OUTPUT_REG(u32_reg);
        return GENERIC_SUCCESS;
    }

    std::int16_t led::toggle(void) const
    {
        uint32_t u32_reg = IORD_GPIO_OUTPUT_REG;
        u32_reg ^= rled_dev.u32_idx;
        IOWR_GPIO_OUTPUT_REG(u32_reg);
        return GENERIC_SUCCESS;
    }

    led_dev &get_led_dev(std::uintmax_t uint_dev)
    {
        static led_dev led_devs[MAX_NUM_LEDs] = {{LED_0}, {LED_1}, {LED_2}, {LED_3}};
        return led_devs[uint_dev];
    }
}