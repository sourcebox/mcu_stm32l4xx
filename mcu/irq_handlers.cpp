/**
 * @file        irq_handlers.cpp
 *
 * IRQ handlers for STM32L4xx
 *
 * @author:     Oliver Rockstedt <info@sourcebox.de>
 * @license     MIT
 */


// This component
#include "../mcu.h"


using namespace mcu;


// ============================================================================
// SysTick
// ============================================================================


extern "C" __attribute__((interrupt("IRQ"))) void SysTick_Handler()
{
    auto& sysTick = SysTick::get();
    sysTick.irq();
}


// ============================================================================
// DMA
// ============================================================================


#ifndef EXCLUDE_DMA

extern "C" __attribute__((interrupt)) void DMA1_Channel1_IRQHandler()
{
    auto dmaChannel = DMA_Channel::get(DMA::DMA1, DMA_Channel::CH1);
    dmaChannel.irq();
}


extern "C" __attribute__((interrupt)) void DMA1_Channel2_IRQHandler()
{
    auto dmaChannel = DMA_Channel::get(DMA::DMA1, DMA_Channel::CH2);
    dmaChannel.irq();
}


extern "C" __attribute__((interrupt)) void DMA1_Channel3_IRQHandler()
{
    auto dmaChannel = DMA_Channel::get(DMA::DMA1, DMA_Channel::CH3);
    dmaChannel.irq();
}


extern "C" __attribute__((interrupt)) void DMA1_Channel4_IRQHandler()
{
    auto dmaChannel = DMA_Channel::get(DMA::DMA1, DMA_Channel::CH4);
    dmaChannel.irq();
}


extern "C" __attribute__((interrupt)) void DMA1_Channel5_IRQHandler()
{
    auto dmaChannel = DMA_Channel::get(DMA::DMA1, DMA_Channel::CH5);
    dmaChannel.irq();
}


extern "C" __attribute__((interrupt)) void DMA1_Channel6_IRQHandler()
{
    auto dmaChannel = DMA_Channel::get(DMA::DMA1, DMA_Channel::CH6);
    dmaChannel.irq();
}


extern "C" __attribute__((interrupt)) void DMA1_Channel7_IRQHandler()
{
    auto dmaChannel = DMA_Channel::get(DMA::DMA1, DMA_Channel::CH7);
    dmaChannel.irq();
}


extern "C" __attribute__((interrupt)) void DMA2_Channel1_IRQHandler()
{
    auto dmaChannel = DMA_Channel::get(DMA::DMA2, DMA_Channel::CH1);
    dmaChannel.irq();
}


extern "C" __attribute__((interrupt)) void DMA2_Channel2_IRQHandler()
{
    auto dmaChannel = DMA_Channel::get(DMA::DMA2, DMA_Channel::CH2);
    dmaChannel.irq();
}


extern "C" __attribute__((interrupt)) void DMA2_Channel3_IRQHandler()
{
    auto dmaChannel = DMA_Channel::get(DMA::DMA2, DMA_Channel::CH3);
    dmaChannel.irq();
}


extern "C" __attribute__((interrupt)) void DMA2_Channel4_IRQHandler()
{
    auto dmaChannel = DMA_Channel::get(DMA::DMA2, DMA_Channel::CH4);
    dmaChannel.irq();
}


extern "C" __attribute__((interrupt)) void DMA2_Channel5_IRQHandler()
{
    auto dmaChannel = DMA_Channel::get(DMA::DMA2, DMA_Channel::CH5);
    dmaChannel.irq();
}


extern "C" __attribute__((interrupt)) void DMA2_Channel6_IRQHandler()
{
    auto dmaChannel = DMA_Channel::get(DMA::DMA2, DMA_Channel::CH6);
    dmaChannel.irq();
}


extern "C" __attribute__((interrupt)) void DMA2_Channel7_IRQHandler()
{
    auto dmaChannel = DMA_Channel::get(DMA::DMA2, DMA_Channel::CH7);
    dmaChannel.irq();
}

#endif


// ============================================================================
// ADC
// ============================================================================


#ifndef EXCLUDE_ADC

