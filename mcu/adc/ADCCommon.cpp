/**
 * @file        ADCCommon.cpp
 *
 * Driver for common ADC configuration on STM32L4xx
 *
 * @author:     Oliver Rockstedt <info@sourcebox.de>
 * @license     MIT
 */


// Corresponding header
#include "ADCCommon.h"

// This component
#include "../utility/bit_manipulation.h"


namespace mcu {


// ============================================================================
// Public members
// ============================================================================


void ADCCommon::setClockPrescaler(ClockPrescaler prescaler)
{
    registers->CCR = bitsReplace(registers->CCR, (int)prescaler, 4,
            ADC_CommonRegisters::CCR::PRESC_0);
}


void ADCCommon::selectChannel17(Channel17Select selection)
{
    if (selection == Channel17Select::TEMP_SENSOR) {
        registers->CCR = bitSet(registers->CCR, ADC_CommonRegisters::CCR::CH17SEL);
    } else {
        registers->CCR = bitReset(registers->CCR, ADC_CommonRegisters::CCR::CH17SEL);
    }
}


void ADCCommon::selectChannel18(Channel18Select selection)
{
    if (selection == Channel18Select::VBAT) {
        registers->CCR = bitSet(registers->CCR, ADC_CommonRegisters::CCR::CH18SEL);
    } else {
        registers->CCR = bitReset(registers->CCR, ADC_CommonRegisters::CCR::CH18SEL);
    }
}


// ============================================================================
// Protected members
// ============================================================================


}   // namespace mcu
