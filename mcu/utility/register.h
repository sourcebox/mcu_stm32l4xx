/**
 * @file        register.h
 *
 * Type definitions for registers
 *
 * @author      Oliver Rockstedt <info@sourcebox.de>
 * @license     MIT
 */


#pragma once


// System libraries
#include <cstdint>


namespace mcu {


typedef volatile uint8_t Register8;
typedef volatile uint16_t Register16;
typedef volatile uint32_t Register32;


}   // namespace mcu
