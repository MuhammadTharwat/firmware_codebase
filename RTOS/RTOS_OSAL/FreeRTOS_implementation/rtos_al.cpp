/**
  ******************************************************************************
  * @file			rtos_al.cpp
  * @description	Implementation of RTOS AL misc APIs
  * @author			Ahmed Salama
  * @version		V0.0
  * @date			23-Aug-2024
  ******************************************************************************
*/
#include <rtos_al.hpp>
#include "assert.h"
#include <rtos_err_map.hpp>
#include "task.h"
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
		vTaskStartScheduler();
		return osal_success;
	}

	tenu_osal_kernel_status kernel_status(void)
	{
		tenu_osal_kernel_status enu_kernel_status = kernel_not_running;
		BaseType_t enu_os_ker_status = xTaskGetSchedulerState();
		if(taskSCHEDULER_RUNNING == enu_os_ker_status)
		{
			enu_kernel_status = kernel_running;
		}
		else
		{
			/*do nothing*/
		}
		return enu_kernel_status;
	}

	tenu_osal_status kernel_suspend(std::uint32_t &u32_suspend_time_ms)
	{
		(void) u32_suspend_time_ms;
		/*AD-TODO:*/
		return osal_success;
	}

	tenu_osal_status kernel_resume(std::uint32_t u32_suspend_time_ms)
	{
		/*AD-TODO:*/
		(void) u32_suspend_time_ms;
		return osal_success;
	}

	std::uint32_t kernel_get_ticks(void)
	{
		return xTaskGetTickCount();
	}

	std::uint32_t kernel_get_ms(void)
	{
		return (portTICK_RATE_MS * xTaskGetTickCount());
	}

	/* This API should not be called from ISR */
	tenu_osal_status kernel_delay(uint32_t u32_dly_ticks)
	{
		vTaskDelay(u32_dly_ticks);
		return osal_success;
	}
}
