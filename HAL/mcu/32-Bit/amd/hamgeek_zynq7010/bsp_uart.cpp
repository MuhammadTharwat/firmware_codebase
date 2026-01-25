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
#include "xparameters.h"
#include "bsp_objects.hpp"
/******************************************   Macros **********************************************************/
#define MAX_NUM_UARTs 1

/*
 * The following constants map to the XPAR parameters created in the
 * xparameters.h file. They are defined here such that a user can easily
 * change all the needed parameters in one place.
 */
#define UART_DEVICE_ID		XPAR_XUARTPS_0_DEVICE_ID

/*
 * The following constant controls the length of the buffers to be sent
 * and received with the UART,
 */
#define TEMP_BUFFER_SIZE	64

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
        std::int32_t s32_status;
        XUartPs_Config *pstr_config;
        XUartPsFormat str_formate;
        str_formate.DataBits = XUARTPS_FORMAT_8_BITS;
        switch (rstr_uart_init.enu_parity)
        {
        case uart_parity_none:
        {
            str_formate.Parity = XUARTPS_FORMAT_NO_PARITY;
            break;
        }

        case uart_parity_even:
        {
            str_formate.Parity = XUARTPS_FORMAT_EVEN_PARITY;
            break;
        }

        case uart_parity_odd:
        {
            str_formate.Parity = XUARTPS_FORMAT_ODD_PARITY;
            break;
        }
        }

        switch (rstr_uart_init.enu_baud_rate)
        {
        case uart_br_4800:
        {
            str_formate.BaudRate = 4800;
            break;
        }

        case uart_br_9600:
        {
            str_formate.BaudRate = 9600;
            break;
        }

        case uart_br_19200:
        {
            str_formate.BaudRate = 19200;
            break;
        }

        case uart_br_38400:
        {
            str_formate.BaudRate = 38400;
            break;
        }

        case uart_br_57600:
        {
            str_formate.BaudRate = 57600;
            break;
        }

        case uart_br_115200:
        {
            str_formate.BaudRate = 115200;
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
                str_formate.StopBits = XUARTPS_FORMAT_1_STOP_BIT;
                break;
            }

            case uart_stop_2_bit:
            {
                /*Do nothing*/
                str_formate.StopBits = XUARTPS_FORMAT_2_STOP_BIT;
                break;
            }

            case uart_stop_1_half_bit:
            {
                /*Do nothing*/
                str_formate.StopBits = XUARTPS_FORMAT_1_5_STOP_BIT;
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
            /*
             * Initialize the UART driver so that it's ready to use
             * Look up the configuration in the config table, then initialize it.
             */

            pstr_config = XUartPs_LookupConfig(ruart_dev.u32_base_addr);
            if (nullptr == pstr_config)
            {
                s16_ret = GENERIC_ERR_HW;
            }
            else 
            {
                /*Do nothing*/
            }
        }
        else
        {
            /*Do nothing*/
        }

        if (GENERIC_SUCCESS == s16_ret)
        {
            s32_status = XUartPs_CfgInitialize(&ruart_dev.str_uart, pstr_config, pstr_config->BaseAddress);
            if (s32_status != XST_SUCCESS)
            {
                s16_ret = GENERIC_ERR_HW;
            }
            else 
            {
                /*Do nothing*/
            }
        }
        else
        {
            /*Do nothing*/
        }

        if (GENERIC_SUCCESS == s16_ret)
        {

            s32_status = XUartPs_SetDataFormat(&ruart_dev.str_uart, &str_formate);
            if (s32_status != XST_SUCCESS)
            {
                s16_ret = GENERIC_ERR_HW;
            }
            else
            {
                /*Do nothing*/
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
        if (nullptr == pfn_tx_handler)
        {
            const std::uint8_t *pu8_data = reinterpret_cast<const std::uint8_t *>(pv_data);
            while (sz_data_len)
            {
                std::uint8_t au8_tmp[TEMP_BUFFER_SIZE];
                std::size_t sz_len;
                if (sz_data_len > TEMP_BUFFER_SIZE)
                {
                    sz_len = TEMP_BUFFER_SIZE;
                }
                else
                {
                    sz_len = sz_data_len;
                }

                std::memcpy(au8_tmp, pu8_data, sz_len);

                std::uint32_t u32_tx = XUartPs_Send(&ruart_dev.str_uart, au8_tmp, static_cast<std::uint32_t>(sz_len));
                sz_data_len -= static_cast<std::size_t>(u32_tx);
                pu8_data += u32_tx;
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
        static uart_dev uart_devs[MAX_NUM_UARTs] = {{UART_DEVICE_ID}};
        return uart_devs[uint_dev];
    }
}