#ifndef _BASICSTRING_H_
#define _BASICSTRING_H_

class Vector
{
    // total size: 0xC
    char* mData;   // offset 0x0, size 0x4
    int mSize;     // offset 0x4, size 0x4
    int mCapacity; // offset 0x8, size 0x4
};

class Data
{
    // total size: 0x10
    Vector mData;  // offset 0x0, size 0xC
    int mRefCount; // offset 0xC, size 0x4
};

class BasicString
{
    // total size: 0x4
    Data* mData; // offset 0x0, size 0x4
};

#endif
