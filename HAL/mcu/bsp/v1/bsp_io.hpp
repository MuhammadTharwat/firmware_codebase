/**
  ******************************************************************************
  * @file			bsp_io.hpp
  * @description	This is the header file of the board support package "IO"
  * @author			Ahmed Salama
  * @version		V0.0
  * @date			08-April-2024
  ******************************************************************************
*/
#ifndef BSP_IO_H_
#define BSP_IO_H_

#include "cstdint"
#include <stddef.h>
#include <noncopyable.hpp>
/***********************************************  Defines    **************************************************/
/***********************************************  Constants   *************************************************/
/***********************************************  Enumerations   **********************************************/
/*********************************************** Data types  **************************************************/

namespace bsp
{
    typedef enum
    {
        io_input = 0,
        io_output
    } tenu_io_direction;

    typedef enum
    {
        pin_lvl_low = 0,
        pin_lvl_high
    } tenu_pin_state;

    typedef enum
    {
        io_res_floating = 0,
        io_res_pull_up,
        io_res_pull_down
    } tenu_io_res_mode;

    class io_base
    {
        public:
            io_base(void) = default;
            ~io_base(void) = default;
            virtual std::int16_t init(tenu_io_direction ) = 0;
            virtual std::int16_t read(tenu_pin_state &) const = 0;
            virtual std::int16_t write(tenu_pin_state ) const = 0;
            virtual std::int16_t set_res_mode(tenu_io_res_mode ) = 0;
    };

    template <std::uint8_t u8_inst>
    class io : private noncopyable, public io_base
    {
        public:
            ~io(void) = default;
            static io &get_instance(void);
            std::int16_t init(tenu_io_direction ) override;
            std::int16_t read(tenu_pin_state &) const override;
            std::int16_t write(tenu_pin_state ) const override;
            std::int16_t set_res_mode(tenu_io_res_mode ) override;
        private:
            io(void) = default;
            tenu_io_direction enu_io_direction;
            tenu_io_res_mode enu_res_mode;
    };

}

#endif