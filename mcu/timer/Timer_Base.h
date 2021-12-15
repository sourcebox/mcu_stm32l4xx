/**
 * @file        Timer_Base.h
 *
 * Base definitions for timer peripherals on STM32L4xx
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


class Timer_Base
{
    public:
        /**
         * Peripheral id
         */
        enum Id
        {
            TIM1,
            TIM2,
            TIM3,
            TIM6,
            TIM7,       // Available on L43x and L44x only
            TIM15,
            TIM16
        };

        /**
         * Channel id
         */
        enum ChannelId
        {
            CH1, CH2, CH3, CH4
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
                IrqId::TIM1_UP_TIM16,
                IrqId::TIM2,
                IrqId::TIM3,
                IrqId::TIM6_DACUNDER,
                IrqId::TIM7,
                IrqId::TIM1_BRK_TIM15,
                IrqId::TIM1_UP_TIM16
            };

            return irqNumbers[id];
        }
};


}   // namespace mcu
