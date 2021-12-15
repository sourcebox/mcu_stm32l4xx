/**
 * @file        UART_Receiver_INT.h
 *
 * Interrupt based UART receiver for STM32L4xx devices
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


class UART_Receiver_INT
{
    public:
        /**
         * Constructor
         */
        UART_Receiver_INT(UART& uart) : uart(uart) {}

        /**
         * Init
         *
         * @param rxBufferLength    Length of receive buffer in bytes
         */
        void init(int rxBufferLength);

        /**
         * Shutdown
         */
        void deinit();

        /**
         * Return length of received data
         *
         * @return              Length of received data in bytes
         */
        int getReceivedLength();

        /**
         * Return one byte from receive buffer
         *
         * @return              Received byte
         */
        uint8_t receive();

        /**
         * Receive multiple bytes into buffer
         *
         * @param buffer        Buffer to be filled with data
         * @param size          Size of buffer
         */
        void receive(uint8_t buffer[], int size);

        /**
         * Clear receive buffer
         */
        void clearBuffer();

    protected:
        /**
         * Allocate RX buffer on heap
         *
         * @param rxBufferLength    Length of receive buffer in bytes
         */
        void allocateBuffer(int rxBufferLength);

        /**
         * Deallocate RX buffer on heap
         */
        void deallocateBuffer();

        /**
         * Receive callback called from IRQ
         */
        void receiveCallback();

       /**
         * Reference to UART peripheral
         */
        UART& uart;

        /**
         * Receive buffer
         */
        struct RxBuffer
        {
            uint8_t* data = nullptr;
            int length;
            int readIndex = 0;
            volatile int writeIndex = 0;
            volatile int count = 0;
        };

        RxBuffer rxBuffer;
};


}   // namespace mcu
