#include "Game/FE/fePresentation.h"

#include "NL/nlString.h"

#include "Game/FE/feTemplates.h"

/**
 * Offset/Address/Size: 0x0 | 0x80210644 | size: 0xD0
 */
void FEPresentation::Update(float deltaTime)
{
    TLSlide* sp8;
    TLSlide* temp_r3;
    f32 temp_f0;
    f32 temp_f2;
    s32 temp_r0;

    if (m_currentSlide != NULL)
    {
        m_fadeDuration += deltaTime;
        temp_r3 = m_currentSlide;
        temp_f2 = m_fadeDuration;
        temp_f0 = temp_r3->m_start + temp_r3->m_duration;
        if (temp_f2 > temp_f0)
        {
            temp_r0 = temp_r3->m_uPlayMode;
            switch (temp_r0)
            { /* irregular */
            case 1:
                m_fadeDuration = temp_f2 - temp_f0;
                break;
            case 0:
                m_fadeDuration = temp_f0;
                break;
            }
        }
        sp8 = m_currentSlide;
        // m_currentSlide->Update(m_currentSlide->unk18, m_fadeDuration);
        // m_currentSlide->unk18 = m_fadeDuration;
        m_currentSlide->Update(deltaTime);
    }
}

/**
 * Offset/Address/Size: 0xD0 | 0x80210714 | size: 0x10
 */
void FEPresentation::SetActiveSlide(TLSlide* slide)
{
    m_fadeDuration = 0.0f;
    m_currentSlide = slide;
}

/**
 * Offset/Address/Size: 0xE0 | 0x80210724 | size: 0x3C
 */
void FEPresentation::SetActiveSlide(unsigned long hash)
{
    TLSlide* slide = FindItemByHashID<TLSlide>(m_slides, hash);
    m_fadeDuration = 0.0f;
    m_currentSlide = slide;
}

/**
 * Offset/Address/Size: 0x11C | 0x80210760 | size: 0x4C
 */
void FEPresentation::SetActiveSlide(const char* slideName)
{
    u32 hash = nlStringLowerHash(slideName);
    TLSlide* slide = FindItemByHashID<TLSlide>(m_slides, hash);
    m_fadeDuration = 0.0f;
    m_currentSlide = slide;
}
