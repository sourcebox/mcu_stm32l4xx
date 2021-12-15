/**
 * @file        Flash_Registers.h
 *
 * Register definitions for embedded flash memory on STM32L4xx
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


class Flash_Registers
{
    public:
        struct Block
        {
            Register32 ACR;         // Flash access control register    Offset 0x00
            Register32 PDKEYR;      // Flash Power-down key register    Offset 0x04
            Register32 KEYR;        // Flash key register               Offset 0x08
            Register32 OPTKEYR;     // Flash option key register        Offset 0x0C
            Register32 SR;          // Flash status register            Offset 0x10
            Register32 CR;          // Flash control register           Offset 0x14
            Register32 ECCR;        // Flash ECC register               Offset 0x18
            Register32 _RESERVED_1; //                                  Offset 0x1C
            Register32 OPTR;        // Flash option register            Offset 0x20
            Register32 PCROP1SR;    // Flash PCROP Start address reg    Offset 0x24
            Register32 PCROP1ER;    // Flash PCROP End address register Offset 0x28
            Register32 WRP1AR;      // Flash WRP area A address reg     Offset 0x2C
            Register32 WRP1BR;      // Flash WRP area B address reg     Offset 0x30
        } __attribute__((packed));

        struct ACR
        {
            static const uint32_t LATENCY_0    = 0;
            static const uint32_t LATENCY_1    = 1;
            static const uint32_t LATENCY_2    = 2;
            static const uint32_t PRFTEN       = 8;
            static const uint32_t ICEN         = 9;
            static const uint32_t DCEN         = 10;
            static const uint32_t ICRST        = 11;
            static const uint32_t DCRST        = 12;
            static const uint32_t RUN_PD       = 13;
            static const uint32_t SLEEP_PD     = 14;
        };

        struct SR
        {
            static const uint32_t EOP          = 0;
            static const uint32_t OPERR        = 1;
            static const uint32_t PROGERR      = 3;
            static const uint32_t WRPERR       = 4;
            static const uint32_t PGAERR       = 5;
            static const uint32_t SIZERR       = 6;
            static const uint32_t PGSERR       = 7;
            static const uint32_t MISSERR      = 8;
            static const uint32_t FASTERR      = 9;
            static const uint32_t RDERR        = 14;
            static const uint32_t OPTVERR      = 15;
            static const uint32_t BSY          = 16;
            static const uint32_t PEMPTY       = 17;
        };

        struct CR
        {
            static const uint32_t PG           = 0;
            static const uint32_t PER          = 1;
            static const uint32_t MER1         = 2;
            static const uint32_t PNB_0        = 3;
            static const uint32_t PNB_1        = 4;
            static const uint32_t PNB_2        = 5;
            static const uint32_t PNB_3        = 6;
            static const uint32_t PNB_4        = 7;
            static const uint32_t PNB_5        = 8;
            static const uint32_t PNB_6        = 9;
            static const uint32_t PNB_7        = 10;
            static const uint32_t STRT         = 16;
            static const uint32_t OPTSTRT      = 17;
            static const uint32_t FSTPG        = 18;
            static const uint32_t EOPIE        = 24;
            static const uint32_t ERRIE        = 25;
            static const uint32_t RDERRIE      = 26;
            static const uint32_t OBL_LAUNCH   = 27;
            static const uint32_t OPTLOCK      = 30;
            static const uint32_t LOCK         = 31;
        };

        struct ECCR
        {
            static const uint32_t SYSF_ECC     = 20;
            static const uint32_t ECCCIE       = 24;
            static const uint32_t ECCC         = 30;
            static const uint32_t ECCD         = 31;
        };

        struct OPTR
        {
            static const uint32_t RDP_0        = 0;
            static const uint32_t RDP_1        = 1;
            static const uint32_t RDP_2        = 2;
            static const uint32_t RDP_3        = 3;
            static const uint32_t RDP_4        = 4;
            static const uint32_t RDP_5        = 5;
            static const uint32_t RDP_6        = 6;
            static const uint32_t RDP_7        = 7;
            static const uint32_t BOR_LEV_0    = 8;
            static const uint32_t BOR_LEV_1    = 9;
            static const uint32_t BOR_LEV_2    = 10;
            static const uint32_t nRST_STOP    = 12;
            static const uint32_t nRST_STDBY   = 13;
            static const uint32_t nRST_SHDW    = 14;
            static const uint32_t IWDG_SW      = 16;
            static const uint32_t IWDG_STOP    = 17;
            static const uint32_t IWDG_STDBY   = 18;
            static const uint32_t WWDG_SW      = 19;
            static const uint32_t nBOOT1       = 23;
            static const uint32_t SRAM2_PE     = 24;
            static const uint32_t SRAM2_RST    = 25;
            static const uint32_t nSW_BOOT0    = 26;
            static const uint32_t nBOOT0       = 27;
        };

        struct PCROP1ER
        {
            static const uint32_t PCROP_RDP    = 31;
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
        static const uint32_t BASE_ADDRESS = AHB1_BASE_ADDRESS + 0x00002000;
};


}   // namespace mcu
