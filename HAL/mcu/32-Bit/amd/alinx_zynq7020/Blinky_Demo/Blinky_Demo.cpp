#include "bsp_led.hpp"
#include "bsp_sys.hpp"
#include "bsp_uart.hpp"
#include "bsp_spi.hpp"
#include "bsp_io.hpp"
#include "diagnostic_log.hpp"
#include "general_includes.hpp"
static bsp::sys *pobj_sys{&bsp::sys::get_instance()};
static bsp::led gobj_led_0(bsp::get_led_dev(0));
static bsp::led gobj_led_1(bsp::get_led_dev(1));
static bsp::led gobj_led_2(bsp::get_led_dev(2));
static bsp::uart gobj_uart0{bsp::get_uart_dev(0)};
diagnostic_logger gobj_diagnostic_logger(gobj_uart0);

int main()
{
	const bsp::tstr_uart_init str_uart_init =
		{
			bsp::uart_parity_none,
			bsp::uart_stop_1_bit,
			bsp::uart_br_115200,
			false};

	gobj_uart0.init(str_uart_init);
	gobj_led_0.init();
	gobj_led_1.init();	
	gobj_led_2.init();	
	while(1)
	{
		DIAGNOSTIC_LOG_STR("Ticking . . ", true);
		gobj_led_0.on();
		gobj_led_1.off();
		gobj_led_2.on();
		for(volatile uint32_t i=0 ; i< 20000000; i++);
		gobj_led_0.off();
		gobj_led_1.on();
		gobj_led_2.off();
		for(volatile uint32_t i=0 ; i< 20000000; i++);
	}
	return 0;
}

void system_assertion_action(void)
{
}