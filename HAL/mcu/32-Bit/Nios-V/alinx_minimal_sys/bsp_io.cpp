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

    output::output(io_dev &rio_dev_in) : io(rio_dev_in)
    {
        /*Do nothing*/
    }

    std::int16_t output::init(void)
    {
        uint32_t u32_pio_data = IORD_ALTERA_AVALON_PIO_DATA(PIO_0_BASE);
        u32_pio_data |= rio_dev.u32_idx;
        IOWR_ALTERA_AVALON_PIO_DATA(PIO_0_BASE, u32_pio_data);
        return GENERIC_SUCCESS;
    }

    std::int16_t io::read(tenu_pin_state &renu_state) const
    {

        uint32_t u32_pio_data = IORD_ALTERA_AVALON_PIO_DATA(PIO_0_BASE);
        renu_state = (u32_pio_data & rio_dev.u32_idx) ? pin_state_high : pin_state_low;
        return GENERIC_SUCCESS;
    }

    std::int16_t io::write(tenu_pin_state enu_state) const
    {
        uint32_t u32_pio_data = IORD_ALTERA_AVALON_PIO_DATA(PIO_0_BASE);
        if (pin_state_high == enu_state)
        {
            u32_pio_data |= rio_dev.u32_idx;
        }
        else
        {
            u32_pio_data &= ~rio_dev.u32_idx;
        }
        IOWR_ALTERA_AVALON_PIO_DATA(PIO_0_BASE, u32_pio_data);
        return GENERIC_SUCCESS;
    }

    io_dev &get_io_dev(std::uintmax_t uint_dev)
    {
        static io_dev io_devs[MAX_NUM_IOs] = {{IO_0}};
        return io_devs[uint_dev];
    }
};