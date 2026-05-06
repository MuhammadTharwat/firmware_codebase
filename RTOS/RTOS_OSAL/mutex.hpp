/**
  ******************************************************************************
  * @file			mutex.hpp
  * @description	Mutex class interface
  * @author			Muhammad Tharwat
  * @version		V0.0
  * @date			8-June-2024
  ******************************************************************************
*/

#ifndef MUTEX_H_
#define MUTEX_H_

#include <noncopyable.hpp>
#include <rtos_imp.hpp>
#include <rtos_err.hpp>
#ifndef __TI_COMPILER_VERSION__
#include <cstdint>
#else
#include <stdint.h>
#endif
/***********************************************  Defines    **************************************************/


/***********************************************  Constants   *************************************************/

/***********************************************  Enumerations   **********************************************/

/*********************************************** Data types  **************************************************/
namespace rtos_osal
{
	class mutex : private noncopyable
	{
	public:
		mutex(void);
		~mutex(void) = default;
		tenu_osal_status lock(uint32_t);
		tenu_osal_status unlock(void);
		tenu_osal_status del(void);
		tenu_osal_status is_held(void);
		uint32_t get_id(void);

	private:
		mutex_mem str_mtx_mem;
	};
}
#endif /* MUTEX_H_ */
