/**
 * @file        RCC.cpp
 *
 * Driver for RCC peripheral on STM32L4xx
 *
 * @author:     Oliver Rockstedt <info@sourcebox.de>
 * @license     MIT
 */


// Corresponding header
#include "RCC.h"

// Local includes
#include "RCC_Registers.h"

// This component
#include "../flash/Flash.h"
#include "../utility/bit_manipulation.h"

// System libraries
#include <algorithm>


namespace mcu {


// ============================================================================
// Public members
// ============================================================================


void RCC::configure(Config& config)
{
    oscillatorFreq = config.oscillatorFreq;

    if (config.adaptFlashSettings) {
        Flash flash;
        flash.enablePrefetchBuffer();
        flash.setLatency(4);
    }

    if (config.enableHSI16) {
        enableHSI16Clock();
    }

    if (config.enableHSE) {
        enableHSEClock(config.enableHSEBypass);
    }

    if (config.enablePLL) {
        setSYSCLKSource(SYSCLK_Source::MSI);
        disablePLL();
        setPLLSource(config.pllSource);
        setPLLDivider(config.pllDivider);
        setPLLMultiplier(config.pllMultiplier);
        setPLLRDivider(config.pllrDivider);
        setPLLQDivider(config.pllqDivider);
        setPLLPDivider(config.pllpDivider);
        enablePLL();
    }

    setSYSCLKSource(config.sysclkSource);
    setAHBPrescaler(config.ahbPrescaler);
    setAPB1Prescaler(config.apb1Prescaler);
    setAPB2Prescaler(config.apb2Prescaler);

    if (config.adaptFlashSettings) {
        auto hclkFreq = getHCLKFreq();
        if (hclkFreq <= 16000000) {
            Flash().setLatency(0);
        } else if (hclkFreq > 16000000 && hclkFreq <= 32000000) {
            Flash().setLatency(1);
        } else if (hclkFreq > 32000000 && hclkFreq <= 48000000) {
            Flash().setLatency(2);
        } else if (hclkFreq > 48000000 && hclkFreq <= 64000000) {
            Flash().setLatency(3);
        } else {
            Flash().setLatency(4);
        }
    }
}


RCC::Config RCC::getConfigTemplate(Config_Template tmpl)
{
    Config config;

    switch (tmpl) {
        case Config_Template::PLL_MSI_80MHZ:
            break;
        case Config_Template::PLL_HSI16_80MHZ:
            config.oscillatorFreq = HSI16_OSCILLATOR_FREQ;
            config.enableHSI16 = true;
            config.pllSource = PLL_Source::HSI16;
            config.pllDivider = 2;
            config.pllMultiplier = 20;
            break;
        case Config_Template::PLL_HSE8_80MHZ:
            config.oscillatorFreq = 8000000;
            config.enableHSE = true;
            config.pllSource = PLL_Source::HSE;
            config.pllDivider = 1;
            config.pllMultiplier = 20;
            break;
        case Config_Template::PLL_HSE8_BYPASS_80MHZ:
            config.oscillatorFreq = 8000000;
            config.enableHSE = true;
            config.enableHSEBypass = true;
            config.pllSource = PLL_Source::HSE;
            config.pllDivider = 1;
            config.pllMultiplier = 20;
            break;
    }

    return config;
}


uint32_t RCC::getSYSCLKFreq()
{
    auto registers = RCC_Registers::get();

    auto sysclockSource = (SYSCLK_Source)bitsValue(registers->CFGR, 2, 0);

    switch (sysclockSource) {
        case SYSCLK_Source::MSI:
            return MSI_OSCILLATOR_FREQ;
        case SYSCLK_Source::HSI16:
            return HSI16_OSCILLATOR_FREQ;
        case SYSCLK_Source::HSE:
            return oscillatorFreq;
        case SYSCLK_Source::PLLCLK:
            return getPLLFreq();
    }

    return 0;
}


uint32_t RCC::getHCLKFreq()
{
    auto registers = RCC_Registers::get();

    auto prescalerBits = bitsValue(registers->CFGR, 4, 4);

    for (auto& prescaler : ahbPrescalers) {
        if (prescaler.bits == prescalerBits) {
            return getSYSCLKFreq() / prescaler.prescaler;
        }
    }

    return 0;
}


uint32_t RCC::getPCLK1Freq()
{
    auto registers = RCC_Registers::get();

    auto prescalerBits = bitsValue(registers->CFGR, 3, 8);

    for (auto& prescaler : apbPrescalers) {
        if (prescaler.bits == prescalerBits) {
            return getSYSCLKFreq() / prescaler.prescaler;
        }
    }

    return 0;
}


uint32_t RCC::getPCLK2Freq()
{
    auto registers = RCC_Registers::get();

    auto prescalerBits = bitsValue(registers->CFGR, 3, 11);

    for (auto& prescaler : apbPrescalers) {
        if (prescaler.bits == prescalerBits) {
            return getSYSCLKFreq() / prescaler.prescaler;
        }
    }

    return 0;
}


void RCC::setMCOSource(MCO_Source value)
{
    auto registers = RCC_Registers::get();

    registers->CFGR = bitsReplace(
        registers->CFGR, (int)value, 4, RCC_Registers::CFGR::MCOSEL_0);
}


void RCC::setMCOPrescaler(MCO_Prescaler value)
{
    auto registers = RCC_Registers::get();

    registers->CFGR = bitsReplace(
        registers->CFGR, (int)value, 3, RCC_Registers::CFGR::MCOPRE_0);
}


// ============================================================================
// Protected members
// ============================================================================


void RCC::enableHSI16Clock()
{
    auto registers = RCC_Registers::get();

    registers->CR |= (1 << RCC_Registers::CR::HSION);

    while (!(registers->CR & (1 << RCC_Registers::CR::HSIRDY))) {
        // Wait until HSI ready
    }
}


void RCC::enableHSEClock(bool bypass)
{
    auto registers = RCC_Registers::get();

    if (bypass) {
        registers->CR |= (1 << RCC_Registers::CR::HSEBYP);
    }

    registers->CR |= (1 << RCC_Registers::CR::HSEON);

    while (!(registers->CR & (1 << RCC_Registers::CR::HSERDY))) {
        // Wait until HSE ready
    }
}


void RCC::disableHSEClock()
{
    auto registers = RCC_Registers::get();

    registers->CR &= ~(1 << RCC_Registers::CR::HSEON);
}


void RCC::setPLLSource(PLL_Source value)
{
    auto registers = RCC_Registers::get();

    registers->PLLCFGR = bitsReplace(
        registers->PLLCFGR, (int)value, 2, RCC_Registers::PLLCFGR::PLLSRC_0);
}


void RCC::setPLLDivider(int value)
{
    auto registers = RCC_Registers::get();

    value = std::clamp(value, 1, 8);
    registers->PLLCFGR = bitsReplace(
        registers->PLLCFGR, value - 1, 3, RCC_Registers::PLLCFGR::PLLM_0);
}


void RCC::setPLLMultiplier(int value)
{
    auto registers = RCC_Registers::get();

    value = std::clamp(value, 8, 86);
    registers->PLLCFGR = bitsReplace(
        registers->PLLCFGR, value, 7, RCC_Registers::PLLCFGR::PLLN_0);
}


void RCC::setPLLRDivider(PLLR_Divider value)
{
    auto registers = RCC_Registers::get();

    registers->PLLCFGR = bitsReplace(
        registers->PLLCFGR, (int)value, 2, RCC_Registers::PLLCFGR::PLLR_0);
}


void RCC::setPLLQDivider(PLLQ_Divider value)
{
    auto registers = RCC_Registers::get();

    registers->PLLCFGR = bitsReplace(
        registers->PLLCFGR, (int)value, 2, RCC_Registers::PLLCFGR::PLLQ_0);
}


void RCC::setPLLPDivider(PLLP_Divider value)
{
    auto registers = RCC_Registers::get();

    registers->PLLCFGR = bitsReplace(
        registers->PLLCFGR, (int)value, 1, RCC_Registers::PLLCFGR::PLLP);
}


void RCC::enablePLL()
{
    auto registers = RCC_Registers::get();

    registers->CR |= (1 << RCC_Registers::CR::PLLON);

    while (!(registers->CR & (1 << RCC_Registers::CR::PLLRDY))) {
        // Wait until PLL ready
    }

    registers->PLLCFGR |= (1 << RCC_Registers::PLLCFGR::PLLREN);
    registers->PLLCFGR |= (1 << RCC_Registers::PLLCFGR::PLLQEN);
    registers->PLLCFGR |= (1 << RCC_Registers::PLLCFGR::PLLPEN);
}


void RCC::disablePLL()
{
    auto registers = RCC_Registers::get();

    registers->PLLCFGR &= ~(1 << RCC_Registers::PLLCFGR::PLLREN);
    registers->PLLCFGR &= ~(1 << RCC_Registers::PLLCFGR::PLLQEN);
    registers->PLLCFGR &= ~(1 << RCC_Registers::PLLCFGR::PLLPEN);

    registers->CR &= ~(1 << RCC_Registers::CR::PLLON);

    while (registers->CR & (1 << RCC_Registers::CR::PLLRDY)) {
        // Wait until PLL stopped
    }
}


uint32_t RCC::getPLLFreq()
{
    auto registers = RCC_Registers::get();

    auto pllSource = (PLL_Source)bitsValue(
        registers->PLLCFGR, 2, RCC_Registers::PLLCFGR::PLLSRC_0);

    int pllInputFreq = 0;

    switch (pllSource) {
        case PLL_Source::NONE:
            pllInputFreq = 0;
            break;
        case PLL_Source::MSI:
            pllInputFreq = MSI_OSCILLATOR_FREQ;
            break;
        case PLL_Source::HSI16:
            pllInputFreq = HSI16_OSCILLATOR_FREQ;
            break;
        case PLL_Source::HSE:
            pllInputFreq = oscillatorFreq;
            break;
    }

    auto pllDivider
        = bitsValue(registers->PLLCFGR, 3, RCC_Registers::PLLCFGR::PLLM_0) + 1;
    auto pllMultiplier
        = bitsValue(registers->PLLCFGR, 7, RCC_Registers::PLLCFGR::PLLN_0);
    auto pllrDivider
        = bitsValue(registers->PLLCFGR, 2, RCC_Registers::PLLCFGR::PLLR_0) * 2
          + 2;

    return pllInputFreq / pllDivider * pllMultiplier / pllrDivider;
}


void RCC::setSYSCLKSource(SYSCLK_Source value)
{
    auto registers = RCC_Registers::get();

    registers->CFGR = bitsReplace(
        registers->CFGR, (int)value, 2, RCC_Registers::CFGR::SW_0);

    while (bitsValue(registers->CFGR, 2, RCC_Registers::CFGR::SWS_0)
           != (uint32_t)value) {
        // Wait until SYSCLK source is active
    }
}


void RCC::setAHBPrescaler(AHB_Prescaler value)
{
    auto registers = RCC_Registers::get();

    int bits = ahbPrescalers[(int)value].bits;
    registers->CFGR
        = bitsReplace(registers->CFGR, bits, 4, RCC_Registers::CFGR::HPRE_0);
}


void RCC::setAPB1Prescaler(APB1_Prescaler value)
{
    auto registers = RCC_Registers::get();

    int bits = apbPrescalers[(int)value].bits;
    registers->CFGR
        = bitsReplace(registers->CFGR, bits, 3, RCC_Registers::CFGR::PPRE1_0);
}


void RCC::setAPB2Prescaler(APB2_Prescaler value)
{
    auto registers = RCC_Registers::get();

    int bits = apbPrescalers[(int)value].bits;
    registers->CFGR
        = bitsReplace(registers->CFGR, bits, 3, RCC_Registers::CFGR::PPRE2_0);
}


RCC RCC::instance;


} // namespace mcu
