/**
 * @file        LPTimer.h
 *
 * Driver for low power timer peripherals on STM32L4xx
 *
 * @author:     Oliver Rockstedt <info@sourcebox.de>
 * @license     MIT
 */


#pragma once


// Local includes
#include "LPTimer_Base.h"
#include "LPTimer_Registers.h"
#include "LPTimer_Channel.h"

// System libraries
#include <cstdint>


namespace mcu {


class LPTimer : public LPTimer_Base
{
    public:
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
        };

        /**
         * Return reference to peripheral
         *
         * @param id            Peripheral id
         * @return              Reference to peripheral
         */
        static LPTimer& get(Id id)
        {
            switch (id) {
                case Id::LPTIM1:
                    return lptimer1;
                case Id::LPTIM2:
                    return lptimer2;
            }

            return lptimer1;
        }

        /**
         * Return reference to channel
         *
         * @param channelId     Channel id
         * @return              Reference to channel object
         */
        LPTimer_Channel& getChannel(ChannelId channelId)
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
         * @param value         Prescaler value 1, 2, 4, 8, 16, 32, 64, 128
         */
        void setPrescaler(uint16_t value);

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
         * Enable
         */
        void enable();

        /**
         * Disable
         */
        void disable();

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
            return LPTimer_Registers::get(id);
        }

        /**
         * Process interrupt, called from IRQ handler
         */
        void irq();

    protected:
        /**
         * Private constructors because of singleton pattern, no copy allowed
         */
        LPTimer(Id id);
        LPTimer(const LPTimer&) = delete;
        LPTimer& operator = (const LPTimer&) = delete;
        LPTimer& operator = (LPTimer&&) = delete;

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
        LPTimer_Channel channels[1] =
        {
            LPTimer_Channel(id, ChannelId::CH1)
        };

        /**
         * Update callback function
         */
        CallbackFunc updateCallback;

        /**
         * Singleton instances
         */
        static LPTimer lptimer1;
        static LPTimer lptimer2;
};


}   // namespace mcu
