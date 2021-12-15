/**
 * @file        RCC.h
 *
 * Driver for RCC peripheral on STM32L4xx
 *
 * @author:     Oliver Rockstedt <info@sourcebox.de>
 * @license     MIT
 */


#pragma once


// System libraries
#include <cstdint>


namespace mcu {


class RCC
{
    public:
        enum class PLL_Source
        {
            NONE,
            MSI,
            HSI16,
            HSE
        };

        enum class PLLR_Divider
        {
            DIV_2 = 0b00,
            DIV_4 = 0b01,
            DIV_6 = 0b10,
            DIV_8 = 0b11
        };

        enum class PLLQ_Divider
        {
            DIV_2 = 0b00,
            DIV_4 = 0b01,
            DIV_6 = 0b10,
            DIV_8 = 0b11
        };

        enum class PLLP_Divider
        {
            DIV_7   = 0b0,
            DIV_17  = 0b1
        };

        enum class SYSCLK_Source
        {
            MSI     = 0b00,
            HSI16   = 0b01,
            HSE     = 0b10,
            PLLCLK  = 0b11
        };

        enum class AHB_Prescaler
        {
            DIV_1,
            DIV_2,
            DIV_4,
            DIV_8,
            DIV_16,
            DIV_64,
            DIV_128,
            DIV_256,
            DIV_512
        };

        enum class APB1_Prescaler
        {
            DIV_1,
            DIV_2,
            DIV_4,
            DIV_8,
            DIV_16
        };

        enum class APB2_Prescaler
        {
            DIV_1,
            DIV_2,
            DIV_4,
            DIV_8,
            DIV_16
        };

        enum class MCO_Source
        {
            NONE    = 0b0000,
            SYSCLK  = 0b0001,
            MSI     = 0b0010,
            HSI16   = 0b0011,
            HSE     = 0b0100,
            PLLCLK  = 0b0101,
            LSI     = 0b0110,
            LSE     = 0b0111,
            HSI48   = 0b1000
        };

        enum class MCO_Prescaler
        {
            DIV_1   = 0b000,
            DIV_2   = 0b001,
            DIV_4   = 0b010,
            DIV_8   = 0b011,
            DIV_16  = 0b100
        };

        static const int MSI_OSCILLATOR_FREQ = 4000000;
        static const int HSI16_OSCILLATOR_FREQ = 16000000;

        /**
         * Configuration settings
         *
         * Default settings for 80 MHz core clock (PLL driven by MSI)
         */
        struct Config
        {
            uint32_t oscillatorFreq = MSI_OSCILLATOR_FREQ;
            bool enableHSI16 = false;
            bool enableHSE = false;
            bool enableHSEBypass = false;
            bool enablePLL = true;
            PLL_Source pllSource = PLL_Source::MSI;
            uint8_t pllDivider = 1;
            uint8_t pllMultiplier = 40;
            PLLR_Divider pllrDivider = PLLR_Divider::DIV_2;
            PLLQ_Divider pllqDivider = PLLQ_Divider::DIV_2;
            PLLP_Divider pllpDivider = PLLP_Divider::DIV_7;
            SYSCLK_Source sysclkSource = SYSCLK_Source::PLLCLK;
            AHB_Prescaler ahbPrescaler = AHB_Prescaler::DIV_1;
            APB1_Prescaler apb1Prescaler = APB1_Prescaler::DIV_1;
            APB2_Prescaler apb2Prescaler = APB2_Prescaler::DIV_1;
            bool adaptFlashSettings = true;
        };

        /**
         * Return reference to peripheral
         *
         * @return              Reference to peripheral
         */
        static RCC& get()
        {
            return instance;
        }

        /**
         * Set configuration
         *
         * @param config        Config struct
         */
        void configure(Config& config);

        /**
         * Predefined configuration templates
         */
        enum class Config_Template
        {
            PLL_MSI_80MHZ,
            PLL_HSI16_80MHZ,
            PLL_HSE8_80MHZ,
            PLL_HSE8_BYPASS_80MHZ,
        };

        /**
         * Return configuration struct with predefined settings
         *
         * @param tmpl          Template according to enum
         */
        Config getConfigTemplate(Config_Template tmpl);

