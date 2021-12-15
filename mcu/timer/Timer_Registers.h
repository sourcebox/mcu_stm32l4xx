/**
 * @file        Timer_Registers.h
 *
 * Register definitions for timer peripherals on STM32L4xx
 *
 * @author:     Oliver Rockstedt <info@sourcebox.de>
 * @license     MIT
 */


#pragma once


// Local includes
#include "Timer_Base.h"

// This component
#include "../core/mcu_base.h"
#include "../utility/register.h"

// System libraries
#include <cstdint>


namespace mcu {


class Timer_Registers : Timer_Base
{
    public:
        struct Block
        {
            Register32 CR1;     // Control register 1               Offset 0x00
            Register32 CR2;     // Control register 1               Offset 0x04
            Register32 SMCR;    // Slave mode control register 1    Offset 0x08
            Register32 DIER;    // DMA/interrupt enable register    Offset 0x0C
            Register32 SR;      // Status register                  Offset 0x10
            Register32 EGR;     // Event generation register        Offset 0x14
            Register32 CCMR1;   // Capture/compare mode register 1  Offset 0x18
            Register32 CCMR2;   // Capture/compare mode register 2  Offset 0x1C
            Register32 CCER;    // Capture/compare enable register  Offset 0x20
            Register32 CNT;     // Counter                          Offset 0x24
            Register32 PSC;     // Prescaler                        Offset 0x28
            Register32 ARR;     // Auto-reload register             Offset 0x2C
            Register32 RCR;     // Repetition counter register      Offset 0x30
            Register32 CCR1;    // Capture/compare register 1       Offset 0x34
            Register32 CCR2;    // Capture/compare register 2       Offset 0x38
            Register32 CCR3;    // Capture/compare register 3       Offset 0x3C
            Register32 CCR4;    // Capture/compare register 4       Offset 0x40
            Register32 BDTR;    // Break and dead-time register     Offset 0x44
            Register32 DCR;     // DMA control register             Offset 0x48
            Register32 DMAR;    // DMA address for full transfer    Offset 0x4C
            Register32 OR1;     // Option register 1                Offset 0x50
            Register32 CCMR3;   // Capture/compare mode register 3  Offset 0x54
            Register32 CCR5;    // Capture/compare register 5       Offset 0x58
            Register32 CCR6;    // Capture/compare register 6       Offset 0x5C
            Register32 OR2;     // Option register 2                Offset 0x60
            Register32 OR3;     // Option register 3                Offset 0x64
        } __attribute__((packed));

        struct CR1
        {
            static const uint32_t CEN       = 0;
            static const uint32_t UDIS      = 1;
            static const uint32_t URS       = 2;
            static const uint32_t OPM       = 3;
            static const uint32_t DIR       = 4;
            static const uint32_t CMS_0     = 5;
            static const uint32_t CMS_1     = 6;
            static const uint32_t ARPE      = 7;
            static const uint32_t CKD_0     = 8;
            static const uint32_t CKD_1     = 9;
            static const uint32_t UIFREMAP  = 11;
        };

        struct CR2
        {
            static const uint32_t CCPC      = 0;
            static const uint32_t CCUS      = 2;
            static const uint32_t CCDS      = 3;
            static const uint32_t MMS_0     = 4;
            static const uint32_t MMS_1     = 5;
            static const uint32_t MMS_2     = 6;
            static const uint32_t TI1S      = 7;
            static const uint32_t OIS1      = 8;
            static const uint32_t OIS1N     = 9;
            static const uint32_t OIS2      = 10;
            static const uint32_t OIS2N     = 11;
            static const uint32_t OIS3      = 12;
            static const uint32_t OIS3N     = 13;
            static const uint32_t OIS4      = 14;
            static const uint32_t OIS5      = 16;
            static const uint32_t OIS6      = 18;
            static const uint32_t MMS2_0    = 20;
            static const uint32_t MMS2_1    = 21;
            static const uint32_t MMS2_2    = 22;
            static const uint32_t MMS2_3    = 23;
        };

