/**
  ******************************************************************************
  * @file			rtos_imp.hpp
  * @description	This file define the memory resources for RTOS objects
  * @author			Muhammad Tharwat
  * @version		V0.0
  * @date			8-June-2024
  ******************************************************************************
*/

#ifndef RTOS_IMP_H_
#define RTOS_IMP_H_

/***********************************************  Defines    **************************************************/


/***********************************************  Constants   *************************************************/

/***********************************************  Enumerations   **********************************************/

/*********************************************** Data types  **************************************************/
namespace rtos_osal
{
  struct mutex_mem
  {
    void *pv;
  };

  struct thread_mem
  {
    void *pv;
  };
  
  struct queue_mem
  {
    void *pv;
  };

  struct semaphore_mem
  {
    void *pv;
  };

  struct timer_mem
  {
    void *pv;
  };
}
#endif /* RTOS_IMP_H_ */