        /**
         * Return SYSCLK clock frequency
         *
         * @return          SYSCLK clock frequency in Hz
         */
        uint32_t getSYSCLKFreq();

        /**
         * Return HCLK clock frequency for AHB bus
         *
         * @return          HCLK clock frequency in Hz
         */
        uint32_t getHCLKFreq();

        /**
         * Return PCLK1 clock frequency for APB1 bus
         *
         * @return          PCLK1 clock frequency in Hz
         */
        uint32_t getPCLK1Freq();

        /**
         * Return PCLK2 clock frequency for APB2 bus
         *
         * @return          PCLK2 clock frequency in Hz
         */
        uint32_t getPCLK2Freq();

        /**
         * Set source for MCO output
         *
         * @param value     Source according to enum
         */
        void setMCOSource(MCO_Source value);

        /**
         * Set prescaler for MCO output
         *
         * @param value     Prescaler according to enum
         */
        void setMCOPrescaler(MCO_Prescaler value);

    protected:
        /**
         * Private constructors because of singleton pattern, no copy allowed
         */
        RCC() {}
        RCC(const RCC&) = delete;
        RCC& operator = (const RCC&) = delete;
        RCC& operator = (RCC&&) = delete;

        /**
         * Enable HSI16 clock
         */
        void enableHSI16Clock();

        /**
         * Enable HSE clock
         *
         * @param bypass    Enable bypass mode for external clock
         */
        void enableHSEClock(bool bypass=false);

        /**
         * Disable HSE clock
         */
        void disableHSEClock();

        /**
         * Set source for PLL
         *
         * @param value     Clock source according to enum
         */
        void setPLLSource(PLL_Source value);

        /**
         * Set divider for PLL
         *
         * @param value     Divider in range 1..8
         */
        void setPLLDivider(int value);

        /**
         * Set multiplier for PLL
         *
         * @param value     Multiplier in range 8..86
         */
        void setPLLMultiplier(int value);

        /**
         * Set divider for PLLR
         *
         * @param value     Divider according to enum
         */
        void setPLLRDivider(PLLR_Divider value);

        /**
         * Set divider for PLLQ
         *
         * @param value     Divider according to enum
         */
        void setPLLQDivider(PLLQ_Divider value);

        /**
         * Set divider for PLLP
         *
         * @param value     Divider according to enum
         */
        void setPLLPDivider(PLLP_Divider value);

        /**
         * Enable PLL
         */
        void enablePLL();

        /**
         * Disable PLL
         */
        void disablePLL();

        /**
         * Return PLL clock frequency
         */
        uint32_t getPLLFreq();

        /**
         * Set source for SYSCLK
         *
         * @param value     Clock source according to enum
         */
        void setSYSCLKSource(SYSCLK_Source value);

        /**
         * Set AHB prescaler for HCLK bus
         *
         * @param value     Prescaler value 1..512 according to enum
         */
        void setAHBPrescaler(AHB_Prescaler value);

        /**
         * Set APB1 prescaler for PCLK1 bus
         *
         * @param value     Prescaler value 1..16 according to enum
         */
        void setAPB1Prescaler(APB1_Prescaler value);

        /**
         * Set APB2 prescaler for PCLK2 bus
         *
         * @param value     Prescaler value 1..16 according to enum
         */
        void setAPB2Prescaler(APB2_Prescaler value);

        uint32_t oscillatorFreq = MSI_OSCILLATOR_FREQ;

        struct Prescalers
        {
            uint16_t prescaler;
            uint8_t bits;
        };

        static constexpr Prescalers ahbPrescalers[] =
        {
            { 1,    0b0000 },
            { 2,    0b1000 },
            { 4,    0b1001 },
            { 8,    0b1010 },
            { 16,   0b1011 },
            { 64,   0b1100 },
            { 128,  0b1101 },
            { 256,  0b1110 },
            { 512,  0b1111 }
        };

        static constexpr Prescalers apbPrescalers[] =
        {
            { 1,    0b000 },
            { 2,    0b100 },
            { 4,    0b101 },
            { 8,    0b110 },
            { 16,   0b111 }
        };

        /**
         * Singleton instance
         */
        static RCC instance;
};


}   // namespace mcu
