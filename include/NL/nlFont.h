#ifndef _NLFONT_H_
#define _NLFONT_H_

#include "NL/nlMath.h"

enum TextureType
{
    InvalidTextureType = 0,
    Colour = 1,
    Greyscale = 2,
    SplitFX = 3,
};

enum Distribution
{
    InvalidDistribution = 0,
    English = 1,
    InOrder = 2,
};

struct ScissorBox
{
    /* 0x0 */ unsigned short X;
    /* 0x2 */ unsigned short Y;
    /* 0x4 */ unsigned short Width;
    /* 0x6 */ unsigned short Height;
}; // total size: 0x8

struct TextMetrics
{
    /* 0x00 */ unsigned long FontName;
    /* 0x04 */ unsigned short Height;
    /* 0x06 */ unsigned short RenderHeight;
    /* 0x08 */ unsigned short Ascent;
    /* 0x0A */ unsigned short RenderAscent;
    /* 0x0C */ unsigned short InternalLeading;
    /* 0x10 */ float Spacing;
    /* 0x14 */ float LineHeight;
}; // total size: 0x18

class nlFont
{
public:
    struct GlyphInfo
    {
        /* 0x0 */ nlVector2 uv;
        /* 0x8 */ unsigned char Advance;
        /* 0x9 */ unsigned char RenderWidth;
        /* 0xA */ signed char Offset;
        /* 0xB */ unsigned char Page : 4;
        /* 0xB */ unsigned char HasKernPairs : 1;
        /* 0xC */ unsigned short UnicodeChar;
    }; // total size: 0x10

    struct KernPair
    {
        /* 0x0 */ unsigned short A;
        /* 0x2 */ unsigned short B;
        /* 0x4 */ int Kern;
    }; // total size: 0x8

    void GetCharWidth(unsigned short, unsigned short) const;
    void DisableScissorBox() const;
    // void SetScissorBox(const nlFont::ScissorBox&) const;
    // void DrawString(eGLView, const FontCharString&, const nlVector2&, const nlColour&, const nlColour&, int, nlFont::TextPass, bool, unsigned long*, nlColour*) const;
    void Load(const char*, char*, unsigned long);
    // void GlyphInfo::SortProc(const nlFont::GlyphInfo*, const nlFont::GlyphInfo*);
    // void KernPair::SortProc(const nlFont::KernPair*, const nlFont::KernPair*);

    ~nlFont();
    nlFont();

    /* 0x000 */ unsigned long m_PageCount;
    /* 0x004 */ unsigned long m_TextureHandles[16];
    /* 0x044 */ unsigned long m_EffectTextureHandles[16];
    /* 0x084 */ TextureType m_TextureType;
    /* 0x088 */ unsigned char m_bScissorBox;
    /* 0x08A */ ScissorBox m_scissorBox;
    /* 0x094 */ Distribution m_Distribution;
    /* 0x098 */ unsigned long m_CharacterSet;
    /* 0x09C */ unsigned long m_PageSize;
    /* 0x0A0 */ char m_FontName[32];
    /* 0x0C0 */ TextMetrics m_Metrics;
    /* 0x0D8 */ float m_InvTexSize;
    /* 0x0DC */ GlyphInfo m_GlyphLookup[95];
    /* 0x6CC */ GlyphInfo* m_pExtendedGlyphs;
    /* 0x6D0 */ unsigned long m_ExtendedGlyphCount;
    /* 0x6D4 */ KernPair* m_pKernTable;
    /* 0x6D8 */ unsigned long m_KernTableSize;
}; // total size: 0x6DC

// class ListContainerBase<nlFont
// {
// public:
//     ListContainerBase<nlFont::GlyphInfo, BasicSlotPoolHigh<ListEntry<nlFont::GlyphInfo>>>::DeleteEntry(ListEntry<nlFont::GlyphInfo>*);
//     ListContainerBase<nlFont::KernPair, BasicSlotPoolHigh<ListEntry<nlFont::KernPair>>>::DeleteEntry(ListEntry<nlFont::KernPair>*);
// };

// class BasicSlotPoolHigh<ListEntry<nlFont
// {
// public:
//     BasicSlotPoolHigh<ListEntry<nlFont::GlyphInfo>>::freeFN(void*);
//     BasicSlotPoolHigh<ListEntry<nlFont::GlyphInfo>>::allocFN(unsigned long);
//     BasicSlotPoolHigh<ListEntry<nlFont::KernPair>>::freeFN(void*);
//     BasicSlotPoolHigh<ListEntry<nlFont::KernPair>>::allocFN(unsigned long);
// };

// class nlQSort<nlFont
// {
// public:
//     nlQSort<nlFont::GlyphInfo>(nlFont::GlyphInfo*, int, int (*)(const nlFont::GlyphInfo*, const nlFont::GlyphInfo*));
//     nlQSort<nlFont::KernPair>(nlFont::KernPair*, int, int (*)(const nlFont::KernPair*, const nlFont::KernPair*));
// };

// class nlBSearch<nlFont
// {
// public:
//     nlBSearch<nlFont::KernPair, nlFont::KernPair>(const nlFont::KernPair&, nlFont::KernPair*, int);
// };

// class nlWalkList<ListEntry<nlFont
// {
// public:
//     nlWalkList<ListEntry<nlFont::GlyphInfo>, ListContainerBase<nlFont::GlyphInfo, BasicSlotPoolHigh<ListEntry<nlFont::GlyphInfo>>>>(ListEntry<nlFont::GlyphInfo>*, ListContainerBase<nlFont::GlyphInfo, BasicSlotPoolHigh<ListEntry<nlFont::GlyphInfo>>>*, void (ListContainerBase<nlFont::GlyphInfo, BasicSlotPoolHigh<ListEntry<nlFont::GlyphInfo>>>::*)(ListEntry<nlFont::GlyphInfo>*));
//     nlWalkList<ListEntry<nlFont::KernPair>, ListContainerBase<nlFont::KernPair, BasicSlotPoolHigh<ListEntry<nlFont::KernPair>>>>(ListEntry<nlFont::KernPair>*, ListContainerBase<nlFont::KernPair, BasicSlotPoolHigh<ListEntry<nlFont::KernPair>>>*, void (ListContainerBase<nlFont::KernPair, BasicSlotPoolHigh<ListEntry<nlFont::KernPair>>>::*)(ListEntry<nlFont::KernPair>*));
// };

// class nlListRemoveStart<ListEntry<nlFont
// {
// public:
//     nlListRemoveStart<ListEntry<nlFont::GlyphInfo>>(ListEntry<nlFont::GlyphInfo>**, ListEntry<nlFont::GlyphInfo>**);
//     nlListRemoveStart<ListEntry<nlFont::KernPair>>(ListEntry<nlFont::KernPair>**, ListEntry<nlFont::KernPair>**);
// };

// class nlListAddStart<ListEntry<nlFont
// {
// public:
//     nlListAddStart<ListEntry<nlFont::KernPair>>(ListEntry<nlFont::KernPair>**, ListEntry<nlFont::KernPair>*, ListEntry<nlFont::KernPair>**);
//     nlListAddStart<ListEntry<nlFont::GlyphInfo>>(ListEntry<nlFont::GlyphInfo>**, ListEntry<nlFont::GlyphInfo>*, ListEntry<nlFont::GlyphInfo>**);
// };

#endif // _NLFONT_H_
