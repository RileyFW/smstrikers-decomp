#include "NL/glx/glxSend.h"

#include "NL/glx/glxSend.h"
#include "dolphin/gx/GXGeometry.h"
#include "dolphin/gx/GXLighting.h"
#include "dolphin/gx/GXEnum.h"
#include "dolphin/gx/GXTev.h"
#include "dolphin/gx/GXTransform.h"
#include "dolphin/mtx.h"
#include "NL/gl/glLightUserData.h"
#include "NL/gl/glMatrix.h"
#include "NL/gl/glState.h"
#include "NL/gl/glUserData.h"
#include "NL/glx/glxGX.h"
#include "NL/glx/glxMatrix.h"
#include "NL/nlColour.h"
#include "NL/platvmath.h"
#include "types.h"
#include <string.h>

// Forward declarations for global variables (these would need to be declared elsewhere)
extern bool glx_ReloadPointLights;
extern bool g_bAllowLighting;
extern u32 glx_prevLightMask;
extern u32 glx_NumIndices;

static u32 gxLights[4] = {
    0x00000001,
    0x00000002,
    0x00000004,
    0x00000008
};

/**
 * Offset/Address/Size: 0x0 | 0x801B9B00 | size: 0x538
 */
void glx_SendFrame_cb(eGLView, unsigned long, const glModelPacket*)
{
}

/**
 * Offset/Address/Size: 0x538 | 0x801BA038 | size: 0xB20
 */
void glx_DrawPacket(const glModelPacket*)
{
}

/**
 * Offset/Address/Size: 0x1058 | 0x801BAB58 | size: 0x964
 */
void glx_SwitchUserData(const glModelPacket*)
{
    FORCE_DONT_INLINE;
}

static eGLView prev_view;
static u8 glx_InvXpose;
static u8 glx_InvXposeChar;
static bool g_bFastSkinPath;
static bool g_bMtxSkinMath;
static bool glx_IsCoPlanarView;
static Mtx gx_mview;
static nlMatrix4 mview;

struct GLSkinUserData
{
    int reg;
    float mat[12];
};

/**
 * Offset/Address/Size: 0x19BC | 0x801BB4BC | size: 0x1D0
 */
void glud_Skin(void* pData, const glModelPacket* pPacket)
{
    float mSkinConcat[3][4];
    float mNormFast[3][4];
    nlMatrix4 nlMat;
    float tempMtx[3][4];
    float gxMat[3][4];
    float mNorm[3][4];
    u32 numMatrices;
    u32 i;
    int slot;
    GLSkinUserData* pSkin;
    u8 bInvXpose;

    numMatrices = *(u32*)pData;
    pSkin = (GLSkinUserData*)((u8*)pData + 4);

    if (prev_view == GLV_Characters)
        bInvXpose = glx_InvXposeChar;
    else
        bInvXpose = glx_InvXpose;

    if (g_bFastSkinPath && g_bMtxSkinMath && !glx_IsCoPlanarView && pPacket->state.matrix == glGetIdentityMatrix())
    {
        // Fast path - use gx_mview directly
        for (i = 0; i < numMatrices; i++, pSkin++)
        {
            PSMTXConcat(gx_mview, *(const Mtx*)pSkin->mat, mSkinConcat);
            slot = pSkin->reg + 99;
            GXLoadPosMtxImm(mSkinConcat, (u32)slot);
            if (bInvXpose)
            {
                PSMTXInvXpose(mSkinConcat, mNormFast);
                GXLoadNrmMtxImm(mNormFast, (u32)slot);
            }
            else
            {
                GXLoadNrmMtxImm(mSkinConcat, (u32)slot);
            }
        }
    }
    else
    {
        // Slow path
        for (i = 0; i < numMatrices; i++, pSkin++)
        {
            if (g_bMtxSkinMath && !glx_IsCoPlanarView)
            {
                glxCopyMatrix(gxMat, *(nlMatrix4*)pPacket->state.matrix);
                PSMTXConcat(gxMat, gx_mview, tempMtx);
                PSMTXConcat(tempMtx, *(const Mtx*)pSkin->mat, mSkinConcat);
            }
            else
            {
                nlMultMatrices(nlMat, *(nlMatrix4*)pPacket->state.matrix, mview);
                glxCopyMatrix(tempMtx, nlMat);
                PSMTXConcat(tempMtx, *(const Mtx*)pSkin->mat, mSkinConcat);
            }
            slot = pSkin->reg + 99;
            GXLoadPosMtxImm(mSkinConcat, (u32)slot);
            if (bInvXpose)
            {
                PSMTXInvXpose(mSkinConcat, mNorm);
                GXLoadNrmMtxImm(mNorm, (u32)slot);
            }
            else
            {
                GXLoadNrmMtxImm(mSkinConcat, (u32)slot);
            }
        }
    }
}

