/**
 * @file        ADCCommon.h
 *
 * Driver for common ADC configuration on STM32L4xx
 *
 * @author:     Oliver Rockstedt <info@sourcebox.de>
 * @license     MIT
 */


#pragma once


// Local includes
#include "ADC_Registers.h"

// System libraries
#include <cstdint>


namespace mcu {


class ADCCommon
{
    public:
        enum class ClockPrescaler
        {
            DIV_1   = 0b0000,
            DIV_2   = 0b0001,
            DIV_4   = 0b0010,
            DIV_6   = 0b0011,
            DIV_8   = 0b0100,
            DIV_10  = 0b0101,
            DIV_12  = 0b0110,
            DIV_16  = 0b0111,
            DIV_32  = 0b1000,
            DIV_64  = 0b1001,
            DIV_128 = 0b1010,
            DIV_256 = 0b1011
        };

        enum class Channel17Select
        {
            DAC_OUT1,
            TEMP_SENSOR
        };

        enum class Channel18Select
        {
            DAC_OUT2,
            VBAT
        };

        /**
         * Set clock prescaler
         *
         * @param prescaler     Prescaler according to enum class
         */
        void setClockPrescaler(ClockPrescaler prescaler);

        /**
         * Select channel 17 input
         *
         * @param selection     Selection according to enum
         */
        void selectChannel17(Channel17Select selection);

        /**
         * Select channel 18 input
         *
         * @param selection     Selection according to enum
         */
        void selectChannel18(Channel18Select selection);

    protected:
        /**
         * Pointer to common registers
         */
        ADC_CommonRegisters::Block* registers = ADC_CommonRegisters::get();
};


}   // namespace mcu
