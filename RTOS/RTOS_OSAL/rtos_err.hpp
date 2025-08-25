/**
  ******************************************************************************
  * @file			rtos_err.hpp
  * @description	This file define the RTOS AL errors
  * @author			Muhammad Tharwat
  * @version		V0.0
  * @date			8-June-2024
  ******************************************************************************
*/

#ifndef RTOS_ERR_H_
#define RTOS_ERR_H_

/***********************************************  Defines    **************************************************/


/***********************************************  Constants   *************************************************/

/***********************************************  Enumerations   **********************************************/

/*********************************************** Data types  **************************************************/
namespace rtos_osal
{
  enum tenu_osal_status
  {
    osal_success,
    osal_err,
    osal_err_invalid_pointer,
    osal_err_address_misaligned,
    osal_err_timeout,
    osal_err_sem_failure,
    osal_err_queue_empty,
    osal_err_queue_full,
    osal_err_queue_invalid_size,
    osal_err_name_too_long,
    osal_err_name_not_found,
    osal_err_invalid_priority,
    osal_err_not_implemented,
    osal_err_invalid_argument,
    osal_err_no_free_mem,
    osal_err_op_not_allowed
  };
}
#endif /* RTOS_ERR_H_ */
