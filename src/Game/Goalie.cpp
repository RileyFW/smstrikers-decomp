#include "Game/Goalie.h"
#include "Game/AI/GoalieLooseBall.h"
#include "Game/AI/AiUtil.h"
#include "Game/Ball.h"
#include "Game/AI/Fielder.h"
#include "Game/CharacterAudio.h"
#include "Game/SAnim.h"
#include "Game/Physics/PhysicsGoalie.h"
#include "Game/Physics/PhysicsFakeBall.h"
#include "Game/Field.h"
#include "Game/AnimInventory.h"
#include "Game/CharacterTriggers.h"
#include "Game/GameTweaks.h"
#include "Game/Team.h"
#include "Game/AI/FilteredRandom.h"
#include "NL/plat/plataudio.h"
#include "types.h"

extern cTeam* g_pCurrentlyUpdatingTeam;

static const nlVector3 v3Zero = { 0.0f, 0.0f, 0.0f };

/**
 * Offset/Address/Size: 0x0 | 0x80042AFC | size: 0x148
 */
void Goalie::InitActionPostWhistle()
{
}

/**
 * Offset/Address/Size: 0x148 | 0x80042C44 | size: 0x150
 */
void Goalie::WhackSTSPlayer(cFielder*)
{
}

/**
 * Offset/Address/Size: 0x298 | 0x80042D94 | size: 0x6C
 */
void Goalie::StealBall(cPlayer* pPlayer)
{
    if (pPlayer == NULL)
    {
        return;
    }

    if (pPlayer->m_eClassType != FIELDER)
    {
        return;
    }

    if (pPlayer->m_pBall == NULL)
    {
        return;
    }

    pPlayer->ReleaseBall();

    cFielder* pFielder = static_cast<cFielder*>(pPlayer);
    if (pFielder->m_eFielderDesireState == FIELDERDESIRE_FINISH_ACTION)
    {
        return;
    }

    pFielder->EndDesire(false);
    pFielder->EndAction();
}

/**
 * Offset/Address/Size: 0x304 | 0x80042E00 | size: 0xC0
 */
void Goalie::TacklePlayer(cPlayer* pPlayer)
{
    cFielder* pFielder = static_cast<cFielder*>(pPlayer);
    if ((pPlayer != NULL) && (pPlayer->m_eClassType == FIELDER) && (pFielder->IsFallenDown(0.0f) == 0))
    {
        pPlayer->PlayRandomCharDialogue(CHAR_DIALOGUE_HIT, VECTORS, 100.0f, -1.0f);
        if (pPlayer->m_pBall != 0)
        {
            pPlayer->ReleaseBall();
        }
        if (IsOnSameTeam(pFielder) != 0)
        {
            pFielder->EndDesire(false);
            pFielder->EndAction();
            return;
        }
        pFielder->InitActionSlideAttackReact(this, false);
    }
}

/**
 * Offset/Address/Size: 0x3C4 | 0x80042EC0 | size: 0x1F4
 */
void Goalie::TrackTarget(const nlVector3&, float)
{
}

/**
 * Offset/Address/Size: 0x5B8 | 0x800430B4 | size: 0x384
 */
void Goalie::SetDesiredSaveFacing(const nlVector3& v3BallPosition)
{
    FORCE_DONT_INLINE;
}

/**
 * Offset/Address/Size: 0x93C | 0x80043438 | size: 0x8
 */
PhysicsGoalie* Goalie::GetPhysicsGoalie()
{
    return static_cast<PhysicsGoalie*>(m_pPhysicsCharacter);
}

/**
 * Offset/Address/Size: 0x944 | 0x80043440 | size: 0x50
 */
void Goalie::FindSTSSpinData(bool bParam)
{
    mpSaveData = GoalieSave::GetSTSSpinMissData(bParam);

    GoalieSave::GetClosestBlendedPos(mBlendInfo, v3Zero, mpSaveData);

    mpLooseBallInfo = NULL;
}

/**
 * Offset/Address/Size: 0x994 | 0x80043490 | size: 0xF0
 */
bool Goalie::FindSTSMissData(const nlVector3& rPos)
{
    nlVector3 localPos = rPos;

    float goalLineX = cField::GetGoalLineX(1U);
    float absY = (float)fabsf(localPos.f.y);
    float sidelineY = cField::GetSidelineY(1U);

    float scale = 6.0f;
    float threshold = goalLineX - ((absY * scale) / sidelineY);

    bool bIsOutsideRange;
    if (localPos.f.x > threshold)
    {
        bIsOutsideRange = true;
    }
    else if (localPos.f.x < -threshold)
    {
        bIsOutsideRange = true;
    }
    else
    {
        bIsOutsideRange = false;
    }

    mpSaveData = GoalieSave::GetRandomSTSMissData(bIsOutsideRange);
    GoalieSave::GetClosestBlendedPos(mBlendInfo, v3Zero, mpSaveData);

    mpLooseBallInfo = NULL;

    return bIsOutsideRange;
}

/**
 * Offset/Address/Size: 0xA84 | 0x80043580 | size: 0x4C
 */
void Goalie::FindSTSStunData()
{
    mpSaveData = GoalieSave::GetRandomSTSSaveData();
    GoalieSave::GetClosestBlendedPos(mBlendInfo, v3Zero, mpSaveData);
    mpLooseBallInfo = NULL;
}

/**
 * Offset/Address/Size: 0xAD0 | 0x800435CC | size: 0x460
 */
void Goalie::EventHandler(Event*, void*)
{
}

/**
 * Offset/Address/Size: 0xF30 | 0x80043A2C | size: 0x8A4
 */
void Goalie::DoPassRelease()
{
}

/**
 * Offset/Address/Size: 0x17D4 | 0x800442D0 | size: 0x3C
 */
void Goalie::ChooseSwatAnim(int nParam)
{
    mpLooseBallInfo = LooseBallAnims::GetSwatSTSInfo(nParam);
    mpSaveData = NULL;
}

/**
 * Offset/Address/Size: 0x1810 | 0x8004430C | size: 0xB8
 */
