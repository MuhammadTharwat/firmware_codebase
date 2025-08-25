/**
 ******************************************************************************
 * @file			bsp_io.cpp
 * @description
 * @author			Muhammad Tharwat
 * @version		    V0.0
 * @date            24-August-2025
 ******************************************************************************
 */
#include "bsp_io.hpp"
#include <altera_avalon_pio_regs.h>
#include "system.h"
#include "general_includes.hpp"

/******************************************   Macros **********************************************************/
#define MAX_NUM_IOs 1
#define IO_0 UINT32_C(1)

/***********************************************  Constants   *************************************************/

/*********************************************** Enumeration	***********************************************/

/*********************************************** Data types  **************************************************/

/*********************************************** APIs  **************************************************/

namespace bsp
{
    template<std::uintmax_t uint_io_nr>
    output<uint_io_nr> &output<uint_io_nr>::get_instance ()
    {
        static_assert(UINTMAX_C(MAX_NUM_IOs) > uint_io_nr, "Unsupported Num Outputs");
        static output<uint_io_nr> obj_output_singleton;
        return obj_output_singleton;
    }

    template <std::uintmax_t uint_io_nr>
    std::int16_t init(void)
    {
        static_assert(UINTMAX_C(MAX_NUM_IOs) > uint_io_nr, "Unsupported Num Outputs");
        switch (uint_io_nr)
        {
        case UINTMAX_C(0):
        {
            uint32_t u32_pio_data = IORD_ALTERA_AVALON_PIO_DATA(PIO_0_BASE);
            u32_pio_data |= IO_0;
            IOWR_ALTERA_AVALON_PIO_DATA(PIO_0_BASE, u32_pio_data);
            break;
        }
        default:
        {
            break;
        }
        }
        return GENERIC_SUCCESS;
    }

    template <std::uintmax_t uint_io_nr>
    std::int16_t read(tenu_pin_state &renu_state)
    {
        static_assert(UINTMAX_C(MAX_NUM_IOs) > uint_io_nr, "Unsupported Num Outputs");
        switch (uint_io_nr)
        {
        case UINTMAX_C(0):
        {
            uint32_t u32_pio_data = IORD_ALTERA_AVALON_PIO_DATA(PIO_0_BASE);
            renu_state = (u32_pio_data & IO_0) pin_state_high : pin_state_low;
            break;
        }
        default:
        {
            break;
        }
        }
        return GENERIC_SUCCESS;
    }

    template <std::uintmax_t uint_io_nr>
    std::int16_t write(tenu_pin_state enu_state)
    {
        static_assert(UINTMAX_C(MAX_NUM_IOs) > uint_io_nr, "Unsupported Num Outputs");
        switch (uint_io_nr)
        {
        case UINTMAX_C(0):
        {
            uint32_t u32_pio_data = IORD_ALTERA_AVALON_PIO_DATA(PIO_0_BASE);
            if (pin_state_high == enu_state)
            {
                u32_pio_data |= IO_0;
            }
            else
            {
                u32_pio_data &= ~IO_0;
            }
            IOWR_ALTERA_AVALON_PIO_DATA(PIO_0_BASE, u32_pio_data);
            break;
        }
        default:
        {
            break;
        }
        }
        return GENERIC_SUCCESS;
    }
};