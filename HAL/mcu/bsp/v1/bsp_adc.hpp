/**
  ******************************************************************************
  * @file			bsp_adc.hpp
  * @description	This is the header file of the board support package "ADC"
  * @author			Ahmed Salama
  * @version		V0.0
  * @date			08-April-2024
  ******************************************************************************
*/
#include "stdint.h"
#include <stddef.h>
#include <noncopyable.hpp>
/***********************************************  Defines    **************************************************/
/***********************************************  Constants   *************************************************/
/***********************************************  Enumerations   **********************************************/
/*********************************************** Data types  **************************************************/
namespace bsp
{
    enum tenu_adc_res
	{
		bsp_adc_res_10bit = 0,
		bsp_adc_res_12bit,
		bsp_adc_res_16bit,
		bsp_adc_res_invalid
	};
    using tpfun_adc_cplt = void (*)(std::int16_t );
    struct tstr_adc_conv_cfg
    {
        tenu_adc_res enu_res;         /*ADC Resolution*/
        const std::uint8_t *pu8_channels;      /*Channels*/
        std::uint8_t u8_num_channels;          /*Number of channels (1 in single channel mode)*/
        void *pv_adc_raw_buff;            /*Data Buffer
                                            Data in the buffer will be ordered
                                            in the same sequence as the given channels.
                                            For example, if ch1 and ch2 are configured,
                                            data of the complete samples of ch1 will come
                                            first, then data of complete samples of ch2 will come
                                            last*/
        std::size_t sz_adc_raw_buff_max;       /*Buffer Size*/
        std::size_t sz_num_samples;            /*Number of samples*/
        std::uint32_t u32_sampling_rate;       /*Sampling Rate as SPS*/
        tpfun_adc_cplt pfun_adc_cplt; /*ADC Conversion Complete Callback, NULL for Synchronous Operation*/
    };

    class adc_base
    {
        public :
            adc_base(void) = default;
            ~adc_base(void) = default;
            virtual std::int16_t init(void) const = 0;
            virtual std::uint32_t get_vref(void) const = 0;
            virtual std::int16_t start_conv(tstr_bsp_adc_conv_cfg &) = 0;
            virtual void stop_conv(void) const = 0;
            virtual void deinit (void) const = 0;
    };

    template <std::uint8_t u8_inst>
    class adc : private noncopyable, public adc_base
    {
        public :
            ~adc(void) = default;
            static adc &get_instance(void);
            std::int16_t init(void) const override;
            std::uint32_t get_vref(void) const override;
            std::int16_t start_conv(tstr_bsp_adc_conv_cfg &) override;
            void stop_conv(void) const override;
            void deinit (void) const override;
        private:
            adc(void) = default;
            tstr_bsp_adc_conv_cfg str_adc_cfg;
    };
}