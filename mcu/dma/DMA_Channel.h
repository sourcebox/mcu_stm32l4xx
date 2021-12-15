/**
 * @file        DMA_Channel.h
 *
 * DMA channel on STM32L4xx
 *
 * @author:     Oliver Rockstedt <info@sourcebox.de>
 * @license     MIT
 */


#pragma once


// Local includes
#include "DMA_Base.h"
#include "DMA_Registers.h"

// System libraries
#include <cstdint>


namespace mcu {


class DMA_Channel : public DMA_Base
{
    friend class DMA;

    public:
        /**
         * Transfer direction
         */
        enum class Direction
        {
            PERIPHERAL_TO_MEMORY,
            MEMORY_TO_PERIPHERAL
        };

        /**
         * Transfer size
         */
        enum class TransferSize
        {
            BITS_8  = 0b00,
            BITS_16 = 0b01,
            BITS_32 = 0b10
        };

        /**
         * Priority level
         */
        enum class PriorityLevel
        {
            LOW         = 0b00,
            MEDIUM      = 0b01,
            HIGH        = 0b10,
            VERY_HIGH   = 0b11
        };

        /**
         * Request peripheral
         */
        enum class RequestPeripheral
        {
            // DMA1
            DMA1_CH1_ADC1           = 0b0000,
            DMA1_CH1_TIM2_CH3       = 0b0100,
            DMA1_CH2_ADC2           = 0b0000,   // STM32L412xx, STM32L422xx only
            DMA1_CH2_SPI1_RX        = 0b0001,
            DMA1_CH2_USART3_TX      = 0b0010,   // Not STM32L432xx, STM32L442xx
            DMA1_CH2_I2C3_TX        = 0b0011,
            DMA1_CH2_TIM2_UP        = 0b0100,
            DMA1_CH2_TIM3_CH3       = 0b0101,   // STM32L45xxx, STM32L46xxx only
            DMA1_CH2_TIM1_CH1       = 0b0111,
            DMA1_CH3_SPI1_TX        = 0b0001,
            DMA1_CH3_USART3_RX      = 0b0010,   // Not STM32L432xx, STM32L442xx
            DMA1_CH3_I2C3_RX        = 0b0011,
            DMA1_CH3_TIM16_CH1      = 0b0100,
            DMA1_CH3_TIM16_UP       = 0b0100,
            DMA1_CH3_TIM3_CH4       = 0b0101,   // STM32L45xxx, STM32L46xxx only
            DMA1_CH3_TIM3_UP        = 0b0101,   // STM32L45xxx, STM32L46xxx only
            DMA1_CH3_TIM6_UP        = 0b0110,
            DMA1_CH3_DAC_CH1        = 0b0110,
            DMA1_CH3_TIM1_CH2       = 0b0111,
            DMA1_CH4_SPI2_RX        = 0b0001,   // Not STM32L432xx, STM32L442xx
            DMA1_CH4_USART1_TX      = 0b0010,
            DMA1_CH4_I2C2_TX        = 0b0011,   // Not STM32L432xx, STM32L442xx
            DMA1_CH4_TIM7_UP        = 0b0101,
            DMA1_CH4_DAC_CH2        = 0b0101,   // STM32L43xx, STM32L44xx only
            DMA1_CH4_TIM1_CH4       = 0b0111,
            DMA1_CH4_TIM1_TRIG      = 0b0111,
            DMA1_CH4_TIM1_COM       = 0b0111,
            DMA1_CH5_DFSDM1_FLT0    = 0b0000,
            DMA1_CH5_SPI2_TX        = 0b0001,   // Not STM32L432xx, STM32L442xx
            DMA1_CH5_USART1_RX      = 0b0010,
            DMA1_CH5_I2C2_RX        = 0b0011,   // Not STM32L432xx, STM32L442xx
            DMA1_CH5_TIM2_CH1       = 0b0100,
            DMA1_CH5_QUADSPI        = 0b0101,
            DMA1_CH5_TIM15_CH1      = 0b0111,
            DMA1_CH5_TIM15_UP       = 0b0111,
            DMA1_CH5_TIM15_TRIG     = 0b0111,
            DMA1_CH5_TIM15_COM      = 0b0111,
            DMA1_CH6_DFSDM1_FLT1    = 0b0000,
            DMA1_CH6_SAI2_A         = 0b0001,   // Not STM32L412xx, STM32L422xx
            DMA1_CH6_USART2_RX      = 0b0010,
            DMA1_CH6_I2C1_TX        = 0b0011,
            DMA1_CH6_TIM16_CH1      = 0b0100,
            DMA1_CH6_TIM16_UP       = 0b0100,
            DMA1_CH6_TIM3_CH1       = 0b0101,   // STM32L45xxx, STM32L46xxx only
            DMA1_CH6_TIM3_TRIG      = 0b0101,   // STM32L45xxx, STM32L46xxx only
            DMA1_CH6_TIM1_UP        = 0b0111,
            DMA1_CH7_SAI2_B         = 0b0001,   // Not STM32L412xx, STM32L422xx
            DMA1_CH7_USART2_TX      = 0b0010,
            DMA1_CH7_I2C1_RX        = 0b0011,
            DMA1_CH7_TIM2_CH2       = 0b0100,
            DMA1_CH7_TIM2_CH4       = 0b0100,
            DMA1_CH7_TIM1_CH3       = 0b0111,

