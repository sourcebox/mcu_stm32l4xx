/**
 * @file        Timer_Channel.h
 *
 * Timer channel on STM32L4xx
 *
 * @author:     Oliver Rockstedt <info@sourcebox.de>
 * @license     MIT
 */


#pragma once


// Local includes
#include "Timer_Base.h"
#include "Timer_Registers.h"

// This component
#include "../gpio/Pin.h"

// System libraries
#include <cstdint>


namespace mcu {


class Timer_Channel : Timer_Base
{
    friend class Timer;

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
        Timer_Channel(Id timerId, ChannelId channelId);
        Timer_Channel(const Timer_Channel&) = delete;
        Timer_Channel& operator = (const Timer_Channel&) = delete;
        Timer_Channel& operator = (Timer_Channel&&) = delete;

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
        static CallbackFunc ch1Callbacks[7];
        static CallbackFunc ch2Callbacks[7];
        static CallbackFunc ch3Callbacks[7];
        static CallbackFunc ch4Callbacks[7];
};


}   // namespace mcu
