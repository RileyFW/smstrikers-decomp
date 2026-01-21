#include "Game/AI/Fielder.h"
#include "Game/AI/AIPlay.h"
#include "Game/AI/AiUtil.h"
#include "Game/AI/ShotMeter.h"
#include "Game/AI/Scripts/ScriptQuestions.h"
#include "Game/AnimInventory.h"
#include "Game/Ball.h"
#include "Game/CharacterTriggers.h"
#include "Game/Game.h"
#include "Game/GameInfo.h"
#include "Game/Render/Bowser.h"
#include "Game/Render/ChainChomp.h"
#include "Game/DB/StatsTracker.h"
#include "Game/RumbleActions.h"
#include "Game/SAnim/pnBlender.h"
#include "Game/SAnim/pnSingleAxisBlender.h"
#include "Game/SAnim/pnSAnimController.h"
#include "Game/SAnim.h"
#include "Game/Sys/eventman.h"
#include "NL/nlSlotPool.h"
#include "math.h"

extern bool g_e3_Build;

const nlVector3 v3Zero = { 0.0f, 0.0f, 0.0f };

// Constants from .sdata2 for IsBallAwayFromCarrier
// @4959 = .sdata2:0x80374EF0
// @4960 = .sdata2:0x80374EF4
// TODO: Extract actual float values from binary
static const float fBallAwayFromCarrierMinTime = 0.0f; // @4959
static const float fBallAwayFromCarrierMaxTime = 1.0f; // @4960

static LooseBallContactAnimInfo gOneTimerIdleGroundContactAnims[4];
static LooseBallContactAnimInfo gOneTimerIdleVolleyContactAnims[4];
static LooseBallContactAnimInfo gOneTimerLeadGroundContactAnims[4];
static LooseBallContactAnimInfo gOneTimerLeadVolleyContactAnims[4];

// Static arrays for GetReceivePassBallContactAnimInfo
static LooseBallContactAnimInfo IdleGroundContactAnims[1] = {
    { 0x37, 3.0f, 0xFFFF, 0xFFFF }
};

static LooseBallContactAnimInfo IdleVolleyContactAnims[1] = {
    { 0x38, 9.0f, 0xFFFF, 0xFFFF }
};

static LooseBallContactAnimInfo LeadGroundContactAnims[4] = {
    { 0x39, 7.0f, 0xE000, 0x2000 },
    { 0x3A, 7.0f, 0xA000, 0xE000 },
    { 0x3C, 7.0f, 0x6000, 0xA000 },
    { 0x3B, 7.0f, 0x2000, 0x6000 }
};

static LooseBallContactAnimInfo LeadVolleyContactAnims[3] = {
    { 0x3D, 10.0f, 0xE000, 0x2000 },
    { 0x3F, 9.0f, 0x2000, 0x8000 },
    { 0x3E, 9.0f, 0x8000, 0xE000 }
};

// static inline bool IsTurboingAnimID(s32 animID)
// {
//     bool result = false;
//     if (animID == 0x1D || animID == 0x1E || animID == 0x1F || animID == 0x20 || animID == 0x21 || animID == 0x22)
//     {
//         result = true;
//     }
//     return result;
// }

// static inline bool IsTurboingWithoutBallAnimID(s32 animID)
// {
//     bool result = false;
//     if (animID == 0x0F || animID == 0x10 || animID == 0x11)
//     {
//         result = true;
//     }
//     return result;
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x80026B20 | size: 0x8
//  */
// void PlayerAttackData::GetID()
// {
// }

// /**
//  * Offset/Address/Size: 0x8 | 0x80026B18 | size: 0x8
//  */
// void cNet::GetNetWidth()
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x80026B10 | size: 0x8
//  */
// void cNet::GetNetHeight()
// {
// }

// /**
//  * Offset/Address/Size: 0x3C | 0x80026AD4 | size: 0x3C
//  */
// FilteredRandomReal::~FilteredRandomReal()
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x80026A98 | size: 0x3C
//  */
// FilteredRandomChance::~FilteredRandomChance()
// {
// }

// /**
//  * Offset/Address/Size: 0xD2E8 | 0x80026624 | size: 0x474
//  */
// cFielder::cFielder(int, int, eCharacterClass, const int*, cSHierarchy*, cAnimInventory*, const CharacterPhysicsData*, FielderTweaks*, AnimRetargetList*)
// {
// }

/**
 * Offset/Address/Size: 0xD264 | 0x800265A0 | size: 0x84
 */
cFielder::~cFielder()
{
}

/**
 * Offset/Address/Size: 0xD240 | 0x8002657C | size: 0x24
 */
void cFielder::AbortPlay()
{
    m_pCurrentPlay->ClearPlay();
}

/**
 * Offset/Address/Size: 0xD1D4 | 0x80026510 | size: 0x6C
 */
void cFielder::AbortPendingThoughts()
{
    g_pGame->AbortPendingThought(mThoughtHashCalcDesire);
    g_pGame->AbortPendingThought(mThoughtHashInitRunToNet);
    g_pGame->AbortPendingThought(mThoughtHashInitGetOpen);
    g_pGame->AbortPendingThought(mThoughtHashInitWindupPass);
    g_pGame->AbortPendingThought(mThoughtHashInitCutAndBreak);
    ClearQueuedDesire();
}

/**
 * Offset/Address/Size: 0xC890 | 0x80025BCC | size: 0x944
 */
void cFielder::CalculateNewDesire()
{
}

/**
 * Offset/Address/Size: 0xC814 | 0x80025B50 | size: 0x7C
 */
bool cFielder::CanDoCaptainShootToScore()
{
    if (nlSingleton<GameInfoManager>::Instance()->GetGameplayOptions().Shoot2Score
        && (IsCaptain() || nlSingleton<GameInfoManager>::Instance()->GetTeam(g_pBall->m_pOwner->m_pTeam->m_nSide) == TEAM_MYSTERY))
    {
        return true;
    }

    return false;
}

/**
 * Offset/Address/Size: 0xC648 | 0x80025984 | size: 0x1CC
 */
bool cFielder::CanLooseBallShoot()
{
    if ((g_pBall->m_pOwner == NULL)
        && (g_pBall->m_pPassTarget == NULL)
        && (g_pBall->m_tShotTimer.m_uPackedTime == 0)
        && (g_pBall->m_unk_0xA6 == 0))
    {

        // Get animation from one timer lead ground contact anims
        u32 nNumKeys = m_pAnimInventory->GetAnim(gOneTimerLeadGroundContactAnims[0].nAnimID)->m_nNumKeys;
        float temp_f6 = ((float)nNumKeys / 30.0f) * (gOneTimerLeadGroundContactAnims[0].fAnimContactFrame / (float)nNumKeys);

        // Calculate predicted ball position at contact frame
        nlVector3 v3PredictedPos;
        nlVec3Set(v3PredictedPos,
            (temp_f6 * g_pBall->m_v3Velocity.f.x) + g_pBall->m_v3Position.f.x,
            (temp_f6 * g_pBall->m_v3Velocity.f.y) + g_pBall->m_v3Position.f.y,
            (temp_f6 * g_pBall->m_v3Velocity.f.z) + g_pBall->m_v3Position.f.z);

        // Get facing delta to predicted position
        s16 facingDelta = GetFacingDeltaToPosition(v3PredictedPos);
        facingDelta = (facingDelta < 0) ? -facingDelta : facingDelta;

        float fInterpolatedValue = InterpolateRangeClamped(1.75f, 2.75f, 32768.0f, 16384.0f, facingDelta);

        if (v3PredictedPos.f.z < 1.0f)
        {
            // Check distance squared from fielder to predicted position
            float fDeltaX = v3PredictedPos.f.x - m_v3Position.f.x;
            float fDeltaY = v3PredictedPos.f.y - m_v3Position.f.y;
            float fDistanceSquared = fDeltaX * fDeltaX + fDeltaY * fDeltaY;

            if (fDistanceSquared < fInterpolatedValue * fInterpolatedValue)
            {
                float fMyInterceptAbility = AbleToInterceptBall(this);
                float fOtherInterceptAbility = AbleToInterceptBall(m_pTeam->GetOtherTeam()->GetStriker());

                if (((float)fabs(fOtherInterceptAbility - fMyInterceptAbility) > 0.03f) && (fMyInterceptAbility > fOtherInterceptAbility))
                {
                    return true;
                }
            }
        }
    }
    return false;
}

/**
 * Offset/Address/Size: 0xC468 | 0x800257A4 | size: 0x1E0
 */
void cFielder::CanLooseBallPass()
{
}

/**
 * Offset/Address/Size: 0xC410 | 0x8002574C | size: 0x58
 */
bool cFielder::CanReceivePass()
{
    bool bCanReceivePass = false;
    if (!IsFallenDown(0.0f) && (m_tFrozenTimer.m_uPackedTime == 0))
    {
        bCanReceivePass = true;
    }

    return bCanReceivePass;
}

/**
 * Offset/Address/Size: 0xC3D8 | 0x80025714 | size: 0x38
 */
void cFielder::SetMark(cFielder* pMark)
{
    if (m_pMark != nullptr && m_pMark->m_pMarker == this)
    {
        m_pMark->m_pMarker = nullptr;
    }

    m_pMark = pMark;

    if (m_pMark != nullptr)
    {
        pMark->m_pMarker = this;
    }
}

