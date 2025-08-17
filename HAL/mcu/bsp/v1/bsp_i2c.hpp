/**
  ******************************************************************************
  * @file			bsp_i2c.hpp
  * @description	This is the header file of the board support package "I2C"
  * @author			Ahmed Salama
  * @version		V0.0
  * @date			08-April-2024
  ******************************************************************************
*/
#ifndef BSP_I2C_H_
#define BSP_I2C_H_

#include "stdint.h"
#include <stddef.h>
#include <noncopyable.hpp>
#include <mutex.hpp>
/***********************************************  Defines    **************************************************/
/***********************************************  Constants   *************************************************/
/***********************************************  Enumerations   **********************************************/
/*********************************************** Data types  **************************************************/
namespace bsp
{
	using tpfun_i2c_tx_cb = void (*)(void);
	using tpfun_i2c_rx_cb = void (*)(const void *pv_rx_data, size_t sz_len);

	class i2c_base
	{
		public:
			i2c_base(void) = default;
			~i2c_base() = default;
			virtual std::int16_t init(std::uint32_t) const = 0;
			virtual std::int16_t deinit(void) const = 0;
			virtual std::int16_t scan(std::uint8_t) const = 0;
			virtual std::int16_t start_condition(void) const = 0;
			virtual std::int16_t write(std::uint8_t , const void *, std::size_t ,tpfun_i2c_tx_cb) = 0;
			virtual std::int16_t read(std::uint8_t , void *, std::size_t , tpfun_i2c_rx_cb) = 0;
			virtual std::int16_t stop_condition(void) const = 0;
			rtos_osal::mutex mtx;
	};

    template <std::uint8_t u8_inst>
	class i2c : private noncopyable, public i2c_base
	{
		public:
			~i2c() = default;
			static i2c &get_instance(void);
			std::int16_t init(std::uint32_t) const override;
			std::int16_t deinit(void) const override;
			std::int16_t scan(std::uint8_t) const override;
			std::int16_t start_condition(void) const override;
			std::int16_t write(std::uint8_t , const void *, std::size_t ,tpfun_i2c_tx_cb) override;
			std::int16_t read(std::uint8_t , void *, std::size_t , tpfun_i2c_rx_cb) override;
			std::int16_t stop_condition(void) const override;
		private:
			i2c(void) = default;
			tpfun_i2c_tx_cb pfun_tx_cb;
			tpfun_i2c_rx_cb pfun_rx_cb;
	};
}
#endif