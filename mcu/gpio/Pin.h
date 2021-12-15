/**
 * @file        Pin.h
 *
 * Pin configuration and manipulation for STM32L4xx
 *
 * @author      Oliver Rockstedt <info@sourcebox.de>
 * @license     MIT
 */


#pragma once

// Local includes
#include "GPIO_Base.h"
#include "GPIO_Registers.h"
#include "Port.h"

// This component
#include "../core/mcu_base.h"
#include "../utility/bit_manipulation.h"

// System libraries
#include <cstdlib>


namespace mcu {


class Pin : public GPIO_Base
{
    public:
        enum Id
        {
            // GPIOA
            PA0, PA1, PA2, PA3, PA4, PA5, PA6, PA7,
            PA8, PA9, PA10, PA11, PA12, PA13, PA14, PA15,

            // GPIOB
            PB0, PB1, PB2, PB3, PB4, PB5, PB6, PB7,
            PB8, PB9, PB10, PB11, PB12, PB13, PB14, PB15,

            // GPIOC
            PC0, PC1, PC2, PC3, PC4, PC5, PC6, PC7,
            PC8, PC9, PC10, PC11, PC12, PC13, PC14, PC15,

            // GPIOD
            PD0, PD1, PD2, PD3, PD4, PD5, PD6, PD7,
            PD8, PD9, PD10, PD11, PD12, PD13, PD14, PD15,

            // GPIOE
            PE0, PE1, PE2, PE3, PE4, PE5, PE6, PE7,
            PE8, PE9, PE10, PE11, PE12, PE13, PE14, PE15,

            // GPIOH
            PH0, PH1, PH3,

            // Special id for no pin
            NONE = -1
        };

        enum class Mode
        {
            INPUT       = 0b00,
            OUTPUT      = 0b01,
            AF          = 0b10,
            ANALOG      = 0b11
        };

        enum class OutputType
        {
            PUSH_PULL   = 0b00,
            OPEN_DRAIN  = 0b01
        };

        enum class OutputSpeed
        {
            LOW         = 0b00,
            MEDIUM      = 0b01,
            HIGH        = 0b10,
            VERY_HIGH   = 0b11
        };

        enum class PullMode
        {
            NONE        = 0b00,
            PULLUP      = 0b01,
            PULLDOWN    = 0b10
        };

        enum class AF
        {
            AF0, AF1, AF2, AF3, AF4, AF5, AF6, AF7,
            AF8, AF9, AF10, AF11, AF12, AF13, AF14, AF15
        };

        /**
         * Return peripheral
         *
         * @param id            Peripheral id
         * @return              Peripheral object
         */
        static Pin get(Id id)
        {
            return Pin(id);
        }

        /**
         * Set mode
         *
         * @param   mode            Mode corresponding to enum
         */
        void setMode(Mode mode)
        {
            if (id == Id::NONE) {
                return;
            }

            registers->MODER = bitsReplace(registers->MODER,
                    (int)mode, 2, pinNo * 2);
        }

        /**
         * Set output type
         *
         * @param   outputType      Output type corresponding to enum
         */
        void setOutputType(OutputType outputType)
        {
            if (id == Id::NONE) {
                return;
            }

            registers->OTYPER = bitsReplace(registers->OTYPER,
                    (int)outputType, 1, pinNo);
        }

        /**
         * Set output speed
         *
         * @param   outputSpeed     Output speed corresponding to enum
         */
        void setOutputSpeed(OutputSpeed outputSpeed)
        {
            if (id == Id::NONE) {
                return;
            }

            registers->OSPEEDR = bitsReplace(registers->OSPEEDR,
                    (int)outputSpeed, 2, pinNo * 2);
        }

        /**
         * Set pullup/pulldown mode
         *
         * @param   pullMode        Mode corresponding to enum
         */
        void setPullMode(PullMode pullMode)
        {
            if (id == Id::NONE) {
                return;
            }

            registers->PUPDR = bitsReplace(registers->PUPDR,
                    (int)pullMode, 2, pinNo * 2);
        }

