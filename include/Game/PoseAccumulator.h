#ifndef _POSEACCUMULATOR_H_
#define _POSEACCUMULATOR_H_

#include "NL/nlMath.h"

#include "Game/SHierarchy.h"
#include "Game/PoseNode.h"

// class cPoseAccumulator;

typedef void (*BuildNodeMatrixFn)(unsigned int, unsigned int, cPoseAccumulator*, unsigned int, int);

class Vector
{
    /* 0x0 */ nlMatrix4* mData;
    /* 0x4 */ int mSize;
    /* 0x8 */ int mCapacity;
}; // total size: 0xC

class cBuildNodeMatrixCallbackInfo
{
public:
    cBuildNodeMatrixCallbackInfo()
    {
        fn = nullptr;
        a = 0;
        b = 0;
    }

    /* 0x00 */ BuildNodeMatrixFn fn;
    /* 0x04 */ unsigned int a;
    /* 0x08 */ unsigned int b;
}; // size: 0x0C

struct RotAccum
{
    /* 0x00 */ nlQuaternion q;
    /* 0x10 */ float weight;
    /* 0x14 */ u16 angleZ;
    /* 0x18 */ float weightZ;
    /* 0x1C */ bool locked;
    /* 0x1D */ u8 _pad[3];
}; // size: 0x20

struct ScaleAccum
{
    /* 0x00 */ nlVector3 s;
    /* 0x0C */ float fAccumulatedWeight;
    /* 0x10 */ bool bIdentity;
    // /* 0x00 */ float x;
    // /* 0x04 */ float y;
    // /* 0x08 */ float z;
    // /* 0x0C */ float weight;
    // /* 0x10 */ bool locked;
    // /* 0x11 */ u8 _pad[3];
}; // total size: 0x14

struct TransAccum
{
    /* 0x00 */ float x;
    /* 0x04 */ float y;
    /* 0x08 */ float z;
    /* 0x0C */ float weight;
    /* 0x10 */ bool locked;
    /* 0x11 */ u8 _pad[3];
}; // size: 0x14

class cPoseAccumulator
{
public:
    cPoseAccumulator(cSHierarchy*, bool);
    void Pose(const cPoseNode&, const nlMatrix4&);
    void InitAccumulators();
    void BuildNodeMatrices(const nlMatrix4&);
    void BlendRot(int, const nlQuaternion*, float, bool);
    void BlendRotAroundZ(int, unsigned short, float);
    void BlendScale(int, const nlVector3*, float, bool);
    void BlendTrans(int, const nlVector3*, float, bool);
    void BlendRotIdentity(int, float);
    void BlendScaleIdentity(int, float);
    void BlendTransIdentity(int, float);
    nlMatrix4* GetNodeMatrix(int) const;
    nlMatrix4* GetNodeMatrixByHashID(unsigned int) const;
    s32 GetNumNodes() const;
    void MultNodeMatrices(const nlMatrix4*);
    void SetBuildNodeMatrixCallback(int, BuildNodeMatrixFn, unsigned int, unsigned int);

    /* 0x00 */ cSHierarchy* m_hierarchy;
    /* 0x04 */ nlMatrix4* m_matsA;
    /* 0x08 */ s32 m_unk_0x08;
    /* 0x0C */ s32 m_unk_0x0C;
    /* 0x10 */ nlMatrix4* m_matsB;
    /* 0x14 */ s32 m_unk_0x14;
    /* 0x18 */ s32 m_unk_0x18;
    /* 0x1C */ RotAccum* m_rot;
    /* 0x20 */ s32 m_unk_0x20;
    /* 0x24 */ s32 m_unk_0x24;
    /* 0x28 */ ScaleAccum* m_scale;
    /* 0x2C */ s32 m_unk_0x2C;
    /* 0x30 */ s32 m_unk_0x30;
    /* 0x34 */ TransAccum* m_trans;
    /* 0x38 */ s32 m_unk_0x38;
    /* 0x3C */ s32 m_unk_0x3C;
    /* 0x40 */ cBuildNodeMatrixCallbackInfo* m_cb;
    /* 0x44 */ s32 m_unk_0x44;
    /* 0x48 */ s32 m_unk_0x48;
    /* 0x4C */ float* m_floatArray;
    /* 0x50 */ s32 m_floatCount;
};

#endif // _POSEACCUMULATOR_H_
