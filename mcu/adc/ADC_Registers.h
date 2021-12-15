/**
 * @file        ADC_Registers.h
 *
 * Register definitions for ADC peripherals on STM32L4xx
 *
 * @author:     Oliver Rockstedt <info@sourcebox.de>
 * @license     MIT
 */


#pragma once


// Local includes
#include "ADC_Base.h"

// This component
#include "../core/mcu_base.h"
#include "../utility/register.h"

// System libraries
#include <cstdint>


namespace mcu {


class ADC_Registers : public ADC_Base
{
    public:
        struct Block
        {
            Register32 ISR;     // Interrupt and status register        Offset 0x00
            Register32 IER;     // Interrupt enable register            Offset 0x04
            Register32 CR;      // Control register                     Offset 0x08
            Register32 CFGR;    // Configuration register               Offset 0x0C
            Register32 CFGR2;   // Configuration register 2             Offset 0x10
            Register32 SMPR1;   // Sample time register 1               Offset 0x14
            Register32 SMPR2;   // Sample time register 2               Offset 0x18
            Register32 _RESERVED_1; // Reserved                         Offset 0x1C
            Register32 TR1;     // Watchdog threshold register 1        Offset 0x20
            Register32 TR2;     // Watchdog threshold register 2        Offset 0x24
            Register32 TR3;     // Watchdog threshold register 3        Offset 0x28
            Register32 _RESERVED_2; // Reserved                         Offset 0x2C
            Register32 SQR1;    // Regular sequence register 1          Offset 0x30
            Register32 SQR2;    // Regular sequence register 2          Offset 0x34
            Register32 SQR3;    // Regular sequence register 3          Offset 0x38
            Register32 SQR4;    // Regular sequence register 4          Offset 0x3C
            Register32 DR;      // Regular data register                Offset 0x40
            Register32 _RESERVED_3; // Reserved                         Offset 0x44
            Register32 _RESERVED_4; // Reserved                         Offset 0x48
            Register32 JSQR;    // Injected sequence register           Offset 0x4C
            Register32 _RESERVED_5; // Reserved                         Offset 0x50
            Register32 _RESERVED_6; // Reserved                         Offset 0x54
            Register32 _RESERVED_7; // Reserved                         Offset 0x58
            Register32 _RESERVED_8; // Reserved                         Offset 0x5C
            Register32 OFR1;    // Offset 1 register                    Offset 0x60
            Register32 OFR2;    // Offset 2 register                    Offset 0x64
            Register32 OFR3;    // Offset 3 register                    Offset 0x68
            Register32 OFR4;    // Offset 4 register                    Offset 0x6C
            Register32 _RESERVED_9;  // Reserved                        Offset 0x70
            Register32 _RESERVED_10; // Reserved                        Offset 0x74
            Register32 _RESERVED_11; // Reserved                        Offset 0x78
            Register32 _RESERVED_12; // Reserved                        Offset 0x7C
            Register32 JDR1;    // Injected channel 1 data register     Offset 0x80
            Register32 JDR2;    // Injected channel 2 data register     Offset 0x84
            Register32 JDR3;    // Injected channel 3 data register     Offset 0x88
            Register32 JDR4;    // Injected channel 4 data register     Offset 0x8C
            Register32 _RESERVED_13; // Reserved                        Offset 0x90
            Register32 _RESERVED_14; // Reserved                        Offset 0x94
            Register32 _RESERVED_15; // Reserved                        Offset 0x98
            Register32 _RESERVED_16; // Reserved                        Offset 0x9C
            Register32 AWD2CR;  // Analog watchdog 2 config register    Offset 0xA0
            Register32 AWD3CR;  // Analog watchdog 3 config register    Offset 0xA4
            Register32 _RESERVED_17; // Reserved                        Offset 0xA8
            Register32 _RESERVED_18; // Reserved                        Offset 0xAC
            Register32 DIFSEL;  // Differential mode sel, register      Offset 0xB0
            Register32 CALFACT; // Calibration factors                  Offset 0xB4
        } __attribute__((packed));