int Goalie::ChooseRunAnim(short nAngle, const nlVector3& rTargetPos, float fThreshold)
{
    float fDeltaX = rTargetPos.f.x - m_v3Position.f.x;
    float fDeltaY = rTargetPos.f.y - m_v3Position.f.y;
    unsigned short nAbsAngle;
    int nCurrentAnimID = m_eAnimID;

    if (((fDeltaX * fDeltaX) + (fDeltaY * fDeltaY)) < (fThreshold * fThreshold))
    {
        mMoveDirection = GOALIEDIR_IDLE;
        return 8;
    }

    nAbsAngle = (nAngle < 0 ? -nAngle : nAngle);

    mMoveDirection = GOALIEDIR_FORWARD;

    int id;

    if (((nCurrentAnimID == 0x24) || (nCurrentAnimID == 0x25)) && (m_pCurrentAnimController->m_fTime < 0.92f))
    {
        id = nCurrentAnimID;
    }
    else if (nAbsAngle <= 0x2AF8 || nCurrentAnimID == 0x26)
    {
        id = 0x26;
    }
    else if (nAngle > 0)
    {
        id = 0x25;
    }
    else
    {
        id = 0x24;
    }

    return id;
}

/**
 * Offset/Address/Size: 0x18C8 | 0x800443C4 | size: 0x4AC
 */
bool Goalie::CanInterceptPass()
{
    FORCE_DONT_INLINE;
    return false;
}

/**
 * Offset/Address/Size: 0x1D74 | 0x80044870 | size: 0xF4
 */
float Goalie::CalcTimeToPlane()
{
    nlVector3 localVelocity;
    nlVector4 plane;
    float time;
    unsigned short desiredFacing;

    SetDesiredSaveFacing(g_pBall->m_v3Position);

    desiredFacing = m_aDesiredFacingDirection;
    MakePerpendicularPlane(m_v3Position, desiredFacing, plane, 0.2f);

    time = FakeBallWorld::GetPredictedPlaneIntersectTime(plane, mv3TargetPosition, localVelocity);

    float absTargetX = (float)fabsf(mv3TargetPosition.f.x);
    float goalLineX = cField::GetGoalLineX(1U);

    if (absTargetX > goalLineX)
    {
        return -1.0f;
    }

    if (time > 0.0f)
    {
        GetLocalPoint(mv3LocalContactPosition, mv3TargetPosition, m_v3Position, desiredFacing);
        GetLocalPoint(mv3LocalContactVelocity, localVelocity, v3Zero, desiredFacing);
    }

    return time;
}

/**
 * Offset/Address/Size: 0x1E68 | 0x80044964 | size: 0x138
 */
float Goalie::CalcSaveParameters(float fTimeToContact, unsigned int uSaveType, bool bFromTakeoff, bool bFindFailSave)
{
    // float fTime = fTimeToContact;
    if (mbShouldMiss)
    {
        fTimeToContact += ((GoalieTweaks*)m_pTweaks)->fSaveMissDelay;
        mpSaveData = NULL;
    }
    else
    {
        mpSaveData = GoalieSave::FindBestSave(mBlendInfo, mv3LocalContactPosition, fTimeToContact, false, uSaveType, bFromTakeoff);
    }

    if (mpSaveData != NULL)
    {
        mbPlayMiss = false;
    }
    else
    {
        if (!mbShouldMiss && !bFindFailSave)
        {
            return -1.0f;
        }

        mpSaveData = GoalieSave::FindBestSave(mBlendInfo, mv3LocalContactPosition, 0.0f, true, uSaveType & 0xFFFC, false);
        mbPlayMiss = true;
    }

    const float blendFactor = (mpSaveData->mv3SavePos.f.x - mv3LocalContactPosition.f.x) / mv3LocalContactVelocity.f.x;

    nlVec3Set(mv3LocalContactPosition,
        (blendFactor * mv3LocalContactVelocity.f.x) + mv3LocalContactPosition.f.x,
        (blendFactor * mv3LocalContactVelocity.f.y) + mv3LocalContactPosition.f.y,
        (blendFactor * mv3LocalContactVelocity.f.z) + mv3LocalContactPosition.f.z);

    return fTimeToContact + blendFactor;
}

/**
 * Offset/Address/Size: 0x1FA0 | 0x80044A9C | size: 0xE4
 */
unsigned short Goalie::CalcBestSave(float fTime, const nlVector3& rTargetPos, const nlVector3& rContactPos, unsigned int uSaveType, bool bParam)
{
    SetDesiredSaveFacing(rTargetPos);

    muSaveType = uSaveType;
    mpLooseBallInfo = NULL;

    GetLocalPoint(mv3LocalContactPosition, rContactPos, m_v3Position, m_aDesiredFacingDirection);

    if (uSaveType == 0 || fTime <= 0.0f)
    {
        mpSaveData = NULL;
        return m_aDesiredFacingDirection;
    }

    mpSaveData = GoalieSave::FindBestSave(mBlendInfo, mv3LocalContactPosition, fTime, bParam, uSaveType, false);

    if (mpSaveData != NULL)
    {
        mbPlayMiss = false;
    }

    return m_aDesiredFacingDirection;
}

/**
 * Offset/Address/Size: 0x2084 | 0x80044B80 | size: 0xC8
 */
void Goalie::InitActionGrabBall()
{
    cFielder* pOwnerFielder = g_pBall->GetOwnerFielder();
    if (pOwnerFielder == NULL)
    {
        return;
    }

    CleanGoalieAction();

    mPrevGoalieActionState = mGoalieActionState;
    mGoalieActionState = GOALIEACTION_GRAB_BALL;
    mnSubstate = 0;

    GetLocalPoint(mv3LocalContactPosition, g_pBall->m_v3Position, m_v3Position, m_aActualFacingDirection);

    mpLooseBallInfo = LooseBallAnims::FindLooseBallAnim(mv3LocalContactPosition, true);

    SetAnimState(mpLooseBallInfo->mnAnimID, true, 0.2f, false, false);
    InitMovementFromAnim(0, v3Zero, 1.0f, false);

    mbDoHeadTrack = false;
    mbPickedUp = false;
}

