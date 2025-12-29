/**
 ******************************************************************************
 * @file			bsp_spi.cpp
 * @description	    SPI class implementation
 * @author			Muhammad Tharwat
 * @version		    V0.0
 * @date			28-December-2025
 ******************************************************************************
 */
#include "bsp_spi.hpp"
#include "general_includes.hpp"

/******************************************   Macros **********************************************************/
#define MAX_NUM_SPI 1

#define SPI0_BASE 0x10002000


/***********************************************  Constants   *************************************************/

/*********************************************** Enumeration	***********************************************/

/*********************************************** Data types  **************************************************/

/*********************************************** APIs  **************************************************/

namespace bsp
{

    spi::spi(spi_dev &rspi_dev_in) : rspi_dev(rspi_dev_in)
    {
        /*Do nothing*/
    }

    std::int16_t spi::init(std::uint16_t u16_spi_clk_divider, tenu_spi_mode enu_spi_mode, bool b_msb_first)
    {
        (void)(u16_spi_clk_divider);
        (void)(b_msb_first);
        std::int16_t s16_ret = GENERIC_SUCCESS;
        switch (enu_spi_mode)
        {
        case cpol_low_cpha_low:
        {
            break;
        }

        case cpol_low_cpha_high:
        {
            break;
        }

        case cpol_high_cpha_low:
        {
            break;
        }

        case cpol_high_cpha_high:
        {
            break;
        }

        default:
        {
            break;
        }
        }
        return s16_ret;
    }

    std::int16_t spi::tx(const void *pv_data, std::size_t sz_data_len, tpfun_spi_tx_cb pfn_tx_handler)
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

    std::int16_t spi::rx(void *pv_data, std::size_t sz_data_len, tpfun_spi_rx_cb pfn_rx_handler)
    {
        (void)(pv_data);
        (void)(sz_data_len);
        if (nullptr == pfn_rx_handler)
        {

        }
        else
        {
            /*Asynchronous Tx*/
        }
        return GENERIC_SUCCESS;
    }

    spi_dev &get_spi_dev(std::uintmax_t uint_dev)
    {
        static spi_dev spi_devs[MAX_NUM_SPI] = {{SPI0_BASE}};
        return spi_devs[uint_dev];
    }
}