extern "C" __attribute__((interrupt)) void ADC1_IRQHandler()
{
    auto& adc = ADC::get(ADC::ADC1);
    adc.irq();
}

#endif


// ============================================================================
// QUADSPI
// ============================================================================


#ifndef EXCLUDE_QUADSPI

extern "C" __attribute__((interrupt)) void QUADSPI_IRQHandler()
{
    auto& quadspi = QUADSPI::get();
    quadspi.irq();
}

#endif


// ============================================================================
// SDMMC
// ============================================================================


#ifndef EXCLUDE_SDMMC

extern "C" __attribute__((interrupt)) void SDMMC1_IRQHandler()
{
    auto& sdmmc = SDMMC::get(SDMMC::SDMMC1);
    sdmmc.irq();
}

#endif


// ============================================================================
// SPI
// ============================================================================


#ifndef EXCLUDE_SPI

extern "C" __attribute__((interrupt)) void SPI1_IRQHandler()
{
    auto& spi = SPI::get(SPI::SPI1);
    spi.irq();
}


extern "C" __attribute__((interrupt)) void SPI2_IRQHandler()
{
    auto& spi = SPI::get(SPI::SPI2);
    spi.irq();
}


extern "C" __attribute__((interrupt)) void SPI3_IRQHandler()
{
    auto& spi = SPI::get(SPI::SPI3);
    spi.irq();
}

#endif


// ============================================================================
// Timers
// ============================================================================


#ifndef EXCLUDE_TIMER

extern "C" __attribute__((interrupt)) void TIM1_UP_TIM16_IRQHandler()
{
    auto& timer1 = Timer::get(Timer::TIM1);
    timer1.irq();

    auto& timer2 = Timer::get(Timer::TIM16);
    timer2.irq();
}


extern "C" __attribute__((interrupt)) void TIM2_IRQHandler()
{
    auto& timer = Timer::get(Timer::TIM2);
    timer.irq();
}


extern "C" __attribute__((interrupt)) void TIM3_IRQHandler()
{
    auto& timer = Timer::get(Timer::TIM3);
    timer.irq();
}


extern "C" __attribute__((interrupt)) void TIM6_DAC_IRQHandler()
{
    auto& timer = Timer::get(Timer::TIM6);
    timer.irq();
}


extern "C" __attribute__((interrupt)) void TIM7_IRQHandler()
{
    auto& timer = Timer::get(Timer::TIM7);
    timer.irq();
}


extern "C" __attribute__((interrupt)) void TIM1_BRK_TIM15_IRQHandler()
{
    auto& timer = Timer::get(Timer::TIM15);
    timer.irq();
}


extern "C" __attribute__((interrupt)) void LPTIM1_IRQHandler()
{
    auto& timer = LPTimer::get(LPTimer::LPTIM1);
    timer.irq();
}


extern "C" __attribute__((interrupt)) void LPTIM2_IRQHandler()
{
    auto& timer = LPTimer::get(LPTimer::LPTIM2);
    timer.irq();
}

#endif


// ============================================================================
// USART/UART
// ============================================================================


#ifndef EXCLUDE_UART

extern "C" __attribute__((interrupt)) void USART1_IRQHandler()
{
    auto& uart = UART::get(UART::USART1);
    uart.irq();
}


extern "C" __attribute__((interrupt)) void USART2_IRQHandler()
{
    auto& uart = UART::get(UART::USART2);
    uart.irq();
}


extern "C" __attribute__((interrupt)) void USART3_IRQHandler()
{
    auto& uart = UART::get(UART::USART3);
    uart.irq();
}


extern "C" __attribute__((interrupt)) void UART4_IRQHandler()
{
    auto& uart = UART::get(UART::UART4);
    uart.irq();
}


extern "C" __attribute__((interrupt)) void LPUART1_IRQHandler()
{
    auto& uart = UART::get(UART::LPUART1);
    uart.irq();
}

#endif


// ============================================================================
// USB
// ============================================================================


#ifndef EXCLUDE_USB

extern "C" __attribute__((interrupt)) void USB_IRQHandler()
{
    auto& usb = USB::get();
    usb.irq();
}

#endif
