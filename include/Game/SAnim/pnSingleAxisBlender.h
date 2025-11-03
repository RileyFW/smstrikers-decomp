#ifndef _PNSINGLEAXISBLENDER_H_
#define _PNSINGLEAXISBLENDER_H_

#include "Game/PoseAccumulator.h"
#include "NL/nlMath.h"

class cPN_SingleAxisBlender : public cPoseNode
{
public:
    cPN_SingleAxisBlender(int, void (*)(unsigned int, cPN_SingleAxisBlender*), unsigned int, float);
    /* 0x08 */ virtual ~cPN_SingleAxisBlender();
    /* 0x14 */ virtual void Evaluate(int, float, cPoseAccumulator*) const;
    /* 0x10 */ virtual void Evaluate(float, cPoseAccumulator*) const;
    /* 0x18 */ virtual cPoseNode* Update(float);
    /* 0x1C */ virtual int GetType() { return 0x3; };
    /* 0x20 */ virtual void BlendRootTrans(nlVector3*, float, float*);
    /* 0x24 */ virtual void BlendRootRot(unsigned short*, float, float*);
};

// class SlotPool<cPN_SingleAxisBlender>
// {
// public:
//     void ~SlotPool();
// };

#endif // _PNSINGLEAXISBLENDER_H_
