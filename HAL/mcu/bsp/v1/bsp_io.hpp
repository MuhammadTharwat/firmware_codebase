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
#include <noncopyable.hpp>
#include "bsp_objects.hpp"
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
        pin_state_low = 0,
        pin_state_high
    } tenu_pin_state;

    typedef enum
    {
        io_bias_floating = 0,
        io_bias_pull_up,
        io_bias_pull_down
    } tenu_io_bias_mode;

    class io : private noncopyable
    {
    public:
        io(io_dev &);
        ~io(void) = default;
        static io &get_instance(void);
        std::int16_t init(tenu_io_direction);
        std::int16_t read(tenu_pin_state &) const;
        std::int16_t write(tenu_pin_state) const;
        std::int16_t set_bias(tenu_io_bias_mode);

    protected:
        io_dev &rio_dev;
        tenu_io_direction enu_io_direction;
        tenu_io_bias_mode enu_bias_mode;
    };

    class output : public io
    {
    public:
        output(io_dev &);
        ~output(void) = default;
        static output &get_instance(void);
        std::int16_t init(tenu_io_direction) = delete;
        std::int16_t init(void);
        std::int16_t set_bias(tenu_io_bias_mode) = delete;
    };

    io_dev &get_io_dev(std::uintmax_t);
}

#endif