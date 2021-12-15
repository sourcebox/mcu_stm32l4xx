/**
 * @file        USB_SRAM.cpp
 *
 * Driver for USB SRAM on STM32L4xx
 *
 * @author:     Oliver Rockstedt <info@sourcebox.de>
 * @license     MIT
 */


// Corresponding header
#include "USB_SRAM.h"

// System libraries
#include <cstring>


namespace mcu {


// ============================================================================
// Public members
// ============================================================================


void USB_SRAM::read(uint32_t address, uint8_t buffer[], size_t size)
{
    auto memory = (uint8_t*)BASE_ADDRESS;

    for (size_t i = 0; i < size; i++) {
        buffer[i] = memory[address + i];
    }
}


uint8_t USB_SRAM::readByte(uint32_t address)
{
    auto memory = (uint8_t*)BASE_ADDRESS;

    return memory[address];
}


uint16_t USB_SRAM::readHalfword(uint32_t address)
{
    auto memory = (uint16_t*)BASE_ADDRESS;

    address >>= 1;

    return memory[address];
}


uint32_t USB_SRAM::readWord(uint32_t address)
{
    auto memory = (uint16_t*)BASE_ADDRESS;

    address >>= 1;

    return memory[address] | (memory[address + 1] << 16);
}


void USB_SRAM::write(uint32_t address, uint8_t buffer[], size_t size)
{
    auto memory = (uint16_t*)BASE_ADDRESS;

    for (size_t i = 0; i < size; i += 2) {
        auto index = (address + i) >> 1;
        memory[index] = buffer[i] | (buffer[i + 1] << 8);
    }
}


void USB_SRAM::writeByte(uint32_t address, uint8_t value)
{
    auto memory = (uint16_t*)BASE_ADDRESS;

    memory[address >> 1] = value | (readByte(address + 1) << 8);
}


void USB_SRAM::writeHalfword(uint32_t address, uint16_t value)
{
    auto memory = (uint16_t*)BASE_ADDRESS;

    address >>= 1;

    memory[address] = value;
}


void USB_SRAM::writeWord(uint32_t address, uint32_t value)
{
    auto memory = (uint16_t*)BASE_ADDRESS;

    address >>= 1;

    memory[address] = value & 0xFFFF;
    memory[address + 1] = value >> 16;
}


void USB_SRAM::clear()
{
    memset((void*)BASE_ADDRESS, 0, SIZE);
}


}
