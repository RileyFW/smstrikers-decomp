#include "Game/Blinker.h"

#include "Sys/debug.h"
#include "string.h"

#include "NL/nlPrint.h"
#include "NL/gl/glState.h"
#include "NL/gl/glTexture.h"

extern float RandomizedValue(float, float);

const float BlinkTimes[4] = { 1.25f, 0.016666667f, 0.033333335f, 0.016666667f };

/**
 * Offset/Address/Size: 0x0 | 0x8016A968 | size: 0x74
 */
void Blinker::Blink(glModel* model)
{
    struct PacketSpan
    {
        u32 unused0;   // +0x00
        s32 baseIndex; // +0x04
        u32 count;     // +0x08
    };

    const u32 choose_off = (m_unk_0x00 == model->id) ? 0u : 4u;
    const PacketSpan* span = *reinterpret_cast<const PacketSpan**>(reinterpret_cast<u8*>(this) + 0x0C + choose_off);
    if (span == nullptr)
    {
        return;
    }

    for (u32 i = 0; i < span->count; ++i)
    {
        const s32 idx = span->baseIndex + static_cast<s32>(i);
        const u32 selected = *reinterpret_cast<const u32*>(reinterpret_cast<u8*>(this) + 0x18 + (static_cast<u32>(m_unk_0x2C) << 2));
        *reinterpret_cast<u32*>(reinterpret_cast<u8*>(model->packets) + idx * 0x4A + 0x28) = selected;
    }
}

/**
 * Offset/Address/Size: 0x74 | 0x8016A9DC | size: 0x130
 */
void Blinker::Update(float arg0)
{
    float var_f31 = arg0;
    if (NisPlayer::Instance()->WorldIsFrozen())
    {
        var_f31 = 0.0f;
    }

    m_unk_0x28 += var_f31;

    if (m_unk_0x28 > reinterpret_cast<float*>(&m_unk_0x30)[m_unk_0x2C])
    {
        m_unk_0x28 = 0.0f;

        switch (m_unk_0x2C)
        {
        case 0:
            m_unk_0x2C = 1;
            if (m_unk_0x40 == 0)
            {
                if (RandomizedValue(0.5f, 1.0f) < 0.2f)
                {
                    m_unk_0x30[0] = RandomizedValue(0.06666667f, 0.06666667f);
                    m_unk_0x40 = 1;
                    return;
                }
            }
            m_unk_0x30[0] = RandomizedValue(1.2f, 1.0f);
            m_unk_0x40 = 0;
            break;
        case 1:
            m_unk_0x2C = 2;
            break;
        case 2:
            m_unk_0x2C = 3;
            break;
        case 3:
            m_unk_0x2C = 0;
            break;
        }
    }
}

/**
 * Offset/Address/Size: 0x1A4 | 0x8016AB0C | size: 0x454
 */
Blinker::Blinker(const char* name, unsigned long arg1, GLMaterialList* list0, GLMaterialList* list1, unsigned long matId)
{
    // Order and initialization to match asm
    m_unk_0x41 = 0;
    m_unk_0x00 = arg1;
    memcpy(&m_unk_0x30, BlinkTimes, 0x10);

    m_unk_0x04 = list0;
    m_unk_0x08 = list1;
    m_unk_0x14 = matId;

    m_unk_0x0C = list0->FindMaterial(matId);
    if (m_unk_0x0C == 0)
    {
        tDebugPrintManager::Print(DEBUG_RENDER, "%s has no eyes on material 0\n", name);
        return;
    }

    if (list1 == 0)
    {
        m_unk_0x10 = 0;
    }
    else
    {
        m_unk_0x10 = list1->FindMaterial(matId);
        if (m_unk_0x10 == 0)
        {
            m_unk_0x08 = 0;
        }
    }

    // Initialize texture ids
    m_unk_0x18 = -1;
    m_unk_0x1C = -1;
    m_unk_0x20 = -1;
    m_unk_0x24 = -1;

    // Stack buffers laid out like asm (0x80 each): sp188, sp108, sp88, sp8
    char sp188[0x80];
    char sp108[0x80];
    char sp88[0x80];
    char sp8[0x80];

    unsigned char var_r30 = 0; // foundFirst
    unsigned char var_r27 = 0; // firstIsZero (1 if index 0 hit, 0 if index 1 hit)
    int var_r28 = 0;           // variant selector: 0,1,2

    // Try index 0 then 1 for each variant until one loads
    for (;;)
    {
        if (var_r28 == 0)
        {
            nlSNPrintf(sp188, 0x80, "%s/%s_eye_%d", name, name, 0);
        }
        else if (var_r28 == 1)
        {
            nlSNPrintf(sp188, 0x80, "%s/%s_eye%d", name, name, 0);
        }
        else if (var_r28 == 2)
        {
            nlSNPrintf(sp188, 0x80, "%s/%seye_%d", name, name, 0);
        }
        else
        {
            break;
        }

        m_unk_0x18 = glGetTexture(sp188);
        if (glTextureLoad(m_unk_0x18))
        {
            var_r27 = 1; // first was 0
            var_r30 = 1;
            break;
        }

        if (var_r28 == 0)
        {
            nlSNPrintf(sp108, 0x80, "%s/%s_eye_%d", name, name, 1);
        }
        else if (var_r28 == 1)
        {
            nlSNPrintf(sp108, 0x80, "%s/%s_eye%d", name, name, 1);
        }
        else // var_r28 == 2
        {
            nlSNPrintf(sp108, 0x80, "%s/%seye_%d", name, name, 1);
        }

        m_unk_0x18 = glGetTexture(sp108);
        if (glTextureLoad(m_unk_0x18))
        {
            var_r27 = 0; // first was 1
            var_r30 = 1;
            break;
        }

        ++var_r28;
        if (var_r28 >= 3)
            break;
    }

    if (var_r30)
    {
        int tmp = (var_r27 != 0) ? -1 : 0;
        int idx2 = tmp + 2;

        if (var_r28 == 0)
        {
            nlSNPrintf(sp88, 0x80, "%s/%s_eye_%d", name, name, idx2);
        }
        else if (var_r28 == 1)
        {
            nlSNPrintf(sp88, 0x80, "%s/%s_eye%d", name, name, idx2);
        }
        else // var_r28 == 2
        {
            nlSNPrintf(sp88, 0x80, "%s/%seye_%d", name, name, idx2);
        }

        m_unk_0x1C = glGetTexture(sp88);

        int idx3 = tmp + 3;
        if (var_r28 == 0)
        {
            nlSNPrintf(sp8, 0x80, "%s/%s_eye_%d", name, name, idx3);
        }
        else if (var_r28 == 1)
        {
            nlSNPrintf(sp8, 0x80, "%s/%s_eye%d", name, name, idx3);
        }
        else // var_r28 == 2
        {
            nlSNPrintf(sp8, 0x80, "%s/%seye_%d", name, name, idx3);
        }

        m_unk_0x20 = glGetTexture(sp8);
    }

    if (!var_r30 || !glTextureLoad(m_unk_0x1C) || !glTextureLoad(m_unk_0x20))
    {
        tDebugPrintManager::Print(DEBUG_RENDER, "Error: %s not properly configured for blinking.\n", name);
        return;
    }

    m_unk_0x24 = m_unk_0x1C;
    m_unk_0x28 = 0.0f;
    m_unk_0x2C = 0;
    m_unk_0x40 = 0;
    m_unk_0x41 = 1;
}