        /**
         * Set alternate function
         *
         * @param   af              Alternate function corresponding to enum
         */
        void setAlternateFunction(AF af)
        {
            if (id == Id::NONE) {
                return;
            }

            if (pinNo < 8) {
                registers->AFRL = bitsReplace(registers->AFRL,
                        (int)af, 4, pinNo * 4);
            } else {
                registers->AFRH = bitsReplace(registers->AFRH,
                        (int)af, 4, pinNo * 4 % 32);
            }
        }

        /**
         * Return pin state
         *
         * @return                  Pin state
         */
        bool read()
        {
            return (registers->IDR & (1 << pinNo)) != 0;
        }

        /**
         * Set pin state
         *
         * @param   state           Pin state
         */
        void write(bool state)
        {
            if (state) {
                high();
            } else {
                low();
            }
        }

        /**
         * Set pin state H
         */
        void high()
        {
            registers->BSRR = (1 << pinNo);
        }

        /**
         * Set pin state L
         */
        void low()
        {
            registers->BRR = (1 << pinNo);
        }

        /**
         * Toggle pin state
         */
        void toggle()
        {
            write(!read());
        }

        /**
         * Return id
         *
         * @return      Id constant
         */
        Id getId()
        {
            return id;
        }

        /**
         * Return port id
         *
         * @param pinId             Pin id
         * @return                  Port id
         */
        static constexpr PortId getPortId(Id pinId)
        {
            if (pinId >= Id::PA0 && pinId <= Id::PA15) {
                return PortId::GPIOA;
            } else if (pinId >= Id::PB0 && pinId <= Id::PB15) {
                return PortId::GPIOB;
            } else if (pinId >= Id::PC0 && pinId <= Id::PC15) {
                return PortId::GPIOC;
            } else if (pinId >= Id::PD0 && pinId <= Id::PD15) {
                return PortId::GPIOD;
            } else if (pinId >= Id::PE0 && pinId <= Id::PE15) {
                return PortId::GPIOE;
            } else if (pinId >= Id::PH0 && pinId <= Id::PH3) {
                return PortId::GPIOH;
            } else {
                return PortId::NONE;
            }
        }

        /**
         * Return pin no
         *
         * @param pinId             Pin id
         * @return                  Pin no 0..15
         */
        static constexpr uint8_t getPinNo(Id pinId)
        {
            if (pinId >= Id::PA0 && pinId <= Id::PA15) {
                return pinId - Id::PA0;
            } else if (pinId >= Id::PB0 && pinId <= Id::PB15) {
                return pinId - Id::PB0;
            } else if (pinId >= Id::PC0 && pinId <= Id::PC15) {
                return pinId - Id::PC0;
            } else if (pinId >= Id::PD0 && pinId <= Id::PD15) {
                return pinId - Id::PD0;
            } else if (pinId >= Id::PE0 && pinId <= Id::PE15) {
                return pinId - Id::PE0;
            } else if (pinId >= Id::PH0 && pinId <= Id::PH1) {
                return pinId - Id::PH0;
            } else if (pinId == Id::PH3) {
                return pinId - Id::PH0 + 1;
            } else {
                return -1;          // No pin
            }
        }

    protected:
        /**
         * Constructor
         *
         * @param   id              Pin id corresponding to enum
         */
        Pin(Id id)
            : id(id)
        {
            auto portId = getPortId(id);
            registers = GPIO_Registers::get(portId);
        }

        /**
         * Private constructors because of singleton pattern, no copy allowed
         */
//        Pin(const Pin&) = delete;
//        Pin& operator = (const Pin&) = delete;
//        Pin& operator = (Pin&&) = delete;

        /**
         * Pin id
         */
        Id id;

        /**
         * Pin number
         */
        uint8_t pinNo = getPinNo(id);

        /**
         * Pointer to port registers
         */
        GPIO_Registers::Block* registers;
};


} // namespace mcu
