/**
 * @file        Flash.cpp
 *
 * Driver for embedded flash on STM32L4xx
 *
 * @author:     Oliver Rockstedt <info@sourcebox.de>
 * @license     MIT
 */


// Corresponding header
#include "Flash.h"


namespace mcu {


// ============================================================================
// Public members
// ============================================================================


void Flash::setLatency(int value)
{
    auto registers = Flash_Registers::get();
    value = std::clamp(value, 0, 4);
    registers->ACR = bitsReplace(
        registers->ACR, value, 3, Flash_Registers::ACR::LATENCY_0);
}


void Flash::enablePrefetchBuffer()
{
    auto registers = Flash_Registers::get();
    registers->ACR = bitSet(registers->ACR, Flash_Registers::ACR::PRFTEN);
}


void Flash::disablePrefetchBuffer()
{
    auto registers = Flash_Registers::get();
    registers->ACR = bitReset(registers->ACR, Flash_Registers::ACR::PRFTEN);
}


void Flash::unlock()
{
    auto registers = Flash_Registers::get();
    registers->KEYR = 0x45670123;
    registers->KEYR = 0xCDEF89AB;
}


void Flash::lock()
{
    auto registers = Flash_Registers::get();
    registers->CR = bitSet(registers->CR, Flash_Registers::CR::LOCK);
}


bool Flash::isBusy()
{
    auto registers = Flash_Registers::get();

    return bitValue(registers->SR, Flash_Registers::SR::BSY);
}


void Flash::clearErrors()
{
    auto registers = Flash_Registers::get();

    auto value = registers->SR;

    value = bitSet(value, Flash_Registers::SR::OPTVERR);
    value = bitSet(value, Flash_Registers::SR::RDERR);
    value = bitSet(value, Flash_Registers::SR::FASTERR);
    value = bitSet(value, Flash_Registers::SR::MISSERR);
    value = bitSet(value, Flash_Registers::SR::PGSERR);
    value = bitSet(value, Flash_Registers::SR::SIZERR);
    value = bitSet(value, Flash_Registers::SR::PGAERR);
    value = bitSet(value, Flash_Registers::SR::WRPERR);
    value = bitSet(value, Flash_Registers::SR::PROGERR);
    value = bitSet(value, Flash_Registers::SR::OPERR);

    registers->SR = value;
}


void Flash::erasePage(uint32_t address)
{
    while (isBusy()) {
        // Wait while busy from previous operation
    }

    clearErrors();

    unlock();

    auto registers = Flash_Registers::get();

    // Enable EOP interrupt
    registers->CR = bitSet(registers->CR, Flash_Registers::CR::EOPIE);

    // Set page erase flag and page number
    auto value = registers->CR;
    value = bitSet(value, Flash_Registers::CR::PER);
    auto pageNo = (address - BASE_ADDRESS) / PAGE_SIZE;
    value = bitsReplace(value, pageNo, 8, Flash_Registers::CR::PNB_0);
    registers->CR = value;

    // Start operation
    registers->CR = bitSet(registers->CR, Flash_Registers::CR::STRT);

    while (isBusy()) {
        // Wait until ready
    }

    while (!bitValue(registers->SR, Flash_Registers::SR::EOP)) {
        // Wait until end of programming flag
    }

    // Reset page erase flag
    registers->CR = bitReset(registers->CR, Flash_Registers::CR::PER);

    // Disable EOP interrupt
    registers->CR = bitSet(registers->CR, Flash_Registers::CR::EOPIE);

    lock();
}


void Flash::program(uint32_t address, uint8_t data[], int length)
{
    while (isBusy()) {
        // Wait while busy from previous operation
    }

    auto registers = Flash_Registers::get();

    // Save state of data cache, disable and reset it
    auto dataCacheEnabled
        = bitValue(registers->ACR, Flash_Registers::ACR::DCEN);
    registers->ACR = bitReset(registers->ACR, Flash_Registers::ACR::DCEN);
    registers->ACR = bitSet(registers->ACR, Flash_Registers::ACR::DCRST);

    clearErrors();

    unlock();

    // Enable EOP interrupt
    registers->CR = bitSet(registers->CR, Flash_Registers::CR::EOPIE);

    // Enable programming
    registers->CR = bitSet(registers->CR, Flash_Registers::CR::PG);

    for (auto n = 0; n < length; n += 8) {
        uint64_t value = 0;

        auto remaining = std::min(length - n, 8);

        for (auto i = 0; i < 8; i++) {
            if (i < remaining) {
                // Fill used bytes with data
                value |= (uint64_t)data[n + i] << (i * 8);
            } else {
                // Fill padding bytes with 0xFF (flash erase value)
                value |= (uint64_t)0xFF << (i * 8);
            }
        }

        *(volatile uint32_t*)(address + n) = (uint32_t)value;
        asm volatile("isb");
        *(volatile uint32_t*)(address + n + 4) = (uint32_t)(value >> 32);

        while (isBusy()) {
            // Wait until ready
        }

        while (!bitValue(registers->SR, Flash_Registers::SR::EOP)) {
            // Wait until end of programming flag
        }

        // Clear end of programming flag
        registers->SR = bitSet(registers->SR, Flash_Registers::SR::EOP);
    }

    // Disable programming
    registers->CR = bitReset(registers->CR, Flash_Registers::CR::PG);

    // Disable EOP interrupt
    registers->CR = bitSet(registers->CR, Flash_Registers::CR::EOPIE);

    if (dataCacheEnabled) {
        // Enable data cache again when it was enabled before programming
        registers->ACR = bitReset(registers->ACR, Flash_Registers::ACR::DCRST);
        registers->ACR = bitSet(registers->ACR, Flash_Registers::ACR::DCEN);
    }

    lock();
}


} // namespace mcu
