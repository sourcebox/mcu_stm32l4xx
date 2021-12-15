/**
 * @file        DMA_Base.h
 *
 * Base definitions for DMA controllers on STM32L4xx
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


class DMA_Base
{
    public:
        /**
         * Controller id
         */
        enum Id
        {
            DMA1, DMA2
        };


        /**
         * Channel id
         */
        enum ChannelId
        {
            CH1, CH2, CH3, CH4, CH5, CH6, CH7
        };

        /**
         * Return IRQ number
         *
         * @param id            Controller id
         * @param channelId     Channel id
         * @return              IRQ number for use with NVIC
         */
        static constexpr int getIRQNumber(Id id, ChannelId channelId)
        {
            constexpr int irqNumbers[2][7] =
            {
                {
                    IrqId::DMA1_Channel1,
                    IrqId::DMA1_Channel2,
                    IrqId::DMA1_Channel3,
                    IrqId::DMA1_Channel4,
                    IrqId::DMA1_Channel5,
                    IrqId::DMA1_Channel6,
                    IrqId::DMA1_Channel7
                },
                {
                    IrqId::DMA2_Channel1,
                    IrqId::DMA2_Channel2,
                    IrqId::DMA2_Channel3,
                    IrqId::DMA2_Channel4,
                    IrqId::DMA2_Channel5,
                    IrqId::DMA2_Channel6,
                    IrqId::DMA2_Channel7
                }
            };

            return irqNumbers[id][channelId];
        }
};


}   // namespace mcu
