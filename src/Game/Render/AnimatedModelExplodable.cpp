#include "Game/Render/AnimatedModelExplodable.h"

// /**
//  * Offset/Address/Size: 0x70 | 0x80158C4C | size: 0x128
//  */
// void 0x8028D2FC..0x8028D300 | size: 0x4
// {
// }

/**
 * Offset/Address/Size: 0x44 | 0x80158C20 | size: 0x2C
 */
// void nlListAddEnd<SidelineExplodableNode>(SidelineExplodableNode**, SidelineExplodableNode**, SidelineExplodableNode*)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x80158BDC | size: 0x44
//  */
// void nlListRemoveStart<SidelineExplodableNode>(SidelineExplodableNode**, SidelineExplodableNode**)
// {
// }

/**
 * Offset/Address/Size: 0x1C4 | 0x80158B30 | size: 0xAC
 */
void AnimatedModelExplodable::CleanUp()
{
}

/**
 * Offset/Address/Size: 0xA8 | 0x80158A14 | size: 0x11C
 */
AnimatedModelExplodable::AnimatedModelExplodable(AnimatedModelExplodableCategory, SkinAnimatedNPC*)
{
}

/**
 * Offset/Address/Size: 0x48 | 0x801589B4 | size: 0x60
 */
AnimatedModelExplodable::~AnimatedModelExplodable()
{
}

/**
 * Offset/Address/Size: 0x30 | 0x8015899C | size: 0x18
 */
void AnimatedModelExplodable::GetCategoryData() const
{
}

/**
 * Offset/Address/Size: 0x24 | 0x80158990 | size: 0xC
 */
const nlMatrix4& AnimatedModelExplodable::GetWorldMatrix() const
{
    return mpAnimatedNPC->mWorldMatrix;
}

/**
 * Offset/Address/Size: 0x18 | 0x80158984 | size: 0xC
 */
void AnimatedModelExplodable::SetUnexplodedModelVisibility(bool)
{
}

/**
 * Offset/Address/Size: 0x0 | 0x8015896C | size: 0x18
 */
bool AnimatedModelExplodable::LoadGeometry()
{
    FORCE_DONT_INLINE;
    return false;
}
