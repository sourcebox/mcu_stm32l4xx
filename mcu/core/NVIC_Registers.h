/**
 * @file        NVIC_Registers.h
 *
 * Register definitions for Nested Interrupt Vector Controller on Cortex-M4
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


class NVIC_Registers
{
    public:
        struct Block
        {
            volatile uint32_t ISER[8];      // Offset 0x000 (R/W)  Interrupt Set Enable Register
            uint32_t _RESERVED_0[24];
            volatile uint32_t ICER[8];      // Offset 0x080 (R/W)  Interrupt Clear Enable Register
            uint32_t _RESERVED_1[24];
            volatile uint32_t ISPR[8];      // Offset 0x100 (R/W)  Interrupt Set Pending Register
            uint32_t _RESERVED_2[24];
            volatile uint32_t ICPR[8];      // Offset 0x180 (R/W)  Interrupt Clear Pending Register
            uint32_t _RESERVED_3[24];
            volatile uint32_t IABR[8];      // Offset 0x200 (R/W)  Interrupt Active bit Register
            uint32_t _RESERVED_4[56];
            volatile uint8_t  IP[240];      // Offset 0x300 (R/W)  Interrupt Priority Register (8Bit wide)
            uint32_t _RESERVED_5[644];
            volatile uint32_t STIR;         // Offset 0xE00 ( /W)  Software Trigger Interrupt Register
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
        static constexpr uint32_t BASE_ADDRESS = SCS_BASE_ADDRESS +  0x0100;
};


}   // namespace mcu
