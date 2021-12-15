/**
 * @file        SDMMC.h
 *
 * Driver for SDMMC peripheral on STM32L4xx
 *
 * @author:     Oliver Rockstedt <info@sourcebox.de>
 * @license     MIT
 */


#pragma once


// Local includes
#include "SDMMC_Base.h"
#include "SDMMC_Registers.h"

// This component
#include "../gpio/Pin.h"

// System libraries
#include <cstdint>


namespace mcu {


class SDMMC : public SDMMC_Base
{
  public:
    enum class ClockEdge
    {
        RISING = 0b0,
        FALLING = 0b1
    };

    enum class BusWidth
    {
        ONE_LINE = 0b00,
        FOUR_LINES = 0b01,
        EIGHT_LINES = 0b10
    };

    /**
     * Configuration settings
     */
    struct Config
    {
        uint32_t clockFreq = 25000000; // Clock frequency in MHz
        Pin::Id ckPinId = Pin::NONE;   // GPIO pin id of CK pin
        Pin::Id cmdPinId = Pin::NONE;  // GPIO pin id of CMD pin
        Pin::Id d0PinId = Pin::NONE;   // GPIO pin id of D0 pin
        Pin::Id d1PinId = Pin::NONE;   // GPIO pin id of D1 pin
        Pin::Id d2PinId = Pin::NONE;   // GPIO pin id of D2 pin
        Pin::Id d3PinId = Pin::NONE;   // GPIO pin id of D3 pin
        Pin::Id d4PinId = Pin::NONE;   // GPIO pin id of D4 pin
        Pin::Id d5PinId = Pin::NONE;   // GPIO pin id of D5 pin
        Pin::Id d6PinId = Pin::NONE;   // GPIO pin id of D6 pin
        Pin::Id d7PinId = Pin::NONE;   // GPIO pin id of D7 pin
    };

    /**
     * Response types
     */
    enum class ResponseType
    {
        NONE = 0b00,
        SHORT = 0b01,
        LONG = 0b11
    };

    /**
     * Command transfer configuration settings
     */
    struct CommandConfig
    {
        uint32_t cmdIndex = 0;
        uint32_t argument = 0;
        ResponseType reponseType = ResponseType::NONE;
        bool waitForInterrupt = false;
        bool enableCPSM = true;
    };

    /**
     * Command response status
     */
    enum class CommandResponseStatus
    {
        OK,
        CRC_FAIL,
        TIMEOUT
    };

    /**
     * Card states
     */
    enum CardState
    {
        IDLE = 0,
        READY = 1,
        IDENT = 2,
        STANDBY = 3,
        TRANSFER = 4,
        DATA = 5,
        RECEIVE = 6,
        PROGRAM = 7,
        DISABLED = 8,

        ERROR = -1
    };

    /**
     * Status codes
     */
    enum Status
    {
        OK,
        INVALID_VOLTAGE,
        CMD_RESPONSE_CRC_FAIL,
        CMD_RESPONSE_TIMEOUT,
        CMD_ERROR,
        DATA_CRC_FAIL,
        DATA_TIMEOUT
    };

    /**
     * Return reference to peripheral
     *
     * @param id            Peripheral id
     * @return              Reference to peripheral
     */
    static SDMMC& get(Id id)
    {
        switch (id) {
            case Id::SDMMC1:
                return sdmmc1;
        }

        return sdmmc1;
    }

    /**
     * Base init
     */
    void init();

    /**
     * Init with config settings
     *
     * @param config        Reference to configuration struct
     */
    void init(Config& config);

    /**
     * Shutdown
     */
    void deinit();

    /**
     * Init card at startup or after being inserted
     *
     * @return              Status enum setting
     */
    Status initCard();

    /**
     * Deinit card
     */
    void deinitCard();

    /**
     * Return card init state
     */
    bool isCardInitialised();

    /**
     * Setup alternate pin function for clock
     *
     * @param ckPinId      Id of CK pin
     */
    void initClockPin(Pin::Id ckPinId);

    /**
     * Setup alternate pin function for command
     *
     * @param cmdPinId     Id of CMD pin
     */
    void initCommandPin(Pin::Id cmdPinId);

    /**
     * Setup alternate pin functions for data lines
     *
     * @param d0PinId       Id of D0 pin
     * @param d1PinId       Id of D1 pin
     * @param d2PinId       Id of D2 pin
     * @param d3PinId       Id of D3 pin
     * @param d4PinId       Id of D4 pin
     * @param d5PinId       Id of D5 pin
     * @param d6PinId       Id of D6 pin
     * @param d7PinId       Id of D7 pin
     */
    void initDataPins(Pin::Id d0PinId, Pin::Id d1PinId, Pin::Id d2PinId,
                      Pin::Id d3PinId, Pin::Id d4PinId, Pin::Id d5PinId,
                      Pin::Id d6PinId, Pin::Id d7PinId);

    /**
     * Release alternate pin function for clock
     *
     * @param ckPinId      Id of CK pin
     */
    void deinitClockPin(Pin::Id ckPinId);

