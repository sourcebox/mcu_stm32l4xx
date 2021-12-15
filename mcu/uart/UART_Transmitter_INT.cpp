/**
 * @file        UART_Transmitter_INT.cpp
 *
 * Interrupt based UART transmitter for STM32L4xx devices
 *
 * @author:     Oliver Rockstedt <info@sourcebox.de>
 * @license     MIT
 */


// Corresponding header
#include "UART_Transmitter_INT.h"


namespace mcu {


// ============================================================================
// Public members
// ============================================================================


void UART_Transmitter_INT::init(int txBufferLength)
{
    allocateBuffer(txBufferLength);

    uart.setTransmitCallback([](UART* uart, void* context) {
        ((UART_Transmitter_INT*)context)->transmitCallback();
    }, this);
}


void UART_Transmitter_INT::deinit()
{
    flushBuffer();
    uart.setTransmitCallback(nullptr);
    deallocateBuffer();
}


void UART_Transmitter_INT::transmit(uint8_t byte)
{
    if (txBuffer.data == nullptr) {
        return;
    }

    disableInterrupts();

    txBuffer.data[txBuffer.writeIndex] = byte;
    txBuffer.count++;
    txBuffer.writeIndex++;

    if (txBuffer.writeIndex >= txBuffer.length) {
        txBuffer.writeIndex = 0;
    }

    enableInterrupts();

    uart.setTransmitInterrupt(true);
}


void UART_Transmitter_INT::transmit(uint8_t buffer[], int size)
{
    if (txBuffer.data == nullptr) {
        return;
    }

    for (auto i = 0; i < size; i++) {
        disableInterrupts();

        txBuffer.data[txBuffer.writeIndex] = buffer[i];
        txBuffer.count++;
        txBuffer.writeIndex++;

        if (txBuffer.writeIndex >= txBuffer.length) {
            txBuffer.writeIndex = 0;
        }

        enableInterrupts();
    }

    uart.setTransmitInterrupt(true);
}


void UART_Transmitter_INT::flushBuffer()
{
    while (txBuffer.readIndex != txBuffer.writeIndex) {
        // Wait until last byte was sent
    }
}


// ============================================================================
// Protected members
// ============================================================================


void UART_Transmitter_INT::allocateBuffer(int txBufferLength)
{
    deallocateBuffer();

    txBuffer.data = new uint8_t[txBufferLength];
    txBuffer.length = txBufferLength;
    txBuffer.count = 0;
}


void UART_Transmitter_INT::deallocateBuffer()
{
    if (txBuffer.data != nullptr) {
        delete[] txBuffer.data;
    }

    txBuffer.length = 0;
    txBuffer.readIndex = 0;
    txBuffer.writeIndex = 0;
    txBuffer.count = 0;
}


void UART_Transmitter_INT::transmitCallback()
{
    auto registers = uart.getRegisters();

    if (txBuffer.count > 0) {
        registers->TDR = (uint16_t)txBuffer.data[txBuffer.readIndex] & 0xFF;
        txBuffer.count--;
        txBuffer.readIndex++;

        if (txBuffer.readIndex >= txBuffer.length) {
            txBuffer.readIndex = 0;
        }

    } else {
        uart.setTransmitInterrupt(false);
    }
}


}   // namespace mcu
