#include "Game/CharacterTriggers.h"
#include "Game/Player.h"
#include "Game/Ball.h"
#include "Game/AI/Fielder.h"
#include "Game/AI/Powerups.h"
#include "Game/ReplayManager.h"
#include "Game/RumbleActions.h"
#include "Game/SAnim/pnSAnimController.h"
#include "Game/SAnim.h"
#include "Game/SAnim/pnSAnimController.h"
#include "Game/Sys/debug.h"

/**
 * Offset/Address/Size: 0x5190 | 0x801A3F40 | size: 0x94
 */
void UpdateEmitterFromCharacterIdxWithoutAnimController(EmissionController& emitter, int index)
{
    if (ReplayManager::Instance()->mRender != NULL)
    {
        ReplayManager* mgr1 = ReplayManager::Instance();
        DrawableCharacter* pChar = &mgr1->mRender->mCharacters[index];
        emitter.SetPosition(pChar->mPosition);
        ReplayManager* mgr2 = ReplayManager::Instance();
        pChar = &mgr2->mRender->mCharacters[index];
        emitter.SetVelocity(pChar->mVelocity);
        ReplayManager* mgr3 = ReplayManager::Instance();
        pChar = &mgr3->mRender->mCharacters[index];
        emitter.SetPoseAccumulator(*pChar->mPoseAccumulator);
    }
}

/**
 * Offset/Address/Size: 0x50B0 | 0x801A3E60 | size: 0xE0
 */
void UpdateEmitterFromCharacterIdxWithCoordSys(EmissionController&, int)
{
}

/**
 * Offset/Address/Size: 0x4FB8 | 0x801A3D68 | size: 0xF8
 */
void UpdateEmitterFromCharacter(EmissionController&)
{
}

/**
 * Offset/Address/Size: 0x4F34 | 0x801A3CE4 | size: 0x84
 */
void UpdateEmitterPoseFromCharacter(EmissionController& emitter)
{
    if (ReplayManager::Instance()->mRender != NULL)
    {
        int index = emitter.m_uUserData;
        ReplayManager* mgr1 = ReplayManager::Instance();
        DrawableCharacter* pChar = &mgr1->mRender->mCharacters[index];
        emitter.SetPoseAccumulator(*pChar->mPoseAccumulator);
        ReplayManager* mgr2 = ReplayManager::Instance();
        pChar = &mgr2->mRender->mCharacters[index];
        emitter.SetAnimController(pChar->GetAnimController());
    }
}

/**
 * Offset/Address/Size: 0x4ECC | 0x801A3C7C | size: 0x68
 */
void UpdateEmitterFromBall(EmissionController& emitter)
{
    if (ReplayManager::Instance()->mRender != NULL)
    {
        ReplayManager* mgr1 = ReplayManager::Instance();
        emitter.SetPosition(mgr1->mRender->mBall.mPosition);
        ReplayManager* mgr2 = ReplayManager::Instance();
        emitter.SetVelocity(mgr2->mRender->mBall.mVelocity);
    }
}

/**
 * Offset/Address/Size: 0x4D18 | 0x801A3AC8 | size: 0x1B4
 */
void EmitGeneric(cCharacter*, const char*, const char*)
{
}

/**
 * Offset/Address/Size: 0x2B1C | 0x801A18CC | size: 0x21FC
 */
void CharacterTriggerHandler(unsigned int uParam)
{
}

/**
 * Offset/Address/Size: 0x2A64 | 0x801A1814 | size: 0xB8
 */
void GetAnimTriggerInfo(cCharacter*, int, bool (*)(float, float, unsigned long, float, void*), void*)
{
}

/**
 * Offset/Address/Size: 0x2A18 | 0x801A17C8 | size: 0x4C
 */
float GetCurrentAnimTriggerTime(cCharacter* pCharacter, unsigned long uTriggerID, unsigned int uInstanceNumber)
{
    cSAnimCallback* cb = pCharacter->m_pCurrentAnimController->m_pSAnim->m_pCallbackList;
    unsigned int count = 0;

    while (cb != NULL)
    {
        cSAnim* pCallbackAnim = (cSAnim*)cb->m_nParam1;
        if (uTriggerID == pCallbackAnim->m_uHashID)
        {
            count++;
            if (count - 1 == uInstanceNumber)
            {
                return cb->m_fTime;
            }
        }
        cb = cb->next;
    }
    return -1.0f;
}

/**
 * Offset/Address/Size: 0x281C | 0x801A15CC | size: 0x1FC
 */
void EmitBallImpact(cPlayer*, bool)
{
}

/**
 * Offset/Address/Size: 0x2658 | 0x801A1408 | size: 0x1C4
 */
void EmitBallPass(cPlayer*)
{
}

/**
 * Offset/Address/Size: 0x1B10 | 0x801A08C0 | size: 0xB48
 */
void EmitBallShot(cPlayer*, eBallShotEffectType, cPlayer*, bool)
{
}

/**
 * Offset/Address/Size: 0x1A44 | 0x801A07F4 | size: 0xCC
 */
void KillBallShot(const char*, bool)
{
}

/**
 * Offset/Address/Size: 0x1A18 | 0x801A07C8 | size: 0x2C
 */
void EmitSolidRumble(cPlayer* player)
{
    BeginRumbleAction(RUMBLE_SHOT_CONTACT, player->GetGlobalPad());
}

/**
 * Offset/Address/Size: 0x18D0 | 0x801A0680 | size: 0x148
 */
void EmitElectrocutionExplosion(cCharacter*)
{
}

/**
 * Offset/Address/Size: 0x1738 | 0x801A04E8 | size: 0x198
 */
