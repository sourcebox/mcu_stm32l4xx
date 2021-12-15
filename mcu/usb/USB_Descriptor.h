/**
 * @file        USB_Descriptor.h
 *
 * Abstract base class for USB descriptors
 *
 * @author:     Oliver Rockstedt <info@sourcebox.de>
 * @license     MIT
 */


#pragma once


// System libraries
#include <cstdint>


namespace mcu {


class USB_Descriptor
{
    public:
        /**
         * Types
         */
        enum class Type
        {
            DEVICE                      = 1,
            CONFIGURATION               = 2,
            STRING                      = 3,
            INTERFACE                   = 4,
            ENDPOINT                    = 5,
            DEVICE_QUALIFIER            = 6,
            OTHER_SPEED_CONFIGURATION   = 7,
            NTERFACE_POWER              = 8
        };

        /**
         * Init, called once before descriptor is read
         */
        virtual void onInit() {};

        /**
         * Deinit, called once after descriptor is read
         */
        virtual void onDeinit() {};

        /**
         * Return total length
         */
        virtual uint16_t onGetLength() = 0;

        /**
         * Return single data byte
         *
         * @param index         Data index 0..getLength()-1
         * @return              Data byte
         */
        virtual uint8_t onGetData(int index) = 0;
};


}   // namespace mcu
