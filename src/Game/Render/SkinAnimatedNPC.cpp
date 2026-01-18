#include "Game/Render/SkinAnimatedNPC.h"
#include "types.h"

extern float GetPlanarShadowOpacity();
extern void DrawPlanarShadow(const glModel*, const nlMatrix4&, float, bool, bool, bool, unsigned long);

/**
 * Offset/Address/Size: 0x60C | 0x80164FB0 | size: 0xC0
 */
SkinAnimatedNPC::SkinAnimatedNPC(cSHierarchy&, int)
{
}

/**
 * Offset/Address/Size: 0x4D8 | 0x80164E7C | size: 0x134
 */
SkinAnimatedNPC::~SkinAnimatedNPC()
{
}

/**
 * Offset/Address/Size: 0x474 | 0x80164E18 | size: 0x64
 */
void SkinAnimatedNPC::Update(float dt)
{
    mpPoseTree = mpPoseTree->Update(dt);
    mpPoseAccumulator->InitAccumulators();
    mpPoseTree->Evaluate(1.0f, mpPoseAccumulator);
}

/**
 * Offset/Address/Size: 0x424 | 0x80164DC8 | size: 0x50
 */
void SkinAnimatedNPC::Render()
{
    mpPoseAccumulator->BuildNodeMatrices(mWorldMatrix);
    RenderFromReplay(*mpPoseAccumulator, &mWorldMatrix);
}

/**
 * Offset/Address/Size: 0x398 | 0x80164D3C | size: 0x8C
 */
void SkinAnimatedNPC::RenderFromReplay(const cPoseAccumulator&, const nlMatrix4*)
{
}

/**
 * Offset/Address/Size: 0x240 | 0x80164BE4 | size: 0x158
 */
void SkinAnimatedNPC::SendToGL() const
{
}

/**
 * Offset/Address/Size: 0x1A4 | 0x80164B48 | size: 0x9C
 */
void SkinAnimatedNPC::DrawShadow(const cPoseAccumulator&, const nlMatrix4&)
{
}

/**
 * Offset/Address/Size: 0x74 | 0x80164A18 | size: 0x130
 */
void SkinAnimatedNPC::SetAnimState(cSAnim& pAnim, float fBlendTime, ePlayMode ePlayMode)
{
    FORCE_DONT_INLINE
}

/**
 * Offset/Address/Size: 0x0 | 0x801649A4 | size: 0x74
 */
void SkinAnimatedNPC::DrawShadow(const glModel* pModel, const nlMatrix4& matrix)
{
    glModel* dup = glModelDupNoStreams(pModel, true, false);
    float opacity = GetPlanarShadowOpacity();
    DrawPlanarShadow(dup, matrix, opacity, false, true, true, (unsigned long)this);
}
