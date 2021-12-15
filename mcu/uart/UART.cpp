/**
 * @file        UART.cpp
 *
 * Driver for UART/USART peripherals on STM32L4xx
 *
 * @author      Oliver Rockstedt <info@sourcebox.de>
 * @license     MIT
 */


// Corresponding header
#include "UART.h"

// This component
#include "../core/NVIC.h"
#include "../rcc/RCC.h"
#include "../utility/bit_manipulation.h"

// System libraries
#include <cstdlib>
#include <cstring>


namespace mcu {


// ============================================================================
// Public members
// ============================================================================


void UART::init()
{
    enableClock();
}


void UART::init(Config& config)
{
    init();

    initPins(config.txPinId, config.rxPinId);

    disable();

    auto registers = getRegisters();

    // Enable transmitter
    if (config.txPinId != Pin::NONE) {
        registers->CR1 |= (1 << UART_Registers::CR1::TE);
    }

    // Enable receiver
    if (config.rxPinId != Pin::NONE) {
        registers->CR1 |= (1 << UART_Registers::CR1::RE);
    }

    setBaudrate(config.baudrate);
    setParity(config.parity);
    setStopBits(config.stopBits);

    setInterruptPriority(config.irqPriority);
    setTransmitCallback(config.transmitCallback);
    setReceiveCallback(config.receiveCallback);

    enable();
}


void UART::deinit()
{
    NVIC::get().disableIrq(getIRQNumber(id));

    disable();

    auto registers = getRegisters();

    // Reset registers
    registers->CR1 = 0;
    registers->CR2 = 0;
    registers->CR3 = 0;

    disableClock();
}


void UART::initPins(Pin::Id txPinId, Pin::Id rxPinId)
{
    Pin::AF af;

    switch (id) {
        case USART1:
        case USART2:
        case USART3:
            af = Pin::AF::AF7;
            break;
        case UART4:
        case LPUART1:
            af = Pin::AF::AF8;
            break;
        default:
            break;
    }

    // TX pin
    if (txPinId != Pin::NONE) {
        auto txPin = Pin::get(txPinId);
        txPin.setMode(Pin::Mode::AF);
        txPin.setAlternateFunction(af);
    }

    // RX pin
    if (rxPinId != Pin::NONE) {
        auto rxPin = Pin::get(rxPinId);
        rxPin.setPullMode(Pin::PullMode::PULLUP);
        rxPin.setMode(Pin::Mode::AF);
        if (rxPinId == Pin::PA15) {
            af = Pin::AF::AF3;
        }
        rxPin.setAlternateFunction(af);
    }
}


void UART::deinitPins(Pin::Id txPinId, Pin::Id rxPinId)
{
    if (txPinId != Pin::NONE) {
        auto txPin = Pin::get(txPinId);
        txPin.setMode(Pin::Mode::INPUT);
        txPin.setAlternateFunction(Pin::AF::AF0);
    }

    if (rxPinId != Pin::NONE) {
        auto rxPin = Pin::get(rxPinId);
        rxPin.setPullMode(Pin::PullMode::NONE);
        rxPin.setMode(Pin::Mode::INPUT);
        rxPin.setAlternateFunction(Pin::AF::AF0);
    }
}


void UART::setBaudrate(int baudrate)
{
    int clockFreq;

    switch (id) {
        case USART1:
            clockFreq = RCC::get().getPCLK2Freq();
            break;
        default:
            clockFreq = RCC::get().getPCLK1Freq();
            break;
    }

    auto registers = getRegisters();

    if (id == LPUART1) {
        registers->BRR = (uint64_t)clockFreq * 256 / baudrate;
    } else {
        registers->BRR = clockFreq / baudrate;
    }
}


void UART::setParity(Parity parity)
{
    auto registers = getRegisters();

    switch (parity) {
        case Parity::NONE:
            registers->CR1 &= ~(1 << UART_Registers::CR1::PCE);
            registers->CR1 &= ~(1 << UART_Registers::CR1::PS);
            break;
        case Parity::EVEN:
            registers->CR1 |= (1 << UART_Registers::CR1::PCE);
            registers->CR1 &= ~(1 << UART_Registers::CR1::PS);
            break;
        case Parity::ODD:
            registers->CR1 |= (1 << UART_Registers::CR1::PCE);
            registers->CR1 |= (1 << UART_Registers::CR1::PS);
            break;
    }

    // Word length depends on parity
    if (parity != Parity::NONE) {
        registers->CR1 |= (1 << UART_Registers::CR1::M0);
        registers->CR1 &= ~(1 << UART_Registers::CR1::M1);
    } else {
        registers->CR1 &= ~(1 << UART_Registers::CR1::M0);
        registers->CR1 &= ~(1 << UART_Registers::CR1::M1);
    }
}


void UART::setStopBits(StopBits stopBits)
{
    auto registers = getRegisters();

    switch (stopBits) {
        case StopBits::BITS_1:
            registers->CR2 &= ~(1 << UART_Registers::CR2::STOP_0);
            registers->CR2 &= ~(1 << UART_Registers::CR2::STOP_1);
            break;
        case StopBits::BITS_2:
            registers->CR2 &= ~(1 << UART_Registers::CR2::STOP_0);
            registers->CR2 |= (1 << UART_Registers::CR2::STOP_1);
            break;
        case StopBits::BITS_1_5:
            registers->CR2 |= (1 << UART_Registers::CR2::STOP_0);
            registers->CR2 |= (1 << UART_Registers::CR2::STOP_1);
            break;
    }
}


void UART::setInterruptPriority(int priority)
{
    auto& nvic = NVIC::get();
    auto irqNum = getIRQNumber(id);
    nvic.setPriority(irqNum, priority);
}


void UART::setTransmitCallback(CallbackFunc func, void* context)
{
    transmitCallback = func;
    transmitCallbackContext = context;

    auto& nvic = NVIC::get();
    nvic.enableIrq(getIRQNumber(id));
}


void UART::setReceiveCallback(CallbackFunc func, void* context)
{
    receiveCallback = func;
    receiveCallbackContext = context;

    auto& nvic = NVIC::get();
    nvic.enableIrq(getIRQNumber(id));
}


void UART::transmit(uint8_t byte)
{
    waitUntilTransmitterEmpty();

    auto registers = getRegisters();
    registers->TDR = (uint16_t)byte & 0xFF;
}


void UART::transmit(uint8_t buffer[], int size)
{
    for (auto i = 0; i < size; i++) {
        transmit(buffer[i]);
    }
}


bool UART::hasDataReceived()
{
    auto registers = getRegisters();

    return bitValue(registers->ISR, UART_Registers::ISR::RXNE);
}


uint8_t UART::receive()
{
    auto registers = getRegisters();

    return registers->RDR & 0xFF;
}


void UART::enable()
{
    auto registers = getRegisters();
    registers->CR1 |= (1 << UART_Registers::CR1::UE);
}


void UART::disable()
{
    auto registers = getRegisters();
    registers->CR1 &= ~(1 << UART_Registers::CR1::UE);
}


void UART::waitUntilTransmitterEmpty()
{
    auto registers = getRegisters();

    while (!bitValue(registers->ISR, UART_Registers::ISR::TXE)) {
    }
}


void UART::waitUntilDataReceived()
{
    while (!hasDataReceived()) {
    }
}


void UART::setTransmitInterrupt(bool state)
{
    auto registers = getRegisters();

    if (state) {
        registers->CR1 = bitSet(registers->CR1, UART_Registers::CR1::TXEIE);
    } else {
        registers->CR1 = bitReset(registers->CR1, UART_Registers::CR1::TXEIE);
    }
}


void UART::setReceiveInterrupt(bool state)
{
    auto registers = getRegisters();

    if (state) {
        registers->CR1 = bitSet(registers->CR1, UART_Registers::CR1::RXNEIE);
    } else {
        registers->CR1 = bitReset(registers->CR1, UART_Registers::CR1::RXNEIE);
    }
}


void UART::irq()
{
    auto registers = getRegisters();

    if (bitValue(registers->ISR, UART_Registers::ISR::TXE)
            && transmitCallback != nullptr) {
        transmitCallback(this, transmitCallbackContext);
    }

    if (bitValue(registers->ISR, UART_Registers::ISR::RXNE)
            && receiveCallback != nullptr) {
        receiveCallback(this, receiveCallbackContext);
    }

    // Overrun error
    if (bitValue(registers->ISR, UART_Registers::ISR::ORE)) {
        registers->ICR |= (1 << UART_Registers::ICR::ORECF);
    }
}


// ============================================================================
// Protected members
// ============================================================================


void UART::enableClock()
{
    auto rccRegisters = RCC_Registers::get();

    switch (id) {
        case USART1:
            rccRegisters->APB2ENR |= (1 << RCC_Registers::APB2ENR::USART1EN);
            break;
        case USART2:
            rccRegisters->APB1ENR1 |= (1 << RCC_Registers::APB1ENR1::USART2EN);
            break;
        case USART3:
            rccRegisters->APB1ENR1 |= (1 << RCC_Registers::APB1ENR1::USART3EN);
            break;
        case UART4:
            rccRegisters->APB1ENR1 |= (1 << RCC_Registers::APB1ENR1::UART4EN);
            break;
        case LPUART1:
            rccRegisters->APB1ENR2 |= (1 << RCC_Registers::APB1ENR2::LPUART1EN);
            break;
        default:
            break;
    }
}


void UART::disableClock()
{
    auto rccRegisters = RCC_Registers::get();

    switch (id) {
        case USART1:
            rccRegisters->APB2ENR &= ~(1 << RCC_Registers::APB2ENR::USART1EN);
            break;
        case USART2:
            rccRegisters->APB1ENR1 &= ~(1 << RCC_Registers::APB1ENR1::USART2EN);
            break;
        case USART3:
            rccRegisters->APB1ENR1 &= ~(1 << RCC_Registers::APB1ENR1::USART3EN);
            break;
        case UART4:
            rccRegisters->APB1ENR1 &= ~(1 << RCC_Registers::APB1ENR1::UART4EN);
            break;
        case LPUART1:
            rccRegisters->APB1ENR2 &= ~(1 << RCC_Registers::APB1ENR2::LPUART1EN);
            break;
        default:
            break;
    }
}


UART UART::usart1 = UART(UART::USART1);
UART UART::usart2 = UART(UART::USART2);
UART UART::usart3 = UART(UART::USART3);
UART UART::uart4 = UART(UART::UART4);
UART UART::lpuart1 = UART(UART::LPUART1);


}   // namespace mcu
