/**
 * @file        Flash.h
 *
 * Driver for embedded flash on STM32L4xx
 *
 * @author:     Oliver Rockstedt <info@sourcebox.de>
 * @license     MIT
 */


#pragma once


// Local includes
#include "Flash_Registers.h"

// This component
#include "../utility/bit_manipulation.h"

// System libraries
#include <algorithm>


namespace mcu {


class Flash
{
  public:
    /**
     * Base address
     */
    static constexpr uint32_t BASE_ADDRESS = 0x08000000;

    /**
     * Page size in bytes
     */
    static constexpr int PAGE_SIZE = 2048;

    /**
     * Set latency
     *
     * @param value         Latency in wait states 0..4
     */
    void setLatency(int value);

    /**
     * Enable prefetch buffer
     */
    void enablePrefetchBuffer();

    /**
     * Disable prefetch buffer
     */
    void disablePrefetchBuffer();

    /**
     * Unlock programming
     */
    void unlock();

    /**
     * Lock programming
     */
    void lock();

    /**
     * Return busy state
     */
    bool isBusy();

    /**
     * Clear error flags
     */
    void clearErrors();

    /**
     * Erase a page
     *
     * @param address   Page base address
     */
    void erasePage(uint32_t address);

    /**
     * Program data
     *
     * @param address   Start address, must be 8-bytes aligned
     * @param data      Buffer containing data
     * @param length    Data length in bytes
     */
    void program(uint32_t address, uint8_t data[], int length);
};


} // namespace mcu
