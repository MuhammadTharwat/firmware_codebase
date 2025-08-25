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
/***********************************************  Defines    **************************************************/

/***********************************************  Constants   *************************************************/

/***********************************************  Enumerations   **********************************************/

/*********************************************** Data types  **************************************************/
namespace rtos_osal
{
  queue::queue(const char *pachr_queue_name, std::uint32_t u32_depth, std::size_t sz_entry_size, void *pv_queue_mem)
  {
    (void)pachr_queue_name;
    (void)u32_depth;
    (void)sz_entry_size;
    (void)pv_queue_mem;
    (void)pv_queue_mem;
  }

  tenu_osal_status queue::receive(void *pv_buff, std::size_t sz_buff_len, std::uint32_t u32_timeout_ms)
  {
    (void)pv_buff;
    (void)sz_buff_len;
    (void)u32_timeout_ms;
    return osal_success;
  }

  tenu_osal_status queue::receive_from_isr(void *pv_buff, std::size_t sz_buff_len)
  {
    (void)pv_buff;
    (void)sz_buff_len;
    return osal_success;
  }


  tenu_osal_status queue::send(const void *pv_data, std::size_t sz_buff_len, std::uint32_t u32_timeout_ms)
  {
    (void)pv_data;
    (void)sz_buff_len;
    (void)u32_timeout_ms;
    return osal_success;
  }

  tenu_osal_status queue::send_from_isr(const void *pv_data, std::size_t sz_buff_len)
  {
    (void)pv_data;
    (void)sz_buff_len;
    return osal_success;
  }

  std::uint32_t queue::get_id(void)
  {
    return 0;
  }

  tenu_osal_status queue::del(void)
  {
    return osal_success;
  }
}
