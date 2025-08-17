/**
  ******************************************************************************
  * @file			bsp_fet.hpp
  * @description	This is the header file of the bsp external interrupt pins interface
  * @author			Ahmed Salama
  * @version		V0.0
  * @date			12-Feb-2024
  ******************************************************************************
*/

#ifndef BSP_FET_H_
#define BSP_FET_H_

#include <cstdint>
#include <stddef.h>
#include <noncopyable.hpp>
/***********************************************  Defines    **************************************************/
/***********************************************  Constants   *************************************************/
/***********************************************  Enumerations   **********************************************/
/*********************************************** Data types  **************************************************/
namespace bsp
{
    class fet_base
    {
      public:
        fet_base(void) = default;
        ~fet_base(void) = default;
        virtual std::int16_t turn_on(void) const = 0;
        virtual std::int16_t turn_off(void) const = 0;
    };

    template <std::uint8_t u8_inst>
    class fet: public fet_base
    {
      public:
        ~fet(void) = default;
        static fet &get_instance(void);
        std::int16_t turn_on(void) const override;
        std::int16_t turn_off(void) const override;
      private:
        fet(void) = default;
        std::uint8_t u8_users;
    };
}
#endif