/**
 * Offset/Address/Size: 0xAEBC | 0x800241F8 | size: 0x151C
 */
void cFielder::CollideWithCharacterCallback(CollisionPlayerPlayerData*)
{
}

/**
 * Offset/Address/Size: 0xAD6C | 0x800240A8 | size: 0x150
 */
bool cFielder::CollideWithShellCallback(ePowerupSize eSize, bool bUnknown, const nlVector3& rv3Pos1, const nlVector3& rv3Pos2)
{
    // Check if player is fallen down
    if (!IsFallenDown(0.0f) && (m_eActionState != ACTION_POST_WHISTLE))
    {
        bool bShouldSkip = false;
        if ((m_ePowerup == POWER_UP_STAR && m_tPowerupEffectTime.m_uPackedTime != 0) || (mActionShootToScoreVars.isCurrentlyInvincible != 0))
        {
            bShouldSkip = true;
        }

        if (!bShouldSkip)
        {
            if (eSize == POWERUPSIZE_LARGE)
            {
                InitActionSquishReact(rv3Pos2);
            }
            else
            {
                InitActionShellReact(rv3Pos1, rv3Pos2);

                ePowerupSize eSoundSize = eSize;
                if (bUnknown)
                {
                    eSoundSize = POWERUPSIZE_LARGE;
                }

                switch (eSoundSize)
                {
                case POWERUPSIZE_SMALL:
                    PlayAttackReactionSounds(g_pGame->m_pGameTweaks->unk254);
                    break;
                case POWERUPSIZE_MEDIUM:
                    PlayAttackReactionSounds(g_pGame->m_pGameTweaks->unk258);
                    break;
                case POWERUPSIZE_LARGE:
                    PlayAttackReactionSounds(g_pGame->m_pGameTweaks->unk24C);
                    break;
                }
            }

            // Clear pass target if this fielder is the current pass target
            if (g_pBall->m_pPassTarget != nullptr && g_pBall->m_pPassTarget == this)
            {
                g_pBall->ClearPassTarget();
            }

            return true;
        }
    }
    return false;
}

/**
 * Offset/Address/Size: 0xAB90 | 0x80023ECC | size: 0x1DC
 */
bool cFielder::CollideWithFreezeCallback()
{
    bool bShouldSkip = false;

    if ((m_ePowerup == POWER_UP_STAR && m_tPowerupEffectTime.m_uPackedTime != 0) || mActionShootToScoreVars.isCurrentlyInvincible != 0)
    {
        bShouldSkip = true;
    }

    // If invincible, don't freeze
    if ((!bShouldSkip) && (m_tFrozenTimer.m_uPackedTime == 0))
    {
        if (m_eAnimID != 0x74 && m_eAnimID != 0x75)
        {

            // If player has the ball, release it and shoot it
            if (m_pBall != nullptr)
            {
                ReleaseBall();
                ShootBallDueToContact(m_v3Velocity);

                switch (m_eActionState)
                {
                case ACTION_SHOT:
                    break;
                case ACTION_RUNNING_WB:
                case ACTION_RUNNING_WB_TURBO:
                case ACTION_RUNNING_WB_TURBO_TURN:
                case ACTION_SHOOT_TO_SCORE:
                    InitActionRunning();
                    break;
                }

                m_pShotMeter->Abort(this);
            }

            float fFreezeDuration = g_pGame->m_pGameTweaks->fFreezeShellFrozenTime;
            m_tFrozenTimer.SetSeconds(fFreezeDuration);

            m_fDesiredSpeed = 0.0f;
            m_fActualSpeed = m_fDesiredSpeed;
            SetVelocity(v3Zero);

            if ((fFreezeDuration > 0.0f) && (m_eFielderDesireState != FIELDERDESIRE_FINISH_ACTION))
            {
                g_pGame->AbortPendingThought(mThoughtHashCalcDesire);
                g_pGame->AbortPendingThought(mThoughtHashInitRunToNet);
                g_pGame->AbortPendingThought(mThoughtHashInitGetOpen);
                g_pGame->AbortPendingThought(mThoughtHashInitWindupPass);
                g_pGame->AbortPendingThought(mThoughtHashInitCutAndBreak);
                ClearQueuedDesire();
                EndDesire(false);
            }

            SetVelocity(v3Zero);
            m_fDesiredSpeed = 0.0f;
            m_fActualSpeed = m_fDesiredSpeed;

            KillDaze(this);
            EmitFreeze(this);

            if (g_pBall->m_pPassTarget != nullptr && g_pBall->m_pPassTarget == this)
            {
                g_pBall->ClearPassTarget();
            }
            return true;
        }
    }
    return false;
}

/**
 * Offset/Address/Size: 0xAACC | 0x80023E08 | size: 0xC4
 */
bool cFielder::CollideWithBananaCallback(const nlVector3& rv3BananaPosition)
{
    if (!IsFallenDown(0.0f) && (m_eActionState != ACTION_POST_WHISTLE))
    {
        bool bShouldSkip = false;
        if ((m_ePowerup == POWER_UP_STAR && m_tPowerupEffectTime.m_uPackedTime != 0) || mActionShootToScoreVars.isCurrentlyInvincible != 0)
        {
            bShouldSkip = true;
        }

        if ((!bShouldSkip) && (m_tFrozenTimer.m_uPackedTime == 0))
        {
            if ((g_pBall->m_pPassTarget != nullptr) && (g_pBall->m_pPassTarget == this))
            {
                g_pBall->ClearPassTarget();
            }
            InitActionBananaReact(rv3BananaPosition);
            return true;
        }
    }
    return false;
}

static bool IsGameplayOrOvertime(eGameState state)
{
    bool result = false;
    if (state == GS_GAMEPLAY || state == GS_OVERTIME)
    {
        result = true;
    }
    return result;
}

/**
 * Offset/Address/Size: 0xA910 | 0x80023C4C | size: 0x1BC
 */
void cFielder::CollideWithChainCallback(ChainChomp* pChainChomp)
{
    if (mActionShootToScoreVars.isInUnbreakablePart == 0)
    {
        // Clear pass target if this fielder is the current pass target
        if (g_pBall->m_pPassTarget != nullptr && g_pBall->m_pPassTarget == this)
        {
            g_pBall->ClearPassTarget();
        }

        // Play powerup sound if not fallen down
        if (!IsFallenDown(0.0f))
        {
            PowerupBase::PlayPowerupSound(POWER_UP_CHAIN_CHOMP, PowerupBase::PWRUP_SOUND_HIT, pChainChomp->mpPhysObj, 100.0f);
        }

        float offsetZ = 0.0f;

        float rightFootZ;
        float leftFootZ;
        float ballJointZ;

        leftFootZ = offsetZ + GetJointPosition(m_nLeftFootJointIndex).f.z;
        rightFootZ = offsetZ + GetJointPosition(m_nRightFootJointIndex).f.z;
        ballJointZ = offsetZ + GetJointPosition(m_nHeadJointIndex).f.z;

        // Determine if player is in air (all joints above ground)
        bool bInAir;
        if (leftFootZ > 1.0f && rightFootZ > 1.0f && ballJointZ > 1.0f)
        {
            bInAir = true;
        }
        else
        {
            bInAir = false;
        }

        if (bInAir)
        {
            // Player is in air - use bomb react
            InitActionBombReact(m_v3Position, 0.0f);
            EmitTackleImpact(this);
        }
        else
        {
            // Player is on ground - use squish react
            InitActionSquishReact(pChainChomp->mv3Velocity);
            EmitChainBite(this);
        }

        if (pChainChomp->mpThrower != nullptr)
        {
            if (g_pGame->IsGameplayOrOvertime() && !IsOnSameTeam(pChainChomp->mpThrower))
            {
                cFielder* pThrower = pChainChomp->mpThrower;
                nlSingleton<StatsTracker>::Instance()->TrackStat(
                    STATS_POWERUPS_HIT,
                    pThrower->m_pTeam->m_nSide,
                    pThrower->m_ID,
                    pChainChomp->mnThrowerPadID,
                    0,
                    0,
                    0);
            }
        }
    }
}

/**
 * Offset/Address/Size: 0xA804 | 0x80023B40 | size: 0x10C
 */
void cFielder::CollideWithBowserCallback(Bowser* pBowser)
{
    if (mActionShootToScoreVars.isInUnbreakablePart == 0)
    {
        if (g_pBall->m_pPassTarget != nullptr && g_pBall->m_pPassTarget == this)
        {
            g_pBall->ClearPassTarget();
        }

        // If this fielder owns the ball, release and shoot it
        if (g_pBall->m_pOwner == this)
        {
            ReleaseBall();

            nlVector3 v3Direction;
            nlVec3Set(v3Direction,
                g_pBall->m_v3Position.f.x - pBowser->mv3Position.f.x,
                g_pBall->m_v3Position.f.y - pBowser->mv3Position.f.y,
                g_pBall->m_v3Position.f.z - pBowser->mv3Position.f.z);
            nlVec3Scale(v3Direction, v3Direction, 2.0f);

            v3Direction.f.z = 3.0f + nlRandomf(4.0f, &nlDefaultSeed);

            g_pBall->ShootRelease(v3Direction, SPINTYPE_NONE);
        }

        if (!IsFallenDown(0.0f))
        {
            InitActionBombHitReact(pBowser->mv3Position);
        }
    }
}

