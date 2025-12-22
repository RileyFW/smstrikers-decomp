#include "Game/Goalie.h"
#include "Game/AI/AiUtil.h"
#include "Game/AI/Fielder.h"
#include "Game/Net.h"
#include "Game/Team.h"
#include "Game/Ball.h"
#include "Game/GameTweaks.h"
#include "Game/SAnim/pnSingleAxisBlender.h"
#include "Game/Audio/WorldAudio.h"
#include "Game/CharacterTriggers.h"
#include "NL/nlMath.h"

cTeam* g_pCurrentlyUpdatingTeam;
extern cBall* g_pBall;
f32 mfGoalieStepDist;
f32 mfGoalieStrafeDist;
f32 mfGoalieRunDist;
f32 mfGoalieUrgentDist;
f32 gfRepositionThreshold;

static const nlVector3 v3Zero = { 0.0f, 0.0f, 0.0f };

inline float CalculateDistanceSquared(const nlVector3& pos1, const nlVector3& pos2)
{
    nlVector3 delta;
    nlVec3Sub(delta, pos1, pos2);
    return nlGetLengthSquared3D(delta.f.x, delta.f.y, delta.f.z);
}

// /**
//  * Offset/Address/Size: 0x4700 | 0x80052C3C | size: 0x10
//  */
// void 0x8028D294..0x8028D298 | size: 0x4
// {
// }

/**
 * Offset/Address/Size: 0x4518 | 0x80052A54 | size: 0x1E8
 */
void Goalie::ActionLooseBallCatch(float deltaTime)
{
    mfTargetTime -= deltaTime;

    if (m_eAnimID == GOALIEACTION_STS)
    {
        if (mfTargetTime <= mBlendInfo.mfMilestoneTime[2] + 0.01f)
        {
            float clampedValue = mBlendInfo.mfMilestoneTime[2] - mfTargetTime;
            if (clampedValue >= mBlendInfo.mfStartTime)
            {
                clampedValue = mBlendInfo.mfStartTime;
            }
            PlayBlendedAnims(clampedValue, -1);
        }
    }
    else
    {

        if (mpSaveData == NULL || m_pCurrentAnimController->m_fTime > 0.95f)
        {
            if (m_pBall == NULL)
            {
                InitActionMove(false);
                return;
            }
            InitActionMoveWB();
            return;
        }

        if (g_pBall->m_pOwner != NULL)
        {
            return;
        }

        if (!m_pCurrentAnimController->TestTrigger(mpSaveData->mfMilestonePercent[2]))
        {
            return;
        }

        const nlVector3& leftHandPos = GetJointPosition(m_nLeftHandJointIndex);
        const nlVector3& rightHandPos = GetJointPosition(m_nRightHandJointIndex);

        float distSqLeft = g_pBall->m_v3Position.CalculateDistanceSquared(leftHandPos);
        if (distSqLeft < 1.0f || g_pBall->m_v3Position.CalculateDistanceSquared(rightHandPos) < 1.0f)
        // if (_CalculateDistanceSquared(leftHandPos, g_pBall->m_v3Position) < 1.0f
        //     || _CalculateDistanceSquared(rightHandPos, g_pBall->m_v3Position) < 1.0f)
        {
            Audio::SoundAttributes soundAttrs;
            soundAttrs.Init();
            soundAttrs.SetSoundType(0xC0, true);
            soundAttrs.UseStationaryPosVector(m_v3Position);
            soundAttrs.mf_Volume = 1.0f; // @2821 - needs verification
            Audio::gStadGenSFX.Play(soundAttrs);

            PickupBall(g_pBall);
            mbPickedUp = true;
            g_pBall->ClearShotInProgress();
            EmitGoalieCatch(this, "goalie_catch", false); // @1580 is likely a string constant
        }
    }
}

/**
 * Offset/Address/Size: 0x3E6C | 0x800523A8 | size: 0x6AC
 */
