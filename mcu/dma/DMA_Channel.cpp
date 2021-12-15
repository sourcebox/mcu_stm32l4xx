/**
 * @file        DMA_Channel.cpp
 *
 * DMA channel on STM32L4xx
 *
 * @author:     Oliver Rockstedt <info@sourcebox.de>
 * @license     MIT
 */


// Corresponding header
#include "DMA_Channel.h"

// Local includes
#include "DMA.h"

// This component
#include "../core/NVIC.h"
#include "../utility/bit_manipulation.h"


namespace mcu {


// ============================================================================
// Public members
// ============================================================================


DMA_Channel::DMA_Channel(Id dmaId, ChannelId channelId)
    : dmaId(dmaId), channelId(channelId)
{
    channelRegisters = (DMA_ChannelRegisters::Block*)
            ((uint32_t)registers + 0x08 + 0x14 * (int)channelId);
}


void DMA_Channel::init()
{
    DMA::get(dmaId).init();
}


void DMA_Channel::init(Config& config)
{
    init();

    disable();

    setDirection(config.direction);
    setPeripheralAddress(config.peripheralAddress);
    setMemoryAddress(config.memoryAddress);
    setTransferLength(config.transferLength);
    setPeripheralIncrement(config.peripheralIncrement);
    setMemoryIncrement(config.memoryIncrement);
    setPeripheralSize(config.peripheralSize);
    setMemorySize(config.memorySize);
    setPriorityLevel(config.priorityLevel);
    setCircularMode(config.circularMode);
    setMemoryToMemory(config.memoryToMemory);
    setRequestPeripheral(config.requestPeripheral);
}


void DMA_Channel::enable()
{
    channelRegisters->CCRx |= (1 << DMA_ChannelRegisters::CCRx::EN);
}


void DMA_Channel::disable()
{
    channelRegisters->CCRx &= ~(1 << DMA_ChannelRegisters::CCRx::EN);
}


void DMA_Channel::setDirection(Direction dir)
{
    switch (dir) {
        case Direction::PERIPHERAL_TO_MEMORY:
            channelRegisters->CCRx &= ~(1 << DMA_ChannelRegisters::CCRx::DIR);
            break;
        case Direction::MEMORY_TO_PERIPHERAL:
            channelRegisters->CCRx |= (1 << DMA_ChannelRegisters::CCRx::DIR);
            break;
    }
}


void DMA_Channel::setPeripheralAddress(uint32_t address)
{
    channelRegisters->CPARx = address;
}


void DMA_Channel::setMemoryAddress(uint32_t address)
{
    channelRegisters->CMARx = address;
}


void DMA_Channel::setTransferLength(volatile uint16_t length)
{
    channelRegisters->CNDTRx = length;
}


void DMA_Channel::setPeripheralIncrement(bool state)
{
    if (state) {
        channelRegisters->CCRx |= (1 << DMA_ChannelRegisters::CCRx::PINC);
    } else {
        channelRegisters->CCRx &= ~(1 << DMA_ChannelRegisters::CCRx::PINC);
    }
}


void DMA_Channel::setMemoryIncrement(bool state)
{
    if (state) {
        channelRegisters->CCRx |= (1 << DMA_ChannelRegisters::CCRx::MINC);
    } else {
        channelRegisters->CCRx &= ~(1 << DMA_ChannelRegisters::CCRx::MINC);
    }
}


void DMA_Channel::setPeripheralSize(TransferSize size)
{
    channelRegisters->CCRx = bitsReplace(channelRegisters->CCRx, (int)size, 2,
            DMA_ChannelRegisters::CCRx::PSIZE_0);
}


void DMA_Channel::setMemorySize(TransferSize size)
{
    channelRegisters->CCRx = bitsReplace(channelRegisters->CCRx, (int)size, 2,
            DMA_ChannelRegisters::CCRx::MSIZE_0);
}


void DMA_Channel::setPriorityLevel(PriorityLevel level)
{
    channelRegisters->CCRx = bitsReplace(channelRegisters->CCRx, (int)level, 2,
            DMA_ChannelRegisters::CCRx::PL_0);
}


void DMA_Channel::setCircularMode(bool state)
{
    if (state) {
        channelRegisters->CCRx |= (1 << DMA_ChannelRegisters::CCRx::CIRC);
    } else {
        channelRegisters->CCRx &= ~(1 << DMA_ChannelRegisters::CCRx::CIRC);
    }
}


void DMA_Channel::setMemoryToMemory(bool state)
{
    if (state) {
        channelRegisters->CCRx |= (1 << DMA_ChannelRegisters::CCRx::MEM2MEM);
    } else {
        channelRegisters->CCRx &= ~(1 << DMA_ChannelRegisters::CCRx::MEM2MEM);
    }
}


void DMA_Channel::setRequestPeripheral(RequestPeripheral request)
{
    auto bitOffset = (int)channelId * 4;

    registers->CSELR = bitsReplace(registers->CSELR, (int)request, 4, bitOffset);
}


void DMA_Channel::setCompleteCallback(CallbackFunc func)
{
    completeCallbacks[dmaId][channelId] = func;

    auto& nvic = NVIC::get();
    auto irqNum = getIRQNumber(dmaId, channelId);

    if (func != nullptr) {
        channelRegisters->CCRx |= (1 << DMA_ChannelRegisters::CCRx::TCIE);
        nvic.enableIrq(irqNum);
    } else {
        channelRegisters->CCRx &= ~(1 << DMA_ChannelRegisters::CCRx::TCIE);
    }
}


void DMA_Channel::setHalfCompleteCallback(CallbackFunc func)
{
    halfCompleteCallbacks[dmaId][channelId] = func;

    auto& nvic = NVIC::get();
    auto irqNum = getIRQNumber(dmaId, channelId);

    if (func != nullptr) {
        channelRegisters->CCRx |= (1 << DMA_ChannelRegisters::CCRx::HTIE);
        nvic.enableIrq(irqNum);
    } else {
        channelRegisters->CCRx &= ~(1 << DMA_ChannelRegisters::CCRx::HTIE);
    }
}


void DMA_Channel::setErrorCallback(CallbackFunc func)
{
    errorCallbacks[dmaId][channelId] = func;

    auto& nvic = NVIC::get();
    auto irqNum = getIRQNumber(dmaId, channelId);

    if (func != nullptr) {
        channelRegisters->CCRx |= (1 << DMA_ChannelRegisters::CCRx::TEIE);
        nvic.enableIrq(irqNum);
    } else {
        channelRegisters->CCRx &= ~(1 << DMA_ChannelRegisters::CCRx::TEIE);
    }
}


bool DMA_Channel::isComplete()
{
    auto bitOffset = (int)channelId * 4 + 1;

    return registers->ISR & (1 << bitOffset);
}


void DMA_Channel::clearComplete()
{
    auto bitOffset = (int)channelId * 4 + 1;

    registers->IFCR |= (1 << bitOffset);
}


bool DMA_Channel::isHalfComplete()
{
    auto bitOffset = (int)channelId * 4 + 2;

    return registers->ISR & (1 << bitOffset);
}


void DMA_Channel::clearHalfComplete()
{
    auto bitOffset = (int)channelId * 4 + 2;

    registers->IFCR |= (1 << bitOffset);
}


bool DMA_Channel::hasError()
{
    auto bitOffset = (int)channelId * 4 + 3;

    return registers->ISR & (1 << bitOffset);
}


void DMA_Channel::clearError()
{
    auto bitOffset = (int)channelId * 4 + 3;

    registers->IFCR |= (1 << bitOffset);
}


void DMA_Channel::irq()
{
    if (isComplete()) {
        clearComplete();

        auto callback = completeCallbacks[dmaId][channelId];

        if (callback != nullptr) {
            callback();
        }
    }

    if (isHalfComplete()) {
        clearHalfComplete();

        auto callback = halfCompleteCallbacks[dmaId][channelId];

        if (callback != nullptr) {
            callback();
        }
    }

    if (hasError()) {
        clearError();

        auto callback = errorCallbacks[dmaId][channelId];

        if (callback != nullptr) {
            callback();
        }
    }
}


// ============================================================================
// Protected members
// ============================================================================


DMA_Channel::CallbackFunc DMA_Channel::completeCallbacks[2][7];
DMA_Channel::CallbackFunc DMA_Channel::halfCompleteCallbacks[2][7];
DMA_Channel::CallbackFunc DMA_Channel::errorCallbacks[2][7];


}   // namespace mcu
