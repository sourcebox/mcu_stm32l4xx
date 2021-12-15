/**
 * @file        SDMMC_Registers.h
 *
 * Register definitions for SDMMC peripheral on STM32L4xx
 *
 * @author:     Oliver Rockstedt <info@sourcebox.de>
 * @license     MIT
 */


#pragma once


// Local includes
#include "SDMMC_Base.h"

// This component
#include "../core/mcu_base.h"
#include "../utility/register.h"

// System libraries
#include <cstdint>


namespace mcu {


class SDMMC_Registers : public SDMMC_Base
{
    public:
        struct Block
        {
            Register32 POWER;   // Power control register           Offset 0x00
            Register32 CLKCR;   // Clock control register           Offset 0x04
            Register32 ARG;     // Argument register                Offset 0x08
            Register32 CMD;     // Command register                 Offset 0x0C
            Register32 RESPCMD; // Command response register        Offset 0x10
            Register32 RESP1;   // Response 1 register              Offset 0x14
            Register32 RESP2;   // Response 2 register              Offset 0x18
            Register32 RESP3;   // Response 3 register              Offset 0x1C
            Register32 RESP4;   // Response 4 register              Offset 0x20
            Register32 DTIMER;  // Data timer register              Offset 0x24
            Register32 DLEN;    // Data length register             Offset 0x28
            Register32 DCTRL;   // Data control register            Offset 0x2C
            Register32 DCOUNT;  // Data counter register            Offset 0x30
            Register32 STA;     // Status register                  Offset 0x34
            Register32 ICR;     // Interrupt clear register         Offset 0x38
            Register32 MASK;    // Mask register                    Offset 0x3C
            Register32 _RESERVED_1[2];  // Reserved
            Register32 FIFOCNT; // FIFO counter register            Offset 0x48
            Register32 _RESERVED_2[13];  // Reserved
            Register32 FIFO;    // Data FIFO register               Offset 0x80
        } __attribute__((packed));

        struct POWER
        {
            static const uint32_t PWRCTL_0      = 0;
            static const uint32_t PWRCTL_1      = 1;
        };

        struct CLKCR
        {
            static const uint32_t CLKDIV_0      = 0;
            static const uint32_t CLKDIV_1      = 1;
            static const uint32_t CLKDIV_2      = 2;
            static const uint32_t CLKDIV_3      = 3;
            static const uint32_t CLKDIV_4      = 4;
            static const uint32_t CLKDIV_5      = 5;
            static const uint32_t CLKDIV_6      = 6;
            static const uint32_t CLKDIV_7      = 7;
            static const uint32_t CLKEN         = 8;
            static const uint32_t PWRSAV        = 9;
            static const uint32_t BYPASS        = 10;
            static const uint32_t WIDBUS_0      = 11;
            static const uint32_t WIDBUS_1      = 12;
            static const uint32_t NEGEDGE       = 13;
            static const uint32_t HWFC_EN       = 14;
        };

        struct CMD
        {
            static const uint32_t CMDINDEX_0    = 0;
            static const uint32_t CMDINDEX_1    = 1;
            static const uint32_t CMDINDEX_2    = 2;
            static const uint32_t CMDINDEX_3    = 3;
            static const uint32_t CMDINDEX_4    = 4;
            static const uint32_t CMDINDEX_5    = 5;
            static const uint32_t WAITRESP_0    = 6;
            static const uint32_t WAITRESP_1    = 7;
            static const uint32_t WAITINT       = 8;
            static const uint32_t WAITPEND      = 9;
            static const uint32_t CPSMEN        = 10;
            static const uint32_t SDIOSuspend   = 11;
        };

        struct DCTRL
        {
            static const uint32_t DTEN          = 0;
            static const uint32_t DTDIR         = 1;
            static const uint32_t DTMODE        = 2;
            static const uint32_t DMAEN         = 3;
            static const uint32_t DBLOCKSIZE_0  = 4;
            static const uint32_t DBLOCKSIZE_1  = 5;
            static const uint32_t DBLOCKSIZE_2  = 6;
            static const uint32_t DBLOCKSIZE_3  = 7;
            static const uint32_t RWSTART       = 8;
            static const uint32_t RWSTOP        = 9;
            static const uint32_t RWMOD         = 10;
            static const uint32_t SDIOEN        = 11;
        };

        struct STA
        {
            static const uint32_t CCRCFAIL      = 0;
            static const uint32_t DCRCFAIL      = 1;
            static const uint32_t CTIMEOUT      = 2;
            static const uint32_t DTIMEOUT      = 3;
            static const uint32_t TXUNDERR      = 4;
            static const uint32_t RXOVERR       = 5;
            static const uint32_t CMDREND       = 6;
            static const uint32_t CMDSENT       = 7;
            static const uint32_t DATAEND       = 8;
            static const uint32_t DBCKEND       = 10;
            static const uint32_t CMDACT        = 11;
            static const uint32_t TXACT         = 12;
            static const uint32_t RXACT         = 13;
            static const uint32_t TXFIFOHE      = 14;
            static const uint32_t RXFIFOHF      = 15;
            static const uint32_t TXFIFOF       = 16;
            static const uint32_t RXFIFOF       = 17;
            static const uint32_t TXFIFOE       = 18;
            static const uint32_t RXFIFOE       = 19;
            static const uint32_t TXDAVL        = 20;
            static const uint32_t RXDAVL        = 21;
            static const uint32_t SDIOIT        = 22;
        };

        struct ICR
        {
            static const uint32_t CCRCFAILC     = 0;
            static const uint32_t DCRCFAILC     = 1;
            static const uint32_t CTIMEOUTC     = 2;
            static const uint32_t DTIMEOUTC     = 3;
            static const uint32_t TXUNDERRC     = 4;
            static const uint32_t RXOVERRC      = 5;
            static const uint32_t CMDRENDC      = 6;
            static const uint32_t CMDSENTC      = 7;
            static const uint32_t DATAENDC      = 8;
            static const uint32_t DBCKENDC      = 10;
            static const uint32_t SDIOITC       = 22;
        };

        struct MASK
        {
            static const uint32_t CCRCFAILIE    = 0;
            static const uint32_t DCRCFAILIE    = 1;
            static const uint32_t CTIMEOUTIE    = 2;
            static const uint32_t DTIMEOUTIE    = 3;
            static const uint32_t TXUNDERRIE    = 4;
            static const uint32_t RXOVERRIE     = 5;
            static const uint32_t CMDRENDIE     = 6;
            static const uint32_t CMDSENTIE     = 7;
            static const uint32_t DATAENDIE     = 8;
            static const uint32_t DBCKENDIE     = 10;
            static const uint32_t CMDACTIE      = 11;
            static const uint32_t TXACTIE       = 12;
            static const uint32_t RXACTIE       = 13;
            static const uint32_t TXFIFOHEIE    = 14;
            static const uint32_t RXFIFOHFIE    = 15;
            static const uint32_t FXFIFOFIE     = 16;
            static const uint32_t RXFIFOFIE     = 17;
            static const uint32_t TXFIFOEIE     = 18;
            static const uint32_t RXFIFOEIE     = 19;
            static const uint32_t TXAVLIE       = 20;
            static const uint32_t RXAVLIE       = 21;
            static const uint32_t SDIOITIE      = 22;
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
                case Id::SDMMC1:
                    return (Block*)SDMMC1_BASE_ADDRESS;
            }

            return nullptr;
        }

    protected:
        // Register block base address
        static const uint32_t SDMMC1_BASE_ADDRESS = APB2_BASE_ADDRESS + 0x00002800;
};


}   // namespace mcu
