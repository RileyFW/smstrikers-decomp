#include "Game/SAnim.h"

#include "NL/nlMemory.h"
#include "NL/nlList.h"

/**
 * Offset/Address/Size: 0xD40 | 0x801E9F54 | size: 0x68C
 */
cSAnim* cSAnim::Initialize(nlChunk* arg0)
{
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
float cSAnim::GetMorphWeight(int index, float t) const
{
    return 0.0f;
}
