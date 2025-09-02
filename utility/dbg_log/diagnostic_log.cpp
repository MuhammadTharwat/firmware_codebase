/**
  ******************************************************************************
  * @file			diagnostic_log.cpp
  * @description	Implementation of event logger
  * @author			Muhammad Tharwat
  * @version		V0.0
  * @date			2-September-2025
  ******************************************************************************
*/

#include <cstring>
#include <iostream>
#include "diagnostic_log.hpp"
#include <cstdlib>  
#include <algorithm>
/***********************************************  Defines    **************************************************/
#ifndef FLOAT_TO_U32_FRACTIONAL_PART
#define FLOAT_TO_U32_FRACTIONAL_PART 1000
#endif

#ifndef DIAGNOSTIC_LOG_BUFF_LEN
#define DIAGNOSTIC_LOG_BUFF_LEN 128
#endif

#ifndef FRACTIONAL_DIGITS_CNT
#define FRACTIONAL_DIGITS_CNT 3
#endif

#define FIRST_NON_LEAD_0_NUM 0x10

#define DIAGNOSTIC_LOGGER_MTX_TIMEOUT UINT32_C(100)
#define DIAGNOSTIC_LOGGER_MAX_DIGITS UINT32_C(64)
/***********************************************  Constants   *************************************************/

/******************************************* Local Global Variables *******************************************/

/*******************************************  functions prototypes **************************************/
int16_t diagnostic_log_write(const void *pv_data, size_t sz_len);
int16_t diagnostic_log_write_assert(const void *pv_data, size_t sz_len);
/******************************************* Local functions prototypes **************************************/

/******************************************* Local function implementation ***********************************/
void u64_to_str(char *pchr_buff, uint64_t u64_val, tenu_radix enu_radix, bool b_new_line)
{
	uint8_t u8_idx = 0;

	if (true == b_new_line)
	{
		pchr_buff[u8_idx] = '\n';
		u8_idx++;
	}
	else
	{
		/*do nothing*/
	}

	if (0 == u64_val)
	{
		pchr_buff[u8_idx] = '0';
		u8_idx++;
	}
	else
	{
		/*do nothing*/
	}

	/*In case of decimal number*/
	if (radix_decimal == enu_radix)
	{
		while (u64_val)
		{
			pchr_buff[u8_idx] = u64_val % 10 + '0';
			u64_val /= 10;
			u8_idx++;
		}
	}

	/*In case of hex number*/
	else if (radix_hexadecimal == enu_radix)
	{
		bool b_is_leading_zero = false;
		if (FIRST_NON_LEAD_0_NUM > u64_val)
		{
			b_is_leading_zero = true;
		}
		else
		{
			/*do nothing*/
		}
		while (u64_val)
		{
			pchr_buff[u8_idx] = u64_val % 16 + '0';
			if ((9 + '0') < (pchr_buff[u8_idx]))
			{
				pchr_buff[u8_idx] = pchr_buff[u8_idx] + 7;
			}
			u64_val /= 16;
			u8_idx++;
		}
		if (true == b_is_leading_zero)
		{
			pchr_buff[u8_idx] = '0';
			u8_idx++;
		}
		else
		{
			/*do nothing*/
		}
		pchr_buff[u8_idx] = 'x';
		u8_idx++;
		pchr_buff[u8_idx] = '0';
		u8_idx++;
	}
	/*In case of binary number*/
	else if (radix_binary == enu_radix)
	{
		while (u64_val)
		{
			pchr_buff[u8_idx] = u64_val % 2 + '0';
			u64_val /= 2;
			u8_idx++;
		}
		pchr_buff[u8_idx] = 'b';
		u8_idx++;
		pchr_buff[u8_idx] = '0';
		u8_idx++;
	}
	else
	{
		/*Do nothing*/
	}
	std::reverse(pchr_buff, pchr_buff + u8_idx);
}
/************************************API Implementation********************************/

diagnostic_logger::diagnostic_logger(bsp::uart &ruart_in) : ruart(ruart_in),
															u32_rd_idx(0),
															u32_wr_idx(0)
{
	/*Do nothing*/
}

void diagnostic_logger::log_str(const char *pchar_str, bool b_new_line)
{
	this->mtx_ring_buff.lock(DIAGNOSTIC_LOGGER_MTX_TIMEOUT);
	this->ruart.tx(pchar_str, std::strlen(pchar_str), nullptr);
	if (true == b_new_line)
	{
		this->ruart.tx("\n", 1, nullptr);
	}
	else
	{
		/*Do nothing*/
	}
	this->mtx_ring_buff.unlock();
}

void diagnostic_logger::log_str_uint(const char *pchar_str, std::uint8_t u8_val, tenu_radix enu_radix, bool b_new_line)
{
	this->log_str_uint(pchar_str, static_cast<std::uint64_t>(u8_val), enu_radix, b_new_line);
}

void diagnostic_logger::log_str_uint(const char *pchr_str, std::uint64_t u64_val, tenu_radix enu_radix, bool b_new_line)
{
	(void)(u64_val);
	char achr_digits[DIAGNOSTIC_LOGGER_MAX_DIGITS];
	this->mtx_ring_buff.lock(DIAGNOSTIC_LOGGER_MTX_TIMEOUT);
	this->ruart.tx(pchr_str, std::strlen(pchr_str), nullptr);
	u64_to_str(achr_digits, u64_val, enu_radix, b_new_line);
	this->ruart.tx(achr_digits, std::strlen(achr_digits), nullptr);
	this->mtx_ring_buff.unlock();
}