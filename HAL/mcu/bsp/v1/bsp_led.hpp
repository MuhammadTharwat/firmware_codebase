/**
  ******************************************************************************
  * @file			bsp_led.hpp
  * @description	This is the header file of the led bsp interface
  * @author			Muhammad Tharwat
  * @version		V0.0
  * @date			10-June-2021
  ******************************************************************************
*/

#ifndef BSP_LED_H_
#define BSP_LED_H_

#ifndef __TI_COMPILER_VERSION__
#include <cstdint>
#else
#include <stdint.h>
#endif
#include <noncopyable.hpp>
#include "bsp_objects.hpp"
/***********************************************  Defines    **************************************************/


/***********************************************  Constants   *************************************************/

/***********************************************  Enumerations   **********************************************/

/*********************************************** Data types  **************************************************/
namespace bsp
{
	class led : private noncopyable
	{
	public:
		led(led_dev &);
		~led(void) = default;
		int16_t init(void) const;
		int16_t on(void) const;
		int16_t off(void) const;
		int16_t toggle(void) const;

	private:
		led_dev &rled_dev;
	};

	led_dev &get_led_dev(uintmax_t);
}

/******************************************      API Prototypes      *************************************/

/******************************************** Board Initialization   *************************************/
#endif /* BSP_LED_H_ */
