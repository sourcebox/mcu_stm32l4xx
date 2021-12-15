/**
 * @file        SysTick.h
 *
 * Driver for SysTick on Cortex-M4
 *
 * @author:     Oliver Rockstedt <info@sourcebox.de>
 * @license     MIT
 */


#pragma once


// Local includes
#include "SysTick_Registers.h"


namespace mcu {


class SysTick
{
  public:
    enum ClockSource
    {
        CLKSOURCE_HCLK_DIV_8,
        CLKSOURCE_HCLK
    };

    /**
     * Return reference to peripheral
     *
     * @return              Reference to peripheral
     */
    static SysTick& get()
    {
        return instance;
    }

    /**
     * Configure
     *
     * @param cycles        Number of clock cycles per tick
     * @param clockSource   Clock source according to enum
     */
    void configure(int cycles, ClockSource clockSource = CLKSOURCE_HCLK);

    /**
     * Deinit
     */
    void deinit();

    /**
     * Return number of elapsed ticks
     *
     * @return                  No of ticks
     */
    uint32_t getTicks();

    /**
     * Return number of elapsed clock cycles
     *
     * @return                  No of clock cycles
     */
    uint64_t getClockCycles();

    /**
     * Process interrupt, called from IRQ handler
     */
    void irq();

    /**
     * Callback function type
     */
    typedef void (*CallbackFunc)(void);

    /**
     * Set callback function
     *
     * @param func          Callback function or nullptr
     */
    void setCallback(CallbackFunc func);

  protected:
    /**
     * Private constructors because of singleton pattern, no copy allowed
     */
    SysTick()
    {
    }
    SysTick(const SysTick&) = delete;
    SysTick& operator=(const SysTick&) = delete;
    SysTick& operator=(SysTick&&) = delete;

    volatile uint32_t ticks = 0;
    CallbackFunc callback = nullptr;

    /**
     * Singleton instance
     */
    static SysTick instance;
};


} // namespace mcu
