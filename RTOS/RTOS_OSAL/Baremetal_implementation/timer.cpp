/**
 ******************************************************************************
 * @file			timer.cpp
 * @description	Implementation of timer class
 * @author			Kalb E Abbas
 * @version		V0.0
 * @date			21-June-2025
 ******************************************************************************
 */
#include "timer.hpp"
/***********************************************  Defines    **************************************************/

/***********************************************  Constants   *************************************************/

/***********************************************  Enumerations   **********************************************/

/*********************************************** Data types  **************************************************/
namespace rtos_osal
{
  timer::timer(const char* pch_name, std::uint32_t u32_period_ms, bool b_auto_reload, void* pv_timer_id, tpfn_timer_cb pfn_timer_cb)
  {
    (void)pch_name;
    (void)u32_period_ms;
    (void)b_auto_reload;
    (void)pv_timer_id;
    (void)pfn_timer_cb;
  }

  tenu_osal_status timer::start(std::uint32_t u32_period_ms)
  {
    (void)u32_period_ms;
    return osal_success;
  }

  tenu_osal_status timer::stop(void)
  {
    /* Stop timer immediately with no blocking */
    return osal_success;
  }

  tenu_osal_status timer::change_period(std::uint32_t u32_period_ms)
  { 
    (void)u32_period_ms;
    return osal_success;
  }

  tenu_osal_status timer::is_active(void)
  {
    return osal_success;
  }

  tenu_osal_status timer::del(void)
  {
    return osal_success;
  }

  void* timer::get_id(void)
  {
    void* pv_timer_id = nullptr;
    return pv_timer_id;
  }

  std::uint32_t timer::get_hdl(void)
  {
    return 0;
  }
}