/**
 * Offset/Address/Size: 0x1B8C | 0x801BB68C | size: 0x320
 */
void glud_Specular(void*)
{
}

struct LightData
{
    u32 numLights;
    GLLightUserData* lights;
};

/**
 * Offset/Address/Size: 0x1EAC | 0x801BB9AC | size: 0xC0
 */
void glud_Light(void* pUserData)
{
    LightData* lightData = (LightData*)pUserData;
    u32 lightMask;
    s32 light_id;
    GLLightUserData* pLight;
    GLLightUserData* pEndLight;

    if (lightData->numLights != 0)
    {
        pLight = (GLLightUserData*)((u8*)pUserData + 4);
        light_id = 0;
        lightMask = 0;
        pEndLight = &pLight[lightData->numLights];
        while (pLight < pEndLight)
        {
            if (light_id >= 4)
            {
                break;
            }
            lightMask |= gxLights[light_id];
            if (glx_ReloadPointLights != 0)
            {
                glx_LoadLight(pLight, (GXLightID)gxLights[light_id]);
            }
            pLight++;
            light_id += 1;
        }

        glx_ReloadPointLights = 0;
        if (g_bAllowLighting != 0)
        {
            glx_prevLightMask = lightMask;
            GXSetChanCtrl(GX_COLOR0, GX_TRUE, GX_SRC_REG, GX_SRC_VTX, lightMask, GX_DF_CLAMP, GX_AF_SPOT);
        }
    }
}

/**
 * Offset/Address/Size: 0x1F6C | 0x801BBA6C | size: 0x334
 */
void glx_LoadLight(GLLightUserData* pLight, _GXLightID lightId)
{
    FORCE_DONT_INLINE;
}

static u32 gx_texattr[] = {
    13,
    14,
    15,
    16,
    17,
    18,
    19,
    20,
};

/**
 * Offset/Address/Size: 0x22A0 | 0x801BBDA0 | size: 0x194
 */
void glx_SwitchStreams(const glModelPacket* pPacket)
{
    static u32 gx_streams[] = {
        9,
        10,
        11,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        26,
        0xFF,
    };

    glModelStream* stream = pPacket->streams;
    glModelStream* end = stream + pPacket->numStreams;

    GXClearVtxDesc();
    glx_NumIndices = 0;

    while (stream < end)
    {
        if (stream->id == 12)
        {
            GXSetVtxDesc(GX_VA_PNMTXIDX, GX_DIRECT);
            glx_NumIndices++;
            stream++;
            continue;
        }

        s32 attr = gx_streams[stream->id];
        if (attr == 0xFF)
        {
            attr = gx_texattr[stream->id - 3];
        }

        if (attr != 0xFF)
        {
            if (stream->address == 0)
            {
                GXSetVtxDesc((GXAttr)attr, GX_DIRECT);
            }
            else
            {
                GXSetArray((GXAttr)attr, (void*)stream->address, stream->stride);
                GXSetVtxDesc((GXAttr)attr, GX_INDEX16);
                glx_NumIndices++;
            }
        }

        if (stream->id == 1)
        {
            if (stream->stride == 12)
            {
                GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_NRM_XYZ, GX_F32, 0);
            }
            else
            {
                GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_NRM_XYZ, GX_S8, 6);
            }
        }

        if (stream->id == 0)
        {
            if (stream->stride == 12)
            {
                GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
            }
            else
            {
                GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_S16, 8);
            }
        }

        stream++;
    }
}

