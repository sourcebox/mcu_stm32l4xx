/**
 * @file        mcu.h
 *
 * Single include entry point for all headers
 *
 * @author      Oliver Rockstedt <info@sourcebox.de>
 * @license     MIT
 */


#pragma once


#include "mcu/adc/ADC.h"
#include "mcu/core/CoreDebug.h"
#include "mcu/core/DWT.h"
#include "mcu/core/NVIC.h"
#include "mcu/core/SCB.h"
#include "mcu/core/SysTick.h"
#include "mcu/core/mcu_base.h"
#include "mcu/dma/DMA.h"
#include "mcu/dma/DMA_Channel.h"
#include "mcu/flash/Flash.h"
#include "mcu/gpio/Pin.h"
#include "mcu/quadspi/QUADSPI.h"
#include "mcu/rcc/RCC.h"
#include "mcu/sdmmc/SDMMC.h"
#include "mcu/spi/SPI.h"
#include "mcu/timer/LPTimer.h"
#include "mcu/timer/Timer.h"
#include "mcu/uart/UART.h"
#include "mcu/usb/USB.h"
#include "mcu/utility/bit_manipulation.h"
#include "mcu/utility/time.h"


namespace mcu {


/**
 * System reset
 */
__attribute__((always_inline)) static inline void systemReset()
{
    __asm volatile("dsb");

    auto scbRegisters = SCB_Registers::get();

    uint32_t value = scbRegisters->AIRCR;
    value = bitsReplace(value, 0x5FA, 16, SCB_Registers::AIRCR::VECTKEY);
    value = bitSet(value, 2);
    scbRegisters->AIRCR = value;

    __asm volatile("dsb");

    while (true) {
        // Wait for reset
    }
}


} // namespace mcu
