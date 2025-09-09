#pragma pool_data off
#include "Game/Camera/MatrixEffectCam.h"

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
void MatrixEffectCam::Reset(const nlVector3& v3InitialCameraPosition, const nlVector3& beginTarget, const nlVector3& endTarget)
{
    f32 sp1C;
    f32 sp18;
    f32 sp14;
    f32 sp10;
    f32 spC;
    f32 sp8;
    f32* temp_r3_2;
    f32 temp_r0;
    f32 temp_r3;
    f32 temp_r4;
    f32 temp_r5;
    void* temp_r6;

    mTargetPosition = v3InitialCameraPosition; // nlVec3Set(mTargetPosition, arg1->unk0, arg1->unk4, arg2->unk4);

    // this->unk4C = arg1->unk0;
    // this->unk50 = arg1->unk4;
    // temp_r3 = arg2->unk4;
    // this->unk54 = arg1->unk8;

    mBeginTarget = mTargetPosition;
    // this->unk40 = this->unk4C;
    // this->unk44 = this->unk50;
    // this->unk48 = this->unk54;

    mFinalTarget = endTarget;
    // this->unk34 = arg2->unk0;
    // this->unk38 = temp_r3;
    // this->unk3C = arg2->unk8;

    // void* tmp = ReplayManager::Instance().GetCameraPosition(mTargetPosition);

    // temp_r6 = Instance__13ReplayManagerFv((bitwise ReplayManager*)temp_r3)->unk5048;
    // temp_r5 = temp_r6->unk20;
    // temp_r4 = temp_r6->unk24;
    // temp_r0 = temp_r6->unk28;
    // sp14 = temp_r5;
    // this->unkB4 = temp_r5;
    // this->unkB8 = temp_r4;
    // this->unkBC = temp_r0;
    // this->unkC0 = temp_r5;
    // this->unkC4 = temp_r4;
    // this->unkC8 = temp_r0;
    // this->unkCC = temp_r5;
    // this->unkD0 = temp_r4;
    // this->unkD4 = temp_r0;
    // this->unkD8 = temp_r5;
    // this->unkDC = temp_r4;
    // this->unkE0 = temp_r0;
    // this->unkE4 = temp_r5;
    // this->unkE8 = temp_r4;
    // this->unkEC = temp_r0;
    // this->unkF0 = temp_r5;
    // this->unkF4 = temp_r4;
    // this->unkF8 = temp_r0;
    // this->unkFC = temp_r5;
    // this->unk100 = temp_r4;
    // this->unk104 = temp_r0;
    // this->unk108 = temp_r5;
    // this->unk10C = temp_r4;
    // this->unk110 = temp_r0;
    // this->unk114 = temp_r5;
    // this->unk118 = temp_r4;
    // this->unk11C = temp_r0;
    // this->unk120 = temp_r5;
    // this->unk124 = temp_r4;
    // this->unk128 = temp_r0;
    // this->unk130 = temp_r5;
    // this->unk134 = temp_r4;
    // this->unk138 = temp_r0;
    // sp18 = temp_r4;
    // sp1C = temp_r0;
    // temp_r3_2 = this->vtable0->GetTargetPosition(this);
    // sp10 = arg0->unk8 - temp_r3_2->unk8;
    // spC = arg0->unk4 - temp_r3_2->unk4;
    // sp8 = arg0->unk0 - temp_r3_2->unk0;
    // nlCartesianToPolar__FR7nlPolarRC9nlVector3(&this->unk9C, &sp8);
    // this->unkA4 = arg0->unk8 - temp_r3_2->unk8;
    // this->unkA8 = 0.0f;
    // this->unk98 = (*nlDLRingGetStart<11cBaseCamera> __FP11cBaseCamera(m_cameraStack__14cCameraManager.unk0))->unk18();
    // this->unkB0 = this->unkA0 > this->unk28;
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

    float var_f6 = mfElapsedTime / mfSpinDuration;
    if (var_f6 > 1.0f)
    {
        var_f6 = 1.0f;
    }

    f32 temp_f3 = mBeginTarget.f.z;
    f32 temp_f4 = mBeginTarget.f.y;
    f32 temp_f5 = mBeginTarget.f.x;

    mTargetPosition.f.x = ((mFinalTarget.f.x - temp_f5) * var_f6) + temp_f5;
    mTargetPosition.f.y = ((mFinalTarget.f.y - temp_f4) * var_f6) + temp_f4;
    mTargetPosition.f.z = ((mFinalTarget.f.z - temp_f3) * var_f6) + temp_f3;

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
