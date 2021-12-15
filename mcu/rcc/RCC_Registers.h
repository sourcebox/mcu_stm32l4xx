/**
 * @file        RCC_Registers.h
 *
 * Register definitions for RCC peripheral on STM32L4xx
 *
 * @author:     Oliver Rockstedt <info@sourcebox.de>
 * @license     MIT
 */


#pragma once


// This component includes
#include "../core/mcu_base.h"
#include "../utility/register.h"

// System libraries
#include <cstdint>


namespace mcu {


class RCC_Registers
{
    public:
        struct Block
        {
            Register32 CR;          // Clock control register           Offset 0x00
            Register32 ICSCR;       // Internal clock sources cal reg   Offset 0x04
            Register32 CFGR;        // Clock configuration register     Offset 0x08
            Register32 PLLCFGR;     // PLL configuration register       Offset 0x0C
            Register32 PLLSAI1CFGR; // PLLSAI1 configuration register   Offset 0x10
            Register32 _RESERVED_1; // Reserved                         Offset 0x14
            Register32 CIER;        // Clock interrupt enable register  Offset 0x18
            Register32 CIFR;        // Clock interrupt flag register    Offset 0x1C
            Register32 CICR;        // Clock interrupt clear register   Offset 0x20
            Register32 _RESERVED_2; // Reserved                         Offset 0x24
            Register32 AHB1RSTR;    // AHB1 peripheral reset register   Offset 0x28
            Register32 AHB2RSTR;    // AHB2 peripheral reset register   Offset 0x2C
            Register32 AHB3RSTR;    // AHB3 peripheral reset register   Offset 0x30
            Register32 _RESERVED_3; // Reserved                         Offset 0x34
            Register32 APB1RSTR1;   // APB1 peripheral reset register 1 Offset 0x38
            Register32 APB1RSTR2;   // APB1 peripheral reset register 2 Offset 0x3C
            Register32 APB2RSTR;    // APB2 peripheral reset register   Offset 0x40
            Register32 _RESERVED_4; // Reserved                         Offset 0x44
            Register32 AHB1ENR;     // AHB1 peripheral clock enable reg Offset 0x48
            Register32 AHB2ENR;     // AHB2 peripheral clock enable reg Offset 0x4C
            Register32 AHB3ENR;     // AHB3 peripheral clock enable reg Offset 0x50
            Register32 _RESERVED_5; // Reserved                         Offset 0x54
            Register32 APB1ENR1;    // APB1 peripheral clk enable reg 1 Offset 0x58
            Register32 APB1ENR2;    // APB1 peripheral clk enable reg 2 Offset 0x5C
            Register32 APB2ENR;     // APB2 peripheral clock enable reg Offset 0x60
            Register32 _RESERVED_6; // Reserved                         Offset 0x64
            Register32 AHB1SMENR;   // AHB1 periph clk enable sleep reg Offset 0x68
            Register32 AHB2SMENR;   // AHB2 periph clk enable sleep reg Offset 0x6C
            Register32 AHB3SMENR;   // AHB3 periph clk enable sleep reg Offset 0x70
            Register32 _RESERVED_7; // Reserved                         Offset 0x74
            Register32 APB1SMENR1;  // APB1 periph clk enable slp reg 1 Offset 0x78
            Register32 APB1SMENR2;  // APB1 periph clk enable slp reg 2 Offset 0x7C
            Register32 APB2SMENR;   // APB2 periph clk enable sleep reg Offset 0x80
            Register32 _RESERVED_8; // Reserved                         Offset 0x84
            Register32 CCIPR;       // Periph independent clk conf reg  Offset 0x88
            Register32 _RESERVED_9;
            Register32 BDCR;        // Backup domain control register   Offset 0x90
            Register32 CSR;         // Control/status register          Offset 0x94
            Register32 CRRCR;       // Clock recovery RC register       Offset 0x98
            Register32 CCIPR2;      // Periph indep clock conf reg 2    Offset 0x9C
        } __attribute__((packed));

