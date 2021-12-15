/**
 * @file        UART.h
 *
 * Driver for UART/USART peripherals on STM32L4xx
 *
 * @author:     Oliver Rockstedt <info@sourcebox.de>
 * @license     MIT
 */


#pragma once


// Local includes
#include "UART_Base.h"
#include "UART_Registers.h"

// This component
#include "../gpio/Pin.h"

// System libraries
#include <cstdint>


namespace mcu {


class UART : public UART_Base
{
    public:
        enum class Parity
        {
            NONE,
            ODD,
            EVEN
        };

        enum class StopBits
        {
            BITS_1,
            BITS_2,
            BITS_1_5
        };

        /**
         * Callback function type
         */
        typedef void(*CallbackFunc)(UART*, void*);

        /**
         * Configuration settings
         */
        struct Config
        {
            Pin::Id txPinId = Pin::NONE;            // Pin id of transmit pin
            Pin::Id rxPinId = Pin::NONE;            // Pin id of receive pin
            int baudrate = 115200;                  // Baudrate
            Parity parity = Parity::NONE;           // Parity enum settings
            StopBits stopBits = StopBits::BITS_1;   // StopBits enum setting
            uint32_t irqPriority = 7;               // IRQ preemption priority
            CallbackFunc transmitCallback = nullptr;
            CallbackFunc receiveCallback = nullptr;
        };

        /**
         * Return reference to peripheral
         *
         * @param id            Peripheral id
         * @return              Reference to peripheral
         */
        static UART& get(Id id)
        {
            switch (id) {
                case Id::USART1:
                    return usart1;
                case Id::USART2:
                    return usart2;
                case Id::USART3:
                    return usart3;
                case Id::UART4:
                    return uart4;
                case Id::LPUART1:
                    return lpuart1;
            }

            return usart1;
        }

        /**
         * Base init
         */
        void init();

        /**
         * Init with config settings
         *
         * @param config        Reference to configuration struct
         */
        void init(Config& config);

        /**
         * Shutdown
         */
        void deinit();

        /**
         * Init pins with alternate function
         *
         * @param txPinId           Id of transmit pin
         * @param rxPinId           Id of receive pin
         */
        void initPins(Pin::Id txPinId, Pin::Id rxPinId);

        /**
         * Deinit pins, set mode to input
         *
         * @param txPinId           Id of transmit pin
         * @param rxPinId           Id of receive pin
         */
        void deinitPins(Pin::Id txPinId, Pin::Id rxPinId);

        /**
         * Set baudrate, peripheral must be disabled
         *
         * @param baudrate      Baudrate
         */
        void setBaudrate(int baudrate);

        /**
         * Set parity, peripheral must be disabled
         *
         * @param parity        Parity enum setting
         */
        void setParity(Parity parity);

        /**
         * Set stop bits, peripheral must be disabled
         *
         * @param stopBits      StopBits enum setting
         */
        void setStopBits(StopBits stopBits);

        /**
         * Set interrupt priority
         *
         * @param priority      Priority value 0..15
         */
        void setInterruptPriority(int priority);

        /**
         * Set transmit callback function and enable interrupts in NVIC
         *
         * @param func          Callback function or nullptr
         * @param context       Pointer to callback context
         */
        void setTransmitCallback(CallbackFunc func, void* context=nullptr);

        /**
         * Set receive callback function and enable interrupts in NVIC
         *
         * @param func          Callback function or nullptr
         * @param context       Pointer to callback context
         */
        void setReceiveCallback(CallbackFunc func, void* context=nullptr);

        /**
         * Transmit single byte
         *
         * @param byte          Byte to send
         */
        void transmit(uint8_t byte);

        /**
         * Transmit array of bytes
         *
         * @param buffer        Buffer containing data
         * @param size          Size of data in buffer
         */
        void transmit(uint8_t buffer[], int size);

        /**
         * Return if a byte was received
         *
         * @return              Received data state
         */
        bool hasDataReceived();

        /**
         * Return last received byte
         *
         * @return              Received byte
         */
        uint8_t receive();

        /**
         * Enable peripheral
         */
        void enable();

        /**
         * Disable peripheral
         */
        void disable();

        /**
         * Wait until transmit register empty
         */
        void waitUntilTransmitterEmpty();

        /**
         * Wait until receive register not empty
         */
        void waitUntilDataReceived();

        /**
         * Return id
         *
         * @return      Id constant
         */
        Id getId()
        {
            return id;
        }

        /**
         * Return pointer to registers
         *
         * @return      Pointer to registers struct
         */
        auto getRegisters()
        {
            return UART_Registers::get(id);
        }

        /**
         * Enable/disable interrupt when transmit register is empty
         *
         * @param state         Interrupt state
         */
        void setTransmitInterrupt(bool state);

        /**
         * Enable/disable interrupt when receive register is not empty
         *
         * @param state         Interrupt state
         */
        void setReceiveInterrupt(bool state);

        /**
         * Process interrupt, called from IRQ handler
         */
        void irq();

    protected:
        /**
         * Private constructors because of singleton pattern, no copy allowed
         */
        UART(Id id) : id(id) {}
        UART(const UART&) = delete;
        UART& operator = (const UART&) = delete;
        UART& operator = (UART&&) = delete;

        /**
         * Enable clock
         */
        void enableClock();

        /**
         * Disable clock
         */
        void disableClock();

        /**
         * Peripheral id
         */
        const Id id;

        /**
         * Callbacks
         */
        CallbackFunc transmitCallback = nullptr;
        CallbackFunc receiveCallback = nullptr;
        void* transmitCallbackContext = nullptr;
        void* receiveCallbackContext = nullptr;

        /**
         * Singleton instances
         */
        static UART usart1;
        static UART usart2;
        static UART usart3;
        static UART uart4;
        static UART lpuart1;
};


}   // namespace mcu
