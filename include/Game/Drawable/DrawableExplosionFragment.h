#ifndef _DRAWABLEEXPLOSIONFRAGMENT_H_
#define _DRAWABLEEXPLOSIONFRAGMENT_H_

#include "Game/Physics/PhysicsObject.h"

// void Replayable<3, SaveFrame, unsigned long>(SaveFrame&, unsigned long&);
// void Replayable<3, SaveFrame, nlQuaternion>(SaveFrame&, nlQuaternion&);
// void Replayable<3, LoadFrame, unsigned long>(LoadFrame&, unsigned long&);
// void Replayable<3, LoadFrame, nlQuaternion>(LoadFrame&, nlQuaternion&);

class DrawableExplosionFragment
{
public:
    void Blend(const float*, const DrawableExplosionFragment&, const DrawableExplosionFragment&);
    void Render() const;
    void Grab();
    // void Replay<LoadFrame>(LoadFrame&);
    // void Replay<SaveFrame>(SaveFrame&);

    /* 0x0, */ unsigned short mID;
    /* 0x2, */ unsigned char mVisible;
    /* 0x4, */ float mOpacity;
    /* 0x8, */ class nlVector3 mPosition;
    /* 0x14 */ class nlQuaternion mOrientation;
    /* 0x24 */ unsigned long mFragmentModelHash;
    /* 0x28 */ PhysicsObject* mpPhysicsObject;
}; // total size: 0x2C

#endif // _DRAWABLEEXPLOSIONFRAGMENT_H_
