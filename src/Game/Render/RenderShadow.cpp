#include "Game/Render/RenderShadow.h"

#include "Game/GL/GLInventory.h"
#include "NL/nlString.h"

extern GLInventory glInventory;

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
 */
void RenderShadowModel(unsigned long, glModel*, unsigned long)
{
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
void ShouldShadowBeUpdated(const ProjectedShadowParams&)
{
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
