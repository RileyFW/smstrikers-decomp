#include "NL/glx/glxSend.h"

#include "NL/glx/glxSend.h"
#include "dolphin/gx/GXGeometry.h"
#include "dolphin/gx/GXLighting.h"
#include "dolphin/gx/GXEnum.h"
#include "NL/gl/glLightUserData.h"
#include "types.h"

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

/**
 * Offset/Address/Size: 0x19BC | 0x801BB4BC | size: 0x1D0
 */
void glud_Skin(void*, const glModelPacket*)
{
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
void glx_SwitchRaster(const glModelPacket*)
{
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

/**
 * Offset/Address/Size: 0x4C94 | 0x801BE794 | size: 0x200
 */
void glx_SendReset()
{
}

/**
 * Offset/Address/Size: 0x4E94 | 0x801BE994 | size: 0x310
 */
void GetConstants()
{
}

/**
 * Offset/Address/Size: 0x51A4 | 0x801BECA4 | size: 0xAC
//  */
// void 0x8028D51C..0x8028D520 | size: 0x4
// {
// }
