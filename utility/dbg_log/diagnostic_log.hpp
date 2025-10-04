/**
  ******************************************************************************
  * @file			    diagnostic_log.hpp
  * @description	This is the header file of the diagnostic to support printing with different types
  * @author			  Mohamed Sami
  * @version		  V0.0
  * @date			    2-September-2025
  ******************************************************************************
*/

#ifndef DIAGNOSTIC_LOG_HPP_
#define DIAGNOSTIC_LOG_HPP_

#include "bsp_uart.hpp"
/***********************************************  Defines    **************************************************/
#ifndef DIAGNOSTIC_LOGGER_BUFF_SIZE
#define DIAGNOSTIC_LOGGER_BUFF_SIZE UINT32_C(128)
#endif

#if defined DIAGNOSTIC_LOG
#define DIAGNOSTIC_LOG_STR_UINT(achrstr, uint_val, enu_radix, b_new_line) gobj_diagnostic_logger.log_str_uint(achrstr, uint_val, enu_radix, b_new_line)
#define DIAGNOSTIC_LOG_STR_SINT(achrstr, sint_val, b_new_line) gobj_diagnostic_logger.log_str_sint(achrstr, sint_val, b_new_line)
#define DIAGNOSTIC_LOG_STR(achrstr, b_new_line) gobj_diagnostic_logger.log_str(achrstr, b_new_line)
#define DIAGNOSTIC_LOG_ASSERT(archstr, uint_line_nr, b_new_line) gobj_diagnostic_logger.log_assert(archstr, uint_line_nr, b_new_line)
#else
#define DIAGNOSTIC_LOG_STR_UINT(achrstr, uint_val, enu_radix, b_new_line) ((void)0)
#define DIAGNOSTIC_LOG_STR_SINT(achrstr, sint_val, b_new_line) ((void)0)
#define DIAGNOSTIC_LOG_STR(achrstr, b_new_line) ((void)0)
#define DIAGNOSTIC_LOG_ASSERT(archstr, u32_line, b_new_line) ((void)0)
#endif
/***********************************************  Enumerations   **********************************************/
typedef enum
{
  radix_binary = 0,
  radix_decimal,
  radix_hexadecimal
}tenu_radix;

/*********************************************** Data types  **************************************************/

class diagnostic_logger
{
public:
  diagnostic_logger(bsp::uart &); /*Note: UART is not initialized here. It must be initialized before passing to
  the event logger */
  ~diagnostic_logger() = default;

  /**
   * API to unsigned int
   * @param [in] pchr_str
   * @param [in] unsigned
   * @param [in] enu_radix
   * @param [in] b_new_line
   * @return none
   */
  void log_str_uint(const char *, std::uint8_t, tenu_radix, bool);
  void log_str_uint(const char *, std::uint16_t, tenu_radix, bool);
  void log_str_uint(const char *, std::uint32_t, tenu_radix, bool);
  void log_str_uint(const char *, std::uint64_t, tenu_radix, bool);

  /**
   * API to print signed int
   * @param [in] pchr_str
   * @param [in] signed
   * @param [in] b_new_line
   * @return none
   */
  void log_str_sint(const char *, std::int8_t, bool);
  void log_str_sint(const char *, std::int16_t, bool);
  void log_str_sint(const char *, std::int32_t, bool);
  void log_str_sint(const char *, std::int64_t, bool);
  /**
   * API to print string.
   * @param [in] pchar_str
   * @param [in] b_new_line
   * @return none
   */
  void log_str(const char *, bool);

  /**
   * API to print float number.
   * @param [in] flt_val
   * @param [in] pchar_str
   * @param [in] b_new_line
   * @return none
   */
  void log_str_flt(const char *, float, bool);

  /**
   * API to print Assertion line and function name.
   * @param [in] pchar_str
   * @param [in] u32_asrt_line
   * @param [in] b_new_line
   * @return none
   */
  void log_assert(const char *, std::uint32_t, bool);

private:
  bsp::uart &ruart;
  std::uint8_t au8_ring_buff[DIAGNOSTIC_LOGGER_BUFF_SIZE];
  std::uint32_t u32_rd_idx;
  std::uint32_t u32_wr_idx;
  rtos_osal::mutex mtx_ring_buff;
};
/******************************************      API Prototypes      *************************************/
#if defined DIAGNOSTIC_LOG
extern diagnostic_logger gobj_diagnostic_logger;
#endif
/*****************************************************/

#endif /* DIAGNOSTIC_H_ */