        struct CR
        {
            static const uint32_t MSION        = 0;
            static const uint32_t MSIRDY       = 1;
            static const uint32_t MSIPLLEN     = 2;
            static const uint32_t MSIRGSEL     = 3;
            static const uint32_t MSIRANGE_0   = 4;
            static const uint32_t MSIRANGE_1   = 5;
            static const uint32_t MSIRANGE_2   = 6;
            static const uint32_t MSIRANGE_3   = 7;
            static const uint32_t HSION        = 8;
            static const uint32_t HSIKERON     = 9;
            static const uint32_t HSIRDY       = 10;
            static const uint32_t HSIASFS      = 11;
            static const uint32_t HSEON        = 16;
            static const uint32_t HSERDY       = 17;
            static const uint32_t HSEBYP       = 18;
            static const uint32_t CSSON        = 19;
            static const uint32_t PLLON        = 24;
            static const uint32_t PLLRDY       = 25;
            static const uint32_t PLLSAI1ON    = 26;
            static const uint32_t PLLSAI1RDY   = 27;
        };

        struct CFGR
        {
            static const uint32_t SW_0         = 0;
            static const uint32_t SW_1         = 1;
            static const uint32_t SWS_0        = 2;
            static const uint32_t SWS_1        = 3;
            static const uint32_t HPRE_0       = 4;
            static const uint32_t HPRE_1       = 5;
            static const uint32_t HPRE_2       = 6;
            static const uint32_t HPRE_3       = 7;
            static const uint32_t PPRE1_0      = 8;
            static const uint32_t PPRE1_1      = 9;
            static const uint32_t PPRE1_2      = 10;
            static const uint32_t PPRE2_0      = 11;
            static const uint32_t PPRE2_1      = 12;
            static const uint32_t PPRE2_2      = 13;
            static const uint32_t STOPWUCK     = 15;
            static const uint32_t MCOSEL_0     = 24;
            static const uint32_t MCOSEL_1     = 25;
            static const uint32_t MCOSEL_2     = 26;
            static const uint32_t MCOSEL_3     = 27;
            static const uint32_t MCOPRE_0     = 28;
            static const uint32_t MCOPRE_1     = 29;
            static const uint32_t MCOPRE_2     = 30;
        };

        struct PLLCFGR
        {
            static const uint32_t PLLSRC_0     = 0;
            static const uint32_t PLLSRC_1     = 1;
            static const uint32_t PLLM_0       = 4;
            static const uint32_t PLLM_1       = 5;
            static const uint32_t PLLM_2       = 6;
            static const uint32_t PLLN_0       = 8;
            static const uint32_t PLLN_1       = 9;
            static const uint32_t PLLN_2       = 10;
            static const uint32_t PLLN_3       = 11;
            static const uint32_t PLLN_4       = 12;
            static const uint32_t PLLN_5       = 13;
            static const uint32_t PLLN_6       = 14;
            static const uint32_t PLLPEN       = 16;
            static const uint32_t PLLP         = 17;
            static const uint32_t PLLQEN       = 20;
            static const uint32_t PLLQ_0       = 21;
            static const uint32_t PLLQ_1       = 22;
            static const uint32_t PLLREN       = 24;
            static const uint32_t PLLR_0       = 25;
            static const uint32_t PLLR_1       = 26;
            static const uint32_t PLLPDIV_0    = 27;
            static const uint32_t PLLPDIV_1    = 28;
            static const uint32_t PLLPDIV_2    = 29;
            static const uint32_t PLLPDIV_3    = 30;
            static const uint32_t PLLPDIV_4    = 31;
        };

