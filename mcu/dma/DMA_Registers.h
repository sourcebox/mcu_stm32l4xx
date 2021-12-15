/**
 * @file        DMA_Registers.h
 *
 * Register definitions for DMA controller on STM32L4xx
 *
 * @author:     Oliver Rockstedt <info@sourcebox.de>
 * @license     MIT
 */


#pragma once


// Local includes
#include "DMA_Base.h"

// This component
#include "../core/mcu_base.h"
#include "../utility/register.h"

// System libraries
#include <cstdint>


namespace mcu {


class DMA_Registers : public DMA_Base
{
    public:
        struct Block
        {
            Register32 ISR;     // Interrupt status register        Offset 0x00
            Register32 IFCR;    // Interrupt flag clear register    Offset 0x04
            Register32 CCR1;    // Ch 1 configuration register      Offset 0x08
            Register32 CNDTR1;  // Ch 1 no of data to transfer reg  Offset 0x0C
            Register32 CPAR1;   // Ch 1 peripheral address reg      Offset 0x10
            Register32 CMAR1;   // Ch 1 memory address register     Offset 0x14
            Register32 _RESERVED_1; // Ch 1 reserved                Offset 0x18
            Register32 CCR2;    // Ch 2 configuration register      Offset 0x1C
            Register32 CNDTR2;  // Ch 2 no of data to transfer reg  Offset 0x20
            Register32 CPAR2;   // Ch 2 peripheral address reg      Offset 0x24
            Register32 CMAR2;   // Ch 2 memory address register     Offset 0x28
            Register32 _RESERVED_2; // Ch 2 reserved                Offset 0x2C
            Register32 CCR3;    // Ch 3 configuration register      Offset 0x30
            Register32 CNDTR3;  // Ch 3 no of data to transfer reg  Offset 0x34
            Register32 CPAR3;   // Ch 3 peripheral address reg      Offset 0x38
            Register32 CMAR3;   // Ch 3 memory address register     Offset 0x3C
            Register32 _RESERVED_3; // Ch 3 reserved                Offset 0x40
            Register32 CCR4;    // Ch 4 configuration register      Offset 0x44
            Register32 CNDTR4;  // Ch 4 no of data to transfer reg  Offset 0x48
            Register32 CPAR4;   // Ch 4 peripheral address reg      Offset 0x4C
            Register32 CMAR4;   // Ch 4 memory address register     Offset 0x50
            Register32 _RESERVED_4; // Ch 4 reserved                Offset 0x54
            Register32 CCR5;    // Ch 5 configuration register      Offset 0x58
            Register32 CNDTR5;  // Ch 5 no of data to transfer reg  Offset 0x5C
            Register32 CPAR5;   // Ch 5 peripheral address reg      Offset 0x60
            Register32 CMAR5;   // Ch 5 memory address register     Offset 0x64
            Register32 _RESERVED_5; // Ch 5 reserved                Offset 0x68
            Register32 CCR6;    // Ch 6 configuration register      Offset 0x6C
            Register32 CNDTR6;  // Ch 6 no of data to transfer reg  Offset 0x70
            Register32 CPAR6;   // Ch 6 peripheral address reg      Offset 0x74
            Register32 CMAR6;   // Ch 6 memory address register     Offset 0x78
            Register32 _RESERVED_6; // Ch 6 reserved                Offset 0x7C
            Register32 CCR7;    // Ch 7 configuration register      Offset 0x80
            Register32 CNDTR7;  // Ch 7 no of data to transfer reg  Offset 0x84
            Register32 CPAR7;   // Ch 7 peripheral address reg      Offset 0x88
            Register32 CMAR7;   // Ch 7 memory address register     Offset 0x8C
            Register32 _RESERVED_7; // Ch 7 reserved                Offset 0x90
            Register32 _RESERVED_8[5];  // Ch 8 reserved            Offset 0x94..0xA4
            Register32 CSELR;   // Channel selection register       Offset 0xA8
        } __attribute__((packed));

        struct ISR
        {
            static const uint32_t GIF1      = 0;
            static const uint32_t TCIF1     = 1;
            static const uint32_t HTIF1     = 2;
            static const uint32_t TEIF1     = 3;
            static const uint32_t GIF2      = 4;
            static const uint32_t TCIF2     = 5;
            static const uint32_t HTIF2     = 6;
            static const uint32_t TEIF2     = 7;
            static const uint32_t GIF3      = 8;
            static const uint32_t TCIF3     = 9;
            static const uint32_t HTIF3     = 10;
            static const uint32_t TEIF3     = 11;
            static const uint32_t GIF4      = 12;
            static const uint32_t TCIF4     = 13;
            static const uint32_t HTIF4     = 14;
            static const uint32_t TEIF4     = 15;
            static const uint32_t GIF5      = 16;
            static const uint32_t TCIF5     = 17;
            static const uint32_t HTIF5     = 18;
            static const uint32_t TEIF5     = 19;
            static const uint32_t GIF6      = 20;
            static const uint32_t TCIF6     = 21;
            static const uint32_t HTIF6     = 22;
            static const uint32_t TEIF6     = 23;
            static const uint32_t GIF7      = 24;
            static const uint32_t TCIF7     = 25;
            static const uint32_t HTIF7     = 26;
            static const uint32_t TEIF7     = 27;
        };

