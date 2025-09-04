#include "Game/Camera/FaceCam.h"

/**
 * Offset/Address/Size: 0x12C | 0x801A8E6C | size: 0x40
 */
FaceCam::FaceCam(float distance)
{
    mpCharacter = nullptr;
    mDistance = distance;
}

/**
 * Offset/Address/Size: 0x10 | 0x801A8D50 | size: 0x11C
 */
void FaceCam::Update(float dt)
{
}

/**
 * Offset/Address/Size: 0x8 | 0x801A8D48 | size: 0x8
 */
const nlVector3& FaceCam::GetCameraPosition() const
{
    return mCameraPosition;
}

/**
 * Offset/Address/Size: 0x0 | 0x801A8D40 | size: 0x8
 */
const nlVector3& FaceCam::GetTargetPosition() const
{
    return mTargetPosition;
}
