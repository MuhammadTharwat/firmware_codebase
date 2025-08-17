/**
  ******************************************************************************
  * @file			bsp_sys.hpp
  * @description	This is the header file of the misc support package "misc"
  * @author			Ahmed Salama
  * @version		V0.0
  * @date			08-April-2024
  ******************************************************************************
*/
#include <cstdint>
#include <noncopyable.hpp>
/***********************************************  Defines    **************************************************/
#define ID_LEN 4u
#define DFU_IMAGE_DIGEST_LEN 16u
#define HW_ID_LEN 3u
#define DFU_VER 0x02

/*Error Codes*/
#define DFU_INVALID_MANIFEST BSP_ERROR_BASE - 1
#define DFU_INVALID_IMG BSP_ERROR_BASE - 2
/***********************************************  Constants   *************************************************/

/***********************************************  Enumerations   **********************************************/

/*********************************************** Data types  **************************************************/
namespace bsp
{
  const std::uint8_t au8_image_key[] = {0x52, 0x66, 0x55, 0x6A, 0x58, 0x6E, 0x32, 0x72,\
									 0x35, 0x75, 0x38, 0x78, 0x2F, 0x41, 0x3F, 0x44};

  using tpfun_brown_out_callback = void (*)(void);
  enum tenu_reset_cause
	{
		reset_unknown = 0,
		reset_low_power,
		reset_watchdog,
		reset_software,
		reset_por_pod_bor,
		reset_external_reset_pin,
	} ;

#pragma pack(push, 1)
  struct tstr_dfu_info
  {
    std::uint8_t u8_dfu_ver;
    std::uint32_t u32_img_start_address;
    std::uint32_t u32_max_img_size;
  };
#pragma pack(pop)

#pragma pack(push, 1)
  struct tstr_dfu_manifest
  {
    std::uint8_t u8_fw_version;
    std::uint32_t u32_curr_img_start_address;
    std::uint32_t u32_curr_img_size;
    std::uint32_t u32_max_img_size;
    std::uint8_t au8_img_digest[DFU_IMAGE_DIGEST_LEN];
    std::uint16_t u16_device_id;
    std::uint8_t au8_hw_id[HW_ID_LEN];
    std::uint8_t au8_rsrved[3u];
  };
  
#pragma pack(pop)
  class sys : private noncopyable
	{
		public:
      ~sys(void) = default;
			std::int16_t get_id(std::uint8_t au8_sys_id[ID_LEN]) const;
      std::uint32_t get_cpu_frequency(void) const;
      tenu_reset_cause get_reset_cause(void) const;
      void reset(void) const;
      void sleep(void) const;
      std::int16_t dfu_get_info(tstr_dfu_info *) const;
      std::int16_t dfu_load_main_region_manifest(tstr_dfu_manifest &) const;
      std::int16_t dfu_store_shadow_region_manifest(const tstr_dfu_manifest &) const;
      std::int16_t dfu_write_shadow_region(std::uint32_t , const std::uint8_t *, std::uint32_t ) const;
      std::int16_t dfu_boot_img(void) const;
      std::int16_t nvm_write_address(std::uint32_t , const void *, std::size_t ) const;
      std::int16_t nvm_read_address(std::uint32_t , void *, std::size_t ) const;
      std::int16_t internal_flash_read(std::uint32_t , void *, std::size_t ) const;
      std::int16_t internal_flash_write(std::uint32_t , const void *, std::size_t ) const;
      std::int16_t internal_flash_erase(std::uint32_t , std::size_t ) const;
      std::int16_t internal_flash_lock(void) const;
      std::int16_t internal_flash_unlock(void) const;
      static sys &get_instance(void);
      template <typename rng_bit_size>
      rng_bit_size random_number_generate(void);
      const std::size_t sz_user_flash_size;
      const std::size_t sz_page_size;
      const std::size_t sz_min_prog_word;
      const std::size_t sz_min_erase_block;
      const std::size_t sz_user_flash_start_addr;
    private:
      sys(void);
	};
}