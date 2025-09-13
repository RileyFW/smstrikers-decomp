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
    static void BaseAddNewBlock(SlotPoolBase*, unsigned int);
    static void BaseFreeBlocks(SlotPoolBase*, unsigned int);
    ~SlotPoolBase();
    SlotPoolBase();

    /* 0x00 */ u32 m_unk_0x00;            // Secondary slot count
    /* 0x04 */ u32 m_unk_0x04;            // Primary slot count
    /* 0x08 */ SlotPoolBlock* m_unk_0x08; // Head of block list
    /* 0x0C */ SlotPoolEntry* m_unk_0x0C; // Head of entry list
    /* 0x10 */ SlotPoolAllocatorFunc m_slotPoolAllocator;
    /* 0x14 */ SlotPoolFreeFunc m_slotPoolFree;
};

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
    // total size: 0x18
};

#endif // _NLSLOTPOOL_H_
