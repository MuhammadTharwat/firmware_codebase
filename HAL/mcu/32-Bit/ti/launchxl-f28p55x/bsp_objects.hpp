/**
  ******************************************************************************
  * @file			bsp_objects.hpp
  * @description	BSP object declaration file
  * @author			Muhammad Tharwat
  * @version		V0.0
 * @date            4-May-2026
  ******************************************************************************
*/
#ifndef BSP_OBJECTS_H_
#define BSP_OBJECTS_H_

#ifndef __TI_COMPILER_VERSION__
#include <cstdint>
#else
#include <stdint.h>
#endif
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
        led_dev(uintmax_t uint_idx) : u32_idx(uint_idx)
        {
        }
        uint32_t u32_idx;
    };

    /*IO Object*/
    class io_dev : private noncopyable
    {
    public:
        ~io_dev() = default;
        io_dev(uintmax_t uint_idx) : u32_idx(uint_idx)
        {
        }
        uint32_t u32_idx;
    };

    /*SPI Object*/
    class spi_dev : private noncopyable
    {
    public:
        ~spi_dev() = default;
        spi_dev(uint32_t u32_base_addr_in) : u32_base_addr(u32_base_addr_in)
        {
        }
        uint32_t u32_base_addr;
    };

    /*UART Object*/
    class uart_dev : private noncopyable
    {
    public:
        ~uart_dev() = default;
        uart_dev(uint32_t u32_base_addr_in) : u32_base_addr(u32_base_addr_in)
        {
        }
        uint32_t u32_base_addr;
    };
}

#endif /*BSP_OBJECTS_H_*/
