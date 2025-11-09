#include "Game/SAnim/pnSAnimController.h"
#include "Game/SAnim.h"
#include "Game/SAnim/AnimRetargeter.h"

SlotPool<cPN_SAnimController> cPN_SAnimController::m_SAnimControllerSlotPool;

/**
 * Offset/Address/Size: 0xDC0 | 0x801EB41C | size: 0x98
 */
cPN_SAnimController::cPN_SAnimController(cSAnim* pSAnim, const AnimRetarget* pAnimRetarget, ePlayMode playMode, void (*funcPlaybackSpeedCallback)(unsigned int, cPN_SAnimController*), unsigned int nPlaybackSpeedCallbackParam, bool bMirror)
    : cPoseNode()
{
    m_pSAnim = pSAnim;
    m_fTime = 0.0f;
    m_bMirror = bMirror;
    m_pAnimRetarget = pAnimRetarget;
    m_fPrevTime = 0.0f;
    m_ePlayMode = playMode;
    m_bIgnoreTriggers = false;
    m_funcPlaybackSpeedCallback = funcPlaybackSpeedCallback;
    m_nPlaybackSpeedCallbackParam = nPlaybackSpeedCallbackParam;
    m_fPlaybackSpeedScale = 1.0f;
    m_bIsSynchronized = false;
    m_pSynchronizedController = nullptr;
    m_funcSychronizedWeightCallback = nullptr;
    m_fSynchronizedWeight = 1.0f;
}

/**
 * Offset/Address/Size: 0xAF0 | 0x801EB14C | size: 0x2D0
 */
cPoseNode* cPN_SAnimController::Update(float dt)
{
    if (!m_bIsSynchronized)
    {
        // Call playback speed callback if it exists
        if (m_funcPlaybackSpeedCallback != nullptr)
        {
            m_funcPlaybackSpeedCallback(m_nPlaybackSpeedCallbackParam, this);
        }

        float playbackSpeedScale = m_fPlaybackSpeedScale;

        // Handle synchronized controller weight calculation
        if (m_pSynchronizedController != nullptr)
        {
            // Call synchronized weight callback if it exists
            if (m_funcSychronizedWeightCallback != nullptr)
            {
                m_funcSychronizedWeightCallback(m_nSynchronizedWeightCallbackParam, this);
            }

            // Calculate synchronized weight ratio
            cSAnim* pSyncSAnim = m_pSynchronizedController->m_pSAnim;
            cSAnim* pThisSAnim = m_pSAnim;

            float syncNumKeys = (float)pSyncSAnim->m_nNumKeys;
            float thisNumKeys = (float)pThisSAnim->m_nNumKeys;

            float syncDuration = syncNumKeys / 30.0f;
            float thisDuration = thisNumKeys / 30.0f;

            float syncTime = m_pSynchronizedController->m_fTime;
            float syncPlaybackSpeed = m_pSynchronizedController->m_fPlaybackSpeedScale;

            float syncNormalizedSpeed = (syncTime / syncDuration) / (m_fTime / thisDuration);
            float weightRatio = (syncNormalizedSpeed - 1.0f) * m_fSynchronizedWeight + 1.0f;

            playbackSpeedScale *= weightRatio;
        }

        // Save previous time
        m_fPrevTime = m_fTime;

        // Calculate animation duration
        float numKeys = (float)m_pSAnim->m_nNumKeys;
        float duration = numKeys / 30.0f;

        // Update time
        if (duration == 0.0f)
        {
            m_fTime = 1.0f;
        }
        else
        {
            float timeDelta = (dt * playbackSpeedScale) / duration;
            m_fTime += timeDelta;
        }

        if (m_fTime > 1.0f)
        {
            if (m_ePlayMode == PM_CYCLIC)
            {
                while (m_fTime > 1.0f)
                {
                    m_fTime -= 1.0f;
                }
            }
            else if (m_ePlayMode == PM_HOLD)
            {
                m_fTime = 1.0f;
            }
        }
        else if (m_fTime < 0.0f)
        {
            if (m_ePlayMode == PM_CYCLIC)
            {
                while (m_fTime < 0.0f)
                {
                    m_fTime += 1.0f;
                }
            }
            else if (m_ePlayMode == PM_HOLD)
            {
                m_fTime = 0.0f;
            }
        }

        // Process callbacks if dt >= 0.0f and not ignoring triggers
        if (dt >= 0.0f && !m_bIgnoreTriggers)
        {
            cSAnimCallback* pCallback = m_pSAnim->GetCallbackList();

            while (pCallback != nullptr)
            {
                float callbackTime = pCallback->m_fTime;

                if (callbackTime == 0.0f)
                {
                    extern float __float_min[];
                    callbackTime = __float_min[0];
                }

                float currTime = m_fTime;
                float prevTime = m_fPrevTime;
                bool shouldTrigger = false;

                if (currTime < prevTime)
                {
                    // Time wrapped around
                    if (callbackTime <= currTime || callbackTime > prevTime)
                    {
                        shouldTrigger = true;
                    }
                }
                else
                {
                    // Normal forward playback
                    if (callbackTime <= currTime && callbackTime > prevTime)
                    {
                        shouldTrigger = true;
                    }
                }

                if (shouldTrigger)
                {
                    pCallback->m_funcCallback(pCallback->m_nParam1);
                }

                pCallback = pCallback->next;
            }
        }

        // Update synchronized controller if it exists
        if (m_pSynchronizedController != nullptr)
        {
            m_pSynchronizedController->UpdateSynchronized(m_fTime);
        }
        // return this;
    }

    return this;
}

