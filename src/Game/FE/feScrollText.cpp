#include "Game/FE/feScrollText.h"

/**
 * Offset/Address/Size: 0x0 | 0x800C89D4 | size: 0x38
 */
void FEScrollText::ApplyNewTextInstancePointer(TLTextInstance* controltext, float boxwidth, float boxheight)
{
    nlVector2 boxSize;
    boxSize.f.y = boxheight;

    this->m_controlText = controltext;
    TLTextInstance* text = this->m_controlText;

    boxSize.f.x = boxwidth;

    text->m_OverloadedAttributes.BoxSize = boxSize;
    text->m_OverloadFlags |= 0x4;
}
/**
 * Offset/Address/Size: 0x38 | 0x800C8A0C | size: 0x190
 */
void FEScrollText::Update(float)
{
}

/**
 * Offset/Address/Size: 0x1C8 | 0x800C8B9C | size: 0x198
 */
void FEScrollText::SetDisplayMessage(const char*)
{
}

/**
 * Offset/Address/Size: 0x360 | 0x800C8D34 | size: 0x190
 */
void FEScrollText::SetDisplayMessage(unsigned long)
{
}

/**
 * Offset/Address/Size: 0x4F0 | 0x800C8EC4 | size: 0x578
 */
// void FEScrollText::SetDisplayMessage(const BasicString<unsigned short, Detail::TempStringAllocator>&)
// {
// }

/**
 * Offset/Address/Size: 0xA68 | 0x800C943C | size: 0x1E8
 */
FEScrollText::FEScrollText(TLTextInstance*, int, int)
{
}

/**
 * Offset/Address/Size: 0x0 | 0x800C9624 | size: 0x90
 */
// void nlBSearch<nlFont::GlyphInfo, nlFont::GlyphInfo>(const nlFont::GlyphInfo&, nlFont::GlyphInfo*, int)
// {
// }
