/**
 * @file        USB.cpp
 *
 * Driver for USB peripheral on STM32L4xx
 *
 * @author:     Oliver Rockstedt <info@sourcebox.de>
 * @license     MIT
 */


// Corresponding header
#include "USB.h"

// Local includes
#include "USB_Registers.h"
#include "USB_SRAM.h"

// This component
#include "../gpio/Pin.h"
#include "../core/NVIC.h"
#include "../pwr/PWR_Registers.h"
#include "../rcc/RCC_Registers.h"
#include "../utility/bit_manipulation.h"
#include "../utility/time.h"

// System libraries
#include <cstring>


namespace mcu {


// ============================================================================
// Public members
// ============================================================================


void USB::init()
{
    enablePower();
    enableClock();

    status = Status::POWERED;

    USB_SRAM::clear();

    auto registers = USB_Registers::get();

    registers->CNTR = (1 << USB_Registers::CNTR::FRES);
    registers->CNTR = 0;
    registers->ISTR = 0;
    registers->BTABLE = 0;

    for (auto& endpoint : endpoints) {
        if (endpoint != nullptr) {
            endpoint->init();
        }
    }
}


void USB::init(Config& config)
{
    init();

    setResetCallback(config.resetCallback);
    setSuspendCallback(config.suspendCallback);
    setResumeCallback(config.resumeCallback);
    setDescriptorCallback(config.descriptorCallback);
}


void USB::deinit()
{
    disconnect();
    disableClock();
    disablePower();

    status = Status::DISABLED;
}


void USB::initPins()
{
    auto dmPin = Pin::get(Pin::PA11);
    dmPin.setPullMode(Pin::PullMode::NONE);
    dmPin.setMode(Pin::Mode::AF);
    dmPin.setAlternateFunction(Pin::AF::AF10);

    auto dpPin = Pin::get(Pin::PA12);
    dpPin.setPullMode(Pin::PullMode::NONE);
    dpPin.setMode(Pin::Mode::AF);
    dpPin.setAlternateFunction(Pin::AF::AF10);
}


void USB::deinitPins()
{
    auto dmPin = Pin::get(Pin::PA11);
    dmPin.setMode(Pin::Mode::INPUT);
    dmPin.setAlternateFunction(Pin::AF::AF0);

    auto dpPin = Pin::get(Pin::PA12);
    dpPin.setMode(Pin::Mode::INPUT);
    dpPin.setAlternateFunction(Pin::AF::AF0);
}


void USB::connect()
{
    enableTransceiver();
    enableInterrupt();
    initPins();
    setPullup(true);
}


void USB::disconnect()
{
    setPullup(false);
    deinitPins();
    disableInterrupt();
    disableTransceiver();
}


void USB::setEndpoint(int number, USB_Endpoint* endpoint)
{
    endpoints[number] = endpoint;
}


void USB::setResetCallback(CallbackFunc func)
{
    resetCallback = func;
}


void USB::setSuspendCallback(CallbackFunc func)
{
    suspendCallback = func;
}


void USB::setResumeCallback(CallbackFunc func)
{
    resumeCallback = func;
}


int USB::getIRQNumber()
{
    return IrqId::USBFS;
}


void USB::irq()
{
    auto registers = USB_Registers::get();

    auto istr = registers->ISTR;

    // Clear all bits at once as recommended in reference manual
    registers->ISTR = 0;

    if (istr & (1 << USB_Registers::ISTR::RESET)) {
        onReset();
        return;
    }

    if (istr & (1 << USB_Registers::ISTR::CTR)) {
        // Correct transfer
        auto endpointNo = bitsValue(istr, 4, USB_Registers::ISTR::EP_ID_0);
        auto endpoint = endpoints[endpointNo];

        if (endpoint != nullptr) {
            auto endpointRegisterValue = *endpoint->getRegister();

            endpoint->clearTxRxFlags();

            auto direction = (bool)bitValue(istr, USB_Registers::ISTR::DIR);

            if (direction && bitValue(endpointRegisterValue,
                                      USB_Registers::EPnR::CTR_RX)) {
                // OUT or SETUP transfer
                auto setup = (bool)bitValue(endpointRegisterValue,
                        USB_Registers::EPnR::SETUP);
                if (setup) {
                    endpoint->onSetupReceptionComplete();
                } else {
                    endpoint->onReceptionComplete();
                }
            }

            if (bitValue(endpointRegisterValue, USB_Registers::EPnR::CTR_TX)) {
                // IN transfer
                endpoint->onTransmissionComplete();
            }
        }
    }

    if (istr & (1 << USB_Registers::ISTR::SUSP)) {
        registers->CNTR = bitSet(registers->CNTR, USB_Registers::CNTR::FSUSP);

        preSuspendStatus = status;
        status = Status::SUSPENDED;

        if (suspendCallback != nullptr) {
            suspendCallback();
        }
    }

    if (istr & (1 << USB_Registers::ISTR::WKUP)) {
        registers->CNTR = bitReset(registers->CNTR, USB_Registers::CNTR::FSUSP);

        if (status == Status::SUSPENDED) {
            status = preSuspendStatus;

            if (resumeCallback != nullptr) {
                resumeCallback();
            }
        }
    }
}


// ============================================================================
// Protected members
// ============================================================================


USB::USB()
{
    for (auto& endpoint : endpoints) {
        endpoint = nullptr;
    }

    endpoints[0] = &controlEndpoint;
}


void USB::enableClock()
{
    auto rccRegisters = RCC_Registers::get();

    rccRegisters->CRRCR |= (1 << RCC_Registers::CRRCR::HSI48ON);

    while (!(rccRegisters->CRRCR & (1 << RCC_Registers::CRRCR::HSI48RDY))) {
        // Wait until HSI48 clock is stable
    }

    rccRegisters->APB1ENR1 |= (1 << RCC_Registers::APB1ENR1::USBFSEN);
}


void USB::disableClock()
{
    auto rccRegisters = RCC_Registers::get();

    rccRegisters->APB1ENR1 &= ~(1 << RCC_Registers::APB1ENR1::USBFSEN);
}


void USB::enablePower()
{
    auto pwrRegisters = PWR_Registers::get();

    pwrRegisters->CR2 |= (1 << PWR_Registers::CR2::USV);
}


void USB::disablePower()
{
    auto pwrRegisters = PWR_Registers::get();

    pwrRegisters->CR2 &= ~(1 << PWR_Registers::CR2::USV);
}


void USB::enableTransceiver()
{
    auto registers = USB_Registers::get();

    registers->CNTR &= ~(1 << USB_Registers::CNTR::PDWN);

    delayMicroseconds(TRANSCEIVER_STARTUP_DELAY);
}


void USB::disableTransceiver()
{
    auto registers = USB_Registers::get();

    registers->CNTR |= (1 << USB_Registers::CNTR::PDWN);
}


void USB::enableInterrupt()
{
    auto& nvic = NVIC::get();
    nvic.enableIrq(getIRQNumber());

    auto registers = USB_Registers::get();

    registers->CNTR |= (1 << USB_Registers::CNTR::RESETM);
    registers->CNTR |= (1 << USB_Registers::CNTR::CTRM);
    registers->CNTR |= (1 << USB_Registers::CNTR::SUSPM);
    registers->CNTR |= (1 << USB_Registers::CNTR::WKUPM);
}


void USB::disableInterrupt()
{
    auto& nvic = NVIC::get();
    nvic.disableIrq(getIRQNumber());

    auto registers = USB_Registers::get();

    registers->ISTR = 0;
}


void USB::setPullup(bool state)
{
    auto registers = USB_Registers::get();

    if (state) {
        registers->BCDR |= (1 << USB_Registers::BCDR::DPPU);
    } else {
        registers->BCDR &= ~(1 << USB_Registers::BCDR::DPPU);
    }
}


void USB::onReset()
{
    auto registers = USB_Registers::get();

    // Set address 0
    registers->DADDR = bitsReplace(registers->DADDR, 0, 7,
            USB_Registers::DADDR::ADD_0);
    registers->DADDR = bitSet(registers->DADDR, USB_Registers::DADDR::EF);

    if (resetCallback != nullptr) {
        resetCallback();
    }

    for (auto& endpoint : endpoints) {
        if (endpoint != nullptr) {
            endpoint->reset();
        }
    }

    status = Status::DEFAULT;
}


USB USB::instance;


}   // namespace mcu
