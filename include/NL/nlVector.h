#ifndef _NLVECTOR_H_
#define _NLVECTOR_H_

#include "NL/nlMath.h"
#include "NL/nlMemory.h"

template <typename T, typename Allocator = DefaultAllocator>
class Vector
{
public:
    /* 0x0 */ T* mData;
    /* 0x4 */ int mSize;
    /* 0x8 */ int mCapacity;
}; // total size: 0xC

#endif // _NLVECTOR_H_
