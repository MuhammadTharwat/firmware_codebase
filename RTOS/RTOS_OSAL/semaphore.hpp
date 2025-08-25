/**
  ******************************************************************************
  * @file			semaphore.hpp
  * @description Semaphore class interface
  * @author			Kalb E Abbas
  * @version		V0.0
  * @date			24-May-2025
  ******************************************************************************
*/

#ifndef SEMA_H_
#define SEMA_H_

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
    class semaphore : private noncopyable
    {
    public:
        semaphore(std::uint32_t u32_max_count, std::uint32_t u32_initial_count);
        /* TO-DO ABBAS: revisiti default destructor if we should rely on*/
        ~semaphore() = default;
        tenu_osal_status acquire(std::uint32_t u32_timeout_ms);
        tenu_osal_status release(void);
        tenu_osal_status release_from_isr(void);
        tenu_osal_status del(void);
        std::uint32_t get_count(void);
        std::uint32_t get_id(void);

    private:
        semaphore_mem str_sem_mem;
    };
}
#endif  /* SEMA_H_ */
