#include "Game/BeginFrameTask.h"

#include "NL/gl/glState.h"
#include "NL/gl/glUserData.h"
#include "Game/GameObjectLighting.h"

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
void cb_ParticleLighting(glModel* pModel)
{
    //     glModelPacket* var_r28;
    //     s32 temp_r30;
    //     s32 temp_r31;
    //     u32 temp_r29;
    //     void* temp_r27;

    //     temp_r29 = glGetProgram("3d pointlit");
    //     temp_r30 = GetGameObjectLightRamp();
    //     var_r28 = arg0->unkC;
    //     temp_r27 = GetInGameLightData();
    //     temp_r31 = GLTT_BumpLocal_bit;
    // loop_2:
    //     if (var_r28 < (void*)(arg0->unkC + (arg0->unk0 * 0x4A)))
    //     {
    //         var_r28->unk1C = temp_r29;
    //         var_r28->unk3C = temp_r30;
    //         var_r28->unk40 |= temp_r31;
    //         glUserAttach(temp_r27, var_r28, 0);
    //         var_r28 += 0x4A;
    //         goto loop_2;
    //     }
    //     return arg0;
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
