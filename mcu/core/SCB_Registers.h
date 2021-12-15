/**
 * @file        SCB_Registers.h
 *
 * Register definitions for System Control Block on Cortex-M4
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


class SCB_Registers
{
    public:
        struct Block
        {
            volatile const uint32_t CPUID;      // Offset 0x000 (R/ )  CPUID Base Register
            volatile uint32_t ICSR;             // Offset 0x004 (R/W)  Interrupt Control and State Register
            volatile uint32_t VTOR;             // Offset 0x008 (R/W)  Vector Table Offset Register
            volatile uint32_t AIRCR;            // Offset 0x00C (R/W)  Application Interrupt and Reset Control Register
            volatile uint32_t SCR;              // Offset 0x010 (R/W)  System Control Register
            volatile uint32_t CCR;              // Offset 0x014 (R/W)  Configuration Control Register
            volatile uint8_t  SHP[12];          // Offset 0x018 (R/W)  System Handlers Priority Registers (4-7, 8-11, 12-15)
            volatile uint32_t SHCSR;            // Offset 0x024 (R/W)  System Handler Control and State Register
            volatile uint32_t CFSR;             // Offset 0x028 (R/W)  Configurable Fault Status Register
            volatile uint32_t HFSR;             // Offset 0x02C (R/W)  HardFault Status Register
            volatile uint32_t DFSR;             // Offset 0x030 (R/W)  Debug Fault Status Register
            volatile uint32_t MMFAR;            // Offset 0x034 (R/W)  MemManage Fault Address Register
            volatile uint32_t BFAR;             // Offset 0x038 (R/W)  BusFault Address Register
            volatile uint32_t AFSR;             // Offset 0x03C (R/W)  Auxiliary Fault Status Register
            volatile const uint32_t PFR[2];     // Offset 0x040 (R/ )  Processor Feature Register
            volatile const uint32_t DFR;        // Offset 0x048 (R/ )  Debug Feature Register
            volatile const uint32_t ADR;        // Offset 0x04C (R/ )  Auxiliary Feature Register
            volatile const uint32_t MMFR[4];    // Offset 0x050 (R/ )  Memory Model Feature Register
            volatile const uint32_t ISAR[5];    // Offset 0x060 (R/ )  Instruction Set Attributes Register
            uint32_t RESERVED0[5];
            volatile uint32_t CPACR;            // Offset 0x088 (R/W)  Coprocessor Access Control Register
        } __attribute__((packed));

        struct AIRCR
        {
            static const uint32_t PRIGROUP  = 8;
            static const uint32_t VECTKEY   = 16;
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
        static constexpr uint32_t BASE_ADDRESS = SCS_BASE_ADDRESS +  0x0D00;
};


}   // namespace mcu
