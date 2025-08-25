/**
  ******************************************************************************
  * @file			mutex.cpp
  * @description	Implementation of mutex class
  * @author			Muhammad Tharwat
  * @version		V0.0
  * @date			8-June-2024
  ******************************************************************************
*/
#include <mutex.hpp>
/***********************************************  Defines    **************************************************/


/***********************************************  Constants   *************************************************/

/***********************************************  Enumerations   **********************************************/

/*********************************************** Data types  **************************************************/
namespace rtos_osal
{
	mutex::mutex(void)
	{

	}

	tenu_osal_status mutex::lock(std::uint32_t u32_timeout_ms)
	{
		(void)(u32_timeout_ms);
		return osal_success;
	}

	tenu_osal_status mutex::unlock(void)
	{
		return osal_success;
	}
}