        struct ISR
        {
            static const uint32_t ADRDY     = 0;
            static const uint32_t EOSMP     = 1;
            static const uint32_t EOC       = 2;
            static const uint32_t EOS       = 3;
            static const uint32_t OVR       = 4;
            static const uint32_t JEOC      = 5;
            static const uint32_t JEOS      = 6;
            static const uint32_t AWD1      = 7;
            static const uint32_t AWD2      = 8;
            static const uint32_t AWD3      = 9;
            static const uint32_t JQOVF     = 10;
        };

        struct IER
        {
            static const uint32_t ADRDYIE   = 0;
            static const uint32_t EOSMPIE   = 1;
            static const uint32_t EOCIE     = 2;
            static const uint32_t EOSIE     = 3;
            static const uint32_t OVRIE     = 4;
            static const uint32_t JEOCIE    = 5;
            static const uint32_t JEOSIE    = 6;
            static const uint32_t AWD1IE    = 7;
            static const uint32_t AWD2IE    = 8;
            static const uint32_t AWD3IE    = 9;
            static const uint32_t JQOVFIE   = 10;
        };

        struct CR
        {
            static const uint32_t ADEN      = 0;
            static const uint32_t ADDIS     = 1;
            static const uint32_t ADSTART   = 2;
            static const uint32_t JADSTART  = 3;
            static const uint32_t ADSTP     = 4;
            static const uint32_t JADSTP    = 5;
            static const uint32_t ADVREGEN  = 28;
            static const uint32_t DEEPPWD   = 29;
            static const uint32_t ADCALDIF  = 30;
            static const uint32_t ADCAL     = 31;
        };

        struct CFGR
        {
            static const uint32_t DMAEN     = 0;
            static const uint32_t DMACFG    = 1;
            static const uint32_t DFSDMCFG  = 2;
            static const uint32_t RES_0     = 3;
            static const uint32_t RES_1     = 4;
            static const uint32_t ALIGN     = 5;
            static const uint32_t EXTSEL_0  = 6;
            static const uint32_t EXTSEL_1  = 7;
            static const uint32_t EXTSEL_2  = 8;
            static const uint32_t EXTSEL_3  = 9;
            static const uint32_t EXTEN_0   = 10;
            static const uint32_t EXTEN_1   = 11;
            static const uint32_t OVRMOD    = 12;
            static const uint32_t CONT      = 13;
            static const uint32_t AUTDLY    = 14;
            static const uint32_t DISCEN    = 16;
            static const uint32_t DISCNUM_0 = 17;
            static const uint32_t DISCNUM_1 = 18;
            static const uint32_t DISCNUM_2 = 19;
            static const uint32_t JDISCEN   = 20;
            static const uint32_t JQM       = 21;
            static const uint32_t AWD1SGL   = 22;
            static const uint32_t AWD1EN    = 23;
            static const uint32_t JAWD1EN   = 24;
            static const uint32_t JAUTO     = 25;
            static const uint32_t AWD1CH_0  = 26;
            static const uint32_t AWD1CH_1  = 27;
            static const uint32_t AWD1CH_2  = 28;
            static const uint32_t AWD1CH_3  = 29;
            static const uint32_t AWD1CH_4  = 30;
            static const uint32_t JQDIS     = 31;
        };

        struct CFGR2
        {
            static const uint32_t ROVSE     = 0;
            static const uint32_t JOVSE     = 1;
            static const uint32_t OVSR_0    = 2;
            static const uint32_t OVSR_1    = 3;
            static const uint32_t OVSR_2    = 4;
            static const uint32_t OVSS_0    = 5;
            static const uint32_t OVSS_1    = 6;
            static const uint32_t OVSS_2    = 7;
            static const uint32_t OVSS_3    = 8;
            static const uint32_t TROVS     = 9;
            static const uint32_t ROVSM     = 10;
        };

