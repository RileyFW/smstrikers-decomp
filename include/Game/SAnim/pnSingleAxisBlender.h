#ifndef _PNSINGLEAXISBLENDER_H_
#define _PNSINGLEAXISBLENDER_H_

#include "Game/PoseAccumulator.h"
#include "NL/nlMath.h"

class cPN_SingleAxisBlender
{
public:
    void GetType();
    ~cPN_SingleAxisBlender();
    cPN_SingleAxisBlender(int, void (*)(unsigned int, cPN_SingleAxisBlender*), unsigned int, float);
    void Update(float);
    void Evaluate(int, float, cPoseAccumulator*) const;
    void Evaluate(float, cPoseAccumulator*) const;
    void BlendRootTrans(nlVector3*, float, float*);
    void BlendRootRot(unsigned short*, float, float*);
};

// class SlotPool<cPN_SingleAxisBlender>
// {
// public:
//     void ~SlotPool();
// };

#endif // _PNSINGLEAXISBLENDER_H_
