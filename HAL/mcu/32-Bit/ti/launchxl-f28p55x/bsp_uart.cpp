/**
 ******************************************************************************
 * @file			bsp_uart.cpp
 * @description	    UART class implementation
 * @author			Muhammad Tharwat
 * @version		    V0.0
 * @date			10-May-2026
 ******************************************************************************
 */
#include "bsp_uart.hpp"
#include "general_includes.hpp"
#include "bsp_objects.hpp"
#include "device.h"
/******************************************   Macros **********************************************************/
#define MAX_NUM_UARTs 1

#define UART0_BASE SCIA_BASE

#define UART0_TX_PIN UINT32_C(29)
#define UART0_RX_PIN UINT32_C(28)

#define UART0_TX_CFG UINT32_C(GPIO_29_SCIA_TX)
#define UART0_RX_CFG UINT32_C(GPIO_28_SCIA_RX)

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

    int16_t uart::init(const tstr_uart_init &rstr_uart_init) const
    {
        int16_t s16_ret = GENERIC_SUCCESS;
        uint32_t u32_baud;
        uint32_t u32_configs = SCI_CONFIG_WLEN_8;
        GPIO_setPinConfig(ruart_dev.u32_tx_pin_cfg);
        GPIO_setPinConfig(ruart_dev.u32_rx_pin_cfg);
        GPIO_setPadConfig(ruart_dev.u32_tx_pin, GPIO_PIN_TYPE_STD);
        GPIO_setPadConfig(ruart_dev.u32_rx_pin, GPIO_PIN_TYPE_PULLUP);

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
            u32_configs |= SCI_CONFIG_PAR_NONE;
            break;
        }

        case uart_parity_even:
        {
            u32_configs |= SCI_CONFIG_PAR_EVEN;
            break;
        }

        case uart_parity_odd:
        {
            u32_configs |= SCI_CONFIG_PAR_ODD;
            break;
        }
        }

        switch (rstr_uart_init.enu_baud_rate)
        {
        case uart_br_4800:
        {
            u32_baud = 4800;
            break;
        }

        case uart_br_9600:
        {
            u32_baud = 9600;
            break;
        }

        case uart_br_19200:
        {
            u32_baud = 19200;
            break;
        }

        case uart_br_38400:
        {
            u32_baud = 38400;
            break;
        }

        case uart_br_57600:
        {
            u32_baud = 57600;
            break;
        }

        case uart_br_115200:
        {
            u32_baud = 115200;
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
                u32_configs |= SCI_CONFIG_STOP_ONE;
                break;
            }
            case uart_stop_2_bit:
            {
                u32_configs |= SCI_CONFIG_STOP_TWO;
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
            SCI_setConfig(ruart_dev.u32_base_addr, DEVICE_LSPCLK_FREQ, u32_baud, u32_configs);
            SCI_enableModule(ruart_dev.u32_base_addr);
            SCI_enableFIFO(ruart_dev.u32_base_addr);
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

    int16_t uart::change_br(tenu_uart_baud_rate enu_br) const
    {
        (void)(enu_br);
        return GENERIC_SUCCESS;
    }

    int16_t uart::tx(const void *pv_data, size_t sz_data_len, tpfn_uart_tx_handler pfn_tx_handler) const
    {
        if (nullptr == pfn_tx_handler)
        {
            const uint8_t *pu8_bytes = static_cast<const uint8_t *>(pv_data);
            /*Synchronous, blocking Tx*/
            for (std::size_t sz_idx = 0; sz_idx < sz_data_len; sz_idx++)
            {
                // Wait until TX buffer is ready (blocking)
                while (SCI_FIFO_TX16 == SCI_getTxFIFOStatus(ruart_dev.u32_base_addr))
                {
                }
                SCI_writeCharBlockingFIFO(ruart_dev.u32_base_addr, static_cast<uint16_t>(pu8_bytes[sz_idx]));
            }
        }
        else
        {
            /*Asynchronous Tx*/
        }
        return GENERIC_SUCCESS;
    }

    int16_t uart::rx(void *pv_data, size_t sz_data_len, tpfn_uart_rx_handler pfn_rx_handler, uint32_t u32_timeout_ms) const
    {
        (void)(pv_data);
        (void)(sz_data_len);
        (void)(pfn_rx_handler);
        (void)(u32_timeout_ms);
        return GENERIC_SUCCESS;
    }

    uart_dev &get_uart_dev(uintmax_t uint_dev)
    {
        static uart_dev uart_devs[MAX_NUM_UARTs] = uart_dev(UART0_BASE, UART0_TX_PIN, UART0_RX_PIN, UART0_TX_CFG, UART0_RX_CFG);
        return uart_devs[uint_dev];
    }
}
