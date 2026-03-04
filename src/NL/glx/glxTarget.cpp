#include "NL/glx/glxTarget.h"
#include "NL/glx/glxTexture.h"
#include "dolphin/gx.h"
#include "NL/nlDebug.h"

#include "dolphin/fake_tgmath.h"
#include "dolphin/mtx.h"

#include "NL/gl/glConstant.h"
#include "NL/gc/gcSwizzler.h"
#include "NL/gl/glMemory.h"
#include "NL/nlPrint.h"
#include "NL/gl/glState.h"
#include "NL/nlString.h"
#include "Game/Sys/debug.h"

struct glx_DOFTexture
{
    /* 0x00 */ u32 m_unk_0x00;
    /* 0x04 */ u32 m_unk_0x04;
    /* 0x08 */ u32 m_unk_0x08;
    /* 0x0C */ u32 m_unk_0x0C;
    /* 0x10 */ u32 m_unk_0x10;
    /* 0x14 */ void* m_unk_0x14;
};

u32 GrabTextureName = 0;
u32 DOFTextureName = 0;
void* clearz_mem = 0;
u32 glx_SharedMemory = 0;
u32 glx_SharedSize = 0;
bool glx_SharedLock = false;

/**
 * Offset/Address/Size: 0x0 | 0x801C26DC | size: 0x104
 */
void glPlatGrabFrameBufferToTexture(unsigned long texHandle, unsigned int width, unsigned int height, unsigned int srcX, unsigned int srcY, unsigned int srcW, unsigned int srcH)
{
    static GXTexFmt gx_format[] = {
        GX_TF_RGB565,
        GX_TF_RGB5A3,
        GX_TF_CMPR,
        GX_TF_RGBA8,
        GX_TF_I8,
        GX_TF_I4,
        GX_TF_A8,
        GX_TF_IA8,
        (GXTexFmt)GX_TF_C8,
    };

    bool colorUpdate = gxSetColourUpdate(true);
    bool alphaUpdate = gxSetAlphaUpdate(true);
    gxSaveZMode();
    gxSetZMode(false, GX_LEQUAL, true);

    PlatTexture* tex = glx_GetTex(texHandle, false, true);

    GXSetTexCopySrc(srcX, srcY, srcW, srcH);

    bool mipmap;
    if (srcW == width * 2 && srcH == height * 2)
    {
        mipmap = true;
    }
    else
    {
        mipmap = false;
    }

    GXSetTexCopyDst(width, height, gx_format[tex->m_Format], mipmap);
    GXCopyTex(tex->m_SwizzledData, true);
    GXPixModeSync();

    gxSetColourUpdate(colorUpdate);
    gxSetAlphaUpdate(alphaUpdate);
    gxRestoreZMode();
}

/**
 * Offset/Address/Size: 0x104 | 0x801C27E0 | size: 0x4
 */
void glx_UpdateWarble()
{
    // EMPTY
}

/**
 * Offset/Address/Size: 0x108 | 0x801C27E4 | size: 0xE0
 */
void glx_DOFUpdate(float arg8)
{
    Vec sp10;
    Mtx sp24;
    Mtx sp3C;
    Mtx sp58;
    // f32 sp20;
    // f32 sp1C;
    // f32 sp18;
    // f32 sp14;
    // ? sp10;

    // nlVector4 sp14;

    // ? spC;
    // f32 sp8;
    // f32 temp_f0;
    // f32 var_f31;

    float var_f31 = arg8;
    if (fabs(var_f31) < 0.001f)
    {
        var_f31 = 0.001f;
    }
    GXGetProjectionv(&sp3C[0][0]);
    GXGetViewportv(&sp24[0][0]);
    PSMTXIdentity(sp58);
    // void GXProject(f32 x, f32 y, f32 z, const Mtx mtx, const f32* pm, const f32* vp, f32* sx, f32* sy, f32* sz)
    GXProject(0.f, 0.f, -arg8, sp58, &sp3C[0][0], &sp24[0][0], &(sp10.x), &(sp10.y), &(sp10.z));
    float temp_f0 = 16777215.0f * -sp10.z; // or x?
    // sp14 = @452.unk0;
    // sp18 = @452.unk4;
    // sp1C = @452.unk8;
    // sp20 = @452.unkC;
    // sp14 = temp_f0;
    // sp18 = temp_f0;
    // sp1C = temp_f0;
    // sp20 = temp_f0;
    nlVector4 v4 = { temp_f0, temp_f0, temp_f0, temp_f0 };
    glConstantSet("dof/depth", v4);
    // glConstantSet("dof/depth", nlVector4(0.f, 0.f, 0.f, temp_f0));

    // sp14.x = temp_f0;
    // sp14.y = temp_f0;
    // sp14.z = temp_f0;
    // sp14.w = temp_f0;

    // glConstantSet("dof/depth", sp14);
}

/**
 * Offset/Address/Size: 0x1E8 | 0x801C28C4 | size: 0xC4
 */
void glx_DOFGrab()
{
    if ((u8)glx_SharedLock == 0)
    {
        bool colorUpdate = gxSetColourUpdate(true);
        bool alphaUpdate = gxSetAlphaUpdate(true);
        gxSaveZMode();
        gxSetZMode(1, GX_LEQUAL, 1);
        GXSetTexCopySrc(0, 0, 0x280, 0x1C0);
        GXSetTexCopyDst(0x140, 0xE0, GX_TF_RGB565, 1);
        GXCopyTex(((glx_DOFTexture*)glx_GetTex(DOFTextureName, true, true))->m_unk_0x14, 0);
        GXPixModeSync();
        gxSetColourUpdate(colorUpdate);
        gxSetAlphaUpdate(alphaUpdate);
        gxRestoreZMode();
    }
}

