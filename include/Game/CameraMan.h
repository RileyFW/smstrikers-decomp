#ifndef _CAMERAMAN_H_
#define _CAMERAMAN_H_

#include "types.h"
#include "NL/nlMath.h"

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

enum eCameraTransition
{
    eCT_NONE = 0,
    eCT_EASE_IN = 1,
};

enum eCameraMessage
{
    eCM_ABORTED_BY_POP = 0,
    eCM_ABORTED_BY_PUSH = 1,
    eCM_COMPLETE = 2,
};

class cBaseCamera;
class DrawableObject;

void FireCameraRumbleFilter(float, float);
// void 0x801A8404..0x801A8634 | size: 0x230;
// void nlDeleteDLRing<cBaseCamera>(cBaseCamera**);
// void nlDLRingRemoveEnd<cBaseCamera>(cBaseCamera**);
// void nlDLRingRemoveStart<cBaseCamera>(cBaseCamera**);
// void nlDLRingGetEnd<cBaseCamera>(cBaseCamera*);
// void nlDLRingRemoveSafely<cBaseCamera>(cBaseCamera**, const cBaseCamera*);
// void nlDLRingValidateContainsElement<cBaseCamera>(cBaseCamera*, const cBaseCamera*);
// void nlDLRingRemove<cBaseCamera>(cBaseCamera**, cBaseCamera*);
// void nlDLRingAddEnd<cBaseCamera>(cBaseCamera**, cBaseCamera*);
// void nlDLRingAddStart<cBaseCamera>(cBaseCamera**, cBaseCamera*);
// void nlDeleteRing<cBaseCamera>(cBaseCamera**);

class cCameraManager
{
public:
    void Startup();
    void Shutdown();
    void Update(float);
    void UpdateGameCameraType();
    void HasCamera(cBaseCamera*);
    void PushCamera(cBaseCamera*);
    void Remove(const cBaseCamera&);
    void Remove(eCameraType, bool);
    void PushCameraWithTransition(cBaseCamera*, float, eCameraTransition, void (*)(eCameraMessage));
    void PopCameraWithTransition(float, eCameraTransition, void (*)(eCameraMessage));
    void IsObjectOccludingField(const DrawableObject*);
    void GetDistanceFromCameraToObject(const nlVector3&);
    void GetViewVector(nlVector3&);
    void GetUpVector(nlVector3&);
    void SetWorldUpVectorTilt(float, float);
    void PushWorldUpVector();
    void PopWorldUpVector();

    static u16 m_aJoystickRemap;
};

#endif // _CAMERAMAN_H_
