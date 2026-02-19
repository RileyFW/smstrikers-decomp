#include "Game/AI/ShotMeter.h"
#include "Game/Ball.h"
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

/**
 * Offset/Address/Size: 0x0 | 0x80062120 | size: 0x1FC
 */
void ShotMeter::ShotReleased(cFielder*)
{
}
