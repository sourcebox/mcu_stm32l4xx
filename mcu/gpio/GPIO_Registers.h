/**
 * @file        GPIO_Registers.h
 *
 * Register definitions for GPIO peripherals on STM32L4xx
 *
 * @author:     Oliver Rockstedt <info@sourcebox.de>
 * @license     MIT
 */


#pragma once

// Local includes
#include "GPIO_Base.h"

// This component
#include "../core/mcu_base.h"
#include "../utility/register.h"

// System libraries
#include <cstdint>


namespace mcu {


class GPIO_Registers : public GPIO_Base
{
    public:
        struct Block
        {
            Register32 MODER;       // Port mode register           Offset 0x00
            Register32 OTYPER;      // Port output type register    Offset 0x04
            Register32 OSPEEDR;     // Port output speed register   Offset 0x08
            Register32 PUPDR;       // Port pullup/pulldown reg     Offset 0x0C
            Register32 IDR;         // Port input data register     Offset 0x10
            Register32 ODR;         // Port output data register    Offset 0x14
            Register32 BSRR;        // Port bit set/reset register  Offset 0x18
            Register32 LCKR;        // Port configuration lock reg  Offset 0x1C
            Register32 AFRL;        // Port alternate func low reg  Offset 0x20
            Register32 AFRH;        // Port alternate func high reg Offset 0x24
            Register32 BRR;         // Port bit reset register      Offset 0x28
        } __attribute__((packed));

        /**
         * Return pointer to registers block
         *
         * @param id        Peripheral id
         * @return          Pointer to registers
         */
        static constexpr Block* get(PortId id)
        {
            switch (id) {
                case PortId::GPIOA:
                    return (Block*)GPIOA_BASE_ADDRESS;
                case PortId::GPIOB:
                    return (Block*)GPIOB_BASE_ADDRESS;
                case PortId::GPIOC:
                    return (Block*)GPIOC_BASE_ADDRESS;
                case PortId::GPIOD:
                    return (Block*)GPIOD_BASE_ADDRESS;
                case PortId::GPIOE:
                    return (Block*)GPIOE_BASE_ADDRESS;
                case PortId::GPIOH:
                    return (Block*)GPIOH_BASE_ADDRESS;
                case PortId::NONE:
                    return nullptr;
            }

            return nullptr;
        }

    protected:
        // Register block base addresses
        static const uint32_t GPIOA_BASE_ADDRESS = AHB2_BASE_ADDRESS + 0x00000000;
        static const uint32_t GPIOB_BASE_ADDRESS = AHB2_BASE_ADDRESS + 0x00000400;
        static const uint32_t GPIOC_BASE_ADDRESS = AHB2_BASE_ADDRESS + 0x00000800;
        static const uint32_t GPIOD_BASE_ADDRESS = AHB2_BASE_ADDRESS + 0x00000C00;
        static const uint32_t GPIOE_BASE_ADDRESS = AHB2_BASE_ADDRESS + 0x00001000;
        static const uint32_t GPIOH_BASE_ADDRESS = AHB2_BASE_ADDRESS + 0x00001C00;
};


}   // namespace mcu
