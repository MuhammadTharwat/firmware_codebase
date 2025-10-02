/**
  ******************************************************************************
  * @file			bsp_objects.hpp
  * @description	BSP object declaration file
  * @author			Muhammad Tharwat
  * @version		V0.0
  * @date			25-August-2025
  ******************************************************************************
*/
#ifndef BSP_OBJECTS_H_
#define BSP_OBJECTS_H_

#include "cstdint"
#include <stddef.h>
#include <noncopyable.hpp>

/***********************************************  Defines    **************************************************/
/***********************************************  Constants   *************************************************/
/***********************************************  Enumerations   **********************************************/
/*********************************************** Data types  **************************************************/

namespace bsp
{

    /*Led Object*/
    class led_dev : private noncopyable
    {
    public:
        ~led_dev() = default;
        led_dev(std::uintmax_t uint_idx) : u32_idx(uint_idx)
        {
        }
        std::uint32_t u32_idx;
    };

    /*IO Object*/
    class io_dev : private noncopyable
    {
    public:
        ~io_dev() = default;
        io_dev(std::uintmax_t uint_idx) : u32_idx(uint_idx)
        {
        }
        std::uint32_t u32_idx;
    };

    /*SPI Object*/
    class spi_dev : private noncopyable
    {
    public:
        ~spi_dev() = default;
        spi_dev(std::uint32_t u32_base_addr_in) : u32_base_addr(u32_base_addr_in)
        {
        }
        std::uint32_t u32_base_addr;
    };

    /*UART Object*/
    class uart_dev : private noncopyable
    {
    public:
        ~uart_dev() = default;
        uart_dev(std::uint32_t u32_base_addr_in) : u32_base_addr(u32_base_addr_in)
        {
        }
        std::uint32_t u32_base_addr;
    };
}

#endif /*BSP_OBJECTS_H_*/