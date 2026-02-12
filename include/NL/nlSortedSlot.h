#ifndef _NLSORTEDSLOT_H_
#define _NLSORTEDSLOT_H_

#include "NL/nlArrayAllocator.h"

template <typename T>
struct EntryLookup
{
    /* 0x0 */ unsigned long Id;
    /* 0x4 */ T* pEntry;
}; // total size: 0x8

template <typename T>
class nlSortedSlot
{
public:
    virtual T* GetNewEntry() = 0;
    virtual void FreeEntry(T*) = 0;
    virtual void ExpandLookup() = 0;
    virtual void FreeLookup() = 0;

    /* 0x04 */ EntryLookup<T>* m_pEntryLookup;
    /* 0x08 */ unsigned long m_EntryCount;
    /* 0x0C */ unsigned long m_LookupAllocated;
}; // total size: 0x10

template <typename T, int N>
class nlStaticSortedSlot : public nlSortedSlot<T>
{
public:
    virtual T* GetNewEntry();
    virtual void FreeEntry(T*);
    virtual void ExpandLookup();
    virtual void FreeLookup();

    /* 0x10 */ unsigned char m_EntryData[sizeof(T) * N];
    /* 0x2C */ EntryLookup<T> m_LookupData[N];
    /* 0x64 */ nlArrayAllocator<T> m_ArrayAllocator;
}; // total size: depends on T, N

#endif // _NLSORTEDSLOT_H_
