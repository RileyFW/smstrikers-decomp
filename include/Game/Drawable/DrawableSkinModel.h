#ifndef _DRAWABLESKINMODEL_H_
#define _DRAWABLESKINMODEL_H_

#include "Game/Drawable/DrawableObj.h"

class WorldAnimController;

class DrawableSkinModel : public DrawableObject
{
public:
    ~DrawableSkinModel();
    /* 0x10 */ virtual void Draw();
    void SetAnimation(const char*, unsigned long);
    void SetAnimationSpeed(float);
    void GetAnimationTime();
    void SetAnimationTime(float);
    void GetAnimationDuration();

    /* 0x9C */ void* m_pField9C;
    /* 0xA0 */ void* m_pFieldA0;
    /* 0xA4 */ WorldAnimController* m_pAnimController;
};

#endif // _DRAWABLESKINMODEL_H_
