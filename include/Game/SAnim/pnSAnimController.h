#ifndef _PNSANIMCONTROLLER_H_
#define _PNSANIMCONTROLLER_H_

#include "Game/SAnim.h"
#include "Game/PoseAccumulator.h"
#include "NL/nlMath.h"

// class SlotPool<cPN_SAnimController>
// {
// public:
//     void ~SlotPool();
// };

// class cSAnim
// {
// public:
//     void GetCallbackList() const;
// };

class AnimRetarget;

class cPN_SAnimController : public cPoseNode
{
public:
    cPN_SAnimController(cSAnim*, const AnimRetarget*, ePlayMode, void (*)(unsigned int, cPN_SAnimController*), unsigned int, bool);
    /* 0x08 */ virtual ~cPN_SAnimController() { };
    /* 0x10 */ virtual void Evaluate(float, cPoseAccumulator*) const;
    /* 0x14 */ virtual void Evaluate(int, float, cPoseAccumulator*) const;
    /* 0x18 */ virtual void Update(float);
    /* 0x1C */ virtual int GetType() { return 0x2; };
    /* 0x20 */ virtual void BlendRootTrans(nlVector3*, float, float*);
    /* 0x24 */ virtual void BlendRootRot(unsigned short*, float, float*);

    void UpdateSynchronized(float);
    void SetTime(float);
    void ProcessCallbacks();
    void TestTrigger(float) const;
    void TestFrameTrigger(float);
    void RemapNode(int) const;

    /* 0x14 */ class cSAnim* m_pSAnim;
    /* 0x18 */ float m_fTime;
    /* 0x1C */ unsigned char m_bMirror;
    /* 0x20 */ const class AnimRetarget* m_pAnimRetarget;
    /* 0x24 */ float m_fPrevTime;
    /* 0x28 */ enum ePlayMode m_ePlayMode;
    /* 0x2C */ float m_fWeight;
    /* 0x30 */ unsigned char m_bIgnoreTriggers;
    /* 0x34 */ void (*m_funcPlaybackSpeedCallback)(unsigned int, class cPN_SAnimController*);
    /* 0x38 */ unsigned int m_nPlaybackSpeedCallbackParam;
    /* 0x3C */ float m_fPlaybackSpeedScale;
    /* 0x40 */ unsigned char m_bIsSynchronized;
    /* 0x44 */ class cPN_SAnimController* m_pSynchronizedController;
    /* 0x48 */ void (*m_funcSychronizedWeightCallback)(unsigned int, class cPN_SAnimController*);
    /* 0x4C */ unsigned int m_nSynchronizedWeightCallbackParam;
    /* 0x50 */ float m_fSynchronizedWeight;
}; // total size: 0x54

#endif // _PNSANIMCONTROLLER_H_
