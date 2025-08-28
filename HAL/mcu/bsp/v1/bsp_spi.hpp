/**
  ******************************************************************************
  * @file			bsp_spi.hpp
  * @description	This is the header file of the board support package "SPI"
  * @author			Ahmed Salama
  * @version		V0.0
  * @date			08-April-2024
  ******************************************************************************
*/
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
        cpol_low_cpha_low = 0,
        cpol_low_cpha_high,
        cpol_high_cpha_low,
        cpol_high_cpha_high
    };
    using tpfun_spi_tx_cb = void (*)(void);
    using tpfun_spi_rx_cb = void (*)(const void *pv_rx_data, size_t sz_len);

    class spi : private noncopyable
    {
    public:
        spi(spi_dev &);
        ~spi(void) = default;
        std::int16_t init(std::uint32_t, tenu_spi_mode);
        std::int16_t deinit(void) const;
        std::int16_t tx(void *, std::size_t, tpfun_spi_tx_cb);
        std::int16_t rx(void *, std::size_t, tpfun_spi_rx_cb);
        rtos_osal::mutex mtx;

    private:
        std::uint32_t u32_spi_clk_divisor;
        tenu_spi_mode enu_spi_mode;
        tpfun_spi_tx_cb pfun_tx_cb;
        tpfun_spi_rx_cb pfun_rx_cb;
    };

    spi_dev &get_spi_dev(std::uintmax_t);
}