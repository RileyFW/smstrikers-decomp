#ifndef _NLSTATICSORTEDSLOT_H_
#define _NLSTATICSORTEDSLOT_H_

#include "NL/nlSlotPool.h"

template <typename T, int N>
class nlStaticSortedSlot : public BasicSlotPool<T>
{
public:
    nlStaticSortedSlot()
    {
        SlotPoolBase::BaseAddNewBlock(&this->m_Allocator, sizeof(T));
    }
}; // total size: 0x18

#endif // _NLSTATICSORTEDSLOT_H_
