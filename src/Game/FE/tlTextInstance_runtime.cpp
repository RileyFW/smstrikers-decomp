#include "Game/FE/tlTextInstance.h"
#include "NL/nlFont.h"

/**
 * Offset/Address/Size: 0x0 | 0x802101D8 | size: 0x1C
 */
void TLTextInstance::SetScissorBox(u16 left, u16 top, u16 width, u16 height)
{
    m_UseScissorRect = true;
    m_ScissorRect.X = left;
    m_ScissorRect.Y = top;
    m_ScissorRect.Width = width;
    m_ScissorRect.Height = height;
}

/**
 * Offset/Address/Size: 0x1C | 0x802101F4 | size: 0x1C
 */
void TLTextInstance::SetString(const unsigned short* utf16)
{
    m_wcUserString = utf16;
    m_pFontString = NULL;
    m_OverloadFlags &= 0xFFFFFFF7;
}

/**
 * Offset/Address/Size: 0x38 | 0x80210210 | size: 0x250
 */
void TLTextInstance::Render(eGLView, const nlColour&) const
{
}

/**
 * Offset/Address/Size: 0x288 | 0x80210460 | size: 0x94
 */
const unsigned short* TLTextInstance::GetString() const
{
    return m_wcUserString;
}
