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

    class spi_base
    {
    public:
        spi_base(void) = default;
        ~spi_base(void) = default;
        virtual std::int16_t init(std::uint32_t , tenu_spi_mode ) = 0;
        virtual std::int16_t deinit(void) const = 0;
        virtual std::int16_t tx(void *, std::size_t , tpfun_spi_tx_cb) = 0;
        virtual std::int16_t rx(void *, std::size_t , tpfun_spi_rx_cb) = 0;
        rtos_osal::mutex mtx;
    };

    template <std::uint8_t u8_inst>
    class spi : private noncopyable, public spi_base
    {
    public:
        ~spi(void) = default;
        static spi &get_instance(void);
        std::int16_t init(std::uint32_t , tenu_spi_mode ) override;
        std::int16_t deinit(void) const override;
        std::int16_t tx(void *, std::size_t , tpfun_spi_tx_cb) override;
        std::int16_t rx(void *, std::size_t , tpfun_spi_rx_cb) override;
    private:
        spi(void) = default;
        std::uint32_t u32_baudrate_bps;
        tenu_spi_mode enu_spi_mode;
        tpfun_spi_tx_cb pfun_tx_cb;
        tpfun_spi_rx_cb pfun_rx_cb;
    };
}