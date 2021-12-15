/**
 * @file        ADC.h
 *
 * Driver for ADC peripherals on STM32L4xx
 *
 * @author:     Oliver Rockstedt <info@sourcebox.de>
 * @license     MIT
 */


#pragma once


// Local includes
#include "ADC_Base.h"
#include "ADC_Registers.h"

// System libraries
#include <cstdint>


namespace mcu {


class ADC : public ADC_Base
{
    public:
        /**
         * Data resolution
         */
        enum class Resolution
        {
            BITS_12 = 0b00,
            BITS_10 = 0b01,
            BITS_8  = 0b10,
            BITS_6  = 0b11
        };

        /**
         * Data alignment
         */
        enum class Alignment
        {
            RIGHT,
            LEFT
        };

        /**
         * Oversampling ratio
         */
        enum class OversamplingRatio
        {
            TIMES_2     = 0b000,
            TIMES_4     = 0b001,
            TIMES_8     = 0b010,
            TIMES_16    = 0b011,
            TIMES_32    = 0b100,
            TIMES_64    = 0b101,
            TIMES_128   = 0b110,
            TIMES_256   = 0b111
        };

        /**
         * Sampling time
         */
        enum class SamplingTime
        {
            CYCLES_2_5      = 0b000,
            CYCLES_6_5      = 0b001,
            CYCLES_12_5     = 0b010,
            CYCLES_24_5     = 0b011,
            CYCLES_47_5     = 0b100,
            CYCLES_92_5     = 0b101,
            CYCLES_247_5    = 0b110,
            CYCLES_640_5    = 0b111
        };

        /**
         * Overrun mode
         */
        enum class OverrunMode
        {
            PRESERVE,
            OVERWRITE
        };

        /**
         * DMA mode
         */
        enum class DMAMode
        {
            ONE_SHOT,
            CIRCULAR
        };

        /**
         * External trigger polarity
         */
        enum class ExternalTriggerPolarity
        {
            DISABLED        = 0b00,
            RISING_EDGE     = 0b01,
            FALLING_EDGE    = 0b10,
            BOTH_EDGES      = 0b11
        };

        /**
         * External trigger source
         */
        enum class ExternalTriggerSource
        {
            EXT0_TIM1_CH1       = 0b0000,
            EXT1_TIM1_CH2       = 0b0001,
            EXT2_TIM1_CH3       = 0b0010,
            EXT3_TIM2_CH2       = 0b0011,
            EXT4_TIM3_TRGO      = 0b0100,
            EXT6_EXTI_LINE11    = 0b0110,
            EXT9_TIM1_TRGO      = 0b1001,
            EXT10_TIM1_TRGO2    = 0b1010,
            EXT11_TIM2_TRGO     = 0b1011,
            EXT13_TIM6_TRGO     = 0b1101,
            EXT14_TIM15_TRGO    = 0b1110
        };

        /**
         * Channels
         */
        enum class Channel
        {
            VREFINT     = 0,
            VREF_N      = 0,

            ADC1_IN1    = 1,
            ADC1_IN2    = 2,
            ADC1_IN3    = 3,
            ADC1_IN4    = 4,
            ADC1_IN5    = 5,
            ADC1_IN6    = 6,
            ADC1_IN7    = 7,
            ADC1_IN8    = 8,
            ADC1_IN9    = 9,
            ADC1_IN10   = 10,
            ADC1_IN11   = 11,
            ADC1_IN12   = 12,
            ADC1_IN13   = 13,
            ADC1_IN14   = 14,
            ADC1_IN15   = 15,
            ADC1_IN16   = 16,

            DAC_OUT1    = 17,
            TEMP_SENSOR = 17,
            DAC_OUT2    = 18,
            VBAT        = 18
        };

        /**
         * Callback function type
         */
        typedef void(*CallbackFunc)(ADC*, void*);

        /**
         * Configuration settings
         */
        struct Config
        {
            Resolution resolution = Resolution::BITS_12;
            Alignment alignment = Alignment::RIGHT;
            bool continuousMode = false;
            bool oversampling = false;
            OversamplingRatio oversamplingRatio = OversamplingRatio::TIMES_2;
            int oversamplingShift = 0;
            OverrunMode overrunMode = OverrunMode::PRESERVE;
            bool dmaEnable = false;
            DMAMode dmaMode = DMAMode::ONE_SHOT;
            ExternalTriggerPolarity externalTrigger =
                    ExternalTriggerPolarity::DISABLED;
            ExternalTriggerSource externalTriggerSource =
                    ExternalTriggerSource::EXT0_TIM1_CH1;
        };