/**
 * Offset/Address/Size: 0xA70C | 0x80023A48 | size: 0xF8
 */
void cFielder::CollideWithWallCallback(const CollisionPlayerWallData* eventData)
{
}

/**
 * Offset/Address/Size: 0xA6D0 | 0x80023A0C | size: 0x3C
 */
void cFielder::ClearPassTargetIfAmThePassTarget()
{
    cBall* pBall = g_pBall;
    if (pBall->m_pPassTarget != nullptr)
    {
        if (pBall->m_pPassTarget == this)
        {
            pBall->ClearPassTarget();
        }
    }
}

/**
 * Offset/Address/Size: 0xA6B8 | 0x800239F4 | size: 0x18
 */
bool cFielder::UsePerfectPass()
{
    return g_pBall->mbHyperSTS != 0;
}

/**
 * Offset/Address/Size: 0xA6A8 | 0x800239E4 | size: 0x10
 */
bool cFielder::IsPlayingPowerupAnim()
{
    return m_nPowerupAnimID >= 0;
}

/**
 * Offset/Address/Size: 0xA5DC | 0x80023918 | size: 0xCC
 */
bool cFielder::IsCharacterInAir(bool) const
{
    return false;
}

/**
 * Offset/Address/Size: 0xA548 | 0x80023884 | size: 0x94
 */
bool cFielder::IsTurboing()
{
    FORCE_DONT_INLINE;
    bool bIsTurboing = false;

    if (m_pBall != nullptr)
    {
        bIsTurboing = IsTurboingAnimID();
        if (bIsTurboing == false)
        {
            return false;
        }
    }
    else
    {
        bIsTurboing = IsTurboingWithoutBallAnimID();
        if (bIsTurboing == false)
        {
            return false;
        }
    }
    return bIsTurboing;

    // // Check if animation ID is one of the turbo animations without ball
    // s32 animID = m_eAnimID;
    // bIsTurboing = false;
    // if (animID == 0x0F || animID == 0x10 || animID == 0x11)
    // {
    //     bIsTurboing = true;
    // }
    // if (bIsTurboing == false)
    // {
    //     return false;
    // }

    // return true;
}

/**
 * Offset/Address/Size: 0xA50C | 0x80023848 | size: 0x3C
 */
bool cFielder::IsRunning() const
{
    FORCE_DONT_INLINE;
    return false;
}

/**
 * Offset/Address/Size: 0xA4D8 | 0x80023814 | size: 0x34
 */
bool cFielder::IsInvincible() const
{
    bool result = false;

    if (((m_ePowerup == POWER_UP_STAR) && (m_tPowerupEffectTime.m_uPackedTime != 0)) || (mActionShootToScoreVars.isCurrentlyInvincible != 0))
    {
        result = true;
    }

    return result;
}

/**
 * Offset/Address/Size: 0xA49C | 0x800237D8 | size: 0x3C
 */
bool cFielder::IsBallAwayFromCarrier() const
{
    if (m_eActionState == ACTION_RUNNING_WB_TURBO)
    {
        if ((m_pCurrentAnimController->m_fTime > 0.2f) && (m_pCurrentAnimController->m_fTime < 0.975f))
        {
            return true;
        }
    }
    return false;
}

/**
 * Offset/Address/Size: 0xA468 | 0x800237A4 | size: 0x34
 */
bool cFielder::IsReceivingVolleyPass() const
{
    eFielderDesireState desireState = m_eFielderDesireState;
    bool result = false;

    if (desireState == FIELDERDESIRE_RECEIVE_PASS_FROM_IDLE || desireState == FIELDERDESIRE_RECEIVE_PASS_FROM_RUN)
    {
        result = m_DesireReceivePassSharedVars.bVolleyPassReceive;
    }
    else if (desireState == FIELDERDESIRE_ONETIMER)
    {
        result = m_DesireOneTimerVars.bVolleyPassReceive;
    }

    return result;
}

/**
 * Offset/Address/Size: 0xA444 | 0x80023780 | size: 0x24
 */
bool cFielder::IsPreparingForOneTimer() const
{
    bool result = false;
    if (m_eFielderDesireState == FIELDERDESIRE_ONETIMER)
    {
        result = m_eDesireSubState == 0;
    }
    return result;
}

/**
 * Offset/Address/Size: 0xA2D0 | 0x8002360C | size: 0x174
 */
void cFielder::CleanUpAction()
{
}

/**
 * Offset/Address/Size: 0xA258 | 0x80023594 | size: 0x78
 */
void cFielder::CleanUpPowerupEffect()
{
    switch (m_ePowerup)
    {
    case POWER_UP_STAR:
        KillStar(this);
        m_ePowerup = POWER_UP_NONE;
        mnNumPowerups = 0;
        m_tPowerupEffectTime.m_uPackedTime = 0;
        break;

    case POWER_UP_MUSHROOM:
        KillMushroom(this);
        m_ePowerup = POWER_UP_NONE;
        mnNumPowerups = 0;
        m_tPowerupEffectTime.m_uPackedTime = 0;
        break;

    default:
        break;
    }
}

/**
 * Offset/Address/Size: 0x9DFC | 0x80023138 | size: 0x45C
 */
void cFielder::CalcRegularShot(nlVector3&, nlVector3&)
{
}

/**
 * Offset/Address/Size: 0x95C8 | 0x80022904 | size: 0x834
 */
void cFielder::CalcShootToScoreShot(nlVector3&, nlVector3&)
{
}

/**
 * Offset/Address/Size: 0x9594 | 0x800228D0 | size: 0x34
 */
void cFielder::SetSlideAttackSuccessFlag()
{
    mActionSlideAttackVars.bAttackSucceeded = true;
    BeginRumbleAction(RUMBLE_MEDIUM_CONTACT, GetGlobalPad());
}

/**
 * Offset/Address/Size: 0x9564 | 0x800228A0 | size: 0x30
 */
void cFielder::SetKickOffWaitTime()
{
    mbCanKickoff = true;
    mtKickOffWaitTimer.SetSeconds(2.0f);
}

/**
 * Offset/Address/Size: 0x94B8 | 0x800227F4 | size: 0xAC
 */
void cFielder::SetBombImpactTime(const nlVector3& v3BombImpactLocation, float fBombImpactRadius)
{
    float fDeltaX = m_v3Position.f.x - v3BombImpactLocation.f.x;
    float fDeltaY = m_v3Position.f.y - v3BombImpactLocation.f.y;
    float fDeltaZ = m_v3Position.f.z - v3BombImpactLocation.f.z;

    float fDistanceSquared = fDeltaX * fDeltaX + fDeltaY * fDeltaY + fDeltaZ * fDeltaZ;
    float fTime = nlSqrt(fDistanceSquared, true) / 25.f;

    mtBombImpactTime.SetSeconds(fTime);
    mv3BombImpactLocation = v3BombImpactLocation;
    mfBombImpactRadius = fBombImpactRadius;
}

/**
 * Offset/Address/Size: 0x93F4 | 0x80022730 | size: 0xC4
 */
void cFielder::SetDesireDuration(float, bool)
{
}

/**
 * Offset/Address/Size: 0x921C | 0x80022558 | size: 0x1D8
 */
void cFielder::ShootBallDueToContact(const nlVector3& aShootDirection)
{
    FORCE_DONT_INLINE;
}

/**
 * Offset/Address/Size: 0x918C | 0x800224C8 | size: 0x90
 */
void cFielder::ShootBallDueToContact(unsigned short aAngle)
{
    bool bBallAwayFromCarrier;

    if ((m_eActionState == ACTION_RUNNING_WB_TURBO) && ((m_pCurrentAnimController->m_fTime > 0.2f) && (m_pCurrentAnimController->m_fTime < 0.975f)))
    {
        bBallAwayFromCarrier = true;
    }
    else
    {
        bBallAwayFromCarrier = false;
    }

    if (!bBallAwayFromCarrier)
    {
        nlVector3 v3Direction;
        nlPolarToCartesian(v3Direction.f.x, v3Direction.f.y, aAngle, 2.0f + m_fActualSpeed);
        v3Direction.f.z = 0.5f;

        g_pBall->ShootRelease(v3Direction, SPINTYPE_NONE);
    }
}

/**
 * Offset/Address/Size: 0x8F5C | 0x80022298 | size: 0x230
 */
void cFielder::DoClearBall()
{
}

/**
 * Offset/Address/Size: 0x8CA8 | 0x80021FE4 | size: 0x2B4
 */
void cFielder::DoHandleActiveShotMeter()
{
}

/**
 * Offset/Address/Size: 0x8A18 | 0x80021D54 | size: 0x290
 */
void cFielder::DoLooseBallContactFromIdle(nlVector3&, float&, nlVector3&, float&, unsigned short, const LooseBallContactAnimInfo*)
{
}

/**
 * Offset/Address/Size: 0x87A8 | 0x80021AE4 | size: 0x270
 */
void cFielder::DoLooseBallContactFromRun(nlVector3&, float&, nlVector3&, float&, const LooseBallContactAnimInfo*, const nlVector3&)
{
}

/**
 * Offset/Address/Size: 0x84AC | 0x800217E8 | size: 0x2FC
 */
