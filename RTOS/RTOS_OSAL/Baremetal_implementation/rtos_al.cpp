/**
  ******************************************************************************
  * @file			rtos_al.cpp
  * @description	Implementation of RTOS AL misc APIs
  * @author			Muhammad Tharwat
  * @version		V0.0
  * @date			16-June-2024
  ******************************************************************************
*/
#include <rtos_al.hpp>
/***********************************************  Defines    **************************************************/


/***********************************************  Constants   *************************************************/

/***********************************************  Enumerations   **********************************************/

/*********************************************** Data types  **************************************************/
namespace rtos_osal
{
	tenu_osal_status kernel_init(void)
	{
		return osal_success;
	}
	
	tenu_osal_status kernel_start(void)
	{
		return osal_success;
	}

	tenu_osal_status kernel_suspend(std::uint32_t &u32_suspend_time_ms)
	{
		(void)(u32_suspend_time_ms);
		return osal_success;
	}

	tenu_osal_status kernel_resume(std::uint32_t u32_suspend_time_ms)
	{
		(void)(u32_suspend_time_ms);
		return osal_success;
	}
}