        struct SMCR
        {
            static const uint32_t SMS_0     = 0;
            static const uint32_t SMS_1     = 1;
            static const uint32_t SMS_2     = 2;
            static const uint32_t OCCS      = 3;
            static const uint32_t TS_0      = 4;
            static const uint32_t TS_1      = 5;
            static const uint32_t TS_2      = 6;
            static const uint32_t MSM       = 7;
            static const uint32_t ETF_0     = 8;
            static const uint32_t ETF_1     = 9;
            static const uint32_t ETF_2     = 10;
            static const uint32_t ETF_3     = 11;
            static const uint32_t ETPS_0    = 12;
            static const uint32_t ETPS_1    = 13;
            static const uint32_t ECE       = 14;
            static const uint32_t ETP       = 15;
            static const uint32_t SMS_3     = 16;
        };

        struct DIER
        {
            static const uint32_t UIE       = 0;
            static const uint32_t CC1IE     = 1;
            static const uint32_t CC2IE     = 2;
            static const uint32_t CC3IE     = 3;
            static const uint32_t CC4IE     = 4;
            static const uint32_t COMIE     = 5;
            static const uint32_t TIE       = 6;
            static const uint32_t BIE       = 7;
            static const uint32_t UDE       = 8;
            static const uint32_t CC1DE     = 9;
            static const uint32_t CC2DE     = 10;
            static const uint32_t CC3DE     = 11;
            static const uint32_t CC4DE     = 12;
            static const uint32_t COMDE     = 13;
            static const uint32_t TDE       = 14;
        };

        struct SR
        {
            static const uint32_t UIF       = 0;
            static const uint32_t CC1IF     = 1;
            static const uint32_t CC2IF     = 2;
            static const uint32_t CC3IF     = 3;
            static const uint32_t CC4IF     = 4;
            static const uint32_t COMIF     = 5;
            static const uint32_t TIF       = 6;
            static const uint32_t BIF       = 7;
            static const uint32_t B2IF      = 8;
            static const uint32_t CC1OF     = 9;
            static const uint32_t CC2OF     = 10;
            static const uint32_t CC3OF     = 11;
            static const uint32_t CC4OF     = 12;
            static const uint32_t SBIF      = 13;
            static const uint32_t CC5IF     = 16;
            static const uint32_t CC6IF     = 17;
        };

        struct EGR
        {
            static const uint32_t UG        = 0;
            static const uint32_t CC1G      = 1;
            static const uint32_t CC2G      = 2;
            static const uint32_t CC3G      = 3;
            static const uint32_t CC4G      = 4;
            static const uint32_t COMG      = 5;
            static const uint32_t TG        = 6;
            static const uint32_t BG        = 7;
            static const uint32_t B2G       = 8;
        };

        struct CCMR1
        {
            static const uint32_t CC1S_0    = 0;
            static const uint32_t CC1S_1    = 1;
            static const uint32_t CC2S_0    = 8;
            static const uint32_t CC2S_1    = 9;

            // Input capture mode
            static const uint32_t IC1PSC_0  = 2;
            static const uint32_t IC1PSC_1  = 3;
            static const uint32_t IC1F_0    = 4;
            static const uint32_t IC1F_1    = 5;
            static const uint32_t IC1F_2    = 6;
            static const uint32_t IC1F_3    = 7;
            static const uint32_t IC2PSC_0  = 10;
            static const uint32_t IC2PSC_1  = 11;
            static const uint32_t IC2F_0    = 12;
            static const uint32_t IC2F_1    = 13;
            static const uint32_t IC2F_2    = 14;
            static const uint32_t IC2F_3    = 15;

            // Output compare mode
            static const uint32_t OC1FE     = 2;
            static const uint32_t OC1PE     = 3;
            static const uint32_t OC1M_0    = 4;
            static const uint32_t OC1M_1    = 5;
            static const uint32_t OC1M_2    = 6;
            static const uint32_t OC1CE     = 7;
            static const uint32_t OC2FE     = 10;
            static const uint32_t OC2PE     = 11;
            static const uint32_t OC2M_0    = 12;
            static const uint32_t OC2M_1    = 13;
            static const uint32_t OC2M_2    = 14;
            static const uint32_t OC2CE     = 15;
            static const uint32_t OC1M_3    = 16;
            static const uint32_t OC2M_3    = 24;
        };

        struct CCMR2
        {
            static const uint32_t CC3S_0    = 0;
            static const uint32_t CC3S_1    = 1;
            static const uint32_t CC4S_0    = 8;
            static const uint32_t CC4S_1    = 9;

