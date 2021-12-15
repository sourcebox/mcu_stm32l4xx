/**
 * @file        bit_manipulation.h
 *
 * Bit manipulation functions
 *
 * @author      Oliver Rockstedt <info@sourcebox.de>
 * @license     MIT
 */


#pragma once


// System libraries
#include <cstdint>


namespace mcu {


/**
 * Return value of a single bit
 *
 * Example: bitValue(0b01100100, 5) -> 1
 *
 * @param   value           Input value
 * @param   bitNo           Number of bit to check, starting with 0
 * @return                  Bit value
 */
__attribute__((always_inline))
static inline unsigned int bitValue(unsigned int value, int bitNo)
{
    return (value >> bitNo) & 0x01;
}


/**
 * Set a single bit
 *
 * Example: bitSet(0b11000001, 3) -> 0b11001001
 *
 * @param   value           Input value
 * @param   bitNo           Number of bit to set, starting with 0
 * @return                  Processed value
 */
__attribute__((always_inline))
static inline unsigned int bitSet(unsigned int value, int bitNo)
{
    return value | (1 << bitNo);
}


/**
 * Reset a single bit
 *
 * Example: bitReset(0b11000001, 6) -> 0b10000001
 *
 * @param   value           Input value
 * @param   bitNo           Number of bit to reset, starting with 0
 * @return                  Processed value
 */
__attribute__((always_inline))
static inline unsigned int bitReset(unsigned int value, int bitNo)
{
    return value & ~(1 << bitNo);
}


/**
 * Return bit mask for a number of bits
 *
 * Example: bitMask(4, 2) -> 0b111100
 *
 * @param   noBits          Number of bits
 * @param   offset          Bit offset, starting with 0
 * @return                  Bit mask
 */
__attribute__((always_inline))
static inline unsigned int bitMask(int noBits, int bitOffset)
{
    return ((1 << noBits) - 1) << bitOffset;
}


/**
 * Return right aligned value for a number of bits
 *
 * Example: bitsValue(0b11010100, 4, 3) -> 0b1010
 *
 * @param   value           Input value
 * @param   noBits          Number of bits
 * @param   offset          Bit offset, starting with 0
 * @return                  Processed value
 */
__attribute__((always_inline))
static inline unsigned int bitsValue(unsigned int value, int noBits, int offset)
{
    return (value >> offset) & bitMask(noBits, 0);
}


/**
 * Replace a number of bits with a new value
 *
 * Example: bitsReplace(0b10010100, 0b1110, 3, 3) -> 0b10110100
 *
 * @param   value           Input value
 * @param   replacement     Replacement value
 * @param   noBits          Number of bits to replace
 * @param   offset          Bit offset for replacement, starting with 0
 * @return                  Processed value
 */
__attribute__((always_inline))
static inline unsigned int bitsReplace(unsigned int value,
                                      unsigned int replacement,
                                      int noBits, int offset)
{
    auto mask = bitMask(noBits, offset);
    return (value & ~mask) | ((replacement << offset) & mask);
}


}   // namespace mcu

