/**
 ******************************************************************************
 * @file			bsp_sys.cpp
 * @description     Implementation of system class
 * @author			Muhammad Tharwat
 * @version		V0.0
 * @date
 ******************************************************************************
 */
#include "bsp_sys.hpp"
#include "common.h"
#include "nrf_power.h"
#include "nrf_pwr_mgmt.h"
#include "nrf_gpio.h"
#include "nrfx_nvmc.h"
#include "error_map.hpp"
/******************************************   Macros **********************************************************/
#define LOG_BAUDRATE            115200u

#define FLASH_MIN_PROG_WORD     4
#define FLASH_MIN_ERASE_BLOCK   1

/***********************************************  Constants   *************************************************/

/*********************************************** Enumeration	***********************************************/

/******************************************* Local Global Variables *******************************************/
extern std::uint32_t * _start_address_of_flash;
extern std::uint32_t * _end_of_code_flash;
extern std::uint32_t * _size_of_flash;

static const std::uint32_t gu32_total_flash_size    = (std::uint32_t)&_size_of_flash;
static const std::uint32_t gu32_start_address_flash = (std::uint32_t)&_start_address_of_flash;
static const std::uint32_t gu32_end_of_code_flash   = (std::uint32_t)&_end_of_code_flash;

static const std::size_t gsz_user_flash_start_address = ((gu32_start_address_flash + gu32_total_flash_size) - (((gu32_start_address_flash + gu32_total_flash_size - gu32_end_of_code_flash)/nrfx_nvmc_flash_page_size_get()) * nrfx_nvmc_flash_page_size_get()));
/******************************************* Local functions prototypes **************************************/

/*********************************************** Data types  **************************************************/

namespace bsp
{
    sys::sys(void) : sz_user_flash_size(gu32_start_address_flash + gu32_total_flash_size - gu32_end_of_code_flash), sz_page_size(nrfx_nvmc_flash_page_size_get()), sz_min_prog_word(FLASH_MIN_PROG_WORD), sz_min_erase_block(FLASH_MIN_ERASE_BLOCK)
    {
#ifdef DEBUG_MODE
        _ASSERT(GENERIC_SUCCESS == dgb_log_init(LOG_BAUDRATE));
#endif
#ifdef DIAGNOSTIC_LOG
        _ASSERT(GENERIC_SUCCESS == diagnostic_log_init(LOG_BAUDRATE));
#endif
        _ASSERT(NRF_SUCCESS == nrf_pwr_mgmt_init());
        nrf_gpio_cfg_output(20);
        nrf_gpio_pin_clear(20);	
        nrf_gpio_cfg_output(25);
        nrf_gpio_pin_clear(25);	
        nrf_power_dcdcen_set(true);
    }

    sys &sys::get_instance(void)
    {
        static sys obj_sys_singleton;
        return obj_sys_singleton;
    }
	
    std::int16_t sys::get_id(std::uint8_t au8_sys_id[ID_LEN]) const
    {
        (void)(au8_sys_id);
        return GENERIC_SUCCESS;
    }

    std::uint32_t sys::get_cpu_frequency(void) const
    {
        return 0;
    }

    tenu_reset_cause sys::get_reset_cause(void) const
    {
        tenu_reset_cause enu_rst_cause = reset_unknown;
        std::uint32_t u32_rst_reason = nrf_power_resetreas_get();
        if (POWER_RESETREAS_RESETPIN_Msk & u32_rst_reason)
        {
            enu_rst_cause = reset_external_reset_pin;
        }
        else if (POWER_RESETREAS_DOG_Msk & u32_rst_reason)
        {
            enu_rst_cause = reset_watchdog;
        }
        else if (POWER_RESETREAS_SREQ_Msk & u32_rst_reason)
        {
            enu_rst_cause = reset_software;
        }
        else if (POWER_RESETREAS_LOCKUP_Msk & u32_rst_reason)
        {
        }
        else if (POWER_RESETREAS_OFF_Msk & u32_rst_reason)
        {
            enu_rst_cause = reset_por_pod_bor;
        }
        else 
        {

        }
        return enu_rst_cause;
    }

    void sys::reset(void) const
    {

    }

    void sys::sleep(void) const
    {
        nrf_pwr_mgmt_run();
    }

    std::int16_t sys::dfu_get_info(tstr_dfu_info *pstr_dfu_info) const
    {
        (void)(pstr_dfu_info);
        return GENERIC_SUCCESS;
    }

    std::int16_t sys::dfu_load_main_region_manifest(tstr_dfu_manifest &str_dfu_manifest) const
    {
        (void)(str_dfu_manifest);
        return GENERIC_SUCCESS;
    }

    std::int16_t sys::dfu_store_shadow_region_manifest(const tstr_dfu_manifest &str_dfu_manifest) const
    {
        (void)(str_dfu_manifest);
        return GENERIC_SUCCESS;
    }

    std::int16_t sys::dfu_write_shadow_region(std::uint32_t u32_address, const std::uint8_t *pu8_data, std::uint32_t u32_size) const
    {
        (void)(u32_address);
        (void)(pu8_data);
        (void)(u32_size);
        return GENERIC_SUCCESS;
    }

    std::int16_t sys::dfu_boot_img(void) const
    {
        return GENERIC_SUCCESS;
    }

    std::int16_t sys::nvm_write_address(std::uint32_t u32_address, const void *pv_data, std::size_t sz_data) const
    {
        (void)(u32_address);
        (void)(pv_data);
        (void)(sz_data);
        return GENERIC_SUCCESS;
    }

    std::int16_t sys::nvm_read_address(std::uint32_t u32_address, void *pv_data, std::size_t sz_data) const
    {
        (void)(u32_address);
        (void)(pv_data);
        (void)(sz_data);
        return GENERIC_SUCCESS;
    }

    std::int16_t sys::internal_flash_read(std::uint32_t u32_address, void *pu8_buff, std::size_t sz_len) const
    {
        MEM_CPY(pu8_buff, (void *)(gsz_user_flash_start_address + u32_address), sz_len);
        return GENERIC_SUCCESS;
    }

    std::int16_t sys::internal_flash_write(std::uint32_t u32_address, const void *pu8_buff, std::size_t sz_len) const
    {
        nrfx_nvmc_bytes_write(gsz_user_flash_start_address + u32_address, pu8_buff, sz_len);
        return GENERIC_SUCCESS;
    }

    std::int16_t sys::internal_flash_erase(std::uint32_t u32_address, std::size_t sz_len) const
    {
        nrfx_err_t enu_err;
        int16_t s16_ret;
        for(uint8_t u8_pg = 0; u8_pg < sz_len; u8_pg++)
        {
            enu_err = nrfx_nvmc_page_erase(gsz_user_flash_start_address + u32_address + ((uint32_t)u8_pg * sz_page_size));
            s16_ret = error_map(enu_err);
            if(GENERIC_SUCCESS != s16_ret)
            {
                break;
            }
            else
            {
                /*Do nothing*/
            }
        }
        return s16_ret;
    }
}

void soft_reset(void)
{
	NVIC_SystemReset();
}