        struct SMPR1
        {
            static const uint32_t SMP0_0    = 0;
            static const uint32_t SMP0_1    = 1;
            static const uint32_t SMP0_2    = 2;
            static const uint32_t SMP1_0    = 3;
            static const uint32_t SMP1_1    = 4;
            static const uint32_t SMP1_2    = 5;
            static const uint32_t SMP2_0    = 6;
            static const uint32_t SMP2_1    = 7;
            static const uint32_t SMP2_2    = 8;
            static const uint32_t SMP3_0    = 9;
            static const uint32_t SMP3_1    = 10;
            static const uint32_t SMP3_2    = 11;
            static const uint32_t SMP4_0    = 12;
            static const uint32_t SMP4_1    = 13;
            static const uint32_t SMP4_2    = 14;
            static const uint32_t SMP5_0    = 15;
            static const uint32_t SMP5_1    = 16;
            static const uint32_t SMP5_2    = 17;
            static const uint32_t SMP6_0    = 18;
            static const uint32_t SMP6_1    = 19;
            static const uint32_t SMP6_2    = 20;
            static const uint32_t SMP7_0    = 21;
            static const uint32_t SMP7_1    = 22;
            static const uint32_t SMP7_2    = 23;
            static const uint32_t SMP8_0    = 24;
            static const uint32_t SMP8_1    = 25;
            static const uint32_t SMP8_2    = 26;
            static const uint32_t SMP9_0    = 27;
            static const uint32_t SMP9_1    = 28;
            static const uint32_t SMP9_2    = 29;
        };

        struct SMPR2
        {
            static const uint32_t SMP10_0   = 0;
            static const uint32_t SMP10_1   = 1;
            static const uint32_t SMP10_2   = 2;
            static const uint32_t SMP11_0   = 3;
            static const uint32_t SMP11_1   = 4;
            static const uint32_t SMP11_2   = 5;
            static const uint32_t SMP12_0   = 6;
            static const uint32_t SMP12_1   = 7;
            static const uint32_t SMP12_2   = 8;
            static const uint32_t SMP13_0   = 9;
            static const uint32_t SMP13_1   = 10;
            static const uint32_t SMP13_2   = 11;
            static const uint32_t SMP14_0   = 12;
            static const uint32_t SMP14_1   = 13;
            static const uint32_t SMP14_2   = 14;
            static const uint32_t SMP15_0   = 15;
            static const uint32_t SMP15_1   = 16;
            static const uint32_t SMP15_2   = 17;
            static const uint32_t SMP16_0   = 18;
            static const uint32_t SMP16_1   = 19;
            static const uint32_t SMP16_2   = 20;
            static const uint32_t SMP17_0   = 21;
            static const uint32_t SMP17_1   = 22;
            static const uint32_t SMP17_2   = 23;
            static const uint32_t SMP18_0   = 24;
            static const uint32_t SMP18_1   = 25;
            static const uint32_t SMP18_2   = 26;
        };

        struct TR1
        {
            static const uint32_t LT1_0     = 0;
            static const uint32_t LT1_1     = 1;
            static const uint32_t LT1_2     = 2;
            static const uint32_t LT1_3     = 3;
            static const uint32_t LT1_4     = 4;
            static const uint32_t LT1_5     = 5;
            static const uint32_t LT1_6     = 6;
            static const uint32_t LT1_7     = 7;
            static const uint32_t LT1_8     = 8;
            static const uint32_t LT1_9     = 9;
            static const uint32_t LT1_10    = 10;
            static const uint32_t LT1_11    = 11;
            static const uint32_t HT1_0     = 16;
            static const uint32_t HT1_1     = 17;
            static const uint32_t HT1_2     = 18;
            static const uint32_t HT1_3     = 19;
            static const uint32_t HT1_4     = 20;
            static const uint32_t HT1_5     = 21;
            static const uint32_t HT1_6     = 22;
            static const uint32_t HT1_7     = 23;
            static const uint32_t HT1_8     = 24;
            static const uint32_t HT1_9     = 25;
            static const uint32_t HT1_10    = 26;
            static const uint32_t HT1_11    = 27;
        };

