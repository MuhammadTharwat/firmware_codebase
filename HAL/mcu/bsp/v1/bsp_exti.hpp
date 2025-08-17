/**
  ******************************************************************************
  * @file			bsp_exti.hpp
  * @description	This is the header file of the bsp external interrupt pins interface
  * @author			Muhammad Tharwat
  * @version		V0.0
  * @date			10-June-2021
  ******************************************************************************
*/

#ifndef BSP_EXTI_H_
#define BSP_EXTI_H_

#include "stdint.h"
#include <stddef.h>
#include <noncopyable.hpp>
/***********************************************  Defines    **************************************************/


/***********************************************  Constants   *************************************************/

/***********************************************  Enumerations   **********************************************/

/*********************************************** Data types  **************************************************/
namespace bsp
{
	enum tenu_exti_mode
	{
		exti_edge_rising,
		exti_edge_falling,
		exti_both_edges,
		exti_high_lvl,
		exti_low_lvl,
		exti_both_lvls
	};

	using tpfn_exti_cb = void (*)(void);

	class exti_base
	{
	public:
		exti_base(void);
		~exti_base(void) = default;
		virtual std::int16_t init(void) const = 0;
		virtual void deinit(void) const = 0;
		virtual std::int16_t activate(std::uint8_t, const tpfn_exti_cb &, const tenu_exti_mode &) = 0;
		virtual void deactivate(void) const = 0;
	};

	template <std::uint8_t u8_inst>
	class exti : private noncopyable, public exti_base
	{
	public:
		~exti(void) = default;
		static exti &get_instance(void);
		std::int16_t init(void) const override;
		void deinit(void) const override;
		std::int16_t activate(std::uint8_t, const tpfn_exti_cb &, const tenu_exti_mode &) override;
		void deactivate(void) const override;

	private:
		exti(void);
		tpfn_exti_cb pfn_exti_cb;
		tenu_exti_mode enu_exti_mode;
	};
}

/******************************************      API Prototypes      *************************************/

/******************************************** Board Initialization   *************************************/

#endif /* EXTI_H_ */
