/**
 * @file        LPTimer_Base.h
 *
 * Base definitions for low power timer peripherals on STM32L4xx
 *
 * @author:     Oliver Rockstedt <info@sourcebox.de>
 * @license     MIT
 */


#pragma once


// This component
#include "../core/mcu_base.h"

// System libraries
#include <cstdint>


namespace mcu {


class LPTimer_Base
{
    public:
        /**
         * Peripheral id
         */
        enum Id
        {
            LPTIM1,
            LPTIM2
        };

        /**
         * Channel id
         */
        enum ChannelId
        {
            CH1
        };

        /**
         * Return IRQ number
         *
         * @param id    Peripheral id
         * @return      IRQ number for use with NVIC
         */
        static constexpr int getIRQNumber(Id id)
        {
            constexpr int irqNumbers[] =
            {
                IrqId::LPTIM1,
                IrqId::LPTIM2
            };

            return irqNumbers[id];
        }
};


}   // namespace mcu
