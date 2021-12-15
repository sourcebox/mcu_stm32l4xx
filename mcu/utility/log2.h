/**
 * @file        log2.h
 *
 * Function to calculate logarithm to the base of 2
 *
 * @author      Oliver Rockstedt <info@sourcebox.de>
 * @license     MIT
 */


#pragma once


namespace mcu {


/**
 * Return logarithm to the base of 2
 *
 * Example: log2(1024) -> 10
 *
 * @param   value           Input value
 * @return                  Log2 value
 */
__attribute__((always_inline))
static inline unsigned int log2(unsigned int value)
{
    if (value > 0) {
        int result = 0;
        while (value >>= 1) {
            result++;
        }
        return result;
    } else {
        return 1;
    }
}


}   //  namespace mcu
