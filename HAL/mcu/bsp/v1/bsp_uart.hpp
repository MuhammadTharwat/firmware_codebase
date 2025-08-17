/**
  ******************************************************************************
  * @file			bsp_uart.hpp
  * @description	UART class interface
  * @author			Ahmed Salama
  * @version		V0.0
  * @date			8-June-2024
  ******************************************************************************
*/

#ifndef BSP_UART_H_
#define BSP_UART_H_

#include <cstdint>
#include <noncopyable.hpp>
#include <mutex.hpp>
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

    struct tstr_uart_init
    {
        tenu_uart_parity enu_parity;
        tenu_uart_stop_bits enu_stop;
        std::uint32_t u32_baudrate;
    };

    using tpfn_uart_tx_handler = void (*)(void);
    using tpfn_uart_rx_handler = void (*)(const void *, std::size_t);

    class uart_base
    {
    public:
        uart_base(void) = default;
        ~uart_base(void) = default;
        virtual std::int16_t init(tstr_uart_init &) const = 0;
        virtual void deinit(void) const = 0;
        virtual std::int16_t change_br(std::uint32_t) const = 0;
        virtual std::int16_t tx(const void *, std::size_t, tpfn_uart_tx_handler) const = 0;
        virtual std::int16_t rx(void *, std::size_t, tpfn_uart_rx_handler) const = 0;
        rtos_osal::mutex mtx;
    };

    template <std::uintmax_t uint_uart_nr>
    class uart : private noncopyable, public uart_base
    {
    public:
        ~uart(void) = default;
        static uart &get_instance(void);
        std::int16_t init(tstr_uart_init &) const override;
        void deinit(void) const override;
        std::int16_t change_br(std::uint32_t) const override;
        std::int16_t tx(const void *, std::size_t, tpfn_uart_tx_handler) const override;
        std::int16_t rx(void *, std::size_t, tpfn_uart_rx_handler) const override;

    private:
        uart(void) = default;
    };
}

#endif /*BSP_UART_H_*/