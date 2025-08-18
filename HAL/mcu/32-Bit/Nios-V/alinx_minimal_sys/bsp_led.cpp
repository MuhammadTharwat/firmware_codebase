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
    template <std::uintmax_t uint_led_nr>
    void led<uint_led_nr>::init(void) const
    {
        static_assert(UINTMAX_C(MAX_NUM_LEDs) > uint_led_nr, "Unsupported Num LEDs");
        switch (uint_led_nr)
        {
        case UINTMAX_C(0):
        {
            uint32_t u32_pio_data = IORD_ALTERA_AVALON_PIO_DATA(PIO_0_BASE);
            u32_pio_data |= LED_0;
            IOWR_ALTERA_AVALON_PIO_DATA(PIO_0_BASE, u32_pio_data);
            break;
        }

        case UINTMAX_C(1):
        {
            uint32_t u32_pio_data = IORD_ALTERA_AVALON_PIO_DATA(PIO_0_BASE);
            u32_pio_data |= LED_1;
            IOWR_ALTERA_AVALON_PIO_DATA(PIO_0_BASE, u32_pio_data);
            break;
        }

        case UINTMAX_C(2):
        {
            uint32_t u32_pio_data = IORD_ALTERA_AVALON_PIO_DATA(PIO_0_BASE);
            u32_pio_data |= LED_2;
            IOWR_ALTERA_AVALON_PIO_DATA(PIO_0_BASE, u32_pio_data);
            break;
        }

        case UINTMAX_C(3):
        {
            uint32_t u32_pio_data = IORD_ALTERA_AVALON_PIO_DATA(PIO_0_BASE);
            u32_pio_data |= LED_3;
            IOWR_ALTERA_AVALON_PIO_DATA(PIO_0_BASE, u32_pio_data);
            break;
        }

        default:
        {
            break;
        }
        }
    }

    template <std::uintmax_t uint_led_nr>
    void led<uint_led_nr>::on(void) const
    {
        static_assert(UINTMAX_C(MAX_NUM_LEDs) > uint_led_nr, "Unsupported Num LEDs");
        switch (uint_led_nr)
        {
        case UINTMAX_C(0):
        {
            uint32_t u32_pio_data = IORD_ALTERA_AVALON_PIO_DATA(PIO_0_BASE);
            u32_pio_data &= ~LED_0;
            IOWR_ALTERA_AVALON_PIO_DATA(PIO_0_BASE, u32_pio_data);
            break;
        }

        case UINTMAX_C(1):
        {
            uint32_t u32_pio_data = IORD_ALTERA_AVALON_PIO_DATA(PIO_0_BASE);
            u32_pio_data &= ~LED_1;
            IOWR_ALTERA_AVALON_PIO_DATA(PIO_0_BASE, u32_pio_data);
            break;
        }

        case UINTMAX_C(2):
        {
            uint32_t u32_pio_data = IORD_ALTERA_AVALON_PIO_DATA(PIO_0_BASE);
            u32_pio_data &= ~LED_2;
            IOWR_ALTERA_AVALON_PIO_DATA(PIO_0_BASE, u32_pio_data);
            break;
        }

        case UINTMAX_C(3):
        {
            uint32_t u32_pio_data = IORD_ALTERA_AVALON_PIO_DATA(PIO_0_BASE);
            u32_pio_data &= ~LED_3;
            IOWR_ALTERA_AVALON_PIO_DATA(PIO_0_BASE, u32_pio_data);
            break;
        }
        default:
        {
            break;
        }
        }
    }

    template <std::uintmax_t uint_led_nr>
    void led<uint_led_nr>::off(void) const
    {
        static_assert(UINTMAX_C(MAX_NUM_LEDs) > uint_led_nr, "Unsupported Num LEDs");
        switch (uint_led_nr)
        {
        case UINTMAX_C(0):
        {
            uint32_t u32_pio_data = IORD_ALTERA_AVALON_PIO_DATA(PIO_0_BASE);
            u32_pio_data |= LED_0;
            IOWR_ALTERA_AVALON_PIO_DATA(PIO_0_BASE, u32_pio_data);
            break;
        }

        case UINTMAX_C(1):
        {
            uint32_t u32_pio_data = IORD_ALTERA_AVALON_PIO_DATA(PIO_0_BASE);
            u32_pio_data |= LED_1;
            IOWR_ALTERA_AVALON_PIO_DATA(PIO_0_BASE, u32_pio_data);
            break;
        }

        case UINTMAX_C(2):
        {
            uint32_t u32_pio_data = IORD_ALTERA_AVALON_PIO_DATA(PIO_0_BASE);
            u32_pio_data |= LED_2;
            IOWR_ALTERA_AVALON_PIO_DATA(PIO_0_BASE, u32_pio_data);
            break;
        }

        case UINTMAX_C(3):
        {
            uint32_t u32_pio_data = IORD_ALTERA_AVALON_PIO_DATA(PIO_0_BASE);
            u32_pio_data |= LED_3;
            IOWR_ALTERA_AVALON_PIO_DATA(PIO_0_BASE, u32_pio_data);
            break;
        }

        default:
        {
            break;
        }
        }
    }

    template <std::uintmax_t uint_led_nr>
    void led<uint_led_nr>::toggle(void) const
    {
        static_assert(UINTMAX_C(MAX_NUM_LEDs) > uint_led_nr, "Unsupported Num LEDs");
        switch (uint_led_nr)
        {
        case UINTMAX_C(0):
        {
            uint32_t u32_pio_data = IORD_ALTERA_AVALON_PIO_DATA(PIO_0_BASE);
            u32_pio_data ^= LED_0;
            IOWR_ALTERA_AVALON_PIO_DATA(PIO_0_BASE, u32_pio_data);
            break;
        }

        case UINTMAX_C(1):
        {
            uint32_t u32_pio_data = IORD_ALTERA_AVALON_PIO_DATA(PIO_0_BASE);
            u32_pio_data ^= LED_1;
            IOWR_ALTERA_AVALON_PIO_DATA(PIO_0_BASE, u32_pio_data);
            break;
        }

        case UINTMAX_C(2):
        {
            uint32_t u32_pio_data = IORD_ALTERA_AVALON_PIO_DATA(PIO_0_BASE);
            u32_pio_data ^= LED_2;
            IOWR_ALTERA_AVALON_PIO_DATA(PIO_0_BASE, u32_pio_data);
            break;
        }

        case UINTMAX_C(3):
        {
            uint32_t u32_pio_data = IORD_ALTERA_AVALON_PIO_DATA(PIO_0_BASE);
            u32_pio_data ^= LED_3;
            IOWR_ALTERA_AVALON_PIO_DATA(PIO_0_BASE, u32_pio_data);
            break;
        }

        default:
        {
            break;
        }
        }
    }

    template <std::uintmax_t uint_led_nr>
    led<uint_led_nr> &led<uint_led_nr>::get_instance(void)
    {
        static_assert(UINTMAX_C(MAX_NUM_LEDs) > uint_led_nr, "Unsupported Num LEDs");
        static led<uint_led_nr> obj_led_singleton;
        return obj_led_singleton;
    }
}

template class bsp::led<0u>;
template class bsp::led<1u>;
template class bsp::led<2u>;
template class bsp::led<3u>;