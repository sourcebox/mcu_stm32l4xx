/**
 * @file        QUADSPI.h
 *
 * Driver for QUADSPI peripheral on STM32L4xx
 *
 * @author:     Oliver Rockstedt <info@sourcebox.de>
 * @license     MIT
 */


#pragma once


// Local includes
#include "QUADSPI_Registers.h"

// This component
#include "../gpio/Pin.h"

// System libraries
#include <cstdint>


namespace mcu {


class QUADSPI
{
    public:
        enum class FunctionalMode
        {
            INDIRECT_WRITE      = 0b00,
            INDIRECT_READ       = 0b01,
            AUTOMATIC_POLLING   = 0b10,
            MEMORY_MAPPED       = 0b11
        };

        enum class InstructionMode
        {
            NONE        = 0b00,
            ONE_LINE    = 0b01,
            TWO_LINES   = 0b10,
            FOUR_LINES  = 0b11
        };

        enum class AddressMode
        {
            NONE        = 0b00,
            ONE_LINE    = 0b01,
            TWO_LINES   = 0b10,
            FOUR_LINES  = 0b11
        };

        enum class AddressSize
        {
            BITS_8      = 0b00,
            BITS_16     = 0b01,
            BITS_24     = 0b10,
            BITS_32     = 0b11
        };

        enum class AlternateBytesMode
        {
            NONE        = 0b00,
            ONE_LINE    = 0b01,
            TWO_LINES   = 0b10,
            FOUR_LINES  = 0b11
        };

        enum class AlternateBytesSize
        {
            BITS_8      = 0b00,
            BITS_16     = 0b01,
            BITS_24     = 0b10,
            BITS_32     = 0b11
        };

        enum class DataMode
        {
            NONE        = 0b00,
            ONE_LINE    = 0b01,
            TWO_LINES   = 0b10,
            FOUR_LINES  = 0b11
        };

        enum class ClockPolarity
        {
            LOW,
            HIGH
        };

        enum class MemorySelect
        {
            FLASH_1,
            FLASH_2
        };

        enum class PollingMatchMode
        {
            AND,
            OR
        };

        /**
         * Callback function type
         */
        typedef void(*CallbackFunc)(QUADSPI*, void*);

        /**
         * Configuration settings
         */
        struct Config
        {
            Pin::Id clkPinId = Pin::NONE;       // GPIO pin id of CLK pin
            Pin::Id bk1ncsPinId = Pin::NONE;    // GPIO pin id of BK1 NCS pin
            Pin::Id bk1io0PinId = Pin::NONE;    // GPIO pin id of BK1 IO0 pin
            Pin::Id bk1io1PinId = Pin::NONE;    // GPIO pin id of BK1 IO1 pin
            Pin::Id bk1io2PinId = Pin::NONE;    // GPIO pin id of BK1 IO2 pin
            Pin::Id bk1io3PinId = Pin::NONE;    // GPIO pin id of BK1 IO3 pin
            Pin::Id bk2ncsPinId = Pin::NONE;    // GPIO pin id of BK2 NCS pin
            Pin::Id bk2io0PinId = Pin::NONE;    // GPIO pin id of BK2 IO0 pin
            Pin::Id bk2io1PinId = Pin::NONE;    // GPIO pin id of BK2 IO1 pin
            Pin::Id bk2io2PinId = Pin::NONE;    // GPIO pin id of BK2 IO2 pin
            Pin::Id bk2io3PinId = Pin::NONE;    // GPIO pin id of BK2 IO3 pin
            uint16_t prescaler = 32;
            bool sampleShift = false;
            uint8_t fifoThreshold = 1;
            uint8_t flashSize = 22;             // 4MB (2 ** 22 bits)
            uint8_t csHighTime = 1;
            ClockPolarity clockPolarity = ClockPolarity::LOW;
            PollingMatchMode pollingMatchMode = PollingMatchMode::AND;
            bool automaticPollModeStop = false;
            bool dmaEnable = false;
            CallbackFunc transferCompleteCallback = nullptr;
        };

        /**
         * Transaction configuration settings
         */
        struct TransactionConfig
        {
            FunctionalMode functionalMode = FunctionalMode::INDIRECT_WRITE;
            InstructionMode instructionMode = InstructionMode::NONE;
            uint8_t instruction = 0;
            AddressMode addressMode = AddressMode::NONE;
            AddressSize addressSize = AddressSize::BITS_8;
            volatile uint32_t address = 0;
            AlternateBytesMode alternateBytesMode = AlternateBytesMode::NONE;
            AlternateBytesSize alternateBytesSize = AlternateBytesSize::BITS_8;
            volatile uint32_t alternateBytes = 0;
            uint8_t dummyCycles = 0;
            DataMode dataMode = DataMode::NONE;
            volatile uint32_t dataLength = 0;
        };

