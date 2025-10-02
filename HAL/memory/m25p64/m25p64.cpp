/**
 ******************************************************************************
 * @file            m25p64.cpp
 * @description     This is the implementation file of the m25p64 serial flash memory
 * @author          Muhammad Tharwat
 * @version         V0.0
 * @date            23-August-2025
 ******************************************************************************
 */

#include "m25p64.hpp"
#include "general_includes.hpp"

/***********************************************  Defines    **************************************************/
#ifndef M25P64_SPI_SPEED_FACTOR
#define M25P64_SPI_SPEED_FACTOR 32
#endif

#define M25P64_ERR_WRONG_SIGNATURE INT16_C(M25P64_ERROR_BASE - 1)
/***********************************************  Constants   *************************************************/
static constexpr std::uint32_t gu32_mtx_timeout_ms = UINT32_C(1000);
static constexpr std::uint16_t gu16_spi_speed_factor = UINT16_C(M25P64_SPI_SPEED_FACTOR);

/*Instructions*/
static constexpr std::uint8_t gu8_read_signature = UINT8_C(0xAB);
static constexpr std::uint8_t gu8_signature_value = UINT8_C(0x16);
/************************************************** Global Variables **************************************************/

/************************************************** APIs **************************************************/

m25p64::m25p64(bsp::spi &rspi_init, bsp::output &routput_init) : rspi(rspi_init),
                                                                 rcs(routput_init)
{
    rcs.init();
    rcs.write(bsp::pin_state_high);
}

std::int16_t m25p64::program_page(std::uint32_t u32_addr, const void *pv_data, std::uint8_t u8_len)
{
    (void)(u32_addr);
    (void)(pv_data);
    (void)(u8_len);
    return GENERIC_SUCCESS;
}

std::int16_t m25p64::verify_electonic_signature(void)
{
    std::int16_t s16_ret;
    std::uint8_t au8_bytes[4u];

    s16_ret = (rtos_osal::osal_success == rspi.mtx.lock(gu32_mtx_timeout_ms)) ? GENERIC_SUCCESS : OSAL_ERR_BASE;

    if (GENERIC_SUCCESS == s16_ret)
    {
        s16_ret = rspi.init(gu16_spi_speed_factor, bsp::cpol_low_cpha_low, true);
    }
    else
    {
        /*Do nothing*/
    }

    if (GENERIC_SUCCESS == s16_ret)
    {
        rcs.write(bsp::pin_state_low);
        au8_bytes[0] = gu8_read_signature;
        s16_ret = rspi.tx(au8_bytes, sizeof(au8_bytes), nullptr);
    }
    else
    {
        /*Do nothing*/
    }

    if (GENERIC_SUCCESS == s16_ret)
    {
        s16_ret = rspi.rx(au8_bytes, 1u, nullptr);
    }
    else
    {
        /*Do nothing*/
    }

    if (GENERIC_SUCCESS == s16_ret)
    {
        s16_ret = (gu8_signature_value == au8_bytes[0]) ? GENERIC_SUCCESS : M25P64_ERR_WRONG_SIGNATURE;
    }
    else
    {
        /*Do nothing*/
    }

    rcs.write(bsp::pin_state_high);
    rspi.mtx.unlock();
    return s16_ret;
}

std::int16_t m25p64::read(std::uint32_t u32_addr, void *pv_data, std::uint32_t u32_len)
{
    (void)(u32_addr);
    (void)(pv_data);
    (void)(u32_len);
    return GENERIC_SUCCESS;
}