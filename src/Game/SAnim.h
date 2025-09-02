#ifndef _SANIM_H_
#define _SANIM_H_

#include "types.h"

#include "NL/nlMath.h"
// #include "NL/nlList.h"

#include "Game/PoseAccumulator.h"

typedef struct cSAnimCallback
{
    /* 0x00 */ f32 time;
    /* 0x04 */ u32 mask;
    /* 0x08 */ void (*fn)(unsigned int);
    /* 0x0C */ cSAnimCallback* next;
} cSAnimCallback; // size: 0x10

class nlChunk
{
public:
    /* 0x00 */ u32 m_ID;
    /* 0x04 */ u32 m_Size;
}; // size: 0x8

class cSAnim
{
public:
    static cSAnim* Initialize(nlChunk*);

    void BlendRot(int, int, float, float, cPoseAccumulator*, bool) const;
    void BlendScale(int, int, float, float, cPoseAccumulator*, bool) const;
    void BlendTrans(int, int, float, float, cPoseAccumulator*, bool) const;
    void Destroy();
    void GetRootRot(float, unsigned short*) const;
    void GetRootTrans(float, nlVector3*) const;
    void CreateCallback(float, unsigned int, void (*)(unsigned int));
    float GetMorphWeight(int, float) const;

    /* 0x00 */ u32 m_chunkID;
    /* 0x04 */ s32 m_chunkSize;
    /* 0x08 */ unsigned long m_numFrames;
    /* 0x0C */ unsigned long m_numBones;
    /* 0x10 */ char pad10[4];
    /* 0x14 */ unsigned long* m_flags;
    /* 0x18 */ void** m_rotTracks;
    /* 0x1C */ void** m_scaleTracks;
    /* 0x20 */ void** m_transTracks;
    /* 0x24 */ unsigned long m_rootKeyCount;
    /* 0x28 */ unsigned short* m_rootRot;
    /* 0x2C */ nlVector3* m_rootTrans;
    /* 0x30 */ void* m_morphTable;
    /* 0x34 */ unsigned long* m_morphIdx;
    /* 0x38 */ unsigned char* m_morphBytes;
    /* 0x3C */ cSAnimCallback* m_cbHead;
    /* 0x40 */ float m_rootSpeed;
};

#endif // _SANIM_H_
