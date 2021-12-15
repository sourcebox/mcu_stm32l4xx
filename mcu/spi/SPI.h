/**
 * @file        SPI.h
 *
 * Driver for SPI peripherals on STM32L4xx
 *
 * @author:     Oliver Rockstedt <info@sourcebox.de>
 * @license     MIT
 */


#pragma once


// Local includes
#include "SPI_Base.h"
#include "SPI_Registers.h"

// This component
#include "../gpio/Pin.h"

// System libraries
#include <cstdint>


namespace mcu {


class SPI : public SPI_Base
{
    public:
        enum class Mode
        {
            MASTER,
            SLAVE
        };

        enum class Prescaler
        {
            DIV_2,
            DIV_4,
            DIV_8,
            DIV_16,
            DIV_32,
            DIV_64,
            DIV_128,
            DIV_256,
        };

        enum class ClockPolarity
        {
            LOW,
            HIGH
        };

        enum class ClockPhase
        {
            EDGE_1,
            EDGE_2
        };

        enum class FrameFormat
        {
            MSB_FIRST,
            LSB_FIRST
        };

        /**
         * Callback function type
         */
        typedef void(*CallbackFunc)(SPI*, void*);

        /**
         * Configuration settings
         */
        struct Config
        {
            Pin::Id clkPinId = Pin::NONE;       // GPIO pin id of CLK pin
            Pin::Id mosiPinId = Pin::NONE;      // GPIO pin id of MOSI pin
            Pin::Id misoPinId = Pin::NONE;      // GPIO pin id of MISO pin
            Pin::Id nssPinId = Pin::NONE;       // GPIO pin id of NSS pin
            Mode mode = Mode::MASTER;
            Prescaler prescaler = Prescaler::DIV_32;
            ClockPolarity clockPolarity = ClockPolarity::LOW;
            ClockPhase clockPhase = ClockPhase::EDGE_1;
            uint8_t dataSize = 8;                   // Data size in bits 4..16
            FrameFormat bitOrder = FrameFormat::MSB_FIRST;
            CallbackFunc transmitCallback = nullptr;
            CallbackFunc receiveCallback = nullptr;
        };

        /**
         * Return reference to peripheral
         *
         * @param id            Peripheral id
         * @return              Reference to peripheral
         */
        static SPI& get(Id id)
        {
            switch (id) {
                case Id::SPI1:
                    return spi1;
                case Id::SPI2:
                    return spi2;
                case Id::SPI3:
                    return spi3;
            }

            return spi1;
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
         * Setup alternate pin functions
         *
         * @param clkPinId      Id of CLK pin
         * @param mosiPinId     Id of MOSI pin
         * @param misoPinId     Id of MISO pin
         * @param nssPinId      Id of NSS pin
         */
        void initPins(Pin::Id clkPinId, Pin::Id mosiPinId, Pin::Id misoPinId,
                      Pin::Id nssPinId);

        /**
         * Release pin functions
         *
         * @param clkPinId      Id of CLK pin
         * @param mosiPinId     Id of MOSI pin
         * @param misoPinId     Id of MISO pin
         * @param nssPinId      Id of NSS pin
         */
        void deinitPins(Pin::Id clkPinId, Pin::Id mosiPinId, Pin::Id misoPinId,
                        Pin::Id nssPinId);

        /**
         * Set mode
         *
         * @param mode          Mode enum setting
         */
        void setMode(Mode mode);

        /**
         * Set baudrate prescaler
         *
         * @param prescaler     Prescaler enum setting
         */
        void setPrescaler(Prescaler prescaler);

        /**
         * Set clock polarity
         *
         * @param polarity      ClockPolarity enum setting
         */
        void setClockPolarity(ClockPolarity polarity);

        /**
         * Set clock phase
         *
         * @param phase         ClockPhase enum setting
         */
        void setClockPhase(ClockPhase phase);

        /**
         * Set data size
         *
         * @param size          Data size in bits 4..16
         */
        void setDataSize(uint8_t size);

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
         * Transmit array of bytes, blocking
         *
         * @param buffer        Buffer containing data
         * @param length        Size of data in buffer in bytes
         */
        void transmit(uint8_t buffer[], int length);

        /**
         * Return if data was received
         *
         * @return              Received data state
         */
        bool hasDataReceived();

        /**
         * Receive multiple bytes into buffer, blocking
         *
         * @param buffer        Buffer to be filled with data
         * @param length        Size of buffer in bytes
         */
        void receive(uint8_t buffer[], int length);

        /**
         * Enable peripheral
         */
        void enable();

        /**
         * Disable peripheral
         */
        void disable();

        /**
         * Return transmitter empty state
         *
         * @return              State of transmitter empty flag
         */
        bool hasTransmitterEmpty();

        /**
         * Return busy state
         *
         * @return              State of busy flag
         */
        bool isBusy();

        /**
         * Wait until transmit register empty
         */
        void waitUntilTransmitterEmpty();

        /**
         * Wait until receive register not empty
         */
        void waitUntilDataReceived();

        /**
         * Wait until all data frame are processed
         */
        void waitWhileBusy();

        /**
         * Flush all data from RX FIFO
         */
        void flushReceiveFIFO();

        /**
         * Enable/disable DMA request when transmit register is empty
         *
         * @param state         DMA request enable state
         */
        void setTransmitDMARequest(bool state);

        /**
         * Enable/disable DMA request when receive register is not empty
         *
         * @param state         DMA request enable state
         */
        void setReceiveDMARequest(bool state);

        /**
         * Return if peripheral is configured as master
         */
        bool isMaster();

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
            return SPI_Registers::get(id);
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
        SPI(Id id) : id(id) {}
        SPI(const SPI&) = delete;
        SPI& operator = (const SPI&) = delete;
        SPI& operator = (SPI&&) = delete;

        /**
         * Enable clock
         */
        void enableClock();

        /**
         * Disable clock
         */
        void disableClock();

        /**
         * Transmit single byte
         *
         * @param byte          Data byte to send
         */
        void transmitByte(uint8_t data);

        /**
         * Return last received byte
         *
         * @return              Received data byte
         */
        uint8_t receiveByte();

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
        static SPI spi1;
        static SPI spi2;
        static SPI spi3;
};


}   // namespace mcu
