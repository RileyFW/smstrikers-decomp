#ifndef _PNBLENDER_H_
#define _PNBLENDER_H_

#include "NL/nlSlotPool.h"
#include "Game/PoseAccumulator.h"

class cPN_Blender : public cPoseNode
{
public:
    cPN_Blender(cPoseNode*, cPoseNode*, float);
    /* 0x08 */ virtual ~cPN_Blender() { };
    /* 0x10 */ virtual void Evaluate(float, cPoseAccumulator*) const;
    /* 0x14 */ virtual void Evaluate(int, float, cPoseAccumulator*) const;
    /* 0x18 */ virtual cPoseNode* Update(float);
    /* 0x1C */ virtual int GetType() { return 0x0; };
    /* 0x20 */ virtual void BlendRootTrans(nlVector3*, float, float*);
    /* 0x24 */ virtual void BlendRootRot(unsigned short*, float, float*);

    /* 0x14 */ float m_fBlendTime;
    /* 0x18 */ float m_fBlendDuration;

    static SlotPool<cPN_Blender> m_BlenderSlotPool;
}; // total size: 0x1C

#endif // _PNBLENDER_H_
