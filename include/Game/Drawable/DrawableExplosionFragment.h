#ifndef _DRAWABLEEXPLOSIONFRAGMENT_H_
#define _DRAWABLEEXPLOSIONFRAGMENT_H_

#include "Game/Replay.h"
#include "Game/Physics/PhysicsObject.h"

// void Replayable<3, SaveFrame, unsigned long>(SaveFrame&, unsigned long&);
// void Replayable<3, SaveFrame, nlQuaternion>(SaveFrame&, nlQuaternion&);
// void Replayable<3, LoadFrame, unsigned long>(LoadFrame&, unsigned long&);
// void Replayable<3, LoadFrame, nlQuaternion>(LoadFrame&, nlQuaternion&);

class DrawableExplosionFragment
{
public:
    template <typename T>
    void Replay(T&);

    void Blend(const float*, const DrawableExplosionFragment&, const DrawableExplosionFragment&);
    void Render() const;
    void Grab();

    // void Replay<LoadFrame>(LoadFrame&);
    // void Replay<SaveFrame>(SaveFrame&);

    /* 0x0, */ u16 mID;
    /* 0x2, */ bool mVisible;
    /* 0x4, */ float mOpacity;
    /* 0x8, */ nlVector3 mPosition;
    /* 0x14 */ nlQuaternion mOrientation;
    /* 0x24 */ u32 mFragmentModelHash;
    /* 0x28 */ PhysicsObject* mpPhysicsObject;
}; // total size: 0x2C

template <>
void DrawableExplosionFragment::Replay<SaveFrame>(SaveFrame&);

template <>
void DrawableExplosionFragment::Replay<LoadFrame>(LoadFrame&);

#endif // _DRAWABLEEXPLOSIONFRAGMENT_H_
