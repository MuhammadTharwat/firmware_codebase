/**
  ******************************************************************************
  * @file			bsp_gint.hpp
  * @description	This is the header file of the gint bsp interface
  * @author			Muhammad Tharwat
  * @version		V0.0
  * @date			15-June-2021
  ******************************************************************************
*/

#ifndef BSP_GINT_H_
#define BSP_GINT_H_

#include "stdint.h"
#include <stddef.h>
#include <noncopyable.hpp>

/***********************************************  Defines    **************************************************/


/***********************************************  Constants   *************************************************/

/***********************************************  Enumerations   **********************************************/

/*********************************************** Data types  **************************************************/
namespace bsp
{
    struct tstr_group_interrupt_cfg
    {
        std::uint8_t *pu8_ios;
        std::uint8_t u8_num_ios;
        tpfun_gpint_cb pfun_cb;
    };
    using tpfun_gpint_cb = void (*)(void);

    class gint_base
	{
	public:
		gint_base(void) = default;
		~gint_base(void) = default;
        virtual std::int16_t cfg(const tstr_group_interrupt_cfg &) = 0;
        virtual std::int16_t enable(void) const = 0;
        virtual std::int16_t disable(void) const = 0;
	};

	template <std::uint8_t u8_inst>
	class gint : private noncopyable, public gint_base
	{
	public:
		~gint(void) = default;
        static gint &get_instance(void);
        std::int16_t cfg(const tstr_group_interrupt_cfg &) override;
        std::int16_t enable(void) const override;
        std::int16_t disable(void) const override;
	private:
		gint(void) = default;
		tstr_group_interrupt_cfg str_gint_cfg;
	};
}
