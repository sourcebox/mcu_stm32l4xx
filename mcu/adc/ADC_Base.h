/**
 * @file        ADC_Base.h
 *
 * Base definitions for ADC peripherals on STM32L4xx
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


class ADC_Base
{
    public:
        /**
         * Peripheral id
         */
        enum Id
        {
            ADC1,
            ADC2
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
                IrqId::ADC1_2,
                IrqId::ADC1_2
            };

            return irqNumbers[id];
        }
};


}   // namespace mcu
