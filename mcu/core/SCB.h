/**
 * @file        SCB.h
 *
 * Driver for System Control Block on Cortex-M4
 *
 * @author:     Oliver Rockstedt <info@sourcebox.de>
 * @license     MIT
 */


#pragma once


// Local includes
#include "SCB_Registers.h"


namespace mcu {


class SCB
{
    public:
        /**
         * Return reference to peripheral
         *
         * @return              Reference to peripheral
         */
        static SCB& get()
        {
            return instance;
        }

    protected:
        /**
         * Private constructors because of singleton pattern, no copy allowed
         */
        SCB() {}
        SCB(const SCB&) = delete;
        SCB& operator = (const SCB&) = delete;
        SCB& operator = (SCB&&) = delete;

        /**
         * Singleton instance
         */
        static SCB instance;
};


}   // namespace mcu