/**
 * Offset/Address/Size: 0x2434 | 0x801BBF34 | size: 0x25C
 */
void glx_SwitchRaster(const glModelPacket* p)
{
    static _GXCompare gx_DepthFunc[] = {
        GX_ALWAYS,
        GX_LEQUAL,
        GX_EQUAL,
        GX_LESS,
    };
    static _GXCompare gx_AlphaTest[] = {
        GX_ALWAYS,
        GX_GREATER,
    };
    static _GXCullMode gx_Culling[] = {
        GX_CULL_NONE,
        GX_CULL_FRONT,
        GX_CULL_BACK,
        GX_CULL_ALL,
    };

    unsigned long DepthTest;
    unsigned long DepthWrite;
    int DepthFunc;
    int AlphaTest;
    unsigned long AlphaTestRef;
    unsigned long AlphaBlend;
    int Culling;
    int ColourWrite;

    glUnHandleizeRasterState(p->state.raster);

    DepthTest = glGetRasterState(GLS_DepthTest);
    DepthWrite = glGetRasterState(GLS_DepthWrite);
    DepthFunc = glGetRasterState(GLS_DepthFunc);
    gxSetZMode((bool)DepthTest, gx_DepthFunc[DepthFunc], (bool)DepthWrite);

    AlphaTest = glGetRasterState(GLS_AlphaTest);
    AlphaTestRef = glGetRasterState(GLS_AlphaTestRef);
    gxSetAlphaCompare(gx_AlphaTest[AlphaTest], (unsigned char)AlphaTestRef);

    if (AlphaTest != 0)
    {
        gxSetZCompLoc(false);
    }
    else
    {
        gxSetZCompLoc(true);
    }

    AlphaBlend = glGetRasterState(GLS_AlphaBlend);

    switch (AlphaBlend)
    {
    case 0:
        gxSetBlendMode(false, (_GXBlendFactor)1, (_GXBlendFactor)0, false);
        break;
    case 1:
        gxSetBlendMode(true, (_GXBlendFactor)4, (_GXBlendFactor)5, false);
        break;
    case 2:
        gxSetBlendMode(true, (_GXBlendFactor)1, (_GXBlendFactor)1, false);
        break;
    case 3:
        gxSetBlendMode(true, (_GXBlendFactor)4, (_GXBlendFactor)1, false);
        break;
    case 4:
        gxSetBlendMode(true, (_GXBlendFactor)2, (_GXBlendFactor)0, false);
        break;
    case 5:
        gxSetBlendMode(true, (_GXBlendFactor)3, (_GXBlendFactor)1, false);
        break;
    case 6:
        gxSetBlendMode(true, (_GXBlendFactor)1, (_GXBlendFactor)0, false);
        break;
    case 7:
        gxSetBlendMode(true, (_GXBlendFactor)2, (_GXBlendFactor)0, true);
        break;
    }

    Culling = glGetRasterState(GLS_Culling);
    gxSetCullMode(gx_Culling[Culling]);

    ColourWrite = glGetRasterState(GLS_ColourWrite);
    switch (ColourWrite)
    {
    case 0:
        gxSetColourUpdate(false);
        gxSetAlphaUpdate(false);
        break;
    case 1:
        gxSetColourUpdate(true);
        gxSetAlphaUpdate(false);
        break;
    case 2:
        gxSetColourUpdate(false);
        gxSetAlphaUpdate(true);
        break;
    case 3:
        gxSetColourUpdate(true);
        if (prev_view == GLV_ShadowTexture)
        {
            gxSetAlphaUpdate(true);
        }
        else
        {
            gxSetAlphaUpdate(false);
        }
        break;
    }
}

/**
 * Offset/Address/Size: 0x2690 | 0x801BC190 | size: 0x48C
 */
void glx_SwitchTextureState(const glModelPacket*)
{
}

/**
 * Offset/Address/Size: 0x2B1C | 0x801BC61C | size: 0x2154
 */
