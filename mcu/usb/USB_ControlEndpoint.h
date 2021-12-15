/**
 * @file        USB_ControlEndpoint.h
 *
 * Driver for USB control endpoint on STM32L4xx
 *
 * @author:     Oliver Rockstedt <info@sourcebox.de>
 * @license     MIT
 */


#pragma once


// Local includes
#include "USB_Endpoint.h"
#include "USB_Descriptor.h"

// System libraries
#include <cstdint>


namespace mcu {


class USB_ControlEndpoint : public USB_Endpoint
{
    public:
        /**
         * Constructor
         */
        USB_ControlEndpoint() : USB_Endpoint(0) {}

        /**
         * Disallow copy
         */
        USB_ControlEndpoint(const USB_ControlEndpoint&) = delete;
        USB_ControlEndpoint& operator= (const USB_ControlEndpoint&) = delete;
        USB_ControlEndpoint& operator = (USB_ControlEndpoint&&) = delete;

        /**
         * Descriptor callback function type
         */
        typedef USB_Descriptor*(*DescriptorCallbackFunc)(USB_Descriptor::Type,
                int, void*);

        /**
         * Sets a function to be called to get descriptors
         *
         * @param func          Callback function
         */
        void setDescriptorCallback(DescriptorCallbackFunc func,
                                   void* context=nullptr)
        {
            descriptorCallbackFunc = func;
            descriptorCallbackContext = context;
        }

    protected:
        /**
         * Called from USB::irq() on reset
         */
        virtual void onReset() override;

        /**
         * Called from USB::irq() when a setup packet was received
         */
        virtual void onSetupReceptionComplete() override;

        /**
         * Called from USB::irq() when data was received
         */
        virtual void onReceptionComplete() override;

        /**
         * Called from USB::irq() when data was transmitted
         */
        virtual void onTransmissionComplete() override;

    private:
        /**
         * Setup stage, called from onReceptionCompleted()
         */
        void onSetupStage();

        /**
         * Data stage IN, called from onReceptionCompleted()
         */
        void onDataStageIN();

        /**
         * Data stage OUT, called from onReceptionCompleted()
         */
        void onDataStageOUT();

        /**
         * Status stage, called from onReceptionCompleted()
         */
        void onStatusStage();

        /**
         * Data stage
         */
        enum class DataStage
        {
            NONE,
            IN,
            OUT
        };

        DataStage dataStage = DataStage::NONE;
        int dataStageLength = 0;

        /**
         * Temporary address storage on setup
         */
        int addressTemp = 0;

        /**
         * Callback function for getting descriptors
         */
        DescriptorCallbackFunc descriptorCallbackFunc = nullptr;
        void* descriptorCallbackContext = nullptr;

        /**
         * Descriptor in transmission
         */
        USB_Descriptor* pendingDescriptor = nullptr;
        int pendingDescriptorDataIndex = 0;
};

}   // namespace mcu
