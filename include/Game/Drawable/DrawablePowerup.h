#ifndef _DRAWABLEPOWERUP_H_
#define _DRAWABLEPOWERUP_H_

#include "Game/Drawable/DrawableObj.h"

void DrawShadow(float, float, float, float);
// void Replayable<3, SaveFrame, bool>(SaveFrame&, bool&);
// void Replayable<3, SaveFrame, char>(SaveFrame&, char&);
// void Replayable<3, SaveFrame, unsigned short>(SaveFrame&, unsigned short&);
// void Replayable<3, SaveFrame, nlVector3>(SaveFrame&, nlVector3&);
// void Replayable<3, SaveFrame, float>(SaveFrame&, float&);
// void Replayable<3, LoadFrame, bool>(LoadFrame&, bool&);
// void Replayable<3, LoadFrame, char>(LoadFrame&, char&);
// void Replayable<3, LoadFrame, unsigned short>(LoadFrame&, unsigned short&);
// void Replayable<3, LoadFrame, nlVector3>(LoadFrame&, nlVector3&);
// void Replayable<3, LoadFrame, float>(LoadFrame&, float&);

class DrawablePowerup
{
public:
    void Blend(const float*, const DrawablePowerup&, const DrawablePowerup&);
    void Render(int) const;
    void Grab(int);
    // void Replay<LoadFrame>(LoadFrame&);
    // void Replay<SaveFrame>(SaveFrame&);

    /* 0x00 */ s8 mType;
    /* 0x04 */ float mScale;
    /* 0x08 */ float mRadius;
    /* 0x0C */ unsigned char mVisible;
    /* 0x10 */ nlVector3 mPosition;
    /* 0x1C */ u16 mOrientation;
}; // total size: 0x20

#endif // _DRAWABLEPOWERUP_H_