/**
 * Offset/Address/Size: 0x7E8 | 0x801EAE44 | size: 0x308
 */
void cPN_SAnimController::UpdateSynchronized(float)
{
}

/**
 * Offset/Address/Size: 0x760 | 0x801EADBC | size: 0x88
 */
void cPN_SAnimController::Evaluate(float weight, cPoseAccumulator* pAccumulator) const
{
    m_fWeight = weight;

    for (int i = 0; i < pAccumulator->GetNumNodes(); ++i)
    {
        Evaluate(i, weight, pAccumulator);
    }
}

/**
 * Offset/Address/Size: 0x5DC | 0x801EAC38 | size: 0x184
 */
void cPN_SAnimController::Evaluate(int nodeIndex, float weight, cPoseAccumulator* pAccumulator) const
{
    int remappedNodeIndex;

    if (nodeIndex == 0)
    {
        for (int i = 0; i < m_pSAnim->m_nNumMorphChannels; ++i)
        {
            pAccumulator->m_floatArray[i] += weight * m_pSAnim->GetMorphWeight(i, m_fTime);
        }
    }

    int actualNodeIndex = nodeIndex;
    if (m_bMirror != 0)
    {
        actualNodeIndex = pAccumulator->m_BaseSHierarchy->GetMirroredNode(nodeIndex);
    }

    if (m_pAnimRetarget != nullptr)
    {
        remappedNodeIndex = m_pAnimRetarget->m_pMap[actualNodeIndex];
    }
    else
    {
        remappedNodeIndex = actualNodeIndex;
    }

    if (remappedNodeIndex != -1)
    {
        m_pSAnim->BlendRot(nodeIndex, remappedNodeIndex, m_fTime, weight, pAccumulator, get_bMirror());
        m_pSAnim->BlendScale(nodeIndex, remappedNodeIndex, m_fTime, weight, pAccumulator, get_bMirror());
        m_pSAnim->BlendTrans(nodeIndex, remappedNodeIndex, m_fTime, weight, pAccumulator, get_bMirror());
        return;
    }

    nlVector3* pTranslationOffset = pAccumulator->m_BaseSHierarchy->GetTranslationOffset(nodeIndex);
    pAccumulator->BlendRotIdentity(nodeIndex, weight);
    pAccumulator->BlendScaleIdentity(nodeIndex, weight);
    pAccumulator->m_trans[nodeIndex].t = *pTranslationOffset;
}

/**
 * Offset/Address/Size: 0x35C | 0x801EA9B8 | size: 0x280
 */
void cPN_SAnimController::BlendRootTrans(nlVector3*, float, float*)
{
}

/**
 * Offset/Address/Size: 0x1F4 | 0x801EA850 | size: 0x168
 */
