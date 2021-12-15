/**
 * @file        LPTimer.cpp
 *
 * Driver for low power timer peripherals on STM32L4xx
 *
 * @author:     Oliver Rockstedt <info@sourcebox.de>
 * @license     MIT
 */


// Corresponding header
#include "LPTimer.h"

// This component
#include "../core/NVIC.h"
#include "../rcc/RCC.h"
#include "../rcc/RCC_Registers.h"
#include "../utility/bit_manipulation.h"
#include "../utility/log2.h"

// System libraries
#include <cstdlib>


namespace mcu {


// ============================================================================
// Public members
// ============================================================================


LPTimer::LPTimer(Id id)
    : id(id)
{
}


void LPTimer::init()
{
    enableClock();

    auto registers = getRegisters();

    registers->CFGR |= (1 << LPTimer_Registers::CFGR::PRELOAD);
}


void LPTimer::init(uint16_t prescaler, uint32_t period)
{
    init();
    setPrescaler(prescaler);
    setPeriod(period);
}


void LPTimer::init(int freq)
{
    init();
    setFrequency(freq);
}


void LPTimer::init(Config& config)
{
    init();
    setPrescaler(config.prescaler);
    setPeriod(config.period);
}


void LPTimer::deinit()
{
    disableClock();
}


uint32_t LPTimer::getPrescaler()
{
    auto registers = getRegisters();

    return (1 << bitsValue(registers->CFGR, 3, LPTimer_Registers::CFGR::PRESC_0));
}


void LPTimer::setPrescaler(uint16_t value)
{
    disable();

    auto registers = getRegisters();

    registers->CFGR = bitsReplace(registers->CFGR, log2(value), 3,
            LPTimer_Registers::CFGR::PRESC_0);

    enable();
}


uint32_t LPTimer::getPeriod()
{
    auto registers = getRegisters();

    return registers->ARR;
}


void LPTimer::setPeriod(volatile uint32_t value)
{
    enable();

    auto registers = getRegisters();

    registers->ARR = value;
}


void LPTimer::setFrequency(uint32_t freq)
{
    uint32_t clockFreq = RCC::get().getPCLK1Freq();

    auto periodCycles = clockFreq / freq;
    uint16_t prescaler = (periodCycles / 0xFFFF) + 1;

    // Force prescaler to a power of 2
    prescaler = 1 << log2(prescaler);

    auto period = (periodCycles + (prescaler / 2)) / prescaler;

    if (period > 0xFFFF) {
        prescaler <<= 1;
        period = (periodCycles + (prescaler / 2)) / prescaler;
    }

    setPrescaler(prescaler);
    setPeriod(period);
}


void LPTimer::enable()
{
    auto registers = getRegisters();
    registers->CR |= (1 << LPTimer_Registers::CR::ENABLE);
}


void LPTimer::disable()
{
    auto registers = getRegisters();
    registers->CR &= ~(1 << LPTimer_Registers::CR::ENABLE);
}


void LPTimer::start()
{
    auto registers = getRegisters();
    registers->CR |= 1 << LPTimer_Registers::CR::CNTSTRT;
}


void LPTimer::stop()
{
    disable();
    enable();
}


uint32_t LPTimer::getCounter()
{
    auto registers = getRegisters();
    return registers->CNT;
}


void LPTimer::setCounter(uint32_t value)
{
    auto registers = getRegisters();
    registers->CNT = value;
}


void LPTimer::setUpdateCallback(CallbackFunc func)
{
    disable();

    updateCallback = func;

    auto registers = getRegisters();

    if (func != nullptr) {
        registers->IER |= (1 << LPTimer_Registers::IER::ARRMIE);
        auto& nvic = NVIC::get();
        nvic.enableIrq(getIRQNumber(id));
    } else {
        registers->IER &= ~(1 << LPTimer_Registers::IER::ARRMIE);
    }

    enable();
}


void LPTimer::irq()
{
    auto registers = getRegisters();

    if (registers->ISR & (1 << LPTimer_Registers::ISR::ARRM)) {
        registers->ICR |= (1 << LPTimer_Registers::ICR::ARRMCF);

        if (updateCallback != nullptr) {
            updateCallback();
        }
    }

    if (registers->ISR & (1 << LPTimer_Registers::ISR::CMPM)) {
        registers->ICR |= (1 << LPTimer_Registers::ICR::CMPMCF);

        auto callback = channels[0].ch1Callbacks[id];

        if (callback != nullptr) {
            callback();
        }
    }
}


// ============================================================================
// Protected members
// ============================================================================


void LPTimer::enableClock()
{
    auto rccRegisters = RCC_Registers::get();

    switch (id) {
        case LPTIM1:
            rccRegisters->APB1ENR1 |= (1 << RCC_Registers::APB1ENR1::LPTIM1EN);
            break;
        case LPTIM2:
            rccRegisters->APB1ENR2 |= (1 << RCC_Registers::APB1ENR2::LPTIM2EN);
            break;
        default:
            break;
    }
}


void LPTimer::disableClock()
{
    auto rccRegisters = RCC_Registers::get();

    switch (id) {
        case LPTIM1:
            rccRegisters->APB1ENR1 &= ~(1 << RCC_Registers::APB1ENR1::LPTIM1EN);
            break;
        case LPTIM2:
            rccRegisters->APB1ENR2 &= ~(1 << RCC_Registers::APB1ENR2::LPTIM2EN);
            break;
        default:
            break;
    }
}


LPTimer LPTimer::lptimer1 = LPTimer(LPTimer::LPTIM1);
LPTimer LPTimer::lptimer2 =LPTimer(LPTimer::LPTIM2);


}   // namespace mcu
