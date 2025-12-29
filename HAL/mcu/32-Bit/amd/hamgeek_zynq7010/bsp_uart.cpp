/**
 ******************************************************************************
 * @file			bsp_uart.cpp
 * @description	    UART class implementation
 * @author			Muhammad Tharwat
 * @version		    V0.0
 * @date			28-December-2025
 ******************************************************************************
 */
#include "bsp_uart.hpp"
#include "general_includes.hpp"

/******************************************   Macros **********************************************************/
#define MAX_NUM_UARTs 1

#define UART0_BASE 0x10001000

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

    std::int16_t uart::init(const tstr_uart_init &rstr_uart_init) const
    {
        std::int16_t s16_ret = GENERIC_SUCCESS;
        if (true == rstr_uart_init.b_msb_first)
        {
            /*Do nothing, Default is MSB*/
        }
        else
        {
            
        }

        switch (rstr_uart_init.enu_parity)
        {
        case uart_parity_none:
        {
            break;
        }

        case uart_parity_even:
        {
            break;
        }

        case uart_parity_odd:
        {
            break;
        }
        }

        switch (rstr_uart_init.enu_baud_rate)
        {
        case uart_br_4800:
        {
            break;
        }

        case uart_br_9600:
        {
            break;
        }

        case uart_br_19200:
        {
            break;
        }

        case uart_br_38400:
        {
            break;
        }

        case uart_br_57600:
        {
            break;
        }

        case uart_br_115200:
        {
            break;
        }

        default:
        {
            s16_ret = GENERIC_ERR_HW_UNSUPPORTED;
        }
        }

        if (GENERIC_SUCCESS == s16_ret)
        {
            switch (rstr_uart_init.enu_stop)
            {
            case uart_stop_1_bit:
            {
                /*Do nothing*/
                break;
            }
            default:
            {
                s16_ret = GENERIC_ERR_HW_UNSUPPORTED;
            }
            }
        }
        else
        {
            /*Do nothing*/
        }

        return s16_ret;
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
        if (nullptr == pfn_tx_handler)
        {

        }
        else
        {
            /*Asynchronous Tx*/
        }
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
        static uart_dev uart_devs[MAX_NUM_UARTs] = {{UART0_BASE}};
        return uart_devs[uint_dev];
    }
}