            // DMA2
            DMA2_CH1_I2C4_RX        = 0b0000,   // STM32L45xxx, STM32L46xxx only
            DMA2_CH1_SAI1_A         = 0b0001,
            DMA2_CH1_SPI3_RX        = 0b0011,
            DMA2_CH1_SWPMI1_RX      = 0b0100,   // STM32L43xxx, STM32L44xxx only
            DMA2_CH1_AES_IN         = 0b0110,   // STM32L44xxx, STM32L46xxx only
            DMA2_CH2_I2C4_TX        = 0b0000,   // STM32L45xxx, STM32L46xxx only
            DMA2_CH2_SAI1_B         = 0b0001,
            DMA2_CH2_SPI3_TX        = 0b0011,
            DMA2_CH2_SWPMI1_TX      = 0b0100,   // STM32L43xxx, STM32L44xxx only
            DMA2_CH2_AES_OUT        = 0b0110,   // STM32L44xxx, STM32L46xxx only
            DMA2_CH3_ADC1           = 0b0000,
            DMA2_CH3_UART4_TX       = 0b0010,   // STM32L45xxx, STM32L46xxx only
            DMA2_CH3_SPI1_RX        = 0b0100,
            DMA2_CH3_AES_OUT        = 0b0110,   // STM32L44xxx, STM32L46xxx only
            DMA2_CH4_ADC2           = 0b0000,   // STM32L41xxx, STM32L42xxx only
            DMA2_CH4_TIM6_UP        = 0b0011,
            DMA2_CH4_DAC_CH1        = 0b0011,
            DMA2_CH4_SPI1_TX        = 0b0100,
            DMA2_CH4_SDMMC1         = 0b0111,   // Not STM32L432xx, STM32L442xx
            DMA2_CH5_UART4_RX       = 0b0010,   // STM32L45xxx, STM32L46xxx only
            DMA2_CH5_TIM7_UP        = 0b0011,
            DMA2_CH5_DAC_CH2        = 0b0011,   // STM32L43xxx, STM32L44xxx only
            DMA2_CH5_AES_IN         = 0b0110,   // STM32L44xxx, STM32L46xxx only
            DMA2_CH5_SDMMC1         = 0b0111,   // Not STM32L432xx, STM32L442xx
            DMA2_CH6_SAI1_A         = 0b0001,
            DMA2_CH6_USART1_TX      = 0b0010,
            DMA2_CH6_LPUART1_TX     = 0b0100,
            DMA2_CH6_I2C1_RX        = 0b0101,
            DMA2_CH7_SAI1_B         = 0b0001,
            DMA2_CH7_USART1_RX      = 0b0010,
            DMA2_CH7_QUADSPI        = 0b0011,
            DMA2_CH7_LPUART1_RX     = 0b0100,
            DMA2_CH7_I2C1_TX        = 0b0101
        };

        /**
         * Callback function type
         */
        typedef void(*CallbackFunc)(void);

        /**
         * Configuration settings
         */
        struct Config
        {
            Direction direction = Direction::PERIPHERAL_TO_MEMORY;
            uint32_t peripheralAddress = 0;
            uint32_t memoryAddress = 0;
            uint16_t transferLength = 0;
            bool peripheralIncrement = false;
            bool memoryIncrement = false;
            TransferSize peripheralSize = TransferSize::BITS_8;
            TransferSize memorySize = TransferSize::BITS_8;
            PriorityLevel priorityLevel = PriorityLevel::LOW;
            bool circularMode = false;
            bool memoryToMemory = false;
            RequestPeripheral requestPeripheral = (RequestPeripheral)0;
        };

