#ifndef _CAMERAGUY_H_
#define _CAMERAGUY_H_

#include "Game/GameRender/SkinAnimatedNPC.h"

void CameraGuyHeadTrackUpdateCallback(unsigned int, unsigned int, cPoseAccumulator*, unsigned int, int);
// void 0x8015DCFC..0x8015DD04 | size: 0x8;

class cHeadTrack;

class CameraGuy : public SkinAnimatedNPC
{
public:
    CameraGuy(cSHierarchy&, int);
    ~CameraGuy();

    void GetSkinAnimatedNPC_Type() const;
    void Init();
    void Render();
    void SetIdleAnim(cSAnim&);
    void Update(float);

    /* 0x5C */ cHeadTrack* mpHeadTrack; // offset 0x5C, size 0x4
}; // total size: 0x60

// class CameraGuy : public SkinAnimatedNPC
// {
//     // total size: 0x60
//     class cHeadTrack* mpHeadTrack; // offset 0x5C, size 0x4
// };

#endif // _CAMERAGUY_H_
