/**
 * @file        Timer_Channel.cpp
 *
 * Timer channel on STM32L4xx
 *
 * @author:     Oliver Rockstedt <info@sourcebox.de>
 * @license     MIT
 */


// Corresponding header
#include "Timer_Channel.h"

// This component
#include "../core/NVIC.h"


namespace mcu {


// ============================================================================
// Public members
// ============================================================================


Timer_Channel::Timer_Channel(Id timerId, ChannelId channelId)
    : timerId(timerId), channelId(channelId)
{
}


void Timer_Channel::initPWM(Pin::Id pinId, Polarity polarity)
{
    auto modeBits = 0b0110;     // PWM mode 1
    bool polarityBit = polarity == Polarity::ACTIVE_HIGH ? 0 : 1;

    auto registers = Timer_Registers::get(timerId);

    switch (channelId) {
        case CH1:
            registers->CCER &= ~(1 << Timer_Registers::CCER::CC1E);
            registers->CCMR1 = bitsReplace(registers->CCMR1,
                    modeBits, 3, Timer_Registers::CCMR1::OC1M_0);
            registers->CCMR1 = bitsReplace(registers->CCMR1,
                    modeBits >> 3, 1, Timer_Registers::CCMR1::OC1M_3);
            registers->CCER = bitsReplace(registers->CCER,
                    polarityBit, 1, Timer_Registers::CCER::CC1P);
            registers->CCER = bitsReplace(registers->CCER,
                    polarityBit, 1, Timer_Registers::CCER::CC1NP);
            registers->CCER |= (1 << Timer_Registers::CCER::CC1NE);
            registers->CCER |= (1 << Timer_Registers::CCER::CC1E);
            break;
        case CH2:
            registers->CCER &= ~(1 << Timer_Registers::CCER::CC2E);
            registers->CCMR1 = bitsReplace(registers->CCMR1,
                    modeBits, 3, Timer_Registers::CCMR1::OC2M_0);
            registers->CCMR1 = bitsReplace(registers->CCMR1,
                    modeBits >> 3, 1, Timer_Registers::CCMR1::OC2M_3);
            registers->CCER = bitsReplace(registers->CCER,
                    polarityBit, 1, Timer_Registers::CCER::CC2P);
            registers->CCER = bitsReplace(registers->CCER,
                    polarityBit, 1, Timer_Registers::CCER::CC2NP);
            registers->CCER |= (1 << Timer_Registers::CCER::CC2NE);
            registers->CCER |= (1 << Timer_Registers::CCER::CC2E);
            break;
        case CH3:
            registers->CCER &= ~(1 << Timer_Registers::CCER::CC3E);
            registers->CCMR2 = bitsReplace(registers->CCMR2,
                    modeBits, 3, Timer_Registers::CCMR2::OC3M_0);
            registers->CCMR2 = bitsReplace(registers->CCMR2,
                    modeBits >> 3, 1, Timer_Registers::CCMR2::OC3M_3);
            registers->CCER = bitsReplace(registers->CCER,
                    polarityBit, 1, Timer_Registers::CCER::CC3P);
            registers->CCER = bitsReplace(registers->CCER,
                    polarityBit, 1, Timer_Registers::CCER::CC3NP);
            registers->CCER |= (1 << Timer_Registers::CCER::CC3NE);
            registers->CCER |= (1 << Timer_Registers::CCER::CC3E);
            break;
        case CH4:
            registers->CCER &= ~(1 << Timer_Registers::CCER::CC4E);
            registers->CCMR2 = bitsReplace(registers->CCMR2,
                    modeBits, 3, Timer_Registers::CCMR2::OC4M_0);
            registers->CCMR2 = bitsReplace(registers->CCMR2,
                    modeBits >> 3, 1, Timer_Registers::CCMR2::OC4M_3);
            registers->CCER = bitsReplace(registers->CCER,
                    polarityBit, 1, Timer_Registers::CCER::CC4P);
            registers->CCER = bitsReplace(registers->CCER,
                    polarityBit, 1, Timer_Registers::CCER::CC4NP);
            registers->CCER |= (1 << Timer_Registers::CCER::CC4NE);
            registers->CCER |= (1 << Timer_Registers::CCER::CC4E);
            break;
    }

    if (timerId == Id::TIM1 || timerId == Id::TIM15 || timerId == Id::TIM16) {
        registers->BDTR |= (1 << Timer_Registers::BDTR::MOE);
    }

    initPin(pinId);
}


void Timer_Channel::initPin(Pin::Id pinId)
{
    if (pinId == Pin::NONE) {
        return;
    }

    Pin::AF af;

    switch (timerId) {
        case Id::TIM1:
        case Id::TIM2:
            af = Pin::AF::AF1;
            break;
        case Id::TIM3:
            af = Pin::AF::AF2;
            break;
        case Id::TIM6:
        case Id::TIM7:
            // These timers have to pins
            return;
        case Id::TIM15:
        case Id::TIM16:
            af = Pin::AF::AF14;
            break;
    }

    auto pin = Pin::get(pinId);

    pin.setMode(Pin::Mode::AF);
    pin.setAlternateFunction(af);
    pin.setOutputType(Pin::OutputType::PUSH_PULL);
    pin.setPullMode(Pin::PullMode::NONE);
}


void Timer_Channel::setCompare(volatile uint32_t value)
{
    auto registers = Timer_Registers::get(timerId);

    switch (channelId) {
        case CH1:
            registers->CCR1 = value;
            break;
        case CH2:
            registers->CCR2 = value;
            break;
        case CH3:
            registers->CCR3 = value;
            break;
        case CH4:
            registers->CCR4 = value;
            break;
    }
}


uint32_t Timer_Channel::getCapture()
{
    auto registers = Timer_Registers::get(timerId);

    switch (channelId) {
        case CH1:
            return registers->CCR1;
        case CH2:
            return registers->CCR2;
        case CH3:
            return registers->CCR3;
        case CH4:
            return registers->CCR4;
    }

    return 0;
}


void Timer_Channel::setCallback(CallbackFunc func)
{
    auto registers = Timer_Registers::get(timerId);

    if (func != nullptr) {

        switch (channelId) {
            case CH1:
                ch1Callbacks[timerId] = func;
                registers->DIER |= (1 << Timer_Registers::DIER::CC1IE);
                break;
            case CH2:
                ch2Callbacks[timerId] = func;
                registers->DIER |= (1 << Timer_Registers::DIER::CC2IE);
                break;
            case CH3:
                ch3Callbacks[timerId] = func;
                registers->DIER |= (1 << Timer_Registers::DIER::CC3IE);
                break;
            case CH4:
                ch4Callbacks[timerId] = func;
                registers->DIER |= (1 << Timer_Registers::DIER::CC4IE);
                break;
        }

        auto& nvic = NVIC::get();
        nvic.enableIrq(getIRQNumber(timerId));
    } else {
        switch (channelId) {
            case CH1:
                ch1Callbacks[timerId] = nullptr;
                registers->DIER &= ~(1 << Timer_Registers::DIER::CC1IE);
                break;
            case CH2:
                ch2Callbacks[timerId] = nullptr;
                registers->DIER &= ~(1 << Timer_Registers::DIER::CC2IE);
                break;
            case CH3:
                ch3Callbacks[timerId] = nullptr;
                registers->DIER &= ~(1 << Timer_Registers::DIER::CC3IE);
                break;
            case CH4:
                ch4Callbacks[timerId] = nullptr;
                registers->DIER &= ~(1 << Timer_Registers::DIER::CC4IE);
                break;
        }
    }

}


// ============================================================================
// Protected members
// ============================================================================


Timer_Channel::CallbackFunc Timer_Channel::ch1Callbacks[7];
Timer_Channel::CallbackFunc Timer_Channel::ch2Callbacks[7];
Timer_Channel::CallbackFunc Timer_Channel::ch3Callbacks[7];
Timer_Channel::CallbackFunc Timer_Channel::ch4Callbacks[7];


}   // namespace mcu