void Goalie::ActionLooseBallDesperate(float)
{
}

/**
 * Offset/Address/Size: 0x36CC | 0x80051C08 | size: 0x7A0
 */
void Goalie::ActionLooseBallPickup(float)
{
}

/**
 * Offset/Address/Size: 0x3630 | 0x80051B6C | size: 0x9C
 */
void Goalie::ActionLooseBallPursueRolling(float deltaTime)
{
    DoNavigation(deltaTime, 0.2f + mfGoalieStepDist, NAVI_FACE_BALL);

    if ((mnOffplayPending)
        || (!IsLooseBallClose(SkillTweaks::GetSkillTweaks(g_pCurrentlyUpdatingTeam->m_nSide)->fLooseBallChaseDistance))
        || ((g_pBall->m_pOwner != NULL) && (g_pBall->m_pOwner != this)))
    {
        InitActionMove(true);
        return;
    }

    InitActionLooseBallSetup();
}

/**
 * Offset/Address/Size: 0x35A8 | 0x80051AE4 | size: 0x88
 */
void Goalie::ActionLooseBallSetup(float)
{
    if ((mnOffplayPending)
        || (!IsLooseBallClose(SkillTweaks::GetSkillTweaks(g_pCurrentlyUpdatingTeam->m_nSide)->fLooseBallChaseDistance))
        || ((g_pBall->m_pOwner != NULL) && (g_pBall->m_pOwner != this)))
    {
        InitActionMove(true);
        return;
    }
    InitActionLooseBallSetup();
}

/**
 * Offset/Address/Size: 0x358C | 0x80051AC8 | size: 0x1C
 */
void Goalie::MoveDirectionCB(unsigned int nParam, cPN_SingleAxisBlender* blender)
{
    Goalie* pGoalie = (Goalie*)nParam;
    float result = 0.0f;
    if (pGoalie->mv3LocalNavTarget.f.y < 0.0f)
    {
        result = 1.0f;
    }
    blender->m_fDesiredWeight = result;
}

/**
 * Offset/Address/Size: 0x3544 | 0x80051A80 | size: 0x48
 */
void Goalie::MoveWeightCB(unsigned int nParam, cPN_SingleAxisBlender* blender)
{
    Goalie* pGoalie = (Goalie*)nParam;
    s16 angle = pGoalie->maLocalAngle;
    if (angle < 0)
    {
        angle = -angle;
    }

    blender->m_fDesiredWeight = (int)angle / 32768.0f;
}

/**
 * Offset/Address/Size: 0x3538 | 0x80051A74 | size: 0xC
 */
void Goalie::StrafeSynchronizedSpeedCallback(unsigned int nParam, cPN_SAnimController* controller)
{
    Goalie* pGoalie = (Goalie*)nParam;
    controller->m_fPlaybackSpeedScale = pGoalie->mfSpeedScale;
}

/**
 * Offset/Address/Size: 0x30E0 | 0x8005161C | size: 0x458
 */
void Goalie::ActionMove(float)
{
}

inline s16 ClampMin(const s16 diff, const s16 min)
{
    if (diff >= min)
    {
        return diff;
    }
    return min;
}

inline s16 ClampMax(const s16 diff, const s16 max)
{
    if (diff <= max)
    {
        return diff;
    }
    return max;
}

/**
 * Offset/Address/Size: 0x3070 | 0x800515AC | size: 0x70
 */
void Goalie::RunWeightCB(unsigned int nParam, cPN_SingleAxisBlender* blender)
{
    const Goalie* pGoalie = (Goalie*)nParam;

    s16 diff = (s16)(pGoalie->m_aDesiredFacingDirection - pGoalie->m_aActualFacingDirection);

    s16 minClampedDiff = -0x31C4;
    if (diff >= -0x31C4)
    {
        minClampedDiff = diff;
    }

    s16 clampedDiff = 0x31C4;
    if (minClampedDiff <= 0x31C4)
    {
        clampedDiff = minClampedDiff;
    }

    // s16 clampedDiff = ClampMax(ClampMin(diff, -0x31C4), 0x31C4);

    blender->m_fDesiredWeight = (float)(clampedDiff + 0x31C4) / 25480.0f;
}

