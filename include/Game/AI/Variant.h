#ifndef _VARIANT_H_
#define _VARIANT_H_

// void 0x8028D2AC..0x8028D2B0 | size : 0x4;
#include "NL/nlMath.h"
#include "Game/Player.h"
#include "Game/Team.h"

enum eVariantType
{
    FT_UNSPECIFIED = -1,
    FT_BOOL = 0,
    FT_CHAR = 1,
    FT_SHORT = 2,
    FT_INT = 3,
    FT_U32 = 4,
    FT_FLOAT = 5,
    FT_PLAYER = 6,
    FT_TEAM = 7,
    FT_VECTOR = 8,
    NUM_V_TYPES = 9,
};

class Variant
{
public:
    virtual ~Variant();

    void ToString() const;
    void GetHash() const;

    /* 0x4 */ enum eVariantType mType;
    /* 0x8 */ union
    {
        bool b;
        char c;
        signed short s;
        float f;
        int i;
        unsigned long u;
        class cPlayer* pPlayer;
        class cTeam* pTeam;
        class nlVector3 vector;
    } mData;
}; // total size: 0x14

// class Format < BasicString < char, Detail
// {
// public:
//     void TempStringAllocator >, float > (const BasicString<char, Detail::TempStringAllocator>&, const float&);
//     void TempStringAllocator >, unsigned long > (const BasicString<char, Detail::TempStringAllocator>&, const unsigned long&);
//     void TempStringAllocator >, char > (const BasicString<char, Detail::TempStringAllocator>&, const char&);
//     void TempStringAllocator >, float, float, float > (const BasicString<char, Detail::TempStringAllocator>&, const float&, const float&, const float&);
// };

// class FormatImpl < BasicString < char, Detail
// {
// public:
//     void TempStringAllocator >> ::operator% <unsigned long>(const unsigned long&);
//     void TempStringAllocator >> ::operator% <char>(const char&);
//     void TempStringAllocator >> ::operator% <float>(const float&);
// };

// class LexicalCast < BasicString < char, Detail
// {
// public:
//     void TempStringAllocator >, unsigned long > (const unsigned long&);
//     void TempStringAllocator >, char > (const char&);
// };

// class Detail
// {
// public:
//     void LexicalCastImpl<BasicString<char, Detail::TempStringAllocator>, unsigned long>::Do(unsigned long);
//     void LexicalCastImpl<BasicString<char, Detail::TempStringAllocator>, char>::Do(char);
// };

#endif // _VARIANT_H_