        /**
         * Constructor
         *
         * @param dmaId         DMA id
         * @param channelId     Channel id
         */
        static DMA_Channel get(Id dmaId, ChannelId channelId)
        {
            return DMA_Channel(dmaId, channelId);
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
         * Enable channel
         */
        void enable();

        /**
         * Disable channel
         */
        void disable();

        /**
         * Set transfer direction
         *
         * @param dir       Direction according to enum class
         */
        void setDirection(Direction dir);

        /**
         * Set peripheral address
         *
         * @param address   Peripheral address
         */
        void setPeripheralAddress(uint32_t address);

        /**
         * Set memory address
         *
         * @param address   Memory address
         */
        void setMemoryAddress(uint32_t address);

        /**
         * Set number of items to transfer
         *
         * @param length    Transfer length in no of items
         */
        void setTransferLength(volatile uint16_t length);

        /**
         * Enable/disable peripheral address increment
         *
         * @param state     Peripheral increment mode state
         */
        void setPeripheralIncrement(bool state);

        /**
         * Enable/disable memory address increment
         *
         * @param state     Memory increment mode state
         */
        void setMemoryIncrement(bool state);

        /**
         * Set peripheral transfer size
         *
         * @param size      Transfer size according to enum class
         */
        void setPeripheralSize(TransferSize size);

        /**
         * Set memory transfer size
         *
         * @param size      Transfer size according to enum class
         */
        void setMemorySize(TransferSize size);

        /**
         * Set priority level
         *
         * @param level     Priority level according to enum class
         */
        void setPriorityLevel(PriorityLevel level);

        /**
         * Enable/disable circular mode
         *
         * @param state     Circular mode state
         */
        void setCircularMode(bool state);

        /**
         * Set memory-to-memory mode
         *
         * @param state     Memory-to-memory mode state
         */
        void setMemoryToMemory(bool state);

        /**
         * Set request peripheral
         *
         * @param request   Request peripheral according to enum class
         */
        void setRequestPeripheral(RequestPeripheral request);

        /**
         * Set transfer complete callback funtion
         *
         * @param func      Callback function or nullptr
         */
        void setCompleteCallback(CallbackFunc func);

        /**
         * Set transfer half complete callback function
         *
         * @param func      Callback function or nullptr
         */
        void setHalfCompleteCallback(CallbackFunc func);

        /**
         * Set transfer error callback function
         *
         * @param func      Callback function or nullptr
         */
        void setErrorCallback(CallbackFunc func);

        /**
         * Return transfer complete state
         *
         * @return          Complete flag state
         */
        bool isComplete();

        /**
         * Clear transfer complete flag
         */
        void clearComplete();

        /**
         * Return transfer half complete state
         *
         * @return          Half complete flag state
         */
        bool isHalfComplete();

        /**
         * Clear transfer half complete flag
         */
        void clearHalfComplete();

        /**
         * Return transfer error state
         *
         * @return          Error flag state
         */
        bool hasError();

        /**
         * Clear transfer error
         */
        void clearError();

        /**
         * Return registers set for this channel
         *
         * @return          Pointer to registers struct
         */
        auto getRegisters()
        {
            return channelRegisters;
        }

        /**
         * Process interrupt, called from IRQ handler
         */
        void irq();

    protected:
        /**
         * Private constructors because of singleton pattern, no copy allowed
         */
        DMA_Channel(Id dmaId, ChannelId channelId);
        DMA_Channel(const DMA_Channel&) = delete;
        DMA_Channel& operator = (const DMA_Channel&) = delete;
        DMA_Channel& operator = (DMA_Channel&&) = delete;

        /**
         * DMA id
         */
        Id dmaId;

        /**
         * Channel id
         */
        const ChannelId channelId;

        /**
         * Pointer to peripheral registers
         */
        DMA_Registers::Block* registers = DMA_Registers::get(dmaId);

        /**
         * Pointer to peripheral channel registers
         */
        DMA_ChannelRegisters::Block* channelRegisters;

        /**
         * Callback functions
         */
        static CallbackFunc completeCallbacks[2][7];
        static CallbackFunc halfCompleteCallbacks[2][7];
        static CallbackFunc errorCallbacks[2][7];
};


}   // namespace mcu
