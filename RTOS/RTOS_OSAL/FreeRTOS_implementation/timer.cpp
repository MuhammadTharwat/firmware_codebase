/**
 ******************************************************************************
 * @file			timer.cpp
 * @description	Implementation of timer class
 * @author			Kalb E Abbas
 * @version		V0.0
 * @date			21-June-2025
 ******************************************************************************
 */
#include "FreeRTOS.h"
#include "timers.h"
#include <rtos_err_map.hpp>
#include <limits>
#include "timer.hpp"
/***********************************************  Defines    **************************************************/

/***********************************************  Constants   *************************************************/

/***********************************************  Enumerations   **********************************************/

/*********************************************** Data types  **************************************************/
namespace rtos_osal
{
  timer::timer(const char* pch_name, std::uint32_t u32_period_ms, bool b_auto_reload, void* pv_timer_id, tpfn_timer_cb pfn_timer_cb)
  {
    str_timer_mem = {
    .hdl_timer = NULL,
    .str_tmr_attr = {}
    };
    UBaseType_t u32_auto_reload = pdFALSE;

    if(true == b_auto_reload)
    {
      u32_auto_reload = pdTRUE;
    }
    else
    {
      /* do nothing */
    }

    str_timer_mem.hdl_timer = xTimerCreateStatic(pch_name, u32_period_ms, u32_auto_reload, pv_timer_id, (TimerCallbackFunction_t)pfn_timer_cb, &str_timer_mem.str_tmr_attr);
  }

  tenu_osal_status timer::start(std::uint32_t u32_period_ms)
  {
    return osal_err_map(xTimerStart(str_timer_mem.hdl_timer, u32_period_ms));
  }

  tenu_osal_status timer::stop(void)
  {
    /* Stop timer immediately with no blocking */
    return osal_err_map(xTimerStop(str_timer_mem.hdl_timer, 0));
  }

  tenu_osal_status timer::change_period(std::uint32_t u32_period_ms)
  { 
    return osal_err_map(xTimerChangePeriod(str_timer_mem.hdl_timer, (TickType_t)u32_period_ms, 0));
  }

  tenu_osal_status timer::is_active(void)
  {
    return osal_err_map(xTimerIsTimerActive(str_timer_mem.hdl_timer));
  }

  tenu_osal_status timer::del(void)
  {
    return osal_err_map(xTimerDelete(str_timer_mem.hdl_timer, 0));
  }

  void* timer::get_id(void)
  {
    return pvTimerGetTimerID(str_timer_mem.hdl_timer);
  }

  std::uint32_t timer::get_hdl(void)
  {
    return reinterpret_cast<std::uint32_t>(str_timer_mem.hdl_timer);
  }
}