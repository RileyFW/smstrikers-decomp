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
        // this->m_Allocator.m_BlockList = nullptr;
        // this->m_Allocator.m_FreeList = nullptr;
        // this->m_Allocator.m_AllocFn = nullptr;
        // this->m_Allocator.m_FreeFn = nullptr;
        // this->m_Allocator.m_Initial = 0;
        // this->m_Allocator.m_Delta = 0;
        SlotPoolBase::BaseAddNewBlock(&this->m_Allocator, sizeof(T));
    }

    ~nlDLListSlotPool()
    {
        SlotPoolBase::BaseFreeBlocks(&this->m_Allocator, sizeof(T));
    }
    // total size: 0x1C
};

#endif // _NLDLLISTSLOTPOOL_H_
