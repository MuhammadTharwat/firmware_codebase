#include "stdio.h"
// #include "xparameters.h"
// #include "xgpiops.h"
// #include "xil_misc_psreset_api.h"

#define GPIO_DEVICE_ID		XPAR_XGPIOPS_0_DEVICE_ID
#define LED_GPIO_PIN		0


// void _init(void) {}
// void _fini(void) {}
// void _exit(int status) {
//     while (1) {
//         // hang here indefinitely
//     }
// }


int main()
{
	// /* Initialize the GPIO driver. */
	// XGpioPs_Config *ConfigPtr;
	// /* Unlock the slcr register access lock */
	// Xil_Out32(XSLCR_UNLOCK_ADDR, XSLCR_UNLOCK_CODE);

	// Xil_Out32(XSLCR_MIO_PIN_00_ADDR, 0x00000600);

	// ConfigPtr = XGpioPs_LookupConfig(GPIO_DEVICE_ID);
	// /* The driver instance for GPIO Device. */
	// XGpioPs Gpio;
	// XGpioPs_CfgInitialize(&Gpio, ConfigPtr,ConfigPtr->BaseAddr);
	// /*
	//  * Set the direction for the pin to be output and
	//  * Enable the Output enable for the LED Pin.
	//  * */
	// XGpioPs_SetDirectionPin(&Gpio, LED_GPIO_PIN, 1);
	// XGpioPs_SetOutputEnablePin(&Gpio, LED_GPIO_PIN, 1);

	while(1)
	{
		// /* Set the GPIO output to be high. */
		// XGpioPs_WritePin(&Gpio, LED_GPIO_PIN, 0x0);
		// for(volatile uint32_t i=0 ; i< 10000000; i++);
		// /* Set the GPIO output to be low. */
		// XGpioPs_WritePin(&Gpio, LED_GPIO_PIN, 0x1);
		// for(volatile uint32_t i=0 ; i< 10000000; i++);
	}
	return 0;
}

void system_assertion_action(void)
{
}