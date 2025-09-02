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
#define MAX_NUM_UARTs 1

#define UART0_BASE 0x10001000

/*Register Definition*/
#define UART_CONFIGURATION_OFFSET UINT32_C(0x00000000)
#define UART_BR_MASK UINT32_C(0x00000007)
#define UART_BR_4800 UINT32_C(0x00000000)
#define UART_BR_9600 UINT32_C(0x00000001)
#define UART_BR_19200 UINT32_C(0x00000002)
#define UART_BR_38400 UINT32_C(0x00000003)
#define UART_BR_57600 UINT32_C(0x00000004)
#define UART_BR_115200 UINT32_C(0x00000005)

#define UART_PARITY_MASK UINT32_C(0x00000018)
#define UART_PARITY_NONE UINT32_C(0x00000000)
#define UART_PARITY_ODD UINT32_C(0x00000008)
#define UART_PARITY_EVEN UINT32_C(0x00000010)


#define UART_LSB_FIRST_MASK UINT32_C(0x00000020)
#define UART_CLEAR_ERROR_MASK UINT32_C(0x00000040)

#define UART_TXR_OFFSET UINT32_C(0x00000001)

#define UART_RXR_OFFSET UINT32_C(0x00000002)

#define UART_STATUS_OFFSET UINT32_C(0x00000003)
#define UART_TX_READY_MASK UINT32_C(0x00000001)
#define UART_RX_VALID_MASK UINT32_C(0x00000002)
#define UART_RX_OVERRUN_ERR_MASK UINT32_C(0x00000004)
#define UART_RX_PARITY_ERR_MASK UINT32_C(0x00000008)

#define IORD_CFG_REG(base) IORD(base, 0)
#define IOWR_CFG_REG(base, data) IOWR(base, 0, data)

#define IORD_TXR_REG(base) IORD(base, 1)
#define IOWR_TXR_REG(base, data) IOWR(base, 1, data)

#define IORD_RXR_REG(base) IORD(base, 2)
#define IOWR_RXR_REG(base, data) IOWR(base, 2, data)

#define IORD_STATUS_REG(base) IORD(base, 3)
#define IOWR_STATUS_REG(base, data) IOWR(base, 3, data)

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
        std::uint32_t u32_reg = 0u;
        if (true == rstr_uart_init.b_msb_first)
        {
            /*Do nothing, Default is MSB*/
        }
        else
        {
            u32_reg |= UART_LSB_FIRST_MASK;
        }

        switch (rstr_uart_init.enu_parity)
        {
        case uart_parity_none:
        {
            u32_reg |= UART_PARITY_NONE;
            break;
        }

        case uart_parity_even:
        {
            u32_reg |= UART_PARITY_EVEN;
            break;
        }

        case uart_parity_odd:
        {
            u32_reg |= UART_PARITY_ODD;
            break;
        }
        }

        switch (rstr_uart_init.enu_baud_rate)
        {
        case uart_br_4800:
        {
            u32_reg |= UART_BR_4800;
            break;
        }

        case uart_br_9600:
        {
            u32_reg |= UART_BR_9600;
            break;
        }

        case uart_br_19200:
        {
            u32_reg |= UART_BR_19200;
            break;
        }

        case uart_br_38400:
        {
            u32_reg |= UART_BR_38400;
            break;
        }

        case uart_br_57600:
        {
            u32_reg |= UART_BR_57600;
            break;
        }

        case uart_br_115200:
        {
            u32_reg |= UART_BR_115200;
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

        if (GENERIC_SUCCESS == s16_ret)
        {
            IOWR_CFG_REG(this->ruart_dev.u32_base_addr, u32_reg);
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
        if (nullptr == pfn_tx_handler)
        {
            const std::uint8_t *pu8_bytes = static_cast<const std::uint8_t *>(pv_data);
            /*Synchronous, blocking Tx*/
            for (std::size_t sz_idx = 0; sz_idx < sz_data_len; sz_idx++)
            {
                std::uint32_t u32_data;
                /*Block on TX ready*/
                while (!(IORD_STATUS_REG(this->ruart_dev.u32_base_addr) & UART_TX_READY_MASK))
                {
                    /*Do nothing*/
                }
                u32_data = static_cast<std::uint32_t>(pu8_bytes[sz_idx]);
                IOWR_TXR_REG(this->ruart_dev.u32_base_addr, u32_data);
            }
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