/**
 * Offset/Address/Size: 0x214C | 0x80044C48 | size: 0x100
 */
bool Goalie::IsTeammateHoardingBall()
{

    return false;
}

/**
 * Offset/Address/Size: 0x224C | 0x80044D48 | size: 0xD8
 */
void Goalie::InitActionSTSAttack()
{
    mbDoHeadTrack = false;
    CleanGoalieAction();

    mPrevGoalieActionState = mGoalieActionState;
    mGoalieActionState = GOALIEACTION_STS_ATTACK;
    mnSubstate = 0;

    SetAnimState(mpLooseBallInfo->mnAnimID, true, 0.2f, false, false);
    InitMovementFromAnim(0, v3Zero, 1.0f, false);

    cFielder* pFielder = g_pBall->GetOwnerFielder();
    float deltaX = pFielder->m_v3Position.f.x - m_v3Position.f.x;
    float deltaY = pFielder->m_v3Position.f.y - m_v3Position.f.y;
    float distance = nlSqrt((deltaX * deltaX) + (deltaY * deltaY), true);
    mfTargetDist = distance - mpLooseBallInfo->mfPickupDistance;
    mpShooter = pFielder;
}

/**
 * Offset/Address/Size: 0x2324 | 0x80044E20 | size: 0x2DC
 */
void Goalie::InitActionDiveRecover()
{
    if (mpSaveData != NULL && mpSaveData->mnRecoverAnimID >= 0)
    {
        mbDoHeadTrack = false;

        if (mnOffplayPending != GOALIE_OFFPLAY_NONE)
        {
            int randomValue = nlRandom(2, &nlDefaultSeed);
            CleanGoalieAction();

            mPrevGoalieActionState = mGoalieActionState;
            mGoalieActionState = GOALIEACTION_OFFPLAY;
            mnSubstate = 0;

            int animID;
            if (m_pAnimInventory->GetMirrored(m_eAnimID))
            {
                animID = (randomValue == 0) ? 0x89 : 0x8B;
            }
            else
            {
                animID = (randomValue == 0) ? 0x88 : 0x8A;
            }

            SetAnimState(animID, true, 0.2f, false, false);
            mnOffplayPending = GOALIE_OFFPLAY_NONE;
        }
        else
        {
            CleanGoalieAction();

            mPrevGoalieActionState = mGoalieActionState;
            mGoalieActionState = GOALIEACTION_DIVE_RECOVER;
            mnSubstate = 0;

            SetAnimState(mpSaveData->mnRecoverAnimID, true, 0.2f, false, false);
        }

        InitMovementFromAnim(0, v3Zero, 1.0f, false);
    }
    else
    {
        if (m_pBall == NULL)
        {
            CleanGoalieAction();

            mPrevGoalieActionState = mGoalieActionState;
            mGoalieActionState = GOALIEACTION_MOVE;
            mnSubstate = 0;

            SetAnimState(8, true, 0.2f, false, false);
            InitMovementFromAnim(0, v3Zero, 1.0f, false);

            mnSubstate = 1;
            mMoveDirection = GOALIEDIR_IDLE;

            m_pPhysicsCharacter->m_CanCollideWithBall = 1;
            mbShouldMiss = false;
            mbDoNavigate = false;
            m_pPhysicsCharacter->m_CanCollidedWithGoalLine = 1;
            m_pPhysicsCharacter->m_CanCollideWithWall = 1;

            if (mbStunEffectActive)
            {
                KillDaze(this);
                mbStunEffectActive = false;
            }

            mpShooter = NULL;
            mUrgency = URGENCY_LOW;
            mfSpeedScale = 1.0f;
            mbPosGoalieNetCheck = false;
            mbNegGoalieNetCheck = false;
            mbDoHeadTrack = true;
            mbBallImpacted = false;
            mbNoUserControl = false;
            mbPickedUp = false;

            ActionMove(0.0f); // TODO: ActionMove needs to be declared in Goalie.h
        }
        else
        {
            if (m_pBall == NULL)
            {
                PickupBall(g_pBall);
            }
            CleanGoalieAction();

            mPrevGoalieActionState = mGoalieActionState;
            mGoalieActionState = GOALIEACTION_MOVE_WB;
            mnSubstate = 0;

            SetAnimState(9, true, 0.2f, false, false);
            InitMovementFromAnim(0, v3Zero, 1.0f, false);

            mfWaitTime = ((GoalieTweaks*)m_pTweaks)->fGoalieBallTime;
            mfTargetTime = 0.0f;
            mpPassTarget = NULL;
        }
    }

    mbPickedUp = false;
}

/**
 * Offset/Address/Size: 0x2600 | 0x800450FC | size: 0x224
 */
void Goalie::InitActionChipShotStumble()
{
}

/**
 * Offset/Address/Size: 0x2824 | 0x80045320 | size: 0x180
 */
void Goalie::InitActionSTSRecover()
{
    if ((mpSaveData != NULL) && (mpSaveData->mnRecoverAnimID >= 0))
    {
        if (mpSaveData->muSaveType & 0x70000)
        {
            mbDoHeadTrack = false;
            CleanGoalieAction();

            mPrevGoalieActionState = mGoalieActionState;
            mGoalieActionState = GOALIEACTION_STS_RECOVER;
            mnSubstate = 0;

            SetAnimState(mpSaveData->mnRecoverAnimID, true, 0.2f, false, false);

            if ((mpSaveData->muSaveType + 0xFFFF0000) == 0)
            {

                mfWaitTime = ((GoalieTweaks*)m_pTweaks)->fGoalieStunTimeMin;

                float timeRange = ((GoalieTweaks*)m_pTweaks)->fGoalieStunTimeMax - mfWaitTime;
                if (timeRange > 0.0f)
                {
                    static FilteredRandomReal randgenTimeRange;
                    float randomValue = timeRange * randgenTimeRange.genrand();
                    mfWaitTime += randomValue;
                }

                InitMovementFromAnim(0, v3Zero, 1.0f, false);
                g_pBall->m_uGoalType = 4;
            }
            return;
        }
        else
        {
            if ((mpSaveData->muSaveType & 0xFFFC) && (mnOffplayPending == GOALIE_OFFPLAY_NONE))
            {
                g_pBall->m_uGoalType = 4;
            }
        }
    }
    InitActionDiveRecover();
}

