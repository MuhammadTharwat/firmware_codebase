/**
 ******************************************************************************
 * @file			queue.cpp
 * @description	Implementation of queue class
 * @author			Ahmed Salama
 * @version		V0.0
 * @date			22-August-2024
 ******************************************************************************
 */
#include <queue.hpp>
#include "queue.h"
#include <rtos_err_map.hpp>
#include <limits>
/***********************************************  Defines    **************************************************/

/***********************************************  Constants   *************************************************/

/***********************************************  Enumerations   **********************************************/

/*********************************************** Data types  **************************************************/
namespace rtos_osal
{
  queue::queue(const char *pachr_queue_name, std::uint32_t u32_depth, std::size_t sz_entry_size, void *pv_queue_mem)
  {
    (void) pachr_queue_name;
    str_queue_mem = {
        .hdl_queue = NULL,
        .str_q_attr = {},
        .sz_depth = u32_depth,
        .sz_entry = sz_entry_size};
    str_queue_mem.hdl_queue = xQueueCreateStatic(u32_depth, sz_entry_size, reinterpret_cast<std::uint8_t *>(pv_queue_mem), &str_queue_mem.str_q_attr);
    /*AD-TODO: Add error checking*/
  }

  tenu_osal_status queue::receive(void *pv_buff, std::size_t sz_buff_len, std::uint32_t u32_timeout_ms)
  {
    tenu_osal_status enu_osal_status = osal_err_no_free_mem;
    if (sz_buff_len < this->str_queue_mem.sz_entry)
    {
      /*Do nothing*/
    }
    else
    {
      BaseType_t enu_status;
      enu_status = xQueueReceive(this->str_queue_mem.hdl_queue, pv_buff, (std::numeric_limits<std::uint32_t>::max() == u32_timeout_ms) ? portMAX_DELAY : (u32_timeout_ms / portTICK_PERIOD_MS));
      enu_osal_status = osal_err_map(enu_status);
    }
    return enu_osal_status;
  }

  tenu_osal_status queue::receive_from_isr(void *pv_buff, std::size_t sz_buff_len)
  {
    tenu_osal_status enu_osal_status = osal_err_no_free_mem;
    BaseType_t u32_task_woken = pdFALSE;
    if (sz_buff_len < this->str_queue_mem.sz_entry)
    {
      /*Do nothing*/
    }
    else
    {
      BaseType_t enu_status;
      enu_status = xQueueReceiveFromISR(this->str_queue_mem.hdl_queue, pv_buff, &u32_task_woken);
      enu_osal_status = osal_err_map(enu_status);
    }

    if (osal_success == enu_osal_status)
    {
        portYIELD_FROM_ISR(u32_task_woken);
    }
    else
    {
      /* do nothing */
    }

    return enu_osal_status;
  }


  tenu_osal_status queue::send(const void *pv_data, std::size_t sz_buff_len, std::uint32_t u32_timeout_ms)
  {
    tenu_osal_status enu_osal_status = osal_err_no_free_mem;
    if (sz_buff_len > this->str_queue_mem.sz_entry)
    {
      /*Do nothing*/
    }
    else
    {
      BaseType_t enu_status;
      enu_status = xQueueSend(this->str_queue_mem.hdl_queue, pv_data, (std::numeric_limits<std::uint32_t>::max() == u32_timeout_ms) ? portMAX_DELAY : (u32_timeout_ms / portTICK_PERIOD_MS));
      enu_osal_status = osal_err_map(enu_status);
    }
    return enu_osal_status;
  }

  tenu_osal_status queue::send_from_isr(const void *pv_data, std::size_t sz_buff_len)
  {
    BaseType_t u32_task_woken = pdFALSE;
    tenu_osal_status enu_osal_status = osal_err_no_free_mem;

    if (sz_buff_len > this->str_queue_mem.sz_entry)
    {
      /*Do nothing*/
    }
    else
    {
      BaseType_t enu_status;
      enu_status = xQueueSendToBackFromISR(this->str_queue_mem.hdl_queue, pv_data, &u32_task_woken);
      enu_osal_status = osal_err_map(enu_status);
    }

    if (osal_success == enu_osal_status)
    {
        portYIELD_FROM_ISR(u32_task_woken);
    }
    else
    {
      /* do nothing */
    }

    return enu_osal_status;
  }

  std::uint32_t queue::get_id(void)
  {
    return reinterpret_cast<std::uint32_t>(this->str_queue_mem.hdl_queue);
  }

  tenu_osal_status queue::del(void)
  {
    vQueueDelete(this->str_queue_mem.hdl_queue);
    return osal_success;
  }
}
