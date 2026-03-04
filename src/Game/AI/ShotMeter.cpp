#include "Game/AI/ShotMeter.h"
#include "Game/AI/AIPad.h"
#include "Game/AI/AiUtil.h"
#include "Game/AI/Scripts/ScriptQuestions.h"
#include "Game/Ball.h"
#include "Game/CharacterTweaks.h"
#include "Game/Game.h"
#include "Game/GameTweaks.h"
#include "Game/CharacterTriggers.h"

extern cTeam* g_pCurrentlyUpdatingTeam;

/**
 * Offset/Address/Size: 0x6C4 | 0x800627E4 | size: 0x16C
 */
void ShotMeter::Update(float fDeltaT, bool bHoldTime)
{
    if (!bHoldTime)
    {
        m_fTime += fDeltaT;
    }

    switch (m_eShotMeterState)
    {
    case SHOT_METER_ACTIVE:
    {
        if (m_fTime >= g_pGame->m_pGameTweaks->unk2D0)
        {
            float fNetDirection = 0.0f;
            cPlayer* pPrevOwner = g_pBall->m_pOwner;
            if (pPrevOwner != NULL)
            {
                cNet* pOtherNet = pPrevOwner->m_pTeam->GetOtherNet();
                fNetDirection = g_pBall->m_pOwner->m_v3Position.f.x * pOtherNet->m_baseLocation.f.x;
            }
            if (fNetDirection > 0.0f)
            {
                if (g_pBall->GetOwnerFielder() != NULL)
                {
                    if (g_pBall->GetOwnerFielder()->CanDoCaptainShootToScore())
                    {
                        m_eShotMeterState = SHOT_METER_STS_TRANSISTION;
                        break;
                    }
                }
            }
            if (!bHoldTime)
            {
                m_eShotMeterState = SHOT_METER_RELEASED;
            }
        }
        break;
    }
    case SHOT_METER_STS_TRANSISTION:
        m_eShotMeterState = SHOT_METER_STS_ACTIVE;
        break;
    case SHOT_METER_STS_ACTIVE:
    {
        SkillTweaks* pSkillTweaks = SkillTweaks::GetSkillTweaks(g_pCurrentlyUpdatingTeam->m_nSide);
        float fSTSWindupTime = pSkillTweaks->fSTSWindupTime;
        float fShotWindupTime = g_pGame->m_pGameTweaks->unk2D0;
        if (m_fTime >= fShotWindupTime + fSTSWindupTime)
        {
            if (!bHoldTime)
            {
                m_eShotMeterState = SHOT_METER_STS_RELEASED;
            }
        }
        break;
    }
    case SHOT_METER_RELEASED:
    case SHOT_METER_STS_RELEASED:
        m_eShotMeterState = SHOT_METER_INACTIVE;
        break;
    case SHOT_METER_INACTIVE:
    default:
        break;
    }
}

/**
 * Offset/Address/Size: 0x684 | 0x800627A4 | size: 0x40
 */
void ShotMeter::Abort(cFielder* pFielder)
{
    KillWindups(pFielder);
    m_eShotMeterState = SHOT_METER_INACTIVE;
    m_fTime = 0.0f;
}

/**
 * Offset/Address/Size: 0x258 | 0x80062378 | size: 0x42C
 */
void ShotMeter::CalcOneTimerValue(cFielder* pFielder, bool bWasPerfectPass)
{
    FORCE_DONT_INLINE;
}

/**
 * Offset/Address/Size: 0x21C | 0x8006233C | size: 0x3C
 */
float ShotMeter::GetTotalDuration() const
{
    float fShotWindupTime;
    float fSTSWindupTime;
    SkillTweaks* pSkillTweaks = SkillTweaks::GetSkillTweaks(g_pCurrentlyUpdatingTeam->m_nSide);
    fSTSWindupTime = pSkillTweaks->fSTSWindupTime;
    fShotWindupTime = g_pGame->m_pGameTweaks->unk2D0;
    return fShotWindupTime + fSTSWindupTime;
}

/**
 * Offset/Address/Size: 0x1FC | 0x8006231C | size: 0x20
 */
