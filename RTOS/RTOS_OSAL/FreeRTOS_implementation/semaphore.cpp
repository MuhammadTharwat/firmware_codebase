/**
  ******************************************************************************
  * @file			semaphore.cpp
  * @description	Implementation of semaphore class
  * @author			Kalb E Abbas
  * @version		V0.0
  * @date			24-May-2025
  ******************************************************************************
*/
#include <semaphore.hpp>
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
  semaphore::semaphore(std::uint32_t u32_max_count, std::uint32_t u32_initial_count)
  {
		str_sem_mem.hdl_sem = xSemaphoreCreateCountingStatic(u32_max_count, u32_initial_count, &this->str_sem_mem.str_sem_attrb);
  }

  tenu_osal_status semaphore::acquire(std::uint32_t u32_timeout_ms)
  {
		return osal_err_map(xSemaphoreTake(str_sem_mem.hdl_sem, (std::numeric_limits<std::uint32_t>::max() == u32_timeout_ms) ? portMAX_DELAY : (u32_timeout_ms / portTICK_PERIOD_MS)));
  }
  tenu_osal_status semaphore::release(void)
  {
		return osal_err_map(xSemaphoreGive(str_sem_mem.hdl_sem));
  }

  tenu_osal_status semaphore::release_from_isr(void)
  {
    tenu_osal_status enu_osal_status = osal_err;

    BaseType_t u32_high_task_awoken = pdFALSE;
    enu_osal_status = osal_err_map(xSemaphoreGiveFromISR(str_sem_mem.hdl_sem, &u32_high_task_awoken));

    if (osal_success != enu_osal_status)
    {
      /* do nothing */
    }
    else
    {
      portYIELD_FROM_ISR(u32_high_task_awoken);
    }

    return enu_osal_status;
  }

  tenu_osal_status semaphore::del(void)
  {
    vSemaphoreDelete(str_sem_mem.hdl_sem);
    return osal_success;
  }

  uint32_t semaphore::get_count(void)
  {
    return uxSemaphoreGetCount(str_sem_mem.hdl_sem);
  }

  std::uint32_t semaphore::get_id(void)
  {
    return reinterpret_cast<std::uint32_t>(str_sem_mem.hdl_sem);
  }
}
