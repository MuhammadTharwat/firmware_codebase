/**
 ******************************************************************************
 * @file			app.c
 * @description	This file implements the Boot ROM application for Alinx NIOS-II BSP
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
static constexpr std::uint32_t gu32_spl_flash_start_addr = UINT32_C(0x400000);
static constexpr std::size_t gsz_spl_size = 0x100000;
static constexpr std::uint32_t gu32_spl_main_memory_start_addr = UINT32_C(0x20000000);
/******************************************* Local Global Variables *******************************************/
static bsp::sys *pobj_sys{&bsp::sys::get_instance()};
/*SPI*/
static bsp::spi gobj_spi(bsp::get_spi_dev(0));
static bsp::output gobj_output(bsp::get_io_dev(0));
static m25p64 gobj_m25p64(gobj_spi, gobj_output);
/******************************************* Local functions prototypes **************************************/

/******************************************* Local function implementation ***********************************/
int main(void)
{
  _ASSERT(GENERIC_SUCCESS == gobj_m25p64.verify_electonic_signature());
  _ASSERT(GENERIC_SUCCESS == gobj_m25p64.verify_identification());
  _ASSERT(GENERIC_SUCCESS == gobj_m25p64.read(gu32_spl_flash_start_addr, reinterpret_cast<void *>(gu32_spl_main_memory_start_addr), gsz_spl_size));
  pobj_sys->boot_image(gu32_spl_main_memory_start_addr);
  while (true)
  {
  }
  return 0;
}

void system_assertion_action(void)
{
}