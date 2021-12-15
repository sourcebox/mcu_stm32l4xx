/**
 * @file        USB_Endpoint.h
 *
 * Driver for USB endpoints on STM32L4xx
 *
 * @author:     Oliver Rockstedt <info@sourcebox.de>
 * @license     MIT
 */


#pragma once


// Local includes
#include "USB_Registers.h"
#include "USB_SRAM.h"

// System libraries
#include <cstdint>


namespace mcu {


class USB_Endpoint
{
    friend class USB;

    public:
        /**
         * Endpoint type
         */
        enum class Type
        {
            BULK        = 0b00,
            CONTROL     = 0b01,
            ISOCHRONOUS = 0b10,
            INTERRUPT   = 0b11
        };

        /**
         * Endpoint status
         */
        enum class Status
        {
            DISABLED    = 0b00,
            STALL       = 0b01,
            NAK         = 0b10,
            VALID       = 0b11
        };

        /**
         * Constructor
         *
         * @param number        Endpoint number 0..7
         */
        USB_Endpoint(int number) : number(number) {}

        /**
         * Disallow copy
         */
        USB_Endpoint(const USB_Endpoint&) = delete;
        USB_Endpoint& operator= (const USB_Endpoint&) = delete;
        USB_Endpoint& operator = (USB_Endpoint&&) = delete;

        /**
         * Transmit data
         *
         * @param data          Buffer containing data
         * @param size          Data size in bytes
         */
        void transmit(uint8_t data[], int size);

        /**
         * Receive data
         *
         * @param data          Buffer to be filled with data
         * @param size          Buffer size in bytes
         * @return              Number of received bytes
         */
        int receive(uint8_t data[], int size);

        /**
         * Return length of received data
         *
         * @return              Length of received data in bytes
         */
        int getReceivedLength();

        /**
         * Set endpoint address
         *
         * @param address       Endpoint address 0..15
         */
        void setAddress(int address);

        /**
         * Set endpoint type
         *
         * @param type          Type according to enum class
         */
        void setType(Type type);

        /**
         * Set endpoint transmission status
         *
         * @param type          Status according to enum class
         */
        void setTransmissionStatus(Status status);

        /**
         * Set endpoint reception status
         *
         * @param type          Status according to enum class
         */
        void setReceptionStatus(Status status);

        /**
         * Set addresses and sizes in buffer description table
         *
         * @param txAddress     Transmit buffer address in table
         * @param txSize        Transmit buffer size
         * @param rxAddress     Receive buffer address in table
         * @param rxSize        Receive buffer size
         */
        void setBufferDescriptor(int txAddress, int txSize, int rxAddress, int rxSize);

        /**
         * Init buffer descriptor in SRAM
         */
        void initBufferDescriptor();

        /**
         * Return number
         *
         * @return              Endpoint number 0..7
         */
        auto getNumber()
        {
            return number;
        }

        /**
         * Return pointer to endpoint register
         */
        auto getRegister()
        {
            return EPnR;
        }

    protected:
        /**
         * Called from USB::init()
         */
        virtual void onInit() {}

        /**
         * Called from USB::irq() on reset
         */
        virtual void onReset() {}

        /**
         * Called from USB::irq() when a setup packet was received
         */
        virtual void onSetupReceptionComplete() {}

        /**
         * Called from USB::irq() when data was received
         */
        virtual void onReceptionComplete() {}

        /**
         * Called from USB::irq() when data was transmitted
         */
        virtual void onTransmissionComplete() {}

        /**
         * Init, called from USB::init()
         */
        void init();

        /**
         * Reset, called from USB::onReset()
         */
        void reset();

        /**
         * Return the value of the CTR_TX bit in the endpoint register
         *
         * @return              Bit value
         */
        bool getTxFlag();

        /**
         * Return the value of the CTR_RX bit in the endpoint register
         *
         * @return              Bit value
         */
        bool getRxFlag();

        /**
         * Clear the CTR_TX bit in the endpoint register
         */
        void clearTxFlag();

        /**
         * Clear the CTR_RX bit in the endpoint register
         */
        void clearRxFlag();

        /**
         * Clear the CTR_TX and CTR_RX bits in the endpoint register
         */
        void clearTxRxFlags();

        /**
         * Endpoint number 0..7
         */
        const uint8_t number;

        /**
         * Endpoint specific register
         */
        Register32* EPnR = (Register32*)(&USB_Registers::get()->EP0R) + number;

        /**
         * Buffer addresses and sizes
         */
        uint8_t bufferDescriptorAddress = number * 8;
        uint16_t txBufferAddress = 64 + number * 128;
        uint16_t txBufferSize = 64;
        uint16_t rxBufferAddress = 128 + number * 128;
        uint16_t rxBufferSize = 64;
};


}   // namespace mcu
