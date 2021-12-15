/**
 * @file        CoreDebug_Registers.h
 *
 * Register definitions for CoreDebug on Cortex-M4
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


class CoreDebug_Registers
{
    public:
        struct Block
        {
            volatile uint32_t DHCSR;    // Offset 0x000 (R/W)  Debug Halting Control and Status Register
            volatile uint32_t DCRSR;    // Offset 0x004 ( /W)  Debug Core Register Selector Register
            volatile uint32_t DCRDR;    // Offset 0x008 (R/W)  Debug Core Register Data Register
            volatile uint32_t DEMCR;    // Offset 0x00C (R/W)  Debug Exception and Monitor Control Register
        } __attribute__((packed));

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
        static constexpr uint32_t BASE_ADDRESS = 0xE000EDF0;
};

}   // namespace mcu
