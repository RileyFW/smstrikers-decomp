#include "Game/Camera/FaceCam.h"

#include "NL/gl/glMatrix.h"

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
    mTargetPosition = mpCharacter->GetJointPosition(mpCharacter->m_nHeadJointIndex);

    const nlMatrix4* mtx = mpCharacter->m_pPoseAccumulator->GetNodeMatrix(mpCharacter->m_nHeadJointIndex);

    float forwardX = mtx->m[1][0]; // f31 = matrix[0x10]
    float forwardZ = mtx->m[1][1]; // f30 = matrix[0x14]

    float invLen = nlRecipSqrt(1.0f + (forwardX * forwardX + forwardZ * forwardZ), 1);

    const float kZero = 0.f;
    const float d = mDistance;
    const float tx = mTargetPosition.f.x;
    const float ty = mTargetPosition.f.y;
    const float tz = mTargetPosition.f.z;

    mCameraPosition.f.x = d * (invLen * forwardX) + tx;
    mCameraPosition.f.y = d * (invLen * forwardZ) + ty;
    mCameraPosition.f.z = d * (invLen * 0.001f) + tz;

    const nlVector3& at = GetTargetPosition();
    const nlVector3& eye = GetCameraPosition();
    glMatrixLookAt(mViewMatrix, eye, at, mUpVector);
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