/**
 * Offset/Address/Size: 0x29A4 | 0x800454A0 | size: 0x3A8
 */
void Goalie::InitActionSTS()
{
    FORCE_DONT_INLINE;
}

/**
 * Offset/Address/Size: 0x2D4C | 0x80045848 | size: 0x250
 */
void Goalie::InitActionSTSSetup()
{
    if (mGoalieActionState != GOALIEACTION_PURSUE_BALL_POUNCE)
    {
        if (mGoalieActionState == GOALIEACTION_DIVE_RECOVER)
        {
            return;
        }

        mnOffplayPending = GOALIE_OFFPLAY_NONE;

        if (mGoalieActionState != GOALIEACTION_STS_RECOVER)
        {
            CleanGoalieAction();
            mPrevGoalieActionState = mGoalieActionState;
            mGoalieActionState = GOALIEACTION_STS_SETUP;
            mnSubstate = 0;
        }
        else
        {
            SaveData* pSavedSaveData = mpSaveData;
            CleanGoalieAction();
            mPrevGoalieActionState = mGoalieActionState;
            mGoalieActionState = GOALIEACTION_STS_SETUP;
            mnSubstate = 0;
            mpSaveData = pSavedSaveData;
        }

        SetDesiredSaveFacing(g_pBall->m_v3Position);

        nlVector4 plane;
        const u16 desiredFacingDirection = m_aDesiredFacingDirection;
        const nlVector3& pPosition = m_v3Position;

        MakePerpendicularPlane(pPosition, desiredFacingDirection, plane, 0.2f);

        nlVector3 localVelocity;
        float time = FakeBallWorld::GetPredictedPlaneIntersectTime(plane, mv3TargetPosition, localVelocity);

        if (IsPositionBeyondGoalLine())
        {
            time = -1.0f;
        }
        else if (time > 0.0f)
        {
            GetLocalPoint(mv3LocalContactPosition, mv3TargetPosition, pPosition, desiredFacingDirection);
            GetLocalPoint(mv3LocalContactVelocity, localVelocity, v3Zero, desiredFacingDirection);
        }

        mfTimeTilSave = time;
        if (mfTimeTilSave < 0.0f)
        {
            mfTimeTilSave = 0.0f;
        }

        if (g_pBall->mbCanDamage && mpLooseBallInfo != NULL)
        {
            mpShooter = static_cast<cFielder*>(g_pBall->m_pShooter);
            mfWaitTime = mfTimeTilSave - (mpLooseBallInfo->mfPickupTime * mpLooseBallInfo->mfAnimDuration);
        }
        else
        {
            mpShooter = NULL;
            cBall* pBall = g_pBall;
            pBall->mbCanDamage = false;
            pBall->mpDamageTarget = NULL;
            mfWaitTime = mfTimeTilSave - mBlendInfo.mfMilestoneTime[2];

            if (mbShouldMiss)
            {
                mfWaitTime += 0.11f;
            }
        }

        if (mfWaitTime <= 0.01f)
        {
            InitActionSTS();
            return;
        }

        SetAnimState(0xA, true, 0.2f, false, false);
        GoalieTweaks* pGoalieTweaks = static_cast<GoalieTweaks*>(m_pTweaks);
        InitMovementFromAnimSeek(pGoalieTweaks->fSaveDirectionSeekSpeed, pGoalieTweaks->fSaveDirectionSeekFalloff);
    }
}

/**
 * Offset/Address/Size: 0x2F9C | 0x80045A98 | size: 0x34C
 */
void Goalie::InitActionSave()
{
}

/**
 * Offset/Address/Size: 0x32E8 | 0x80045DE4 | size: 0x70C
 */
void Goalie::InitActionSaveSetup(bool)
{
}

/**
 * Offset/Address/Size: 0x39F4 | 0x800464F0 | size: 0xB0
 */
void Goalie::InitActionMoveWB()
{
    if (m_pBall == NULL)
    {
        PickupBall(g_pBall);
    }

    CleanGoalieAction();

    mPrevGoalieActionState = mGoalieActionState;
    mGoalieActionState = GOALIEACTION_MOVE_WB;
    mnSubstate = 0;

    SetAnimState(9, true, 0.2f, false, false);
    InitMovementFromAnim(0, v3Zero, 1.0f, false);

    mfWaitTime = ((GoalieTweaks*)m_pTweaks)->fGoalieBallTime;
    mfTargetTime = 0.0f;
    mpPassTarget = NULL;
}

/**
 * Offset/Address/Size: 0x3AA4 | 0x800465A0 | size: 0x12C
 */
void Goalie::InitActionMove(bool bParam)
{
    CleanGoalieAction();

    mPrevGoalieActionState = mGoalieActionState;
    mGoalieActionState = GOALIEACTION_MOVE;
    mnSubstate = 0;

    SetAnimState(8, true, 0.2f, false, false);
    InitMovementFromAnim(0, v3Zero, 1.0f, false);

    mnSubstate = 1;
    mMoveDirection = GOALIEDIR_IDLE;

    m_pPhysicsCharacter->m_CanCollideWithBall = 1;
    mbShouldMiss = false;
    mbDoNavigate = false;
    m_pPhysicsCharacter->m_CanCollidedWithGoalLine = 1;
    m_pPhysicsCharacter->m_CanCollideWithWall = 1;

    if (mbStunEffectActive)
    {
        KillDaze(this);
        mbStunEffectActive = false;
    }

    mpShooter = NULL;
    mUrgency = URGENCY_LOW;
    mfSpeedScale = 1.0f;
    mbPosGoalieNetCheck = false;
    mbNegGoalieNetCheck = false;
    mbDoHeadTrack = true;
    mbBallImpacted = false;
    mbNoUserControl = false;
    mbPickedUp = false;

    if (bParam)
    {
        ActionMove(0.0f);
    }
}

