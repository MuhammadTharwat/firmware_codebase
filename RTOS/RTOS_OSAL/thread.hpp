/**
  ******************************************************************************
  * @file			thread.hpp
  * @description	Thread class interface
  * @author			Muhammad Tharwat
  * @version		V0.0
  * @date			15-June-2024
  ******************************************************************************
*/

#ifndef THREAD_H_
#define THREAD_H_

#include <noncopyable.hpp>
#include <rtos_imp.hpp>
#include <rtos_err.hpp>
#include <cstdint>
/***********************************************  Defines    **************************************************/


/***********************************************  Constants   *************************************************/

/***********************************************  Enumerations   **********************************************/

/*********************************************** Data types  **************************************************/
namespace rtos_osal
{
	enum tenu_thread_priority
	{
		priority_very_low,
		priority_low, 
		priority_medium_low, 
		priority_medium, 
		priority_medium_high, 
		priority_high, 
		priority_very_high
	};
	typedef void (*tpfn_thread)(void *);
	class thread : private noncopyable
	{
	public:
		explicit thread(const char *pachr_thread_name, tpfn_thread pfn_thread,
						std::uint8_t *pu8_thread_stack, std::size_t sz_stack, tenu_thread_priority enu_priority, void *pv_args);
		~thread(void) = default;
		std::uint32_t get_id(void);
		tenu_osal_status del();
		tenu_osal_status start();
		tenu_osal_status suspend();
		tenu_osal_status resume();
		tenu_osal_status delay(std::uint32_t);
		tenu_osal_status flags_set(std::uint32_t);
		tenu_osal_status flags_set_from_isr(std::uint32_t);

	private:
		thread_mem str_thread_mem;
		tpfn_thread pfn_thread;
		void *pv_args;
	};

	tenu_osal_status get_task_name(char* pch_name);
	void* get_curr_task(void);
	tenu_osal_status flags_wait(std::uint32_t, std::uint32_t);
}
#endif /* THREAD_H_ */
