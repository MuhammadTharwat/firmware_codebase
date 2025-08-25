/**
  ******************************************************************************
  * @file			rtos_os_err_map.hpp
  * @description	This file define the error mapping file
  * @author			Ahmed Salama
  * @version		V0.0
  * @date			22-Aug-2024
  ******************************************************************************
*/

#ifndef RTOS_ERR_MAP_H_
#define RTOS_ERR_MAP_H_

#include <rtos_err.hpp>
#include "FreeRTOSConfig.h"
#include <projdefs.h>
#include "portmacro.h"
/***********************************************  Defines    **************************************************/


/***********************************************  Constants   *************************************************/

/***********************************************  Enumerations   **********************************************/

/*********************************************** Data types  **************************************************/
namespace rtos_osal
{
  tenu_osal_status osal_err_map(BaseType_t enu_status);
}
#endif /* RTOS_ERR_MAP_H_ */
