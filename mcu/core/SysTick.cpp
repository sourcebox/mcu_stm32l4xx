/**
 * @file        SysTick.cpp
 *
 * Driver for SysTick on Cortex-M4
 *
 * @author:     Oliver Rockstedt <info@sourcebox.de>
 * @license     MIT
 */


// Corresponding header
#include "SysTick.h"

// Local includes
#include "../utility/bit_manipulation.h"
#include "NVIC.h"


namespace mcu {


// ============================================================================
// Public members
// ============================================================================


void SysTick::configure(int cycles, ClockSource clockSource)
{
    auto registers = SysTick_Registers::get();

    registers->LOAD = cycles - 1;
    registers->VAL = 0;

    if (clockSource == CLKSOURCE_HCLK) {
        registers->CTRL |= (1 << SysTick_Registers::CTRL::CLKSOURCE);
    }

    NVIC::get().setPriority(-1, (1 << NVIC_PRIO_BITS) - 1);

    registers->CTRL |= (1 << SysTick_Registers::CTRL::ENABLE)
                       | (1 << SysTick_Registers::CTRL::TICKINT);
}


void SysTick::deinit()
{
    auto registers = SysTick_Registers::get();

    registers->CTRL
        = bitReset(registers->CTRL, SysTick_Registers::CTRL::ENABLE);
    registers->CTRL
        = bitReset(registers->CTRL, SysTick_Registers::CTRL::TICKINT);
}


uint32_t SysTick::getTicks()
{
    return ticks;
}


uint64_t SysTick::getClockCycles()
{
    disableInterrupts();

    auto registers = SysTick_Registers::get();

    uint64_t loadValue = registers->LOAD;
    uint64_t clockCycles
        = ((loadValue + 1) * ticks) + (loadValue - registers->VAL);

    enableInterrupts();

    return clockCycles;
}


void SysTick::irq()
{
    ticks++;

    if (callback != nullptr) {
        callback();
    }
}


void SysTick::setCallback(CallbackFunc func)
{
    callback = func;
}


// ============================================================================
// Protected members
// ============================================================================


SysTick SysTick::instance;


} // namespace mcu