/**
 * Offset/Address/Size: 0x2AC | 0x801C2988 | size: 0x26C
 */
void glx_ShadowTextureGrab()
{
}

/**
 * Offset/Address/Size: 0x518 | 0x801C2BF4 | size: 0xB0
 */
void glx_ClearZBuffer()
{
    s32 temp_r30;
    s32 temp_r31;

    if ((u8)glx_SharedLock == 0)
    {
        bool colorUpdate = gxSetColourUpdate(false);
        bool alphaUpdate = gxSetAlphaUpdate(false);
        gxSaveZMode();
        gxSetZMode(0, GX_LEQUAL, 1);
        GXSetTexCopySrc(0, 0, 0x280, 0x1C0);
        GXSetTexCopyDst(0x140, 0xE0, (_GXTexFmt)0x28, 1);
        GXCopyTex(clearz_mem, 1);
        gxSetColourUpdate(colorUpdate);
        gxSetAlphaUpdate(alphaUpdate);
        gxRestoreZMode();
    }
}

/**
 * Offset/Address/Size: 0x5C8 | 0x801C2CA4 | size: 0x20
 */
void glx_OffsetGrab()
{
    nlBreak();
}

/**
 * Offset/Address/Size: 0x5E8 | 0x801C2CC4 | size: 0x20
 */
void glx_ColourGrab()
{
    nlBreak();
}

/**
 * Offset/Address/Size: 0x608 | 0x801C2CE4 | size: 0x20
 */
void glx_ShadowGrab()
{
    nlBreak();
}

/**
 * Offset/Address/Size: 0x628 | 0x801C2D04 | size: 0x54
 */
void glxPostInitTargets()
{
    nlVector4 vec = { 10.f, 0.f, 0.f, 0.f };
    glConstantSet("target/pshadow_num", vec);
}

/**
 * Offset/Address/Size: 0x67C | 0x801C2D58 | size: 0x1EC
 * TODO: 99.47% match - r29/r30 swap for sharedSize/singleSize in grab texture section, MWCC register allocator quirk
 */
void glxInitTargets()
{
    PlatTexture* pTex;
    unsigned long numBytes;
    void* sharedMemory;
    unsigned long sharedSize;
    unsigned long singleSize;

    numBytes = 0;

    singleSize = GCTextureSize(GXTex_RGB565, 320, 224, 1, (u32)-1);
    singleSize = (singleSize + 31) & ~31;
    sharedSize = singleSize * 2;

    sharedMemory = (void*)glResourceAlloc(sharedSize + 320 * 224, GLM_TextureData);

    glx_SharedMemory = (u32)sharedMemory;
    glx_SharedSize = sharedSize + 320 * 224;
    clearz_mem = (void*)((u8*)sharedMemory + sharedSize);
    numBytes += 320 * 224;

    pTex = glx_CreatePlatTexture();
    pTex->CreateWithMemory(320, 224, GXTex_RGB565, 1, (const void*)sharedMemory);
    pTex->Prepare();
    glx_AddTex(GrabTextureName, pTex);
    numBytes += GCTextureSize(pTex->m_Format, pTex->m_Width, pTex->m_Height, pTex->m_Levels, (u32)-1);

    pTex = glx_CreatePlatTexture();
    pTex->CreateWithMemory(320, 224, GXTex_RGB565, 1, (const void*)((u8*)sharedMemory + singleSize));
    pTex->Prepare();
    glx_AddTex(DOFTextureName, pTex);
    numBytes += GCTextureSize(pTex->m_Format, pTex->m_Width, pTex->m_Height, pTex->m_Levels, (u32)-1);

    for (int i = 0; i < 10; i++)
    {
        char texturename[32];
        nlSNPrintf(texturename, 32, "target/pshadow%02d", i);
        unsigned long handle = glGetTexture(texturename);
        pTex = glx_CreatePlatTexture();
        pTex->Create(80, 80, GXTex_A8, 1, false, false);
        nlZeroMemory(pTex->m_SwizzledData, GCTextureSize(pTex->m_Format, pTex->m_Width, pTex->m_Height, pTex->m_Levels, (u32)-1));
        pTex->Prepare();
        glx_AddTex(handle, pTex);
        numBytes += GCTextureSize(pTex->m_Format, pTex->m_Width, pTex->m_Height, pTex->m_Levels, (u32)-1);
    }

    tDebugPrintManager::Print(DC_GL, "glxTarget used %uKB for targets\n", numBytes >> 10);
}

/**
 * Offset/Address/Size: 0x868 | 0x801C2F44 | size: 0x8
 */
bool glx_GetSharedLock()
{
    return glx_SharedLock;
}

/**
 * Offset/Address/Size: 0x870 | 0x801C2F4C | size: 0xC
 */
void glx_UnlockSharedMemory()
{
    glx_SharedLock = false;
}

/**
 * Offset/Address/Size: 0x87C | 0x801C2F58 | size: 0xC
 */
void glx_LockSharedMemory()
{
    glx_SharedLock = true;
}

/**
 * Offset/Address/Size: 0x888 | 0x801C2F64 | size: 0x8
 */
u32 glx_GetSharedMemorySize()
{
    return glx_SharedSize;
}

/**
 * Offset/Address/Size: 0x890 | 0x801C2F6C | size: 0x8
 */
u32 glx_GetSharedMemory()
{
    return glx_SharedMemory;
}

/**
 * Offset/Address/Size: 0x898 | 0x801C2F74 | size: 0x3C
//  */
// void 0x8028D520..0x8028D524 | size: 0x4
// {
// }
