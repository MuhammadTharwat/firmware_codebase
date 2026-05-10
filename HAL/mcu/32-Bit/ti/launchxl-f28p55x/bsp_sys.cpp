/**
 ******************************************************************************
 * @file			bsp_sys.cpp
 * @description     Implementation of system class
 * @author			Muhammad Tharwat
 * @version		V0.0
 * @date
 ******************************************************************************
 */
#include "bsp_sys.hpp"
#include "general_includes.hpp"
#include "driverlib.h"
#include "device.h"

/******************************************   Macros **********************************************************/
#define LOG_BAUDRATE            115200u


/***********************************************  Constants   *************************************************/

/*********************************************** Enumeration	***********************************************/

/******************************************* Local Global Variables *******************************************/

/******************************************* Local functions prototypes **************************************/

/*********************************************** Data types  **************************************************/

extern "C" void boot_image_wrapper(uint32_t);

namespace bsp
{
    sys::sys(void)
    {
        //
        // Initializes system control, device clock, and peripherals
        //
        Device_init();

        //
        // Disable pin locks and enable internal pullups.
        //
        Device_initGPIO();
        //
        // Initializes PIE and clear PIE registers. Disables CPU interrupts.
        // and clear all CPU interrupt flags.
        //
        // Interrupt_initModule();

        // //
        // // Initialize the PIE vector table with pointers to the shell interrupt
        // // Service Routines (ISR).
        // //
        // Interrupt_initVectorTable();
    }

    sys &sys::get_instance(void)
    {
        static sys obj_sys_singleton;
        return obj_sys_singleton;
    }
	
    int16_t sys::get_id(uint8_t au8_sys_id[ID_LEN]) const
    {
        (void)(au8_sys_id);
        return GENERIC_SUCCESS;
    }

    uint32_t sys::get_cpu_frequency(void) const
    {
        return 0;
    }

    tenu_reset_cause sys::get_reset_cause(void) const
    {
        return reset_unknown;
    }

    void sys::reset(void) const
    {

    }

    void sys::delay_us(uint32_t u32_us_delay) const
    {
        DEVICE_DELAY_US(u32_us_delay);
    }

    void sys::sleep(void) const
    {
        
    }

    void sys::boot_image(uint32_t u32_image_addr)
    {
        boot_image_wrapper(u32_image_addr);
    }
}
