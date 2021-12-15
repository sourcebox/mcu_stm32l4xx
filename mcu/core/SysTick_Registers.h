/**
 * @file        SysTick_Registers.h
 *
 * Register definitions for SysTick on Cortex-M4
 *
 * @author:     Oliver Rockstedt <info@sourcebox.de>
 * @license     MIT
 */


#pragma once


// Local includes
#include "cortex_m4.h"

// System libraries
#include <cstdint>


namespace mcu {

class SysTick_Registers
{
    public:
        struct Block
        {
            volatile uint32_t CTRL;     // Offset 0x000 (R/W)  SysTick Control and Status Register
            volatile uint32_t LOAD;     // Offset 0x004 (R/W)  SysTick Reload Value Register
            volatile uint32_t VAL;      // Offset 0x008 (R/W)  SysTick Current Value Register
            volatile uint32_t CALIB;    // Offset 0x00C (R/ )  SysTick Calibration Value Register
        } __attribute__((packed));

        struct CTRL
        {
            static const uint32_t ENABLE    = 0;
            static const uint32_t TICKINT   = 1;
            static const uint32_t CLKSOURCE = 2;
        };

        /**
         * Return pointer to registers block
         *
         * @return          Pointer to registers
         */
        static constexpr Block* get()
        {
            return (Block*)BASE_ADDRESS;
        }

    protected:
        // Register block base address
        static constexpr uint32_t BASE_ADDRESS = SCS_BASE_ADDRESS +  0x0010;
};


}   // namespace mcu
