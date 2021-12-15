/**
 * @file        UART_Registers.h
 *
 * Register definitions for UART/USART peripherals on STM32L4xx
 *
 * @author:     Oliver Rockstedt <info@sourcebox.de>
 * @license     MIT
 */


#pragma once


// Local includes
#include "UART_Base.h"

// This component
#include "../core/mcu_base.h"
#include "../utility/register.h"

// System libraries
#include <cstdint>


namespace mcu {


class UART_Registers : public UART_Base
{
    public:
        struct Block
        {
            Register32 CR1;    // Control register 1               Offset 0x00
            Register32 CR2;    // Control register 2               Offset 0x04
            Register32 CR3;    // Control register 3               Offset 0x08
            Register32 BRR;    // Baud rate register               Offset 0x0C
            Register32 GTPR;   // Guard time and prescaler reg.    Offset 0x10
            Register32 RTOR;   // Receiver Timeout register        Offset 0x14
            Register32 RQR;    // Request register                 Offset 0x18
            Register32 ISR;    // Interrupt and status register    Offset 0x1C
            Register32 ICR;    // Interrupt flag clear register    Offset 0x20
            Register32 RDR;    // Receive data register            Offset 0x24
            Register32 TDR;    // Transmit data register           Offset 0x28
        } __attribute__((packed));

        struct CR1
        {
            static const uint32_t UE        = 0;
            static const uint32_t UESM      = 1;
            static const uint32_t RE        = 2;
            static const uint32_t TE        = 3;
            static const uint32_t IDLEIE    = 4;
            static const uint32_t RXNEIE    = 5;
            static const uint32_t TCIE      = 6;
            static const uint32_t TXEIE     = 7;
            static const uint32_t PEIE      = 8;
            static const uint32_t PS        = 9;
            static const uint32_t PCE       = 10;
            static const uint32_t WAKE      = 11;
            static const uint32_t M0        = 12;
            static const uint32_t MME       = 13;
            static const uint32_t CMIE      = 14;
            static const uint32_t OVER8     = 15;
            static const uint32_t DEDT_0    = 16;
            static const uint32_t DEDT_1    = 17;
            static const uint32_t DEDT_2    = 18;
            static const uint32_t DEDT_3    = 19;
            static const uint32_t DEDT_4    = 20;
            static const uint32_t DEAT_0    = 21;
            static const uint32_t DEAT_1    = 22;
            static const uint32_t DEAT_2    = 23;
            static const uint32_t DEAT_3    = 24;
            static const uint32_t DEAT_4    = 25;
            static const uint32_t RTOIE     = 26;
            static const uint32_t EOBIE     = 27;
            static const uint32_t M1        = 28;
        };

        struct CR2
        {
            static const uint32_t ADDM7     = 4;
            static const uint32_t LBDL      = 5;
            static const uint32_t LBDIE     = 6;
            static const uint32_t LBCL      = 8;
            static const uint32_t CPHA      = 9;
            static const uint32_t CPOL      = 10;
            static const uint32_t CLKEN     = 11;
            static const uint32_t STOP_0    = 12;
            static const uint32_t STOP_1    = 13;
            static const uint32_t LINEN     = 14;
            static const uint32_t SWAP      = 15;
            static const uint32_t RXINV     = 16;
            static const uint32_t TXINV     = 17;
            static const uint32_t DATAINV   = 18;
            static const uint32_t MSBFIRST  = 19;
            static const uint32_t ABREN     = 20;
            static const uint32_t ABRMOD_0  = 21;
            static const uint32_t ABRMOD_1  = 22;
            static const uint32_t RTOEN     = 23;
            static const uint32_t ADD_0     = 24;
            static const uint32_t ADD_1     = 25;
            static const uint32_t ADD_2     = 26;
            static const uint32_t ADD_3     = 27;
            static const uint32_t ADD_4     = 28;
            static const uint32_t ADD_5     = 29;
            static const uint32_t ADD_6     = 30;
            static const uint32_t ADD_7     = 31;
        };

        struct CR3
        {
            static const uint32_t EIE       = 0;
            static const uint32_t IREN      = 1;
            static const uint32_t IRLP      = 2;
            static const uint32_t HDSEL     = 3;
            static const uint32_t NACK      = 4;
            static const uint32_t SCEN      = 5;
            static const uint32_t DMAR      = 6;
            static const uint32_t DMAT      = 7;
            static const uint32_t RTSE      = 8;
            static const uint32_t CTSE      = 9;
            static const uint32_t CTSIE     = 10;
            static const uint32_t ONEBIT    = 11;
            static const uint32_t OVRDIS    = 12;
            static const uint32_t DDRE      = 13;
            static const uint32_t DEM       = 14;
            static const uint32_t DEP       = 15;
            static const uint32_t SCARCNT0  = 17;
            static const uint32_t SCARCNT1  = 18;
            static const uint32_t SCARCNT2  = 19;
            static const uint32_t WUS0      = 20;
            static const uint32_t WUS1      = 21;
            static const uint32_t WUFIE     = 22;
            static const uint32_t UCESM     = 23;
            static const uint32_t TCBGTIE   = 24;
        };

