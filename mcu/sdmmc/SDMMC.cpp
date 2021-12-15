/**
 * @file        SDMMC.cpp
 *
 * Driver for SDMMC peripheral on STM32L4xx
 *
 * @author:     Oliver Rockstedt <info@sourcebox.de>
 * @license     MIT
 */


// Corresponding header
#include "SDMMC.h"

// This component
#include "../core/NVIC.h"
#include "../rcc/RCC.h"
#include "../rcc/RCC_Registers.h"
#include "../utility/bit_manipulation.h"
#include "../utility/register.h"
#include "../utility/time.h"

// System libraries
#include <cstdlib>
#include <cstring>


namespace mcu {


// ============================================================================
// Public members
// ============================================================================


void SDMMC::init()
{
    enablePeripheralClock();
}


void SDMMC::init(Config& config)
{
    init();

    initClockPin(config.ckPinId);
    initCommandPin(config.cmdPinId);
    initDataPins(config.d0PinId,
                 config.d1PinId,
                 config.d2PinId,
                 config.d3PinId,
                 config.d4PinId,
                 config.d5PinId,
                 config.d6PinId,
                 config.d7PinId);

    clockFreq = config.clockFreq;
}


void SDMMC::deinit()
{
    disablePeripheralClock();
}


SDMMC::Status SDMMC::initCard()
{
    setClockEdge(ClockEdge::RISING);
    setClockDividerBypass(false);
    setClockPowerSave(false);
    setHardwareFlowControl(false);
    setBusWidth(BusWidth::ONE_LINE);

    setClockFreq(400000);

    disableClock();
    powerOn();
    enableClock();

    // Wait at least 74 clock cycles after startup, use 250µs delay to be safe
    delayMicroseconds(250);

    // Reset card via CMD0 - GO_IDLE_STATE
    CommandConfig cmd0config;
    cmd0config.cmdIndex = 0;
    cmd0config.enableCPSM = true;
    sendCommand(cmd0config);
    auto cmd0response = waitUntilCommandTransferred();

    if (cmd0response != CommandResponseStatus::OK) {
        return Status::CMD_RESPONSE_TIMEOUT;
    }

    // Check supported supply voltage via CMD8 - SEND_IF_COND
    // This command is only supported by V2.0 cards
    CommandConfig cmd8config;
    cmd8config.cmdIndex = 8;
    cmd8config.argument = (0x01 << 8) | 0xAA;
    cmd8config.reponseType = ResponseType::SHORT;
    cmd8config.enableCPSM = true;
    sendCommand(cmd8config);

    auto cmd8response = waitForCommandResponse();

    if (cmd8response == CommandResponseStatus::OK) {
        auto response = getCommandResponse(0);
        if (!bitValue(response, 8)) {
            // Card does not accept 3.3V, should not happen
            return Status::INVALID_VOLTAGE;
        }
        cardV2 = true;
    }

    bool validVoltage = false;

    int retryCount = 0;

    while (!validVoltage) {
        // Signal via CMD55 - APP_CMD that next command is application specific
        CommandConfig cmd55config;
        cmd55config.cmdIndex = 55;
        cmd55config.reponseType = ResponseType::SHORT;
        cmd55config.enableCPSM = true;
        sendCommand(cmd55config);

        auto cmd55response = waitForCommandResponse();

        if (cmd55response != CommandResponseStatus::OK) {
            if (cmd55response == CommandResponseStatus::CRC_FAIL) {
                return Status::CMD_RESPONSE_CRC_FAIL;
            } else {
                return Status::CMD_RESPONSE_TIMEOUT;
            }
        }

        // Initialize card via ACMD41 - SD_SEND_OP_COND
        CommandConfig acmd41config;
        acmd41config.cmdIndex = 41;
        acmd41config.argument = 0x80100000 | 0x40000000 | 0x01000000;
        acmd41config.reponseType = ResponseType::SHORT;
        acmd41config.enableCPSM = true;
        sendCommand(acmd41config);

        auto acmd41response = waitForCommandResponse();

        if (acmd41response != CommandResponseStatus::TIMEOUT) {
            // Response does not have a CRC field, so CRC_FAIL will always
            // happen
            auto response = getCommandResponse(0);
            validVoltage = (response >> 31) == 1;
            highCapacity = response & 0x40000000;
        }

        retryCount++;

        if (retryCount > 0xFFFF) {
            return Status::CMD_RESPONSE_TIMEOUT;
        }
    }

    // Get card id data via CMD2 - ALL_SEND_CID
    CommandConfig cmd2config;
    cmd2config.cmdIndex = 2;
    cmd2config.reponseType = ResponseType::LONG;
    cmd2config.enableCPSM = true;
    sendCommand(cmd2config);

    auto cmd2response = waitForCommandResponse();

    if (cmd2response == CommandResponseStatus::OK) {
        cid[0] = getCommandResponse(0);
        cid[1] = getCommandResponse(1);
        cid[2] = getCommandResponse(2);
        cid[3] = getCommandResponse(3);
    } else {
        if (cmd2response == CommandResponseStatus::CRC_FAIL) {
            return Status::CMD_RESPONSE_CRC_FAIL;
        } else {
            return Status::CMD_RESPONSE_TIMEOUT;
        }
    }

    // Get new relative address from card via CMD3 - SEND_RELATIVE_ADDR
    CommandConfig cmd3config;
    cmd3config.cmdIndex = 3;
    cmd3config.reponseType = ResponseType::SHORT;
    cmd3config.enableCPSM = true;
    sendCommand(cmd3config);

    auto cmd3response = waitForCommandResponse();

    if (cmd3response == CommandResponseStatus::OK) {
        auto response = getCommandResponse(0);
        rca = response >> 16;
    } else {
        if (cmd3response == CommandResponseStatus::CRC_FAIL) {
            return Status::CMD_RESPONSE_CRC_FAIL;
        } else {
            return Status::CMD_RESPONSE_TIMEOUT;
        }
    }

    // Get card specific data via CMD9 - SEND_CSD
    CommandConfig cmd9config;
    cmd9config.cmdIndex = 9;
    cmd9config.argument = (uint32_t)rca << 16;
    cmd9config.reponseType = ResponseType::LONG;
    cmd9config.enableCPSM = true;
    sendCommand(cmd9config);

    auto cmd9response = waitForCommandResponse();

    if (cmd9response == CommandResponseStatus::OK) {
        csd[0] = getCommandResponse(0);
        csd[1] = getCommandResponse(1);
        csd[2] = getCommandResponse(2);
        csd[3] = getCommandResponse(3);
        ccc = csd[1] >> 20;
    } else {
        if (cmd9response == CommandResponseStatus::CRC_FAIL) {
            return Status::CMD_RESPONSE_CRC_FAIL;
        } else {
            return Status::CMD_RESPONSE_TIMEOUT;
        }
    }

    // Select the card via CMD7 - SELECT/DESELECT_CARD
    CommandConfig cmd7config;
    cmd7config.cmdIndex = 7;
    cmd7config.argument = (uint32_t)rca << 16;
    cmd7config.reponseType = ResponseType::SHORT;
    cmd7config.enableCPSM = true;
    sendCommand(cmd7config);

    auto cmd7response = waitForCommandResponse();

    if (cmd7response != CommandResponseStatus::OK) {
        if (cmd7response == CommandResponseStatus::CRC_FAIL) {
            return Status::CMD_RESPONSE_CRC_FAIL;
        } else {
            return Status::CMD_RESPONSE_TIMEOUT;
        }
    }

    retryCount = 0;

    while (true) {
        // Get card status via CMD13 - SEND_STATUS
        CommandConfig cmd13config;
        cmd13config.cmdIndex = 13;
        cmd13config.argument = (uint32_t)rca << 16;
        cmd13config.reponseType = ResponseType::SHORT;
        cmd13config.enableCPSM = true;
        sendCommand(cmd13config);

        auto cmd13response = waitForCommandResponse();

        if (cmd13response == CommandResponseStatus::OK) {
            auto response = getCommandResponse(0);
            if (bitsValue(response, 4, 9) == 4) {
                // Card is now in transfer state, so move on
                break;
            }
        } else {
            if (cmd13response == CommandResponseStatus::CRC_FAIL) {
                return Status::CMD_RESPONSE_CRC_FAIL;
            } else {
                return Status::CMD_RESPONSE_TIMEOUT;
            }
        }

        retryCount++;

        if (retryCount > 0xFFFF) {
            return Status::CMD_RESPONSE_TIMEOUT;
        }
    }

    setClockFreq(clockFreq);

    cardInitialised = true;

    return Status::OK;
}


void SDMMC::deinitCard()
{
    cardInitialised = false;
    disableClock();
    powerOff();
}


bool SDMMC::isCardInitialised()
{
    return cardInitialised;
}


void SDMMC::initClockPin(Pin::Id ckPinId)
{
    auto af = Pin::AF::AF12;
    auto speed = Pin::OutputSpeed::MEDIUM;

    if (ckPinId != Pin::NONE) {
        auto pin = Pin::get(ckPinId);
        pin.setMode(Pin::Mode::AF);
        pin.setOutputSpeed(speed);
        pin.setAlternateFunction(af);
    }
}


void SDMMC::initCommandPin(Pin::Id cmdPinId)
{
    auto af = Pin::AF::AF12;
    auto speed = Pin::OutputSpeed::MEDIUM;

    if (cmdPinId != Pin::NONE) {
        auto pin = Pin::get(cmdPinId);
        pin.setMode(Pin::Mode::AF);
        pin.setOutputSpeed(speed);
        pin.setAlternateFunction(af);
    }
}


void SDMMC::initDataPins(Pin::Id d0PinId, Pin::Id d1PinId, Pin::Id d2PinId,
                         Pin::Id d3PinId, Pin::Id d4PinId, Pin::Id d5PinId,
                         Pin::Id d6PinId, Pin::Id d7PinId)
{
    auto af = Pin::AF::AF12;
    auto speed = Pin::OutputSpeed::MEDIUM;

    if (d0PinId != Pin::NONE) {
        auto pin = Pin::get(d0PinId);
        pin.setMode(Pin::Mode::AF);
        pin.setOutputSpeed(speed);
        pin.setAlternateFunction(af);
    }

    if (d1PinId != Pin::NONE) {
        auto pin = Pin::get(d1PinId);
        pin.setMode(Pin::Mode::AF);
        pin.setOutputSpeed(speed);
        pin.setAlternateFunction(af);
    }

    if (d2PinId != Pin::NONE) {
        auto pin = Pin::get(d2PinId);
        pin.setMode(Pin::Mode::AF);
        pin.setOutputSpeed(speed);
        pin.setAlternateFunction(af);
    }

    if (d3PinId != Pin::NONE) {
        auto pin = Pin::get(d3PinId);
        pin.setMode(Pin::Mode::AF);
        pin.setOutputSpeed(speed);
        pin.setAlternateFunction(af);
    }

    if (d4PinId != Pin::NONE) {
        auto pin = Pin::get(d4PinId);
        pin.setMode(Pin::Mode::AF);
        pin.setOutputSpeed(speed);
        pin.setAlternateFunction(af);
    }

    if (d5PinId != Pin::NONE) {
        auto pin = Pin::get(d5PinId);
        pin.setMode(Pin::Mode::AF);
        pin.setOutputSpeed(speed);
        pin.setAlternateFunction(af);
    }

    if (d6PinId != Pin::NONE) {
        auto pin = Pin::get(d6PinId);
        pin.setMode(Pin::Mode::AF);
        pin.setOutputSpeed(speed);
        pin.setAlternateFunction(af);
    }

    if (d7PinId != Pin::NONE) {
        auto pin = Pin::get(d7PinId);
        pin.setMode(Pin::Mode::AF);
        pin.setOutputSpeed(speed);
        pin.setAlternateFunction(af);
    }
}


void SDMMC::deinitClockPin(Pin::Id ckPinId)
{
    if (ckPinId != Pin::NONE) {
        auto pin = Pin::get(ckPinId);
        pin.setMode(Pin::Mode::INPUT);
        pin.setAlternateFunction(Pin::AF::AF0);
    }
}


void SDMMC::deinitCommandPin(Pin::Id cmdPinId)
{
    if (cmdPinId != Pin::NONE) {
        auto pin = Pin::get(cmdPinId);
        pin.setMode(Pin::Mode::INPUT);
        pin.setAlternateFunction(Pin::AF::AF0);
    }
}


void SDMMC::deinitDataPins(Pin::Id d0PinId, Pin::Id d1PinId, Pin::Id d2PinId,
                           Pin::Id d3PinId, Pin::Id d4PinId, Pin::Id d5PinId,
                           Pin::Id d6PinId, Pin::Id d7PinId)
{
    if (d0PinId != Pin::NONE) {
        auto pin = Pin::get(d0PinId);
        pin.setMode(Pin::Mode::INPUT);
        pin.setAlternateFunction(Pin::AF::AF0);
    }

    if (d1PinId != Pin::NONE) {
        auto pin = Pin::get(d1PinId);
        pin.setMode(Pin::Mode::INPUT);
        pin.setAlternateFunction(Pin::AF::AF0);
    }

    if (d2PinId != Pin::NONE) {
        auto pin = Pin::get(d2PinId);
        pin.setMode(Pin::Mode::INPUT);
        pin.setAlternateFunction(Pin::AF::AF0);
    }

    if (d3PinId != Pin::NONE) {
        auto pin = Pin::get(d3PinId);
        pin.setMode(Pin::Mode::INPUT);
        pin.setAlternateFunction(Pin::AF::AF0);
    }

    if (d4PinId != Pin::NONE) {
        auto pin = Pin::get(d4PinId);
        pin.setMode(Pin::Mode::INPUT);
        pin.setAlternateFunction(Pin::AF::AF0);
    }

    if (d5PinId != Pin::NONE) {
        auto pin = Pin::get(d5PinId);
        pin.setMode(Pin::Mode::INPUT);
        pin.setAlternateFunction(Pin::AF::AF0);
    }

    if (d6PinId != Pin::NONE) {
        auto pin = Pin::get(d6PinId);
        pin.setMode(Pin::Mode::INPUT);
        pin.setAlternateFunction(Pin::AF::AF0);
    }

    if (d7PinId != Pin::NONE) {
        auto pin = Pin::get(d7PinId);
        pin.setMode(Pin::Mode::INPUT);
        pin.setAlternateFunction(Pin::AF::AF0);
    }
}


void SDMMC::setClockFreq(uint32_t clockFreq)
{
    const uint32_t SDMMC_CLOCK_FREQ = 50000000;
    auto clockDiv = SDMMC_CLOCK_FREQ / clockFreq;
    setClockDivider(clockDiv);
}


void SDMMC::setClockEdge(ClockEdge clockEdge)
{
    auto registers = getRegisters();

    registers->CLKCR = bitsReplace(
        registers->CLKCR, (int)clockEdge, 1, SDMMC_Registers::CLKCR::NEGEDGE);
}


void SDMMC::setClockDivider(uint8_t clockDivider)
{
    if (clockDivider < 2) {
        clockDivider = 2;
    }

    auto registers = getRegisters();

    registers->CLKCR = bitsReplace(registers->CLKCR,
                                   clockDivider - 2,
                                   8,
                                   SDMMC_Registers::CLKCR::CLKDIV_0);
}


void SDMMC::setClockDividerBypass(bool state)
{
    auto registers = getRegisters();

    if (state) {
        registers->CLKCR
            = bitSet(registers->CLKCR, SDMMC_Registers::CLKCR::BYPASS);
    } else {
        registers->CLKCR
            = bitReset(registers->CLKCR, SDMMC_Registers::CLKCR::BYPASS);
    }
}


void SDMMC::setClockPowerSave(bool state)
{
    auto registers = getRegisters();

    if (state) {
        registers->CLKCR
            = bitSet(registers->CLKCR, SDMMC_Registers::CLKCR::PWRSAV);
    } else {
        registers->CLKCR
            = bitReset(registers->CLKCR, SDMMC_Registers::CLKCR::PWRSAV);
    }
}


void SDMMC::setHardwareFlowControl(bool state)
{
    auto registers = getRegisters();

    if (state) {
        registers->CLKCR
            = bitSet(registers->CLKCR, SDMMC_Registers::CLKCR::HWFC_EN);
    } else {
        registers->CLKCR
            = bitReset(registers->CLKCR, SDMMC_Registers::CLKCR::HWFC_EN);
    }
}


void SDMMC::setBusWidth(BusWidth busWidth)
{
    auto registers = getRegisters();

    registers->CLKCR = bitsReplace(
        registers->CLKCR, (int)busWidth, 2, SDMMC_Registers::CLKCR::WIDBUS_0);
}


void SDMMC::enableClock()
{
    auto registers = getRegisters();

    registers->CLKCR = bitSet(registers->CLKCR, SDMMC_Registers::CLKCR::CLKEN);
}


void SDMMC::disableClock()
{
    auto registers = getRegisters();

    registers->CLKCR
        = bitReset(registers->CLKCR, SDMMC_Registers::CLKCR::CLKEN);
}


void SDMMC::powerOn()
{
    auto registers = getRegisters();

    registers->POWER = bitsReplace(
        registers->POWER, 0b11, 2, SDMMC_Registers::POWER::PWRCTL_0);

    // Power up wait time
    delayMilliseconds(2);
}


void SDMMC::powerOff()
{
    auto registers = getRegisters();

    registers->POWER = 0;
}


void SDMMC::sendCommand(CommandConfig& config)
{
    auto registers = getRegisters();

    registers->ARG = config.argument;

    uint32_t value = 0;

    value = bitsReplace(
        value, config.cmdIndex, 6, SDMMC_Registers::CMD::CMDINDEX_0);

    value = bitsReplace(
        value, (int)config.reponseType, 2, SDMMC_Registers::CMD::WAITRESP_0);

    if (config.waitForInterrupt) {
        value = bitSet(value, SDMMC_Registers::CMD::WAITINT);
    }

    if (config.enableCPSM) {
        value = bitSet(value, SDMMC_Registers::CMD::CPSMEN);
    }

    registers->CMD = value;
}


SDMMC::CommandResponseStatus SDMMC::waitUntilCommandTransferred()
{
    auto registers = getRegisters();

    volatile uint32_t status = 0;

    auto timestamp = getMilliseconds();
    auto timeout = false;

    do {
        status = registers->STA;
        if (getMilliseconds() > timestamp + 1) {
            timeout = true;
        }
    } while (bitValue(status, SDMMC_Registers::STA::CMDACT) != 0 && !timeout);

    if (timeout) {
        return CommandResponseStatus::TIMEOUT;
    }

    return CommandResponseStatus::OK;
}


SDMMC::CommandResponseStatus SDMMC::waitForCommandResponse()
{
    auto registers = getRegisters();

    volatile uint32_t status = 0;

    do {
        status = registers->STA;
    } while ((bitValue(status, SDMMC_Registers::STA::CMDACT) != 0)
             && (bitValue(status, SDMMC_Registers::STA::CMDREND) == 0)
             && (bitValue(status, SDMMC_Registers::STA::CCRCFAIL) == 0)
             && (bitValue(status, SDMMC_Registers::STA::CTIMEOUT) == 0));

    if (bitValue(status, SDMMC_Registers::STA::CTIMEOUT)) {
        registers->ICR
            = bitSet(registers->ICR, SDMMC_Registers::ICR::CTIMEOUTC);
        return CommandResponseStatus::TIMEOUT;
    } else if (bitValue(status, SDMMC_Registers::STA::CCRCFAIL)) {
        registers->ICR
            = bitSet(registers->ICR, SDMMC_Registers::ICR::CCRCFAILC);
        return CommandResponseStatus::CRC_FAIL;
    }

    registers->ICR = bitSet(registers->ICR, SDMMC_Registers::ICR::CMDRENDC);

    return CommandResponseStatus::OK;
}


uint32_t SDMMC::getCommandResponse(int index)
{
    auto registers = getRegisters();

    switch (index) {
        case 0:
            return registers->RESP1;
        case 1:
            return registers->RESP2;
        case 2:
            return registers->RESP3;
        case 3:
            return registers->RESP4;
    }

    return 0;
}


SDMMC::CardState SDMMC::getCardState()
{
    // Get card status via CMD13 - SEND_STATUS
    CommandConfig cmdConfig;
    cmdConfig.cmdIndex = 13;
    cmdConfig.argument = (uint32_t)rca << 16;
    cmdConfig.reponseType = ResponseType::SHORT;
    cmdConfig.enableCPSM = true;
    sendCommand(cmdConfig);

    auto cmdResponse = waitForCommandResponse();

    if (cmdResponse == CommandResponseStatus::OK) {
        auto response = getCommandResponse(0);
        return (CardState)bitsValue(response, 4, 9);
    } else {
        return CardState::ERROR;
    }
}


SDMMC::Status SDMMC::readBlock(uint8_t buffer[], uint32_t blockNo)
{
    clearDataStatusFlags();

    auto registers = getRegisters();

    // Configure data path
    registers->DTIMER = 0xFFFFFFFF;
    registers->DLEN = bitsReplace(registers->DLEN, 512, 12, 0);

    uint32_t value = 0;
    value = bitSet(value, SDMMC_Registers::DCTRL::DTDIR);
    value = bitsReplace(value, 0b1001, 4, SDMMC_Registers::DCTRL::DBLOCKSIZE_0);
    value = bitSet(value, SDMMC_Registers::DCTRL::DTEN);
    registers->DCTRL = value;

    // Read via CMD17 - READ_SINGLE_BLOCK
    CommandConfig cmd17config;
    cmd17config.cmdIndex = 17;
    cmd17config.argument = blockNo; // Data address
    cmd17config.reponseType = ResponseType::SHORT;

    sendCommand(cmd17config);

    auto cmd17response = waitForCommandResponse();

    if (cmd17response != CommandResponseStatus::OK) {
        if (cmd17response == CommandResponseStatus::CRC_FAIL) {
            return Status::CMD_RESPONSE_CRC_FAIL;
        } else {
            return Status::CMD_RESPONSE_TIMEOUT;
        }
    }

    uint32_t bufferIndex = 0;

    volatile uint32_t status = 0;

    do {
        status = registers->STA;
        if (bitValue(status, SDMMC_Registers::STA::RXFIFOHF)) {
            // FIFO contains at least 8 values
            for (auto i = 0; i < 8; i++) {
                auto data = registers->FIFO;
                buffer[bufferIndex++] = data & 0xFF;
                buffer[bufferIndex++] = (data >> 8) & 0xFF;
                buffer[bufferIndex++] = (data >> 16) & 0xFF;
                buffer[bufferIndex++] = (data >> 24) & 0xFF;
            }
        }
    } while ((bitValue(status, SDMMC_Registers::STA::RXOVERR) == 0)
             && (bitValue(status, SDMMC_Registers::STA::DATAEND) == 0)
             && (bitValue(status, SDMMC_Registers::STA::DCRCFAIL) == 0)
             && (bitValue(status, SDMMC_Registers::STA::DTIMEOUT) == 0)
             && (bufferIndex <= (512 - 32)));

    // Empty FIFO if there is some data remaining
    while (bitValue(registers->STA, SDMMC_Registers::STA::RXDAVL)) {
        __attribute__((unused)) auto data = registers->FIFO;
    }

    if (bitValue(status, SDMMC_Registers::STA::DTIMEOUT)) {
        return Status::DATA_TIMEOUT;
    } else if (bitValue(status, SDMMC_Registers::STA::DCRCFAIL)) {
        return Status::DATA_CRC_FAIL;
    }

    while (getCardState() != CardState::TRANSFER) {
        // Wait until card is in transfer state again
    }

    return Status::OK;
}


SDMMC::Status SDMMC::writeBlock(uint8_t buffer[], uint32_t blockNo)
{
    clearDataStatusFlags();

    auto registers = getRegisters();

    // Configure data path
    registers->DTIMER = 0xFFFFFFFF;
    registers->DLEN = bitsReplace(registers->DLEN, 512, 12, 0);

    uint32_t value = 0;
    value = bitsReplace(value, 0b1001, 4, SDMMC_Registers::DCTRL::DBLOCKSIZE_0);
    value = bitSet(value, SDMMC_Registers::DCTRL::DTEN);
    registers->DCTRL = value;

    // Write via CMD24 - WRITE_BLOCK
    CommandConfig cmd24config;
    cmd24config.cmdIndex = 24;
    cmd24config.argument = blockNo; // Data address
    cmd24config.reponseType = ResponseType::SHORT;

    sendCommand(cmd24config);

    auto cmd24response = waitForCommandResponse();

    if (cmd24response != CommandResponseStatus::OK) {
        if (cmd24response == CommandResponseStatus::CRC_FAIL) {
            return Status::CMD_RESPONSE_CRC_FAIL;
        } else {
            return Status::CMD_RESPONSE_TIMEOUT;
        }
    }

    uint32_t bufferIndex = 0;

    volatile uint32_t status = 0;

    do {
        status = registers->STA;
        if (bitValue(status, SDMMC_Registers::STA::TXFIFOHE)) {
            // FIFO contains less than 8 values
            for (auto i = 0; i < 8; i++) {
                auto data = (uint32_t)buffer[bufferIndex]
                                   | ((uint32_t)buffer[bufferIndex + 1] << 8)
                                   | ((uint32_t)buffer[bufferIndex + 2] << 16)
                                   | ((uint32_t)buffer[bufferIndex + 3] << 24);
                bufferIndex += 4;
                registers->FIFO = data;
            }
        }
    } while ((bitValue(status, SDMMC_Registers::STA::TXUNDERR) == 0)
             && (bitValue(status, SDMMC_Registers::STA::DATAEND) == 0)
             && (bitValue(status, SDMMC_Registers::STA::DCRCFAIL) == 0)
             && (bitValue(status, SDMMC_Registers::STA::DTIMEOUT) == 0)
             && (bufferIndex <= (512 - 32)));

    while (bitValue(registers->STA, SDMMC_Registers::STA::TXDAVL)) {
        // While until FIFO is empty
    }

    if (bitValue(status, SDMMC_Registers::STA::DTIMEOUT)) {
        return Status::DATA_TIMEOUT;
    } else if (bitValue(status, SDMMC_Registers::STA::DCRCFAIL)) {
        return Status::DATA_CRC_FAIL;
    }

    while (getCardState() != CardState::TRANSFER) {
        // Wait until card is in transfer state again
    }

    return Status::OK;
}


void SDMMC::irq()
{
}


// ============================================================================
// Protected members
// ============================================================================


void SDMMC::enablePeripheralClock()
{
    auto rccRegisters = RCC_Registers::get();

    // HSI48 clock has to be enabled for SDMMMC peripheral
    if (!bitValue(rccRegisters->CRRCR, RCC_Registers::CRRCR::HSI48ON)) {
        rccRegisters->CRRCR
            = bitSet(rccRegisters->CRRCR, RCC_Registers::CRRCR::HSI48ON);

        while (!bitValue(rccRegisters->CRRCR, RCC_Registers::CRRCR::HSI48RDY)) {
            // Wait until HSI48 clock is stable
        }
    }

    rccRegisters->APB2ENR
        = bitSet(rccRegisters->APB2ENR, RCC_Registers::APB2ENR::SDMMC1EN);
};


void SDMMC::disablePeripheralClock()
{
    auto rccRegisters = RCC_Registers::get();

    rccRegisters->APB2ENR
        = bitReset(rccRegisters->APB2ENR, RCC_Registers::APB2ENR::SDMMC1EN);
};


void SDMMC::clearAllStatusFlags()
{
    auto registers = getRegisters();

    auto value = 0;
    value = bitSet(value, SDMMC_Registers::ICR::CCRCFAILC);
    value = bitSet(value, SDMMC_Registers::ICR::DCRCFAILC);
    value = bitSet(value, SDMMC_Registers::ICR::CTIMEOUTC);
    value = bitSet(value, SDMMC_Registers::ICR::DTIMEOUTC);
    value = bitSet(value, SDMMC_Registers::ICR::TXUNDERRC);
    value = bitSet(value, SDMMC_Registers::ICR::RXOVERRC);
    value = bitSet(value, SDMMC_Registers::ICR::CMDRENDC);
    value = bitSet(value, SDMMC_Registers::ICR::CMDSENTC);
    value = bitSet(value, SDMMC_Registers::ICR::DATAENDC);
    value = bitSet(value, SDMMC_Registers::ICR::DBCKENDC);
    value = bitSet(value, SDMMC_Registers::ICR::SDIOITC);

    registers->ICR = value;
}


void SDMMC::clearDataStatusFlags()
{
    auto registers = getRegisters();

    auto value = 0;
    value = bitSet(value, SDMMC_Registers::ICR::DCRCFAILC);
    value = bitSet(value, SDMMC_Registers::ICR::DTIMEOUTC);
    value = bitSet(value, SDMMC_Registers::ICR::TXUNDERRC);
    value = bitSet(value, SDMMC_Registers::ICR::RXOVERRC);
    value = bitSet(value, SDMMC_Registers::ICR::DATAENDC);
    value = bitSet(value, SDMMC_Registers::ICR::DBCKENDC);
    value = bitSet(value, SDMMC_Registers::ICR::SDIOITC);

    registers->ICR = value;
}


SDMMC SDMMC::sdmmc1 = SDMMC(SDMMC::SDMMC1);
} // namespace mcu