void cPN_SAnimController::BlendRootRot(unsigned short* pOutRot, float weight, float* pAccumWeight)
{
    unsigned short deltaRot;

    float currTime = m_fTime;
    float prevTime = m_fPrevTime;

    if (currTime < prevTime)
    {
        unsigned short rot1, rot2, rot3, rot4;
        m_pSAnim->GetRootRot(prevTime, &rot1);
        m_pSAnim->GetRootRot(1.0f, &rot2);
        m_pSAnim->GetRootRot(0.0f, &rot3);
        m_pSAnim->GetRootRot(m_fTime, &rot4);
        deltaRot = (rot2 - rot1) + (rot4 - rot3);
    }
    else
    {
        unsigned short rot1, rot2;
        m_pSAnim->GetRootRot(currTime, &rot2);
        m_pSAnim->GetRootRot(m_fPrevTime, &rot1);
        deltaRot = rot2 - rot1;
    }

    if (m_bMirror != 0)
    {
        deltaRot *= -1;
    }

    *pAccumWeight += weight;
    float w = *pAccumWeight;

    if (w != 0.0f)
    {
        float blendFactor = weight / *pAccumWeight;
        short signedDelta = deltaRot - *pOutRot;
        float blendedDelta = blendFactor * signedDelta;

        *pOutRot = *pOutRot + (int)blendedDelta;
    }
}

/**
 * Offset/Address/Size: 0x114 | 0x801EA770 | size: 0xE0
 */
void cPN_SAnimController::ProcessCallbacks()
{
    bool shouldTrigger;

    if (m_bIgnoreTriggers)
    {
        return;
    }

    cSAnimCallback* pCallback = m_pSAnim->GetCallbackList();

    while (pCallback != nullptr)
    {
        float callbackTime = pCallback->m_fTime;

        if (callbackTime == 0.0f)
        {
            extern float __float_min[];
            callbackTime = __float_min[0];
        }

        float currTime = m_fTime;
        float prevTime = m_fPrevTime;

        if (currTime < prevTime)
        {
            shouldTrigger = false;
            if (callbackTime <= currTime || callbackTime > prevTime)
            {
                shouldTrigger = true;
            }
        }
        else
        {
            shouldTrigger = false;
            if (callbackTime <= currTime && callbackTime > prevTime)
            {
                shouldTrigger = true;
            }
        }

        if (shouldTrigger)
        {
            pCallback->m_funcCallback(pCallback->m_nParam1);
        }

        pCallback = pCallback->next;
    }
}

/**
 * Offset/Address/Size: 0xB0 | 0x801EA70C | size: 0x64
 */
bool cPN_SAnimController::TestTrigger(float normalizedTime) const
{
    bool isTriggering;

    if (normalizedTime == 0.0f)
    {
        extern float __float_min[];
        normalizedTime = __float_min[0];
    }

    float currTime = m_fTime;
    float prevTime = m_fPrevTime;

    if (currTime < prevTime)
    {
        isTriggering = 0;
        if ((normalizedTime <= currTime) || (normalizedTime > prevTime))
        {
            isTriggering = 1;
        }
    }
    else
    {
        isTriggering = 0;
        if (normalizedTime <= currTime && normalizedTime > prevTime)
        {
            isTriggering = 1;
        }
    }
    return isTriggering;
}

/**
 * Offset/Address/Size: 0x20 | 0x801EA67C | size: 0x90
 */
bool cPN_SAnimController::TestFrameTrigger(float frame)
{
    bool isTriggering;
    float normalizedTime = frame / (float)m_pSAnim->m_nNumKeys;

    if (normalizedTime == 0.0f)
    {
        extern float __float_min[];
        normalizedTime = __float_min[0];
    }

    float currTime = m_fTime;
    float prevTime = m_fPrevTime;

    if (currTime < prevTime)
    {
        isTriggering = 0;
        if (normalizedTime <= currTime || normalizedTime > prevTime)
        {
            isTriggering = 1;
        }
    }
    else
    {
        isTriggering = 0;
        if ((normalizedTime <= currTime) && (normalizedTime > prevTime))
        {
            isTriggering = 1;
        }
    }
    return isTriggering;
}

/**
 * Offset/Address/Size: 0x0 | 0x801EA65C | size: 0x20
 */
int cPN_SAnimController::RemapNode(int nodeIndex) const
{
    int remappedIndex = nodeIndex;
    if (m_pAnimRetarget != NULL)
    {
        remappedIndex = m_pAnimRetarget->m_pMap[remappedIndex];
    }
    return remappedIndex;
}