void ShotMeter::Reset()
{
    m_eShotMeterState = SHOT_METER_ACTIVE;
    m_fTime = 0.0f;
    m_fScoreValue = 0.0f;
    m_fSpeedValue = 0.0f;
    m_fSTSValue = 0.0f;
}

static inline void CalcShotAim(cFielder* pFielder, ShotMeter* pMeter)
{
    cAIPad* pPad = pFielder->m_pController;
    float fAimValue = 0.0f;
    if (pPad != NULL)
    {
        if (pPad->GetMovementStickMagnitude() > 0.1f)
        {
            s16 dir = pPad->GetMovementStickDirection();
            if ((s16)(dir + 0x8000) < 0)
            {
                fAimValue = 1.0f;
            }
            else
            {
                fAimValue = -1.0f;
            }
        }
    }
    pMeter->mfSShotAimValue = fAimValue;
}

static inline void CalcScoreValue(cFielder* pFielder, ShotMeter* pMeter)
{
    float fLikelyToScore = LikelyToScore(pFielder);
    float fDistance = PlayerShotDistance(pFielder);

    float fSpeedValue = pMeter->m_fSpeedValue;
    float fShooting = ((FielderTweaks*)pFielder->m_pTweaks)->fShooting;
    GameTweaks* pGameTweaks = g_pGame->m_pGameTweaks;
    float fRatingsWeight = pGameTweaks->unk2D8;
    bool bIsChipShot = pFielder->mActionShotVars.bIsChipShot || pFielder->mActionLooseBallShotVars.bIsChipShot;

    if (!bIsChipShot)
    {
        float fDistWeight = pGameTweaks->unk2E0;
        fShooting *= fRatingsWeight;
        float fOpenWeight = pGameTweaks->unk2DC;
        float fDistVal = fDistance * fDistWeight;
        float fSumD = fDistWeight + fOpenWeight;
        float fOpenVal = fLikelyToScore * fOpenWeight;
        float fSumWeights = fRatingsWeight + fSumD;
        float fResult = fOpenVal + fDistVal;
        float fRemainder = 1.0f - fSumWeights;
        fSpeedValue *= fRemainder;
        fResult = fSpeedValue + fResult;
        pMeter->m_fScoreValue = fShooting + fResult;
    }
    else
    {
        float fChipWeight = pGameTweaks->unk2E4;
        float fGoalieOut = GoalieOutOfPosition(pFielder);
        pGameTweaks = g_pGame->m_pGameTweaks;
        float fGoalieVal = fGoalieOut * fChipWeight;
        fShooting *= fRatingsWeight;
        float fChipOpenWeight = pGameTweaks->unk2E8;
        float fSum = fChipWeight + fChipOpenWeight;
        float fOpenVal = fLikelyToScore * fChipOpenWeight;
        float fSumWeights = fRatingsWeight + fSum;
        float fResult = fGoalieVal + fOpenVal;
        float fRemainder = 1.0f - fSumWeights;
        fSpeedValue *= fRemainder;
        fResult = fSpeedValue + fResult;
        pMeter->m_fScoreValue = fShooting + fResult;
    }
}

/**
 * Offset/Address/Size: 0x0 | 0x80062120 | size: 0x1FC
 * TODO: 97.52% match - 22 volatile float temp register allocation diffs in
 * CalcScoreValue arithmetic (f4/f5 vs f1/f3 in non-chip, f2/f1 swap in chip).
 * Inherent to MWCC register allocator with -inline deferred; CalcScoreValue
 * and CalcShotAim were originally erased static member functions that got inlined.
 */
void ShotMeter::ShotReleased(cFielder* pFielder)
{
    KillWindups(pFielder);
    m_eShotMeterState = SHOT_METER_RELEASED;

    GameTweaks* pGameTweaks = g_pGame->m_pGameTweaks;
    if (m_fTime > pGameTweaks->unk2D0)
    {
        m_fSpeedValue = 1.0f;
    }
    else
    {
        m_fSpeedValue = Interpolate(0.0f, 1.0f, m_fTime / pGameTweaks->unk2D0);
    }

    CalcScoreValue(pFielder, this);
    CalcShotAim(pFielder, this);
    m_fTime = 0.0f;
}