void cFielder::DoLooseBallContactFromRunVolley(nlVector3&, float&, nlVector3&, float&, const LooseBallContactAnimInfo*, const nlVector3&)
{
}

/**
 * Offset/Address/Size: 0x82B0 | 0x800215EC | size: 0x1FC
 */
void cFielder::DoPenaltyCardBooking(cFielder* pVictim, ePenaltyType ePenaltyType)
{
    float fMaxAmount;
    float fMinAmount;

    int ePenaltyTypeAdjusted = ePenaltyType;
    if (pVictim->m_tBallUnPossessionTimer.GetSeconds() < 0.5f)
    {
        if (ePenaltyTypeAdjusted == 1)
        {
            ePenaltyTypeAdjusted = 0;
        }
        else if (ePenaltyTypeAdjusted == 3)
        {
            ePenaltyTypeAdjusted = 2;
        }
    }

    // Update penalty card status
    switch (m_ePenaltyCardStatus)
    {
    case PENALTY_CARD_NONE:
        m_ePenaltyCardStatus = PENALTY_CARD_YELLOW_1;
        break;
    case PENALTY_CARD_YELLOW_1:
        m_ePenaltyCardStatus = PENALTY_CARD_YELLOW_2;
        break;
    case PENALTY_CARD_RED: // ??
        break;
    case PENALTY_CARD_YELLOW_2:
        m_ePenaltyCardStatus = PENALTY_CARD_RED;
        break;
    }
    PenaltyData* pData;
    if (ePenaltyTypeAdjusted == PEN_TYPE_HIT_NO_BALL)
    {
        Event* pEvent = g_pEventManager->CreateValidEvent(0x3D, 0x24);
        pData = new ((u8*)pEvent + 0x10) PenaltyData();
    }
    else
    {
        Event* pEvent = g_pEventManager->CreateValidEvent(0x3C, 0x24);
        pData = new ((u8*)pEvent + 0x10) PenaltyData();
    }

    fMinAmount = 0.0f;
    fMaxAmount = 0.0f;

    switch (ePenaltyTypeAdjusted)
    {
    case PEN_TYPE_HIT_WITH_BALL:
    {
        GameTweaks* pTweaks = g_pGame->m_pGameTweaks;
        fMinAmount = pTweaks->fPowerupHitWithBallMinAmount;
        fMaxAmount = pTweaks->fPowerupHitWithBallMaxAmount;
        break;
    }
    case PEN_TYPE_HIT_NO_BALL:
    {
        GameTweaks* pTweaks = g_pGame->m_pGameTweaks;
        fMinAmount = pTweaks->fPowerupHitNoBallMinAmount;
        fMaxAmount = pTweaks->fPowerupHitNoBallMaxAmount;
        break;
    }
    case PEN_TYPE_SLIDE_WITH_BALL:
    {
        GameTweaks* pTweaks = g_pGame->m_pGameTweaks;
        fMinAmount = pTweaks->fPowerupSlideWithBallMinAmount;
        fMaxAmount = pTweaks->fPowerupSlideWithBallMaxAmount;
        break;
    }
    case PEN_TYPE_SLIDE_NO_BALL:
    {
        GameTweaks* pTweaks = g_pGame->m_pGameTweaks;
        fMinAmount = pTweaks->fPowerupSlideNoBallMinAmount;
        fMaxAmount = pTweaks->fPowerupSlideNoBallMaxAmount;
        break;
    }
    }

    pData->fPenaltyWorth = InterpolateRangeClamped(fMinAmount, fMaxAmount, 0.0f, 1.0f, nlRandomf(1.0f, &nlDefaultSeed));
    pData->pFouler = this;
    pData->pFoulee = pVictim;
}

/**
 * Offset/Address/Size: 0x8184 | 0x800214C0 | size: 0x12C
 */
void cFielder::DoPositioningInterceptBall()
{
    int nInterceptResult;
    float fInterceptTimes[2];
    nlVector3* pPos = &m_v3Position;

    if (nlGetLengthSquared2D(g_pBall->m_v3Position.f.x - pPos->f.x, g_pBall->m_v3Position.f.y - pPos->f.y) <= 4.0f)
    {
        CalcInterceptXY(*pPos, m_pTweaks->fRunningSpeed, 0.f, g_pBall->m_v3Position, g_pBall->m_v3Velocity, nInterceptResult, fInterceptTimes);

        if (nInterceptResult != 0)
        {
            float fTime;

            if (nInterceptResult == 2)
            {
                fTime = (fInterceptTimes[0] < fInterceptTimes[1]) ? fInterceptTimes[0] : fInterceptTimes[1];
            }
            else
            {
                fTime = fInterceptTimes[0];
            }

            float fInterceptX = g_pBall->m_v3Position.f.x + fTime * g_pBall->m_v3Velocity.f.x;
            float fInterceptY = g_pBall->m_v3Position.f.y + fTime * g_pBall->m_v3Velocity.f.y;

            float dyToIntercept = fInterceptY - m_v3Position.f.y;
            float dxToIntercept = fInterceptX - m_v3Position.f.x;
            float angleRad = nlATan2f(dyToIntercept, dxToIntercept);

            float angle16 = 10430.378f * angleRad;
            u16 targetAngle = (u16)(s32)angle16;

            s16 angleDelta = (s16)(targetAngle - m_aDesiredFacingDirection);
            angleDelta = (angleDelta < 0) ? -angleDelta : angleDelta;

            if ((u16)angleDelta <= 0x3000)
            {
                m_aDesiredFacingDirection = targetAngle;
                s16 tmp = m_aDesiredFacingDirection;
                m_aDesiredMovementDirection = tmp;
            }
        }
    }
}

/**
 * Offset/Address/Size: 0x8024 | 0x80021360 | size: 0x160
 */
void cFielder::DoAwardPowerupStuff(eAwardPowerupType ePowerupType, float fParam)
{
    Event* pEvent = g_pEventManager->CreateValidEvent(0x3E, 0x20);
    PowerupData* pData = new ((u8*)pEvent + 0x10) PowerupData();

    float fMinAmount = 0.0f;
    float fMaxAmount = 0.0f;

    switch (ePowerupType)
    {
    case AWARD_POWERUP_POWER_SHOT:
    {
        GameTweaks* pTweaks = g_pGame->m_pGameTweaks;
        fMaxAmount = InterpolateRangeClamped(pTweaks->fPowerupPowerShotMinAmount, pTweaks->fPowerupPowerShotMaxAmount, 0.0f, 0.9f, fParam);
        fMinAmount = fMaxAmount;
        break;
    }
    case AWARD_POWERUP_INTERCEPT_PASS:
    {
        GameTweaks* pTweaks = g_pGame->m_pGameTweaks;
        fMinAmount = pTweaks->fPowerupInterceptPassMinAmount;
        fMaxAmount = pTweaks->fPowerupInterceptPassMaxAmount;
        break;
    }
    case AWARD_POWERUP_PERFECT_PASS:
    {
        GameTweaks* pTweaks = g_pGame->m_pGameTweaks;
        fMinAmount = pTweaks->fPowerupPerfectPassMinAmount;
        fMaxAmount = pTweaks->fPowerupPerfectPassMaxAmount;
        break;
    }
    case AWARD_POWERUP_CONTEXT_DEKE:
    {
        GameTweaks* pTweaks = g_pGame->m_pGameTweaks;
        fMinAmount = pTweaks->fPowerupContextDekeMinAmount;
        fMaxAmount = pTweaks->fPowerupContextDekeMaxAmount;
        break;
    }
    }

    pData->fAwardWorth = InterpolateRangeClamped(fMinAmount, fMaxAmount, 0.0f, 1.0f, nlRandomf(1.0f, &nlDefaultSeed));
    pData->pFielder = this;
}

/**
 * Offset/Address/Size: 0x7E78 | 0x800211B4 | size: 0x1AC
 */
void cFielder::DoCalcShootToScoreResult(float f1, float f2, float f3, float f4, float f5)
{
    eShootToScoreResult result = S2S_SAVED;
    float fAbsDiff = (float)fabs(f2 - f4);

    if (f1 == f3 && fAbsDiff < f5)
    {
        result = S2S_SUPER_SHOT;

        Event* pEvent = g_pEventManager->CreateValidEvent(0x43, 0x1C);
        ShotAtGoalData* pData = new ((u8*)pEvent + 0x10) ShotAtGoalData();
        pData->pShooter = this;

        if (g_e3_Build)
        {
            result = S2S_SCORE;
        }
    }
    else
    {
        g_pEventManager->CreateValidEvent(0x44, 0x14);

        GameInfoManager* pGameInfoManager = nlSingleton<GameInfoManager>::Instance();
        if (pGameInfoManager->IsPerfectStrikesOn())
        {
            result = S2S_SUPER_SHOT;

            Event* pEvent = g_pEventManager->CreateValidEvent(0x43, 0x1C);
            ShotAtGoalData* pData = new ((u8*)pEvent + 0x10) ShotAtGoalData();
            pData->pShooter = this;
        }
        else if (fAbsDiff < mActionShootToScoreVars.fCaptainYellowWidth)
        {
            if (fAbsDiff < f5 && f5 > 0.0f)
            {
                result = S2S_SCORE;
            }
            else
            {
                float fValue = (float)fabs(fAbsDiff - f5) / (mActionShootToScoreVars.fCaptainYellowWidth - f5);

                if (f1 == f3)
                {
                    m_pShotMeter->m_fSTSValue = 0.01f;
                }
                else
                {
                    m_pShotMeter->m_fSTSValue = fValue;
                }

                result = S2S_SAVED_YELLOW;
            }
        }
    }

    meS2SResult = result;
}

