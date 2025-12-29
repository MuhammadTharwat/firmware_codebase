#include "bsp_led.hpp"
#include "bsp_sys.hpp"
#include "bsp_uart.hpp"
#include "bsp_spi.hpp"
#include "diagnostic_log.hpp"
#include "general_includes.hpp"

extern "C" void _init(void) {}
extern "C" void _fini(void) {}

static bsp::led gobj_led_0(bsp::get_led_dev(0));

int main()
{
	gobj_led_0.init();
	while(1)
	{
		gobj_led_0.on();
		for(volatile uint32_t i=0 ; i< 10000000; i++);
		gobj_led_0.off();
		for(volatile uint32_t i=0 ; i< 10000000; i++);
	}
	return 0;
}

void system_assertion_action(void)
{
}