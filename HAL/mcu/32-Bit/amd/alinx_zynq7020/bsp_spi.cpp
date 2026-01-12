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
#include "xparameters.h"
#include "bsp_objects.hpp"
/******************************************   Macros **********************************************************/
#define MAX_NUM_SPIs 1

/*
 * The following constants map to the XPAR parameters created in the
 * xparameters.h file. They are defined here such that a user can easily
 * change all the needed parameters in one place.
 */
#define SPI_DEVICE_ID		XPAR_XSPIPS_0_DEVICE_ID

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

    spi::spi(spi_dev &rspi_dev_in) : rspi_dev(rspi_dev_in)
    {
        /*Do nothing*/
    }

    std::int16_t spi::init(std::uint16_t u16_spi_clk_divider, tenu_spi_mode enu_spi_mode, bool b_msb_first)
    {
        (void)(b_msb_first);
        std::uint8_t u8_prescaler;
        std::int16_t s16_ret = GENERIC_SUCCESS;
        std::int32_t s32_status;
        std::uint32_t u32_options = XSPIPS_MASTER_OPTION;
        XSpiPs_Config *pstr_config;

        pstr_config = XSpiPs_LookupConfig(rspi_dev.u32_base_addr);
        if (nullptr == pstr_config)
        {
            s16_ret = GENERIC_ERR_HW;
        }
        else
        {
            /*Do nothing*/
        }

        if (GENERIC_SUCCESS == s16_ret)
        {
            s32_status = XSpiPs_CfgInitialize(&rspi_dev.str_spi, pstr_config, pstr_config->BaseAddress);
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
            s32_status = XSpiPs_SelfTest(&rspi_dev.str_spi);
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

        switch (u16_spi_clk_divider)
        {
        case 4:
        {
            u8_prescaler = XSPIPS_CLK_PRESCALE_4;
            break;
        }

        case 8:
        {
            u8_prescaler = XSPIPS_CLK_PRESCALE_8;
            break;
        }

        case 16:
        {
            u8_prescaler = XSPIPS_CLK_PRESCALE_16;
            break;
        }

        case 32:
        {
            u8_prescaler = XSPIPS_CLK_PRESCALE_32;
            break;
        }

        case 64:
        {
            u8_prescaler = XSPIPS_CLK_PRESCALE_64;
            break;
        }

        case 128:
        {
            u8_prescaler = XSPIPS_CLK_PRESCALE_128;
            break;
        }

        case 256:
        {
            u8_prescaler = XSPIPS_CLK_PRESCALE_256;
            break;
        }

        default:
        {
            s16_ret = GENERIC_ERR_HW_UNSUPPORTED;
            break;
        }
        }

        if (GENERIC_SUCCESS == s16_ret)
        {
            s32_status = XSpiPs_SetClkPrescaler(&rspi_dev.str_spi, u8_prescaler);
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
            switch (enu_spi_mode)
            {
            case spi_mode_pol_high_ph_1st_edge:
            {
                break;
            }

            case spi_mode_pol_high_ph_2nd_edge:
            {
                u32_options |= XSPIPS_CLK_PHASE_1_OPTION;
                break;
            }

            case spi_mode_pol_low_ph_1st_edge:
            {
                u32_options |= XSPIPS_CLK_ACTIVE_LOW_OPTION;
                break;
            }

            case spi_mode_pol_low_ph_2nd_edge:
            {
                u32_options |= XSPIPS_CLK_ACTIVE_LOW_OPTION;
                u32_options |= XSPIPS_CLK_PHASE_1_OPTION;
                break;
            }

            default:
            {
                break;
            }
            }
        }
        else
        {
            /*Do nothing*/
        }

        if (GENERIC_SUCCESS == s16_ret)
        {
            s32_status = XSpiPs_SetOptions(&rspi_dev.str_spi, u32_options);
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

    std::int16_t spi::slave_enable(std::uint8_t u8_slave)
    {
        std::int16_t s16_ret = GENERIC_SUCCESS;
        if (XST_SUCCESS != XSpiPs_SetSlaveSelect(&rspi_dev.str_spi, u8_slave))
        {
            s16_ret = GENERIC_ERR_HW;
        }
        else
        {
            /*Do nothing */
        }
        return s16_ret;
    }

    std::int16_t spi::slave_disable(std::uint8_t u8_slave)
    {
        (void)(u8_slave);
        return GENERIC_ERR_HW;
    }

    std::int16_t spi::tx(const void *pv_data, std::size_t sz_data_len, tpfun_spi_tx_cb pfn_tx_handler)
    {
        std::int16_t s16_ret = GENERIC_SUCCESS;
        if (nullptr == pfn_tx_handler)
        {
                while (sz_data_len)
                {
                    std::int32_t s32_status;
                    std::uint8_t au8_tmp[TEMP_BUFFER_SIZE];
                    std::uint32_t u32_len;
                    if (sz_data_len > TEMP_BUFFER_SIZE)
                    {
                        u32_len = TEMP_BUFFER_SIZE;
                    }
                    else
                    {
                        u32_len = static_cast<std::uint32_t>(sz_data_len);
                    }

                    std::memcpy(au8_tmp, pv_data, u32_len);

                    s32_status = XSpiPs_PolledTransfer(&rspi_dev.str_spi, au8_tmp, nullptr, u32_len);
                    if (XST_SUCCESS == s32_status)
                    {
                        s16_ret = GENERIC_SUCCESS;
                    }
                    else
                    {
                        break;
                    }
                    sz_data_len -= u32_len;
            }
        }
        else
        {
            /*Asynchronous Tx*/
        }
        return s16_ret;
    }

    std::int16_t spi::rx(void *pv_data, std::size_t sz_data_len, tpfun_spi_rx_cb pfn_rx_handler)
    {
        std::int16_t s16_ret = GENERIC_SUCCESS;
        if (nullptr == pfn_rx_handler)
        {
            while (sz_data_len)
            {
                std::int32_t s32_status;
                std::uint32_t u32_len;
                if (sz_data_len > TEMP_BUFFER_SIZE)
                {
                    u32_len = TEMP_BUFFER_SIZE;
                }
                else
                {
                    u32_len = static_cast<std::uint32_t>(sz_data_len);
                }

                std::memset(pv_data, 0x00, u32_len);

                s32_status = XSpiPs_PolledTransfer(&rspi_dev.str_spi, reinterpret_cast<std::uint8_t *>(pv_data), reinterpret_cast<std::uint8_t *>(pv_data), u32_len);
                if (XST_SUCCESS == s32_status)
                {
                    s16_ret = GENERIC_SUCCESS;
                }
                else
                {
                    break;
                }
                sz_data_len -= u32_len;
            }
        }
        else
        {
            /*Asynchronous Rx*/
        }
        return s16_ret;
    }

        spi_dev &get_spi_dev(std::uintmax_t uint_dev)
        {
            static spi_dev spi_devs[MAX_NUM_SPIs] = {{SPI_DEVICE_ID}};
            return spi_devs[uint_dev];
        }
    }