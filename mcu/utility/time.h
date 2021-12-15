/**
 * @file        time.h
 *
 * System time functions
 *
 * @author:     Oliver Rockstedt
 * @license     MIT
 */


#pragma once


// This component
#include "../core/SysTick.h"
#include "../rcc/RCC.h"

// System libraries
#include <cstdint>


namespace mcu {


/**
 * Return number of elapsed microseconds
 *
 * @return                  No of microseconds
 */
static inline uint64_t getMicroseconds()
{
    return SysTick::get().getClockCycles() / (RCC::get().getSYSCLKFreq() / 1000000);
}


/**
 * Return number of elapsed milliseconds
 *
 * @return                  No of milliseconds
 */
static inline uint32_t getMilliseconds()
{
    // Todo: Make independent of 1ms systick interval
    return SysTick::get().getTicks();
}


/**
 * Delay by a number of microseconds
 *
 * @param value             No of microseconds to wait
 */
static inline void delayMicroseconds(uint64_t value)
{
    uint64_t startTime = getMicroseconds();

    volatile uint64_t interval;

    do {
        interval = getMicroseconds() - startTime;
    } while (interval < value);
}


/**
 * Delay by a number of milliseconds
 *
 * @param value             No of milliseconds to wait
 */
static inline void delayMilliseconds(uint32_t value)
{
    uint32_t startTime = getMilliseconds();

    volatile uint32_t interval;

    do {
        interval = getMilliseconds() - startTime;
    } while (interval < value);
}


}   // namespace mcu
