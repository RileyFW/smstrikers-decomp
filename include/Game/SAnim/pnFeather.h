#ifndef _PNFEATHER_H_
#define _PNFEATHER_H_

#include "Game/SHierarchy.h"
#include "Game/PoseAccumulator.h"

enum eFeatherBlendMode
{
    eFEATHER_BLEND_IN = 0,
    eFEATHER_BLEND_OUT = 1,
};

class cPN_Feather : public cPoseNode
{
public:
    void GetType();
    cPN_Feather(cSHierarchy*, void (*)(unsigned int, cPN_Feather*), unsigned int);
    ~cPN_Feather();
    void ClearNodeWeights();
    void SetNodeWeight(int, float, float);
    void SetChildFeatherWeight(int, float);
    void SetNodeWeight(int, float);
    void BeginBlendIn(float);
    void BeginBlendOut(float);
    void Update(float);
    void Evaluate(float, cPoseAccumulator*) const;
    void Evaluate(int, float, cPoseAccumulator*) const;
    void BlendRootTrans(nlVector3*, float, float*);
    void BlendRootRot(unsigned short*, float, float*);

    /* 0x14 */ float* m_pFeatherWeights;
    /* 0x18 */ float m_fBlendTime;
    /* 0x1C */ void (*m_fWeightTableCallback)(unsigned int, class cPN_Feather*);
    /* 0x20 */ unsigned int m_nCallbackParam1;
    /* 0x24 */ float m_fBlendDuration;
    /* 0x28 */ cSHierarchy* m_pBaseHierarchy;
    /* 0x2C */ eFeatherBlendMode m_eFeatherBlendMode;
}; // total size: 0x30

// class SlotPool<cPN_Feather>
// {
// public:
//     void ~SlotPool();
// };

#endif // _PNFEATHER_H_
