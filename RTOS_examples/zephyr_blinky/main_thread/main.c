#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include "ui_thread.h"


int main(void)
{
	ui_thread_init();
	return 0;
}
