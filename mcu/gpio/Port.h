/**
 * @file        Port.h
 *
 * GPIO port functions for STM32L4xx
 *
 * @author      Oliver Rockstedt <info@sourcebox.de>
 * @license     MIT
 */


#pragma once


// Local includes
#include "GPIO_Base.h"
#include "GPIO_Registers.h"

// This component
#include "../rcc/RCC_Registers.h"


namespace mcu {


class Port : public GPIO_Base
{
    public:
        /**
         * Return peripheral
         *
         * @param id            Peripheral id
         * @return              Peripheral object
         */
        static Port get(PortId id)
        {
            return Port(id);
        }

        void enableClock()
        {
            auto rccRegisters = RCC_Registers::get();

            switch (id) {
                case PortId::GPIOA:
                    rccRegisters->AHB2ENR |= (1 << RCC_Registers::AHB2ENR::GPIOAEN);
                    break;
                case PortId::GPIOB:
                    rccRegisters->AHB2ENR |= (1 << RCC_Registers::AHB2ENR::GPIOBEN);
                    break;
                case PortId::GPIOC:
                    rccRegisters->AHB2ENR |= (1 << RCC_Registers::AHB2ENR::GPIOCEN);
                    rccRegisters->APB1ENR1 |= (1 << mcu::RCC_Registers::APB1ENR1::PWREN);
                    break;
                case PortId::GPIOD:
                    rccRegisters->AHB2ENR |= (1 << RCC_Registers::AHB2ENR::GPIODEN);
                    break;
                case PortId::GPIOE:
                    rccRegisters->AHB2ENR |= (1 << RCC_Registers::AHB2ENR::GPIOEEN);
                    break;
                case PortId::GPIOH:
                    rccRegisters->AHB2ENR |= (1 << RCC_Registers::AHB2ENR::GPIOHEN);
                    break;
                default:
                    break;
            }
        }

        /**
         * Return id
         *
         * @return      Id constant
         */
        PortId getId()
        {
            return id;
        }

    protected:
        /**
         * Private constructors because of singleton pattern, no copy allowed
         */
        Port(PortId id) : id(id) {}
        Port(const Port&) = delete;
        Port& operator = (const Port&) = delete;
        Port& operator = (Port&&) = delete;

        /**
         * Port id
         */
        const PortId id;
};


}   // namespace mcu