        struct TR2
        {
            static const uint32_t LT2_0     = 0;
            static const uint32_t LT2_1     = 1;
            static const uint32_t LT2_2     = 2;
            static const uint32_t LT2_3     = 3;
            static const uint32_t LT2_4     = 4;
            static const uint32_t LT2_5     = 5;
            static const uint32_t LT2_6     = 6;
            static const uint32_t LT2_7     = 7;
            static const uint32_t HT2_0     = 16;
            static const uint32_t HT2_1     = 17;
            static const uint32_t HT2_2     = 18;
            static const uint32_t HT2_3     = 19;
            static const uint32_t HT2_4     = 20;
            static const uint32_t HT2_5     = 21;
            static const uint32_t HT2_6     = 22;
            static const uint32_t HT2_7     = 23;
        };

        struct TR3
        {
            static const uint32_t LT3_0     = 0;
            static const uint32_t LT3_1     = 1;
            static const uint32_t LT3_2     = 2;
            static const uint32_t LT3_3     = 3;
            static const uint32_t LT3_4     = 4;
            static const uint32_t LT3_5     = 5;
            static const uint32_t LT3_6     = 6;
            static const uint32_t LT3_7     = 7;
            static const uint32_t HT3_0     = 16;
            static const uint32_t HT3_1     = 17;
            static const uint32_t HT3_2     = 18;
            static const uint32_t HT3_3     = 19;
            static const uint32_t HT3_4     = 20;
            static const uint32_t HT3_5     = 21;
            static const uint32_t HT3_6     = 22;
            static const uint32_t HT3_7     = 23;
        };

        struct SQR1
        {
            static const uint32_t L_0       = 0;
            static const uint32_t L_1       = 1;
            static const uint32_t L_2       = 2;
            static const uint32_t L_3       = 3;
            static const uint32_t SQ1_0     = 6;
            static const uint32_t SQ1_1     = 7;
            static const uint32_t SQ1_2     = 8;
            static const uint32_t SQ1_3     = 9;
            static const uint32_t SQ1_4     = 10;
            static const uint32_t SQ2_0     = 12;
            static const uint32_t SQ2_1     = 13;
            static const uint32_t SQ2_2     = 14;
            static const uint32_t SQ2_3     = 15;
            static const uint32_t SQ2_4     = 16;
            static const uint32_t SQ3_0     = 18;
            static const uint32_t SQ3_1     = 19;
            static const uint32_t SQ3_2     = 20;
            static const uint32_t SQ3_3     = 21;
            static const uint32_t SQ3_4     = 22;
            static const uint32_t SQ4_0     = 24;
            static const uint32_t SQ4_1     = 25;
            static const uint32_t SQ4_2     = 26;
            static const uint32_t SQ4_3     = 27;
            static const uint32_t SQ4_4     = 28;
        };

        struct SQR2
        {
            static const uint32_t SQ5_0     = 0;
            static const uint32_t SQ5_1     = 1;
            static const uint32_t SQ5_2     = 2;
            static const uint32_t SQ5_3     = 3;
            static const uint32_t SQ5_4     = 4;
            static const uint32_t SQ6_0     = 6;
            static const uint32_t SQ6_1     = 7;
            static const uint32_t SQ6_2     = 8;
            static const uint32_t SQ6_3     = 9;
            static const uint32_t SQ6_4     = 10;
            static const uint32_t SQ7_0     = 12;
            static const uint32_t SQ7_1     = 13;
            static const uint32_t SQ7_2     = 14;
            static const uint32_t SQ7_3     = 15;
            static const uint32_t SQ7_4     = 16;
            static const uint32_t SQ8_0     = 18;
            static const uint32_t SQ8_1     = 19;
            static const uint32_t SQ8_2     = 20;
            static const uint32_t SQ8_3     = 21;
            static const uint32_t SQ8_4     = 22;
            static const uint32_t SQ9_0     = 24;
            static const uint32_t SQ9_1     = 25;
            static const uint32_t SQ9_2     = 26;
            static const uint32_t SQ9_3     = 27;
            static const uint32_t SQ9_4     = 28;
        };

