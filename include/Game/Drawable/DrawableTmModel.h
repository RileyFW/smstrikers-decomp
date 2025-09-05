#ifndef _DRAWABLETMMODEL_H_
#define _DRAWABLETMMODEL_H_

#include "Game/Drawable/DrawableObj.h"

class DrawableTmModel
{
public:
    ~DrawableTmModel();
    void Draw();
    void Clone() const;
    void SetAnimation(const char*, unsigned long);
    void SetAnimationSpeed(float);
    void GetAnimationTime();
    void SetAnimationTime(float);
};

#endif // _DRAWABLETMMODEL_H_