        struct GTPR
        {
            static const uint32_t PSC_0     = 0;
            static const uint32_t PSC_1     = 1;
            static const uint32_t PSC_2     = 2;
            static const uint32_t PSC_3     = 3;
            static const uint32_t PSC_4     = 4;
            static const uint32_t PSC_5     = 5;
            static const uint32_t PSC_6     = 6;
            static const uint32_t PSC_7     = 7;
            static const uint32_t GT_0      = 8;
            static const uint32_t GT_1      = 9;
            static const uint32_t GT_2      = 10;
            static const uint32_t GT_3      = 11;
            static const uint32_t GT_4      = 12;
            static const uint32_t GT_5      = 13;
            static const uint32_t GT_6      = 14;
            static const uint32_t GT_7      = 15;
        };

        struct RTOR
        {
            static const uint32_t RTO_0     = 0;
            static const uint32_t RTO_1     = 1;
            static const uint32_t RTO_2     = 2;
            static const uint32_t RTO_3     = 3;
            static const uint32_t RTO_4     = 4;
            static const uint32_t RTO_5     = 5;
            static const uint32_t RTO_6     = 6;
            static const uint32_t RTO_7     = 7;
            static const uint32_t RTO_8     = 8;
            static const uint32_t RTO_9     = 9;
            static const uint32_t RTO_10    = 10;
            static const uint32_t RTO_11    = 11;
            static const uint32_t RTO_12    = 12;
            static const uint32_t RTO_13    = 13;
            static const uint32_t RTO_14    = 14;
            static const uint32_t RTO_15    = 15;
            static const uint32_t RTO_16    = 16;
            static const uint32_t RTO_17    = 17;
            static const uint32_t RTO_18    = 18;
            static const uint32_t RTO_19    = 19;
            static const uint32_t RTO_20    = 20;
            static const uint32_t RTO_21    = 21;
            static const uint32_t RTO_22    = 22;
            static const uint32_t RTO_23    = 23;
            static const uint32_t BLEN_0    = 24;
            static const uint32_t BLEN_1    = 25;
            static const uint32_t BLEN_2    = 26;
            static const uint32_t BLEN_3    = 27;
            static const uint32_t BLEN_4    = 28;
            static const uint32_t BLEN_5    = 29;
            static const uint32_t BLEN_6    = 30;
            static const uint32_t BLEN_7    = 31;
        };

        struct RQR
        {
            static const uint32_t ABRRQ     = 0;
            static const uint32_t SBKRQ     = 1;
            static const uint32_t MMRQ      = 2;
            static const uint32_t RXFRQ     = 3;
            static const uint32_t TXFRQ     = 4;
        };

        struct ISR
        {
            static const uint32_t PE        = 0;
            static const uint32_t FE        = 1;
            static const uint32_t NF        = 2;
            static const uint32_t ORE       = 3;
            static const uint32_t IDLE      = 4;
            static const uint32_t RXNE      = 5;
            static const uint32_t TC        = 6;
            static const uint32_t TXE       = 7;
            static const uint32_t LBDF      = 8;
            static const uint32_t CTSIF     = 9;
            static const uint32_t CTS       = 10;
            static const uint32_t RTOF      = 11;
            static const uint32_t EOBF      = 12;
            static const uint32_t ABRE      = 14;
            static const uint32_t ABRF      = 15;
            static const uint32_t BUSY      = 16;
            static const uint32_t CMF       = 17;
            static const uint32_t SBKF      = 18;
            static const uint32_t RWU       = 19;
            static const uint32_t WUF       = 20;
            static const uint32_t TEACK     = 21;
            static const uint32_t REACK     = 22;
            static const uint32_t TCBGT     = 25;
        };

        struct ICR
        {
            static const uint32_t PECF      = 0;
            static const uint32_t FECF      = 1;
            static const uint32_t NCF       = 2;
            static const uint32_t ORECF     = 3;
            static const uint32_t IDLECF    = 4;
            static const uint32_t TCCF      = 6;
            static const uint32_t TCBGTCF   = 7;
            static const uint32_t LBDCF     = 8;
            static const uint32_t CTSCF     = 9;
            static const uint32_t RTOCF     = 11;
            static const uint32_t EOBCF     = 12;
            static const uint32_t CMCF      = 17;
            static const uint32_t WUCF      = 20;
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
                case Id::USART1:
                    return (Block*)USART1_BASE_ADDRESS;
                case Id::USART2:
                    return (Block*)USART2_BASE_ADDRESS;
                case Id::USART3:
                    return (Block*)USART3_BASE_ADDRESS;
                case Id::UART4:
                    return (Block*)UART4_BASE_ADDRESS;
                case Id::LPUART1:
                    return (Block*)LPUART1_BASE_ADDRESS;
            }

            return nullptr;
        }

    protected:
        // Register block base addresses
        static const uint32_t USART1_BASE_ADDRESS = APB2_BASE_ADDRESS + 0x00003800;
        static const uint32_t USART2_BASE_ADDRESS = APB1_BASE_ADDRESS + 0x00004400;
        static const uint32_t USART3_BASE_ADDRESS = APB1_BASE_ADDRESS + 0x00004800;
        static const uint32_t UART4_BASE_ADDRESS = APB1_BASE_ADDRESS + 0x00004C00;
        static const uint32_t LPUART1_BASE_ADDRESS = APB1_BASE_ADDRESS + 0x00008000;
};


}   // namespace mcu
