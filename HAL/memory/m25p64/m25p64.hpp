/**
 ******************************************************************************
 * @file            m25p64.hpp
 * @description     This is header file of the m25p64 serial flash memory
 * @author          Muhammad Tharwat
 * @version         V0.0
 * @date            23-August-2025
 ******************************************************************************
 */

#ifndef M25P64_H
#define M25P64_H

#include "bsp_spi.hpp"
#include "bsp_io.hpp"

/***********************************************  Defines    **************************************************/

/***********************************************  Constants   *************************************************/

/***********************************************  Enumerations   **********************************************/

/*********************************************** Data types  **************************************************/

class m25p64
{
public:
    m25p64(bsp::spi &, bsp::output &);
    ~m25p64() = default;
    std::int16_t program_page(std::uint32_t, const void *, std::uint8_t);
    std::int16_t verify_electonic_signature(void);
    std::int16_t verify_identification(void);
    std::int16_t read(std::uint32_t, void *, std::uint32_t);

private:
    bsp::spi &rspi;
    bsp::output &rcs;
};
#endif /*M25P64_H */