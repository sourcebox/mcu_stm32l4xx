/**
 * @file        GPIO_Base.h
 *
 * Base definitions for GPIO peripherals on STM32L4xx
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


class GPIO_Base
{
    public:
        /**
         * Port id
         */
        enum PortId
        {
            GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOH,

            // Special id for no port
            NONE = -1
        };
};


}   // namespace mcu
