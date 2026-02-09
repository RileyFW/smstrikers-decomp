#include "Game/Drawable/DrawablePowerup.h"

/**
 * Offset/Address/Size: 0x0 | 0x8011EC74 | size: 0xF8
 * TODO: 68.5% match - MWCC CSE prevents second blendFactors[2] load and second
 * 1.0f-t subtraction. Target has two separate lfs from 8(r4) and two fsubs for
 * invT, causing FPR register renaming (f5/f6/f9/f8 vs f7/f8). All logic correct.
 */
void DrawablePowerup::Blend(const float* blendFactors, const DrawablePowerup& lhs, const DrawablePowerup& rhs)
{
    mVisible = lhs.mVisible && rhs.mVisible;
    if (!mVisible)
        return;

    float t = blendFactors[2];
    float invT = 1.0f - t;
    mType = lhs.mType;
    mScale = invT * lhs.mScale + t * rhs.mScale;
    mRadius = lhs.mRadius;
    mOrientation = lhs.mOrientation + (s16)((s16)(rhs.mOrientation - lhs.mOrientation) * t);
    mPosition.f.x = invT * lhs.mPosition.f.x + t * rhs.mPosition.f.x;
    mPosition.f.y = invT * lhs.mPosition.f.y + t * rhs.mPosition.f.y;
    mPosition.f.z = invT * lhs.mPosition.f.z + t * rhs.mPosition.f.z;
}

/**
 * Offset/Address/Size: 0xF8 | 0x8011ED6C | size: 0x27C
 */
void DrawablePowerup::Render(int) const
{
}

/**
 * Offset/Address/Size: 0x374 | 0x8011EFE8 | size: 0x190
 */
void DrawablePowerup::Grab(int)
{
}

/**
 * Offset/Address/Size: 0x504 | 0x8011F178 | size: 0x1A0
 */
void DrawShadow(float, float, float, float)
{
}

/**
 * Offset/Address/Size: 0x0 | 0x8011F318 | size: 0x88
 */
// void DrawablePowerup::Replay<LoadFrame>(LoadFrame&)
// {
// }

/**
 * Offset/Address/Size: 0x88 | 0x8011F3A0 | size: 0x88
 */
// void DrawablePowerup::Replay<SaveFrame>(SaveFrame&)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8011F428 | size: 0x8
//  */
// DrawableModel* DrawableObject::AsDrawableModel()
// {
//     return NULL;
// }

/**
 * Offset/Address/Size: 0x0 | 0x8011F430 | size: 0x64
 */
// void Replayable<3, SaveFrame, bool>(SaveFrame&, bool&)
// {
// }

/**
 * Offset/Address/Size: 0x64 | 0x8011F494 | size: 0x50
 */
// void Replayable<3, SaveFrame, char>(SaveFrame&, char&)
// {
// }

/**
 * Offset/Address/Size: 0xB4 | 0x8011F4E4 | size: 0x50
 */
// void Replayable<3, SaveFrame, unsigned short>(SaveFrame&, unsigned short&)
// {
// }

/**
 * Offset/Address/Size: 0x104 | 0x8011F534 | size: 0x50
 */
// void Replayable<3, SaveFrame, nlVector3>(SaveFrame&, nlVector3&)
// {
// }

/**
 * Offset/Address/Size: 0x154 | 0x8011F584 | size: 0x50
 */
// void Replayable<3, SaveFrame, float>(SaveFrame&, float&)
// {
// }

/**
 * Offset/Address/Size: 0x1A4 | 0x8011F5D4 | size: 0x7C
 */
// void Replayable<3, LoadFrame, bool>(LoadFrame&, bool&)
// {
// }

/**
 * Offset/Address/Size: 0x220 | 0x8011F650 | size: 0x54
 */
// void Replayable<3, LoadFrame, char>(LoadFrame&, char&)
// {
// }

/**
 * Offset/Address/Size: 0x274 | 0x8011F6A4 | size: 0x54
 */
// void Replayable<3, LoadFrame, unsigned short>(LoadFrame&, unsigned short&)
// {
// }

/**
 * Offset/Address/Size: 0x2C8 | 0x8011F6F8 | size: 0x54
 */
// void Replayable<3, LoadFrame, nlVector3>(LoadFrame&, nlVector3&)
// {
// }

/**
 * Offset/Address/Size: 0x31C | 0x8011F74C | size: 0x54
 */
// void Replayable<3, LoadFrame, float>(LoadFrame&, float&)
// {
// }
