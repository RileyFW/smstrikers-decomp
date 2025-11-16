#ifndef _TLTEXTINSTANCE_H_
#define _TLTEXTINSTANCE_H_

#include "types.h"
#include "NL/nlColour.h"
#include "NL/GL/gl.h"
#include "NL/nlFont.h"
#include "NL/nlMath.h"

#include "Game/FE/tlInstance.h"

struct ScissorBox
{
    /* 0x0 */ unsigned short X;
    /* 0x2 */ unsigned short Y;
    /* 0x4 */ unsigned short Width;
    /* 0x6 */ unsigned short Height;
}; // total size: 0x8

struct FETextLibObjectAttributes
{
    /* 0x0 */ nlColour EffectColour;
    /* 0x4 */ nlVector2 BoxSize;
}; // total size: 0xC

struct Row
{
    /* 0x00 */ unsigned short XOffset;
    /* 0x02 */ unsigned short FirstChar;
}; // total size: 0x4

struct StringDrawInfo
{
    /* 0x00 */ const nlFont* pFont;
    /* 0x04 */ const unsigned short* String;
    /* 0x08 */ const nlMatrix4* pMatrix;
    /* 0x0C */ unsigned long DrawOptions;
    /* 0x10 */ unsigned short RowCount;
    /* 0x12 */ signed short YOffset;
    /* 0x14 */ Row Rows[17];
}; // total size: 0x58

class FontCharString
{
    unsigned short* m_pString;      // offset 0x0, size 0x4
    unsigned char m_InternalBuffer; // offset 0x4, size 0x1
}; // total size: 0x8

class TLTextInstance : public TLInstance
{
public:
    void SetScissorBox(u16 left, u16 top, u16 width, u16 height);
    void SetString(const unsigned short* utf16);
    void SetStringId(const char* name);
    const unsigned short* GetString() const;
    void Render(eGLView, const nlColour&) const;

    unsigned long m_LocStrId;                         // offset 0x80, size 0x4
    FETextLibObjectAttributes m_OverloadedAttributes; // offset 0x84, size 0xC
    unsigned long m_OverloadFlags;                    // offset 0x90, size 0x4
    StringDrawInfo m_DrawInfo;                        // offset 0x94, size 0x58
    FontCharString* m_pFontString;                    // offset 0xEC, size 0x4
    unsigned long m_DrawOptions;                      // offset 0xF0, size 0x4
    const unsigned short* m_wcUserString;             // offset 0xF4, size 0x4
    bool m_UseScissorRect;                            // offset 0xF8, size 0x1
    ScissorBox m_ScissorRect;                         // offset 0xFA, size 0x8

}; // total size: 0x104

#endif // _TLTEXTINSTANCE_H_
