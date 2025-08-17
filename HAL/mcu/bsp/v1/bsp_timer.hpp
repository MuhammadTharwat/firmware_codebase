/**
  ******************************************************************************
  * @file			bsp_timer.hpp
  * @description	This is the header file of the timer bsp interface
  * @author			Muhammad Tharwat
  * @version		V0.0
  * @date			15-June-2021
  ******************************************************************************
*/

#ifndef BSP_TIMER_H_
#define BSP_TIMER_H_

#include "stdint.h"
#include <stddef.h>
#include <noncopyable.hpp>

/***********************************************  Defines    **************************************************/


/***********************************************  Constants   *************************************************/

/***********************************************  Enumerations   **********************************************/

/*********************************************** Data types  **************************************************/
namespace bsp
{
	using tpfn_timer_cb = void (*)(std::uint32_t);

	class timer_base
	{
	public:
		timer_base(void) = default;
		~timer_base(void) = default;
		virtual void init(void) const = 0;
		virtual void deinit(void) const = 0;
		virtual void start(const uint32_timer_cb, std::uint32_t) = 0;
		virtual void stop(void) const = 0;
		virtual std::uint32_t get_tick(void) const = 0;
		virtual std::uint32_t get_elapsed_time(std::uint32_t) const = 0;
		virtual std::uint32_t get_min_timeout_ticks(void) const = 0;
		virtual std::int16_t ms_to_tick(float, std::uint32_t &) const = 0;
		virtual float tick_to_ms(std::uint32_t) const = 0;
		virtual std::int16_t delay_ms(std::uint32_t) const = 0;
		virtual std::int16_t delay_us(std::uint32_t) const = 0;
	};

	template <typename timer_bit_size, std::uint8_t u8_inst>
	class timer : private noncopyable, public timer_base
	{
	public:
		~timer(void) = default;
		static timer &get_instance(void);
		void init(void) const override;
		void deinit(void) const override;
		void start(const uint32_timer_cb, std::uint32_t) override;
		void stop(void) const override;
		std::uint32_t get_tick(void) const override;
		std::uint32_t get_elapsed_time(std::uint32_t) const override;
		std::uint32_t get_min_timeout_ticks(void) const override;
		std::int16_t ms_to_tick(float, std::uint32_t &) const override;
		float tick_to_ms(std::uint32_t) const override;
		std::int16_t delay_ms(std::uint32_t) const override;
		std::int16_t delay_us(std::uint32_t) const override;
	private:
		timer(void) = default;
		tpfn_timer_cb pfn_timer_cb;
	};
}
/******************************************      API Prototypes      *************************************/

/******************************************** Board Initialization   *************************************/
#endif /* BSP_TIMER_H_ */
