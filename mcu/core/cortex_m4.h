/**
 * @file        cortex_m4.h
 *
 * Definitions for Cortex-M4
 *
 * @author      Oliver Rockstedt <info@sourcebox.de>
 * @license     MIT
 */


#pragma once


// System libraries
#include <cstdint>


namespace mcu {


static const uint32_t NVIC_PRIO_BITS = 4;


// Hardware addresses
static const uint32_t SCS_BASE_ADDRESS = 0xE000E000;
static const uint32_t ITM_BASE_ADDRESS = 0xE0000000;
static const uint32_t TPI_BASE_ADDRESS = 0xE0040000;


/**
 * Enable interrupts
 */
__attribute__((always_inline))
static inline void enableInterrupts()
{
  __asm volatile ("cpsie i" : : : "memory");
}


/**
 * Disable interrupts
 */
__attribute__((always_inline))
static inline void disableInterrupts()
{
  __asm volatile ("cpsid i" : : : "memory");
}


/**
 * Breakpoint
 */
__attribute__((always_inline))
static inline void breakpoint()
{
  __asm volatile ("bkpt");
}


}   // namespace mcu