/**
 * Offset/Address/Size: 0x3BD0 | 0x800466CC | size: 0x1B04
 */
void Goalie::InitActionLooseBallSetup()
{
    FORCE_DONT_INLINE;
}

/**
 * Offset/Address/Size: 0x56D4 | 0x800481D0 | size: 0x8C
 */
void Goalie::InitActionLooseBallCatch()
{
    CleanGoalieAction();

    mPrevGoalieActionState = mGoalieActionState;
    mGoalieActionState = GOALIEACTION_LOOSEBALL_CATCH;
    mnSubstate = 0;

    mv3LocalContactPosition.f.x = 0.2f;

    mpSaveData = GoalieSave::FindBestSave(mBlendInfo, mv3LocalContactPosition, mfTargetTime, false, 1, true);

    mpLooseBallInfo = NULL;
    mMoveDirection = GOALIEDIR_IDLE;

    if (mpSaveData == NULL)
    {
        InitActionLooseBallSetup();
    }
}

/**
 * Offset/Address/Size: 0x5760 | 0x8004825C | size: 0x118
 */
void Goalie::CleanGoalieAction()
{
    switch (mGoalieActionState)
    {
    case GOALIEACTION_MOVE:
        mbDoNavigate = false;
        break;

    case GOALIEACTION_SAVE_SETUP:
    case GOALIEACTION_SAVE_REPOSITION:
    case GOALIEACTION_SAVE:
        if (mpSaveData != NULL)
        {
            if (mpSaveData->mnRecoverAnimID < 0)
            {
                mpSaveData = NULL;
            }
        }
        muSaveType = 0xFFFF;
        mbShouldMiss = false;
        mpPassTarget = NULL;
        mbBallImpacted = false;
        break;

    case GOALIEACTION_MISS_CHIP_SHOT:
        mpSaveData = NULL;
        break;

    case GOALIEACTION_DIVE_RECOVER:
        mbPosGoalieNetCheck = false;
        mbNegGoalieNetCheck = false;
        break;

    case GOALIEACTION_STS_SETUP:
    case GOALIEACTION_STS:
        mpShooter = NULL;
        break;

    case GOALIEACTION_STS_RECOVER:
        mpSaveData = NULL;
        if (mbStunEffectActive != false)
        {
            KillDaze(this);
            mbStunEffectActive = false;
        }
        break;

    case GOALIEACTION_STS_ATTACK_SETUP:
    case GOALIEACTION_STS_ATTACK:
        mbPlayMiss = false;
        break;

    case GOALIEACTION_LOOSEBALL_PICKUP:
        mbPlayMiss = false;
        mbNoUserControl = false;
        mbPickedUp = false;
        break;

    case GOALIEACTION_OFFPLAY:
        mnOffplayPending = GOALIE_OFFPLAY_NONE;
        break;

    case GOALIEACTION_SNAP_BALL:
        mpShooter = NULL;
        break;

    case GOALIEACTION_GRAB_BALL:
    default:
        break;
    }
}

/**
 * Offset/Address/Size: 0x5878 | 0x80048374 | size: 0x6C
 */
void Goalie::PlayNewAnim(int nAnimID)
{
    if (nAnimID == m_eAnimID)
    {
        cPN_SAnimController* pController = m_pCurrentAnimController;
        bool bSkipSetAnimState = false;

        if (pController->m_ePlayMode == PM_HOLD && pController->m_fTime == 1.0f)
        {
            bSkipSetAnimState = true;
        }

        if (!bSkipSetAnimState)
        {
            return;
        }
    }

    SetAnimState(nAnimID, true, 0.2f, false, false);
}

/**
 * Offset/Address/Size: 0x58E4 | 0x800483E0 | size: 0x458
 */
void Goalie::PlayBlendedAnims(float, int)
{
    FORCE_DONT_INLINE;
}

/**
 * Offset/Address/Size: 0x5D3C | 0x80048838 | size: 0x204
 */
void Goalie::SetupBlender(bool, const float*, int, int)
{
}

/**
 * Offset/Address/Size: 0x5F40 | 0x80048A3C | size: 0x64
 */
void Goalie::SaveBlendCallback(unsigned int nParam, cPN_SAnimController* pAnimCtrl)
{
    Goalie* pThis = reinterpret_cast<Goalie*>(nParam & ~3U);
    unsigned int saveDataIndex = nParam & 3U;

    SaveData* pSaveData = pThis->mBlendInfo.mpSaveData[saveDataIndex];
    if (pSaveData == NULL)
    {
        return;
    }

    float fTime = pAnimCtrl->m_fTime;

    int milestoneIndex = 0;

    while (milestoneIndex < 4 && fTime >= pSaveData->mfMilestonePercent[milestoneIndex])
    {
        milestoneIndex++;
    }

    pAnimCtrl->m_fPlaybackSpeedScale = pThis->mBlendInfo.mfMilestoneScale[saveDataIndex][milestoneIndex];
}

/**
 * Offset/Address/Size: 0x5FA4 | 0x80048AA0 | size: 0x54
 */
void Goalie::SetGoalieAction(eGoalieActionState newGoalieState, int newSubstate)
{
    CleanGoalieAction();
    mPrevGoalieActionState = mGoalieActionState;
    mGoalieActionState = newGoalieState;
    mnSubstate = newSubstate;
}

/**
 * Offset/Address/Size: 0x5FF8 | 0x80048AF4 | size: 0x10C
 */