/**
 * Offset/Address/Size: 0x7C34 | 0x80020F70 | size: 0x244
 */
void cFielder::DoFindBestHitTarget()
{
}

/**
 * Offset/Address/Size: 0x73B8 | 0x800206F4 | size: 0x87C
 */
void cFielder::DoFindBestShotTarget(nlVector3&, float&, bool)
{
}

/**
 * Offset/Address/Size: 0x6E28 | 0x80020164 | size: 0x590
 */
void cFielder::DoRegularShooting()
{
}

/**
 * Offset/Address/Size: 0x6DE4 | 0x80020120 | size: 0x44
 */
void cFielder::DoResetShotMeter(float fTime)
{
    m_pShotMeter->Reset();
    m_pShotMeter->m_fTime = fTime;
}

/**
 * Offset/Address/Size: 0x6DD0 | 0x8002010C | size: 0x14
 */
bool cFielder::IsActionDone() const
{
    return (u8)(m_eActionState == ACTION_NEED_ACTION);
}

/**
 * Offset/Address/Size: 0x6D94 | 0x800200D0 | size: 0x3C
 */
void cFielder::SetAction(eFielderActionState actionState)
{
    CleanUpAction();
    m_eActionState = actionState;
}

/**
 * Offset/Address/Size: 0x6D58 | 0x80020094 | size: 0x3C
 */
void cFielder::GetFormationPosition(nlVector3& v3DestPosition, float fBallPosFormationWeight)
{
    if (fBallPosFormationWeight < 0.0f)
    {
        fBallPosFormationWeight = 1.0f;
    }

    m_pTeam->CalculateFormationPosition(v3DestPosition, this, m_DesireCommonVars.bInPosition, fBallPosFormationWeight);
}

/**
 * Offset/Address/Size: 0x6D4C | 0x80020088 | size: 0xC
 */
const LooseBallContactAnimInfo* GetOneTimerLeadGroundContactAnims()
{
    return gOneTimerLeadGroundContactAnims;
}

/**
 * Offset/Address/Size: 0x6C1C | 0x8001FF58 | size: 0x130
 */
void cFielder::GetOneTimerBallContactAnimInfo(unsigned short, const nlVector3&, const nlVector3&, bool, bool)
{
}

/**
 * Offset/Address/Size: 0x6AEC | 0x8001FE28 | size: 0x130
 * TODO: there are some regswaps in the section with min/max angle checks, need to fix them
 */
const LooseBallContactAnimInfo* cFielder::GetReceivePassBallContactAnimInfo(cBall* pBall, const nlVector3& rv3Pos, unsigned short aAngle, bool bLeadPass, bool bVolleyPass)
{
    const LooseBallContactAnimInfo* pBallContactAnimInfo;
    int nNumContactAnims;
    const LooseBallContactAnimInfo* pResult;
    int i;

    if (bLeadPass)
    {
        if (bVolleyPass)
        {
            nNumContactAnims = 3;
            pBallContactAnimInfo = LeadVolleyContactAnims;
        }
        else
        {
            nNumContactAnims = 4;
            pBallContactAnimInfo = LeadGroundContactAnims;
        }
    }
    else
    {
        if (bVolleyPass)
        {
            nNumContactAnims = 1;
            pBallContactAnimInfo = IdleVolleyContactAnims;
        }
        else
        {
            nNumContactAnims = 1;
            pBallContactAnimInfo = IdleGroundContactAnims;
        }
    }

    s32 angle32 = (s32)(10430.378f * nlATan2f(pBall->m_v3Position.f.y - rv3Pos.f.y, pBall->m_v3Position.f.x - rv3Pos.f.x));
    u16 normalizedAngle = (u16)angle32 - aAngle;

    pResult = nullptr;

    for (i = 0; i < nNumContactAnims; i++)
    {
        const u16 minAngle = pBallContactAnimInfo[i].aIncomingAngleMin;
        const u16 maxAngle = pBallContactAnimInfo[i].aIncomingAngleMax;

        if (minAngle < maxAngle)
        {
            if ((normalizedAngle >= minAngle) && (normalizedAngle <= maxAngle))
            {
                pResult = &pBallContactAnimInfo[i];
            }
        }
        else if ((normalizedAngle >= minAngle) || (normalizedAngle <= maxAngle))
        {
            pResult = &pBallContactAnimInfo[i];
        }
    }
    return pResult;
}
/**
 * Offset/Address/Size: 0x68F0 | 0x8001FC2C | size: 0x110
 */
bool cFielder::IsFallenDown(float fThreshold) const
{
    s32 nAnimID = m_eAnimID;
    u32 nIndex = (u32)(nAnimID - 0x5c);
    float fThresholdValue = 0.0f;

    switch (nIndex)
    {
    case 0:
        fThresholdValue = 67.0f;
        break;
    case 1:
        fThresholdValue = 64.0f;
        break;
    case 2:
        fThresholdValue = 34.0f;
        break;
    case 3:
        fThresholdValue = 32.0f;
        break;
    case 4:
        fThresholdValue = 42.0f;
        break;
    case 5:
        fThresholdValue = 46.0f;
        break;
    case 6:
        fThresholdValue = 43.0f;
        break;
    case 7:
        fThresholdValue = 30.0f;
        break;
    case 8:
        fThresholdValue = 20.0f;
        if (fThresholdValue < fThreshold)
        {
            return false;
        }
        break;
    case 9:
        fThresholdValue = 43.0f;
        break;
    case 10:
        fThresholdValue = 46.0f;
        break;
    case 11:
        fThresholdValue = 61.0f;
        break;
    case 12:
        fThresholdValue = 108.0f;
        break;
    case 13:
    {
        fThresholdValue = (float)(m_pCurrentAnimController->m_pSAnim->m_nNumKeys);
        break;
    }
    case 14:
        fThresholdValue = 29.0f;
        break;
    case 15:
    case 16:
    case 17:
    case 18:
    case 19:
    case 20:
    case 21:
    case 22:
    case 23:
    case 24:
    case 25:
    case 26:
        break;
    }

    return m_pCurrentAnimController->m_fTime < (fThresholdValue / m_pCurrentAnimController->m_pSAnim->m_nNumKeys);
}

/**
 * Offset/Address/Size: 0x6868 | 0x8001FBA4 | size: 0x88
 */
bool cFielder::IsHitting() const
{
    bool isHitting = false;
    // float fAnimTime;

    const cPN_SAnimController* pAnimController = m_pCurrentAnimController;
    const float fAnimTime = 30.0f * pAnimController->m_fTime * (pAnimController->m_pSAnim->m_nNumKeys / 30.0f);

    if ((m_tFrozenTimer.m_uPackedTime == 0) && m_eActionState == ACTION_HIT)
    {
        if (fAnimTime >= 4.0f && fAnimTime <= 14.0f)
        {
            isHitting = true;
        }
    }
    return isHitting;
}

/**
 * Offset/Address/Size: 0x682C | 0x8001FB68 | size: 0x3C
 */
bool cFielder::IsSlideTackling() const
{
    if ((m_tFrozenTimer.m_uPackedTime == 0) && (m_eActionState == ACTION_SLIDE_ATTACK) && ((mActionSlideAttackVars.eSlideAttackState == SLIDE_ATTACK_DOWN || mActionSlideAttackVars.eSlideAttackState == SLIDE_ATTACK_DECELERATE)))
    {
        return true;
    }
    return false;
}

/**
 * Offset/Address/Size: 0x681C | 0x8001FB58 | size: 0x10
 */
bool cFielder::IsStriker() const
{
    return m_eRole == ROLE_STRIKER;
}

/**
 * Offset/Address/Size: 0x6808 | 0x8001FB44 | size: 0x14
 */
bool cFielder::IsWinger() const
{
    return m_eRole == ROLE_WINGER;
}

/**
 * Offset/Address/Size: 0x67F4 | 0x8001FB30 | size: 0x14
 */
bool cFielder::IsMidField() const
{
    return m_eRole == ROLE_MIDFIELD;
}

/**
 * Offset/Address/Size: 0x67E0 | 0x8001FB1C | size: 0x14
 */
bool cFielder::IsDefense() const
{
    return m_eRole == ROLE_DEFENCE;
}

/**
 * Offset/Address/Size: 0x67CC | 0x8001FB08 | size: 0x14
 */
bool cFielder::IsFrozen() const
{
    return m_tFrozenTimer.m_uPackedTime != 0;
}

/**
 * Offset/Address/Size: 0x6700 | 0x8001FA3C | size: 0xCC
 */
