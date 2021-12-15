/**
 * @file        DWT_Registers.h
 *
 * Register definitions for Data Watchpoint and Trace on Cortex-M4
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


class DWT_Registers
{
    public:
        struct Block
        {
            volatile uint32_t CTRL;         // Offset 0x000 (R/W)  Control Register
            volatile uint32_t CYCCNT;       // Offset 0x004 (R/W)  Cycle Count Register
            volatile uint32_t CPICNT;       // Offset 0x008 (R/W)  CPI Count Register
            volatile uint32_t EXCCNT;       // Offset 0x00C (R/W)  Exception Overhead Count Register
            volatile uint32_t SLEEPCNT;     // Offset 0x010 (R/W)  Sleep Count Register
            volatile uint32_t LSUCNT;       // Offset 0x014 (R/W)  LSU Count Register
            volatile uint32_t FOLDCNT;      // Offset 0x018 (R/W)  Folded-instruction Count Register
            volatile uint32_t PCSR;         // Offset 0x01C (R/ )  Program Counter Sample Register
            volatile uint32_t COMP0;        // Offset 0x020 (R/W)  Comparator Register 0
            volatile uint32_t MASK0;        // Offset 0x024 (R/W)  Mask Register 0
            volatile uint32_t FUNCTION0;    // Offset 0x028 (R/W)  Function Register 0
            volatile uint32_t _RESERVED_0;
            volatile uint32_t COMP1;        // Offset 0x030 (R/W)  Comparator Register 1
            volatile uint32_t MASK1;        // Offset 0x034 (R/W)  Mask Register 1
            volatile uint32_t FUNCTION1;    // Offset 0x038 (R/W)  Function Register 1
            volatile uint32_t _RESERVED_1;
            volatile uint32_t COMP2;        // Offset 0x040 (R/W)  Comparator Register 2
            volatile uint32_t MASK2;        // Offset 0x044 (R/W)  Mask Register 2
            volatile uint32_t FUNCTION2;    // Offset 0x048 (R/W)  Function Register 2
            volatile uint32_t _RESERVED_2;
            volatile uint32_t COMP3;        // Offset 0x050 (R/W)  Comparator Register 3
            volatile uint32_t MASK3;        // Offset 0x054 (R/W)  Mask Register 3
            volatile uint32_t FUNCTION3;    // Offset 0x058 (R/W)  Function Register 3
            volatile uint32_t _RESERVED_3;
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
        static constexpr uint32_t BASE_ADDRESS = 0xE0001000;
};


}   // namespace mcu