        struct SQR3
        {
            static const uint32_t SQ10_0    = 0;
            static const uint32_t SQ10_1    = 1;
            static const uint32_t SQ10_2    = 2;
            static const uint32_t SQ10_3    = 3;
            static const uint32_t SQ10_4    = 4;
            static const uint32_t SQ11_0    = 6;
            static const uint32_t SQ11_1    = 7;
            static const uint32_t SQ11_2    = 8;
            static const uint32_t SQ11_3    = 9;
            static const uint32_t SQ11_4    = 10;
            static const uint32_t SQ12_0    = 12;
            static const uint32_t SQ12_1    = 13;
            static const uint32_t SQ12_2    = 14;
            static const uint32_t SQ12_3    = 15;
            static const uint32_t SQ12_4    = 16;
            static const uint32_t SQ13_0    = 18;
            static const uint32_t SQ13_1    = 19;
            static const uint32_t SQ13_2    = 20;
            static const uint32_t SQ13_3    = 21;
            static const uint32_t SQ13_4    = 22;
            static const uint32_t SQ14_0    = 24;
            static const uint32_t SQ14_1    = 25;
            static const uint32_t SQ14_2    = 26;
            static const uint32_t SQ14_3    = 27;
            static const uint32_t SQ14_4    = 28;
        };

        struct SQR4
        {
            static const uint32_t SQ15_0    = 0;
            static const uint32_t SQ15_1    = 1;
            static const uint32_t SQ15_2    = 2;
            static const uint32_t SQ15_3    = 3;
            static const uint32_t SQ15_4    = 4;
            static const uint32_t SQ16_0    = 6;
            static const uint32_t SQ16_1    = 7;
            static const uint32_t SQ16_2    = 8;
            static const uint32_t SQ16_3    = 9;
            static const uint32_t SQ16_4    = 10;
        };

        struct JSQR
        {
            static const uint32_t JL_0      = 0;
            static const uint32_t JL_1      = 1;
            static const uint32_t JEXTSEL_0 = 2;
            static const uint32_t JEXTSEL_1 = 3;
            static const uint32_t JEXTSEL_2 = 4;
            static const uint32_t JEXTSEL_3 = 5;
            static const uint32_t JEXTEN_0  = 6;
            static const uint32_t JEXTEN_1  = 7;
            static const uint32_t JSQ1_0    = 8;
            static const uint32_t JSQ1_1    = 9;
            static const uint32_t JSQ1_2    = 10;
            static const uint32_t JSQ1_3    = 11;
            static const uint32_t JSQ1_4    = 12;
            static const uint32_t JSQ2_0    = 14;
            static const uint32_t JSQ2_1    = 15;
            static const uint32_t JSQ2_2    = 16;
            static const uint32_t JSQ2_3    = 17;
            static const uint32_t JSQ2_4    = 18;
            static const uint32_t JSQ3_0    = 20;
            static const uint32_t JSQ3_1    = 21;
            static const uint32_t JSQ3_2    = 22;
            static const uint32_t JSQ3_3    = 23;
            static const uint32_t JSQ3_4    = 24;
            static const uint32_t JSQ4_0    = 26;
            static const uint32_t JSQ4_1    = 27;
            static const uint32_t JSQ4_2    = 28;
            static const uint32_t JSQ4_3    = 29;
            static const uint32_t JSQ4_4    = 30;
        };