            // Input capture mode
            static const uint32_t IC3PSC_0  = 2;
            static const uint32_t IC3PSC_1  = 3;
            static const uint32_t IC3F_0    = 4;
            static const uint32_t IC3F_1    = 5;
            static const uint32_t IC3F_2    = 6;
            static const uint32_t IC3F_3    = 7;
            static const uint32_t IC4PSC_0  = 10;
            static const uint32_t IC4PSC_1  = 11;
            static const uint32_t IC4F_0    = 12;
            static const uint32_t IC4F_1    = 13;
            static const uint32_t IC4F_2    = 14;
            static const uint32_t IC4F_3    = 15;

            // Output compare mode
            static const uint32_t OC3FE     = 2;
            static const uint32_t OC3PE     = 3;
            static const uint32_t OC3M_0    = 4;
            static const uint32_t OC3M_1    = 5;
            static const uint32_t OC3M_2    = 6;
            static const uint32_t OC3CE     = 7;
            static const uint32_t OC4FE     = 10;
            static const uint32_t OC4PE     = 11;
            static const uint32_t OC4M_0    = 12;
            static const uint32_t OC4M_1    = 13;
            static const uint32_t OC4M_2    = 14;
            static const uint32_t OC4CE     = 15;
            static const uint32_t OC3M_3    = 16;
            static const uint32_t OC4M_3    = 24;
        };

        struct CCER
        {
            static const uint32_t CC1E      = 0;
            static const uint32_t CC1P      = 1;
            static const uint32_t CC1NE     = 2;
            static const uint32_t CC1NP     = 3;
            static const uint32_t CC2E      = 4;
            static const uint32_t CC2P      = 5;
            static const uint32_t CC2NE     = 6;
            static const uint32_t CC2NP     = 7;
            static const uint32_t CC3E      = 8;
            static const uint32_t CC3P      = 9;
            static const uint32_t CC3NE     = 10;
            static const uint32_t CC3NP     = 11;
            static const uint32_t CC4E      = 12;
            static const uint32_t CC4P      = 13;
            static const uint32_t CC4NE     = 14;
            static const uint32_t CC4NP     = 15;
            static const uint32_t CC5E      = 16;
            static const uint32_t CC5P      = 17;
            static const uint32_t CC6E      = 20;
            static const uint32_t CC6P      = 21;
        };

        struct CNT
        {
            static const uint32_t UIFCPY    = 31;
        };

        struct BDTR
        {
            static const uint32_t DTG_0     = 0;
            static const uint32_t DTG_1     = 1;
            static const uint32_t DTG_2     = 2;
            static const uint32_t DTG_3     = 3;
            static const uint32_t DTG_4     = 4;
            static const uint32_t DTG_5     = 5;
            static const uint32_t DTG_6     = 6;
            static const uint32_t DTG_7     = 7;
            static const uint32_t LOCK_0    = 8;
            static const uint32_t LOCK_1    = 9;
            static const uint32_t OSSI      = 10;
            static const uint32_t OSSR      = 11;
            static const uint32_t BKE       = 12;
            static const uint32_t BKP       = 13;
            static const uint32_t AOE       = 14;
            static const uint32_t MOE       = 15;
            static const uint32_t BKF_0     = 16;
            static const uint32_t BKF_1     = 17;
            static const uint32_t BKF_2     = 18;
            static const uint32_t BKF_3     = 19;
            static const uint32_t BK2F_0    = 20;
            static const uint32_t BK2F_1    = 21;
            static const uint32_t BK2F_2    = 22;
            static const uint32_t BK2F_3    = 23;
            static const uint32_t BK2E      = 24;
            static const uint32_t BK2P      = 25;
        };

        struct DCR
        {
            static const uint32_t DBA_0     = 0;
            static const uint32_t DBA_1     = 1;
            static const uint32_t DBA_2     = 2;
            static const uint32_t DBA_3     = 3;
            static const uint32_t DBA_4     = 4;
            static const uint32_t DBL_0     = 8;
            static const uint32_t DBL_1     = 9;
            static const uint32_t DBL_2     = 10;
            static const uint32_t DBL_3     = 11;
            static const uint32_t DBL_4     = 12;
        };