void EmitDaze(cPlayer*)
{
}

/**
 * Offset/Address/Size: 0x16FC | 0x801A04AC | size: 0x3C
 */
void KillDaze(cPlayer* player)
{
    player->KillEffect(fxGetGroup("dazed"));
}

/**
 * Offset/Address/Size: 0x1598 | 0x801A0348 | size: 0x164
 */
void EmitFreeze(cPlayer*)
{
}

/**
 * Offset/Address/Size: 0x1420 | 0x801A01D0 | size: 0x178
 */
void EmitUnFreeze(cPlayer*)
{
}

/**
 * Offset/Address/Size: 0x1400 | 0x801A01B0 | size: 0x20
 */
void ElectrocutionFinishedCallback(EmissionController&)
{
}

/**
 * Offset/Address/Size: 0x1290 | 0x801A0040 | size: 0x170
 */
void ElectrocutionUpdateCallback(EmissionController&)
{
}

/**
 * Offset/Address/Size: 0x1060 | 0x8019FE10 | size: 0x230
 */
void CharacterElectrocutionEffect(cCharacter* pCharacter, const nlVector3& v3Position, const nlVector3& v3Normal)
{
}

/**
 * Offset/Address/Size: 0xFF4 | 0x8019FDA4 | size: 0x6C
 */
void EmitBallWallHit(const char* name)
{
    EmissionController* pController = EmissionManager::Create(fxGetGroup(name), 0);
    static const nlVector3 velocity = { 0.0f, 0.0f, 0.0f };
    nlVector3 vel = velocity;
    pController->SetVelocity(vel);
    pController->SetPosition(g_pBall->m_v3Position);
}

/**
 * Offset/Address/Size: 0xE7C | 0x8019FC2C | size: 0x178
 */
void EmitGoalieCatch(cPlayer*, const char*, bool)
{
}

/**
 * Offset/Address/Size: 0xD2C | 0x8019FADC | size: 0x150
 */
void EmitShootToScoreHyperStrike(cFielder*)
{
}

/**
 * Offset/Address/Size: 0xC04 | 0x8019F9B4 | size: 0x128
 */
void EmitWindupAtBall(cCharacter*, const char*)
{
}

/**
 * Offset/Address/Size: 0xB00 | 0x8019F8B0 | size: 0x104
 */
void EmitWindupAtCharacter(cCharacter*, const char*)
{
}

/**
 * Offset/Address/Size: 0xA8C | 0x8019F83C | size: 0x74
 */
void KillWindups(cCharacter* pCharacter) {
    KillWindup(pCharacter, "ball_shot_windup", true);
    KillWindup(pCharacter, "ball_pass_windup", true);
    KillWindup(pCharacter, "ball_sts_windup", true);
    KillWindup(pCharacter, "shoot_to_score_windup", true);
}

/**
 * Offset/Address/Size: 0x87C | 0x8019F62C | size: 0x210
 */
void KillWindup(cCharacter*, const char*, bool)
{
    FORCE_DONT_INLINE;
}

/**
 * Offset/Address/Size: 0x838 | 0x8019F5E8 | size: 0x44
 */
void EmitTurbo(cPlayer* player, const char* unused)
{
    player->InitBlur(12);
    BeginRumbleAction((eRumbleActionPreset)0, player->GetGlobalPad());
}

/**
 * Offset/Address/Size: 0x6F0 | 0x8019F4A0 | size: 0x148
 */
void EmitDust(cPlayer*, const char*)
{
}

/**
 * Offset/Address/Size: 0x570 | 0x8019F320 | size: 0x180
 */
void EmitMushroom(cFielder*)
{
}

/**
 * Offset/Address/Size: 0x510 | 0x8019F2C0 | size: 0x60
 */
void KillMushroom(cFielder* pFielder)
{
    pFielder->StopSFX(Audio::CHARSFX_PWRUP_MUSH_IN_EFFECT);
    PowerupBase::PlayPowerupSound(POWER_UP_MUSHROOM, PowerupBase::PWRUP_SOUND_END, pFielder->m_pPhysicsCharacter, 1.0f);
    pFielder->EndBlur();
    tDebugPrintManager::Print(DC_SOUND, "***KillMushroom()***\n");
}

/**
 * Offset/Address/Size: 0x388 | 0x8019F138 | size: 0x188
 */
void EmitStar(cFielder*)
{
}

/**
 * Offset/Address/Size: 0x320 | 0x8019F0D0 | size: 0x68
 */
void KillStar(cFielder* pFielder)
{
    pFielder->StopSFX(Audio::CHARSFX_PWRUP_STAR_IN_EFFECT);
    pFielder->KillEffect(fxGetGroup("star"));
    pFielder->EndBlur();
    pFielder->m_pEffectsTexturing = NULL;
    tDebugPrintManager::Print(DC_SOUND, "***KillStar()***\n");
}

/**
 * Offset/Address/Size: 0x2C8 | 0x8019F078 | size: 0x58
 */
void EmitChainBite(cFielder*)
{
}

/**
 * Offset/Address/Size: 0x17C | 0x8019EF2C | size: 0x14C
 */
void EmitTackleImpact(cPlayer*)
{
}

/**
 * Offset/Address/Size: 0x44 | 0x8019EDF4 | size: 0x138
 */
void EmitSlideTackleTrail(cCharacter*)
{
}

/**
 * Offset/Address/Size: 0x0 | 0x8019EDB0 | size: 0x44
 */
void KillSlideTackleTrail(cCharacter* pCharacter)
{
    const EffectsGroup* pGroup = fxGetGroup("SLIDE_TRAIL");
    pCharacter->EndEffect(pGroup);
}
