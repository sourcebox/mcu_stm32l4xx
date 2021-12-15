/**
 * @file        LPTimer_Channel.h
 *
 * Low power timer channel on STM32L4xx
 *
 * @author:     Oliver Rockstedt <info@sourcebox.de>
 * @license     MIT
 */


#pragma once


// Local includes
#include "LPTimer_Base.h"
#include "LPTimer_Registers.h"

// This component
#include "../gpio/Pin.h"

// System libraries
#include <cstdint>


namespace mcu {


class LPTimer_Channel : public LPTimer_Base
{
    friend class LPTimer;

    public:
        /**
         * Output Polarity
         */
        enum class Polarity
        {
            ACTIVE_HIGH,
            ACTIVE_LOW
        };

        /**
         * Callback function type
         */
        typedef void(*CallbackFunc)(void);

        /**
         * Init PWM mode
         *
         * @param pinId         Pin id
         * @param polarity      Output polarity according to enum
         */
        void initPWM(Pin::Id pinId=Pin::NONE, Polarity polarity=Polarity::ACTIVE_HIGH);

        /**
         * Init pin with alternate function
         *
         * @param pinId         Pin id
         */
        void initPin(Pin::Id pinId);

        /**
         * Set compare value
         *
         * @param value         compare value
         */
        void setCompare(volatile uint32_t value);

        /**
         * Return capture value
         *
         * @return          Capture value
         */
        uint32_t getCapture();

        /**
         * Set capture/compare callback funtion
         *
         * @param func      Callback function or nullptr
         */
        void setCallback(CallbackFunc func);

    protected:
        /**
         * Private constructors because of singleton pattern, no copy allowed
         */
        LPTimer_Channel(Id timerId, ChannelId id);
        LPTimer_Channel(const LPTimer_Channel&) = delete;
        LPTimer_Channel& operator = (const LPTimer_Channel&) = delete;
        LPTimer_Channel& operator = (LPTimer_Channel&&) = delete;

        /**
         * Timer id
         */
        const Id timerId;

        /**
         * Channel id
         */
        const ChannelId channelId;

        /**
         * Callback function
         */
        static CallbackFunc ch1Callbacks[2];
};


}   // namespace mcu
