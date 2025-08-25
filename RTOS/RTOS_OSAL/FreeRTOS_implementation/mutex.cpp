/**
  ******************************************************************************
  * @file			mutex.cpp
  * @description	Implementation of mutex class
  * @author			Ahmed Salama
  * @version		V0.0
  * @date			22-Aug-2024
  ******************************************************************************
*/
#include <mutex.hpp>
#include "semphr.h"
#include <rtos_err_map.hpp>
#include "rtos_imp.hpp"
#include <limits>
/***********************************************  Defines    **************************************************/


/***********************************************  Constants   *************************************************/

/***********************************************  Enumerations   **********************************************/

/*********************************************** Data types  **************************************************/
namespace rtos_osal
{
	mutex::mutex(void)
	{
		str_mtx_mem.hdl_mtx = xSemaphoreCreateMutexStatic(&this->str_mtx_mem.str_mtx_attrb);
		/*MT-TODO: Add error checking*/
	}

	tenu_osal_status mutex::lock(std::uint32_t u32_timeout_ms)
	{
		return osal_err_map(xSemaphoreTake(str_mtx_mem.hdl_mtx, (std::numeric_limits<std::uint32_t>::max() == u32_timeout_ms) ? portMAX_DELAY : (u32_timeout_ms / portTICK_PERIOD_MS)));
	}

	tenu_osal_status mutex::unlock(void)
	{
		return osal_err_map(xSemaphoreGive(str_mtx_mem.hdl_mtx));
	}

	tenu_osal_status mutex::del(void)
	{
		vSemaphoreDelete(str_mtx_mem.hdl_mtx);
		return osal_success;
	}

	tenu_osal_status mutex::is_held(void)
	{
		return ((xSemaphoreGetMutexHolder((xSemaphoreHandle)str_mtx_mem.hdl_mtx) == xTaskGetCurrentTaskHandle()) ? osal_success: osal_err);
	}

	std::uint32_t mutex::get_id(void)
	{
		return reinterpret_cast<std::uint32_t>(str_mtx_mem.hdl_mtx);
	}
}
