#include "bsp_led.hpp"
#include "bsp_sys.hpp"
#include "bsp_uart.hpp"
#include "bsp_spi.hpp"
#include "bsp_io.hpp"
#include "diagnostic_log.hpp"
#include "general_includes.hpp"
#include "xparameters.h"
static bsp::sys *pobj_sys{&bsp::sys::get_instance()};
static bsp::led gobj_led_0(bsp::get_led_dev(0));
static bsp::output gobj_output(bsp::get_io_dev(0));
static bsp::uart gobj_uart0{bsp::get_uart_dev(0)};
diagnostic_logger gobj_diagnostic_logger(gobj_uart0);
// static bsp::spi gobj_spi0{bsp::get_spi_dev(0)};
#define SPI_DEVICE_ID		XPAR_XSPIPS_0_DEVICE_ID
XSpiPs Spi;

void spi_init(void)
{
	XSpiPs_Config *cfg;

	cfg = XSpiPs_LookupConfig(SPI_DEVICE_ID);
	XSpiPs_CfgInitialize(&Spi, cfg, cfg->BaseAddress);

	/* IMPORTANT:
	 * - No FORCE_SSELECT
	 * - Hardware SS enabled
	 */
	XSpiPs_SetOptions(&Spi,
					  XSPIPS_MASTER_OPTION |
						  XSPIPS_CLK_PHASE_1_OPTION	| XSPIPS_FORCE_SSELECT_OPTION);

	/* AD9361-safe clock */
	XSpiPs_SetClkPrescaler(&Spi, XSPIPS_CLK_PRESCALE_64);

	XSpiPs_Enable(&Spi);

	/* Select SS0 (SPI0) */
	XSpiPs_SetSlaveSelect(&Spi, 0);
}

u8 ad9361_spi_read(u16 reg)
{
    u8 tx[3];
    u8 rx[3];

    tx[0] = (reg >> 8) & 0x7F; // READ
    tx[1] = reg & 0xFF;
    tx[2] = 0x00;

    XSpiPs_PolledTransfer(&Spi, tx, rx, 3);

    return rx[2];
}

int main()
{
	//static uint8_t au8_test[2]{0x00,0x37};
	const bsp::tstr_uart_init str_uart_init =
		{
			bsp::uart_parity_none,
			bsp::uart_stop_1_bit,
			bsp::uart_br_115200,
			false};

	gobj_uart0.init(str_uart_init);
	gobj_led_0.init();
	gobj_output.init();
	gobj_output.write(bsp::pin_state_low);
	for(volatile uint32_t i=0 ; i< 10000000; i++);
	gobj_output.write(bsp::pin_state_high);
	for(volatile uint32_t i=0 ; i< 10000000; i++);

	spi_init();
	// _ASSERT(GENERIC_SUCCESS == gobj_spi0.init(128, bsp::spi_mode_pol_low_ph_2nd_edge, true));
	// _ASSERT(GENERIC_SUCCESS == gobj_spi0.slave_enable(0));
	// _ASSERT(GENERIC_SUCCESS == gobj_spi0.tx(au8_test, 2, nullptr));
	// _ASSERT(GENERIC_SUCCESS == gobj_spi0.rx(au8_test, 1, nullptr));
	DIAGNOSTIC_LOG_STR_UINT("Reg ", ad9361_spi_read(0x037), radix_hexadecimal, true);

	DIAGNOSTIC_LOG_STR_UINT("Reg ", ad9361_spi_read(0x037), radix_hexadecimal, true);

	while(1)
	{
		DIAGNOSTIC_LOG_STR("Ticking . . ", true);
		gobj_led_0.on();
		for(volatile uint32_t i=0 ; i< 20000000; i++);
		gobj_led_0.off();
		for(volatile uint32_t i=0 ; i< 20000000; i++);
	}
	return 0;
}

void system_assertion_action(void)
{
}