void Goalie::UpdateActionState(float fDeltaTime)
{
    switch (mGoalieActionState)
    {
    case GOALIEACTION_MOVE:
        ActionMove(fDeltaTime);
        break;
    case GOALIEACTION_MOVE_WB:
        ActionMoveWB(fDeltaTime);
        break;
    case GOALIEACTION_SAVE_SETUP:
        ActionSaveSetup(fDeltaTime);
        break;
    case GOALIEACTION_SAVE_REPOSITION:
        ActionSaveReposition(fDeltaTime);
        break;
    case GOALIEACTION_SAVE:
        ActionSave(fDeltaTime);
        break;
    case GOALIEACTION_MISS_CHIP_SHOT:
        ActionChipShotStumble(fDeltaTime);
        break;
    case GOALIEACTION_DIVE_RECOVER:
        ActionDiveRecover(fDeltaTime);
        break;
    case GOALIEACTION_STS_SETUP:
        ActionSTSSetup(fDeltaTime);
        break;
    case GOALIEACTION_STS:
        ActionSTS(fDeltaTime);
        break;
    case GOALIEACTION_STS_RECOVER:
        ActionSTSRecover(fDeltaTime);
        break;
    case GOALIEACTION_PASS:
        ActionPass(fDeltaTime);
        break;
    case GOALIEACTION_PASS_INTERCEPT:
        ActionPassIntercept(fDeltaTime);
        break;
    case GOALIEACTION_PRE_CROUCH:
        ActionPreCrouch(fDeltaTime);
        break;
    case GOALIEACTION_PURSUE_BALL_CARRIER:
        ActionPursueBallCarrier(fDeltaTime);
        break;
    case GOALIEACTION_PURSUE_BALL_POUNCE:
        ActionPursueBallPounce(fDeltaTime);
        break;
    case GOALIEACTION_LOOSEBALL_SETUP:
        ActionLooseBallSetup(fDeltaTime);
        break;
    case GOALIEACTION_LOOSEBALL_CATCH:
        ActionLooseBallCatch(fDeltaTime);
        break;
    case GOALIEACTION_LOOSEBALL_PICKUP:
        ActionLooseBallPickup(fDeltaTime);
        break;
    case GOALIEACTION_LOOSEBALL_PURSUE_BOUNCING:
        ActionLooseBallPursueBouncing(fDeltaTime);
        break;
    case GOALIEACTION_LOOSEBALL_PURSUE_ROLLING:
        ActionLooseBallPursueRolling(fDeltaTime);
        break;
    case GOALIEACTION_LOOSEBALL_DESPERATE:
        ActionLooseBallDesperate(fDeltaTime);
        break;
    case GOALIEACTION_OFFPLAY:
        ActionOffplay(fDeltaTime);
        break;
    case GOALIEACTION_SNAP_BALL:
        ActionSnapBall(fDeltaTime);
        break;
    case GOALIEACTION_GRAB_BALL:
        ActionGrabBall(fDeltaTime);
        break;
    case GOALIEACTION_STS_ATTACK_SETUP:
        ActionSTSAttackSetup(fDeltaTime);
        break;
    case GOALIEACTION_STS_ATTACK:
        ActionSTSAttack(fDeltaTime);
        break;
    }
}

/**
 * Offset/Address/Size: 0x6104 | 0x80048C00 | size: 0x114
 */
void Goalie::MakeSaveEvent(bool)
{
}

/**
 * Offset/Address/Size: 0x6218 | 0x80048D14 | size: 0x104
 */
bool Goalie::IsPassThreat()
{
    bool var_r0;

    cPlayer* pPassTarget = g_pBall->m_pPassTarget;
    if (pPassTarget != NULL)
    {
        if (!IsOnSameTeam(pPassTarget))
        {
            cBall* pBall = g_pBall;
            float ballPassX = pBall->m_v3PassIntercept.f.x;

            if (
                ((float)fabs(pBall->m_v3PassIntercept.f.x) > (cField::GetPenaltyBoxX(1U) - 2.0f))
                && (ballPassX * m_v3Position.f.x > 0.0f)
                && ((float)fabs(pBall->m_v3PassIntercept.f.y) < (cField::GetPenaltyBoxY() + 2.0f)))
            {
                var_r0 = true;
            }
            else
            {
                var_r0 = false;
            }

            if (var_r0)
            {
                mpPassTarget = pPassTarget;
                muBallDeflectCount = g_pBall->m_bBallDeflectCount;
                return true;
            }
        }
    }
    return false;
}

/**
 * Offset/Address/Size: 0x631C | 0x80048E18 | size: 0x6C
 */
bool Goalie::IsOpponentInSTS()
{
    cFielder* pFielder = g_pBall->GetOwnerFielder();
    if ((pFielder != NULL) && !IsOnSameTeam(pFielder) && (pFielder->m_eActionState == ACTION_SHOOT_TO_SCORE))
    {
        return true;
    }

    return false;
}

/**
 * Offset/Address/Size: 0x6388 | 0x80048E84 | size: 0x138
 */
bool Goalie::IsOpponentBallCarrierInRange()
{
    return false;
}

/**
 * Offset/Address/Size: 0x64C0 | 0x80048FBC | size: 0xDC
 */
bool Goalie::IsWithinPounceRange()
{
    cFielder* pFielder = g_pBall->GetOwnerFielder();
    if ((pFielder != NULL) && !IsOnSameTeam(pFielder))
    {
        if (pFielder->m_eActionState == ACTION_SHOOT_TO_SCORE)
        {
            return false;
        }

        const float temp_f5 = m_v3Position.f.y - pFielder->m_v3Position.f.y;
        const float temp_f4 = LooseBallAnims::mTrapBallInfo.mfPickupDistance + ((GoalieTweaks*)m_pTweaks)->fPounceRange;
        const float temp_f1 = m_v3Position.f.x - pFielder->m_v3Position.f.x;
        const float temp_f4_2 = temp_f4 * temp_f4;

        if ((temp_f4_2 > ((temp_f1 * temp_f1) + (temp_f5 * temp_f5)))
            || (temp_f4_2 > ((m_v3Position.f.x - g_pBall->m_v3Position.f.x) * (m_v3Position.f.x - g_pBall->m_v3Position.f.x) + (m_v3Position.f.y - g_pBall->m_v3Position.f.y) * (m_v3Position.f.y - g_pBall->m_v3Position.f.y))))
        {
            return true;
        }
    }

    return false;
}

