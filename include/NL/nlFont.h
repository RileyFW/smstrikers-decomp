#ifndef _NLFONT_H_
#define _NLFONT_H_

struct TextMetrics
{
    // total size: 0x18
    unsigned long FontName;         // offset 0x0, size 0x4
    unsigned short Height;          // offset 0x4, size 0x2
    unsigned short RenderHeight;    // offset 0x6, size 0x2
    unsigned short Ascent;          // offset 0x8, size 0x2
    unsigned short RenderAscent;    // offset 0xA, size 0x2
    unsigned short InternalLeading; // offset 0xC, size 0x2
    // 2 bytes padding
    float Spacing;    // offset 0x10, size 0x4
    float LineHeight; // offset 0x14, size 0x4
};

struct ScissorBox
{
    /* 0x0 */ unsigned short X;
    /* 0x2 */ unsigned short Y;
    /* 0x4 */ unsigned short Width;
    /* 0x6 */ unsigned short Height;
}; // total size: 0x8

class nlFont
{
public:
    typedef struct
    {
        // TODO: Define GlyphInfo struct
    } GlyphInfo;

    typedef struct
    {
        // TODO: Define GlyphInfo struct
    } KernPair;

    void GetCharWidth(unsigned short, unsigned short) const;
    void DisableScissorBox() const;
    // void SetScissorBox(const nlFont::ScissorBox&) const;
    // void DrawString(eGLView, const FontCharString&, const nlVector2&, const nlColour&, const nlColour&, int, nlFont::TextPass, bool, unsigned long*, nlColour*) const;
    void Load(const char*, char*, unsigned long);
    // void GlyphInfo::SortProc(const nlFont::GlyphInfo*, const nlFont::GlyphInfo*);
    // void KernPair::SortProc(const nlFont::KernPair*, const nlFont::KernPair*);

    ~nlFont();
    nlFont();

    unsigned long m_PageCount;                // offset 0x0, size 0x4
    unsigned long m_TextureHandles[16];       // offset 0x4, size 0x40
    unsigned long m_EffectTextureHandles[16]; // offset 0x44, size 0x40
    unsigned long m_TextureType;              // offset 0x84, size 0x4
private:
    unsigned char m_bScissorBox; // offset 0x88, size 0x1
    // 1 byte padding
    ScissorBox m_scissorBox; // offset 0x8A, size 0x8
    // 2 bytes padding
    unsigned long m_Distribution; // offset 0x94, size 0x4
    unsigned long m_CharacterSet; // offset 0x98, size 0x4
    unsigned long m_PageSize;     // offset 0x9C, size 0x4
    char m_FontName[32];          // offset 0xA0, size 0x20
public:
    TextMetrics m_Metrics; // offset 0xC0, size 0x18
};

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
