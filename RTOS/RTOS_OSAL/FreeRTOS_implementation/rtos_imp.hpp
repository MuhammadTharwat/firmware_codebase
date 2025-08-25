/**
  ******************************************************************************
  * @file			rtos_imp.hpp
  * @description	This file define the memory resources for RTOS objects
  * @author			Ahmed Salama
  * @version		V0.0
  * @date			22-Aug-2024
  ******************************************************************************
*/

#ifndef RTOS_IMP_H_
#define RTOS_IMP_H_
#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"
#include "task.h"
#include "timers.h"
#include <cstdint>
/***********************************************  Defines    **************************************************/
#ifndef MAX_THREAD_NAME_LEN
#define MAX_THREAD_NAME_LEN 48
#endif
/***********************************************  Constants   *************************************************/

/***********************************************  Enumerations   **********************************************/

/*********************************************** Data types  **************************************************/
namespace rtos_osal
{
  struct mutex_mem
  {
    SemaphoreHandle_t hdl_mtx;
    StaticSemaphore_t str_mtx_attrb;
  };

  struct semaphore_mem
  {
    SemaphoreHandle_t hdl_sem;
    StaticSemaphore_t str_sem_attrb;
  };

  struct thread_mem
  {
    char achr_name[MAX_THREAD_NAME_LEN];
    std::size_t sz_stack;
    UBaseType_t enu_priority;
    StackType_t *pstr_stack;
    TaskHandle_t hdl_thread;
    StaticTask_t str_tcb;
  };

  struct queue_mem
  {
    QueueHandle_t hdl_queue;
    StaticQueue_t str_q_attr;
    std::size_t sz_depth;
    std::size_t sz_entry;
  };

  struct timer_mem
  {
    TimerHandle_t hdl_timer;
    StaticTimer_t str_tmr_attr;
  };
}
#endif /* RTOS_IMP_H_ */
