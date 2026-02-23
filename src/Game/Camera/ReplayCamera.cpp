#include "Game/Camera/ReplayCamera.h"
#include "types.h"

// /**
//  * Offset/Address/Size: 0x18 | 0x801ACB7C | size: 0x8
//  */
// void ReplayCamera::GetFOV() const
// {
// }

// /**
//  * Offset/Address/Size: 0x10 | 0x801ACB74 | size: 0x8
//  */
// void ReplayCamera::GetCameraPosition() const
// {
// }

// /**
//  * Offset/Address/Size: 0x8 | 0x801ACB6C | size: 0x8
//  */
// void ReplayCamera::GetTargetPosition() const
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x801ACB64 | size: 0x8
//  */
// void ReplayCamera::GetType()
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x801AC980 | size: 0x1E4
//  */
// void BasicString<char, Detail::TempStringAllocator>::AppendInPlace<Detail::TempStringAllocator>(const BasicString<char, Detail::TempStringAllocator>&)
// {
// }

/**
 * Offset/Address/Size: 0x1C78 | 0x801AC97C | size: 0x4
 */
void ReplayCamera::UpdateTweakMode()
{
    // EMPTY
}

/**
 * Offset/Address/Size: 0x1BC8 | 0x801AC8CC | size: 0xB0
 */
ReplayCamera::ReplayCamera()
{
    mDeltaFov = 0.0f;
    mFov = 50.0f;
    mSideOfInterest = 0;
    mNoDampenForOneUpdate = false;
    mFrozen = false;
    mFocus = 1;
    mCamPos = REPLAY_CAMERA_POSITION_SIDELINE;
    mViewMatrix.SetIdentity();
    nlVec3Set(mPosition, 0.0f, 0.0f, 2.0f);
    nlVec3Set(mLookAt, 0.0f, 0.0f, 1.0f);
}

// /**
//  * Offset/Address/Size: 0x1B88 | 0x801AC88C | size: 0x40
//  */
const nlMatrix4& ReplayCamera::GetViewMatrix() const
{
    glMatrixLookAt(*(nlMatrix4*)&mViewMatrix, mPosition, mLookAt, mUpVector);
    return mViewMatrix;
};

/**
 * Offset/Address/Size: 0x1B84 | 0x801AC888 | size: 0x4
 */
void ReplayCamera::Update(float)
{
    // EMPTY
}

/**
 * Offset/Address/Size: 0x16E8 | 0x801AC3EC | size: 0x49C
 */
void ReplayCamera::ManualUpdate(float)
{
}

/**
 * Offset/Address/Size: 0x16E0 | 0x801AC3E4 | size: 0x8
 */
void ReplayCamera::SetSideOfInterest(int sideOfInterest)
{
    mSideOfInterest = sideOfInterest;
}

/**
 * Offset/Address/Size: 0x1668 | 0x801AC36C | size: 0x78
 */
void ReplayCamera::CutTo(ReplayCameraPosition camPos)
{
    mFrozen = false;
    mNoDampenForOneUpdate = true;
    mCamPos = camPos;
    mPosition = GetPosition(mCamPos, -1.0f);
    mFov = GetFov(mCamPos);
}

/**
 * Offset/Address/Size: 0x11AC | 0x801ABEB0 | size: 0x4BC
 */
float ReplayCamera::GetFov(ReplayCameraPosition) const
{
    FORCE_DONT_INLINE;
    return mFov;
}

/**
 * Offset/Address/Size: 0x0 | 0x801AAD04 | size: 0x11AC
 */
nlVector3 ReplayCamera::GetPosition(ReplayCameraPosition, float) const
{
    FORCE_DONT_INLINE;
    return mPosition;
}
