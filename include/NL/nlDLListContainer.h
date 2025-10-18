#ifndef _NLDLLISTCONTAINER_H_
#define _NLDLLISTCONTAINER_H_

#include "NL/nlDLRing.h"
#include "NL/nlAdapter.h"

template <typename T, typename Adapter>
class DLListContainerBase
{
public:
    void DeleteEntry(DLListEntry<T>* entry);

    /* 0x0 */ Adapter m_Allocator;    // offset 0x0, size 0x1
    /* 0x4 */ DLListEntry<T>* m_Head; // offset 0x4, size 0x4
}; // total size: 0x1C

template <typename T>
class nlDLListContainer : public DLListContainerBase<T, NewAdapter<DLListEntry<T> > >
{
public:
}; // total size: 0x8

#endif // _NLDLLISTCONTAINER_H_
