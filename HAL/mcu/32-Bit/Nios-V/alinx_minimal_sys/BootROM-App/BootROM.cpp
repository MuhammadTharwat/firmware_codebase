/**
 ******************************************************************************
 * @file			app.c
 * @description	This file implements the blinky demo for NIOS-V CPU
 * @author			Muhammad Tharwat
 * @version		V0.0
 * @date			17-Jun-2025
 ******************************************************************************
 */


/***********************************************  Defines    **************************************************/

/***********************************************  Constants   *************************************************/

/******************************************* Local Global Variables *******************************************/

/******************************************* Local functions prototypes **************************************/

/******************************************* Local function implementation ***********************************/

#include "bsp_led.hpp"
#include "bsp_sys.hpp"
/***********************************************  Defines    **************************************************/

/***********************************************  Constants   *************************************************/
/******************************************* Local Global Variables *******************************************/
/******************************************* Local functions prototypes **************************************/
/******************************************* Local function implementation ***********************************/
//static bsp::sys *pobj_sys{&bsp::sys::get_instance()};
static bsp::led obj_led_0{bsp::get_led_dev(0)};
static bsp::led obj_led_1{bsp::get_led_dev(1)};
static bsp::led obj_led_2{bsp::get_led_dev(2)};
static bsp::led obj_led_3{bsp::get_led_dev(3)};
int main(void)
{
  obj_led_0.init();
  obj_led_1.init();
  obj_led_2.init();
  obj_led_3.init();

  obj_led_0.toggle();
  obj_led_1.toggle();
  while (1)
  {
    volatile uint32_t u32_cnt;
    for(u32_cnt = 0u; u32_cnt < 2000000; u32_cnt++);
    obj_led_0.toggle();
    obj_led_3.toggle();
    for(u32_cnt = 0u; u32_cnt < 2000000; u32_cnt++);
    obj_led_1.toggle();
    obj_led_2.toggle();
  }
  return 0;
}