/**
 * Offset/Address/Size: 0x27FC | 0x80050D38 | size: 0x874
 */
void Goalie::ActionMoveWB(float)
{
}

/**
 * Offset/Address/Size: 0x2758 | 0x80050C94 | size: 0xA4
 */
void Goalie::ActionSaveSetup(float deltaTime)
{
    float deflectResult = CheckForDelflectAwayFromNet();

    if (deflectResult < 0.0f)
    {
        return;
    }

    if (deflectResult > 0.0f)
    {
        InitActionSaveSetup(false);
        return;
    }

    if (mnOffplayPending != 0)
    {
        InitActionMove(true);
        return;
    }

    mfWaitTime -= deltaTime;
    if (mfWaitTime <= 0.01f)
    {
        InitActionSave();
    }
}

/**
 * Offset/Address/Size: 0x25D8 | 0x80050B14 | size: 0x180
 */
void Goalie::ActionSaveReposition(float deltaTime)
{
    if (mnOffplayPending != 0)
    {
        InitActionMove(true);
        return;
    }

    mfWaitTime -= deltaTime;

    float distSq = nlGetLengthSquared2D(m_v3Position.f.x - mv3NavTarget.f.x, m_v3Position.f.y - mv3NavTarget.f.y);

    bool shouldReposition = false;
    if ((distSq < gfRepositionThreshold * gfRepositionThreshold) || (distSq > mfTargetDist && distSq < 1.6899998f))
    {
        shouldReposition = true;
    }

    mfTargetDist = distSq;

    float deflectResult = CheckForDelflectAwayFromNet();
    if (deflectResult < 0.0f)
    {
        return;
    }

    if (mfWaitTime <= 0.02f || deflectResult > 0.0f || shouldReposition)
    {
        InitActionSaveSetup(false);
        return;
    }

    if (mfWaitTime < 0.05f)
    {
        PlayNewAnim(10);
        InitMovementFromAnimSeek(m_pTweaks->fRunningDirectionSeekSpeed, m_pTweaks->fRunningDirectionSeekFalloff);
        return;
    }

    float ballDx = g_pBall->m_v3Position.f.x - m_v3Position.f.x;
    float ballDy = g_pBall->m_v3Position.f.y - m_v3Position.f.y;
    float angle = nlATan2f(ballDy, ballDx);
    m_aDesiredFacingDirection = (u16)(s32)(10430.378f * angle); // @1734 constant

    DoNavigation(deltaTime, gfRepositionThreshold, NAVI_FACE_DESIRED);
}

/**
 * Offset/Address/Size: 0x20BC | 0x800505F8 | size: 0x51C
 */
void Goalie::ActionSave(float)
{
}

/**
 * Offset/Address/Size: 0x1C30 | 0x8005016C | size: 0x48C
 */
void Goalie::ActionSTS(float)
{
}

/**
 * Offset/Address/Size: 0x1BD8 | 0x80050114 | size: 0x58
 */
void Goalie::ActionSTSSetup(float deltaTime)
{
    if (mnOffplayPending != 0)
    {
        InitActionMove(true);
        return;
    }

    mfWaitTime -= deltaTime;
    if (mfWaitTime <= 0.01f)
    {
        InitActionSTS();
    }
}

/**
 * Offset/Address/Size: 0x1B18 | 0x80050054 | size: 0xC0
 */
void Goalie::ActionSTSRecover(float deltaTime)
{
    if (CheckForSTSAttack())
    {
        return;
    }

    mfWaitTime -= deltaTime;
    if (mfWaitTime <= 0.0f)
    {
        if (m_eAnimID != 0x70)
        {
            PlayNewAnim(0x70);
            InitMovementFromAnim(0, v3Zero, 1.0f, false);
        }
        else
        {
            if (m_pCurrentAnimController->m_fTime > 0.95f)
            {
                InitActionMove(true);
            }
        }
    }
}