void cFielder::SetFrozen(float seconds)
{
    static const nlVector3 v3Zero = { 0.0f, 0.0f, 0.0f };

    m_tFrozenTimer.SetSeconds(seconds);
    m_fDesiredSpeed = 0.0f;
    m_fActualSpeed = m_fDesiredSpeed;
    SetVelocity(v3Zero);

    if (seconds > 0.0f)
    {
        if (m_eFielderDesireState != FIELDERDESIRE_FINISH_ACTION)
        {
            g_pGame->AbortPendingThought(mThoughtHashCalcDesire);
            g_pGame->AbortPendingThought(mThoughtHashInitRunToNet);
            g_pGame->AbortPendingThought(mThoughtHashInitGetOpen);
            g_pGame->AbortPendingThought(mThoughtHashInitWindupPass);
            g_pGame->AbortPendingThought(mThoughtHashInitCutAndBreak);
            ClearQueuedDesire();
            EndDesire(false);
        }
    }
}

/**
 * Offset/Address/Size: 0x6310 | 0x8001F64C | size: 0x3F0
 */
void cFielder::DoFindBestSlideAttackTarget(nlVector3&, nlVector3&)
{
}

/**
 * Offset/Address/Size: 0x62DC | 0x8001F618 | size: 0x34
 */
bool cFielder::CanPickupBall(cBall* pBall)
{
    if (m_tFrozenTimer.m_uPackedTime != 0)
    {
        return false;
    }
    return cPlayer::CanPickupBall(pBall);
}

/**
 * Offset/Address/Size: 0x6284 | 0x8001F5C0 | size: 0x58
 */
bool cFielder::CanBeBlownUp()
{
    switch (m_eActionState)
    {
    case ACTION_ELECTROCUTION:
        // Check if anim ID is 0x75 or 0x76
        if (m_eAnimID == 0x76 || m_eAnimID == 0x75)
        {
            return true;
        }
        return false;

    case ACTION_STS_HIT_REACT:
    case ACTION_SQUISH_REACT:
        return false;

    default:
        return true;
    }
}

/**
 * Offset/Address/Size: 0x6230 | 0x8001F56C | size: 0x54
 */
void cFielder::CanBreakOutOfSlideTackle()
{
    if (m_eActionState == ACTION_SLIDE_ATTACK)
    {
        if (mActionSlideAttackVars.bAttackSucceeded != 0)
        {
            m_tSlideAttackTimer.SetSeconds(0.0f);
            mActionSlideAttackVars.eSlideAttackState = SLIDE_ATTACK_DECELERATE;
        }
    }
}

/**
 * Offset/Address/Size: 0x5F54 | 0x8001F290 | size: 0x2DC
 */
void cFielder::CalculateStrafeDirection(unsigned short, unsigned short)
{
}

/**
 * Offset/Address/Size: 0x5DF0 | 0x8001F12C | size: 0x164
 */
void cFielder::CalcPointOnPerimeter(nlVector3&, const nlVector3&, float)
{
}

/**
 * Offset/Address/Size: 0x5DA4 | 0x8001F0E0 | size: 0x4C
 */
void cFielder::ClearTimers()
{
    m_tPowerupEffectTime.SetSeconds(0.0f);
    mtBombImpactTime.SetSeconds(0.0f);
    m_tFrozenTimer.SetSeconds(0.0f);
}

/**
 * Offset/Address/Size: 0x5DA0 | 0x8001F0DC | size: 0x4
 */
void cFielder::ClearVolleyPass()
{
}

/**
 * Offset/Address/Size: 0x5B34 | 0x8001EE70 | size: 0x26C
 */
void cFielder::CleanActionShootToScore()
{
}

/**
 * Offset/Address/Size: 0x5A64 | 0x8001EDA0 | size: 0xD0
 */
void cFielder::SetAttemptOneTouchPass()
{
}

/**
 * Offset/Address/Size: 0x59C0 | 0x8001ECFC | size: 0xA4
 */
void cFielder::SetAttemptOneTouchShot()
{
    bool shouldAttempt = false;

    cGlobalPad* pad = GetGlobalPad();
    if (pad != NULL) {
        GameTweaks* tweaks = g_pGame->m_pGameTweaks;
        float pressure = GetGlobalPad()->GetPressure(0x15, true);
        if (pressure > tweaks->unk2B0) {
            shouldAttempt = true;
        }
    }

    m_DesireReceivePassSharedVars.iAttemptOneTouchShot = shouldAttempt ? 2 : 1;
    m_DesireReceivePassSharedVars.iAttemptOneTouchPass = 0;
    m_DesireReceivePassSharedVars.pOneTouchPassTarget = NULL;
}

/**
 * Offset/Address/Size: 0x595C | 0x8001EC98 | size: 0x64
 */
s16 cFielder::GetOneTouchShotDesire()
{
    float fZero = 0.f;
    float fResult = ReceivingPass(this);
    if (fResult != fZero)
    {
        return ((m_DesireReceivePassSharedVars.iAttemptOneTouchShot != 0) || (m_DesireReceivePassSharedVars.iAttemptOneTouchPass != 0));
    }

    return 0;
}

/**
 * Offset/Address/Size: 0x573C | 0x8001EA78 | size: 0x220
 */
void cFielder::SetStartAnimState(int)
{
}

/**
 * Offset/Address/Size: 0x5618 | 0x8001E954 | size: 0x124
 */
void cFielder::SetWindupWBAnimState()
{
    cNet* pOtherNet = m_pTeam->GetOtherNet();
    s16 facingDelta = GetFacingDeltaToPosition(pOtherNet->m_baseLocation);

    if (facingDelta < 0)
    {
        SetAnimState(0x57, true, 0.2f, false, false);
    }
    else
    {
        SetAnimState(0x56, true, 0.2f, false, false);
    }

    m_fDesiredSpeed = 0.0f;
    if (m_fActualSpeed > ((FielderTweaks*)m_pTweaks)->fRunningWBSpeed)
    {
        m_fActualSpeed = ((FielderTweaks*)m_pTweaks)->fRunningWBSpeed;
    }

    InitMovementRunningNoTurn(0.0f, ((FielderTweaks*)m_pTweaks)->fShotWindupDecel);

    Event* pEvent = g_pEventManager->CreateValidEvent(0x15, 0x1c);
    ShotAtGoalData* pData = new ((u8*)pEvent + 0x10) ShotAtGoalData();
    pData->pShooter = this;

    Play3DSFX(Audio::CHARSFX_SHOT_WINDUP, PHYSOBJ, 100.0f);
    Play3DSFX(Audio::CHARSFX_EFFORTS_HEAD_SHAKE, PHYSOBJ, 100.0f);

    EmitWindupAtBall(this, "ball_shot_windup");
}

/**
 * Offset/Address/Size: 0x5464 | 0x8001E7A0 | size: 0x1B4
 */
void cFielder::SetStartWBAnimState()
{
}

/**
 * Offset/Address/Size: 0x53E0 | 0x8001E71C | size: 0x84
 */
void cFielder::SetRunTurboAnimState(int animID, bool bForceMirrorSwap)
{
    if (animID == 0x1D)
    {
        EmitTurbo(this, "footy_burst");
    }

    SetAnimState(animID, false, 0.067f, false, bForceMirrorSwap);

    FielderTweaks* pTweaks = (FielderTweaks*)m_pTweaks;
    InitMovementRunningNoTurn(pTweaks->fRunningWBTurboAccel, pTweaks->fRunningWBTurboDecel);
}

/**
 * Offset/Address/Size: 0x5350 | 0x8001E68C | size: 0x90
 */
void cFielder::SetHardStopAnimState()
{
    if (m_pBall != nullptr)
    {
        SetAnimState(0x24, true, 0.2f, false, false);
    }
    else
    {
        SetAnimState(0x12, true, 0.2f, false, false);
    }
    InitMovementFromAnim(0, v3Zero, 1.0f, false);
    m_pCurrentAnimController->m_fPlaybackSpeedScale = 1.4f;
}

/**
 * Offset/Address/Size: 0x52C0 | 0x8001E5FC | size: 0x90
 */
void cFielder::SetHardStopRecoverAnimState()
{
    if (m_pBall != nullptr)
    {
        SetAnimState(0x26, false, 0.03f, false, false);
    }
    else
    {
        SetAnimState(0x14, false, 0.03f, false, false);
    }
    InitMovementFromAnim(0, v3Zero, 1.0f, false);
    m_pCurrentAnimController->m_fPlaybackSpeedScale = 1.4f;
}

/**
 * Offset/Address/Size: 0x5230 | 0x8001E56C | size: 0x90
 */
void cFielder::SetHardStopTurnAnimState()
{
    if (m_pBall != nullptr)
    {
        SetAnimState(0x25, false, 0.03f, false, false);
    }
    else
    {
        SetAnimState(0x13, false, 0.03f, false, false);
    }
    InitMovementFromAnim(0, v3Zero, 1.0f, false);
    m_pCurrentAnimController->m_fPlaybackSpeedScale = 1.4f;
}

/**
 * Offset/Address/Size: 0x51CC | 0x8001E508 | size: 0x64
 */
void cFielder::SetRunBackwardsAnimState()
{
    SetAnimState(0x27, true, 0.067f, true, false);

    FielderTweaks* pTweaks = (FielderTweaks*)m_pTweaks;
    InitMovementStrafing(pTweaks->fRunningStrafeDirectionSeekSpeed, pTweaks->fRunningStrafeDirectionSeekFalloff, pTweaks->fRunningStrafeAccel, pTweaks->fRunningStrafeDecel);

    m_aActualMovementDirection = m_aDesiredMovementDirection;
}