        struct PLLSAI1CFGR
        {
            static const uint32_t PLLSAI1N_0       = 8;
            static const uint32_t PLLSAI1N_1       = 9;
            static const uint32_t PLLSAI1N_2       = 10;
            static const uint32_t PLLSAI1N_3       = 11;
            static const uint32_t PLLSAI1N_4       = 12;
            static const uint32_t PLLSAI1N_5       = 13;
            static const uint32_t PLLSAI1N_6       = 14;
            static const uint32_t PLLSAI1PEN       = 16;
            static const uint32_t PLLSAI1P         = 17;
            static const uint32_t PLLSAI1QEN       = 20;
            static const uint32_t PLLSAI1Q_0       = 21;
            static const uint32_t PLLSAI1Q_1       = 22;
            static const uint32_t PLLSAI1REN       = 24;
            static const uint32_t PLLSAI1R_0       = 25;
            static const uint32_t PLLSAI1R_1       = 26;
            static const uint32_t PLLSAI1PDIV_0    = 27;
            static const uint32_t PLLSAI1PDIV_1    = 28;
            static const uint32_t PLLSAI1PDIV_2    = 29;
            static const uint32_t PLLSAI1PDIV_3    = 30;
            static const uint32_t PLLSAI1PDIV_4    = 31;
        };

        struct CIER
        {
            static const uint32_t LSIRDYIE     = 0;
            static const uint32_t LSERDYIE     = 1;
            static const uint32_t MSIRDYIE     = 2;
            static const uint32_t HSIRDYIE     = 3;
            static const uint32_t HSERDYIE     = 4;
            static const uint32_t PLLRDYIE     = 5;
            static const uint32_t PLLSAI1RDYIE = 6;
            static const uint32_t LSECSSIE     = 9;
            static const uint32_t HSI48RDYIE   = 10;
        };

        struct CIFR
        {
            static const uint32_t LSIRDYF      = 0;
            static const uint32_t LSERDYF      = 1;
            static const uint32_t MSIRDYF      = 2;
            static const uint32_t HSIRDYF      = 3;
            static const uint32_t HSERDYF      = 4;
            static const uint32_t PLLRDYF      = 5;
            static const uint32_t PLLSAI1RDYF  = 6;
            static const uint32_t CSSF         = 8;
            static const uint32_t LSECSSF      = 9;
            static const uint32_t HSI48RDYF    = 10;
        };

        struct CICR
        {
            static const uint32_t LSIRDYC      = 0;
            static const uint32_t LSERDYC      = 1;
            static const uint32_t MSIRDYC      = 2;
            static const uint32_t HSIRDYC      = 3;
            static const uint32_t HSERDYC      = 4;
            static const uint32_t PLLRDYC      = 5;
            static const uint32_t PLLSAI1RDYC  = 6;
            static const uint32_t CSSC         = 8;
            static const uint32_t LSECSSC      = 9;
            static const uint32_t HSI48RDYC    = 10;
        };

        struct AHB1RSTR
        {
            static const uint32_t DMA1RST      = 0;
            static const uint32_t DMA2RST      = 1;
            static const uint32_t FLASHRST     = 8;
            static const uint32_t CRCRST       = 12;
            static const uint32_t TSCRST       = 16;
        };

        struct AHB2RSTR
        {
            static const uint32_t GPIOARST     = 0;
            static const uint32_t GPIOBRST     = 1;
            static const uint32_t GPIOCRST     = 2;
            static const uint32_t GPIODRST     = 3;
            static const uint32_t GPIOERST     = 4;
            static const uint32_t GPIOHRST     = 7;
            static const uint32_t ADCRST       = 13;
            static const uint32_t AESRST       = 16;
            static const uint32_t RNGRST       = 18;
        };

