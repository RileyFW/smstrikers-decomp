#ifndef _DRAWABLEEXPLOSIONFRAGMENT_H_
#define _DRAWABLEEXPLOSIONFRAGMENT_H_

#include "Game/Drawable/DrawableObj.h"

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
};

#endif // _DRAWABLEEXPLOSIONFRAGMENT_H_
