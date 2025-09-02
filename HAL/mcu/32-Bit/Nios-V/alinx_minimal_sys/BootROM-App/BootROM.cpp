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
#include "bsp_uart.hpp"
#include "diagnostic_log.hpp"
/***********************************************  Defines    **************************************************/

/***********************************************  Constants   *************************************************/
/******************************************* Local Global Variables *******************************************/
/******************************************* Local functions prototypes **************************************/
/******************************************* Local function implementation ***********************************/
//static bsp::sys *pobj_sys{&bsp::sys::get_instance()};
static bsp::led gobj_led_0{bsp::get_led_dev(0)};
static bsp::led gobj_led_1{bsp::get_led_dev(1)};
static bsp::led gobj_led_2{bsp::get_led_dev(2)};
static bsp::led gobj_led_3{bsp::get_led_dev(3)};

/*UART */
static bsp::uart gobj_uart0{bsp::get_uart_dev(0)};
diagnostic_logger gobj_diagnostic_logger(gobj_uart0);
int main(void)
{
  const bsp::tstr_uart_init str_uart_init = 
  {
    bsp::uart_parity_none,
    bsp::uart_stop_1_bit,
    bsp::uart_br_115200,
    false
  };
  gobj_led_0.init();
  gobj_led_1.init();
  gobj_led_2.init();
  gobj_led_3.init();

  gobj_led_0.toggle();
  gobj_led_1.toggle();
  
  gobj_uart0.init(str_uart_init);
  while (1)
  {
    volatile uint32_t u32_cnt;
    for(u32_cnt = 0u; u32_cnt < 2000000; u32_cnt++);
    gobj_led_0.toggle();
    gobj_led_3.toggle();
    for(u32_cnt = 0u; u32_cnt < 2000000; u32_cnt++);
    gobj_led_1.toggle();
    gobj_led_2.toggle();
    DIAGNOSTIC_LOG_STR("Ticking", true);
  }
  return 0;
}