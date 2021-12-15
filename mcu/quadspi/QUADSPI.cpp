/**
 * @file        QUADSPI.cpp
 *
 * Driver for QUADSPI peripheral on STM32L4xx
 *
 * @author:     Oliver Rockstedt <info@sourcebox.de>
 * @license     MIT
 */


// Corresponding header
#include "QUADSPI.h"

// This component
#include "../core/NVIC.h"
#include "../rcc/RCC_Registers.h"
#include "../utility/register.h"
#include "../utility/bit_manipulation.h"

// System libraries
#include <cstdlib>
#include <cstring>


namespace mcu {


// ============================================================================
// Public members
// ============================================================================


void QUADSPI::init()
{
    enableClock();
}


void QUADSPI::init(Config& config)
{
    init();

    initClockPin(config.clkPinId);
    initBankPins(config.bk1ncsPinId, config.bk1io0PinId, config.bk1io1PinId,
                 config.bk1io2PinId, config.bk1io3PinId);
    initBankPins(config.bk2ncsPinId, config.bk2io0PinId, config.bk2io1PinId,
                 config.bk2io2PinId, config.bk2io3PinId);

    disable();

    setPrescaler(config.prescaler);
    setSampleShift(config.sampleShift);
    setFIFOThreshold(config.fifoThreshold);
    setFlashSize(config.flashSize);
    setCSHighTime(config.csHighTime);
    setClockPolarity(config.clockPolarity);
    setPollingMatchMode(config.pollingMatchMode);
    setAutomaticPollModeStop(config.automaticPollModeStop);
    setDMAEnable(config.dmaEnable);
    setTransferCompleteCallback(config.transferCompleteCallback);

    enable();
}


void QUADSPI::deinit()
{
    disableClock();
}


void QUADSPI::initClockPin(Pin::Id clkPinId)
{
    auto af = Pin::AF::AF10;
    auto speed = Pin::OutputSpeed::MEDIUM;

    if (clkPinId != Pin::NONE) {
        auto pin = Pin::get(clkPinId);
        pin.setMode(Pin::Mode::AF);
        pin.setOutputSpeed(speed);
        pin.setAlternateFunction(af);
    }
}


void QUADSPI::initBankPins(Pin::Id ncsPinId, Pin::Id io0PinId, Pin::Id io1PinId,
                           Pin::Id io2PinId, Pin::Id io3PinId)
{
    auto af = Pin::AF::AF10;
    auto speed = Pin::OutputSpeed::MEDIUM;

    if (ncsPinId != Pin::NONE) {
        auto pin = Pin::get(ncsPinId);
        pin.setMode(Pin::Mode::AF);
        pin.setOutputSpeed(speed);
        pin.setAlternateFunction(af);
    }

    if (io0PinId != Pin::NONE) {
        auto pin = Pin::get(io0PinId);
        pin.setMode(Pin::Mode::AF);
        pin.setOutputSpeed(speed);
        pin.setAlternateFunction(af);
    }

    if (io1PinId != Pin::NONE) {
        auto pin = Pin::get(io1PinId);
        pin.setMode(Pin::Mode::AF);
        pin.setOutputSpeed(speed);
        pin.setAlternateFunction(af);
    }

    if (io2PinId != Pin::NONE) {
        auto pin = Pin::get(io2PinId);
        pin.setMode(Pin::Mode::AF);
        pin.setOutputSpeed(speed);
        pin.setAlternateFunction(af);
    }

    if (io3PinId != Pin::NONE) {
        auto pin = Pin::get(io3PinId);
        pin.setMode(Pin::Mode::AF);
        pin.setOutputSpeed(speed);
        pin.setAlternateFunction(af);
    }
}


void QUADSPI::deinitClockPin(Pin::Id clkPinId)
{
    if (clkPinId != Pin::NONE) {
        auto pin = Pin::get(clkPinId);
        pin.setMode(Pin::Mode::INPUT);
        pin.setAlternateFunction(Pin::AF::AF0);
    }
}


void QUADSPI::deinitBankPins(Pin::Id ncsPinId, Pin::Id io0PinId, Pin::Id io1PinId,
                           Pin::Id io2PinId, Pin::Id io3PinId)
{
    if (ncsPinId != Pin::NONE) {
        auto pin = Pin::get(ncsPinId);
        pin.setMode(Pin::Mode::INPUT);
        pin.setAlternateFunction(Pin::AF::AF0);
    }

    if (io0PinId != Pin::NONE) {
        auto pin = Pin::get(io0PinId);
        pin.setMode(Pin::Mode::INPUT);
        pin.setAlternateFunction(Pin::AF::AF0);
    }

    if (io1PinId != Pin::NONE) {
        auto pin = Pin::get(io1PinId);
        pin.setMode(Pin::Mode::INPUT);
        pin.setAlternateFunction(Pin::AF::AF0);
    }

    if (io2PinId != Pin::NONE) {
        auto pin = Pin::get(io2PinId);
        pin.setMode(Pin::Mode::INPUT);
        pin.setAlternateFunction(Pin::AF::AF0);
    }

    if (io3PinId != Pin::NONE) {
        auto pin = Pin::get(io3PinId);
        pin.setMode(Pin::Mode::INPUT);
        pin.setAlternateFunction(Pin::AF::AF0);
    }
}


void QUADSPI::setPrescaler(int prescaler)
{
    auto registers = getRegisters();
    registers->CR = bitsReplace(registers->CR, prescaler - 1, 8,
            QUADSPI_Registers::CR::PRESCALER_0);
}


void QUADSPI::setSampleShift(bool state)
{
    auto registers = getRegisters();

    if (state) {
        registers->CR = bitSet(registers->CR, QUADSPI_Registers::CR::SSHIFT);
    } else {
        registers->CR = bitReset(registers->CR, QUADSPI_Registers::CR::SSHIFT);
    }
}


void QUADSPI::setFIFOThreshold(int level)
{
    auto registers = getRegisters();
    registers->CR = bitsReplace(registers->CR, level - 1, 4,
            QUADSPI_Registers::CR::FTHRES_0);
}


void QUADSPI::setFlashSize(int bits)
{
    auto registers = getRegisters();
    registers->DCR = bitsReplace(registers->DCR, bits - 1, 5,
            QUADSPI_Registers::DCR::FSIZE_0);
}


void QUADSPI::setCSHighTime(int cycles)
{
    auto registers = getRegisters();
    registers->DCR = bitsReplace(registers->DCR, cycles - 1, 3,
            QUADSPI_Registers::DCR::CSHT_0);
}


void QUADSPI::setClockPolarity(ClockPolarity polarity)
{
    auto registers = getRegisters();

    if (polarity == ClockPolarity::HIGH) {
        registers->DCR = bitSet(registers->DCR, QUADSPI_Registers::DCR::CKMODE);
    } else {
        registers->DCR = bitReset(registers->DCR, QUADSPI_Registers::DCR::CKMODE);
    }
}


void QUADSPI::setDMAEnable(bool state)
{
    auto registers = getRegisters();

    if (state) {
        registers->CR = bitSet(registers->CR, QUADSPI_Registers::CR::DMAEN);
    } else {
        registers->CR = bitReset(registers->CR, QUADSPI_Registers::CR::DMAEN);
    }
}


void QUADSPI::selectMemory(MemorySelect memory)
{
    auto registers = getRegisters();

    if (memory == MemorySelect::FLASH_2) {
        registers->CR = bitSet(registers->CR, QUADSPI_Registers::CR::FSEL);
    } else {
        registers->CR = bitReset(registers->CR, QUADSPI_Registers::CR::FSEL);
    }
}


void QUADSPI::setAddress(volatile uint32_t address)
{
    auto registers = getRegisters();
    registers->AR = address;
}


void QUADSPI::setAlternateBytes(volatile uint32_t value)
{
    auto registers = getRegisters();
    registers->ABR = value;
}


void QUADSPI::setDataLength(volatile uint32_t length)
{
    auto registers = getRegisters();
    registers->DLR = length - 1;
}


void QUADSPI::setStatusMask(volatile uint32_t mask)
{
    auto registers = getRegisters();
    registers->PSMKR = mask;
}


void QUADSPI::setStatusMatch(volatile uint32_t match)
{
    auto registers = getRegisters();
    registers->PSMAR = match;
}


void QUADSPI::setPollingInterval(volatile uint16_t cycles)
{
    auto registers = getRegisters();
    registers->PIR = cycles;
}


void QUADSPI::setPollingMatchMode(PollingMatchMode mode)
{
    auto registers = getRegisters();

    if (mode == PollingMatchMode::OR) {
        registers->CR = bitSet(registers->CR, QUADSPI_Registers::CR::PMM);
    } else {
        registers->CR = bitReset(registers->CR, QUADSPI_Registers::CR::PMM);
    }
}


void QUADSPI::setAutomaticPollModeStop(bool state)
{
    auto registers = getRegisters();

    if (state) {
        registers->CR = bitSet(registers->CR, QUADSPI_Registers::CR::APMS);
    } else {
        registers->CR = bitReset(registers->CR, QUADSPI_Registers::CR::APMS);
    }
}


void QUADSPI::initTransaction(TransactionConfig& config)
{
    auto registers = getRegisters();

    uint32_t ccrValue = 0;

    ccrValue = bitsReplace(ccrValue, (int)config.functionalMode, 2,
            QUADSPI_Registers::CCR::FMODE_0);

    ccrValue = bitsReplace(ccrValue, (int)config.instructionMode, 2,
            QUADSPI_Registers::CCR::IMODE_0);

    ccrValue = bitsReplace(ccrValue, config.instruction, 8,
            QUADSPI_Registers::CCR::INSTRUCTION_0);

    ccrValue = bitsReplace(ccrValue, (int)config.addressMode, 2,
            QUADSPI_Registers::CCR::ADMODE_0);

    ccrValue = bitsReplace(ccrValue, (int)config.addressSize, 2,
            QUADSPI_Registers::CCR::ADSIZE_0);

    ccrValue = bitsReplace(ccrValue, (int)config.alternateBytesMode, 2,
            QUADSPI_Registers::CCR::ABMODE_0);

    ccrValue = bitsReplace(ccrValue, (int)config.alternateBytesSize, 2,
            QUADSPI_Registers::CCR::ABSIZE_0);

    ccrValue = bitsReplace(ccrValue, config.dummyCycles, 5,
            QUADSPI_Registers::CCR::DCYC_0);

    ccrValue = bitsReplace(ccrValue, (int)config.dataMode, 2,
            QUADSPI_Registers::CCR::DMODE_0);

    setDataLength(config.dataLength);
    setAlternateBytes(config.alternateBytes);

    registers->CCR = ccrValue;

    if (config.addressMode != AddressMode::NONE) {
        setAddress(config.address);
    }
}


void QUADSPI::setTransferCompleteCallback(CallbackFunc func, void* context)
{
    transferCompleteCallback = func;
    transferCompleteCallbackContext = context;

    if (transferCompleteCallback != nullptr) {
        setTransferCompleteInterrupt(true);
        auto& nvic = NVIC::get();
        nvic.enableIrq(getIRQNumber());
    } else {
        setTransferCompleteInterrupt(false);
    }
}


void QUADSPI::transmitData(uint8_t buffer[], int length)
{
    for (auto i = 0; i < length; i++) {
        transmitByte(buffer[i]);
    }

    waitUntilTransferComplete();
}


void QUADSPI::receiveData(uint8_t buffer[], int length)
{
    for (auto i = 0; i < length; i++) {
        buffer[i] = receiveByte();
    }
}


void QUADSPI::enable()
{
    auto registers = getRegisters();
    registers->CR = bitSet(registers->CR, QUADSPI_Registers::CR::EN);
}


void QUADSPI::disable()
{
    auto registers = getRegisters();
    registers->CR = bitReset(registers->CR, QUADSPI_Registers::CR::EN);
}


void QUADSPI::abort()
{
    auto registers = getRegisters();
    registers->CR = bitSet(registers->CR, QUADSPI_Registers::CR::ABORT);
}


bool QUADSPI::isBusy()
{
    auto registers = getRegisters();

    return bitValue(registers->SR, QUADSPI_Registers::SR::BUSY);
}


bool QUADSPI::hasTransferComplete()
{
    auto registers = getRegisters();

    return bitValue(registers->SR, QUADSPI_Registers::SR::TCF);
}


void QUADSPI::waitWhileBusy()
{
    while (isBusy()) {
    }
}


void QUADSPI::waitUntilTransferComplete()
{
    while (!hasTransferComplete()) {
    }
}


void QUADSPI::setTransferCompleteInterrupt(bool state)
{
    auto registers = getRegisters();

    if (state) {
        registers->CR = bitSet(registers->CR, QUADSPI_Registers::CR::TCIE);
    } else {
        registers->CR = bitReset(registers->CR, QUADSPI_Registers::CR::TCIE);
    }
}


void QUADSPI::irq()
{
    auto registers = getRegisters();

    if (bitValue(registers->SR, QUADSPI_Registers::SR::TCF)
            && transferCompleteCallback != nullptr) {
        registers->FCR = bitSet(registers->FCR, QUADSPI_Registers::FCR::CTCF);
        transferCompleteCallback(this, transferCompleteCallbackContext);
    }
}


// ============================================================================
// Protected members
// ============================================================================


void QUADSPI::enableClock()
{
    auto rccRegisters = RCC_Registers::get();

    rccRegisters->AHB3ENR = bitSet(rccRegisters->AHB3ENR,
            RCC_Registers::AHB3ENR::QSPIEN);
};


void QUADSPI::disableClock()
{
    auto rccRegisters = RCC_Registers::get();

    rccRegisters->AHB3ENR = bitReset(rccRegisters->AHB3ENR,
            RCC_Registers::AHB3ENR::QSPIEN);
};


void QUADSPI::transmitByte(uint8_t data)
{
    auto registers = getRegisters();
    *((Register8*)&registers->DR) = data;
}


uint8_t QUADSPI::receiveByte()
{
    auto registers = getRegisters();

    return *((Register8*)&registers->DR);
}


void QUADSPI::transmitHalfword(uint16_t data)
{
    auto registers = getRegisters();
    *((Register16*)&registers->DR) = data;
}


uint16_t QUADSPI::receiveHalfword()
{
    auto registers = getRegisters();

    return *((Register16*)&registers->DR);
}


void QUADSPI::transmitWord(uint32_t data)
{
    auto registers = getRegisters();
    *((Register32*)&registers->DR) = data;
}


uint32_t QUADSPI::receiveWord()
{
    auto registers = getRegisters();

    return *((Register32*)&registers->DR);
}


QUADSPI QUADSPI::instance;


}   // namespace mcu
