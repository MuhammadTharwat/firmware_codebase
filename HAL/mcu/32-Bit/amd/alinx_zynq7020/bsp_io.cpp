/**
 ******************************************************************************
 * @file			bsp_io.cpp
 * @description
 * @author			Muhammad Tharwat
 * @version		    V0.0
 * @date            03-January-2026
 ******************************************************************************
 */
#include "bsp_io.hpp"
#include "general_includes.hpp"
#include "xgpiops.h"
#include "xil_misc_psreset_api.h"
/******************************************   Macros **********************************************************/
#define MAX_NUM_IOs 1
#define IO_0 UINT32_C(54)

#define GPIO_DEVICE_ID		XPAR_XGPIOPS_0_DEVICE_ID

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
        XGpioPs_Config *ConfigPtr;
        /* The driver instance for GPIO Device. */

        ConfigPtr = XGpioPs_LookupConfig(GPIO_DEVICE_ID);

        XGpioPs_CfgInitialize(&rio_dev.Gpio, ConfigPtr, ConfigPtr->BaseAddr);
        /*
         * Set the direction for the pin to be output and
         * Enable the Output enable for the LED Pin.
         * */
        XGpioPs_SetDirectionPin(&rio_dev.Gpio, rio_dev.u32_idx, 1);
        XGpioPs_SetOutputEnablePin(&rio_dev.Gpio, rio_dev.u32_idx, 1);
        return GENERIC_SUCCESS;
    }

    std::int16_t io::write(tenu_pin_state enu_state) const
    {
        switch (enu_state)
        {
        case pin_state_low:
        {
            XGpioPs_WritePin(&rio_dev.Gpio, rio_dev.u32_idx, 0x0);
            break;
        }

        case pin_state_high:
        {
            XGpioPs_WritePin(&rio_dev.Gpio, rio_dev.u32_idx, 0x1);
            break;
        }

        default:
        {
            break;
        }
        }
        return GENERIC_SUCCESS;
    }

    io_dev &get_io_dev(std::uintmax_t uint_dev)
    {
        static io_dev io_devs[MAX_NUM_IOs] = {{IO_0}};
        return io_devs[uint_dev];
    }
};