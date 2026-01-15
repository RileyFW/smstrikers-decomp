#ifndef _FEFINDER_H_
#define _FEFINDER_H_

#include "NL/nlString.h"

class TLSlide;

struct InlineHasher
{
    /* 0x0 */ unsigned long m_Hash;
}; // total size: 0x4

template <typename T, int N>
class FEFinder
{
public:
    static T* Find(TLSlide* slide, InlineHasher& h1, InlineHasher& h2, InlineHasher& h3, InlineHasher& h4, InlineHasher& h5, InlineHasher& h6);
    static T* _Find(TLSlide* slide, unsigned long hash1, unsigned long hash2, unsigned long hash3, unsigned long hash4, unsigned long hash5, unsigned long hash6);
};

#endif // _FEFINDER_H_
