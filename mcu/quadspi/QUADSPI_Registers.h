/**
 * @file        QUADSPI_Registers.h
 *
 * Register definitions for QUADSPI peripheral
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


class QUADSPI_Registers
{
    public:
        struct Block
        {
            Register32 CR;      // Control register                 Offset 0x00
            Register32 DCR;     // Device configuration register    Offset 0x04
            Register32 SR;      // Status register                  Offset 0x08
            Register32 FCR;     // Flag clear register              Offset 0x0C
            Register32 DLR;     // Data length register             Offset 0x10
            Register32 CCR;     // Communication config register    Offset 0x14
            Register32 AR;      // Address register                 Offset 0x18
            Register32 ABR;     // Alternate bytes register         Offset 0x1C
            Register32 DR;      // Data register                    Offset 0x20
            Register32 PSMKR;   // Polling status mask register     Offset 0x24
            Register32 PSMAR;   // Polling status match register    Offset 0x28
            Register32 PIR;     // Polling interval register        Offset 0x2C
            Register32 LPTR;    // Low-power timeout register       Offset 0x30
        } __attribute__((packed));

        struct CR
        {
            static const uint32_t EN            = 0;
            static const uint32_t ABORT         = 1;
            static const uint32_t DMAEN         = 2;
            static const uint32_t TCEN          = 3;
            static const uint32_t SSHIFT        = 4;
            static const uint32_t DFM           = 6;
            static const uint32_t FSEL          = 7;
            static const uint32_t FTHRES_0      = 8;
            static const uint32_t FTHRES_1      = 9;
            static const uint32_t FTHRES_2      = 10;
            static const uint32_t FTHRES_3      = 11;
            static const uint32_t TEIE          = 16;
            static const uint32_t TCIE          = 17;
            static const uint32_t FTIE          = 18;
            static const uint32_t SMIE          = 19;
            static const uint32_t TOIE          = 20;
            static const uint32_t APMS          = 22;
            static const uint32_t PMM           = 23;
            static const uint32_t PRESCALER_0   = 24;
            static const uint32_t PRESCALER_1   = 25;
            static const uint32_t PRESCALER_2   = 26;
            static const uint32_t PRESCALER_3   = 27;
            static const uint32_t PRESCALER_4   = 28;
            static const uint32_t PRESCALER_5   = 29;
            static const uint32_t PRESCALER_6   = 30;
            static const uint32_t PRESCALER_7   = 31;
        };

        struct DCR
        {
            static const uint32_t CKMODE        = 1;
            static const uint32_t CSHT_0        = 8;
            static const uint32_t CSHT_1        = 9;
            static const uint32_t CSHT_2        = 10;
            static const uint32_t FSIZE_0       = 16;
            static const uint32_t FSIZE_1       = 17;
            static const uint32_t FSIZE_2       = 18;
            static const uint32_t FSIZE_3       = 19;
            static const uint32_t FSIZE_4       = 20;
        };

        struct SR
        {
            static const uint32_t TEF           = 0;
            static const uint32_t TCF           = 1;
            static const uint32_t FTF           = 2;
            static const uint32_t SMF           = 3;
            static const uint32_t TOF           = 4;
            static const uint32_t BUSY          = 5;
            static const uint32_t FLEVEL_0      = 8;
            static const uint32_t FLEVEL_1      = 9;
            static const uint32_t FLEVEL_2      = 10;
            static const uint32_t FLEVEL_3      = 11;
            static const uint32_t FLEVEL_4      = 12;
        };

        struct FCR
        {
            static const uint32_t CTEF          = 0;
            static const uint32_t CTCF          = 1;
            static const uint32_t CSMF          = 3;
            static const uint32_t CTOF          = 4;
        };

        struct CCR
        {
            static const uint32_t INSTRUCTION_0 = 0;
            static const uint32_t INSTRUCTION_1 = 1;
            static const uint32_t INSTRUCTION_2 = 2;
            static const uint32_t INSTRUCTION_3 = 3;
            static const uint32_t INSTRUCTION_4 = 4;
            static const uint32_t INSTRUCTION_5 = 5;
            static const uint32_t INSTRUCTION_6 = 6;
            static const uint32_t INSTRUCTION_7 = 7;
            static const uint32_t IMODE_0       = 8;
            static const uint32_t IMODE_1       = 9;
            static const uint32_t ADMODE_0      = 10;
            static const uint32_t ADMODE_1      = 11;
            static const uint32_t ADSIZE_0      = 12;
            static const uint32_t ADSIZE_1      = 13;
            static const uint32_t ABMODE_0      = 14;
            static const uint32_t ABMODE_1      = 15;
            static const uint32_t ABSIZE_0      = 16;
            static const uint32_t ABSIZE_1      = 17;
            static const uint32_t DCYC_0        = 18;
            static const uint32_t DCYC_1        = 19;
            static const uint32_t DCYC_2        = 20;
            static const uint32_t DCYC_3        = 21;
            static const uint32_t DCYC_4        = 22;
            static const uint32_t DMODE_0       = 24;
            static const uint32_t DMODE_1       = 25;
            static const uint32_t FMODE_0       = 26;
            static const uint32_t FMODE_1       = 27;
            static const uint32_t SIOO          = 28;
            static const uint32_t DHHC          = 30;
            static const uint32_t DDRM          = 31;
        };

        /**
         * Return pointer to registers block
         *
         * @return          Pointer to registers
         */
        static constexpr Block* get()
        {
            return (Block*)QUADSPI_BASE_ADDRESS;
        }

    protected:
        // Register base address
        static const uint32_t QUADSPI_BASE_ADDRESS = 0xA0001000;
};


}   // namespace mcu
