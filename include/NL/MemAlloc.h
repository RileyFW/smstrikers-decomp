#ifndef _MEMALLOC_H_
#define _MEMALLOC_H_

#include "types.h"
#include "NL/nlDLRing.h"

// void nlDLRingGetEnd<FreeBlockList>(FreeBlockList*);
// void nlDLRingGetStart<FreeBlockList>(FreeBlockList*);
// void nlDLRingRemove<FreeBlockList>(FreeBlockList**, FreeBlockList*);
// void nlDLRingAddStart<FreeBlockList>(FreeBlockList**, FreeBlockList*);
// void nlDLRingInsert<FreeBlockList>(FreeBlockList**, FreeBlockList*, FreeBlockList*);

struct FreeBlockList
{
    /* 0x0 */ FreeBlockList* m_next;
    /* 0x4 */ FreeBlockList* m_prev;
    /* 0x8 */ u32 m_unk_0x08;
};

class MemoryAllocator
{
public:
    unsigned int LargestFreeBlock();
    unsigned int TotalFreeMemory();
    void Initialize(void*, unsigned int);
    void* Allocate(unsigned long, unsigned int, bool);
    void Free(void*);

    /* 0x0 */ FreeBlockList* m_free_block_list;
};

extern MemoryAllocator StandardAllocator;
extern MemoryAllocator VirtualAllocator;

class LargestFreeBlockCallback
{
public:
    void Callback(FreeBlockList*);

    /* 0x0 */ u32 m_unk_0x00;
};

class TotalFreeMemCallback
{
public:
    void Callback(FreeBlockList*);

    /* 0x0 */ u32 m_unk_0x00;
};

// Template function declaration for nlWalkDLRing
template <typename T, typename CallbackType>
void nlWalkDLRing(T* head, CallbackType* callback, void (CallbackType::*callbackFunc)(T*));

// class nlWalkDLRing<FreeBlockList, LargestFreeBlockCallback>(FreeBlockList*, LargestFreeBlockCallback*, void (LargestFreeBlockCallback
// {
// public:
//     void *)(FreeBlockList*));
// };

// class nlWalkDLRing<FreeBlockList, TotalFreeMemCallback>(FreeBlockList*, TotalFreeMemCallback*, void (TotalFreeMemCallback
// {
// public:
//     void *)(FreeBlockList*));
// };

// class nlWalkRing<FreeBlockList, TotalFreeMemCallback>(FreeBlockList*, TotalFreeMemCallback*, void (TotalFreeMemCallback
// {
// public:
//     void *)(FreeBlockList*));
// };

// class nlWalkRing<FreeBlockList, LargestFreeBlockCallback>(FreeBlockList*, LargestFreeBlockCallback*, void (LargestFreeBlockCallback
// {
// public:
//     void *)(FreeBlockList*));
// };

#endif // _MEMALLOC_H_
