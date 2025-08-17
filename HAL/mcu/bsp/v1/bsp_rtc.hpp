/**
  ******************************************************************************
  * @file			bsp_rtc.hpp
  * @description	This is the header file of the RTC bsp interface
  * @author			Ahmed Salama
  * @version		V0.0
  * @date			09-Feb-2024
  ******************************************************************************
*/

#ifndef BSP_RTC_H_
#define BSP_RTC_H_

#include "stdint.h"
#include <stddef.h>
#include <noncopyable.hpp>

/***********************************************  Defines    **************************************************/


/***********************************************  Constants   *************************************************/

/***********************************************  Enumerations   **********************************************/

/*********************************************** Data types  **************************************************/
namespace bsp
{
    typedef struct
    {
        /* Time 24-hour system*/
        std::uint8_t u8_hour;
        std::uint8_t u8_minute;
        std::uint8_t u8_second;
        /* Date */
        std::uint16_t u16_year;
        std::uint8_t u8_month;
        std::uint8_t u8_day;
    } tstr_rtc_date_time;
    using tpfun_rtc_alarm_cb = void (*)(void);

    class rtc_base
    {
        public:
            rtc_base(void) = default;
            ~rtc_base(void) = default;
            virtual std::int16_t set_date(const tstr_rtc_date_time &) const = 0;
            virtual std::int16_t get_date(tstr_rtc_date_time &) const = 0;
            virtual std::int16_t set_alarm(const tstr_rtc_date_time &, tpfun_rtc_alarm_cb ) = 0;
            virtual std::int16_t stop_alarm(void) const = 0;
    };

    template <std::uint8_t u8_inst>
    class rtc : private noncopyable, public rtc_base
    {
        public:
            ~rtc(void) = default;
            static rtc &get_instance(void);
            std::int16_t set_date(const tstr_rtc_date_time &) const override;
            std::int16_t get_date(tstr_rtc_date_time &) const override;
            std::int16_t set_alarm(const tstr_rtc_date_time &, tpfun_rtc_alarm_cb ) override;
            std::int16_t stop_alarm(void) const override;
        private:
            rtc(void) = default;
            tpfun_rtc_alarm_cb pfun_cb;
            tstr_rtc_date_time str_alarm_time;
    };
}