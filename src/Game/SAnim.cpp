#include "Game/SAnim.h"

#include "NL/nlMemory.h"
#include "NL/nlList.h"

/**
 * Offset/Address/Size: 0xD40 | 0x801E9F54 | size: 0x68C
 */
cSAnim* cSAnim::Initialize(nlChunk* arg0)
{
    return nullptr;
}

/**
 * Offset/Address/Size: 0x91C | 0x801E9B30 | size: 0x424
 */
void cSAnim::BlendRot(int nodeIndex, int remappedNodeIndex, float tNorm, float weight, cPoseAccumulator* acc, bool additive) const
{
}

/**
 * Offset/Address/Size: 0x608 | 0x801E981C | size: 0x314
 */
void cSAnim::BlendScale(int nodeIndex, int remappedNodeIndex, float tNorm, float weight, cPoseAccumulator* acc, bool additive) const
{
}

/**
 * Offset/Address/Size: 0x404 | 0x801E9618 | size: 0x204
 */
void cSAnim::BlendTrans(int nAccumulatorNode, int nSAnimNode, float fTime, float fWeight, cPoseAccumulator* pAccumulator, bool bMirror) const
{
    if (pAccumulator->m_BaseSHierarchy->PreserveBoneLength(nAccumulatorNode))
    {
        return;
    }

    PackedTrans* pKeys = m_pTransKeys[nSAnimNode];
    if (pKeys != NULL && (unsigned int)nSAnimNode < m_nNumNodes)
    {
        if (m_pNodeProperties[nSAnimNode] & 0x4)
        {
            nlVector3 v;
            v.f.x = pKeys[0].x;
            v.f.y = pKeys[0].y;
            v.f.z = pKeys[0].z;
            pAccumulator->BlendTrans(nAccumulatorNode, &v, fWeight, bMirror);
            return;
        }

        if (1.0f == fTime)
        {
            PackedTrans* pLastKey = &pKeys[m_nNumKeys - 1];
            nlVector3 v;
            v.f.x = pLastKey->x;
            v.f.y = pLastKey->y;
            v.f.z = pLastKey->z;
            pAccumulator->BlendTrans(nAccumulatorNode, &v, fWeight, bMirror);
            return;
        }

        int nKeyIndex = (int)(fTime * (float)(m_nNumKeys - 1));
        float fFrac = fTime * (float)(m_nNumKeys - 1) - (float)nKeyIndex;
        float fWeight2 = fWeight * fFrac;
        float fWeight1 = fWeight - fWeight2;

        PackedTrans* pKey = &pKeys[nKeyIndex];
        nlVector3 v1;
        v1.f.x = pKey->x;
        v1.f.y = pKey->y;
        v1.f.z = pKey->z;
        pAccumulator->BlendTrans(nAccumulatorNode, &v1, fWeight1, bMirror);

        PackedTrans* pNextKey = &m_pTransKeys[nSAnimNode][nKeyIndex + 1];
        nlVector3 v2;
        v2.f.x = pNextKey->x;
        v2.f.y = pNextKey->y;
        v2.f.z = pNextKey->z;
        pAccumulator->BlendTrans(nAccumulatorNode, &v2, fWeight2, bMirror);
    }
    else
    {
        pAccumulator->BlendTransIdentity(nAccumulatorNode, fWeight);
    }
}

/**
 * Offset/Address/Size: 0x3CC | 0x801E95E0 | size: 0x38
 */
void cSAnim::Destroy()
{
    nlDeleteList<cSAnimCallback>(&m_pCallbackList);
    m_pCallbackList = 0;
}

/**
 * Offset/Address/Size: 0x2EC | 0x801E9500 | size: 0xE0
 */
void cSAnim::GetRootRot(float t, unsigned short* outZ) const
{
    int nIndex;       // r0
    float fRealIndex; // f3

    if (m_nNumRootKeys != 0)
    {
        if (t == 0.0f || m_nNumRootKeys == 1)
        {
            *outZ = m_pRootRot[m_nNumRootKeys - 1];
            return;
        }

        fRealIndex = t * (m_nNumRootKeys - 1);
        nIndex = (int)fRealIndex;
        float fraction = fRealIndex - nIndex;
        const unsigned short val0 = m_pRootRot[nIndex];
        const unsigned short val1 = m_pRootRot[nIndex + 1];
        const u16 diff = (u16)(val1 - val0);
        *outZ = val0 + (int)(fraction * diff);
        return;
    }
    *outZ = 0;
}
/**
 * Offset/Address/Size: 0x1E0 | 0x801E93F4 | size: 0x10C
 */
void cSAnim::GetRootTrans(float t, nlVector3* out) const
{
    if (m_nNumRootKeys != 0)
    {
        if (t == 1.0f || m_nNumRootKeys == 1)
        {
            *out = m_pRootTrans[m_nNumRootKeys - 1];
            return;
        }

        float fRealIndex = t * (m_nNumRootKeys - 1);
        int nIndex = (int)fRealIndex;
        float fWeight = fRealIndex - nIndex;
        const nlVector3& val0 = m_pRootTrans[nIndex];
        const nlVector3& val1 = m_pRootTrans[nIndex + 1];

        out->f.x = (fWeight * val1.f.x) + (1.0f - fWeight) * val0.f.x;
        out->f.y = (fWeight * val1.f.y) + (1.0f - fWeight) * val0.f.y;
        out->f.z = (fWeight * val1.f.z) + (1.0f - fWeight) * val0.f.z;

        return;
    }
    out->f.x = 0.0f;
    out->f.y = 0.0f;
    out->f.z = 0.0f;
}

/**
 * Offset/Address/Size: 0x160 | 0x801E9374 | size: 0x80
 */
void cSAnim::CreateCallback(float time, unsigned int param1, void (*funcCallback)(unsigned int))
{
    cSAnimCallback* temp_r3;
    temp_r3 = (cSAnimCallback*)nlMalloc(0x10, 8, 0);

    if (temp_r3 != NULL)
    {
        temp_r3->m_fTime = time;
        temp_r3->m_nParam1 = param1;
        temp_r3->m_funcCallback = funcCallback;
    }

    nlListAddStart<cSAnimCallback>(&m_pCallbackList, temp_r3, NULL);
}

/**
 * Offset/Address/Size: 0x0 | 0x801E9214 | size: 0x160
 */
float cSAnim::GetMorphWeight(int channel, float fTime) const
{
    const u8* keys = m_pMorphKeys;
    int numKeys = m_pNumMorphKeys[channel];
    int i = 0;

    for (i = 0; i < channel; i++)
    {
        keys += m_pNumMorphKeys[channel];
    }

    if (numKeys == 1 || fTime == 1.0f)
    {
        float weight = (float)keys[numKeys - 1] / 255.0f;
        return weight;
    }

    float fRealIndex = fTime * (float)(numKeys - 1);
    int nIndex = (int)fRealIndex;
    float fWeightB = fRealIndex - (float)nIndex;
    return (1.0f - fWeightB) * ((float)keys[nIndex] / 255.0f) + fWeightB * ((float)keys[nIndex + 1] / 255.0f);
}