/**
 * Offset/Address/Size: 0x19A0 | 0x8004FEDC | size: 0x178
 * TODO: regswaps still around nlATan2f....
 */
void Goalie::ActionChipShotStumble(float deltaTime)
{
    bool bShouldRecover = false;
    if (m_pCurrentAnimController->m_ePlayMode == PM_HOLD && m_pCurrentAnimController->m_fTime == 1.0f)
    {
        bShouldRecover = true;
    }

    if (bShouldRecover)
    {
        if (m_eAnimID == 0x70)
        {
            InitActionMove(true);
            return;
        }
        InitActionDiveRecover();
        return;
    }

    if (m_pCurrentAnimController->m_fTime < mpSaveData->mfMilestonePercent[2])
    {
        float deflectResult = CheckForDelflectAwayFromNet();
        if (deflectResult < 0.0f)
        {
            return;
        }

        if (deflectResult > 0.0f)
        {
            m_pPhysicsCharacter->m_CanCollidedWithGoalLine = true;
            InitActionSaveSetup(false);
            return;
        }
    }

    float x = mv3NavTarget.f.x;

    if ((float)fabs(x) > (0.5f + (float)fabs(m_v3Position.f.x)) && m_pCurrentAnimController->m_fTime < 0.5f)
    {
        m_aDesiredFacingDirection = (u16)(s32)(10430.378f * nlATan2f(m_v3Position.f.y - mv3NavTarget.f.y, m_v3Position.f.x - x));

        GoalieTweaks* pTweaks = static_cast<GoalieTweaks*>(m_pTweaks);
        u16 newFacing = SeekDirection(
            m_aActualFacingDirection,
            m_aDesiredFacingDirection,
            pTweaks->fThrowingDirectionSeekSpeed,
            pTweaks->fThrowingDirectionSeekFalloff,
            deltaTime);
        SetFacingDirection(newFacing);
    }
}

/**
 * Offset/Address/Size: 0x1904 | 0x8004FE40 | size: 0x9C
 */
void Goalie::ActionDiveRecover(float)
{
    if (m_pBall == nullptr)
    {
        GoalieTweaks* pTweaks = static_cast<GoalieTweaks*>(m_pTweaks);
        if (mFatigue.mfEnergyLevel < pTweaks->fGetupEnergyHigh)
        {
            float result = InterpolateRangeClamped(
                pTweaks->fGetupSpeedLow,
                0.0f,
                pTweaks->fGetupEnergyLow,
                pTweaks->fGetupEnergyHigh,
                mFatigue.mfEnergyLevel);
            m_pCurrentAnimController->m_fPlaybackSpeedScale = result;
        }

        if (ShouldStartCrossBlend(8))
        {
            InitActionMove(false);
        }
    }
    else
    {
        if (ShouldStartCrossBlend(9))
        {
            InitActionMoveWB();
        }
    }
}

/**
 * Offset/Address/Size: 0x17FC | 0x8004FD38 | size: 0x108
 */
void Goalie::ActionPass(float deltaTime)
{
    if (m_pBall != nullptr)
    {
        if (mpPassTarget != nullptr)
        {
            float dy = mpPassTarget->m_v3Position.f.y - m_v3Position.f.y;
            float dx = mpPassTarget->m_v3Position.f.x - m_v3Position.f.x;
            float angleRad = nlATan2f(dy, dx);

            m_aDesiredFacingDirection = (unsigned short)(s32)(10430.378f * angleRad);
        }
        else
        {
            if (m_pTeam->m_pNet->m_baseLocation.f.x > 0.0f)
            {
                m_aDesiredFacingDirection = 0x8000;
            }
            else
            {
                m_aDesiredFacingDirection = 0;
            }
        }

        GoalieTweaks* pTweaks = static_cast<GoalieTweaks*>(m_pTweaks);
        unsigned short newFacing = SeekDirection(
            m_aActualFacingDirection,
            m_aDesiredFacingDirection,
            pTweaks->fThrowingDirectionSeekSpeed,
            pTweaks->fThrowingDirectionSeekFalloff,
            deltaTime);
        SetFacingDirection(newFacing);
    }
    if (ShouldStartCrossBlend(8))
    {
        InitActionMove(false);
    }
}

