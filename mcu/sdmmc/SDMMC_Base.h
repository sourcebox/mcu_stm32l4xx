/**
 * @file        SDMMC_Base.h
 *
 * Base definitions for SDMMC peripherals on STM32L4xx
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


class SDMMC_Base
{
    public:
        /**
         * Peripheral id
         */
        enum Id
        {
            SDMMC1
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
                IrqId::SDMMC1
            };

            return irqNumbers[id];
        }
};


}   // namespace mcu
