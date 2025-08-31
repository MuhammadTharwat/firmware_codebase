/**
 ******************************************************************************
 * @file			bsp_uart.cpp
 * @description	    UART class implementation
 * @author			Muhammad Tharwat
 * @version		    V0.0
 * @date			31-August-2025
 ******************************************************************************
 */
#include "bsp_uart.hpp"
#include "system.h"
#include "io.h"
#include "general_includes.hpp"

/******************************************   Macros **********************************************************/
#define MAX_NUM_LEDs 1
#define UART_0 UINT32_C(1)

#define UART0_BASE 0x10000000

#define IORD_GPIO_DIRECTION_REG IORD(GPIO_BASE, 0)
#define IOWR_GPIO_DIRECTION_REG(data) IOWR(GPIO_BASE, 0, data)

#define IORD_GPIO_INPUT_REG IORD(GPIO_BASE, 1)
#define IOWR_GPIO_INPUT_REG(data) IOWR(GPIO_BASE, 1, data)

#define IORD_GPIO_OUTPUT_REG IORD(GPIO_BASE, 2)
#define IOWR_GPIO_OUTPUT_REG(data) IOWR(GPIO_BASE, 2, data)

/***********************************************  Constants   *************************************************/

/*********************************************** Enumeration	***********************************************/

/*********************************************** Data types  **************************************************/

/*********************************************** APIs  **************************************************/

namespace bsp
{

    uart::uart(uart_dev &ruart_dev_in) : ruart_dev(ruart_dev_in)
    {
        /*Do nothing*/
    }

    std::int16_t uart::init(tstr_uart_init &rstr_uart_init) const
    {
        (void)(rstr_uart_init);
        return GENERIC_SUCCESS;
    }

    void uart::deinit(void) const
    {
    }

    std::int16_t uart::change_br(tenu_uart_baud_rate enu_br) const
    {
        (void)(enu_br);
        return GENERIC_SUCCESS;
    }

    std::int16_t uart::tx(const void *pv_data, std::size_t sz_data_len, tpfn_uart_tx_handler pfn_tx_handler) const
    {
        (void)(pv_data);
        (void)(sz_data_len);
        (void)(pfn_tx_handler);
        return GENERIC_SUCCESS;
    }

    std::int16_t uart::rx(void *pv_data, std::size_t sz_data_len, tpfn_uart_rx_handler pfn_rx_handler, std::uint32_t u32_timeout_ms) const
    {
        (void)(pv_data);
        (void)(sz_data_len);
        (void)(pfn_rx_handler);
        (void)(u32_timeout_ms);
        return GENERIC_SUCCESS;
    }

    uart_dev &get_uart_dev(std::uintmax_t uint_dev)
    {
        static uart_dev uart_devs[MAX_NUM_LEDs] = {{UART_0}};
        return uart_devs[uint_dev];
    }
}