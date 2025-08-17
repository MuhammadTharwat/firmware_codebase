/**
  ******************************************************************************
  * @file			bsp_button.hpp
  * @description	This is the header file of the board support package "button"
  * @author			Ahmed Salama
  * @version		V0.0
  * @date			09-April-2024
  ******************************************************************************
*/
#include <cstdint>
#include <stddef.h>
#include <noncopyable.hpp>
/***********************************************  Defines    **************************************************/
/***********************************************  Constants   *************************************************/
/***********************************************  Enumerations   **********************************************/
/*********************************************** Data types  **************************************************/
namespace bsp
{
    using tpfun_bsp_bttn_release_cb = void (*)(std::uint32_t);
    using tpfun_bsp_bttn_press_cb = void (*)(void);

    class button_base
    {
        public:
            button_base(void) = default;
            ~button_base(void) = default;
            virtual std::int16_t start(tpfun_bsp_bttn_press_cb ,tpfun_bsp_bttn_release_cb ) = 0;
            virtual void stop(void) const = 0;
    };

    template <std::uint8_t u8_inst>
    class button  : private noncopyable, public button_base
    {
        public:
            ~button(void) = default;
            static button &get_instance(void);
            std::int16_t start(tpfun_bsp_bttn_press_cb ,tpfun_bsp_bttn_release_cb ) override;
            void stop(void) const override;
        private:
            button(void) = default;
            tpfun_bsp_bttn_press_cb pfun_press_cb;
            tpfun_bsp_bttn_release_cb pfun_release_cb;
    };
}