/**
 * @file        USB_Registers.h
 *
 * Register definitions for USB peripheral on STM32L4xx
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


class USB_Registers
{
    public:
        struct Block
        {
            Register32 EP0R;    // Endpoint 0 register              Offset 0x00
            Register32 EP1R;    // Endpoint 1 register              Offset 0x04
            Register32 EP2R;    // Endpoint 2 register              Offset 0x08
            Register32 EP3R;    // Endpoint 3 register              Offset 0x0C
            Register32 EP4R;    // Endpoint 4 register              Offset 0x10
            Register32 EP5R;    // Endpoint 5 register              Offset 0x14
            Register32 EP6R;    // Endpoint 6 register              Offset 0x18
            Register32 EP7R;    // Endpoint 7 register              Offset 0x1C
            Register32 _RESERVED_1[8];  // Reserved                 Offset 0x20..0x3F
            Register32 CNTR;    // Control register                 Offset 0x40
            Register32 ISTR;    // Interrupt status register        Offset 0x44
            Register32 FNR;     // Frame number register            Offset 0x48
            Register32 DADDR;   // Device address                   Offset 0x4C
            Register32 BTABLE;  // Buffer table address             Offset 0x50
            Register32 LPMCSR;  // LPM control and status register  Offset 0x54
            Register32 BCDR;    // Battery charger detector         Offset 0x58
        } __attribute__((packed));

        struct EPnR
        {
            static const uint32_t EA_0          = 0;
            static const uint32_t EA_1          = 1;
            static const uint32_t EA_2          = 2;
            static const uint32_t EA_3          = 3;
            static const uint32_t STAT_TX_0     = 4;
            static const uint32_t STAT_TX_1     = 5;
            static const uint32_t DTOG_TX       = 6;
            static const uint32_t CTR_TX        = 7;
            static const uint32_t EP_KIND       = 8;
            static const uint32_t EP_TYPE_0     = 9;
            static const uint32_t EP_TYPE_1     = 10;
            static const uint32_t SETUP         = 11;
            static const uint32_t STAT_RX_0     = 12;
            static const uint32_t STAT_RX_1     = 13;
            static const uint32_t DTOG_RX       = 14;
            static const uint32_t CTR_RX        = 15;

            // Mask for STAT_TX bits
            static const uint32_t STAT_TX_MASK = (
                (1 << EPnR::STAT_TX_0)
                | (1 << EPnR::STAT_TX_1)
            );

            // Mask for STAT_RX bits
            static const uint32_t STAT_RX_MASK = (
                (1 << EPnR::STAT_RX_0)
                | (1 << EPnR::STAT_RX_1)
            );

            // Bit mask for all write 0 bits
            static const uint32_t RC_W0_MASK = (
                (1 << EPnR::CTR_TX)
                | (1 << EPnR::CTR_RX)
            );

            // Bit mask for all toggle bits
            static const uint32_t TOGGLE_MASK = (
                STAT_TX_MASK
                | (1 << EPnR::DTOG_TX)
                | STAT_RX_MASK
                | (1 << EPnR::DTOG_RX)
            );
        };

        struct CNTR
        {
            static const uint32_t FRES          = 0;
            static const uint32_t PDWN          = 1;
            static const uint32_t LP_MODE       = 2;
            static const uint32_t FSUSP         = 3;
            static const uint32_t RESUME        = 4;
            static const uint32_t L1RESUME      = 5;
            static const uint32_t L1REQM        = 7;
            static const uint32_t ESOFM         = 8;
            static const uint32_t SOFM          = 9;
            static const uint32_t RESETM        = 10;
            static const uint32_t SUSPM         = 11;
            static const uint32_t WKUPM         = 12;
            static const uint32_t ERRM          = 13;
            static const uint32_t PMAOVRM       = 14;
            static const uint32_t CTRM          = 15;
        };

        struct ISTR
        {
            static const uint32_t EP_ID_0       = 0;
            static const uint32_t EP_ID_1       = 1;
            static const uint32_t EP_ID_2       = 2;
            static const uint32_t EP_ID_3       = 3;
            static const uint32_t DIR           = 4;
            static const uint32_t L1REQ         = 7;
            static const uint32_t ESOF          = 8;
            static const uint32_t SOF           = 9;
            static const uint32_t RESET         = 10;
            static const uint32_t SUSP          = 11;
            static const uint32_t WKUP          = 12;
            static const uint32_t ERR           = 13;
            static const uint32_t PMAOVR        = 14;
            static const uint32_t CTR           = 15;
        };

        struct FNR
        {
            static const uint32_t FN_0          = 0;
            static const uint32_t FN_1          = 1;
            static const uint32_t FN_2          = 2;
            static const uint32_t FN_3          = 3;
            static const uint32_t FN_4          = 4;
            static const uint32_t FN_5          = 5;
            static const uint32_t FN_6          = 6;
            static const uint32_t FN_7          = 7;
            static const uint32_t FN_8          = 8;
            static const uint32_t FN_9          = 9;
            static const uint32_t FN_10         = 10;
            static const uint32_t LSOF_0        = 11;
            static const uint32_t LSOF_1        = 12;
            static const uint32_t LCK           = 13;
            static const uint32_t RXDM          = 14;
            static const uint32_t RXDP          = 15;
        };

        struct DADDR
        {
            static const uint32_t ADD_0         = 0;
            static const uint32_t ADD_1         = 1;
            static const uint32_t ADD_2         = 2;
            static const uint32_t ADD_3         = 3;
            static const uint32_t ADD_4         = 4;
            static const uint32_t ADD_5         = 5;
            static const uint32_t ADD_6         = 6;
            static const uint32_t EF            = 7;
        };

        struct BTABLE
        {
            static const uint32_t BTABLE_3      = 3;
            static const uint32_t BTABLE_4      = 4;
            static const uint32_t BTABLE_5      = 5;
            static const uint32_t BTABLE_6      = 6;
            static const uint32_t BTABLE_7      = 7;
            static const uint32_t BTABLE_8      = 8;
            static const uint32_t BTABLE_9      = 9;
            static const uint32_t BTABLE_10     = 10;
            static const uint32_t BTABLE_11     = 11;
            static const uint32_t BTABLE_12     = 12;
            static const uint32_t BTABLE_13     = 13;
            static const uint32_t BTABLE_14     = 14;
            static const uint32_t BTABLE_15     = 15;
        };

        struct LPMCSR
        {
            static const uint32_t LPMEN         = 0;
            static const uint32_t LPMACK        = 1;
            static const uint32_t REMWAKE       = 3;
            static const uint32_t BESL_0        = 4;
            static const uint32_t BESL_1        = 5;
            static const uint32_t BESL_2        = 6;
            static const uint32_t BESL_3        = 7;
        };

        struct BCDR
        {
            static const uint32_t BCDEN         = 0;
            static const uint32_t DCDEN         = 1;
            static const uint32_t PDEN          = 2;
            static const uint32_t SDEN          = 3;
            static const uint32_t DCDET         = 4;
            static const uint32_t PDET          = 5;
            static const uint32_t SDET          = 6;
            static const uint32_t PS2DET        = 7;
            static const uint32_t DPPU          = 15;
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
        static constexpr uint32_t BASE_ADDRESS = APB1_BASE_ADDRESS + 0x00006800;
};


}   // namespace mcu
