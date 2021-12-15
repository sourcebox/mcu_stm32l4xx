/**
 * @file        mcu_base.h
 *
 * Common address and type definitions for STM32L4xx MCUs
 *
 * @author      Oliver Rockstedt <info@sourcebox.de>
 * @license     MIT
 */


#pragma once


// Local includes
#include "cortex_m4.h"

// System libraries
#include <cstdint>


namespace mcu {


static const uint32_t PERIPHERAL_BASE_ADDRESS = 0x40000000;

static const uint32_t APB1_BASE_ADDRESS = PERIPHERAL_BASE_ADDRESS;
static const uint32_t APB2_BASE_ADDRESS = PERIPHERAL_BASE_ADDRESS + 0x00010000;
static const uint32_t AHB1_BASE_ADDRESS = PERIPHERAL_BASE_ADDRESS + 0x00020000;
static const uint32_t AHB2_BASE_ADDRESS = PERIPHERAL_BASE_ADDRESS + 0x08000000;


struct IrqId
{
    enum
    {
        // Cortex-M4 processor exceptions numbers
        NMI                 = -14,  // Non maskable interrupt
        HardFault           = -13,  // Hard fault interrupt
        MemManage           = -12,  // Memory management interrupt
        BusFault            = -11,  // Bus fault interrupt
        UsageFault          = -10,  // Usage fault interrupt
        SVCall              = -5,   // SV call interrupt
        DebugMonitor        = -4,   // Debug monitor interrupt
        PendSV              = -2,   // Pend SV interrupt
        SysTick             = -1,   // System tick interrupt

