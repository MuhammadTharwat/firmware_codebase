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

/***********************************************  Constants   *************************************************/

/***********************************************  Enumerations   **********************************************/

/*********************************************** Data types  **************************************************/
namespace bsp
{
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

  class sys : private noncopyable
	{
		public:
      ~sys(void) = default;
			std::int16_t get_id(std::uint8_t au8_sys_id[ID_LEN]) const;
      std::uint32_t get_cpu_frequency(void) const;
      tenu_reset_cause get_reset_cause(void) const;
      void reset(void) const;
      void sleep(void) const;
      static sys &get_instance(void);
    private:
      sys(void);
	};
}