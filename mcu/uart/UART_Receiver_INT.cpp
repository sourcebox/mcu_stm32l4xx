/**
 * @file        UART_Receiver_INT.h
 *
 * Interrupt based UART receiver for STM32L4xx devices
 *
 * @author:     Oliver Rockstedt <info@sourcebox.de>
 * @license     MIT
 */


// Corresponding header
#include "UART_Receiver_INT.h"


namespace mcu {


// ============================================================================
// Public members
// ============================================================================


void UART_Receiver_INT::init(int rxBufferLength)
{
    allocateBuffer(rxBufferLength);

    uart.setReceiveCallback([](UART* uart, void* context) {
        ((UART_Receiver_INT*)context)->receiveCallback();
    }, this);

    uart.setReceiveInterrupt(true);
}


void UART_Receiver_INT::deinit()
{
    deallocateBuffer();
}


int UART_Receiver_INT::getReceivedLength()
{
    return rxBuffer.count;
}


uint8_t UART_Receiver_INT::receive()
{
    while (rxBuffer.count == 0) {
        // Wait until data is received
    }

    disableInterrupts();

    uint8_t value = rxBuffer.data[rxBuffer.readIndex];
    rxBuffer.count--;
    rxBuffer.readIndex++;

    if (rxBuffer.readIndex >= rxBuffer.length) {
        rxBuffer.readIndex = 0;
    }

    enableInterrupts();

    return value;
}


void UART_Receiver_INT::receive(uint8_t buffer[], int size)
{
    int index = 0;

    while (index < size) {
        buffer[index++] = receive();
    }
}


void UART_Receiver_INT::clearBuffer()
{
    disableInterrupts();
    rxBuffer.readIndex = 0;
    rxBuffer.writeIndex = 0;
    rxBuffer.count = 0;
    enableInterrupts();
}


// ============================================================================
// Protected members
// ============================================================================


void UART_Receiver_INT::allocateBuffer(int rxBufferLength)
{
    deallocateBuffer();

    rxBuffer.data = new uint8_t[rxBufferLength];
    rxBuffer.length = rxBufferLength;
    rxBuffer.count = 0;
}


void UART_Receiver_INT::deallocateBuffer()
{
    if (rxBuffer.data != nullptr) {
        delete[] rxBuffer.data;
    }

    rxBuffer.length = 0;
    rxBuffer.readIndex = 0;
    rxBuffer.writeIndex = 0;
    rxBuffer.count = 0;
}


void UART_Receiver_INT::receiveCallback()
{
    auto registers = uart.getRegisters();

    uint8_t value = registers->RDR & 0xFF;

    rxBuffer.data[rxBuffer.writeIndex] = value;
    rxBuffer.count++;
    rxBuffer.writeIndex++;

    if (rxBuffer.writeIndex >= rxBuffer.length) {
        rxBuffer.writeIndex = 0;
    }
}


}   // namespace mcu
