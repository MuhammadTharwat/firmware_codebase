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

#include <alt_types.h>
#include <altera_avalon_pio_regs.h>
#include <stdio.h>
#include "system.h"

extern "C" {
#include "priv/alt_busy_sleep.h"
  }


int main(void)
{

  IOWR_ALTERA_AVALON_PIO_DIRECTION(PIO_0_BASE,0xF);
  IOWR_ALTERA_AVALON_PIO_DATA(PIO_0_BASE,0x0F);
  while (1)
  {
    alt_busy_sleep(100000);
    IOWR_ALTERA_AVALON_PIO_DATA(PIO_0_BASE,0x05);
    alt_busy_sleep(100000);
    IOWR_ALTERA_AVALON_PIO_DATA(PIO_0_BASE,0x0F);
  }
}