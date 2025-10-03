#ifndef _FUZZYVARIANT_H_
#define _FUZZYVARIANT_H_

#include "Game/AI/Variant.h"

// void 0x8028D28C..0x8028D290 | size: 0x4;

class FuzzyVariant : public Variant
{
public:
    FuzzyVariant();
    FuzzyVariant(const FuzzyVariant&);
    virtual ~FuzzyVariant();

    float Confidence;      // offset 0x14, size 0x4
    float SelectionChance; // offset 0x18, size 0x4
    Variant ExtraData;     // offset 0x1C, size 0x14
}; // total size: 0x30

#endif // _FUZZYVARIANT_H_