/**
 * Offset/Address/Size: 0x515C | 0x8001E498 | size: 0x70
 */
void cFielder::SetRunToBackRunningAnimState()
{
    SetAnimState(0x2d, true, 0.067f, true, false);
    InitMovementFromAnim(0, v3Zero, 1.0f, false);
    m_aActualMovementDirection = m_aDesiredMovementDirection;
    m_pCurrentAnimController->m_fPlaybackSpeedScale = 1.25f;
}

/**
 * Offset/Address/Size: 0x50EC | 0x8001E428 | size: 0x70
 */
void cFielder::SetBackRunningToRunAnimState()
{
    SetAnimState(0x2e, true, 0.067f, true, false);
    InitMovementFromAnim(0, v3Zero, 1.0f, false);
    m_aActualMovementDirection = m_aDesiredMovementDirection;
    m_pCurrentAnimController->m_fPlaybackSpeedScale = 1.25f;
}

/**
 * Offset/Address/Size: 0x507C | 0x8001E3B8 | size: 0x70
 */
void cFielder::SetBackRunningStopAnimState()
{
    SetAnimState(0x2a, true, 0.067f, true, false);
    InitMovementFromAnim(0, v3Zero, 1.0f, false);
    m_aActualMovementDirection = m_aDesiredMovementDirection;
    m_pCurrentAnimController->m_fPlaybackSpeedScale = 1.25f;
}

/**
 * Offset/Address/Size: 0x500C | 0x8001E348 | size: 0x70
 */
void cFielder::SetBackRunningStopStartAnimState()
{
    SetAnimState(0x2b, true, 0.067f, true, false);
    InitMovementFromAnim(0, v3Zero, 1.0f, false);
    m_aActualMovementDirection = m_aDesiredMovementDirection;
    m_pCurrentAnimController->m_fPlaybackSpeedScale = 1.25f;
}

/**
 * Offset/Address/Size: 0x4FA8 | 0x8001E2E4 | size: 0x64
 */
void cFielder::SetBackRunningStopRecoverAnimState()
{
    SetAnimState(0x2c, true, 0.067f, true, false);
    InitMovementFromAnim(0, v3Zero, 1.0f, false);
    m_aActualMovementDirection = m_aDesiredMovementDirection;
}

/**
 * Offset/Address/Size: 0x4F44 | 0x8001E280 | size: 0x64
 */
void cFielder::SetStopAnimState()
{
    SetAnimState(0xb, true, 0.2f, false, false);
    InitMovementFromAnim(0, v3Zero, 1.0f, false);
    m_fDesiredSpeed = 0.0f;
}

/**
 * Offset/Address/Size: 0x4EE8 | 0x8001E224 | size: 0x5C
 */
void cFielder::SetStopWBAnimState()
{
    SetAnimState(0x23, true, 0.2f, false, false);
    InitMovementFromAnim(0, v3Zero, 1.0f, false);
}

/**
 * Offset/Address/Size: 0x4E84 | 0x8001E1C0 | size: 0x64
 */
void cFielder::SetStrafeLeftAnimState()
{
    SetAnimState(0x28, true, 0.067f, true, false);

    FielderTweaks* pTweaks = (FielderTweaks*)m_pTweaks;
    InitMovementStrafing(pTweaks->fRunningStrafeDirectionSeekSpeed, pTweaks->fRunningStrafeDirectionSeekFalloff, pTweaks->fRunningStrafeAccel, pTweaks->fRunningStrafeDecel);

    m_aActualMovementDirection = m_aDesiredMovementDirection;
}

/**
 * Offset/Address/Size: 0x4E20 | 0x8001E15C | size: 0x64
 */
void cFielder::SetStrafeRightAnimState()
{
    SetAnimState(0x29, true, 0.067f, true, false);

    FielderTweaks* pTweaks = (FielderTweaks*)m_pTweaks;
    InitMovementStrafing(pTweaks->fRunningStrafeDirectionSeekSpeed, pTweaks->fRunningStrafeDirectionSeekFalloff, pTweaks->fRunningStrafeAccel, pTweaks->fRunningStrafeDecel);

    m_aActualMovementDirection = m_aDesiredMovementDirection;
}

/**
 * Offset/Address/Size: 0x4DB4 | 0x8001E0F0 | size: 0x6C
 */
void cFielder::SetIdleStrafeAnimState()
{
    SetAnimState(0, true, 0.2f, false, false);

    FielderTweaks* pTweaks = (FielderTweaks*)m_pTweaks;
    InitMovementRunning(pTweaks->fRunningDirectionSeekSpeed, pTweaks->fRunningDirectionSeekFalloff, pTweaks->fRunningAccel, pTweaks->fRunningDecel);

    m_fActualSpeed = 0.0f;
    m_aActualMovementDirection = m_aDesiredMovementDirection;
}

/**
 * Offset/Address/Size: 0x4D58 | 0x8001E094 | size: 0x5C
 */
void cFielder::SetIdleAnimState()
{
    SetAnimState(0, true, 0.2f, false, false);

    FielderTweaks* pTweaks = (FielderTweaks*)m_pTweaks;
    InitMovementRunning(pTweaks->fRunningDirectionSeekSpeed, pTweaks->fRunningDirectionSeekFalloff, pTweaks->fRunningAccel, pTweaks->fRunningDecel);
}

/**
 * Offset/Address/Size: 0x4CFC | 0x8001E038 | size: 0x5C
 */
void cFielder::SetIdleWBAnimState()
{
    SetAnimState(0x15, true, 0.2f, false, false);

    FielderTweaks* pTweaks = (FielderTweaks*)m_pTweaks;
    InitMovementRunning(pTweaks->fRunningWBDirectionSeekSpeed, pTweaks->fRunningWBDirectionSeekFalloff, pTweaks->fRunningWBAccel, pTweaks->fRunningWBDecel);
}

/**
 * Offset/Address/Size: 0x4CA8 | 0x8001DFE4 | size: 0x54
 */
void cFielder::RunningSABcallback(unsigned int nParam1, cPN_SingleAxisBlender* pSAB)
{
    cFielder* pThis = (cFielder*)nParam1;

    if (pThis->m_eAnimID == ACTION_LOOSE_BALL_SHOT || pThis->m_eAnimID == 0x1A || pThis->m_eAnimID == ACTION_RUNNING_WB_TURBO)
    {
        float fWeight = (0.5f * pThis->m_fLeanAmount) + 0.5f;
        if (pThis->m_pCurrentAnimController->m_bMirror != 0)
        {
            fWeight = 1.0f - fWeight;
        }

        pSAB->m_fDesiredWeight = fWeight;
        return;
    }
    pSAB->m_fDesiredWeight = pSAB->m_fSmoothedWeight;
}

/**
 * Offset/Address/Size: 0x4B70 | 0x8001DEAC | size: 0x138
 */
void cFielder::SetRunningAnimState(float)
{
}

/**
 * Offset/Address/Size: 0x4A30 | 0x8001DD6C | size: 0x140
 */
void cFielder::SetRunningTurboAnimState()
{
}

/**
 * Offset/Address/Size: 0x48F8 | 0x8001DC34 | size: 0x138
 * TODO: regswap on r28/r29
 */
void cFielder::SetRunningWBAnimState(float)
{
    int animIDsArray[3] = {
        0x0000001B,
        0x0000001A,
        0x0000001C,
    };

    int i;
    cPN_SAnimController* pChild1;
    cPN_SingleAxisBlender* pSingleAxisBlender;
    cPN_SAnimController* pChild;

    pSingleAxisBlender = CreateSingleAxisBlender(animIDsArray, 3, 1, RunningSABcallback, 0.0f, nullptr);

    pChild1 = (cPN_SAnimController*)pSingleAxisBlender->GetChild(1);
    pChild1->m_fSynchronizedWeight = 0.0f;

    for (i = 0; i < 3; ++i)
    {
        if (i != 1)
        {
            pChild = (cPN_SAnimController*)pSingleAxisBlender->GetChild(i);
            pChild->m_bIsSynchronized = true;
            pChild1->m_pSynchronizedController = pChild;
            pChild1 = pChild;
        }
    }

    *m_pAILayer = new (AllocateBlender()) cPN_Blender(*m_pAILayer, pSingleAxisBlender, 0.0f);

    FielderTweaks* pTweaks = ((FielderTweaks*)m_pTweaks);
    InitMovementRunning(pTweaks->fRunningWBDirectionSeekSpeed, pTweaks->fRunningWBDirectionSeekFalloff, pTweaks->fRunningWBAccel, pTweaks->fRunningWBDecel);
}

/**
 * Offset/Address/Size: 0x48A8 | 0x8001DBE4 | size: 0x50
 */
bool cFielder::ShouldIClearBall()
{
    cNet* pOtherNet = m_pTeam->GetOtherNet();
    float fPositionX = m_v3Position.f.x;
    float fSideSign = pOtherNet->m_sideSign;
    float fResult = fPositionX * fSideSign;

    return fResult <= 0.0f;
}

/**
 * Offset/Address/Size: 0x4894 | 0x8001DBD0 | size: 0x14
 */
bool cFielder::ShouldILeadPass()
{
    return m_eActionState == ACTION_RUNNING;
}

/**
 * Offset/Address/Size: 0x4564 | 0x8001D8A0 | size: 0x330
 */
