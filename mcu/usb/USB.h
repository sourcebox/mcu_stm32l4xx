/**
 * @file        USB.h
 *
 * Driver for USB peripheral on STM32L4xx
 *
 * @author:     Oliver Rockstedt <info@sourcebox.de>
 * @license     MIT
 */


#pragma once


// Local includes
#include "USB_Endpoint.h"
#include "USB_ControlEndpoint.h"

// System libraries
#include <cstdint>


namespace mcu {


class USB
{
    friend class USB_ControlEndpoint;

    public:
        /**
         * Device status
         */
        enum class Status
        {
            DISABLED,
            POWERED,
            DEFAULT,
            ADDRESSED,
            CONFIGURED,
            SUSPENDED,
            ATTACHED
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
            CallbackFunc resetCallback = nullptr;
            CallbackFunc suspendCallback = nullptr;
            CallbackFunc resumeCallback = nullptr;
            USB_ControlEndpoint::DescriptorCallbackFunc descriptorCallback;
        };

        /**
         * Return reference to peripheral
         *
         * @return              Reference to peripheral
         */
        static USB& get()
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
         * Init pins with alternate function
         */
        void initPins();

        /**
         * Deinit pins, set mode to input
         */
        void deinitPins();

        /**
         * Connect to bus
         */
        void connect();

        /**
         * Disconnect from bus
         */
        void disconnect();

        /**
         * Return status
         *
         * @return              Status according to enum class
         */
        Status getStatus()
        {
            return status;
        }

        /**
         * Return if device is ready
         *
         * @return              True if device is ready
         */
        bool isReady()
        {
            return status == Status::CONFIGURED;
        }

        /**
         * Set an endpoint
         *
         * @param number        Endpoint number
         * @param endpoint      Pointer to endpoint instance or nullptr
         */
        void setEndpoint(int number, USB_Endpoint* endpoint);

        /**
         * Set a callback function for reset
         */
        void setResetCallback(CallbackFunc func);

        /**
         * Set a callback function for suspend
         */
        void setSuspendCallback(CallbackFunc func);

        /**
         * Set a callback function for resume
         */
        void setResumeCallback(CallbackFunc func);

        /**
         * Sets a function to be called to get descriptors
         *
         * @param func          Callback function
         */
        void setDescriptorCallback(USB_ControlEndpoint::DescriptorCallbackFunc func,
                                   void* context=nullptr)
        {
            controlEndpoint.setDescriptorCallback(func, context);
        }

        /**
         * Return IRQ number
         */
        int getIRQNumber();

        /**
         * Process interrupt, called from IRQ handler
         */
        void irq();

    protected:
        static const int NUM_ENDPOINTS = 8;
        static const int TRANSCEIVER_STARTUP_DELAY = 10;        // In µs

        /**
         * Private constructors because of singleton pattern, no copy allowed
         */
        USB();
        USB(const USB&) = delete;
        USB& operator = (const USB&) = delete;
        USB& operator = (USB&&) = delete;

        /**
         * Enable clock
         */
        void enableClock();

        /**
         * Disable clock
         */
        void disableClock();

        /**
         * Enable power domain
         */
        void enablePower();

        /**
         * Disable power domain
         */
        void disablePower();

        /**
         * Enable transceiver
         */
        void enableTransceiver();

        /**
         * Disable transceiver
         */
        void disableTransceiver();

        /**
         * Enable interrupt
         */
        void enableInterrupt();

        /**
         * Disable interrupt
         */
        void disableInterrupt();

        /**
         * Enable/disable pullup resistor on DP line
         *
         * @param state         Pullup state
         */
        void setPullup(bool state);

        /**
         * Called from ISR on reset
         */
        void onReset();

        /**
         * Status
         */
        Status status = Status::DISABLED;
        Status preSuspendStatus = Status::DISABLED;

        /**
         * Endpoints
         */
        USB_Endpoint* endpoints[NUM_ENDPOINTS];
        USB_ControlEndpoint controlEndpoint;

        /**
         * Callbacks
         */
        CallbackFunc resetCallback = nullptr;
        CallbackFunc suspendCallback = nullptr;
        CallbackFunc resumeCallback = nullptr;

        /**
         * Singleton instance
         */
        static USB instance;
};


}   // namespace mcu
