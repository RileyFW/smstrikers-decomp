#ifndef _NLSLOTPOOL_H_
#define _NLSLOTPOOL_H_

#include "types.h"

typedef void* (*SlotPoolAllocatorFunc)(unsigned long size);
typedef void (*SlotPoolFreeFunc)(void* data);

// Forward declarations
struct SlotPoolBlock;
struct SlotPoolEntry;

template <typename T>
void nlListAddStart(T** head, T* newNode, T** prev)
{
    if ((prev != NULL) && ((T*)*head == NULL))
    {
        *prev = newNode;
    }
    *(T**)newNode = *head;
    *head = newNode;
}

class SlotPoolBase
{
public:
    SlotPoolBase();
    ~SlotPoolBase();

    static void BaseAddNewBlock(SlotPoolBase* pool, unsigned int entrySize);
    static void BaseFreeBlocks(SlotPoolBase* pool, unsigned int entrySize);

    /* 0x00 */ u32 m_Initial;              // Secondary slot count
    /* 0x04 */ u32 m_Delta;                // Primary slot count
    /* 0x08 */ SlotPoolBlock* m_BlockList; // Head of block list
    /* 0x0C */ SlotPoolEntry* m_FreeList;  // Head of entry list
    /* 0x10 */ SlotPoolAllocatorFunc m_AllocFn;
    /* 0x14 */ SlotPoolFreeFunc m_FreeFn;
}; // total size: 0x18

struct SlotPoolBlock
{
    SlotPoolBlock* m_next; // Pointer for linked list functionality
};

struct SlotPoolEntry
{
    SlotPoolEntry* m_next; // Pointer for linked list functionality
};

static void DefaultSlotPoolFree(void*);
static void* DefaultSlotPoolAllocator(unsigned long);

template <typename T>
class BasicSlotPool : public SlotPoolBase
{
public:
    BasicSlotPool()
        : SlotPoolBase()
    {
        this->m_Initial = 0x400;
        BaseAddNewBlock(this, sizeof(T));
        this->m_Delta = 0x80;
    }
    BasicSlotPool(const int initial, const int delta)
        : SlotPoolBase()
    {
        this->m_Initial = initial;
        BaseAddNewBlock(this, sizeof(T));
        this->m_Delta = delta;
    }

    ~BasicSlotPool()
    {
        BaseFreeBlocks(this, sizeof(T));
    };
}; // total size: 0x18

template <typename T>
class SlotPool : public BasicSlotPool<T>
{
public:
    // SlotPool()
    //     : BasicSlotPool<T>(0x400, 0x80)
    // {
    // }
}; // total size: 0x18

#endif // _NLSLOTPOOL_H_
