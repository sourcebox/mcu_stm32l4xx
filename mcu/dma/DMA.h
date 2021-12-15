/**
 * @file        DMA.h
 *
 * Driver for DMA controller on STM32L4xx
 *
 * @author:     Oliver Rockstedt <info@sourcebox.de>
 * @license     MIT
 */


#pragma once


// Local includes
#include "DMA_Base.h"
#include "DMA_Registers.h"
#include "DMA_Channel.h"

// System libraries
#include <cstdint>


namespace mcu {


class DMA : public DMA_Base
{
    public:
        /**
         * Return reference to peripheral
         *
         * @param id            Peripheral id
         * @return              Reference to peripheral
         */
        static DMA& get(Id id)
        {
            switch (id) {
                case Id::DMA1:
                    return dma1;
                case Id::DMA2:
                    return dma2;
            }

            return dma1;
        }

        DMA_Channel getChannel(ChannelId channelId)
        {
            return DMA_Channel(id, channelId);
        }

        /**
         * Init
         */
        void init();

        /**
         * Shutdown
         */
        void deinit();

        /**
         * Return id
         *
         * @return      Id constant
         */
        Id getId()
        {
            return id;
        }

    protected:
        /**
         * Private constructors because of singleton pattern, no copy allowed
         */
        DMA(Id id) : id(id) {}
        DMA(const DMA&) = delete;
        DMA& operator = (const DMA&) = delete;
        DMA& operator = (DMA&&) = delete;

        /**
          * Enable clock
          */
         void enableClock();

         /**
          * Disable clock
          */
         void disableClock();

        /**
         * Controller id
         */
        const Id id;

        /**
         * Singleton instances
         */
        static DMA dma1;
        static DMA dma2;
};


}   // namespace mcu
