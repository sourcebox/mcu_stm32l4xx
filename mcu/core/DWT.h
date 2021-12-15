/**
 * @file        DWT.h
 *
 * Driver for Data Watchpoint and Trace on Cortex-M4
 *
 * @author:     Oliver Rockstedt <info@sourcebox.de>
 * @license     MIT
 */


#pragma once


// Local includes
#include "DWT_Registers.h"


namespace mcu {


class DWT
{
    public:
        /**
         * Return reference to peripheral
         *
         * @return              Reference to peripheral
         */
        static DWT& get()
        {
            return instance;
        }

    protected:
        /**
         * Private constructors because of singleton pattern, no copy allowed
         */
        DWT() {}
        DWT(const DWT&) = delete;
        DWT& operator = (const DWT&) = delete;
        DWT& operator = (DWT&&) = delete;

        /**
         * Singleton instance
         */
        static DWT instance;
};


}   // namespace mcu
