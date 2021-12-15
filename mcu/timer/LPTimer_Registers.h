/**
 * @file        LPTimer_Registers.h
 *
 * Register definitions for low power timer peripherals on STM32L4xx
 *
 * @author:     Oliver Rockstedt <info@sourcebox.de>
 * @license     MIT
 */


#pragma once


// Local includes
#include "LPTimer_Base.h"

// This component
#include "../core/mcu_base.h"
#include "../utility/register.h"

// System libraries
#include <cstdint>


namespace mcu {


class LPTimer_Registers : LPTimer_Base
{
    public:
        struct Block
        {
            Register32 ISR;     // Interrupt and status register    Offset 0x00
            Register32 ICR;     // Interrupt clear register         Offset 0x04
            Register32 IER;     // Interrupt enable register        Offset 0x08
            Register32 CFGR;    // Configuration register           Offset 0x0C
            Register32 CR;      // Control register                 Offset 0x10
            Register32 CMP;     // Compare register                 Offset 0x14
            Register32 ARR;     // Auto-reload register             Offset 0x18
            Register32 CNT;     // Counter register                 Offset 0x1C
            Register32 OR;      // Option register                  Offset 0x20
            Register32 CFGR2;   // Configuration register 2         Offset 0x24
            Register32 RCR;     // Repetition register              Offset 0x28
        } __attribute__((packed));

        struct ISR
        {
            static const uint32_t CMPM      = 0;
            static const uint32_t ARRM      = 1;
            static const uint32_t EXTTRIG   = 2;
            static const uint32_t CMPOK     = 3;
            static const uint32_t ARROK     = 4;
            static const uint32_t UP        = 5;
            static const uint32_t DOWM      = 6;
            static const uint32_t UE        = 7;
            static const uint32_t REPOK     = 8;
        };

        struct ICR
        {
            static const uint32_t CMPMCF    = 0;
            static const uint32_t ARRMCF    = 1;
            static const uint32_t EXTTRIGCF = 2;
            static const uint32_t CMPOKCF   = 3;
            static const uint32_t ARROKCF   = 4;
            static const uint32_t UPCF      = 5;
            static const uint32_t DOWNCF    = 6;
            static const uint32_t UECF      = 7;
            static const uint32_t REPOKCF   = 8;
        };

        struct IER
        {
            static const uint32_t CMPMIE    = 0;
            static const uint32_t ARRMIE    = 1;
            static const uint32_t EXTTRIGIE = 2;
            static const uint32_t CMPOKIE   = 3;
            static const uint32_t ARROKIE   = 4;
            static const uint32_t UPIE      = 5;
            static const uint32_t DOWNIE    = 6;
            static const uint32_t UEIE      = 7;
            static const uint32_t REPOKIE   = 8;
        };

        struct CFGR
        {
            static const uint32_t CKSEL     = 0;
            static const uint32_t CKPOL_0   = 1;
            static const uint32_t CKPOL_1   = 2;
            static const uint32_t CKFLT_0   = 3;
            static const uint32_t CKFLT_1   = 4;
            static const uint32_t TRGFLT_0  = 6;
            static const uint32_t TRGFLT_1  = 7;
            static const uint32_t PRESC_0   = 9;
            static const uint32_t PRESC_1   = 10;
            static const uint32_t PRESC_2   = 11;
            static const uint32_t TRIGSEL_0 = 13;
            static const uint32_t TRIGSEL_1 = 14;
            static const uint32_t TRIGSEL_2 = 15;
            static const uint32_t TRIGEN_0  = 17;
            static const uint32_t TRIGEN_1  = 18;
            static const uint32_t TIMOUT    = 19;
            static const uint32_t WAVE      = 20;
            static const uint32_t WAVPOL    = 21;
            static const uint32_t PRELOAD   = 22;
            static const uint32_t COUNTMODE = 23;
            static const uint32_t ENC       = 24;
        };

        struct CR
        {
            static const uint32_t ENABLE    = 0;
            static const uint32_t SNGSTRT   = 1;
            static const uint32_t CNTSTRT   = 2;
            static const uint32_t CNTRST    = 3;
            static const uint32_t RSTARE    = 4;
        };

        struct OR
        {
            static const uint32_t OR_0      = 0;
            static const uint32_t OR_1      = 1;
        };

        struct CFGR2
        {
            static const uint32_t IN1SEL_0  = 0;
            static const uint32_t IN1SEL_1  = 1;
            static const uint32_t IN2SEL_0  = 4;
            static const uint32_t IN2SEL_1  = 5;
        };

        /**
         * Return pointer to registers block
         *
         * @param id        Peripheral id
         * @return          Pointer to registers
         */
        static constexpr Block* get(Id id)
        {
            switch (id) {
                case Id::LPTIM1:
                    return (Block*)LPTIM1_BASE_ADDRESS;
                case Id::LPTIM2:
                    return (Block*)LPTIM2_BASE_ADDRESS;
            }

            return nullptr;
        }

    protected:
        // Register block base addresses
        static const uint32_t LPTIM1_BASE_ADDRESS = APB1_BASE_ADDRESS + 0x00007C00;
        static const uint32_t LPTIM2_BASE_ADDRESS = APB1_BASE_ADDRESS + 0x00009400;
};


}   // namespace mcu
