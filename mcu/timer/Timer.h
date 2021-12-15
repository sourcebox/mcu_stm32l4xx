/**
 * @file        Timer.h
 *
 * Driver for timer peripherals on STM32L4xx
 *
 * @author:     Oliver Rockstedt <info@sourcebox.de>
 * @license     MIT
 */


#pragma once


// Local includes
#include "Timer_Base.h"
#include "Timer_Registers.h"
#include "Timer_Channel.h"

// System libraries
#include <cstdint>


namespace mcu {


class Timer : public Timer_Base
{
    public:
        /**
         * Master mode
         */
        enum class MasterMode
        {
            RESET   = 0b00,
            ENABLE  = 0b01,
            UPDATE  = 0b10
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
            uint16_t prescaler = 1;
            uint32_t period = 0;
            MasterMode masterMode = MasterMode::RESET;
        };

        /**
         * Return reference to peripheral
         *
         * @param id            Peripheral id
         * @return              Reference to peripheral
         */
        static Timer& get(Id id)
        {
            switch (id) {
                case Id::TIM1:
                    return tim1;
                case Id::TIM2:
                    return tim2;
                case Id::TIM3:
                    return tim3;
                case Id::TIM6:
                    return tim6;
                case Id::TIM7:
                    return tim7;
                case Id::TIM15:
                    return tim15;
                case Id::TIM16:
                    return tim16;
            }

            return tim1;
        }

        /**
         * Return reference to channel
         *
         * @param channelId     Channel id
         * @return              Reference to channel object
         */
        Timer_Channel& getChannel(ChannelId channelId)
        {
            return channels[(int)channelId];
        }

        /**
         * Base init
         */
        void init();

        /**
         * Init with prescaler and period
         *
         * @param prescaler     Prescaler value
         * @param period        Period value
         */
        void init(uint16_t prescaler, uint32_t period);

        /**
         * Init with frequency
         *
         * @param freq          Frequency value in Hz
         */
        void init(int freq);

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
         * Return prescaler value
         *
         * @return              Current prescaler value
         */
        uint32_t getPrescaler();

        /**
         * Set prescaler
         *
         * @param value         Prescaler value starting with 1
         */
        void setPrescaler(volatile uint16_t value);

        /**
         * Return period value
         *
         * @return              Current period value
         */
        uint32_t getPeriod();

        /**
         * Set period
         *
         * @param value         Period value
         */
        void setPeriod(volatile uint32_t value);

        /**
         * Set prescaler and period by frequency
         *
         * @param freq          Frequency in Hz
         */
        void setFrequency(uint32_t freq);

        /**
         * Set master mode
         *
         * @param mode          Mode according to enum class
         */
        void setMasterMode(MasterMode mode);

        /**
         * Start counter
         */
        void start();

        /**
         * Stop counter
         */
        void stop();

        /**
         * Return counter value
         *
         * @return              Current counter value
         */
        uint32_t getCounter();

        /**
         * Set counter value
         *
         * @param value         New counter value
         */
        void setCounter(uint32_t value);

        /**
         * Set update callback function and enable interrupts
         *
         * @param func          Callback function or nullptr
         */
        void setUpdateCallback(CallbackFunc func);

        /**
         * Trigger an update event
         */
        void triggerUpdateEvent();

        /**
         * Enable/disable update DMA request
         *
         * @param state         Request state
         */
        void setUpdateDMARequest(bool state);

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
            return Timer_Registers::get(id);
        }

        /**
         * Process interrupt, called from IRQ handler
         */
        void irq();

    protected:
        /**
         * Private constructors because of singleton pattern, no copy allowed
         */
        Timer(Id id);
        Timer(const Timer&) = delete;
        Timer& operator = (const Timer&) = delete;
        Timer& operator = (Timer&&) = delete;

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
         * Channels
         */
        Timer_Channel channels[4] = {
            Timer_Channel(id, ChannelId::CH1),
            Timer_Channel(id, ChannelId::CH2),
            Timer_Channel(id, ChannelId::CH3),
            Timer_Channel(id, ChannelId::CH4)
        };

        /**
         * Update callback function
         */
        CallbackFunc updateCallback;

        /**
         * Singleton instances
         */
        static Timer tim1;
        static Timer tim2;
        static Timer tim3;
        static Timer tim6;
        static Timer tim7;
        static Timer tim15;
        static Timer tim16;
};


}   // namespace mcu
