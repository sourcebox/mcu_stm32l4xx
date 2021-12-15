/**
 * @file        NVIC.cpp
 *
 * Driver for Nested Interrupt Vector Controller on Cortex-M4
 *
 * @author:     Oliver Rockstedt <info@sourcebox.de>
 * @license     MIT
 */


// Corresponding header
#include "NVIC.h"

// Local includes
#include "SCB_Registers.h"


namespace mcu {


// ============================================================================
// Public members
// ============================================================================


void NVIC::enableIrq(int irqNum)
{
    auto registers = NVIC_Registers::get();

    registers->ISER[irqNum >> 5] = 1 << (irqNum & 0x1F);
}


void NVIC::disableIrq(int irqNum)
{
    auto registers = NVIC_Registers::get();

    registers->ICER[irqNum >> 5] = 1 << (irqNum & 0x1F);
}


void NVIC::setPriority(int irqNum, int priority, int subPriority)
{
    auto encodedPriority = encodePriority(getPriorityGrouping(),
            priority, subPriority);

    if ((int32_t)(irqNum) < 0) {
        auto registers = SCB_Registers::get();
        registers->SHP[(irqNum & 0xF) - 4]
                 = (uint8_t)((encodedPriority << (8 - NVIC_PRIO_BITS)) & 0xFF);
    } else {
        auto registers = NVIC_Registers::get();
        registers->IP[irqNum]
                 = (uint8_t)((encodedPriority << (8 - NVIC_PRIO_BITS)) & 0xFF);
    }
}


void NVIC::setPriorityGrouping(PriorityGroup priorityGroup)
{
    uint32_t priorityGroupTmp = priorityGroup & 0x07;

    auto scbRegisters = SCB_Registers::get();

    static const uint32_t PRIGROUP_Msk = 7 << SCB_Registers::AIRCR::PRIGROUP;
    static const uint32_t VECTKEY_Msk  = (0xFFFF << SCB_Registers::AIRCR::VECTKEY);

    uint32_t value = scbRegisters->AIRCR;
    value &= ~(VECTKEY_Msk | PRIGROUP_Msk);
    value = value | (0x5FA << SCB_Registers::AIRCR::VECTKEY) | (priorityGroupTmp << 8);

    scbRegisters->AIRCR = value;
}


NVIC::PriorityGroup NVIC::getPriorityGrouping()
{
    static const uint32_t PRIGROUP_Msk = 7 << SCB_Registers::AIRCR::PRIGROUP;

    return (PriorityGroup)((SCB_Registers::get()->AIRCR & PRIGROUP_Msk)
            >> SCB_Registers::AIRCR::PRIGROUP);
}


// ============================================================================
// Protected members
// ============================================================================


uint32_t NVIC::encodePriority(PriorityGroup priorityGroup,
                        int preemptPriority, int subPriority)
{
    uint32_t priorityGroupTmp = priorityGroup & 0x07;

    uint32_t preemptPriorityBits = (7 - priorityGroupTmp) > NVIC_PRIO_BITS
            ? NVIC_PRIO_BITS : (uint32_t)(7 - priorityGroupTmp);
    uint32_t subPriorityBits = ((priorityGroupTmp + NVIC_PRIO_BITS) < 7)
            ? 0 : priorityGroupTmp - 7 + NVIC_PRIO_BITS;

    return (
         ((preemptPriority & ((1 << preemptPriorityBits) - 1)) << subPriorityBits)
         | ((subPriority & ((1 << subPriorityBits) - 1)))
    );
}


NVIC NVIC::instance;


}   // namespace mcu
