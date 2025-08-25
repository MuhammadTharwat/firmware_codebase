/**
  ******************************************************************************
  * @file			rtos_al.hpp
  * @description	RTOS AL class interface
  * @author			Muhammad Tharwat
  * @version		V0.0
  * @date			8-June-2024
  ******************************************************************************
*/

#ifndef RTOS_AL_H_
#define RTOS_AL_H_

#include <mutex.hpp>
#include <thread.hpp>
/***********************************************  Defines    **************************************************/


/***********************************************  Constants   *************************************************/

/***********************************************  Enumerations   **********************************************/

/*********************************************** Data types  **************************************************/
namespace rtos_osal
{
  typedef enum
  {
    kernel_running = 0,
    kernel_not_running,
    kernel_stopped,
    kernel_ready
  }tenu_osal_kernel_status;

  tenu_osal_status kernel_init(void);
  tenu_osal_status kernel_start(void);
  tenu_osal_kernel_status kernel_status(void);
  tenu_osal_status kernel_suspend(std::uint32_t &u32_suspend_time_ms);
  tenu_osal_status kernel_resume(std::uint32_t u32_suspend_time_ms);
  std::uint32_t kernel_get_ticks(void);
  std::uint32_t kernel_get_ms(void);
  tenu_osal_status kernel_delay(std::uint32_t u32_dly_ticks);
}
#endif /* RTOS_AL_H_ */
