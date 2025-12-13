#include "Game/AI/ShotMeter.h"
#include "Game/Game.h"
#include "Game/GameTweaks.h"
#include "Game/CharacterTriggers.h"

extern cTeam* g_pCurrentlyUpdatingTeam;

/**
 * Offset/Address/Size: 0x6C4 | 0x800627E4 | size: 0x16C
 */
void ShotMeter::Update(float, bool)
{
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
void ShotMeter::CalcOneTimerValue(cFielder*, bool)
{
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