        struct APB1RSTR1
        {
            static const uint32_t TIM2RST      = 0;
            static const uint32_t TIM3RST      = 1;
            static const uint32_t TIM6RST      = 4;
            static const uint32_t TIM7RST      = 5;
            static const uint32_t LCDRST       = 9;
            static const uint32_t SPI2RST      = 14;
            static const uint32_t SPI3RST      = 15;
            static const uint32_t USART2RST    = 17;
            static const uint32_t USART3RST    = 18;
            static const uint32_t UART4RST     = 19;
            static const uint32_t I2C1RST      = 21;
            static const uint32_t I2C2RST      = 22;
            static const uint32_t I2C3RST      = 23;
            static const uint32_t CRSRST       = 24;
            static const uint32_t CAN1RST      = 25;
            static const uint32_t USBFSRST     = 26;
            static const uint32_t PWRRST       = 28;
            static const uint32_t DAC1RST      = 29;
            static const uint32_t OPAMPRST     = 30;
            static const uint32_t LPTIM1RST    = 31;
        };

        struct APB1RSTR2
        {
            static const uint32_t LPUART1RST   = 0;
            static const uint32_t I2C4RST      = 1;
            static const uint32_t SWPMI1RST    = 2;
            static const uint32_t LPTIM2RST    = 5;
        };

        struct APB2RSTR
        {
            static const uint32_t SYSCFGRST    = 0;
            static const uint32_t SDMMC1RST    = 10;
            static const uint32_t TIM1RST      = 11;
            static const uint32_t SPI1RST      = 12;
            static const uint32_t USART1RST    = 14;
            static const uint32_t TIM15RST     = 16;
            static const uint32_t TIM16RST     = 17;
            static const uint32_t SAI1RST      = 21;
            static const uint32_t DFSDM1RST    = 24;
        };

        struct AHB1ENR
        {
            static const uint32_t DMA1EN       = 0;
            static const uint32_t DMA2EN       = 1;
            static const uint32_t FLASHEN      = 8;
            static const uint32_t CRCEN        = 12;
            static const uint32_t TSCEN        = 16;
        };

        struct AHB2ENR
        {
            static const uint32_t GPIOAEN      = 0;
            static const uint32_t GPIOBEN      = 1;
            static const uint32_t GPIOCEN      = 2;
            static const uint32_t GPIODEN      = 3;
            static const uint32_t GPIOEEN      = 4;
            static const uint32_t GPIOHEN      = 7;
            static const uint32_t ADCEN        = 13;
            static const uint32_t AESEN        = 16;
            static const uint32_t RNGEN        = 18;
        };

        struct AHB3ENR
        {
            static const uint32_t QSPIEN       = 8;
        };

        struct APB1ENR1
        {
            static const uint32_t TIM2EN       = 0;
            static const uint32_t TIM3EN       = 1;
            static const uint32_t TIM6EN       = 4;
            static const uint32_t TIM7EN       = 5;
            static const uint32_t LCDEN        = 9;
            static const uint32_t RTCAPBEN     = 10;
            static const uint32_t WWDGEN       = 11;
            static const uint32_t SPI2EN       = 14;
            static const uint32_t SPI3EN       = 15;
            static const uint32_t USART2EN     = 17;
            static const uint32_t USART3EN     = 18;
            static const uint32_t UART4EN      = 19;
            static const uint32_t I2C1EN       = 21;
            static const uint32_t I2C2EN       = 22;
            static const uint32_t I2C3EN       = 23;
            static const uint32_t CRSEN        = 24;
            static const uint32_t CAN1EN       = 25;
            static const uint32_t USBFSEN      = 26;
            static const uint32_t PWREN        = 28;
            static const uint32_t DAC1EN       = 29;
            static const uint32_t OPAMPEN      = 30;
            static const uint32_t LPTIM1EN     = 31;
        };

        struct APB1ENR2
        {
            static const uint32_t LPUART1EN    = 0;
            static const uint32_t I2C4EN       = 1;
            static const uint32_t SWPMI1EN     = 2;
            static const uint32_t LPTIM2EN     = 5;
        };

