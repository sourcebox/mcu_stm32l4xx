/**
 * @file        SPI.cpp
 *
 * Driver for SPI peripherals on STM32L4xx
 *
 * @author      Oliver Rockstedt <info@sourcebox.de>
 * @license     MIT
 */


// Corresponding header
#include "SPI.h"

// This component
#include "../core/NVIC.h"
#include "../rcc/RCC_Registers.h"
#include "../utility/register.h"
#include "../utility/bit_manipulation.h"

// System libraries
#include <cstdlib>
#include <cstring>


namespace mcu {


// ============================================================================
// Public members
// ============================================================================


void SPI::init()
{
    enableClock();
}


void SPI::init(Config& config)
{
    init();

    initPins(config.clkPinId, config.mosiPinId, config.misoPinId, config.nssPinId);

    disable();

    setPrescaler(config.prescaler);
    setClockPolarity(config.clockPolarity);
    setClockPhase(config.clockPhase);
    setMode(config.mode);
    setDataSize(config.dataSize);
    setTransmitCallback(config.transmitCallback);
    setReceiveCallback(config.receiveCallback);

    enable();
};


void SPI::deinit()
{
    disableClock();
}


void SPI::initPins(Pin::Id clkPinId, Pin::Id mosiPinId, Pin::Id misoPinId,
                   Pin::Id nssPinId)
{
    Pin::AF af;

    switch (id) {
        case SPI1:
        case SPI2:
            af = Pin::AF::AF5;
            break;
        case SPI3:
            af = Pin::AF::AF6;
            break;
        default:
            break;
    }

    // CLK pin
    if (clkPinId != Pin::NONE) {
        auto pin = Pin::get(clkPinId);
        pin.setMode(Pin::Mode::AF);
        pin.setOutputSpeed(Pin::OutputSpeed::MEDIUM);
        pin.setAlternateFunction(af);
    }

    // MOSI pin
    if (mosiPinId != Pin::NONE) {
        auto pin = Pin::get(mosiPinId);
        pin.setMode(Pin::Mode::AF);
        pin.setOutputSpeed(Pin::OutputSpeed::MEDIUM);
        pin.setAlternateFunction(af);
    }

    // MISO pin
    if (misoPinId != Pin::NONE) {
        auto pin = Pin::get(misoPinId);
        pin.setMode(Pin::Mode::AF);
        pin.setAlternateFunction(af);
    }

    // NSS pin
    if (nssPinId != Pin::NONE) {
        auto pin = Pin::get(nssPinId);
        pin.setMode(Pin::Mode::AF);
        pin.setAlternateFunction(af);
    }
};


void SPI::deinitPins(Pin::Id clkPinId, Pin::Id mosiPinId, Pin::Id misoPinId,
                     Pin::Id nssPinId)
{
    // CLK pin
    if (clkPinId != Pin::NONE) {
        auto pin = Pin::get(clkPinId);
        pin.setMode(Pin::Mode::INPUT);
        pin.setAlternateFunction(Pin::AF::AF0);
    }

    // MOSI pin
    if (mosiPinId != Pin::NONE) {
        auto pin = Pin::get(mosiPinId);
        pin.setMode(Pin::Mode::INPUT);
        pin.setAlternateFunction(Pin::AF::AF0);
    }

    // MISO pin
    if (misoPinId != Pin::NONE) {
        auto pin = Pin::get(misoPinId);
        pin.setMode(Pin::Mode::INPUT);
        pin.setAlternateFunction(Pin::AF::AF0);
    }

    // NSS pin
    if (nssPinId != Pin::NONE) {
        auto pin = Pin::get(nssPinId);
        pin.setMode(Pin::Mode::INPUT);
        pin.setAlternateFunction(Pin::AF::AF0);
    }
}


void SPI::setMode(Mode mode)
{
    auto registers = getRegisters();

    if (mode == Mode::MASTER) {
        registers->CR1 = bitSet(registers->CR1, SPI_Registers::CR1::MSTR);
        registers->CR1 = bitSet(registers->CR1, SPI_Registers::CR1::SSM);
        registers->CR1 = bitSet(registers->CR1, SPI_Registers::CR1::SSI);
    } else {
        registers->CR1 = bitReset(registers->CR1, SPI_Registers::CR1::MSTR);
    }
}


void SPI::setPrescaler(Prescaler prescaler)
{
    auto registers = getRegisters();

    registers->CR1 = bitsReplace(registers->CR1, (int)prescaler,
            3, SPI_Registers::CR1::BR_0);
}


void SPI::setClockPolarity(ClockPolarity polarity)
{
    auto registers = getRegisters();

    if (polarity == ClockPolarity::HIGH) {
        registers->CR1 = bitSet(registers->CR1, SPI_Registers::CR1::CPOL);
    } else {
        registers->CR1 = bitReset(registers->CR1, SPI_Registers::CR1::CPOL);
    }
}


void SPI::setClockPhase(ClockPhase phase)
{
    auto registers = getRegisters();

    if (phase == ClockPhase::EDGE_2) {
        registers->CR1 = bitSet(registers->CR1, SPI_Registers::CR1::CPHA);
    } else {
        registers->CR1 = bitReset(registers->CR1, SPI_Registers::CR1::CPHA);
    }
}


void SPI::setDataSize(uint8_t size)
{
    auto registers = getRegisters();

    registers->CR2 = bitsReplace(registers->CR2, size - 1,
            4, SPI_Registers::CR2::DS_0);

    if (size > 8) {
        registers->CR2 = bitReset(registers->CR2, SPI_Registers::CR2::FRXTH);
    } else {
        registers->CR2 = bitSet(registers->CR2, SPI_Registers::CR2::FRXTH);
    }
}


void SPI::setTransmitCallback(CallbackFunc func, void* context)
{
    transmitCallback = func;
    transmitCallbackContext = context;

    auto& nvic = NVIC::get();
    nvic.enableIrq(getIRQNumber(id));
}


void SPI::setReceiveCallback(CallbackFunc func, void* context)
{
    receiveCallback = func;
    receiveCallbackContext = context;

    auto& nvic = NVIC::get();
    nvic.enableIrq(getIRQNumber(id));
}


void SPI::transmit(uint8_t buffer[], int length)
{
    for (auto i = 0; i < length; i++) {
        transmitByte(buffer[i]);
    }

    waitWhileBusy();
}


bool SPI::hasDataReceived()
{
    auto registers = getRegisters();

    return bitValue(registers->SR, SPI_Registers::SR::RXNE);
}


void SPI::receive(uint8_t buffer[], int length)
{
    flushReceiveFIFO();

    for (auto i = 0; i < length; i++) {
        buffer[i] = receiveByte();
    }
}


void SPI::enable()
{
    auto registers = getRegisters();
    registers->CR1 = bitSet(registers->CR1, SPI_Registers::CR1::SPE);
}


void SPI::disable()
{
    auto registers = getRegisters();

    while (bitsValue(registers->SR, 2, SPI_Registers::SR::FTLVL_0) != 0b00) {
        // Wait until no more data to transmit
    }

    waitWhileBusy();

    registers->CR1 = bitReset(registers->CR1, SPI_Registers::CR1::SPE);

    while (bitsValue(registers->SR, 2, SPI_Registers::SR::FRLVL_0) != 0b00) {
        // Wait until all received data is read
    }
}


bool SPI::hasTransmitterEmpty()
{
    auto registers = getRegisters();

    return bitValue(registers->SR, SPI_Registers::SR::TXE);
}


bool SPI::isBusy()
{
    auto registers = getRegisters();

    return bitValue(registers->SR, SPI_Registers::SR::BSY);
}


void SPI::waitUntilTransmitterEmpty()
{
    while (!hasTransmitterEmpty()) {
    }
}


void SPI::waitUntilDataReceived()
{
    while (!hasDataReceived()) {
    }
}


void SPI::waitWhileBusy()
{
    while (isBusy()) {
    }
}


void SPI::flushReceiveFIFO()
{
    auto registers = getRegisters();

    while (bitsValue(registers->SR, 2, SPI_Registers::SR::FRLVL_0) != 0) {
        volatile uint8_t __attribute__((unused))
        rxData = *((Register8*)&registers->DR);
    }
}


void SPI::setTransmitDMARequest(bool state)
{
    auto registers = getRegisters();

    if (state) {
        registers->CR2 = bitSet(registers->CR2, SPI_Registers::CR2::TXDMAEN);
    } else {
        registers->CR2 = bitReset(registers->CR2, SPI_Registers::CR2::TXDMAEN);
    }
}


void SPI::setReceiveDMARequest(bool state)
{
    auto registers = getRegisters();

    if (state) {
        registers->CR2 = bitSet(registers->CR2, SPI_Registers::CR2::RXDMAEN);
    } else {
        registers->CR2 = bitReset(registers->CR2, SPI_Registers::CR2::RXDMAEN);
    }
}


bool SPI::isMaster()
{
    auto registers = getRegisters();

    return bitValue(registers->CR1, SPI_Registers::CR1::MSTR);
}


void SPI::setTransmitInterrupt(bool state)
{
    auto registers = getRegisters();

    if (state) {
        registers->CR2 = bitSet(registers->CR2, SPI_Registers::CR2::TXEIE);
    } else {
        registers->CR2 = bitReset(registers->CR2, SPI_Registers::CR2::TXEIE);
    }
}


void SPI::setReceiveInterrupt(bool state)
{
    auto registers = getRegisters();

    if (state) {
        registers->CR2 = bitSet(registers->CR2, SPI_Registers::CR2::RXNEIE);
    } else {
        registers->CR2 = bitReset(registers->CR2, SPI_Registers::CR2::RXNEIE);
    }
}


void SPI::irq()
{
    auto registers = getRegisters();

    if (bitValue(registers->SR, SPI_Registers::SR::TXE)
            && transmitCallback != nullptr) {
        transmitCallback(this, transmitCallbackContext);
    }

    if (bitValue(registers->SR, SPI_Registers::SR::RXNE)
            && receiveCallback != nullptr) {
        receiveCallback(this, receiveCallbackContext);
    }
}


// ============================================================================
// Protected members
// ============================================================================


void SPI::enableClock()
{
    auto rccRegisters = RCC_Registers::get();

    switch (id) {
        case SPI1:
            rccRegisters->APB2ENR = bitSet(rccRegisters->APB2ENR,
                    RCC_Registers::APB2ENR::SPI1EN);
            break;
        case SPI2:
            rccRegisters->APB1ENR1 = bitSet(rccRegisters->APB1ENR1,
                    RCC_Registers::APB1ENR1::SPI2EN);
            break;
        case SPI3:
            rccRegisters->APB1ENR1 = bitSet(rccRegisters->APB1ENR1,
                    RCC_Registers::APB1ENR1::SPI3EN);
            break;
    }
}


void SPI::disableClock()
{
    auto rccRegisters = RCC_Registers::get();

    switch (id) {
        case SPI1:
            rccRegisters->APB2ENR = bitReset(rccRegisters->APB2ENR,
                    RCC_Registers::APB2ENR::SPI1EN);
            break;
        case SPI2:
            rccRegisters->APB1ENR1 = bitReset(rccRegisters->APB1ENR1,
                    RCC_Registers::APB1ENR1::SPI2EN);
            break;
        case SPI3:
            rccRegisters->APB1ENR1 = bitReset(rccRegisters->APB1ENR1,
                    RCC_Registers::APB1ENR1::SPI3EN);
            break;
    }
}


void SPI::transmitByte(uint8_t data)
{
    waitUntilTransmitterEmpty();

    auto registers = getRegisters();
    *((Register8*)&registers->DR) = data;
}


uint8_t SPI::receiveByte()
{
    auto registers = getRegisters();

    if (isMaster()) {
        transmitByte(0);
    }

    waitUntilDataReceived();

    return *((Register8*)&registers->DR);
}


SPI SPI::spi1 = SPI(SPI::SPI1);
SPI SPI::spi2 = SPI(SPI::SPI2);
SPI SPI::spi3 = SPI(SPI::SPI3);


}   // namespace mcu
