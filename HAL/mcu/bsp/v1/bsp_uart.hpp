/**
  ******************************************************************************
  * @file			bsp_uart.hpp
  * @description	UART class interface
  * @author			Muhammad Tharwat
  * @version		V0.0
  * @date			31-August-2025
  ******************************************************************************
*/

#ifndef BSP_UART_H_
#define BSP_UART_H_

#include <cstdint>
#include <noncopyable.hpp>
#include <mutex.hpp>
#include "bsp_objects.hpp"
/***********************************************  Defines    **************************************************/


/***********************************************  Constants   *************************************************/

/***********************************************  Enumerations   **********************************************/

/*********************************************** Data types  **************************************************/
namespace bsp
{
    enum tenu_uart_parity
    {
        uart_parity_none,
        uart_parity_even,
        uart_parity_odd
    };

    enum tenu_uart_stop_bits
    {
        uart_stop_half_bit = 0,
        uart_stop_1_bit,
        uart_stop_1_half_bit,
        uart_stop_2_bit
    };

    enum tenu_uart_baud_rate
    {
        uart_br_1200 = 0,
        uart_br_2400,
        uart_br_4800,
        uart_br_9600,
        uart_br_19200,
        uart_br_38400,
        uart_br_57600,
        uart_br_115200
    };

    struct tstr_uart_init
    {
        tenu_uart_parity enu_parity;
        tenu_uart_stop_bits enu_stop;
        tenu_uart_baud_rate enu_baud_rate;
        bool b_msb_first;
    };

    using tpfn_uart_tx_handler = void (*)(void);
    using tpfn_uart_rx_handler = void (*)(const void *, std::size_t);

    class uart : private noncopyable
    {
    public:
        uart(uart_dev &);
        ~uart() = default;
        std::int16_t init(const tstr_uart_init &) const;
        void deinit(void) const;
        std::int16_t change_br(tenu_uart_baud_rate) const;
        std::int16_t tx(const void *, std::size_t, tpfn_uart_tx_handler) const;
        std::int16_t rx(void *, std::size_t, tpfn_uart_rx_handler, std::uint32_t) const;
        rtos_osal::mutex mtx;

    private:
        uart_dev &ruart_dev;
    };

    uart_dev &get_uart_dev(std::uintmax_t);

}

#endif /*BSP_UART_H_*/