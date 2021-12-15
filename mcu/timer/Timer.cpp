/**
 * @file        Timer.cpp
 *
 * Driver for timer peripherals on STM32L4xx
 *
 * @author:     Oliver Rockstedt <info@sourcebox.de>
 * @license     MIT
 */


// Corresponding header
#include "Timer.h"

// This component
#include "../core/NVIC.h"
#include "../rcc/RCC.h"
#include "../rcc/RCC_Registers.h"
#include "../utility/bit_manipulation.h"

// System libraries
#include <cstdlib>


namespace mcu {


// ============================================================================
// Public members
// ============================================================================


Timer::Timer(Id id)
        : id(id)
{
}


void Timer::init()
{
    enableClock();

    auto registers = getRegisters();
    registers->CR1 |= (1 << Timer_Registers::CR1::ARPE);
}


void Timer::init(uint16_t prescaler, uint32_t period)
{
    init();
    setPrescaler(prescaler);
    setPeriod(period);
}


void Timer::init(int freq)
{
    init();
    setFrequency(freq);
}


void Timer::init(Config& config)
{
    init();
    setPrescaler(config.prescaler);
    setPeriod(config.period);
    setMasterMode(config.masterMode);
}


void Timer::deinit()
{
    disableClock();
}


uint32_t Timer::getPrescaler()
{
    auto registers = getRegisters();

    return registers->PSC + 1;
}


void Timer::setPrescaler(volatile uint16_t value)
{
    auto registers = getRegisters();

    registers->PSC = value - 1;
}


uint32_t Timer::getPeriod()
{
    auto registers = getRegisters();

    return registers->ARR;
}


void Timer::setPeriod(volatile uint32_t value)
{
    auto registers = getRegisters();

    registers->ARR = value;
    triggerUpdateEvent();
}


void Timer::setFrequency(uint32_t freq)
{
    uint32_t clockFreq;

    switch (id) {
        case TIM1:
        case TIM15:
        case TIM16:
            clockFreq = RCC::get().getPCLK2Freq();
            break;
        default:
            clockFreq = RCC::get().getPCLK1Freq();
            break;
    }

    if (id != TIM2) {
        // 16-bit timers
        auto periodCycles = clockFreq / freq;
        uint16_t prescaler = (periodCycles / 0xFFFF) + 1;
        auto period = (periodCycles + (prescaler / 2)) / prescaler;
        setPrescaler(prescaler);
        setPeriod(period);
    } else {
        // 32-bit timers
        auto periodCycles = clockFreq / freq;
        setPrescaler(1);
        setPeriod(periodCycles);
    }
}


void Timer::setMasterMode(MasterMode mode)
{
    auto registers = getRegisters();

    registers->CR2 = bitsReplace(registers->CR2, (int)mode, 3,
            Timer_Registers::CR2::MMS_0);
}


void Timer::start()
{
    auto registers = getRegisters();
    registers->CR1 |= (1 << Timer_Registers::CR1::CEN);
}


void Timer::stop()
{
    auto registers = getRegisters();
    registers->CR1 &= ~(1 << Timer_Registers::CR1::CEN);
}


uint32_t Timer::getCounter()
{
    auto registers = getRegisters();
    return registers->CNT;
}


void Timer::setCounter(uint32_t value)
{
    auto registers = getRegisters();
    registers->CNT = value;
}


void Timer::setUpdateCallback(CallbackFunc func)
{
    updateCallback = func;

    auto registers = getRegisters();

    if (func != nullptr) {
        registers->DIER |= (1 << Timer_Registers::DIER::UIE);
        auto& nvic = NVIC::get();
        nvic.enableIrq(getIRQNumber(id));
    } else {
        registers->DIER &= ~(1 << Timer_Registers::DIER::UIE);
    }
}


void Timer::triggerUpdateEvent()
{
    auto registers = getRegisters();

    registers->EGR |= (1 << Timer_Registers::EGR::UG);
}


void Timer::setUpdateDMARequest(bool state)
{
    auto registers = getRegisters();

    if (state) {
        registers->DIER |= (1 << Timer_Registers::DIER::UDE);
    } else {
        registers->DIER &= ~(1 << Timer_Registers::DIER::UDE);
    }
}


void Timer::irq()
{
    auto registers = getRegisters();

    if (registers->SR & (1 << Timer_Registers::SR::UIF)) {
        registers->SR &= ~(1 << Timer_Registers::SR::UIF);

        if (updateCallback != nullptr) {
            updateCallback();
        }
    }

    if (registers->SR & (1 << Timer_Registers::SR::CC1IF)) {
        registers->SR &= ~(1 << Timer_Registers::SR::CC1IF);

        auto callback = channels[0].ch1Callbacks[id];

        if (callback != nullptr) {
            callback();
        }
    }

    if (registers->SR & (1 << Timer_Registers::SR::CC2IF)) {
        registers->SR &= ~(1 << Timer_Registers::SR::CC2IF);

        auto callback = channels[1].ch2Callbacks[id];

        if (callback != nullptr) {
            callback();
        }
    }

    if (registers->SR & (1 << Timer_Registers::SR::CC3IF)) {
        registers->SR &= ~(1 << Timer_Registers::SR::CC3IF);

        auto callback = channels[2].ch3Callbacks[id];

        if (callback != nullptr) {
            callback();
        }
    }

    if (registers->SR & (1 << Timer_Registers::SR::CC4IF)) {
        registers->SR &= ~(1 << Timer_Registers::SR::CC4IF);

        auto callback = channels[3].ch4Callbacks[id];

        if (callback != nullptr) {
            callback();
        }
    }
}


// ============================================================================
// Protected members
// ============================================================================


void Timer::enableClock()
{
    auto rccRegisters = RCC_Registers::get();

    switch (id) {
        case TIM1:
            rccRegisters->APB2ENR |= (1 << RCC_Registers::APB2ENR::TIM1EN);
            break;
        case TIM2:
            rccRegisters->APB1ENR1 |= (1 << RCC_Registers::APB1ENR1::TIM2EN);
            break;
        case TIM3:
            rccRegisters->APB1ENR1 |= (1 << RCC_Registers::APB1ENR1::TIM3EN);
            break;
        case TIM6:
            rccRegisters->APB1ENR1 |= (1 << RCC_Registers::APB1ENR1::TIM6EN);
            break;
        case TIM7:
            rccRegisters->APB1ENR1 |= (1 << RCC_Registers::APB1ENR1::TIM7EN);
            break;
        case TIM15:
            rccRegisters->APB2ENR |= (1 << RCC_Registers::APB2ENR::TIM15EN);
            break;
        case TIM16:
            rccRegisters->APB2ENR |= (1 << RCC_Registers::APB2ENR::TIM16EN);
            break;
        default:
            break;
    }
}


void Timer::disableClock()
{
    auto rccRegisters = RCC_Registers::get();

    switch (id) {
        case TIM1:
            rccRegisters->APB2ENR &= ~(1 << RCC_Registers::APB2ENR::TIM1EN);
            break;
        case TIM2:
            rccRegisters->APB1ENR1 &= ~(1 << RCC_Registers::APB1ENR1::TIM2EN);
            break;
        case TIM3:
            rccRegisters->APB1ENR1 &= ~(1 << RCC_Registers::APB1ENR1::TIM3EN);
            break;
        case TIM6:
            rccRegisters->APB1ENR1 &= ~(1 << RCC_Registers::APB1ENR1::TIM6EN);
            break;
        case TIM7:
            rccRegisters->APB1ENR1 &= ~(1 << RCC_Registers::APB1ENR1::TIM7EN);
            break;
        case TIM15:
            rccRegisters->APB2ENR &= ~(1 << RCC_Registers::APB2ENR::TIM15EN);
            break;
        case TIM16:
            rccRegisters->APB2ENR &= ~(1 << RCC_Registers::APB2ENR::TIM16EN);
            break;
        default:
            break;
    }
}


Timer Timer::tim1 = Timer(Timer::TIM1);
Timer Timer::tim2 = Timer(Timer::TIM2);
Timer Timer::tim3 = Timer(Timer::TIM3);
Timer Timer::tim6 = Timer(Timer::TIM6);
Timer Timer::tim7 = Timer(Timer::TIM7);
Timer Timer::tim15 = Timer(Timer::TIM15);
Timer Timer::tim16 = Timer(Timer::TIM16);


}   // namespace mcu
