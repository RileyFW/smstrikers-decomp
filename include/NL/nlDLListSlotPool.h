#ifndef _NLDLLISTSLOTPOOL_H_
#define _NLDLLISTSLOTPOOL_H_

#include "NL/nlDLListContainer.h"
#include "NL/nlSlotPool.h"

template <typename T>
class nlDLListSlotPool : public DLListContainerBase<T, BasicSlotPool<DLListEntry<T> > >
{
public:
    nlDLListSlotPool()
    {
        SlotPoolBase::BaseAddNewBlock(&this->m_Allocator, sizeof(T));
    }

    ~nlDLListSlotPool()
    {
        SlotPoolBase::BaseFreeBlocks(&this->m_Allocator, sizeof(T));
    }
}; // total size: 0x1C

#endif // _NLDLLISTSLOTPOOL_H_
