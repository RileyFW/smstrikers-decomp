#include "Game/BeginFrameTask.h"

#include "NL/gl/glState.h"
#include "NL/gl/glUserData.h"
#include "Game/GameObjectLighting.h"

#include "NL/glx/glxTexture.h"

const u32 GLTT_BumpLocal_bit = 1 << (int)GLTT_BumpLocal;
// /**
//  * Offset/Address/Size: 0xA8 | 0x80170214 | size: 0x84
//  */
// void Config::TagValuePair::Get<BasicString<char, Detail::TempStringAllocator>>() const
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8017016C | size: 0xA8
//  */
// void Config::Get<BasicString<char, Detail::TempStringAllocator>>(const char*, BasicString<char, Detail::TempStringAllocator>)
// {
// }

/**
 * Offset/Address/Size: 0x19E8 | 0x801700C8 | size: 0x98
 */
glModel* cb_ParticleLighting(glModel* pModel)
{
    glModelPacket* pPacket; // r27
    u32 LitProgram = glGetProgram("3d pointlit");
    u32 lightRamp = GetGameObjectLightRamp();
    void* pLightData = GetInGameLightData();
    pPacket = pModel->packets;

    while (pPacket < &pModel->packets[pModel->numPackets])
    {
        pPacket->state.program = LitProgram;
        pPacket->state.texture[5] = lightRamp;
        pPacket->state.texconfig |= GLTT_BumpLocal_bit;
        glUserAttach(pLightData, pPacket, 0);
        pPacket++;
    }
    return pModel;
}

/**
 * Offset/Address/Size: 0x14B8 | 0x8016FB98 | size: 0x530
 */
void SetupMatrices()
{
}

/**
 * Offset/Address/Size: 0x1068 | 0x8016F748 | size: 0x450
 */
void SetupRenderInfo()
{
}

/**
 * Offset/Address/Size: 0x950 | 0x8016F030 | size: 0x718
 */
void DrawSafeFrame()
{
}

/**
 * Offset/Address/Size: 0x410 | 0x8016EAF0 | size: 0x540
 */
void DrawGrid(int)
{
}

/**
 * Offset/Address/Size: 0x0 | 0x8016E6E0 | size: 0x410
 */
void BeginFrameTask::Run(float)
{
}