/**
 * Offset/Address/Size: 0x1554 | 0x8004FA90 | size: 0x2A8
 */
void Goalie::ActionPassIntercept(float deltaTime)
{
    if (muBallDeflectCount != g_pBall->m_bBallDeflectCount)
    {
        InitActionMove(true);
        return;
    }

    mfWaitTime -= deltaTime;

    switch (mnSubstate)
    {
    case 1:
    {
        if (mfWaitTime <= 0.02f)
        {
            InitActionPassInterceptSave();
        }
        return;
    }
    case 4:
    {
        // Calculate angle to target position
        float dy = mv3TargetPosition.f.y - m_v3Position.f.y;
        float dx = mv3TargetPosition.f.x - m_v3Position.f.x;
        float angleToTarget = nlATan2f(dy, dx);
        u16 targetAngle = (u16)(s32)(10430.378f * angleToTarget);

        // Calculate angle to ball position
        dy = g_pBall->m_v3Position.f.y - m_v3Position.f.y;
        dx = g_pBall->m_v3Position.f.x - m_v3Position.f.x;
        float angleToBall = nlATan2f(dy, dx);
        u16 ballAngle = (u16)(s32)(10430.378f * angleToBall);

        // Choose run animation based on angle difference
        s16 angleDiff = (s16)(targetAngle - m_aActualFacingDirection);
        int animID = ChooseRunAnim(angleDiff, mv3TargetPosition, 1.0f);

        // Check if we need to adjust the target angle
        s16 ballAngleDiff = (s16)(ballAngle - targetAngle);
        ballAngleDiff = ballAngleDiff < 0 ? -ballAngleDiff : ballAngleDiff;

        u16 absBallAngleDiff = (u16)ballAngleDiff;

        if ((absBallAngleDiff > 0x4000) && (animID != 8) && ((m_eAnimID == 8) || (m_eAnimID == 0x27)))
        {
            targetAngle += 0x8000;
        }

        if ((mfWaitTime > 0.25f) && (animID != 8))
        {
            PlayNewAnim(animID);
            InitMovementFromAnim(0, v3Zero, 1.0f, false);

            GoalieTweaks* pTweaks = static_cast<GoalieTweaks*>(m_pTweaks);
            u16 newFacing = SeekDirection(
                m_aActualFacingDirection,
                targetAngle,
                pTweaks->fRunningDirectionSeekSpeed,
                pTweaks->fRunningDirectionSeekFalloff,
                deltaTime);
            SetFacingDirection(newFacing);
            return;
        }

        if (CanInterceptPass())
        {
            if (mfWaitTime <= 0.02f)
            {
                InitActionPassInterceptSave();
                return;
            }

            mnSubstate = 1;
            PlayNewAnim(8);

            GoalieTweaks* pTweaks = static_cast<GoalieTweaks*>(m_pTweaks);
            InitMovementFromAnimSeek(pTweaks->fRunningDirectionSeekSpeed, pTweaks->fRunningDirectionSeekFalloff);
            return;
        }

        float tmp = GoalieSave::mfCrouchDuration;
        if ((g_pBall->m_tPassTargetTimer.GetSeconds() < tmp) && (IsCloseToPlane(mv3TargetPosition, m_v3Position, 1.2f)))
        {
            InitActionPreCrouch(GOALIECROUCH_PASS);
            return;
        }

        mUrgency = URGENCY_HIGH;
        InitActionMove(true);
    }
    }
}

