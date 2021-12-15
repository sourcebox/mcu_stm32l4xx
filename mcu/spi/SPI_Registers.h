/**
 * @file        SPI_Registers.h
 *
 * Register definitions for SPI peripherals
 *
 * @author:     Oliver Rockstedt <info@sourcebox.de>
 * @license     MIT
 */


#pragma once


// Local includes
#include "SPI_Base.h"

// This component
#include "../core/mcu_base.h"
#include "../utility/register.h"

// System libraries
#include <cstdint>


namespace mcu {


class SPI_Registers : public SPI_Base
{
    public:
        struct Block
        {
            Register32 CR1;     // Control register 1               Offset 0x00
            Register32 CR2;     // Control register 2               Offset 0x04
            Register32 SR;      // Status register                  Offset 0x08
            Register32 DR;      // Data register                    Offset 0x0C
            Register32 CRCPR;   // CRC polynomial register          Offset 0x10
            Register32 RXCRCR;  // RX CRC register                  Offset 0x14
            Register32 TXCRCR;  // TX CRC register                  Offset 0x18
        } __attribute__((packed));

        struct CR1
        {
            static const uint32_t CPHA      = 0;
            static const uint32_t CPOL      = 1;
            static const uint32_t MSTR      = 2;
            static const uint32_t BR_0      = 3;
            static const uint32_t BR_1      = 4;
            static const uint32_t BR_2      = 5;
            static const uint32_t SPE       = 6;
            static const uint32_t LSBFIRST  = 7;
            static const uint32_t SSI       = 8;
            static const uint32_t SSM       = 9;
            static const uint32_t RXONLY    = 10;
            static const uint32_t CRCL      = 11;
            static const uint32_t CRCNEX    = 12;
            static const uint32_t CRCEN     = 13;
            static const uint32_t BIDIOE    = 14;
            static const uint32_t BIDIMODE  = 15;
        };

        struct CR2
        {
            static const uint32_t RXDMAEN   = 0;
            static const uint32_t TXDMAEN   = 1;
            static const uint32_t SSOE      = 2;
            static const uint32_t NSSP      = 3;
            static const uint32_t FRF       = 4;
            static const uint32_t ERRIE     = 5;
            static const uint32_t RXNEIE    = 6;
            static const uint32_t TXEIE     = 7;
            static const uint32_t DS_0      = 8;
            static const uint32_t DS_1      = 9;
            static const uint32_t DS_2      = 10;
            static const uint32_t DS_3      = 11;
            static const uint32_t FRXTH     = 12;
            static const uint32_t LDMA_RX   = 13;
            static const uint32_t LDMA_TX   = 14;
        };

        struct SR
        {
            static const uint32_t RXNE      = 0;
            static const uint32_t TXE       = 1;
            static const uint32_t CHSIDE    = 2;
            static const uint32_t UDR       = 3;
            static const uint32_t CRCERR    = 4;
            static const uint32_t MODF      = 5;
            static const uint32_t OVR       = 6;
            static const uint32_t BSY       = 7;
            static const uint32_t FRE       = 8;
            static const uint32_t FRLVL_0   = 9;
            static const uint32_t FRLVL_1   = 10;
            static const uint32_t FTLVL_0   = 11;
            static const uint32_t FTLVL_1   = 12;
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
                case Id::SPI1:
                    return (Block*)SPI1_BASE_ADDRESS;
                case Id::SPI2:
                    return (Block*)SPI2_BASE_ADDRESS;
                case Id::SPI3:
                    return (Block*)SPI3_BASE_ADDRESS;
            }

            return nullptr;
        }

    protected:
        // Register base addresses
        static const uint32_t SPI1_BASE_ADDRESS = APB2_BASE_ADDRESS + 0x00003000;
        static const uint32_t SPI2_BASE_ADDRESS = APB1_BASE_ADDRESS + 0x00003800;
        static const uint32_t SPI3_BASE_ADDRESS = APB1_BASE_ADDRESS + 0x00003C00;
};


}   // namespace mcu
