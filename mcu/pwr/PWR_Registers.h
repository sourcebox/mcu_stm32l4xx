/**
 * @file        PWR_Registers.h
 *
 * Register definitions for PWR peripheral on STM32L4xx
 *
 * @author:     Oliver Rockstedt <info@sourcebox.de>
 * @license     MIT
 */


#pragma once


// This component
#include "../core/mcu_base.h"
#include "../utility/register.h"

// System libraries
#include <cstdint>


namespace mcu {


class PWR_Registers
{
    public:
        struct Block
        {
            Register32 CR1;     // Power control register 1             Offset 0x00
            Register32 CR2;     // Power control register 2             Offset 0x04
            Register32 CR3;     // Power control register 3             Offset 0x08
            Register32 CR4;     // Power control register 4             Offset 0x0C
            Register32 SR1;     // Power status register 1              Offset 0x10
            Register32 SR2;     // Power status register 2              Offset 0x14
            Register32 SCR;     // Power status clear register          Offset 0x18
            Register32 _RESERVED_1;     // Reserved                     Offset 0x1C
            Register32 PUCRA;   // Port A pullup control register       Offset 0x20
            Register32 PDCRA;   // Port A pulldown control register     Offset 0x24
            Register32 PUCRB;   // Port B pullup control register       Offset 0x28
            Register32 PDCRB;   // Port B pulldown control register     Offset 0x2C
            Register32 PUCRC;   // Port C pullup control register       Offset 0x30
            Register32 PDCRC;   // Port C pulldown control register     Offset 0x34
            Register32 PUCRD;   // Port D pullup control register       Offset 0x38
            Register32 PDCRD;   // Port D pulldown control register     Offset 0x3C
            Register32 PUCRE;   // Port E pullup control register       Offset 0x40
            Register32 PDCRE;   // Port E pulldown control register     Offset 0x44
            Register32 _RESERVED_2[4];  // Reserved
            Register32 PUCRH;   // Port H pullup control register       Offset 0x58
            Register32 PDCRH;   // Port H pulldown control register     Offset 0x5C
        } __attribute__((packed));

        struct CR1
        {
            static const uint32_t LPMS_0    = 0;
            static const uint32_t LPMS_1    = 1;
            static const uint32_t DBP       = 8;
            static const uint32_t VOS_0     = 9;
            static const uint32_t VOS_1     = 10;
            static const uint32_t LPR       = 14;
        };

        struct CR2
        {
            static const uint32_t PVDE      = 0;
            static const uint32_t PLS_0     = 1;
            static const uint32_t PLS_1     = 2;
            static const uint32_t PLS_2     = 3;
            static const uint32_t PVME1     = 4;
            static const uint32_t PVME3     = 6;
            static const uint32_t PVME4     = 7;
            static const uint32_t USV       = 10;
        };

        struct CR3
        {
            static const uint32_t EWUP1         = 0;
            static const uint32_t EWUP2         = 1;
            static const uint32_t EWUP3         = 2;
            static const uint32_t EWUP4         = 3;
            static const uint32_t EWUP5         = 4;
            static const uint32_t RRS           = 8;
            static const uint32_t APC           = 10;
            static const uint32_t ENULP         = 11;
            static const uint32_t EIWUL         = 15;
        };

        struct CR4
        {
            static const uint32_t WP1           = 0;
            static const uint32_t WP2           = 1;
            static const uint32_t WP3           = 2;
            static const uint32_t WP4           = 3;
            static const uint32_t WP5           = 4;
            static const uint32_t VBE           = 8;
            static const uint32_t VBRS          = 9;
            static const uint32_t EXT_SMPS_ON   = 13;
        };

        struct SR1
        {
            static const uint32_t WUF1          = 0;
            static const uint32_t WUF2          = 1;
            static const uint32_t WUF3          = 2;
            static const uint32_t WUF4          = 3;
            static const uint32_t WUF5          = 4;
            static const uint32_t SBF           = 8;
            static const uint32_t EXT_SMPS_RDY  = 13;
            static const uint32_t WUFI          = 15;
        };

        struct SR2
        {
            static const uint32_t REGLPS        = 8;
            static const uint32_t REGLPF        = 9;
            static const uint32_t VOSF          = 10;
            static const uint32_t PVDO          = 11;
            static const uint32_t PVMO1         = 12;
            static const uint32_t PVMO3         = 14;
            static const uint32_t PVMO4         = 15;
        };

        struct SCR
        {
            static const uint32_t CWUF1         = 0;
            static const uint32_t CWUF2         = 1;
            static const uint32_t CWUF3         = 2;
            static const uint32_t CWUF4         = 3;
            static const uint32_t CWUF5         = 4;
            static const uint32_t CSBF          = 8;
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
        static const uint32_t BASE_ADDRESS = APB1_BASE_ADDRESS + 0x00007000;
};


}   // namespace mcu
