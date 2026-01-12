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
#include "xgpiops.h"
#include "xil_misc_psreset_api.h"
/******************************************   Macros **********************************************************/
#define MAX_NUM_LEDs 1
#define LED_0 UINT32_C(0)

#define GPIO_DEVICE_ID		XPAR_XGPIOPS_0_DEVICE_ID


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
        XGpioPs_Config *ConfigPtr;
        /* The driver instance for GPIO Device. */
        
        /* Unlock the slcr register access lock */
        Xil_Out32(XSLCR_UNLOCK_ADDR, XSLCR_UNLOCK_CODE);

        Xil_Out32(XSLCR_MIO_PIN_00_ADDR, 0x00000600);

        ConfigPtr = XGpioPs_LookupConfig(GPIO_DEVICE_ID);

        XGpioPs_CfgInitialize(&rled_dev.Gpio, ConfigPtr, ConfigPtr->BaseAddr);
        /*
         * Set the direction for the pin to be output and
         * Enable the Output enable for the LED Pin.
         * */
        XGpioPs_SetDirectionPin(&rled_dev.Gpio, rled_dev.u32_idx, 1);
        XGpioPs_SetOutputEnablePin(&rled_dev.Gpio, rled_dev.u32_idx, 1);
        return GENERIC_SUCCESS;
    }

    std::int16_t led::on(void) const
    {
        XGpioPs_WritePin(&rled_dev.Gpio, rled_dev.u32_idx, 0x0);
        return GENERIC_SUCCESS;
    }

    std::int16_t led::off(void) const
    {
        XGpioPs_WritePin(&rled_dev.Gpio, rled_dev.u32_idx, 0x1);
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