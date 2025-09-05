#ifndef _DRAWABLESKINMODEL_H_
#define _DRAWABLESKINMODEL_H_

#include "Game/Drawable/DrawableObj.h"

class DrawableSkinModel
{
public:
    ~DrawableSkinModel();
    void Draw();
    void SetAnimation(const char*, unsigned long);
    void SetAnimationSpeed(float);
    void GetAnimationTime();
    void SetAnimationTime(float);
    void GetAnimationDuration();
};

#endif // _DRAWABLESKINMODEL_H_