/**
 * Offset/Address/Size: 0x135C | 0x8004F898 | size: 0x1F8
 */
void Goalie::ActionPreCrouch(float deltaTime)
{
    nlVector3 targetPos = g_pBall->m_v3Position;

    if (!CheckForSTSAttack())
    {
        if (g_pBall->GetOwnerFielder() != NULL)
        {
            cFielder* pOwnerFielder = g_pBall->GetOwnerFielder();
            if (IsOnSameTeam((cPlayer*)pOwnerFielder))
            {
                InitActionMove(false);
            }
            else if (IsWithinPounceRange())
            {
                InitActionPursueBallCarrier();
                InitActionPursueBallPounce();
            }
            else
            {
                if (pOwnerFielder->m_eActionState != ACTION_SHOT && pOwnerFielder->m_eActionState != ACTION_SHOOT_TO_SCORE)
                {
                    InitActionMove(true);
                }
                else if (mCrouchType != GOALIECROUCH_SHOT)
                {
                    InitActionMove(true);
                }
            }
        }
        else if (g_pBall->m_pPassTarget == NULL)
        {
            if (mpShooter == NULL || (mpShooter->m_eActionState != ACTION_LOOSE_BALL_SHOT) || (mCrouchType != GOALIECROUCH_LOOSEBALL))
            {
                InitActionMove(true);
            }
        }
        else
        {
            if (mCrouchType != GOALIECROUCH_PASS)
            {
                InitActionMove(true);
            }

            targetPos = g_pBall->m_pPassTarget->m_v3Position;
        }

        if (mGoalieActionState == GOALIEACTION_PRE_CROUCH)
        {
            float dy = targetPos.f.y - m_v3Position.f.y;
            float dx = targetPos.f.x - m_v3Position.f.x;
            float angle = nlATan2f(dy, dx);

            m_aDesiredFacingDirection = (u16)(s32)(10430.378f * angle);

            GoalieTweaks* pTweaks = static_cast<GoalieTweaks*>(m_pTweaks);
            u16 newFacing = SeekDirection(
                m_aActualFacingDirection,
                m_aDesiredFacingDirection,
                75000.0f,
                4000.0f,
                deltaTime);
            SetFacingDirection(newFacing);
        }
    }
}

/**
 * Offset/Address/Size: 0xF9C | 0x8004F4D8 | size: 0x3C0
 */
void Goalie::ActionPursueBallCarrier(float)
{
}

static inline cPlayer* GetBallOwner(cBall* pBall, cBall** ppBall)
{
    *ppBall = pBall;
    return pBall->m_pOwner;
}

/**
 * Offset/Address/Size: 0xCCC | 0x8004F208 | size: 0x2D0
 */
