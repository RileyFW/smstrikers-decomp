#ifndef _CAMERAGUY_H_
#define _CAMERAGUY_H_

#include "Game/AI/HeadTrack.h"
#include "Game/Render/SkinAnimatedNPC.h"

extern int g_nCameraTiltMax;
extern u16 g_aCameraOOIConstraint;
extern int g_nCameraSpinMax;

static void CameraGuyHeadTrackUpdateCallback(unsigned int, unsigned int, cPoseAccumulator*, unsigned int, int);

class cHeadTrack;

class CameraGuy : public SkinAnimatedNPC
{
public:
    CameraGuy(cSHierarchy& pHierarchy, int nModelID);

    virtual ~CameraGuy();
    virtual SkinAnimatedNPC_Type GetSkinAnimatedNPC_Type() const { return SkinAnimatedNPC_CAMERA_GUY; };
    virtual void Render();
    virtual void Update(float);

    virtual void Init();

    void SetIdleAnim(cSAnim&);

    /* 0x5C */ cHeadTrack* mpHeadTrack; // offset 0x5C, size 0x4
}; // total size: 0x60

#endif // _CAMERAGUY_H_
