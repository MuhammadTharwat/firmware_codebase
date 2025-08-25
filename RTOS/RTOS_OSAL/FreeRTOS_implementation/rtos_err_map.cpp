/**
  ******************************************************************************
  * @file			rtos_os_err_map.cpp
  * @description	This file define the error mapping file
  * @author			Ahmed Salama
  * @version		V0.0
  * @date			22-Aug-2024
  ******************************************************************************
*/
#include <cstdint>
#include <rtos_err.hpp>
#include <rtos_err_map.hpp>
/***********************************************  Defines    **************************************************/


/***********************************************  Constants   *************************************************/

/***********************************************  Enumerations   **********************************************/

/*********************************************** Data types  **************************************************/
namespace rtos_osal
{
  tenu_osal_status osal_err_map(BaseType_t enu_status)
  {
    tenu_osal_status enu_osal_err = osal_err;
    switch(enu_status)
    {
      case pdTRUE:
      {
        enu_osal_err = osal_success;
        break; 
      }

      case pdFAIL:
      {
        enu_osal_err = osal_err;
        break; 
      }

      case errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY:
      {
        enu_osal_err = osal_err_no_free_mem;
        break; 
      }

      case errQUEUE_YIELD:
      {
        enu_osal_err = osal_err_queue_full;
        break; 
      }

      case errQUEUE_BLOCKED:
      {
        enu_osal_err = osal_err_op_not_allowed;
        break; 
      }

      default:
      {
        break; 
      }
    }
    return enu_osal_err;
  }
}