        struct APB2ENR
        {
            static const uint32_t SYSCFGEN     = 0;
            static const uint32_t FWEN         = 7;
            static const uint32_t SDMMC1EN     = 10;
            static const uint32_t TIM1EN       = 11;
            static const uint32_t SPI1EN       = 12;
            static const uint32_t USART1EN     = 14;
            static const uint32_t TIM15EN      = 16;
            static const uint32_t TIM16EN      = 17;
            static const uint32_t SAI15EN      = 21;
            static const uint32_t DFSDM1EN     = 24;
        };

        struct AHB1SMENR
        {
            static const uint32_t DMA1SMEN     = 0;
            static const uint32_t DMA2SMEN     = 1;
            static const uint32_t FLASHSMEN    = 8;
            static const uint32_t SRAM1SMEN    = 9;
            static const uint32_t CRCSMEN      = 12;
            static const uint32_t TSCSMEN      = 16;
        };

        struct AHB2SMENR
        {
            static const uint32_t GPIOASMEN    = 0;
            static const uint32_t GPIOBSMEN    = 1;
            static const uint32_t GPIOCSMEN    = 2;
            static const uint32_t GPIODSMEN    = 3;
            static const uint32_t GPIOESMEN    = 4;
            static const uint32_t GPIOHSMEN    = 7;
            static const uint32_t SRAM2SMEN    = 9;
            static const uint32_t ADCSMEN      = 13;
            static const uint32_t AESSMEN      = 16;
            static const uint32_t RNGSMEN      = 18;
        };

        struct AHB3SMENR
        {
            static const uint32_t QSPISMEN     = 8;
        };

        struct APB1SMENR1
        {
            static const uint32_t TIM2SMEN     = 0;
            static const uint32_t TIM3SMEN     = 1;
            static const uint32_t TIM6SMEN     = 4;
            static const uint32_t TIM7SMEN     = 5;
            static const uint32_t LCDSMEN      = 9;
            static const uint32_t RTCAPBSMEN   = 10;
            static const uint32_t WWDGSMEN     = 11;
            static const uint32_t SPI2SMEN     = 14;
            static const uint32_t SPI3SMEN     = 15;
            static const uint32_t USART2SMEN   = 17;
            static const uint32_t USART3SMEN   = 18;
            static const uint32_t UART4SMEN    = 19;
            static const uint32_t I2C1SMEN     = 21;
            static const uint32_t I2C2SMEN     = 22;
            static const uint32_t I2C3SMEN     = 23;
            static const uint32_t CRSSMEN      = 24;
            static const uint32_t CAN1SMEN     = 25;
            static const uint32_t USBFSSMEN    = 26;
            static const uint32_t PWRSMEN      = 28;
            static const uint32_t DAC1SMEN     = 29;
            static const uint32_t OPAMPSMEN    = 30;
            static const uint32_t LPTIM1SMEN   = 31;
        };

        struct APB1SMENR2
        {
            static const uint32_t LPUART1SMEN  = 0;
            static const uint32_t SWPMI1SMEN   = 2;
            static const uint32_t LPTIM2SMEN   = 5;
        };

        struct APB2SMENR
        {
            static const uint32_t SYSCFGSMEN   = 0;
            static const uint32_t SDMMC1MEN    = 10;
            static const uint32_t TIM1SMEN     = 11;
            static const uint32_t SPI1SMEN     = 12;
            static const uint32_t USART1SMEN   = 14;
            static const uint32_t TIM15SMEN    = 16;
            static const uint32_t TIM16SMEN    = 17;
            static const uint32_t SAI1SMEN     = 21;
        };

