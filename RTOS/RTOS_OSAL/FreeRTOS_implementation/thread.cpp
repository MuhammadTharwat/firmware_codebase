/**
  ******************************************************************************
  * @file			thread.cpp
  * @description	Implementation of thread class
  * @author			Ahmed Salama
  * @version		V0.0
  * @date			22-Aug-2024
  ******************************************************************************
*/
#include <thread.hpp>
#include "task.h"
#include <rtos_err_map.hpp>
#include <cstring>
#include "common.h"
/***********************************************  Defines    **************************************************/


/***********************************************  Constants   *************************************************/

/***********************************************  Enumerations   **********************************************/

/*********************************************** Data types  **************************************************/
namespace rtos_osal
{
  thread::thread(const char *pachr_thread_name, tpfn_thread pfn_thread,
                 std::uint8_t *pu8_thread_stack, std::size_t sz_stack, tenu_thread_priority enu_priority, void *pv_args)
      : str_thread_mem{
              {0},
              sz_stack / sizeof(StackType_t),
              enu_priority,
              (reinterpret_cast<StackType_t *>(pu8_thread_stack)),
              nullptr,
              {}},
        pfn_thread(pfn_thread),
        pv_args(pv_args)

  {
    std::uint8_t u8_len = 0;
    if (nullptr == pachr_thread_name)
    {
      /*Do nothing*/
    }
    else
    {
      u8_len = ((MAX_THREAD_NAME_LEN - 1) > strlen(pachr_thread_name)) ? strlen(pachr_thread_name) : (MAX_THREAD_NAME_LEN - 1);
      MEM_CPY(str_thread_mem.achr_name, pachr_thread_name, u8_len);
    }
    str_thread_mem.achr_name[u8_len] = '\0';
  }

  tenu_osal_status thread::start(void)
  {
    const char *pch_tmp = str_thread_mem.achr_name;
    str_thread_mem.hdl_thread = xTaskCreateStatic(pfn_thread, pch_tmp, str_thread_mem.sz_stack, pv_args, str_thread_mem.enu_priority, str_thread_mem.pstr_stack, &str_thread_mem.str_tcb);
    return ((nullptr != str_thread_mem.hdl_thread) ? osal_success : osal_err);
  }

  std::uint32_t thread::get_id(void)
  {
    return reinterpret_cast<std::uint32_t>(str_thread_mem.hdl_thread);
  }

  tenu_osal_status thread::del(void)
  {
    vTaskDelete(str_thread_mem.hdl_thread);
    return osal_success;
  }

  tenu_osal_status thread::suspend(void)
  {
    vTaskSuspend(str_thread_mem.hdl_thread);
    return osal_success;
  }

  tenu_osal_status thread::resume(void)
  {
    vTaskResume(str_thread_mem.hdl_thread);
    return osal_success;
  }

  tenu_osal_status thread::delay(std::uint32_t u32_delay_ms)
  {
    vTaskDelay(u32_delay_ms);
    return osal_success;
  }

  tenu_osal_status get_task_name(char* pch_name)
  {
    (void)pch_name;
    xTaskHandle str_task_hdl = xTaskGetCurrentTaskHandle();
    pch_name = pcTaskGetName(str_task_hdl);
    return osal_success;
  }

  tenu_osal_status thread::flags_set(std::uint32_t u32_flags)
  {
    return osal_err_map(xTaskNotify(str_thread_mem.hdl_thread, u32_flags, eSetBits));
  }

  tenu_osal_status flags_wait(std::uint32_t u32_flags, std::uint32_t u32_timeout)
  {
    uint32_t u32_flag_val = 0;
    tenu_osal_status enu_osal_status = osal_err;
    TickType_t u32_ticks = portMAX_DELAY;

    if (UINT32_MAX > u32_timeout)
    {
        u32_ticks = pdMS_TO_TICKS(u32_timeout);
    }
    else
    {
        /* do nothing */
    }
    
    enu_osal_status = osal_err_map(xTaskNotifyWait(0x00, 0xFFFFFFFFUL, &u32_flag_val, u32_ticks));

    if(osal_success == enu_osal_status)
    {
      enu_osal_status = ((u32_flag_val == u32_flags) ? osal_success: osal_err);
    }
    else
    {
      /* do nothing */
    }

    return enu_osal_status;
  }

  tenu_osal_status thread::flags_set_from_isr(std::uint32_t u32_flags_val)
  {
    BaseType_t u32_high_task_awoken = pdFALSE;
    tenu_osal_status enu_osal_status = osal_err_map(xTaskNotifyFromISR(str_thread_mem.hdl_thread, u32_flags_val, eSetBits, &u32_high_task_awoken));

    if (osal_success == enu_osal_status)
    {
        portYIELD_FROM_ISR(u32_high_task_awoken);
    }
    else
    {
      /* do nothing */
    }

    return enu_osal_status;

  }

  void* get_curr_task(void)
  {
    return xTaskGetCurrentTaskHandle();
  }

}
