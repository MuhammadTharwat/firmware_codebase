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
/***********************************************  Defines    **************************************************/


/***********************************************  Constants   *************************************************/

/***********************************************  Enumerations   **********************************************/

/*********************************************** Data types  **************************************************/
namespace rtos_osal
{
  semaphore::semaphore(std::uint32_t u32_max_count, std::uint32_t u32_initial_count)
  {
    (void)u32_max_count;
    (void)u32_initial_count;
  }

  tenu_osal_status semaphore::acquire(std::uint32_t u32_timeout_ms)
  {
    (void)u32_timeout_ms;
		return osal_success;
  }
  tenu_osal_status semaphore::release(void)
  {
		return osal_success;
  }

  tenu_osal_status semaphore::release_from_isr(void)
  {
    return osal_success;
  }

  tenu_osal_status semaphore::del(void)
  {
    return osal_success;
  }

  uint32_t semaphore::get_count(void)
  {
    return 0;
  }

  std::uint32_t semaphore::get_id(void)
  {
    return 0;
  }
}
