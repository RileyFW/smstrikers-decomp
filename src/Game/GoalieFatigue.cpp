#include "Game/GoalieFatigue.h"

/**
 * Offset/Address/Size: 0xA0 | 0x80052CEC | size: 0x1C
 */
GoalieFatigue::GoalieFatigue()
{
    m_unk_0x00 = 0.0f;
    m_unk_0x04 = 1.0f;
    m_unk_0x08 = 0.0f;
    m_unk_0x0C = 0.0f;
}

/**
 * Offset/Address/Size: 0x88 | 0x80052CD4 | size: 0x18
 */
void GoalieFatigue::Reset()
{
    m_unk_0x00 = 100.0f;
    m_unk_0x08 = 0.0f;
    m_unk_0x0C = 0.0f;
}

/**
 * Offset/Address/Size: 0x38 | 0x80052C84 | size: 0x50
 */
void GoalieFatigue::Update(float arg0)
{
    f32 temp_f0;
    f32 temp_f2;

    temp_f2 = m_unk_0x00;
    if (temp_f2 < 100.0f)
    {
        m_unk_0x00 = (m_unk_0x04 * arg0) + temp_f2;
    }
    temp_f0 = m_unk_0x0C;
    if (temp_f0 > 0.0f)
    {
        m_unk_0x0C = temp_f0 - arg0;
        if (m_unk_0x0C <= 0.0f)
        {
            m_unk_0x00 = 100.0f;
        }
    }
}

/**
 * Offset/Address/Size: 0x0 | 0x80052C4C | size: 0x38
 */
void GoalieFatigue::RegisterShot(float arg0)
{
    m_unk_0x00 -= arg0;
    if (m_unk_0x00 < 100.0f)
    {
        m_unk_0x0C = 0.0f;
        if (m_unk_0x00 < 0.0f)
        {
            m_unk_0x00 = 0.0f;
        }
    }
}
