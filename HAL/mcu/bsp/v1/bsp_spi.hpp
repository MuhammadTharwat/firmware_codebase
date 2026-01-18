/**
  ******************************************************************************
  * @file			bsp_spi.hpp
  * @description	This is the header file of the board support package "SPI"
  * @author			Ahmed Salama
  * @version		V0.0
  * @date			08-April-2024
  ******************************************************************************
*/
#ifndef BSP_SPI_H_
#define BSP_SPI_H_
#include <cstdint>
#include <stddef.h>
#include <noncopyable.hpp>
#include <mutex.hpp>
#include "bsp_objects.hpp"
/***********************************************  Defines    **************************************************/
/***********************************************  Constants   *************************************************/
/***********************************************  Enumerations   **********************************************/
/*********************************************** Data types  **************************************************/
namespace bsp
{
    enum tenu_spi_mode
    {
        spi_mode_pol_high_ph_1st_edge = 0,
        spi_mode_pol_high_ph_2nd_edge,
        spi_mode_pol_low_ph_1st_edge,
        spi_mode_pol_low_ph_2nd_edge
    };
    
    using tpfun_spi_tx_cb = void (*)(void);
    using tpfun_spi_rx_cb = void (*)(const void *pv_rx_data, size_t sz_len);

    class spi : private noncopyable
    {
    public:
        spi(spi_dev &);
        ~spi(void) = default;
        std::int16_t init(std::uint16_t, tenu_spi_mode, bool);
        std::int16_t deinit(void) const;
        std::int16_t slave_enable(std::uint8_t);
        std::int16_t slave_disable(std::uint8_t);
        std::int16_t tx(const void *, std::size_t, tpfun_spi_tx_cb);
        std::int16_t rx(void *, std::size_t, tpfun_spi_rx_cb);
        std::int16_t tx_rx_ring(const void *, void *, std::size_t, tpfun_spi_tx_cb);
        rtos_osal::mutex mtx;

    private:
        std::uint16_t u16_spi_clk_divisor;
        tenu_spi_mode enu_spi_mode;
        tpfun_spi_tx_cb pfun_tx_cb;
        tpfun_spi_rx_cb pfun_rx_cb;
        spi_dev &rspi_dev;
    };

    spi_dev &get_spi_dev(std::uintmax_t);
}

#endif /*BSP_SPI_H_*/