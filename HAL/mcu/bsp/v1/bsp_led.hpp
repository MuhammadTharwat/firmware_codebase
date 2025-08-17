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

/***********************************************  Defines    **************************************************/


/***********************************************  Constants   *************************************************/

/***********************************************  Enumerations   **********************************************/

/*********************************************** Data types  **************************************************/
namespace bsp
{
	class led_base
	{
	public:
		led_base(void) = default;
		~led_base(void) = default;
		virtual void init(void) const = 0;
		virtual void on(void) const = 0;
		virtual void off(void) const = 0;
		virtual void toggle(void) const = 0;
	};

	template <std::uintmax_t uint_led_nr>
	class led : private noncopyable, public virtual led_base
	{
	public:
		~led(void) = default;
		static led &get_instance(void);
		void init(void) const override;
		void on(void) const override;
		void off(void) const override;
		void toggle(void) const override;

	private:
		led(void) = default;
	};
}

/******************************************      API Prototypes      *************************************/

/******************************************** Board Initialization   *************************************/
#endif /* BSP_LED_H_ */
