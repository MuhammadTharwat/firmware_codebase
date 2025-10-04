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
#include "system.h"
#include "io.h"
#include "general_includes.hpp"

/******************************************   Macros **********************************************************/
#define MAX_NUM_IOs 1
#define IO_0 UINT32_C(0x10)

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

    io::io(io_dev &rio_dev_in) : rio_dev(rio_dev_in)
    {
        /*Do nothing*/
    }

    output::output(io_dev &rio_dev_in) : io(rio_dev_in)
    {
        /*Do nothing*/
    }

    std::int16_t output::init(void)
    {
        /*Set output direction*/
        uint32_t u32_reg = IORD_GPIO_DIRECTION_REG;
        u32_reg |= rio_dev.u32_idx;
        IOWR_GPIO_DIRECTION_REG(u32_reg);
        u32_reg = IORD_GPIO_OUTPUT_REG;
        u32_reg |= rio_dev.u32_idx;
        IOWR_GPIO_OUTPUT_REG(u32_reg);
        return GENERIC_SUCCESS;
    }

    std::int16_t io::write(tenu_pin_state enu_state) const
    {
        uint32_t u32_reg = IORD_GPIO_OUTPUT_REG;
        switch (enu_state)
        {
        case pin_state_low:
        {
            u32_reg &= ~rio_dev.u32_idx;
            break;
        }

        case pin_state_high:
        {
            u32_reg |= rio_dev.u32_idx;
            break;
        }

        default:
        {
            break;
        }
        }
        IOWR_GPIO_OUTPUT_REG(u32_reg);
        return GENERIC_SUCCESS;
    }

    io_dev &get_io_dev(std::uintmax_t uint_dev)
    {
        static io_dev io_devs[MAX_NUM_IOs] = {{IO_0}};
        return io_devs[uint_dev];
    }
};