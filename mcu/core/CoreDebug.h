/**
 * @file        CoreDebug.h
 *
 * Driver for CoreDebug on Cortex-M4
 *
 * @author:     Oliver Rockstedt <info@sourcebox.de>
 * @license     MIT
 */


#pragma once


// Local includes
#include "CoreDebug_Registers.h"


namespace mcu {


class CoreDebug
{
    public:
        /**
         * Return reference to peripheral
         *
         * @return              Reference to peripheral
         */
        static CoreDebug& get()
        {
            return instance;
        }

    protected:
        /**
         * Private constructors because of singleton pattern, no copy allowed
         */
        CoreDebug() {}
        CoreDebug(const CoreDebug&) = delete;
        CoreDebug& operator = (const CoreDebug&) = delete;
        CoreDebug& operator = (CoreDebug&&) = delete;

        /**
         * Singleton instance
         */
        static CoreDebug instance;
};


}   // namespace mcu