        /**
         * Return reference to peripheral
         *
         * @param id            Peripheral id
         * @return              Reference to peripheral
         */
        static ADC& get(Id id)
        {
            switch (id) {
                case Id::ADC1:
                    return adc1;
                case Id::ADC2:
                    return adc2;
            }

            return adc1;
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
         * Perform calibration
         */
        void calibrate();

        /**
         * Start conversion
         */
        void startConversion();

        /**
         * Stop conversion
         */
        void stopConversion();

        /**
         * Return if a conversion is running
         *
         * @return              Current conversion state
         */
        bool isConverting();

        /**
         * Return if a conversion is complete
         *
         * @return              Conversion complete state
         */
        bool isConversionComplete();

        /**
         * Return if a sequence is complete
         *
         * @return              Sequence complete state
         */
        bool isSequenceComplete();

        /**
         * Read converted value
         *
         * @return              Last converted value
         */
        volatile uint16_t read();

        /**
         * Set data resolution
         *
         * @param resolution    Resolution according to enum class
         */
        void setResolution(Resolution resolution);

        /**
         * Set data alignment
         *
         * @param alignment     Alignment according to enum class
         */
        void setAlignment(Alignment alignment);

        /**
         * Enable/disable continuous mode
         *
         * @param state         Mode state
         */
        void setContinuousMode(bool state);

        /**
         * Enable/disable oversampling
         *
         * @param state         Oversampling state
         */
        void setOversampling(bool state);

        /**
         * Enable/disable oversampling with ratio an shift
         *
         * @param state         Oversampling state
         * @param ratio         Ratio according to enum class
         * @param bits          No of bits to shift 0..8
         */
        void setOversampling(bool state, OversamplingRatio ratio, int shift);

        /**
         * Set oversampling ratio
         *
         * @param ratio         Ratio according to enum class
         */
        void setOversamplingRatio(OversamplingRatio ratio);

        /**
         * Set oversampling shift
         *
         * @param bits          No of bits to shift 0..8
         */
        void setOversamplingShift(int bits);

        /**
         * Set overrun mode
         *
         * @param mode          Mode according to enum class
         */
        void setOverrunMode(OverrunMode mode);

        /**
         * Set sampling time for a channel
         *
         * @param channel       Channel according to enum class
         * @param samplingTime  Sampling time according to enum class
         */
        void setSamplingTime(Channel channel, SamplingTime samplingTime);

        /**
         * Set sequence
         *
         * @param channels      Array of channels
         * @param length        Length of channels array in elements
         */
        void setSequence(Channel channels[], int length);

        /**
         * Set sequence with common sampling time
         *
         * @param channels      Array of channels
         * @param length        Length of channels array in elements
         * @param samplingTime  Sampling time according to enum class
         */
        void setSequence(Channel channels[], int length, SamplingTime samplingTime);

        /**
         * Set sequence length
         *
         * @param length        Sequence length 1..16
         */
        void setSequenceLength(int length);

        /**
         * Set channel no for a sequence
         * @param sequenceIndex Sequence index 1..16
         * @param channel       Channel according to enum class
         */
        void setSequenceChannel(int sequenceIndex, Channel channel);

        /**
         * Enable/disable DMA
         *
         * @param state         DMA state
         */
        void setDMAEnable(bool state);

        /**
         * Set DMA mode
         *
         * @param mode          Mode according to enum class
         */
        void setDMAMode(DMAMode mode);

        /**
         * Set external trigger polarity and source
         *
         * @param polarity      Polarity according to enum class
         * @param source        Source according to enum class
         */
        void setExternalTrigger(ExternalTriggerPolarity polarity,
                                ExternalTriggerSource source);

        /**
         * Set conversion complete callback function
         *
         * @param func      Callback function or nullptr
         * @param context       Pointer to callback context
         */
        void setConversionCompleteCallback(CallbackFunc func,
                                           void* context= nullptr);

        /**
         * Set sequence complete callback function
         *
         * @param func      Callback function or nullptr
         * @param context       Pointer to callback context
         */
        void setSequenceCompleteCallback(CallbackFunc func,
                                         void* context= nullptr);

        /**
         * Enable peripheral
         */
        void enable();

        /**
         * Disable peripheral
         */
        void disable();

        /**
         * Return if peripheral is enabled
         *
         * @return          Enabled state
         */
        bool isEnabled();

        /**
         * Return if ADC is ready for conversion
         *
         * @return              Ready state
         */
        bool isReady();

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
         * Return pointer to registers
         *
         * @return      Pointer to registers struct
         */
        auto getRegisters()
        {
            return ADC_Registers::get(id);
        }

        /**
         * Process interrupt, called from IRQ handler
         */
        void irq();

    protected:
        static const int VREG_STARTUP_DELAY = 20;       // In µs

        /**
         * Private constructors because of singleton pattern, no copy allowed
         */
        ADC(Id id);
        ADC(const ADC&) = delete;
        ADC& operator = (const ADC&) = delete;
        ADC& operator = (ADC&&) = delete;

        /**
         * Enable clock
         */
        void enableClock();

        /**
         * Disable clock
         */
        void disableClock();

        /**
         * Enable voltage regulator
         */
        void enableVoltageRegulator();

        /**
         * Disable voltage regulator
         */
        void disableVoltageRegulator();

        /**
         * Peripheral id
         */
        const Id id;

        /**
         * Callback functions
         */
        CallbackFunc conversionCompleteCallback = nullptr;
        CallbackFunc sequenceCompleteCallback = nullptr;
        void* conversionCompleteCallbackContext = nullptr;
        void* sequenceCompleteCallbackContext = nullptr;

        /**
         * Singleton instances
         */
        static ADC adc1;
        static ADC adc2;
};


}   // namespace mcu
