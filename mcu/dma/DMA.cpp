/**
 * @file        DMA.cpp
 *
 * Driver for DMA controller on STM32L4xx
 *
 * @author:     Oliver Rockstedt <info@sourcebox.de>
 * @license     MIT
 */


// Corresponding header
#include "DMA.h"

// This component
#include "../rcc/RCC_Registers.h"


namespace mcu {


// ============================================================================
// Public members
// ============================================================================


void DMA::init()
{
    enableClock();
}


void DMA::deinit()
{
    disableClock();
}


// ============================================================================
// Protected members
// ============================================================================


void DMA::enableClock()
{
    auto rccRegisters = RCC_Registers::get();

    switch (id) {
        case DMA1:
            rccRegisters->AHB1ENR |= (1 << RCC_Registers::AHB1ENR::DMA1EN);
            break;
        case DMA2:
            rccRegisters->AHB1ENR |= (1 << RCC_Registers::AHB1ENR::DMA2EN);
            break;
    }
}


void DMA::disableClock()
{
    auto rccRegisters = RCC_Registers::get();

    switch (id) {
        case DMA1:
            rccRegisters->AHB1ENR &= ~(1 << RCC_Registers::AHB1ENR::DMA1EN);
            break;
        case DMA2:
            rccRegisters->AHB1ENR &= ~(1 << RCC_Registers::AHB1ENR::DMA2EN);
            break;
    }
}


DMA DMA::dma1 = DMA(DMA::DMA1);
DMA DMA::dma2 = DMA(DMA::DMA2);


}   // namespace mcu