        struct CCIPR
        {
            static const uint32_t USART1SEL_0  = 0;
            static const uint32_t USART1SEL_1  = 1;
            static const uint32_t USART2SEL_0  = 2;
            static const uint32_t USART2SEL_1  = 3;
            static const uint32_t USART3SEL_0  = 4;
            static const uint32_t USART3SEL_1  = 5;
            static const uint32_t UART4SEL_0   = 6;
            static const uint32_t UART4SEL_1   = 7;
            static const uint32_t LPUART1SEL_0 = 10;
            static const uint32_t LPUART1SEL_1 = 11;
            static const uint32_t I2C1SEL_0    = 12;
            static const uint32_t I2C1SEL_1    = 13;
            static const uint32_t I2C2SEL_0    = 14;
            static const uint32_t I2C2SEL_1    = 15;
            static const uint32_t I2C3SEL_0    = 16;
            static const uint32_t I2C3SEL_1    = 17;
            static const uint32_t LPTIM1SEL_0  = 18;
            static const uint32_t LPTIM1SEL_1  = 19;
            static const uint32_t LPTIM2SEL_0  = 20;
            static const uint32_t LPTIM2SEL_1  = 21;
            static const uint32_t SAI1SEL_0    = 22;
            static const uint32_t SAI1SEL_1    = 23;
            static const uint32_t CLK48SEL_0   = 26;
            static const uint32_t CLK48SEL_1   = 27;
            static const uint32_t ADCSEL_0     = 28;
            static const uint32_t ADCSEL_1     = 29;
            static const uint32_t SWPMI1SEL    = 30;
        };

        struct BDCR
        {
            static const uint32_t LSEON        = 0;
            static const uint32_t LSERDY       = 1;
            static const uint32_t LSEBYP       = 2;
            static const uint32_t LSEDRV_0     = 3;
            static const uint32_t LSEDRV_1     = 4;
            static const uint32_t LSECSSON     = 5;
            static const uint32_t LSECSSD      = 6;
            static const uint32_t LSESYSDIS    = 7;
            static const uint32_t RTCSEL_0     = 8;
            static const uint32_t RTCSEL_1     = 9;
            static const uint32_t RTCEN        = 15;
            static const uint32_t BDRST        = 16;
            static const uint32_t LSCOEN       = 24;
            static const uint32_t LSCOSEL      = 25;
        };

        struct CSR
        {
            static const uint32_t LSION        = 0;
            static const uint32_t LSIRDY       = 1;
            static const uint32_t LSIPREDIV    = 4;
            static const uint32_t MSISRANGE_0  = 8;
            static const uint32_t MSISRANGE_1  = 9;
            static const uint32_t MSISRANGE_2  = 10;
            static const uint32_t MSISRANGE_3  = 11;
            static const uint32_t RMVF         = 23;
            static const uint32_t FWRSTF       = 24;
            static const uint32_t OBLRSTF      = 25;
            static const uint32_t PINRSTF      = 26;
            static const uint32_t BORRSTF      = 27;
            static const uint32_t SFTRSTF      = 28;
            static const uint32_t IWWGRSTF     = 29;
            static const uint32_t WWDGRSTF     = 30;
            static const uint32_t LPWRRSTF     = 31;
        };

        struct CRRCR
        {
            static const uint32_t HSI48ON      = 0;
            static const uint32_t HSI48RDY     = 1;
            static const uint32_t HSI48CAL_0   = 7;
            static const uint32_t HSI48CAL_1   = 8;
            static const uint32_t HSI48CAL_2   = 9;
            static const uint32_t HSI48CAL_3   = 10;
            static const uint32_t HSI48CAL_4   = 11;
            static const uint32_t HSI48CAL_5   = 12;
            static const uint32_t HSI48CAL_6   = 13;
            static const uint32_t HSI48CAL_7   = 14;
            static const uint32_t HSI48CAL_8   = 15;
        };

        struct CCIPR2
        {
            static const uint32_t I2C4SEL_0    = 0;
            static const uint32_t I2C4SEL_1    = 1;
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
        /**
         * Register block base address
         */
        static const uint32_t BASE_ADDRESS = AHB1_BASE_ADDRESS + 0x00001000;
};


}   // namespace mcu
