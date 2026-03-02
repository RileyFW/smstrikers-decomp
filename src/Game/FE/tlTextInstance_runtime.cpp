#include "Game/FE/tlTextInstance.h"
#include "NL/nlFont.h"
#include "NL/nlLocalization.h"

extern nlLocalization* g_pLocalization;
extern const unsigned short LocalizationTableNotFound[];
extern const unsigned short MissingLocString[];

template <typename T, typename U>
T* nlBSearch(const U& key, T* table, int count);

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
 * TODO: 95.3% match - prologue stw r31 scheduling diff and add r0 vs r3 register destination diff
 */
const unsigned short* TLTextInstance::GetString() const
{
    if (m_OverloadFlags & 0x8)
    {
        unsigned long key = m_LocStrId;
        nlLocalization* loc = g_pLocalization;
        const unsigned short* pWideTextString;

        if (loc->m_LookupTable == NULL)
        {
            pWideTextString = LocalizationTableNotFound;
        }
        else
        {
            nlLocalization::StringLookup* result = nlBSearch<nlLocalization::StringLookup, unsigned long>(key, loc->m_LookupTable, loc->m_pFile->StringCount);
            if (result != NULL)
            {
                pWideTextString = loc->m_FirstString + result->StringOffset;
            }
            else
            {
                pWideTextString = MissingLocString;
            }
        }
        return pWideTextString;
    }

    return m_wcUserString;
}
