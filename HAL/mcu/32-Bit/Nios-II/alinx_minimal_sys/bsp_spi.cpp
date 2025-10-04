/**
 ******************************************************************************
 * @file			bsp_spi.cpp
 * @description	    SPI class implementation
 * @author			Muhammad Tharwat
 * @version		    V0.0
 * @date			02-October-2025
 ******************************************************************************
 */
#include "bsp_spi.hpp"
#include "system.h"
#include "io.h"
#include "general_includes.hpp"

/******************************************   Macros **********************************************************/
#define MAX_NUM_SPI 1

#define SPI0_BASE 0x10002000

/*Register Definition*/
#define SPI_CONFIGURATION_OFFSET UINT32_C(0x00000000)
#define SPI_CLK_DIVISOR_MASK UINT32_C(0x000003FF)
#define SPI_LSB_MASK UINT32_C(0x00000400)
#define SPI_CPOL_MASK UINT32_C(0x00000800)
#define SPI_CPHA_MASK UINT32_C(0x00001000)

#define SPI_TXR_OFFSET UINT32_C(0x00000001)
#define SPI_RXR_OFFSET UINT32_C(0x00000002)

#define SPI_STATUS_OFFSET UINT32_C(0x00000003)
#define SPI_TX_READY_MASK UINT32_C(0x00000001)

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

    spi::spi(spi_dev &rspi_dev_in) : rspi_dev(rspi_dev_in)
    {
        /*Do nothing*/
    }

    std::int16_t spi::init(std::uint16_t u16_spi_clk_divider, tenu_spi_mode enu_spi_mode, bool b_msb_first)
    {
        std::int16_t s16_ret = GENERIC_SUCCESS;
        std::uint32_t u32_reg = 0u;

        u32_reg |= SPI_CLK_DIVISOR_MASK & u16_spi_clk_divider;

        u32_reg |= (true == b_msb_first) ? 0u : SPI_LSB_MASK;

        switch (enu_spi_mode)
        {
        case cpol_low_cpha_low:
        {
            break;
        }

        case cpol_low_cpha_high:
        {
            u32_reg |= SPI_CPHA_MASK;
            break;
        }

        case cpol_high_cpha_low:
        {
            u32_reg |= SPI_CPOL_MASK;
            break;
        }

        case cpol_high_cpha_high:
        {
            u32_reg |= SPI_CPOL_MASK;
            u32_reg |= SPI_CPHA_MASK;
            break;
        }

        default:
        {
            break;
        }
        }

        if (GENERIC_SUCCESS == s16_ret)
        {
            IOWR_CFG_REG(this->rspi_dev.u32_base_addr, u32_reg);
        }
        else
        {
            /*Do nothing*/
        }

        return s16_ret;
    }

    std::int16_t spi::tx(const void *pv_data, std::size_t sz_data_len, tpfun_spi_tx_cb pfn_tx_handler)
    {
        if (nullptr == pfn_tx_handler)
        {
            const std::uint8_t *pu8_bytes = static_cast<const std::uint8_t *>(pv_data);
            /*Synchronous, blocking Tx*/
            for (std::size_t sz_idx = 0; sz_idx < sz_data_len; sz_idx++)
            {
                std::uint32_t u32_data;
                /*Block on TX ready*/
                while (!(IORD_STATUS_REG(this->rspi_dev.u32_base_addr) & SPI_TX_READY_MASK))
                {
                    /*Do nothing*/
                }
                u32_data = static_cast<std::uint32_t>(pu8_bytes[sz_idx]);
                IOWR_TXR_REG(this->rspi_dev.u32_base_addr, u32_data);
            }
        }
        else
        {
            /*Asynchronous Tx*/
        }
        return GENERIC_SUCCESS;
    }

    std::int16_t spi::rx(void *pv_data, std::size_t sz_data_len, tpfun_spi_rx_cb pfn_rx_handler)
    {
        if (nullptr == pfn_rx_handler)
        {
            std::uint8_t *pu8_bytes = static_cast<std::uint8_t *>(pv_data);
            /*Synchronous, blocking Tx*/
            for (std::size_t sz_idx = 0; sz_idx < sz_data_len; sz_idx++)
            {
                std::uint32_t u32_data = 0;
                /*Block on TX ready*/
                while (!(IORD_STATUS_REG(this->rspi_dev.u32_base_addr) & SPI_TX_READY_MASK))
                {
                    /*Do nothing*/
                }
                IOWR_TXR_REG(this->rspi_dev.u32_base_addr, u32_data);

                /*Block until the byte has been shifted out*/
                while (!(IORD_STATUS_REG(this->rspi_dev.u32_base_addr) & SPI_TX_READY_MASK))
                {
                    /*Do nothing*/
                }
                u32_data = IORD_RXR_REG(this->rspi_dev.u32_base_addr);
                pu8_bytes[sz_idx] = static_cast<std::uint8_t>(u32_data);
            }
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