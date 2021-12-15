/**
 * @file        ADC.cpp
 *
 * Driver for ADC peripherals on STM32L4xx
 *
 * @author:     Oliver Rockstedt <info@sourcebox.de>
 * @license     MIT
 */


// Corresponding header
#include "ADC.h"

// This component
#include "../core/NVIC.h"
#include "../rcc/RCC_Registers.h"
#include "../utility/bit_manipulation.h"
#include "../utility/time.h"


namespace mcu {


// ============================================================================
// Public members
// ============================================================================


void ADC::init()
{
    enableClock();
    enableVoltageRegulator();
    calibrate();
    enable();
}


void ADC::init(Config& config)
{
    enableClock();
    enableVoltageRegulator();

    setResolution(config.resolution);
    setAlignment(config.alignment);
    setContinuousMode(config.continuousMode);
    setOversampling(config.oversampling);
    setOversamplingRatio(config.oversamplingRatio);
    setOverrunMode(config.overrunMode);
    setDMAEnable(config.dmaEnable);
    setDMAMode(config.dmaMode);

    calibrate();
    enable();
};


void ADC::deinit()
{
    disable();
    disableVoltageRegulator();
    disableClock();
}


void ADC::calibrate()
{
    auto registers = getRegisters();

    registers->CR = bitSet(registers->CR, ADC_Registers::CR::ADCAL);

    while (bitValue(registers->CR, ADC_Registers::CR::ADCAL)) {
        // Wait until calibration completed
    }
}


void ADC::startConversion()
{
    if (!isEnabled()) {
        enable();
    }

    auto registers = getRegisters();
    registers->CR = bitSet(registers->CR, ADC_Registers::CR::ADSTART);
}


void ADC::stopConversion()
{
    if (!isConverting()) {
        return;
    }

    auto registers = getRegisters();
    registers->CR = bitSet(registers->CR, ADC_Registers::CR::ADSTP);

    while (bitValue(registers->CR, ADC_Registers::CR::ADSTP)) {
        // Wait until stopped
    }
}


bool ADC::isConverting()
{
    auto registers = getRegisters();

    return bitValue(registers->CR, ADC_Registers::CR::ADSTART);
}


bool ADC::isConversionComplete()
{
    auto registers = getRegisters();

    return bitValue(registers->ISR, ADC_Registers::ISR::EOC);
}


bool ADC::isSequenceComplete()
{
    auto registers = getRegisters();

    return bitValue(registers->ISR, ADC_Registers::ISR::EOS);
}


volatile uint16_t ADC::read()
{
    auto registers = getRegisters();

    return registers->DR;
}


void ADC::setResolution(Resolution resolution)
{
    auto registers = getRegisters();

    registers->CFGR = bitsReplace(registers->CFGR, (int)resolution,
            2, ADC_Registers::CFGR::RES_0);
}


void ADC::setAlignment(Alignment alignment)
{
    auto registers = getRegisters();

    if (alignment == Alignment::LEFT) {
        registers->CFGR = bitSet(registers->CFGR, ADC_Registers::CFGR::ALIGN);
    } else {
        registers->CFGR = bitReset(registers->CFGR, ADC_Registers::CFGR::ALIGN);
    }
}


void ADC::setContinuousMode(bool state)
{
    auto registers = getRegisters();

    if (state) {
        registers->CFGR = bitSet(registers->CFGR, ADC_Registers::CFGR::CONT);
    } else {
        registers->CFGR = bitReset(registers->CFGR, ADC_Registers::CFGR::CONT);
    }
}


void ADC::setOversampling(bool state)
{
    auto registers = getRegisters();

    if (state) {
        registers->CFGR2 = bitSet(registers->CFGR2, ADC_Registers::CFGR2::ROVSE);
    } else {
        registers->CFGR2 = bitReset(registers->CFGR2, ADC_Registers::CFGR2::ROVSE);
    }
}


void ADC::setOversampling(bool state, OversamplingRatio ratio, int shift)
{
    setOversampling(state);
    setOversamplingRatio(ratio);
    setOversamplingShift(shift);
}


void ADC::setOversamplingRatio(OversamplingRatio ratio)
{
    auto registers = getRegisters();

    registers->CFGR2 = bitsReplace(registers->CFGR2, (int)ratio,
            3, ADC_Registers::CFGR2::OVSR_0);
}


void ADC::setOversamplingShift(int bits)
{
    auto registers = getRegisters();

    registers->CFGR2 = bitsReplace(registers->CFGR2, bits,
            4, ADC_Registers::CFGR2::OVSS_0);
}


void ADC::setOverrunMode(OverrunMode mode)
{
    auto registers = getRegisters();

    if (mode == OverrunMode::OVERWRITE) {
        registers->CFGR = bitSet(registers->CFGR, ADC_Registers::CFGR::OVRMOD);
    } else {
        registers->CFGR = bitReset(registers->CFGR, ADC_Registers::CFGR::OVRMOD);
    }
}


void ADC::setSamplingTime(Channel channel, SamplingTime samplingTime)
{
    auto channelNo = (int)channel;

    auto registers = getRegisters();

    if (channelNo >= 0 && channelNo <= 9) {
        registers->SMPR1 = bitsReplace(registers->SMPR1, (int)samplingTime,
                3, channelNo * 3);
    } else if (channelNo >= 10 && channelNo <= 18) {
        registers->SMPR2 = bitsReplace(registers->SMPR2, (int)samplingTime,
                3, (channelNo - 10) * 3);
    }
}


void ADC::setSequence(Channel channels[], int length)
{
    for (auto i = 0; i < length; i++) {
        setSequenceChannel(i + 1, channels[i]);
    }

    setSequenceLength(length);
}


void ADC::setSequence(Channel channels[], int length, SamplingTime samplingTime)
{
    for (auto i = 0; i < length; i++) {
        auto channel = channels[i];
        setSequenceChannel(i + 1, channel);
        setSamplingTime(channel, samplingTime);
    }

    setSequenceLength(length);
}


void ADC::setSequenceLength(int length)
{
    auto registers = getRegisters();

    registers->SQR1 = bitsReplace(registers->SQR1, length - 1, 4,
            ADC_Registers::SQR1::L_0);
}


void ADC::setSequenceChannel(int sequenceIndex, Channel channel)
{
    auto registers = getRegisters();

    auto channelNo = (int)channel;

    if (sequenceIndex >= 1 && sequenceIndex <= 4) {
        auto offset = 6 + (sequenceIndex - 1) * 6;
        registers->SQR1 = bitsReplace(registers->SQR1, channelNo, 5, offset);
    } else if (sequenceIndex >= 5 && sequenceIndex <= 9) {
        auto offset = (sequenceIndex - 5) * 6;
        registers->SQR2 = bitsReplace(registers->SQR2, channelNo, 5, offset);
    } else if (sequenceIndex >= 10 && sequenceIndex <= 14) {
        auto offset = (sequenceIndex - 10) * 6;
        registers->SQR3 = bitsReplace(registers->SQR3, channelNo, 5, offset);
    } else if (sequenceIndex >= 15 && sequenceIndex <= 16) {
        auto offset = (sequenceIndex - 15) * 6;
        registers->SQR4 = bitsReplace(registers->SQR4, channelNo, 5, offset);
    }
}


void ADC::setDMAEnable(bool state)
{
    auto registers = getRegisters();

    if (state) {
        registers->CFGR = bitSet(registers->CFGR, ADC_Registers::CFGR::DMAEN);
    } else {
        registers->CFGR = bitReset(registers->CFGR, ADC_Registers::CFGR::DMAEN);
    }
}


void ADC::setDMAMode(DMAMode mode)
{
    auto registers = getRegisters();

    if (mode == DMAMode::CIRCULAR) {
        registers->CFGR = bitSet(registers->CFGR, ADC_Registers::CFGR::DMACFG);
    } else {
        registers->CFGR = bitReset(registers->CFGR, ADC_Registers::CFGR::DMACFG);
    }
}


void ADC::setExternalTrigger(ExternalTriggerPolarity polarity,
                             ExternalTriggerSource source)
{
    auto registers = getRegisters();

    registers->CFGR = bitsReplace(registers->CFGR, (int)polarity, 2,
            ADC_Registers::CFGR::EXTEN_0);
    registers->CFGR = bitsReplace(registers->CFGR, (int)source, 4,
            ADC_Registers::CFGR::EXTSEL_0);
}


void ADC::setConversionCompleteCallback(CallbackFunc func, void* context)
{
    conversionCompleteCallback = func;
    conversionCompleteCallbackContext = context;

    auto& nvic = NVIC::get();
    auto irqNum = getIRQNumber(id);

    auto registers = getRegisters();

    if (func != nullptr) {
        registers->IER = bitSet(registers->IER, ADC_Registers::IER::EOCIE);
        nvic.enableIrq(irqNum);
    } else {
        registers->IER = bitReset(registers->IER, ADC_Registers::IER::EOCIE);
    }
}


void ADC::setSequenceCompleteCallback(CallbackFunc func, void* context)
{
    sequenceCompleteCallback = func;
    sequenceCompleteCallbackContext = context;

    auto& nvic = NVIC::get();
    auto irqNum = getIRQNumber(id);

    auto registers = getRegisters();

    if (func != nullptr) {
        registers->IER = bitSet(registers->IER, ADC_Registers::IER::EOSIE);
        nvic.enableIrq(irqNum);
    } else {
        registers->IER = bitReset(registers->IER, ADC_Registers::IER::EOSIE);
    }
}


void ADC::enable()
{
    if (isEnabled()) {
        return;
    }

    auto registers = getRegisters();

    registers->ISR = bitSet(registers->ISR, ADC_Registers::ISR::ADRDY);
    registers->CR = bitSet(registers->CR, ADC_Registers::CR::ADEN);

    while (!isReady()) {
        // Wait until ready
    }
}


void ADC::disable()
{
    if (!isEnabled()) {
        return;
    }

    auto registers = getRegisters();

    while (isConverting() || bitValue(registers->CR, ADC_Registers::CR::JADSTART)) {
        // Wait until all conversions are completed
    }

    registers->CR = bitSet(registers->CR, ADC_Registers::CR::ADDIS);

    while (bitValue(registers->CR, ADC_Registers::CR::ADDIS)) {
        // Wait until disabled
    }
}


bool ADC::isEnabled()
{
    auto registers = getRegisters();

    return bitValue(registers->CR, ADC_Registers::CR::ADEN);
}


bool ADC::isReady()
{
    auto registers = getRegisters();

    return bitValue(registers->ISR, ADC_Registers::ISR::ADRDY);
}


void ADC::irq()
{
    auto conversionComplete = isConversionComplete();
    auto sequenceComplete = isSequenceComplete();

    auto registers = getRegisters();

    if (conversionComplete) {
        registers->ISR = bitSet(registers->ISR, ADC_Registers::ISR::EOC);

        if (conversionCompleteCallback != nullptr) {
            conversionCompleteCallback(this, conversionCompleteCallbackContext);
        }
    }

    if (sequenceComplete) {
        registers->ISR = bitSet(registers->ISR, ADC_Registers::ISR::EOS);

        if (sequenceCompleteCallback != nullptr) {
            sequenceCompleteCallback(this, sequenceCompleteCallbackContext);
        }
    }
}


// ============================================================================
// Protected members
// ============================================================================


ADC::ADC(Id id)
        : id(id)
{
}


void ADC::enableClock()
{
    auto rccRegisters = RCC_Registers::get();

    rccRegisters->AHB2ENR = bitSet(rccRegisters->AHB2ENR, RCC_Registers::AHB2ENR::ADCEN);
    rccRegisters->CCIPR = bitsReplace(rccRegisters->CCIPR, 0b11, 2,
            RCC_Registers::CCIPR::ADCSEL_0);
}


void ADC::disableClock()
{
    auto rccRegisters = RCC_Registers::get();

    rccRegisters->AHB2ENR = bitReset(rccRegisters->AHB2ENR, RCC_Registers::AHB2ENR::ADCEN);
}


void ADC::enableVoltageRegulator()
{
    auto registers = getRegisters();

    if (bitValue(registers->CR, ADC_Registers::CR::ADVREGEN)) {
        // Already enabled
        return;
    }

    // Disable deep power down
    registers->CR = bitReset(registers->CR, ADC_Registers::CR::DEEPPWD);

    registers->CR = bitSet(registers->CR, ADC_Registers::CR::ADVREGEN);

    delayMicroseconds(VREG_STARTUP_DELAY);
}


void ADC::disableVoltageRegulator()
{
    auto registers = getRegisters();

    registers->CR = bitReset(registers->CR, ADC_Registers::CR::ADVREGEN);
}


ADC ADC::adc1 = ADC(ADC::ADC1);
ADC ADC::adc2 = ADC(ADC::ADC2);


}   // namespace mcu