        struct OR1
        {
            // TIM1 only
            static const uint32_t ETR_ADC1_RMP  = 0;
            static const uint32_t TIM1_TI1_RMP  = 4;

            // TIM2 only
            static const uint32_t ITR1_RMP      = 0;
            static const uint32_t ETR1_RMP      = 1;
            static const uint32_t TI4_RMP_0     = 2;
            static const uint32_t TI4_RMP_1     = 3;

            // TIM15 only
            static const uint32_t TIM15_TI1_RMP     = 0;
            static const uint32_t ENCODER_MODE_0    = 1;
            static const uint32_t ENCODER_MODE_1    = 2;

            // TIM16 only
            static const uint32_t TIM16_TI1_RMP_0   = 0;
            static const uint32_t TIM16_TI1_RMP_1   = 1;
            static const uint32_t TIM16_TI1_RMP_2   = 2;
        };

        struct CCMR3
        {
            // Output compare mode
            static const uint32_t OC5FE     = 2;
            static const uint32_t OC5PE     = 3;
            static const uint32_t OC5M_0    = 4;
            static const uint32_t OC5M_1    = 5;
            static const uint32_t OC5M_2    = 6;
            static const uint32_t OC5CE     = 7;
            static const uint32_t OC6FE     = 10;
            static const uint32_t OC6PE     = 11;
            static const uint32_t OC6M_0    = 12;
            static const uint32_t OC6M_1    = 13;
            static const uint32_t OC6M_2    = 14;
            static const uint32_t OC6CE     = 15;
            static const uint32_t OC5M_3    = 16;
            static const uint32_t OC6M_3    = 24;
        };

        struct CCR5
        {
            static const uint32_t GC5C1     = 29;
            static const uint32_t GC5C2     = 30;
            static const uint32_t GC5C3     = 31;
        };

        struct OR2
        {
            static const uint32_t BKINE     = 0;
            static const uint32_t BKCMP1E   = 1;
            static const uint32_t BKCMP2E   = 2;
            static const uint32_t BKINP     = 9;
            static const uint32_t BKCMP1P   = 10;
            static const uint32_t BKCMP2P   = 11;
            static const uint32_t ETRSEL_0  = 14;
            static const uint32_t ETRSEL_1  = 15;
            static const uint32_t ETRSEL_2  = 16;
        };

        struct OR3
        {
            static const uint32_t BK2INE    = 0;
            static const uint32_t BK2CMP1E  = 1;
            static const uint32_t BK2CMP2E  = 2;
            static const uint32_t BK2INP    = 9;
            static const uint32_t BK2CMP1P  = 10;
            static const uint32_t BK2CMP2P  = 11;
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
                case Id::TIM1:
                    return (Block*)TIM1_BASE_ADDRESS;
                case Id::TIM2:
                    return (Block*)TIM2_BASE_ADDRESS;
                case Id::TIM3:
                    return (Block*)TIM3_BASE_ADDRESS;
                case Id::TIM6:
                    return (Block*)TIM6_BASE_ADDRESS;
                case Id::TIM7:
                    return (Block*)TIM7_BASE_ADDRESS;
                case Id::TIM15:
                    return (Block*)TIM15_BASE_ADDRESS;
                case Id::TIM16:
                    return (Block*)TIM16_BASE_ADDRESS;
            }

            return nullptr;
        }

    protected:
        // Register block base addresses
        static const uint32_t TIM1_BASE_ADDRESS = APB2_BASE_ADDRESS + 0x00002C00;
        static const uint32_t TIM2_BASE_ADDRESS = APB1_BASE_ADDRESS + 0x00000000;
        static const uint32_t TIM3_BASE_ADDRESS = APB1_BASE_ADDRESS + 0x00000400;
        static const uint32_t TIM6_BASE_ADDRESS = APB1_BASE_ADDRESS + 0x00001000;
        static const uint32_t TIM7_BASE_ADDRESS = APB1_BASE_ADDRESS + 0x00001400;
        static const uint32_t TIM15_BASE_ADDRESS = APB2_BASE_ADDRESS + 0x00004000;
        static const uint32_t TIM16_BASE_ADDRESS = APB2_BASE_ADDRESS + 0x00004400;
};


}   // namespace mcu