/**
 * Offset/Address/Size: 0x659C | 0x80049098 | size: 0x43C
 */
bool Goalie::IsLooseBallClose(float)
{
    return false;
}

/**
 * Offset/Address/Size: 0x69D8 | 0x800494D4 | size: 0x3A8
 */
bool Goalie::CheckForSTSAttack()
{
    return false;
}

/**
 * Offset/Address/Size: 0x6D80 | 0x8004987C | size: 0x268
 */
bool Goalie::CheckForLooseBallShotInProgress()
{
    return false;
}

/**
 * Offset/Address/Size: 0x6FE8 | 0x80049AE4 | size: 0x268
 */
float Goalie::CheckForDelflectAwayFromNet()
{
    return 0.0f;
}

/**
 * Offset/Address/Size: 0x7250 | 0x80049D4C | size: 0xD8
 */
bool Goalie::IsInsideGoalieBox(const nlVector3& rPos, float fXOffset, float fYOffset)
{
    float x = rPos.f.x;
    if (((float)fabs(x) > (cField::GetPenaltyBoxX(1U) - fXOffset)) && ((x * m_v3Position.f.x) > 0.0f))
    {
        float absPosY = (float)fabs(rPos.f.y);
        if (absPosY < (fYOffset + cField::GetPenaltyBoxY()))
        {
            return true;
        }
    }

    return false;
}

/**
 * Offset/Address/Size: 0x7328 | 0x80049E24 | size: 0xBC
 */
bool Goalie::IsCloseToPlane(const nlVector3& rPos1, const nlVector3& rPos2, float fThreshold)
{
    nlVector3 v3Dir;
    nlVector4 plane;

    nlVector3* pBallPos = &g_pBall->m_v3Position;

    v3Dir.f.x = pBallPos->f.y - rPos1.f.y;
    v3Dir.f.y = rPos1.f.x - pBallPos->f.x;
    v3Dir.f.z = 0.0f;

    MakePerpendicularPlane(*pBallPos, v3Dir, plane, 0.0f);

    float distance = (rPos2.f.x * plane.f.x) + (rPos2.f.y * plane.f.y) + (rPos2.f.z * plane.f.z) - plane.f.w;
    float absDistance = (float)fabsf(distance);

    return absDistance <= fThreshold;
}

/**
 * Offset/Address/Size: 0x73E4 | 0x80049EE0 | size: 0x1D0
 */
void Goalie::InitiatePanicGrab(cPlayer* pPlayer)
{
    if (pPlayer == NULL)
    {
        return;
    }

    if (IsOnSameTeam(pPlayer))
    {
        return;
    }

    cFielder* pFielder = static_cast<cFielder*>(pPlayer);
    if (pFielder->IsFallenDown(0.0f))
    {
        return;
    }

    if (pFielder->IsInvincible())
    {
        return;
    }

    if (pPlayer == NULL)
    {
        return;
    }

    if (pPlayer->m_eClassType != FIELDER)
    {
        return;
    }

    if (pFielder->IsFallenDown(0.0f))
    {
        return;
    }

    pPlayer->PlayRandomCharDialogue(CHAR_DIALOGUE_HIT, VECTORS, 100.0f, -1.0f);

    if (pPlayer->m_pBall != NULL)
    {
        pPlayer->ReleaseBall();
    }

    if (IsOnSameTeam(pFielder))
    {
        pFielder->EndDesire(false);
        pFielder->EndAction();
    }
    else
    {
        pFielder->InitActionSlideAttackReact(this, false);
    }

    if (mpLooseBallInfo != NULL && mpLooseBallInfo->mnAnimID != m_eAnimID)
    {
        SetAnimState(0, true, 0.2f, false, false);

        cPN_SAnimController* pController = m_pCurrentAnimController;
        pController->m_fPrevTime = pController->m_fTime;
        pController->m_fTime = 0.5f * mpLooseBallInfo->mfPickupTime;
        InitMovementFromAnim(0, v3Zero, 1.0f, false);
    }

    if (m_pBall == NULL)
    {
        PickupBall(g_pBall);
        mbPickedUp = true;
        g_pBall->ClearShotInProgress();
        EmitGoalieCatch(this, "goalie_catch", false);
    }
}

/**
 * Offset/Address/Size: 0x75B4 | 0x8004A0B0 | size: 0x494
 */
void Goalie::InitiatePickup()
{
}

/**
 * Offset/Address/Size: 0x7A48 | 0x8004A544 | size: 0x5DC
 */
void Goalie::HandleSTSContact(cBall*)
{
}

/**
 * Offset/Address/Size: 0x8024 | 0x8004AB20 | size: 0x2CC
 */
void Goalie::ShouldReposition()
{
}

/**
 * Offset/Address/Size: 0x82F0 | 0x8004ADEC | size: 0x588
 */
void Goalie::FindDesiredGoaliePosition(nlVector3&, nlVector3&, nlVector3&, unsigned short&, const nlVector3*)
{
}

/**
 * Offset/Address/Size: 0x8878 | 0x8004B374 | size: 0xC70
 */
void Goalie::DoNavigation(float, float, Goalie::eNaviMode)
{
}

/**
 * Offset/Address/Size: 0x94E8 | 0x8004BFE4 | size: 0x94
 */
void Goalie::InitActionPursueRecover()
{
    CleanGoalieAction();

    mPrevGoalieActionState = mGoalieActionState;
    mGoalieActionState = GOALIEACTION_DIVE_RECOVER;
    mnSubstate = 0;

    int animID = 0x8f;
    if (m_pBall == NULL)
    {
        animID = 0x8e;
    }

    SetAnimState(animID, true, 0.2f, false, false);
    InitMovementFromAnim(0, v3Zero, 1.0f, false);

    mbPickedUp = false;
}

/**
 * Offset/Address/Size: 0x957C | 0x8004C078 | size: 0x80
 */
