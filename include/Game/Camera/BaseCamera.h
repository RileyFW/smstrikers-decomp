#ifndef _BASECAMERA_H_
#define _BASECAMERA_H_

#include "NL/nlMath.h"
// #include "Game/RumbleFilter.h"

class cRumbleFilter;

enum eCameraType
{
    eCameraType_Debug = 0,
    eCameraType_FollowCharacter = 1,
    eCameraType_FollowBall = 2,
    eCameraType_Replay = 3,
    eCameraType_Animated = 4,
    eCameraType_KickOff = 5,
    eCameraType_TopDown = 6,
    eCameraType_Gameplay = 7,
    eCameraType_MatrixEffect = 8,
    eCameraType_Goal = 9,
    eCameraType_ShootToScore = 10,
    eCameraType_AnimViewer = 11,
    eCameraType_FaceCloseup = 12,
    NUM_CAMERA_TYPES = 13,
};

class cBaseCamera
{
public:
    cBaseCamera()
    {
        m_pFilter = nullptr;
        mUpVector.f.x = 0.0f;
        mUpVector.f.y = 0.0f;
        mUpVector.f.z = 1.0f;
    };
    virtual ~cBaseCamera() { };
    virtual eCameraType GetType() = 0;
    virtual void Update(float) = 0;
    virtual nlMatrix4& GetViewMatrix() const = 0;
    virtual float GetFOV() const { return 0.0f; };
    virtual void Reactivate() { };
    virtual const nlVector3& GetTargetPosition() const = 0;
    virtual const nlVector3& GetCameraPosition() const = 0;

    /* 0x04 */ cBaseCamera* next;
    /* 0x08 */ cBaseCamera* prev;
    /* 0x0C */ cRumbleFilter* m_pFilter;
    /* 0x10 */ nlVector3 mUpVector;
}; // total size: 0x1C

#endif // _BASECAMERA_H_