void Goalie::ActionPursueBallPounce(float)
{
    float animTime = m_pCurrentAnimController->m_fTime;

    if (m_pBall == NULL)
    {
        if (animTime < 0.2f && CheckForSTSAttack())
        {
            PlayNewAnim(8);
            return;
        }

        cBall* pBall;
        cPlayer* pOwner = GetBallOwner(g_pBall, &pBall); // wtf..

        if (pOwner == NULL)
        {
            SetGoalieAction(GOALIEACTION_LOOSEBALL_PICKUP, 0);
            mfTargetTime = 0.0f;
            mfWaitTime = -1.0f;
            return;
        }

        if (IsOnSameTeam(pOwner) || !IsOpponentBallCarrierInRange())
        {
            InitActionMove(true);
            return;
        }

        if (CalculateDistanceSquared(GetJointPosition(m_nBallJointIndex), pBall->m_v3Position) < 0.16000001f
            || CalculateDistanceSquared(GetJointPosition(m_nLeftHandJointIndex), pBall->m_v3Position) < 0.16000001f
            || CalculateDistanceSquared(GetJointPosition(m_nRightHandJointIndex), pBall->m_v3Position) < 0.16000001f)
        {
            ExecutePounce(pOwner, true);
            return;
        }

        float pickupTime = mpLooseBallInfo->mfPickupTime;
        if ((animTime < pickupTime) && g_pBall->m_tShotTimer.m_uPackedTime == 0)
        {
            float ratio = animTime / pickupTime;
            float interpValue = ratio * (ratio * ((-2.0f * ratio) + 3.0f));

            if (interpValue < 0.99f && !mbPlayMiss)
            {
                TrackTarget(g_pBall->m_v3Position, interpValue);
            }
        }
    }

    if (animTime > 0.95f)
    {
        if (m_eAnimID != 0x7C)
        {
            if (m_pBall == NULL)
            {
                const GoalieTweaks* pTweaks = static_cast<const GoalieTweaks*>(m_pTweaks);
                if (mFatigue.mfEnergyLevel < pTweaks->fGetupEnergyHigh)
                {
                    float speed = InterpolateRangeClamped(
                        pTweaks->fGetupSpeedLow,
                        0.0f,
                        pTweaks->fGetupEnergyLow,
                        pTweaks->fGetupEnergyHigh,
                        mFatigue.mfEnergyLevel);
                    m_pCurrentAnimController->m_fPlaybackSpeedScale = speed;
                }

                if (ShouldStartCrossBlend(8))
                {
                    InitActionMove(false);
                    return;
                }
            }
            else
            {
                if (ShouldStartCrossBlend(9))
                {
                    InitActionMoveWB();
                    return;
                }
            }
        }
        else
        {
            InitActionPursueRecover();
        }
    }
}

/**
 * Offset/Address/Size: 0xA7C | 0x8004EFB8 | size: 0x250
 */
void Goalie::ActionOffplay(float)
{
}

/**
 * Offset/Address/Size: 0x860 | 0x8004ED9C | size: 0x21C
 */
void Goalie::ActionLooseBallPursueBouncing(float)
{
}

/**
 * Offset/Address/Size: 0x6CC | 0x8004EC08 | size: 0x194
 * TODO: the math to define the angle for SetFacingDirection does not match yet
 */
void Goalie::ActionSTSAttackSetup(float deltaTime)
{
    if (!IsOpponentInSTS())
    {
        InitActionMove(true);
        return;
    }

    mfWaitTime -= deltaTime;
    if (mfWaitTime <= 0.0)
    {
        InitActionSTSAttack();
        return;
    }

    cFielder* pOwnerFielder = g_pBall->GetOwnerFielder();

    float dx = m_v3Position.f.x - pOwnerFielder->m_v3Position.f.x;
    float dy = m_v3Position.f.y - pOwnerFielder->m_v3Position.f.y;
    float distSq = dx * dx + dy * dy;
    float pickupDistSq = mpLooseBallInfo->mfPickupDistance * mpLooseBallInfo->mfPickupDistance;

    int animID = 8;
    if (distSq > pickupDistSq)
    {
        animID = 0x1A;
    }

    PlayNewAnim(animID);
    InitMovementFromAnim(0, v3Zero, 1.0f, false);

    GetLocalPoint(mv3LocalContactPosition, pOwnerFielder->m_v3Position, m_v3Position, m_aActualFacingDirection);

    float angle = 10430.378f * nlATan2f(mv3LocalContactPosition.f.y, mv3LocalContactPosition.f.x);
    float progressRatio = (mfTargetTime - mfWaitTime) / mfTargetTime;

    s32 angleDeltaInt = (s32)angle;
    s32 multiplierInt = (s32)(1024.0f * (progressRatio * (progressRatio * ((-2.0f * progressRatio) + 3.0f))));
    s32 adjustedDelta = (multiplierInt * angleDeltaInt) / 1024;

    u16 newFacing = m_aActualFacingDirection + adjustedDelta;

    SetFacingDirection(newFacing);
    m_aDesiredFacingDirection = newFacing;
}

