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

#include "cstdint"
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
		std::int16_t init(void) const;
		std::int16_t on(void) const;
		std::int16_t off(void) const;
		std::int16_t toggle(void) const;

	private:
		led_dev &rled_dev;
	};

	led_dev &get_led_dev(std::uintmax_t);
}

/******************************************      API Prototypes      *************************************/

/******************************************** Board Initialization   *************************************/
#endif /* BSP_LED_H_ */
