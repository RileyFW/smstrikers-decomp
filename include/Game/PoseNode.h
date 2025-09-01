#ifndef _POSENODE_H_
#define _POSENODE_H_

#include "NL/nlMath.h"

class cPoseAccumulator;

class cPoseNode
{
public:
    cPoseNode();
    cPoseNode(int);
    virtual ~cPoseNode();

    /* 0x0C */ virtual void V_unkC(int) = 0;
    // /* 0x10 */ virtual void V_unk10(float) const = 0;
    /* 0x10 */ virtual void V_unk10(cPoseAccumulator* accum, float weight) const = 0;

    /* 0x14 */ virtual void V_unk14() = 0;
    /* 0x18 */ virtual void V_unk18() = 0;
    /* 0x1C */ virtual void V_GetRootTrans(nlVector3* outBase, float weight, float* scratch) = 0;
    /* 0x20 */ virtual void V_GetRootRot(unsigned short* outRot, float weight, float* scratch) = 0;

    void GetRootRot(unsigned short*);
    void GetRootTrans(nlVector3*, unsigned short);
    void SetChild(int, cPoseNode*);
    cPoseNode** GetChildPtr(int);
    cPoseNode* GetChild(int) const;
    cPoseNode* GetChild(int);

    cPoseNode* m_children[3];
    int m_numChildren;
};

#endif // _POSENODE_H_
