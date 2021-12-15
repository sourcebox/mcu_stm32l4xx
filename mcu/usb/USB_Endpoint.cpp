/**
 * @file        USB_Endpoint.cpp
 *
 * Driver for USB endpoints on STM32L4xx
 *
 * @author:     Oliver Rockstedt <info@sourcebox.de>
 * @license     MIT
 */


// Corresponding header
#include "USB_Endpoint.h"

// This component
#include "../utility/bit_manipulation.h"

// System libraries
#include <algorithm>


namespace mcu {


// ============================================================================
// Public members
// ============================================================================


void USB_Endpoint::transmit(uint8_t data[], int size)
{
    auto writeSize = std::min(size, (int)txBufferSize);

    USB_SRAM::write(txBufferAddress, data, writeSize);
    USB_SRAM::writeHalfword(bufferDescriptorAddress + 2, writeSize);

    setTransmissionStatus(Status::VALID);
}


int USB_Endpoint::receive(uint8_t data[], int size)
{
    auto readLength = std::min(size, getReceivedLength());

    USB_SRAM::read(rxBufferAddress, data, readLength);

    setReceptionStatus(Status::VALID);

    return readLength;
}


int USB_Endpoint::getReceivedLength()
{
    return USB_SRAM::readHalfword(bufferDescriptorAddress + 6) & 0x3FF;
}


void USB_Endpoint::setAddress(int address)
{
    volatile uint32_t value = *EPnR;

    value = bitsReplace(value, address, 4, USB_Registers::EPnR::EA_0);
    value &= ~USB_Registers::EPnR::TOGGLE_MASK;
    value |= USB_Registers::EPnR::RC_W0_MASK;

    *EPnR = value;
}


void USB_Endpoint::setType(Type type)
{
    volatile uint32_t value = *EPnR;

    value = bitsReplace(value, (int)type, 2, USB_Registers::EPnR::EP_TYPE_0);
    value &= ~USB_Registers::EPnR::TOGGLE_MASK;
    value |= USB_Registers::EPnR::RC_W0_MASK;

    *EPnR = value;
}


void USB_Endpoint::setTransmissionStatus(Status status)
{
    volatile uint32_t value = *EPnR;

    auto statTx = bitsValue(value, 2, USB_Registers::EPnR::STAT_TX_0);
    statTx ^= (int)status;

    value &= ~USB_Registers::EPnR::TOGGLE_MASK;
    value |= USB_Registers::EPnR::RC_W0_MASK;
    value = bitsReplace(value, statTx, 2, USB_Registers::EPnR::STAT_TX_0);

    *EPnR = value;
}


void USB_Endpoint::setReceptionStatus(Status status)
{
    volatile uint32_t value = *EPnR;

    auto statRx = bitsValue(value, 2, USB_Registers::EPnR::STAT_RX_0);
    statRx ^= (int)status;

    value &= ~USB_Registers::EPnR::TOGGLE_MASK;
    value |= USB_Registers::EPnR::RC_W0_MASK;
    value = bitsReplace(value, statRx, 2, USB_Registers::EPnR::STAT_RX_0);

    *EPnR = value;
}


void USB_Endpoint::setBufferDescriptor(int txAddress, int txSize, int rxAddress, int rxSize)
{
    txBufferAddress = txAddress;
    txBufferSize = txSize;
    rxBufferAddress = rxAddress;
    rxBufferSize = rxSize;
}


void USB_Endpoint::initBufferDescriptor()
{
    USB_SRAM::Registers::Block bufferDescriptor;

    bufferDescriptor.ADDRn_TX = txBufferAddress;
    bufferDescriptor.COUNTn_TX = 0;
    bufferDescriptor.ADDRn_RX = rxBufferAddress;

    if (rxBufferSize >= 2 && rxBufferSize <= 62) {
        bufferDescriptor.COUNTn_RX = bitsReplace(0, rxBufferSize / 2, 5,
                USB_SRAM::Registers::COUNTn_RX::NUM_BLOCK_0);
    } else if (rxBufferSize >= 64) {
        bufferDescriptor.COUNTn_RX = bitsReplace(0, rxBufferSize / 32 - 1, 5,
                USB_SRAM::Registers::COUNTn_RX::NUM_BLOCK_0)
                | (1 << USB_SRAM::Registers::COUNTn_RX::BL_SIZE);
    }

    USB_SRAM::write(bufferDescriptorAddress, (uint8_t*)&bufferDescriptor,
                    sizeof(bufferDescriptor));
}


// ============================================================================
// Protected members
// ============================================================================


void USB_Endpoint::init()
{
    onInit();
    initBufferDescriptor();
}


void USB_Endpoint::reset()
{
    setAddress(number);
    onReset();
}


bool USB_Endpoint::getTxFlag()
{
    return bitValue(*EPnR, USB_Registers::EPnR::CTR_TX);
}


bool USB_Endpoint::getRxFlag()
{
    return bitValue(*EPnR, USB_Registers::EPnR::CTR_RX);
}


void USB_Endpoint::clearTxFlag()
{
    volatile uint32_t value = *EPnR;

    value &= ~USB_Registers::EPnR::TOGGLE_MASK;
    value |= USB_Registers::EPnR::RC_W0_MASK;
    value &= ~(1 << USB_Registers::EPnR::CTR_TX);

    *EPnR = value;
}


void USB_Endpoint::clearRxFlag()
{
    volatile uint32_t value = *EPnR;

    value &= ~USB_Registers::EPnR::TOGGLE_MASK;
    value |= USB_Registers::EPnR::RC_W0_MASK;
    value &= ~(1 << USB_Registers::EPnR::CTR_RX);

    *EPnR = value;
}


void USB_Endpoint::clearTxRxFlags()
{
    volatile uint32_t value = *EPnR;

    value &= ~USB_Registers::EPnR::TOGGLE_MASK;
    value |= USB_Registers::EPnR::RC_W0_MASK;
    value &= ~((1 << USB_Registers::EPnR::CTR_TX)
            | (1 << USB_Registers::EPnR::CTR_RX));

    *EPnR = value;
}


}   // namespace mcu
