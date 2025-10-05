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
#include "bsp_spi.hpp"
#include "diagnostic_log.hpp"
#include "m25p64.hpp"
#include "general_includes.hpp"
/***********************************************  Defines    **************************************************/

/***********************************************  Constants   *************************************************/
static constexpr std::uint32_t gu32_spl_start_addr = UINT32_C(0x400000);
static constexpr std::size_t gsz_spl_size = 0x100000;
static constexpr std::size_t gsz_buff_size = 128;

/******************************************* Local Global Variables *******************************************/
//static bsp::sys *pobj_sys{&bsp::sys::get_instance()};
static bsp::led gobj_led_0(bsp::get_led_dev(0));
static bsp::led gobj_led_1(bsp::get_led_dev(1));
static bsp::led gobj_led_2(bsp::get_led_dev(2));
static bsp::led gobj_led_3(bsp::get_led_dev(3));

/*UART */
static bsp::uart gobj_uart0(bsp::get_uart_dev(0));
diagnostic_logger gobj_diagnostic_logger(gobj_uart0);

/*SPI*/
static bsp::spi gobj_spi(bsp::get_spi_dev(0));
static bsp::output gobj_output(bsp::get_io_dev(0));
static m25p64 gobj_m25p64(gobj_spi, gobj_output);

static std::uint8_t gau8_buffer[gsz_buff_size];
/******************************************* Local functions prototypes **************************************/

/******************************************* Local function implementation ***********************************/
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

  _ASSERT(GENERIC_SUCCESS == gobj_m25p64.verify_electonic_signature());
  _ASSERT(GENERIC_SUCCESS == gobj_m25p64.verify_identification());
  _ASSERT(GENERIC_SUCCESS == gobj_m25p64.read(gu32_spl_start_addr, gau8_buffer, gsz_buff_size));

  while (true)
  {
    volatile uint32_t u32_cnt;
    for(u32_cnt = 0u; u32_cnt < 200000; u32_cnt++);
    gobj_led_0.toggle();
    gobj_led_3.toggle();
    for(u32_cnt = 0u; u32_cnt < 200000; u32_cnt++);
    gobj_led_1.toggle();
    gobj_led_2.toggle();
  }
  return 0;
}

void system_assertion_action(void)
{
}