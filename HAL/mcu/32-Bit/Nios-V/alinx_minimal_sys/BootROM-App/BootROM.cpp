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
static bsp::led<0u> *pobj_led_0{&bsp::led<0u>::get_instance()};
static bsp::led<1u> *pobj_led_1{&bsp::led<1u>::get_instance()};
static bsp::led<2u> *pobj_led_2{&bsp::led<2u>::get_instance()};
static bsp::led<3u> *pobj_led_3{&bsp::led<3u>::get_instance()};
int main(void)
{
  pobj_led_0->init();
  pobj_led_1->init();
  pobj_led_2->init();
  pobj_led_3->init();
  pobj_led_0->toggle();
  while (1)
  {
    volatile uint32_t u32_cnt;
    for(u32_cnt = 0u; u32_cnt < 2000000; u32_cnt++);
    pobj_led_0->toggle();
    pobj_led_1->toggle();
  }
  return 0;
}