        struct ICFR
        {
            static const uint32_t CGIF1     = 0;
            static const uint32_t CTCIF1    = 1;
            static const uint32_t CHTIF1    = 2;
            static const uint32_t CTEIF1    = 3;
            static const uint32_t CGIF2     = 4;
            static const uint32_t CTCIF2    = 5;
            static const uint32_t CHTIF2    = 6;
            static const uint32_t CTEIF2    = 7;
            static const uint32_t CGIF3     = 8;
            static const uint32_t CTCIF3    = 9;
            static const uint32_t CHTIF3    = 10;
            static const uint32_t CTEIF3    = 11;
            static const uint32_t CGIF4     = 12;
            static const uint32_t CTCIF4    = 13;
            static const uint32_t CHTIF4    = 14;
            static const uint32_t CTEIF4    = 15;
            static const uint32_t CGIF5     = 16;
            static const uint32_t CTCIF5    = 17;
            static const uint32_t CHTIF5    = 18;
            static const uint32_t CTEIF5    = 19;
            static const uint32_t CGIF6     = 20;
            static const uint32_t CTCIF6    = 21;
            static const uint32_t CHTIF6    = 22;
            static const uint32_t CTEIF6    = 23;
            static const uint32_t CGIF7     = 24;
            static const uint32_t CTCIF7    = 25;
            static const uint32_t CHTIF7    = 26;
            static const uint32_t CTEIF7    = 27;
        };

        struct CSELR
        {
            static const uint32_t C1S_0     = 0;
            static const uint32_t C1S_1     = 1;
            static const uint32_t C1S_2     = 2;
            static const uint32_t C1S_3     = 3;
            static const uint32_t C2S_0     = 4;
            static const uint32_t C2S_1     = 5;
            static const uint32_t C2S_2     = 6;
            static const uint32_t C2S_3     = 7;
            static const uint32_t C3S_0     = 8;
            static const uint32_t C3S_1     = 9;
            static const uint32_t C3S_2     = 10;
            static const uint32_t C3S_3     = 11;
            static const uint32_t C4S_0     = 12;
            static const uint32_t C4S_1     = 13;
            static const uint32_t C4S_2     = 14;
            static const uint32_t C4S_3     = 15;
            static const uint32_t C5S_0     = 16;
            static const uint32_t C5S_1     = 17;
            static const uint32_t C5S_2     = 18;
            static const uint32_t C5S_3     = 19;
            static const uint32_t C6S_0     = 20;
            static const uint32_t C6S_1     = 21;
            static const uint32_t C6S_2     = 22;
            static const uint32_t C6S_3     = 23;
            static const uint32_t C7S_0     = 24;
            static const uint32_t C7S_1     = 25;
            static const uint32_t C7S_2     = 26;
            static const uint32_t C7S_3     = 27;
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
                case Id::DMA1:
                    return (Block*)DMA1_BASE_ADDRESS;
                case Id::DMA2:
                    return (Block*)DMA2_BASE_ADDRESS;
            }

            return nullptr;
        }

    protected:
        // Register block base addresses
        static const uint32_t DMA1_BASE_ADDRESS = AHB1_BASE_ADDRESS + 0x00000000;
        static const uint32_t DMA2_BASE_ADDRESS = AHB1_BASE_ADDRESS + 0x00000400;

};


class DMA_ChannelRegisters
{
    public:
        struct Block
        {
            Register32 CCRx;    // Channel configuration register       Offset 0x00
            Register32 CNDTRx;  // Channel no of data to transfer reg   Offset 0x04
            Register32 CPARx;   // Channel peripheral address reg       Offset 0x08
            Register32 CMARx;   // Channel memory address register      Offset 0x0C
            Register32 _RESERVED_x; // Channel reserved                 Offset 0x10
        } __attribute__((packed));

        struct CCRx
        {
            static const uint32_t EN        = 0;
            static const uint32_t TCIE      = 1;
            static const uint32_t HTIE      = 2;
            static const uint32_t TEIE      = 3;
            static const uint32_t DIR       = 4;
            static const uint32_t CIRC      = 5;
            static const uint32_t PINC      = 6;
            static const uint32_t MINC      = 7;
            static const uint32_t PSIZE_0   = 8;
            static const uint32_t PSIZE_1   = 9;
            static const uint32_t MSIZE_0   = 10;
            static const uint32_t MSIZE_1   = 11;
            static const uint32_t PL_0      = 12;
            static const uint32_t PL_1      = 13;
            static const uint32_t MEM2MEM   = 14;
        };
};


}   // namespace mcu