void glx_SwitchTexConfig(const glModelPacket*)
{
}

/**
 * Offset/Address/Size: 0x4C70 | 0x801BE770 | size: 0x24
 */
void glx_SendEnd()
{
    glx_SwitchUserData(nullptr);
}

static GXTexObj glx_texobj[6];
static GXTlutObj glx_tlutobj[6];
static u32 glx_texture[6];
static u32 glx_texdirty;
static u32 gx_vtxfmt;
static nlColour world_ambient;
static nlColour nlBlack;
static nlColour nlWhite;
static u32 glx_prevSpecMask;
static u32 glx_DirtyFlags;
static bool glx_ReloadSpecLights;
static bool glx_allowSpecular;
static bool glx_envdiffuse;
static bool glx_mobilediffuse;
static bool glx_constantcolour;
static bool glx_viewport;
static bool glx_CoPlanar;
static bool glx_translucent;
static bool glx_norasterizedalpha;
static s32 glx_RasterizedAlphaStage;
static s32 glx_RasterizedAlphaArg;
static s32 glx_GlossMapStage;
static s32 glx_GlossMapCoord;
static bool glx_NoFog;

/**
 * Offset/Address/Size: 0x4C94 | 0x801BE794 | size: 0x200
 * TODO: 99.8% match - 4 register diffs (first loop counter r28 vs r31), 1 label diff (@142 vs @419)
 */
void glx_SendReset()
{
    prev_view = GLV_Num;

    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR1, GX_CLR_RGBA, GX_RGBA8, 0);

    for (s32 i = 0; i < 6; i++)
    {
        GXSetVtxAttrFmt(GX_VTXFMT0, (GXAttr)(GX_VA_TEX0 + i), GX_TEX_ST, GX_S16, 10);
    }

    glx_texdirty = 0;

    for (s32 i = 0; i < 6; i++)
    {
        memset(&glx_texobj[i], 0, sizeof(GXTexObj));
        memset(&glx_tlutobj[i], 0, sizeof(GXTlutObj));
        glx_texture[i] = 0;
    }

    gx_vtxfmt = 0;

    GetConstants();

    {
        nlColour amb;
        nlColour temp = {};
        nlColourSet(temp, world_ambient.c[0], world_ambient.c[1], world_ambient.c[2], world_ambient.c[3]);
        amb = temp;
        gxSetChanAmbColour(0, amb);
    }
    gxSetChanMatColour(0, nlWhite);
    gxSetChanAmbColour(1, nlBlack);
    gxSetChanMatColour(1, nlWhite);

    GXSetTevSwapModeTable(GX_TEV_SWAP3, GX_CH_RED, GX_CH_RED, GX_CH_RED, GX_CH_RED);

    if (glx_prevSpecMask != 0)
    {
        gxSetNumChans(1);
        GXSetChanCtrl(GX_COLOR1, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, glx_prevSpecMask, GX_DF_NONE, GX_AF_NONE);
    }

    glx_DirtyFlags = 0;
    glx_ReloadPointLights = true;
    glx_ReloadSpecLights = true;
    glx_prevLightMask = 0;
    glx_prevSpecMask = 0;
    glx_allowSpecular = 0;
    glx_envdiffuse = false;
    glx_mobilediffuse = false;
    glx_constantcolour = false;
    glx_viewport = false;
    glx_CoPlanar = false;

    gxSetCoPlanar(false);

    glx_translucent = false;
    glx_norasterizedalpha = false;
    glx_RasterizedAlphaStage = -1;
    glx_RasterizedAlphaArg = -1;
    glx_GlossMapStage = -1;
    glx_GlossMapCoord = -1;
    glx_NoFog = false;
}

/**
 * Offset/Address/Size: 0x4E94 | 0x801BE994 | size: 0x310
 */
void GetConstants()
{
    FORCE_DONT_INLINE;
}

/**
 * Offset/Address/Size: 0x51A4 | 0x801BECA4 | size: 0xAC
//  */
// void 0x8028D51C..0x8028D520 | size: 0x4
// {
// }
