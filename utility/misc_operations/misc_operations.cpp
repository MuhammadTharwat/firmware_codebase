/**
 ******************************************************************************
 * @file			misc_operations.cpp
 * @description	    This file implements the miscellaneous operations
 * @author			Muhammad Tharwat
 * @version		    V0.0
 * @date			2-September-2025
 ******************************************************************************
 */
#include "misc_operations.hpp"

/***********************************************  Defines    **************************************************/

/***********************************************  Constants   *************************************************/

/******************************************* Local Global Variables *******************************************/

/******************************************* Local functions prototypes **************************************/

/******************************************* Local function implementation ***********************************/

/******************************************      API Implementation      *************************************/
void reverse_array(void *pv_arr, uint32_t u32_arr_len)
{
    uint32_t u32_cnt;
    uint8_t u8_tmp;
    uint8_t *pu8_arr;
    _ASSERT(pv_arr != NULL);
    u32_cnt = u32_arr_len / 2;
    pu8_arr = (uint8_t *)pv_arr;
    while (u32_cnt)
    {
        u8_tmp = pu8_arr[u32_cnt - 1];
        pu8_arr[u32_cnt - 1] = pu8_arr[u32_arr_len - u32_cnt];
        pu8_arr[u32_arr_len - u32_cnt] = u8_tmp;
        u32_cnt--;
    }
}
