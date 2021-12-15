/**
 * @file        UART_Base.h
 *
 * Base definitions for UART peripherals on STM32L4xx
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


class UART_Base
{
    public:
        /**
         * Peripheral id
         */
        enum Id
        {
            USART1,
            USART2,
            USART3,
            UART4,
            LPUART1
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
                IrqId::USART1,
                IrqId::USART2,
                IrqId::USART3,
                IrqId::UART4,
                IrqId::LPUART1
            };

            return irqNumbers[id];
        }
};


}   // namespace mcu