void Goalie::InitActionPursueBallPounce()
{
    CleanGoalieAction();

    mPrevGoalieActionState = mGoalieActionState;
    mGoalieActionState = GOALIEACTION_PURSUE_BALL_POUNCE;
    mnSubstate = 0;

    SetAnimState(mpLooseBallInfo->mnAnimID, true, 0.2f, false, false);
    InitMovementFromAnimSeek(m_pTweaks->fRunningDirectionSeekSpeed, m_pTweaks->fRunningDirectionSeekFalloff);

    mbPickedUp = false;
}

/**
 * Offset/Address/Size: 0x95FC | 0x8004C0F8 | size: 0x88
 */
void Goalie::InitActionPursueBallCarrier()
{
    CleanGoalieAction();

    mPrevGoalieActionState = mGoalieActionState;
    mGoalieActionState = GOALIEACTION_PURSUE_BALL_CARRIER;
    mnSubstate = 0;

    mpLooseBallInfo = &LooseBallAnims::mTrapBallInfo;

    SkillTweaks* pSkillTweaks = SkillTweaks::GetSkillTweaks(g_pCurrentlyUpdatingTeam->m_nSide);
    float random = nlRandomf(1.0f, &nlDefaultSeed);
    mbPlayMiss = (random < pSkillTweaks->fGoalieDekeChance);
}

/**
 * Offset/Address/Size: 0x9684 | 0x8004C180 | size: 0xD0
 */
void Goalie::InitActionPreCrouch(eGoalieCrouchType crouchType)
{
    if (mGoalieActionState == GOALIEACTION_STS || mGoalieActionState == GOALIEACTION_STS_RECOVER)
    {
        return;
    }

    mCrouchType = crouchType;
    CleanGoalieAction();

    mPrevGoalieActionState = mGoalieActionState;
    mGoalieActionState = GOALIEACTION_PRE_CROUCH;
    mnSubstate = 0;

    if (m_eAnimID == 0x2e)
    {
        bool bShouldSetAnim = false;
        if (m_pCurrentAnimController->m_ePlayMode == PM_HOLD && m_pCurrentAnimController->m_fTime == 1.0f)
        {
            bShouldSetAnim = true;
        }
        if (bShouldSetAnim)
        {
            goto check;
        }
    }
    else
    {
    check:
        SetAnimState(0x2e, true, 0.2f, false, false);
    }

    InitMovementFromAnim(0, v3Zero, 0.0f, false);
}

/**
 * Offset/Address/Size: 0x9754 | 0x8004C250 | size: 0x128
 */
void Goalie::InitActionPassInterceptSave()
{
    CleanGoalieAction();

    mPrevGoalieActionState = mGoalieActionState;
    mGoalieActionState = GOALIEACTION_SAVE;
    mnSubstate = 0;

    PlayBlendedAnims(mBlendInfo.mfStartTime, -1);

    u8* pByte = (u8*)m_pPhysicsCharacter + 0x80;
    *pByte |= 0x40; // Set bit 6

    mnOffplayPending = GOALIE_OFFPLAY_NONE;
    mbBallImpacted = false;

    Event* pEvent = g_pEventManager->CreateValidEvent(0x13, 0x38);
    GoalieSaveData* pSaveData = new ((u8*)pEvent + 0x10) GoalieSaveData();

    pSaveData->pGoalie = this;
    pSaveData->v3BallVelocity = v3Zero;
    *((f32*)((u8*)pSaveData + 0x1C)) = 0.0f;

    // Clear bit 7 of byte at offset 0x20
    u8* pByte20 = (u8*)pSaveData + 0x20;
    *pByte20 &= ~0x80;

    *((u32*)((u8*)pSaveData + 0x18)) = g_pBall->m_uGoalType;
    *((cPlayer**)((u8*)pSaveData + 0x14)) = g_pBall->m_pShooter;

    u32* pWord20 = (u32*)((u8*)pSaveData + 0x20);
    if (mpSaveData != NULL)
    {
        *pWord20 = (*pWord20 & 0xFFFFFF00) | (mpSaveData->muSaveType & 0xFF);
    }
    else
    {
        *pWord20 = (*pWord20 & 0xFFFFFF00) | 3;
    }
}

/**
 * Offset/Address/Size: 0x987C | 0x8004C378 | size: 0x174
 */
void Goalie::InitActionPassIntercept()
{
}

/**
 * Offset/Address/Size: 0x99F0 | 0x8004C4EC | size: 0x328
 */
void Goalie::InitActionPass(bool)
{
}

/**
 * Offset/Address/Size: 0x9D18 | 0x8004C814 | size: 0x304
 */
void Goalie::ExecutePounce(cPlayer*, bool)
{
    FORCE_DONT_INLINE;
}

/**
 * Offset/Address/Size: 0xA01C | 0x8004CB18 | size: 0x15C
 */
void Goalie::PreCollideWithBallCallback(const dContact&)
{
}

/**
 * Offset/Address/Size: 0xA178 | 0x8004CC74 | size: 0x6F4
 */
void Goalie::CollideWithCharacterCallback(CollisionPlayerPlayerData*)
{
}

/**
 * Offset/Address/Size: 0xA86C | 0x8004D368 | size: 0xD2C
 */
void Goalie::CollideWithBallCallback(cBall*)
{
}

/**
 * Offset/Address/Size: 0xB598 | 0x8004E094 | size: 0x17C
 */
void Goalie::Update(float)
{
}

/**
 * Offset/Address/Size: 0xB714 | 0x8004E210 | size: 0x6C
 */
Goalie::~Goalie()
{
    GoalieSave::ClearData();
    LooseBallAnims::Destroy();
}

/**
 * Offset/Address/Size: 0xB780 | 0x8004E27C | size: 0x2B8
 */
Goalie::Goalie(eCharacterClass charClass, const int* nModelID, cSHierarchy* pHierarchy, cAnimInventory* pAnimInventory, const CharacterPhysicsData* pPhysicsData, GoalieTweaks* pCharTweaks, AnimRetargetList* pAnimRetargetList)
    : cPlayer(0, charClass, nModelID, pHierarchy, pAnimInventory, pPhysicsData, pCharTweaks, pAnimRetargetList, GOALIE)
{
}