        /**
         * Return reference to peripheral
         *
         * @return              Reference to peripheral
         */
        static QUADSPI& get()
        {
            return instance;
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
         * Setup alternate pin function for clock
         *
         * @param clkPinId      Id of CLK pin
         */
        void initClockPin(Pin::Id clkPinId);

        /**
         * Setup alternate pin functions for a bank
         *
         * @param ncsPinId      Id of NCS pin
         * @param io0PinId      Id of IO0 pin
         * @param io1PinId      Id of IO1 pin
         * @param io2PinId      Id of IO2 pin
         * @param io3PinId      Id of IO3 pin
         */
        void initBankPins(Pin::Id ncsPinId, Pin::Id io0PinId, Pin::Id io1PinId,
                      Pin::Id io2PinId, Pin::Id io3PinId);

        /**
         * Release alternate pin function for clock
         *
         * @param clkPinId      Id of CLK pin
         */
        void deinitClockPin(Pin::Id clkPinId);

        /**
         * Release alternate pin functions for a bank
         *
         * @param ncsPinId      Id of NCS pin
         * @param io0PinId      Id of IO0 pin
         * @param io1PinId      Id of IO1 pin
         * @param io2PinId      Id of IO2 pin
         * @param io3PinId      Id of IO3 pin
         */
        void deinitBankPins(Pin::Id ncsPinId, Pin::Id io0PinId, Pin::Id io1PinId,
                      Pin::Id io2PinId, Pin::Id io3PinId);

        /**
         * Set clock prescaler
         *
         * @param prescaler     Prescaler value 1..256
         */
        void setPrescaler(int prescaler);

        /**
         * Set sample shift state
         *
         * @param state         State of sample shift
         */
        void setSampleShift(bool state);

        /**
         * Set FIFO threshold level
         *
         * @param level         Threshold level value 1..16
         */
        void setFIFOThreshold(int level);

        /**
         * Set flash size
         *
         * @param bits          Number of address bits
         */
        void setFlashSize(int bits);

        /**
         * Set minimum high time for CS line between commands
         *
         * @param cycles        Number of cycles 1..8
         */
        void setCSHighTime(int cycles);

        /**
         * Set clock polarity
         *
         * @param polarity      ClockPolarity enum setting
         */
        void setClockPolarity(ClockPolarity polarity);

        /**
         * Enable/disable DMA
         *
         * @param state         DMA state
         */
        void setDMAEnable(bool state);

        /**
         * Select memory
         *
         * @param memory        MemorySelect enum setting
         */
        void selectMemory(MemorySelect memory);

        /**
         * Set address
         *
         * @param address       Address value
         */
        void setAddress(volatile uint32_t address);

        /**
         * Set alternate bytes
         *
         * @param value         Alternate bytes value
         */
        void setAlternateBytes(volatile uint32_t value);

        /**
         * Set data length
         *
         * @param length        Data length in bytes
         */
        void setDataLength(volatile uint32_t length);

        /**
         * Set polling status mask
         *
         * @param mask          Status mask value
         */
        void setStatusMask(volatile uint32_t mask);

        /**
         * Set polling status match
         *
         * @param match         Status match value
         */
        void setStatusMatch(volatile uint32_t match);

        /**
         * Set polling interval
         *
         * @param cycles        Number of clock cycles
         */
        void setPollingInterval(volatile uint16_t cycles);

        /**
         * Set polling match mode
         *
         * @param mode          PollingMatchMode enum setting
         */
        void setPollingMatchMode(PollingMatchMode mode);

        /**
         * Set automatic poll mode stop after match
         *
         * @param state         Mode state
         */
        void setAutomaticPollModeStop(bool state);

        /**
         * Initialize a transaction
         *
         * @param config        Reference to configuration struct
         */
        void initTransaction(TransactionConfig& config);

        /**
         * Set transfer complete callback function and enable interrupts in NVIC
         *
         * @param func          Callback function or nullptr
         * @param context       Pointer to callback context
         */
        void setTransferCompleteCallback(CallbackFunc func, void* context=nullptr);

        /**
         * Transmit array of data bytes, blocking
         *
         * @param buffer        Buffer containing data
         * @param length        Size of data in buffer in bytes
         */
        void transmitData(uint8_t buffer[], int length);

        /**
         * Receive multiple data bytes into buffer, blocking
         *
         * @param buffer        Buffer to be filled with data
         * @param length        Size of buffer in bytes
         */
        void receiveData(uint8_t buffer[], int length);

        /**
         * Enable peripheral
         */
        void enable();

        /**
         * Disable peripheral
         */
        void disable();

        /**
         * Abort current request
         */
        void abort();

        /**
         * Return busy state
         *
         * @return              State of busy flag
         */
        bool isBusy();

        /**
         * Return transfer complete state
         *
         * @return          Complete flag state
         */
        bool hasTransferComplete();

        /**
         * Wait until all data frame are processed
         */
        void waitWhileBusy();

        /**
         * Wait until transfer is complete
         */
        void waitUntilTransferComplete();

        /**
         * Return pointer to registers
         *
         * @return      Pointer to registers struct
         */
        auto getRegisters()
        {
            return QUADSPI_Registers::get();
        }

        /**
         * Return IRQ number
         */
        int getIRQNumber()
        {
            return IrqId::QUADSPI;
        }

        /**
         * Enable/disable interrupt when transfer is complete
         *
         * @param state         Interrupt state
         */
        void setTransferCompleteInterrupt(bool state);

        /**
         * Process interrupt, called from IRQ handler
         */
        void irq();

    protected:
        /**
         * Private constructors because of singleton pattern, no copy allowed
         */
        QUADSPI() {}
        QUADSPI(const QUADSPI&) = delete;
        QUADSPI& operator = (const QUADSPI&) = delete;
        QUADSPI& operator = (QUADSPI&&) = delete;

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
         * Transmit single halfword
         *
         * @param data          Data halfword to send
         */
        void transmitHalfword(uint16_t data);

        /**
         * Return last received halfword
         *
         * @return              Received data halfword
         */
        uint16_t receiveHalfword();

        /**
         * Transmit single word
         *
         * @param data          Data word to send
         */
        void transmitWord(uint32_t data);

        /**
         * Return last received word
         *
         * @return              Received data word
         */
        uint32_t receiveWord();

        /**
         * Callbacks
         */
        CallbackFunc transferCompleteCallback = nullptr;
        void* transferCompleteCallbackContext = nullptr;

        /**
         * Singleton instance
         */
        static QUADSPI instance;
};


}   // namespace mcu