/**
 * Offset/Address/Size: 0x2B8 | 0x8004E7F4 | size: 0x414
 */
void Goalie::ActionSTSAttack(float)
{
}

/**
 * Offset/Address/Size: 0x168 | 0x8004E6A4 | size: 0x150
 */
void Goalie::ActionSnapBall(float)
{
    unsigned short aRootRot;
    float fTimeLeft;
    nlVector3 v3TargetPos;
    nlVector3 v3RootPos;

    if (g_pBall->m_pOwner != this)
    {
        TacklePlayer(g_pBall->m_pOwner);

        fTimeLeft = m_tNoPickupTimer.GetSeconds();

        if (fTimeLeft > 0.0f)
        {
            GetCurrentAnimFuture(m_nBallJointIndex, m_pCurrentAnimController->m_fTime, v3TargetPos, v3RootPos, aRootRot);

            float invInterpFactor;
            float interpFactor;

            interpFactor = (1.0f / mfWaitTime) * (mfWaitTime - fTimeLeft);
            invInterpFactor = 1.0f - interpFactor;

            v3TargetPos.f.x = (invInterpFactor * g_pBall->m_v3Position.f.x) + (interpFactor * v3TargetPos.f.x);
            v3TargetPos.f.y = (invInterpFactor * g_pBall->m_v3Position.f.y) + (interpFactor * v3TargetPos.f.y);
            v3TargetPos.f.z = (invInterpFactor * g_pBall->m_v3Position.f.z) + (interpFactor * v3TargetPos.f.z);

            g_pBall->SetPosition(v3TargetPos);
            return;
        }
        PickupBall(g_pBall);
        mbPickedUp = true;
        return;
    }

    if (m_pBall == NULL)
    {
        InitActionMove(true);
        return;
    }

    bool shouldMoveWB = false;
    if (m_pCurrentAnimController->m_ePlayMode == PM_HOLD && m_pCurrentAnimController->m_fTime == 1.0f)
    {
        shouldMoveWB = true;
    }

    if (shouldMoveWB)
    {
        InitActionMoveWB();
    }
}

/**
 * Offset/Address/Size: 0x0 | 0x8004E53C | size: 0x168
 */
void Goalie::ActionGrabBall(float)
{
    bool bShouldInitMove = false;
    if (m_pCurrentAnimController->m_ePlayMode == PM_HOLD && m_pCurrentAnimController->m_fTime == 0.0f)
    {
        bShouldInitMove = true;
    }

    if (bShouldInitMove)
    {
        if (m_pBall == NULL)
        {
            InitActionMove(true);
            return;
        }
        InitActionMoveWB();
        return;
    }

    if (g_pBall->m_pOwner != this)
    {
        if (g_pBall->GetOwnerFielder() == NULL)
        {
            InitActionMove(false);
            return;
        }

        float fTimeThreshold = 0.1f + mpLooseBallInfo->mfPickupTime;
        if (m_pCurrentAnimController->m_fTime < fTimeThreshold)
        {
            float fInterpFactor = m_pCurrentAnimController->m_fTime / fTimeThreshold;
            TrackTarget(g_pBall->m_v3Position, fInterpFactor);

            const nlVector3& jointPos = GetJointPosition(m_nBallJointIndex);

            nlVector3 delta;
            nlVec3Set(delta, g_pBall->m_v3Position.f.x - jointPos.f.x, g_pBall->m_v3Position.f.y - jointPos.f.y, g_pBall->m_v3Position.f.z - jointPos.f.z);

            if (nlGetLengthSquared3D(delta.f.x, delta.f.y, delta.f.z) < 0.25f)
            {
                StealBall(g_pBall->m_pOwner);
                PickupBall(g_pBall);
                mbPickedUp = true;
                g_pBall->ClearShotInProgress();
                EmitGoalieCatch(this, "goalie_catch", false);
            }
        }
    }
}
