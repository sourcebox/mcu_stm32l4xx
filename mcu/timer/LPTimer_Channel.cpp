/**
 * @file        LPTimer_Channel.cpp
 *
 * Low power timer channel on STM32L4xx
 *
 * @author:     Oliver Rockstedt <info@sourcebox.de>
 * @license     MIT
 */


// Corresponding header
#include "LPTimer_Channel.h"

// This component
#include "../core/NVIC.h"
#include "../utility/bit_manipulation.h"


namespace mcu {


// ============================================================================
// Public members
// ============================================================================


LPTimer_Channel::LPTimer_Channel(Id timerId, ChannelId channelId)
    : timerId(timerId), channelId(channelId)
{
}


void LPTimer_Channel::initPWM(Pin::Id pinId, Polarity polarity)
{
    auto registers = LPTimer_Registers::get(timerId);

    // Disable timer
    registers->CR = bitReset(registers->CR, LPTimer_Registers::CR::ENABLE);

    bool polarityBit = polarity == Polarity::ACTIVE_HIGH ? 0 : 1;

    registers->CFGR = bitsReplace(registers->CFGR, polarityBit, 1,
            LPTimer_Registers::CFGR::WAVPOL);

    initPin(pinId);

    // Enable timer
    registers->CR = bitSet(registers->CR, LPTimer_Registers::CR::ENABLE);
}


void LPTimer_Channel::initPin(Pin::Id pinId)
{
    if (pinId == Pin::NONE) {
        return;
    }

    Pin::AF af;

    switch (timerId) {
        case Id::LPTIM1:
            af = Pin::AF::AF1;
            break;
        case Id::LPTIM2:
            af = Pin::AF::AF14;
            break;
    }

    auto pin = Pin::get(pinId);

    pin.setMode(Pin::Mode::AF);
    pin.setAlternateFunction(af);
    pin.setOutputType(Pin::OutputType::PUSH_PULL);
    pin.setPullMode(Pin::PullMode::NONE);
}


void LPTimer_Channel::setCompare(volatile uint32_t value)
{
    auto registers = LPTimer_Registers::get(timerId);

    registers->CMP = value;
}


uint32_t LPTimer_Channel::getCapture()
{
    auto registers = LPTimer_Registers::get(timerId);

    return registers->CMP;
}


void LPTimer_Channel::setCallback(CallbackFunc func)
{
    auto registers = LPTimer_Registers::get(timerId);

    // Disable timer
    registers->CR = bitReset(registers->CR, LPTimer_Registers::CR::ENABLE);

    if (func != nullptr) {

        switch (channelId) {
            case CH1:
                ch1Callbacks[timerId] = func;
                registers->IER |= (1 << LPTimer_Registers::IER::CMPMIE);
                break;
        }

        auto& nvic = NVIC::get();
        nvic.enableIrq(getIRQNumber(timerId));
    } else {
        switch (channelId) {
            case CH1:
                ch1Callbacks[timerId] = nullptr;
                registers->IER &= ~(1 << LPTimer_Registers::IER::CMPMIE);
                break;
        }
    }

    // Enable timer
    registers->CR = bitSet(registers->CR, LPTimer_Registers::CR::ENABLE);
}


// ============================================================================
// Protected members
// ============================================================================


LPTimer_Channel::CallbackFunc LPTimer_Channel::ch1Callbacks[2];


}   // namespace mcu
