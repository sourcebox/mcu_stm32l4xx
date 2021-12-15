/**
 * @file        USB_SRAM.h
 *
 * Driver for USB SRAM on STM32L4xx
 *
 * @author:     Oliver Rockstedt <info@sourcebox.de>
 * @license     MIT
 */


#pragma once


// This component
#include "../core/mcu_base.h"
#include "../utility/register.h"

// System libraries
#include <cstdint>
#include <cstring>


namespace mcu {


class USB_SRAM
{
    public:
        struct Registers
        {
            struct Block
            {
                Register16 ADDRn_TX;    // Transmission buffer address n    Offset 0x00
                Register16 COUNTn_TX;   // Transmission byte count n        Offset 0x02
                Register16 ADDRn_RX;    // Reception buffer address n       Offset 0x04
                Register16 COUNTn_RX;   // Reception byte count n           Offset 0x08
            } __attribute__((packed));

            struct ADDRn_TX
            {
                static const uint32_t ADDRn_TX_1    = 1;
                static const uint32_t ADDRn_TX_2    = 2;
                static const uint32_t ADDRn_TX_3    = 3;
                static const uint32_t ADDRn_TX_4    = 4;
                static const uint32_t ADDRn_TX_5    = 5;
                static const uint32_t ADDRn_TX_6    = 6;
                static const uint32_t ADDRn_TX_7    = 7;
                static const uint32_t ADDRn_TX_8    = 8;
                static const uint32_t ADDRn_TX_9    = 9;
                static const uint32_t ADDRn_TX_10   = 10;
                static const uint32_t ADDRn_TX_11   = 11;
                static const uint32_t ADDRn_TX_12   = 12;
                static const uint32_t ADDRn_TX_13   = 13;
                static const uint32_t ADDRn_TX_14   = 14;
                static const uint32_t ADDRn_TX_15   = 15;
            };

            struct COUNTn_TX
            {
                static const uint32_t COUNTn_TX_0   = 0;
                static const uint32_t COUNTn_TX_1   = 1;
                static const uint32_t COUNTn_TX_2   = 2;
                static const uint32_t COUNTn_TX_3   = 3;
                static const uint32_t COUNTn_TX_4   = 4;
                static const uint32_t COUNTn_TX_5   = 5;
                static const uint32_t COUNTn_TX_6   = 6;
                static const uint32_t COUNTn_TX_7   = 7;
                static const uint32_t COUNTn_TX_8   = 8;
                static const uint32_t COUNTn_TX_9   = 9;
            };

            struct ADDRn_RX
            {
                static const uint32_t ADDRn_RX_1    = 1;
                static const uint32_t ADDRn_RX_2    = 2;
                static const uint32_t ADDRn_RX_3    = 3;
                static const uint32_t ADDRn_RX_4    = 4;
                static const uint32_t ADDRn_RX_5    = 5;
                static const uint32_t ADDRn_RX_6    = 6;
                static const uint32_t ADDRn_RX_7    = 7;
                static const uint32_t ADDRn_RX_8    = 8;
                static const uint32_t ADDRn_RX_9    = 9;
                static const uint32_t ADDRn_RX_10   = 10;
                static const uint32_t ADDRn_RX_11   = 11;
                static const uint32_t ADDRn_RX_12   = 12;
                static const uint32_t ADDRn_RX_13   = 13;
                static const uint32_t ADDRn_RX_14   = 14;
                static const uint32_t ADDRn_RX_15   = 15;
            };

            struct COUNTn_RX
            {
                static const uint32_t COUNTn_RX_0   = 0;
                static const uint32_t COUNTn_RX_1   = 1;
                static const uint32_t COUNTn_RX_2   = 2;
                static const uint32_t COUNTn_RX_3   = 3;
                static const uint32_t COUNTn_RX_4   = 4;
                static const uint32_t COUNTn_RX_5   = 5;
                static const uint32_t COUNTn_RX_6   = 6;
                static const uint32_t COUNTn_RX_7   = 7;
                static const uint32_t COUNTn_RX_8   = 8;
                static const uint32_t COUNTn_RX_9   = 9;
                static const uint32_t NUM_BLOCK_0   = 10;
                static const uint32_t NUM_BLOCK_1   = 11;
                static const uint32_t NUM_BLOCK_2   = 12;
                static const uint32_t NUM_BLOCK_3   = 13;
                static const uint32_t NUM_BLOCK_4   = 14;
                static const uint32_t BL_SIZE       = 15;
            };
        };

        /**
         * Read data into buffer
         *
         * @param address   Relative start address inside block 0..SIZE-1
         * @param buffer    Buffer to be filled with data
         * @param size      Number of bytes to be read
         */
        static void read(uint32_t address, uint8_t buffer[], size_t size);

        /**
         * Read a single byte from memory
         *
         * @param address   Relative start address inside block 0..SIZE-1
         * @return          Read memory content
         */
        static uint8_t readByte(uint32_t address);

        /**
         * Read a single halfword from memory
         *
         * @param address   Relative start address inside block 0..SIZE-1
         * @return          Read memory content
         */
        static uint16_t readHalfword(uint32_t address);

        /**
         * Read a single word from memory
         *
         * @param address   Relative start address inside block 0..SIZE-1
         * @return          Read memory content
         */
        static uint32_t readWord(uint32_t address);

        /**
         * Write data from buffer
         *
         * @param address   Relative start address inside block 0..SIZE-1
         * @param buffer    Buffer containing data
         * @param size      Number of bytes to be written
         */
        static void write(uint32_t address, uint8_t buffer[], size_t size);

        /**
         * Write a single byte into memory
         *
         * @param address   Relative start address inside block 0..SIZE-1
         * @param value     Value to be written
         */
        static void writeByte(uint32_t address, uint8_t value);

        /**
         * Write a single halfword into memory
         *
         * @param address   Relative start address inside block 0..SIZE-1
         * @param value     Value to be written
         */
        static void writeHalfword(uint32_t address, uint16_t value);

        /**
         * Write a single word into memory
         *
         * @param address   Relative start address inside block 0..SIZE-1
         * @param value     Value to be written
         */
        static void writeWord(uint32_t address, uint32_t value);

        /**
         * Clear memory completely
         */
        static void clear();

    protected:
        static constexpr uint32_t BASE_ADDRESS = APB1_BASE_ADDRESS + 0x00006C00;
        static constexpr uint32_t SIZE = 1024;
};


}   // namespace mcu
