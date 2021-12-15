/**
 * @file        UART_Transmitter_INT.h
 *
 * Interrupt based UART transmitter for STM32L4xx devices
 *
 * @author:     Oliver Rockstedt <info@sourcebox.de>
 * @license     MIT
 */


#pragma once

// Local includes
#include "UART.h"

// System libraries
#include <cstdint>


namespace mcu {


class UART_Transmitter_INT
{
    public:
        /**
         * Constructor
         */
        UART_Transmitter_INT(UART& uart) : uart(uart) {}

        /**
         * Init
         *
         * @param txBufferLength    Length of transmit buffer in bytes
         */
        void init(int txBufferLength);

        /**
         * Shutdown
         */
        void deinit();

        /**
         * Transmit single byte via buffer
         *
         * @param byte          Byte to send
         */
        void transmit(uint8_t byte);

        /**
         * Transmit array of bytes via buffer
         *
         * @param buffer        Buffer containing data
         * @param size          Size of data in buffer
         */
        void transmit(uint8_t buffer[], int size);

        /**
         * Flush transmit buffer
         */
        void flushBuffer();

    protected:
        /**
         * No copy allowed
         */
        UART_Transmitter_INT(const UART_Transmitter_INT&) = delete;
        UART_Transmitter_INT& operator = (const UART_Transmitter_INT&) = delete;
        UART_Transmitter_INT& operator = (UART_Transmitter_INT&&) = delete;

        /**
         * Allocate TX buffer on heap
         *
         * @param txBufferLength    Length of transmit buffer in bytes
         */
        void allocateBuffer(int txBufferLength);

        /**
         * Deallocate TX buffer on heap
         */
        void deallocateBuffer();

        /**
         * Transmit callback called from IRQ
         */
        void transmitCallback();

        /**
         * Reference to UART peripheral
         */
        UART& uart;

        /**
         * Transmit buffer
         */
        struct TxBuffer
        {
            uint8_t* data = nullptr;
            int length;
            volatile int readIndex = 0;
            int writeIndex = 0;
            volatile int count = 0;
        };

        TxBuffer txBuffer;
};


}   // namespace mcu