void cFielder::CanISlideAttack(const nlVector3&, const nlVector3&, float*)
{
}

/**
 * Offset/Address/Size: 0x4518 | 0x8001D854 | size: 0x4C
 */
void cFielder::SetPosition(const nlVector3& v3Position)
{
    m_v3DesiredPosition = v3Position;
    cCharacter::SetPosition(v3Position);
    m_fDistanceToDesiredPosition = -9999.9f;
}

/**
 * Offset/Address/Size: 0x3F70 | 0x8001D2AC | size: 0x5A8
 */
void cFielder::SetDesiredSpeedAndDirectionToPosition(float, const nlVector3&, eTurboRequest, float, float)
{
}

/**
 * Offset/Address/Size: 0x3EE8 | 0x8001D224 | size: 0x88
 */
void cFielder::SetDesiredSpeed(float fMinSpeed, float fMaxSpeed)
{
    if (m_pController != nullptr)
    {
        float fMagnitude = m_pController->GetMovementStickMagnitude();
        if (fMagnitude > 0.0f)
        {
            m_fDesiredSpeed = (fMaxSpeed - fMinSpeed) * m_pController->GetMovementStickMagnitude() + fMinSpeed;
        }
        else
        {
            m_fDesiredSpeed = 0.0f;
        }
    }
}

/**
 * Offset/Address/Size: 0x3E8C | 0x8001D1C8 | size: 0x5C
 */
float cFielder::GetSpeedPowerupAdjusted(float fSpeed)
{
    float fMultiplier = 1.0f;

    if (fSpeed >= 0.0f)
    {
        switch (m_ePowerup)
        {
        case POWER_UP_MUSHROOM:
            fMultiplier = fMultiplier * g_pGame->m_pGameTweaks->fMushroomSpeed;
            break;
        case POWER_UP_STAR:
            fMultiplier = fMultiplier * g_pGame->m_pGameTweaks->fStarSpeed;
            break;
        }
    }

    return fMultiplier * fSpeed;
}

/**
 * Offset/Address/Size: 0x3E0C | 0x8001D148 | size: 0x80
 */
float cFielder::GetSlideAttackSpeed()
{
    float fSpeed = ((FielderTweaks*)m_pTweaks)->fRunningWBTurboSpeedLevel2;
    float fResult = 1.0f;

    if (fSpeed >= 0.0f)
    {
        switch (m_ePowerup)
        {
        case POWER_UP_MUSHROOM:
            fResult *= g_pGame->m_pGameTweaks->fMushroomSpeed;
            break;
        case POWER_UP_STAR:
            fResult *= g_pGame->m_pGameTweaks->fStarSpeed;
            break;
        }
    }

    fResult *= fSpeed;

    if (m_ePowerup >= 9)
    {
        return fResult;
    }

    if (m_ePowerup < POWER_UP_MUSHROOM)
    {
        return fResult;
    }

    float fMultiplier = 1.4f;
    return fResult * fMultiplier;
}

/**
 * Offset/Address/Size: 0x3D5C | 0x8001D098 | size: 0xB0
 */
void cFielder::SetDesire(eFielderDesireState, float)
{
}

/**
 * Offset/Address/Size: 0x3B44 | 0x8001CE80 | size: 0x218
 */
void cFielder::ShouldIStrafe()
{
}

/**
 * Offset/Address/Size: 0x39F8 | 0x8001CD34 | size: 0x14C
 */
void cFielder::ShouldITurboWithoutBall()
{
}

/**
 * Offset/Address/Size: 0x3890 | 0x8001CBCC | size: 0x168
 */
void cFielder::ShouldIWave()
{
}

/**
 * Offset/Address/Size: 0x3668 | 0x8001C9A4 | size: 0x228
 */
void cFielder::TestCollisionForInvicibility(cFielder*)
{
}

/**
 * Offset/Address/Size: 0x355C | 0x8001C898 | size: 0x10C
 */
void cFielder::TestButtonsToQueueActions(float)
{
}

/**
 * Offset/Address/Size: 0x346C | 0x8001C7A8 | size: 0xF0
 */
bool cFielder::TestQueuedActions()
{
    bool bResult = false;
    int eAction = m_eLastPadAction;

    if (eAction == PAD_SHOOT)
    {
        InitActionRunningWB(false);
        bResult = true;
    }
    else if (eAction == PAD_PASS)
    {
        bool bAllowLeadPass = false;
        if (GetGlobalPad() != nullptr)
        {
            GameTweaks* pTweaks = g_pGame->m_pGameTweaks;
            if (GetGlobalPad()->GetPressure(PAD_AIM, true) > pTweaks->unk2B0)
            {
                bAllowLeadPass = true;
            }
        }

        InitActionPass(DoFindBestPassTarget(bAllowLeadPass, false), bAllowLeadPass, false);
        bResult = true;
    }
    else if (eAction >= PAD_DEKE && eAction <= PAD_DEKE_RIGHT)
    {
        InitActionDeke(m_eLastPadAction);
        bResult = true;
    }

    return bResult;
}

/**
 * Offset/Address/Size: 0x2BB0 | 0x8001BEEC | size: 0x8BC
 */
void cFielder::TestButtonsRunning()
{
}

/**
 * Offset/Address/Size: 0x2A6C | 0x8001BDA8 | size: 0x144
 */
void cFielder::TestButtonsRunningWB(float)
{
}

/**
 * Offset/Address/Size: 0x2A34 | 0x8001BD70 | size: 0x38
 */
void cFielder::PreUpdate(float fTime)
{
    cPlayer::PreUpdate(fTime);
    m_bHasBeenUpdated = false;
    mbWasHitByPowerupThisFrame = false;
}

/**
 * Offset/Address/Size: 0x27EC | 0x8001BB28 | size: 0x248
 */
void cFielder::PostPhysicsUpdate()
{
}

/**
 * Offset/Address/Size: 0x234C | 0x8001B688 | size: 0x4A0
 */
void cFielder::Update(float)
{
}

/**
 * Offset/Address/Size: 0x21D8 | 0x8001B514 | size: 0x174
 */
void cFielder::ThrowPowerup()
{
}

/**
 * Offset/Address/Size: 0x1D18 | 0x8001B054 | size: 0x4C0
 */
void cFielder::SetPowerup(ePowerUpType, int, cFielder*)
{
}

/**
 * Offset/Address/Size: 0x1BE4 | 0x8001AF20 | size: 0x134
 */
void cFielder::UseTeamPowerup(cFielder*)
{
}

/**
 * Offset/Address/Size: 0x1AB4 | 0x8001ADF0 | size: 0x130
 */
void cFielder::UpdateActionState(float)
{
}

/**
 * Offset/Address/Size: 0x17CC | 0x8001AB08 | size: 0x2E8
 */
void cFielder::UpdateHeadTracking(float)
{
}

/**
 * Offset/Address/Size: 0x13C4 | 0x8001A700 | size: 0x408
 */
void cFielder::UpdateController(float)
{
}

/**
 * Offset/Address/Size: 0x13A0 | 0x8001A6DC | size: 0x24
 */
void cFielder::UpdatePlay(float fTime)
{
    m_pCurrentPlay->Update(fTime);
}

/**
 * Offset/Address/Size: 0x1338 | 0x8001A674 | size: 0x68
 */
float cFielder::GetDistanceToDesiredPos()
{
    if (m_fDistanceToDesiredPosition == -9999.9f)
    {
        float dx = m_v3Position.f.x - m_v3DesiredPosition.f.x;
        float dy = m_v3Position.f.y - m_v3DesiredPosition.f.y;
        float distanceSquared = dx * dx + dy * dy;
        m_fDistanceToDesiredPosition = nlSqrt(distanceSquared, true);
    }
    return m_fDistanceToDesiredPosition;
}

/**
 * Offset/Address/Size: 0x1224 | 0x8001A560 | size: 0x114
 */
void cFielder::S2SShootWasPressed()
{
}

/**
 * Offset/Address/Size: 0x11AC | 0x8001A4E8 | size: 0x78
 * TODO: 100% match, but I believe the goto in the class-inline is probably movable to another class-inline method.
 */
void cFielder::StartRunning()
{
    if (!IsRunningState())
    {
        if (m_pBall != 0)
        {
            InitActionRunningWB(false);
            return;
        }
        InitActionRunning();
    }
}

/**
 * Offset/Address/Size: 0xC14 | 0x80019F50 | size: 0x598
 */
void cFielder::DoAILooseBallActionSelection()
{
}

/**
 * Offset/Address/Size: 0x6BC | 0x800199F8 | size: 0x558
 */
void cFielder::DoAIReceivePassActionSelection()
{
}

/**
 * Offset/Address/Size: 0x3C | 0x80019378 | size: 0x680
 */
void cFielder::DoAIWindupActionSelection()
{
}

/**
 * Offset/Address/Size: 0x0 | 0x8001933C | size: 0x3C
 */
void cFielder::DoSpeedBoost()
{
    eShotMeterState state = m_pShotMeter->m_eShotMeterState;
    bool bReturn = (state == SHOT_METER_ACTIVE || state == SHOT_METER_STS_ACTIVE || state == SHOT_METER_STS_TRANSISTION);

    if (bReturn)
        return;

    m_fActualSpeed = 0.0f;
}
