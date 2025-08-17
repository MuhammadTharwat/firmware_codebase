/**
  ******************************************************************************
  * @file			bsp_lptime.hpp
  * @description	This is the header file of the board support package "lptim"
  * @author			Ahmed Salama
  * @version		V0.0
  * @date			08-April-2024
  ******************************************************************************
*/
#ifndef BSP_LPTIM_H_
#define BSP_LPTIM_H_

#include "stdint.h"
#include <stddef.h>
#include <noncopyable.hpp>
/***********************************************  Defines    **************************************************/
/***********************************************  Constants   *************************************************/
/***********************************************  Enumerations   **********************************************/
/*********************************************** Data types  **************************************************/
namespace bsp
{
    using tpfun_lp_timer_cb = void (*)(std::uint32_t );

    class lptim_base
    {
        public:
            lptim_base(void) = default;
            ~lptim_base(void) = default;
            virtual std::int16_t init(void) const = 0;
            virtual std::int16_t deinit(void) const = 0;
            virtual std::int16_t start(std::uint32_t , tpfun_cb ) = 0;
            virtual std::int16_t stop(void) const = 0;
            virtual std::int16_t get_tick(std::uint32_t &) const = 0;
            virtual std::int16_t get_elapsed_time(std::uint32_t , std::uint32_t &) const = 0;
            virtual std::uint32_t get_min_timeout(void) const = 0;
            virtual std::uint32_t ms_to_tick(std::uint32_t) const = 0;
            virtual std::uint32_t tick_to_ms(std::uint32_t) const = 0;
    };

    template <typename timer_bit_size, std::uint8_t u8_inst>
    class lptim : private noncopyable, public lptim_base
    {
        public:
            ~lptim(void) = default;
            static lptim &get_instance(void);
            std::int16_t init(void) const override;
            std::int16_t deinit(void) const override;
            std::int16_t start(std::uint32_t , tpfun_cb ) override;
            std::int16_t stop(void) const override;
            std::int16_t get_tick(std::uint32_t &) const override;
            std::int16_t get_elapsed_time(std::uint32_t , std::uint32_t &) const override;
            std::uint32_t get_min_timeout(void) const override;
            std::uint32_t ms_to_tick(std::uint32_t) const override;
            std::uint32_t tick_to_ms(std::uint32_t) const override;
        private:
            lptim(void) = default;
            tpfun_timer_cb pfun_cb;
            std::uint32_t u32_min_timeout;
    };
}