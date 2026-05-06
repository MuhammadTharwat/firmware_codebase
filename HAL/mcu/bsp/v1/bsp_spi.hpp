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
#ifndef __TI_COMPILER_VERSION__
#include <cstdint>
#else
#include <stdint.h>
#endif
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

#ifndef __TI_COMPILER_VERSION__
    using tpfun_spi_tx_cb = void (*)(void);
    using tpfun_spi_rx_cb = void (*)(const void *pv_rx_data, size_t sz_len);
#else
    typedef void (*tpfun_spi_tx_cb)(void);
    typedef void (*tpfun_spi_rx_cb)(const void *pv_rx_data, size_t sz_len);
#endif

    class spi : private noncopyable
    {
    public:
        spi(spi_dev &);
        ~spi(void) = default;
        int16_t init(uint16_t, tenu_spi_mode, bool);
        int16_t deinit(void) const;
        int16_t slave_enable(uint8_t);
        int16_t slave_disable(uint8_t);
        int16_t tx(const void *, size_t, tpfun_spi_tx_cb);
        int16_t rx(void *, size_t, tpfun_spi_rx_cb);
        int16_t tx_rx_ring(const void *, void *, size_t, tpfun_spi_tx_cb);
        rtos_osal::mutex mtx;

    private:
        uint16_t u16_spi_clk_divisor;
        tenu_spi_mode enu_spi_mode;
        tpfun_spi_tx_cb pfun_tx_cb;
        tpfun_spi_rx_cb pfun_rx_cb;
        spi_dev &rspi_dev;
    };

    spi_dev &get_spi_dev(uintmax_t);
}

#endif /*BSP_SPI_H_*/
