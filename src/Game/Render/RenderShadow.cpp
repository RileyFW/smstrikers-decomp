#include "Game/Render/RenderShadow.h"

#include "Game/GL/GLInventory.h"
#include "Game/WorldManager.h"
#include "NL/nlString.h"

extern GLInventory glInventory;
extern unsigned long ResolvedWhiteTexture;

static u8 g_bPreview;
static unsigned long FourTexture;
static glModel* pCylinder;
static glModel* pBox;
int MaxProjectedShadows;

// /**
//  * Offset/Address/Size: 0x1734 | 0x80124768 | size: 0x7C
//  */
// void 0x8028D2CC..0x8028D2D0 | size: 0x4
// {
// }

/**
 * Offset/Address/Size: 0x16B4 | 0x801246E8 | size: 0x80
 */
void ShadowStartup()
{
    pCylinder = glInventory.GetModel(nlStringHash("debug/cylinder"));
    pBox = glInventory.GetModel(nlStringHash("debug/box"));
    const nlVector4& result = glConstantGet("target/pshadow_num");
    MaxProjectedShadows = (int)result.f.x;
}

/**
 * Offset/Address/Size: 0x1558 | 0x8012458C | size: 0x15C
 * TODO: 97.13% match - preview loop pkt register r28 vs target r26,
 *       and MWCC schedules li r3 after conditional li r4 for first glSetRasterState(GLS_Culling, v).
 */
void RenderShadowModel(unsigned long flags, glModel* model, unsigned long matrix)
{
    unsigned long fourTex;
    eGLView view = GLV_Shadow1;
    if (flags & 1)
        view = GLV_Shadow0;

    if (matrix == 0xFFFFFFFF)
        matrix = glGetIdentityMatrix();

    if (g_bPreview) {
        glModelPacket* pkt = model->packets;
        while (pkt < model->packets + model->numPackets) {
            glModelPacket* dup = glModelPacketDup(pkt, true);
            dup->state.texture[0] = ResolvedWhiteTexture;
            dup->state.matrix = matrix;
            glViewAttachPacket(GLV_Unshadowed, dup);
            pkt++;
        }
    } else {
        glModelPacket* pkt;
        glModelPacket* dup;
        s32 pass = 0;
        fourTex = FourTexture;
        do {
            pkt = model->packets;
            while (pkt < model->packets + model->numPackets) {
                dup = glModelPacketDup(pkt, true);
                dup->state.texture[0] = fourTex;
                dup->state.matrix = matrix;
                glUnHandleizeRasterState(dup->state.raster);

                u32 v = 1;
                if (pass == 0) v = 2;
                glSetRasterState(GLS_Culling, v);
                glSetRasterState(GLS_DepthWrite, 0);

                glSetRasterState(GLS_AlphaBlend, (pass == 0) ? 2 : 7);
                glSetRasterState(GLS_ColourWrite, 2);

                dup->state.raster = glHandleizeRasterState();
                glViewAttachPacket(view, dup);
                pkt++;
            }
            pass++;
        } while (pass < 2);
    }
}

/**
 * Offset/Address/Size: 0x14DC | 0x80124510 | size: 0x7C
 */
void GetShadowPartitionIndex()
{
    static s32 index = 0;
    static s32 prevFrame = 0;

    s32 currentFrame = glGetCurrentFrame();
    if ((u32)prevFrame != (u32)currentFrame)
    {
        prevFrame = currentFrame;
        index = 0;
    }

    index++;
}

/**
 * Offset/Address/Size: 0x140C | 0x80124440 | size: 0xD0
 */
u8 ShouldShadowBeUpdated(const ProjectedShadowParams& params)
{
    float fRadius = 2.0f * params.fRadius;
    nlMatrix4 mWorld;
    mWorld.SetIdentity();
    mWorld.f.m41 = params.vPosition.f.x;
    mWorld.f.m42 = params.vPosition.f.y;
    mWorld.f.m43 = params.vPosition.f.z;
    mWorld.f.m44 = 1.0f;
    mWorld.f.m43 += 0.5f * params.fHeight;

    u8 isVisible = WorldManager::s_World->IsSphereInFrustum(mWorld, fRadius);
    u32 interval;
    if (isVisible) {
        interval = params.nVisibleInterval;
    } else {
        interval = params.nInvisibleInterval;
    }

    u32 currentFrame = (u32)glGetCurrentFrame();
    u32 frame = (u32)params.nPartitionIndex + currentFrame;
    if (frame % interval != 0) {
        return 0;
    }
    return 1;
}

/**
 * Offset/Address/Size: 0xF9C | 0x80123FD0 | size: 0x470
 */
void RenderCharacterIntoTexture(const ProjectedShadowParams&)
{
}

/**
 * Offset/Address/Size: 0xF24 | 0x80123F58 | size: 0x78
 */
void SetCharacterShadowUpdated(int index, bool updated)
{
    char buffer[32];
    nlSNPrintf(buffer, 32, "target/pshadow_updated%02d", index);

    nlVector4 v;
    v.f.x = updated ? 1.0f : 0.0f;
    v.f.y = 0.0f;
    v.f.z = 0.0f;
    v.f.w = 0.0f;

    glConstantSet(buffer, v);
}

/**
 * Offset/Address/Size: 0xB44 | 0x80123B78 | size: 0x3E0
 */
void SubdivideAndRender(glQuad3&, eGLView)
{
}

/**
 * Offset/Address/Size: 0x750 | 0x80123784 | size: 0x3F4
 */
void RenderBlobShadow(const nlVector3&, const nlVector3*, int, const int*, const nlColour*)
{
}

/**
 * Offset/Address/Size: 0x0 | 0x80123034 | size: 0x750
 */
void RenderProjectedShadow(const ProjectedShadowParams&)
{
}
