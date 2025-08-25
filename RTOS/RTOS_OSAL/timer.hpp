/**
  ******************************************************************************
  * @file			timer.hpp
  * @description  Timer class interface
  * @author			Kalb E Abbas
  * @version		V0.0
  * @date			21-June-2025
  ******************************************************************************
*/

#ifndef TIMER_H_
#define TIMER_H_

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
    using tpfn_timer_cb = void (*)(void*);
    typedef void (*tpfn_thread)(void *);

    class timer : private noncopyable
    {
    public:
        timer(const char* pch_name, uint32_t u32_period_ms, bool b_auto_reload, void* pv_timer_id, tpfn_timer_cb pfn_timer_cb);
        ~timer() = default;
        tenu_osal_status start(uint32_t u32_period_ms);
        tenu_osal_status stop(void);
        tenu_osal_status change_period(uint32_t u32_period_ms);
        tenu_osal_status is_active(void);
        void* get_id(void);
        tenu_osal_status del(void);
        std::uint32_t get_hdl(void);


    private:
        timer_mem str_timer_mem;
    };
}
#endif  /* TIMER_H_ */
