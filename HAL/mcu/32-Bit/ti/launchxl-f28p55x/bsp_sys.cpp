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
/******************************************   Macros **********************************************************/
#define LOG_BAUDRATE            115200u


/***********************************************  Constants   *************************************************/

/*********************************************** Enumeration	***********************************************/

/******************************************* Local Global Variables *******************************************/

/******************************************* Local functions prototypes **************************************/

/*********************************************** Data types  **************************************************/

extern "C" void boot_image_wrapper(std::uint32_t);

namespace bsp
{
    sys::sys(void)
    {

    }

    sys &sys::get_instance(void)
    {
        static sys obj_sys_singleton;
        return obj_sys_singleton;
    }
	
    std::int16_t sys::get_id(std::uint8_t au8_sys_id[ID_LEN]) const
    {
        (void)(au8_sys_id);
        return GENERIC_SUCCESS;
    }

    std::uint32_t sys::get_cpu_frequency(void) const
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

    void sys::sleep(void) const
    {
        
    }

    void sys::boot_image(std::uint32_t u32_image_addr)
    {
        boot_image_wrapper(u32_image_addr);
    }
}