        struct OFRy
        {
            static const uint32_t OFFSETy_0     = 0;
            static const uint32_t OFFSETy_1     = 1;
            static const uint32_t OFFSETy_2     = 2;
            static const uint32_t OFFSETy_3     = 3;
            static const uint32_t OFFSETy_4     = 4;
            static const uint32_t OFFSETy_5     = 5;
            static const uint32_t OFFSETy_6     = 6;
            static const uint32_t OFFSETy_7     = 7;
            static const uint32_t OFFSETy_8     = 8;
            static const uint32_t OFFSETy_9     = 9;
            static const uint32_t OFFSETy_10    = 10;
            static const uint32_t OFFSETy_11    = 11;
            static const uint32_t OFFSETy_CH_0  = 26;
            static const uint32_t OFFSETy_CH_1  = 27;
            static const uint32_t OFFSETy_CH_2  = 28;
            static const uint32_t OFFSETy_CH_3  = 29;
            static const uint32_t OFFSETy_CH_4  = 30;
            static const uint32_t OFFSETy_EN    = 31;
        };

        struct AWD2CR
        {
            static const uint32_t AWD2CH_0      = 0;
            static const uint32_t AWD2CH_1      = 1;
            static const uint32_t AWD2CH_2      = 2;
            static const uint32_t AWD2CH_3      = 3;
            static const uint32_t AWD2CH_4      = 4;
            static const uint32_t AWD2CH_5      = 5;
            static const uint32_t AWD2CH_6      = 6;
            static const uint32_t AWD2CH_7      = 7;
            static const uint32_t AWD2CH_8      = 8;
            static const uint32_t AWD2CH_9      = 9;
            static const uint32_t AWD2CH_10     = 10;
            static const uint32_t AWD2CH_11     = 11;
            static const uint32_t AWD2CH_12     = 12;
            static const uint32_t AWD2CH_13     = 13;
            static const uint32_t AWD2CH_14     = 14;
            static const uint32_t AWD2CH_15     = 15;
            static const uint32_t AWD2CH_16     = 16;
            static const uint32_t AWD2CH_17     = 17;
            static const uint32_t AWD2CH_18     = 18;
        };

        struct AWD3CR
        {
            static const uint32_t AWD3CH_0      = 0;
            static const uint32_t AWD3CH_1      = 1;
            static const uint32_t AWD3CH_2      = 2;
            static const uint32_t AWD3CH_3      = 3;
            static const uint32_t AWD3CH_4      = 4;
            static const uint32_t AWD3CH_5      = 5;
            static const uint32_t AWD3CH_6      = 6;
            static const uint32_t AWD3CH_7      = 7;
            static const uint32_t AWD3CH_8      = 8;
            static const uint32_t AWD3CH_9      = 9;
            static const uint32_t AWD3CH_10     = 10;
            static const uint32_t AWD3CH_11     = 11;
            static const uint32_t AWD3CH_12     = 12;
            static const uint32_t AWD3CH_13     = 13;
            static const uint32_t AWD3CH_14     = 14;
            static const uint32_t AWD3CH_15     = 15;
            static const uint32_t AWD3CH_16     = 16;
            static const uint32_t AWD3CH_17     = 17;
            static const uint32_t AWD3CH_18     = 18;
        };

        struct DIFSEL
        {
            static const uint32_t DIFSEL_0      = 0;
            static const uint32_t DIFSEL_1      = 1;
            static const uint32_t DIFSEL_2      = 2;
            static const uint32_t DIFSEL_3      = 3;
            static const uint32_t DIFSEL_4      = 4;
            static const uint32_t DIFSEL_5      = 5;
            static const uint32_t DIFSEL_6      = 6;
            static const uint32_t DIFSEL_7      = 7;
            static const uint32_t DIFSEL_8      = 8;
            static const uint32_t DIFSEL_9      = 9;
            static const uint32_t DIFSEL_10     = 10;
            static const uint32_t DIFSEL_11     = 11;
            static const uint32_t DIFSEL_12     = 12;
            static const uint32_t DIFSEL_13     = 13;
            static const uint32_t DIFSEL_14     = 14;
            static const uint32_t DIFSEL_15     = 15;
            static const uint32_t DIFSEL_16     = 16;
            static const uint32_t DIFSEL_17     = 17;
            static const uint32_t DIFSEL_18     = 18;
        };

