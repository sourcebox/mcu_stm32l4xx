/**
 * @file        NVIC.h
 *
 * Driver for Nested Interrupt Vector Controller on Cortex-M4
 *
 * @author:     Oliver Rockstedt <info@sourcebox.de>
 * @license     MIT
 */


#pragma once


// Local includes
#include "NVIC_Registers.h"


namespace mcu {


class NVIC
{
    public:
        /**
         * Return reference to peripheral
         *
         * @return              Reference to peripheral
         */
        static NVIC& get()
        {
            return instance;
        }

        /**
         * Enable interrupt
         *
         * @param   irqNum          IRQ number
         */
        void enableIrq(int irqNum);

        /**
         * Disable interrupt
         *
         * @param   irqNum          IRQ number
         */
        void disableIrq(int irqNum);

        /**
         * Set interrupt priority
         *
         * @param   irqNum          IRQ number
         * @param   priority        Priority
         * @param   subPriority     Sub priority
         */
        void setPriority(int irqNum, int priority, int subPriority=0);

        enum PriorityGroup
        {
            PRIORITY_GROUP_0 = 7,
            PRIORITY_GROUP_1 = 6,
            PRIORITY_GROUP_2 = 5,
            PRIORITY_GROUP_3 = 4,
            PRIORITY_GROUP_4 = 3
        };

        /**
         * Set the priority grouping
         *
         * @param priorityGroup     Grouping value
         */
        void setPriorityGrouping(PriorityGroup priorityGroup);

        /**
         * Return the priority grouping
         *
         * @return                  Priority grouping
         */
        PriorityGroup getPriorityGrouping();

    protected:
        /**
         * Private constructors because of singleton pattern, no copy allowed
         */
        NVIC() {}
        NVIC(const NVIC&) = delete;
        NVIC& operator = (const NVIC&) = delete;
        NVIC& operator = (NVIC&&) = delete;

        /**
         * Encode priority
         *
         * @param priorityGroup     Priority group
         * @param preemptPriority   Preemptive priority
         * @param subPriority       Subpriority value
         * @return                  Encoded priority
         */
        uint32_t encodePriority(PriorityGroup priorityGroup,
                                int preemptPriority, int subPriority);

        /**
         * Singleton instance
         */
        static NVIC instance;
};


}   // namespace mcu
