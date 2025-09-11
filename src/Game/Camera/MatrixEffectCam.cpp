#pragma pool_data off

// #include "NL/math.h"

#include "NL/nlDLRing.h"

#include "Game/Camera/MatrixEffectCam.h"

#include "Game/CameraMan.h"
#include "Game/ReplayManager.h"

// static nlVector3 cameraPosition = { 0.0f, 0.0f, 0.0f };
static nlVector3 cameraPosition;
f32 sfDuration = 3.0f;
f32 sfSpinRate = 120.0f;
f32 sfDesiredDistanceFromTarget = 10.0f;
f32 sfDesiredHeightAboveTarget = 1.0f;
f32 sfZoomTime = 2.0f;

/**
 * Offset/Address/Size: 0x788 | 0x801A4B50 | size: 0x8C
 */
MatrixEffectCam::MatrixEffectCam()
{
    mfSpinDuration = sfDuration;
    mfPauseAfterSpin = 0.0f;
    mfZoomTime = sfZoomTime;
    mfDesiredDistanceFromTarget = sfDesiredDistanceFromTarget;
    mfDesiredHeightAboveTarget = sfDesiredHeightAboveTarget;
    mfSpinRate = sfSpinRate;
    mfFOV = 60.0f;
    mfElapsedTime = 0.0f;
    mFinishedCallback = NULL;
    mbFollowBall = false;
    mCurrentFilterDataIndex = 0;
    mbUseGameplayTransparencyFlags = false;
    nlVec3Set(mFilteredTargetPosition, 0.0f, 0.0f, 0.0f);
}

/**
 * Offset/Address/Size: 0x5C0 | 0x801A4988 | size: 0x1C8
 */
void MatrixEffectCam::Reset(const nlVector3& cameraStart, const nlVector3& beginTarget, const nlVector3& endTarget)
{
    mTargetPosition = beginTarget;
    mBeginTarget = mTargetPosition;
    mFinalTarget = endTarget;

    ReplayManager* rm = ReplayManager::Instance();
    // const nlVector3 p = rm->mTrack->pos;
    const nlVector3 p = { 0.0f, 0.0f, 0.0f }; // TODO: Get the position from the replay manager

    for (int i = 0; i < 10; ++i)
        mTargetFilterData[i] = p;

    mCurrentFilterDataIndex = 0;
    mFilteredTargetPosition.f.x = 0.f;
    mFilteredTargetPosition.f.y = 0.f;
    mFilteredTargetPosition.f.z = 0.f;

    nlVector3 dir;
    const nlVector3& tgt = GetTargetPosition();
    dir.f.x = cameraStart.f.x - tgt.f.x;
    dir.f.y = cameraStart.f.y - tgt.f.y;
    dir.f.z = cameraStart.f.z - tgt.f.z;

    nlCartesianToPolar(mCurrentPolarFromTarget, dir);

    mfCurrentCameraHeightAboveTarget = cameraStart.f.z - tgt.f.z;
    mfElapsedTime = 0.0f;

    cBaseCamera* top = nlDLRingGetStart<cBaseCamera>(cCameraManager::m_cameraStack);
    mfFOV = top->GetFOV();

    mbZoomingIn = (mCurrentPolarFromTarget.r > mfDesiredDistanceFromTarget) ? true : false;
}

/**
 * Offset/Address/Size: 0x1D8 | 0x801A45A0 | size: 0x3E8
 */
void MatrixEffectCam::Update(float)
{
}

/**
 * Offset/Address/Size: 0x148 | 0x801A4510 | size: 0x90
 */
const nlVector3& MatrixEffectCam::GetTargetPosition() const
{
    if (mbFollowBall)
    {
        mTargetPosition = mFilteredTargetPosition;
        return mFilteredTargetPosition;
    }

    float alpha = mfElapsedTime / mfSpinDuration;
    if (alpha > 1.0f)
    {
        alpha = 1.0f;
    }

    f32 temp_f3 = mBeginTarget.f.z;
    f32 temp_f4 = mBeginTarget.f.y;
    f32 temp_f5 = mBeginTarget.f.x;

    mTargetPosition.f.x = ((mFinalTarget.f.x - temp_f5) * alpha) + temp_f5;
    mTargetPosition.f.y = ((mFinalTarget.f.y - temp_f4) * alpha) + temp_f4;
    mTargetPosition.f.z = ((mFinalTarget.f.z - temp_f3) * alpha) + temp_f3;

    return mTargetPosition;
}

/**
 * Offset/Address/Size: 0xA8 | 0x801A4470 | size: 0xA0
 */
const nlVector3& MatrixEffectCam::GetCameraPosition() const
{
    nlVector3 targetPosition;
    nlPolarToCartesian(cameraPosition, mCurrentPolarFromTarget);
    cameraPosition.f.z = mfCurrentCameraHeightAboveTarget;
    targetPosition = GetTargetPosition();
    nlVec3Set(cameraPosition, cameraPosition.f.x + targetPosition.f.x, cameraPosition.f.y + targetPosition.f.y, cameraPosition.f.z + targetPosition.f.z);

    return cameraPosition;
}

/**
 * Offset/Address/Size: 0x88 | 0x801A4450 | size: 0x20
 */
void MatrixEffectCam::SetInitialDistance(float distance)
{
    mCurrentPolarFromTarget.r = distance;
    mbZoomingIn = mCurrentPolarFromTarget.r > mfDesiredDistanceFromTarget;
}

/**
 * Offset/Address/Size: 0x64 | 0x801A442C | size: 0x24
 */
void MatrixEffectCam::SetInitialAngle(float angle)
{
    mCurrentPolarFromTarget.a = 10430.378f * angle;
}

/**
 * Offset/Address/Size: 0x5C | 0x801A4424 | size: 0x8
 */
void MatrixEffectCam::SetInitialHeightAboveTarget(float distance)
{
    mfCurrentCameraHeightAboveTarget = distance;
}

/**
 * Offset/Address/Size: 0x0 | 0x801A43C8 | size: 0x5C
 */
MatrixEffectCam::~MatrixEffectCam()
{
}