        struct CALFACT
        {
            static const uint32_t CALFACT_S_0   = 0;
            static const uint32_t CALFACT_S_1   = 1;
            static const uint32_t CALFACT_S_2   = 2;
            static const uint32_t CALFACT_S_3   = 3;
            static const uint32_t CALFACT_S_4   = 4;
            static const uint32_t CALFACT_S_5   = 5;
            static const uint32_t CALFACT_S_6   = 6;
            static const uint32_t CALFACT_D_0   = 16;
            static const uint32_t CALFACT_D_1   = 17;
            static const uint32_t CALFACT_D_2   = 18;
            static const uint32_t CALFACT_D_3   = 19;
            static const uint32_t CALFACT_D_4   = 20;
            static const uint32_t CALFACT_D_5   = 21;
            static const uint32_t CALFACT_D_6   = 22;
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
                case Id::ADC1:
                    return (Block*)ADC1_BASE_ADDRESS;
                case Id::ADC2:
                    return (Block*)ADC2_BASE_ADDRESS;
            }

            return nullptr;
        }

    protected:
        // Register block base addresses
        static const uint32_t ADC1_BASE_ADDRESS = AHB2_BASE_ADDRESS + 0x08040000;
        static const uint32_t ADC2_BASE_ADDRESS = ADC1_BASE_ADDRESS + 0x0100;
};


class ADC_CommonRegisters
{
    public:
        struct Block
        {
            Register32 CSR;     // Common status register               Offset 0x00
            Register32 _RESERVED_1; // Reserved                         Offset 0x04
            Register32 CCR;     // Common control register              Offset 0x08
            Register32 CDR;     // Common regular data reg dual mode    Offset 0x0C
        } __attribute__((packed));

        struct CSR
        {
            static const uint32_t ADRDY_MST     = 0;
            static const uint32_t EOSMP_MST     = 1;
            static const uint32_t EOC_MST       = 2;
            static const uint32_t EOS_MST       = 3;
            static const uint32_t OVR_MST       = 4;
            static const uint32_t JEOC_MST      = 5;
            static const uint32_t JEOS_MST      = 6;
            static const uint32_t AWD1_MST      = 7;
            static const uint32_t AWD2_MST      = 8;
            static const uint32_t AWD3_MST      = 9;
            static const uint32_t JQOVF_MST     = 10;
            static const uint32_t ADRDY_SLV     = 16;
            static const uint32_t EOSMP_SLV     = 17;
            static const uint32_t EOC_SLV       = 18;
            static const uint32_t EOS_SLV       = 19;
            static const uint32_t OVR_SLV       = 20;
            static const uint32_t JEOC_SLV      = 21;
            static const uint32_t JEOS_SLV      = 22;
            static const uint32_t AWD1_SLV      = 23;
            static const uint32_t AWD2_SLV      = 24;
            static const uint32_t AWD3_SLV      = 25;
            static const uint32_t JQOVF_SLV     = 26;
        };

        struct CCR
        {
            static const uint32_t DUAL_0        = 0;
            static const uint32_t DUAL_1        = 1;
            static const uint32_t DUAL_2        = 2;
            static const uint32_t DUAL_3        = 3;
            static const uint32_t DUAL_4        = 4;
            static const uint32_t DELAY_0       = 8;
            static const uint32_t DELAY_1       = 9;
            static const uint32_t DELAY_2       = 10;
            static const uint32_t DELAY_3       = 11;
            static const uint32_t DMACFG        = 13;
            static const uint32_t MDMA_0        = 14;
            static const uint32_t MDMA_1        = 15;
            static const uint32_t CKMODE_0      = 16;
            static const uint32_t CKMODE_1      = 17;
            static const uint32_t PRESC_0       = 18;
            static const uint32_t PRESC_1       = 19;
            static const uint32_t PRESC_2       = 20;
            static const uint32_t PRESC_3       = 21;
            static const uint32_t VREFEN        = 22;
            static const uint32_t CH17SEL       = 23;
            static const uint32_t CH18SEL       = 24;
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
        static const uint32_t BASE_ADDRESS = AHB2_BASE_ADDRESS + 0x08040300;
};


}   // namespace mcu
