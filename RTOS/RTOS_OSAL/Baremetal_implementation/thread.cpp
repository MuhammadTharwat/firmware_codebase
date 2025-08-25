/**
  ******************************************************************************
  * @file			thread.cpp
  * @description	Implementation of thread class
  * @author			Muhammad Tharwat
  * @version		V0.0
  * @date			15-June-2024
  ******************************************************************************
*/
#include <thread.hpp>
/***********************************************  Defines    **************************************************/


/***********************************************  Constants   *************************************************/

/***********************************************  Enumerations   **********************************************/

/*********************************************** Data types  **************************************************/
namespace rtos_osal
{
  thread::thread(const char *pachr_thread_name, tpfn_thread pfn_thread,
                 std::uint8_t *pu8_thread_stack, std::size_t sz_stack, tenu_thread_priority enu_priority, void *pv_args)
  {
    (void)(pachr_thread_name);
    (void)(pfn_thread);
    (void)(pu8_thread_stack);
    (void)(sz_stack);
    (void)(enu_priority);
    (void)(pv_args);
  }

  std::uint32_t thread::get_id(void)
  {
    return 0u;
  }

  tenu_osal_status thread::del(void)
  {
    return osal_success;
  }

  tenu_osal_status thread::suspend(void)
  {
    return osal_success;
  }

  tenu_osal_status thread::resume(void)
  {
    return osal_success;
  }

  tenu_osal_status delay(std::uint32_t u32_delay_ms)
  {
    (void)(u32_delay_ms);
    return osal_success;
  }
}
