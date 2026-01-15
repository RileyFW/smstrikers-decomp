#ifndef _NLARRAYALLOCATOR_H_
#define _NLARRAYALLOCATOR_H_

#include "NL/nlDLRing.h"

template <typename T>
class nlArrayAllocator
{
public:
    /* 0x0 */ T* m_pFree; // size 0x4
}; // total size: 0x4

#endif // _NLARRAYALLOCATOR_H_