    /**
     * Release alternate pin function for command
     *
     * @param cmdPinId     Id of CMD pin
     */
    void deinitCommandPin(Pin::Id cmdPinId);

    /**
     * Release alternate pin functions for data lines
     *
     * @param d0PinId       Id of D0 pin
     * @param d1PinId       Id of D1 pin
     * @param d2PinId       Id of D2 pin
     * @param d3PinId       Id of D3 pin
     * @param d4PinId       Id of D4 pin
     * @param d5PinId       Id of D5 pin
     * @param d6PinId       Id of D6 pin
     * @param d7PinId       Id of D7 pin
     */
    void deinitDataPins(Pin::Id d0PinId, Pin::Id d1PinId, Pin::Id d2PinId,
                        Pin::Id d3PinId, Pin::Id d4PinId, Pin::Id d5PinId,
                        Pin::Id d6PinId, Pin::Id d7PinId);

    /**
     * Set clock frequency
     *
     * @param clockFreq     Clock frequency in Hz
     */
    void setClockFreq(uint32_t clockFreq);

    /**
     * Set clock edge
     *
     * @param clockEgde     ClockEdge enum setting
     */
    void setClockEdge(ClockEdge clockEdge);

    /**
     * Set clock divider
     *
     * @param clockDivider  Clock divider value 1..255
     */
    void setClockDivider(uint8_t clockDivider);

    /**
     * Enable/disable clock divider bypass
     *
     * @param state         Bypass state
     */
    void setClockDividerBypass(bool state);

    /**
     * Enable/disable clock power save
     *
     * @param state         Power save state
     */
    void setClockPowerSave(bool state);

    /**
     * Enable/disable hardware flow control
     *
     * @param state         Flow control state
     */
    void setHardwareFlowControl(bool state);

    /**
     * Set data bus width
     *
     * @param busWidth      BusWidth enum setting
     */
    void setBusWidth(BusWidth busWidth);

    /**
     * Enable SDMMC_CK clock
     */
    void enableClock();

    /**
     * Disable SDMMC_CK clock
     */
    void disableClock();

    /**
     * Set power on
     */
    void powerOn();

    /**
     * Set power off
     */
    void powerOff();

    /**
     * Send a command
     *
     * @param config    Reference to config struct
     */
    void sendCommand(CommandConfig& config);

    /**
     * Wait until command is transferred completely
     *
     * @return          CommandResponseStatus enum setting
     */
    SDMMC::CommandResponseStatus waitUntilCommandTransferred();

    /**
     * Wait for command response after sending
     *
     * @return          CommandResponseStatus enum setting
     */
    CommandResponseStatus waitForCommandResponse();

    /**
     * Return command reponse
     *
     * @param           Response index 0..3, MSB first
     * @return          Response content
     */
    uint32_t getCommandResponse(int index);

    /**
     * Return card state
     *
     * @return          CardState enum setting
     */
    CardState getCardState();

    /**
     * Read a block of data into buffer
     *
     * @param buffer    Buffer to be filled with data, must be 512 bytes long
     * @param blockNo   Block number
     * @return          Status enum setting
     */
    Status readBlock(uint8_t buffer[], uint32_t blockNo);

    /**
     * Write a block of data to card
     *
     * @param buffer    Buffer containing data, must be 512 bytes long
     * @param blockNo   Block number
     * @return          Status enum setting
     */
    Status writeBlock(uint8_t buffer[], uint32_t blockNo);

    /**
     * Return pointer to registers
     *
     * @return      Pointer to registers struct
     */
    auto getRegisters()
    {
        return SDMMC_Registers::get(id);
    }

    /**
     * Process interrupt, called from IRQ handler
     */
    void irq();

  protected:
    /**
     * Private constructors because of singleton pattern, no copy allowed
     */
    SDMMC(Id id) : id(id)
    {
    }
    SDMMC(const SDMMC&) = delete;
    SDMMC& operator=(const SDMMC&) = delete;
    SDMMC& operator=(SDMMC&&) = delete;

    /**
     * Enable RCC peripheral clock
     */
    void enablePeripheralClock();

    /**
     * Disable RCC peripheral clock
     */
    void disablePeripheralClock();

    /**
     * Clear all status flags
     */
    void clearAllStatusFlags();

    /**
     * Clear data status flags
     */
    void clearDataStatusFlags();

    /**
     * Peripheral id
     */
    const Id id;

    /**
     * Flag for successful card initialisation
     */
    bool cardInitialised = false;

    /**
     * Flag for card V2.x
     */
    bool cardV2 = false;

    /**
     * Flag for SDHC/SDXC
     */
    bool highCapacity = false;

    /**
     * Relative card address
     */
    uint16_t rca = 0;

    /**
     * CID register data
     */
    uint32_t cid[4];

    /**
     * CSD register data
     */
    uint32_t csd[4];

    /**
     * Card command classes
     */
    uint16_t ccc = 0;

    /**
     * Clock frequency in MHz
     */
    uint32_t clockFreq = 25000000;

    /**
     * Singleton instance
     */
    static SDMMC sdmmc1;
};


} // namespace mcu
