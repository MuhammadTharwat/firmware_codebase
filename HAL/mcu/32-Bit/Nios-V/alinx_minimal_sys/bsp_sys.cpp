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

namespace bsp
{
    sys::sys(void)
    {
#ifdef DEBUG_MODE
        _ASSERT(GENERIC_SUCCESS == dgb_log_init(LOG_BAUDRATE));
#endif
#ifdef DIAGNOSTIC_LOG
        _ASSERT(GENERIC_SUCCESS == diagnostic_log_init(LOG_BAUDRATE));
#endif
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
}