        // Device specific interrupt numbers
        WWDG                = 0,    // Window WatchDog interrupt
        PVD_PVM             = 1,    // PVD/PVM through EXTI line detection interrupt
        TAMP_STAMP          = 2,    // Tamper and TimeStamp interrupts through the EXTI Line 19
        RTC_WKUP            = 3,    // RTC Wakeup interrupt through the EXTI Line 20
        FLASH               = 4,    // FLASH global interrupt
        RCC                 = 5,    // RCC global interrupt
        EXTI0               = 6,    // EXTI Line0 interrupt
        EXTI1               = 7,    // EXTI Line1 interrupt
        EXTI2               = 8,    // EXTI Line2 interrupt
        EXTI3               = 9,    // EXTI Line3 interrupt
        EXTI4               = 10,   // EXTI Line4 interrupt
        DMA1_Channel1       = 11,   // DMA1 Channel 1 interrupt
        DMA1_Channel2       = 12,   // DMA1 Channel 2 interrupt
        DMA1_Channel3       = 13,   // DMA1 Channel 3 interrupt
        DMA1_Channel4       = 14,   // DMA1 Channel 4 interrupt
        DMA1_Channel5       = 15,   // DMA1 Channel 5 interrupt
        DMA1_Channel6       = 16,   // DMA1 Channel 6 interrupt
        DMA1_Channel7       = 17,   // DMA1 Channel 7 interrupt
        ADC1_2              = 18,   // ADC1 & ADC2 global interrupts
        CAN1_TX             = 19,   // CAN1 TX interrupt
        CAN1_RX0            = 20,   // CAN1 RX0 interrupt
        CAN1_RX1            = 21,   // CAN1 RX1 interrupt
        CAN1_SCE            = 22,   // CAN1 SCE interrupt
        EXTI9_5             = 23,   // External Line[9:5] interrupts
        TIM1_BRK_TIM15      = 24,   // TIM1 Break and TIM15 interrupts
        TIM1_UP_TIM16       = 25,   // TIM1 Update and TIM16 interrupts
        TIM1_TRG_COM        = 26,   // TIM1 Trigger and Commutation interrupt
        TIM1_CC             = 27,   // TIM1 Capture Compare interrupt
        TIM2                = 28,   // TIM2 global interrupt
        TIM3                = 29,   // TIM3 global interrupt
        I2C1_EV             = 31,   // I2C1 event interrupt
        I2C1_ER             = 32,   // I2C1 error interrupt
        I2C2_EV             = 33,   // I2C2 event interrupt
        I2C2_ER             = 34,   // I2C2 error interrupt
        SPI1                = 35,   // SPI1 global interrupt
        SPI2                = 36,   // SPI2 global interrupt
        USART1              = 37,   // USART1 global interrupt
        USART2              = 38,   // USART2 global interrupt
        USART3              = 39,   // USART3 global interrupt
        EXTI15_10           = 40,   // External Line[15:10] interrupts
        RTC_Alarm           = 41,   // RTC Alarm (A and B) through EXTI Line 18 interrupt
        SDMMC1              = 49,   // SDMMC1 global interrupt
        SPI3                = 51,   // SPI3 global interrupt
        UART4               = 52,   // UART4 global interrupt
        TIM6_DACUNDER       = 54,   // TIM6 global and DAC1 underrun error interrupts
        TIM7                = 55,   // TIM7 global interrupt
        DMA2_Channel1       = 56,   // DMA2 Channel 1 interrupt
        DMA2_Channel2       = 57,   // DMA2 Channel 2 interrupt
        DMA2_Channel3       = 58,   // DMA2 Channel 3 interrupt
        DMA2_Channel4       = 59,   // DMA2 Channel 4 interrupt
        DMA2_Channel5       = 60,   // DMA2 Channel 5 interrupt
        DFSDM1_FLT0         = 61,   // DFSDM1_FLT0 global Interrupt
        DFSDM1_FLT1         = 62,   // DFSDM1_FLT1 global Interrupt
        COMP                = 64,   // COMP1/COMP2 through EXTI Line21/22 interrupts
        LPTIM1              = 65,   // LPTIM1 global interrupt
        LPTIM2              = 66,   // LPTIM2 global interrupt
        USBFS               = 67,   // USB event interrupt through EXTI line 17
        DMA2_Channel6       = 68,   // DMA2 channel 6 interrupt
        DMA2_Channel7       = 69,   // DMA2 channel 7 interrupt
        LPUART1             = 70,   // LPUART1 global interrupt
        QUADSPI             = 71,   // QUADSPI global interrupt
        I2C3_EV             = 72,   // I2C3 event interrupt
        I2C3_ER             = 73,   // I2C3 error interrupt
        SAI1                = 74,   // SAI1 global interrupt
        SWPMI1              = 76,   // SWPMI1 global interrupt
        TSC                 = 77,   // TSC global interrupt
        LCD                 = 78,   // LCD global interrupt
        AES                 = 79,   // AES global interrupt
        RNG                 = 80,   // RNG global interrupt
        FPU                 = 81,   // Floating point interrupt
        CRS                 = 82,   // CRS interrupt
        I2C4_EV             = 83,   // I2C4 event interrupt, wakeup through EXTI line 40
        I2C4_ER             = 84    // I2C4 error interrupt
    };
};


/**
 * Return unique device id
 *
 * @param value         Array to be filled with data
 */
__attribute__((always_inline))
static inline void readUniqueId(uint32_t value[3])
{
    value[0] = *(uint32_t*)(0x1FFF7590);
    value[1] = *(uint32_t*)(0x1FFF7594);
    value[2] = *(uint32_t*)(0x1FFF7598);
}


/**
 * Read unique device id as string
 *
 * @param buffer        Array to be filled with data, size must be 25 bytes
 */
__attribute__((always_inline))
static inline void readUniqueIdString(char buffer[25])
{
    uint32_t uniqueId[3];
    readUniqueId(uniqueId);

    for (uint32_t i = 0; i < 3; i++) {
        uint32_t ds = uniqueId[i];

        for (uint32_t n = 0; n < 8; n++) {
            uint32_t value = ds & 0x0F;
            char letter = value < 10 ? '0' + value : 'A' + value - 10;
            buffer[i * 8 + n] = letter;
            ds >>= 4;
        }
    }

    buffer[25] = 0;
}


}   // namespace mcu
