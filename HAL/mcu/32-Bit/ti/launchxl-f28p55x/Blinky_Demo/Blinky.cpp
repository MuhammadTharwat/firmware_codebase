/**
 ******************************************************************************
 * @file			Blinky.c
 * @description	This file implements the blinky demo for launchxl-f28p55x
 * @author			Muhammad Tharwat
 * @version		V0.0
 * @date			04-May-2026
 ******************************************************************************
 */


/***********************************************  Defines    **************************************************/

/***********************************************  Constants   *************************************************/

/******************************************* Local Global Variables *******************************************/

/******************************************* Local functions prototypes **************************************/

/******************************************* Local function implementation ***********************************/

#include "diagnostic_log.hpp"
#include "general_includes.hpp"
#include <bsp_led.hpp>
#include <bsp_sys.hpp>
/***********************************************  Defines    **************************************************/

/***********************************************  Constants   *************************************************/

/******************************************* Local Global Variables *******************************************/
static bsp::sys *pobj_sys(&bsp::sys::get_instance());
/******************************************* Local functions prototypes **************************************/

/******************************************* Local function implementation ***********************************/
int main(void)
{
  bsp::led obj_led_red(bsp::get_led_dev(0));
  bsp::led obj_led_green(bsp::get_led_dev(1));
  obj_led_red.init();
  obj_led_green.init();
  obj_led_red.on();
  obj_led_green.off();
  while (true)
  {
    pobj_sys->delay_us(200000);
    obj_led_red.toggle();
    obj_led_green.toggle();
  }
}

void system_assertion_action(void)
{
}
