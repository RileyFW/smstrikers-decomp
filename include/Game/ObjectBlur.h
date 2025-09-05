#ifndef _OBJECTBLUR_H_
#define _OBJECTBLUR_H_

#include "NL/nlMath.h"

// void nlDeleteDLRing<BlurHandler>(BlurHandler**);
// void nlDLRingIsEnd<BlurHandler>(BlurHandler*, BlurHandler*);
// void nlDLRingGetStart<BlurHandler>(BlurHandler*);
// void nlDLRingRemove<BlurHandler>(BlurHandler**, BlurHandler*);
// void nlDLRingAddEnd<BlurHandler>(BlurHandler**, BlurHandler*);
// void nlDLRingAddStart<BlurHandler>(BlurHandler**, BlurHandler*);
// void nlDeleteRing<BlurHandler>(BlurHandler**);

class BlurHandler
{
public:
    void RenderMesh(unsigned long);
    void Die(float);
    void AddViewOrientedPoint(const nlVector3&, const nlVector3&);
    void ConstructViewOrientedPoints(nlVector3&, nlVector3&, nlVector3, const nlVector3&);
};

class BlurManager
{
public:
    void Shutdown();
    void Update(float);
    static void DestroyHandler(BlurHandler*, float);
    static BlurHandler* GetNewHandler(const char*, float, int, bool);
};

// class SlotPool<BlurHandler>
// {
// public:
//     void ~SlotPool();
// };

#endif // _OBJECTBLUR_H_
