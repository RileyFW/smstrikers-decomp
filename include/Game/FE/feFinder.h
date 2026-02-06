#ifndef _FEFINDER_H_
#define _FEFINDER_H_

#include "NL/nlString.h"

struct InlineHasher
{
    /* 0x0 */ unsigned long m_Hash;
}; // total size: 0x4

template <typename T, int N>
class FEFinder
{
public:
    template <typename U>
    static T* Find(U* slide, InlineHasher h1, InlineHasher h2, InlineHasher h3, InlineHasher h4, InlineHasher h5, InlineHasher h6);
    template <typename U>
    static T* _Find(U* slide, const unsigned long hash1, const unsigned long hash2, const unsigned long hash3, const unsigned long hash4, const unsigned long hash5, const unsigned long hash6);
};

#endif // _FEFINDER_H_
