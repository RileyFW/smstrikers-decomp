#include "Game/AI/FielderActions.h"
#include "Game/Camera/CameraMan.h"
#include "Game/RumbleActions.h"
#include "Game/Sys/eventman.h"
#include "Game/ReplayManager.h"
#include "Game/Drawable/DrawableCharacter.h"
#include "Game/FixedUpdateTask.h"
#include "Game/ParticleUpdateTask.h"
#include "types.h"

// /**
//  * Offset/Address/Size: 0x13C | 0x80030010 | size: 0xD74
//  */
// void FormatImpl<BasicString<char, Detail::TempStringAllocator> >::operator% <const char*>(const char* const&)
// {
// }

// /**
//  * Offset/Address/Size: 0x114 | 0x8002FFE8 | size: 0x28
//  */
// void FormatImpl<BasicString<char, Detail::TempStringAllocator> >::operator BasicString<char, Detail::TempStringAllocator>() const
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8002FED4 | size: 0x114
//  */
// void Format<BasicString<char, Detail::TempStringAllocator>, const char*>(const BasicString<char, Detail::TempStringAllocator>&, const char* const&)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8002FEBC | size: 0x18
//  */
// void nlDLRingGetStart<cBaseCamera>(cBaseCamera*)
// {
// }

// /**
//  * Offset/Address/Size: 0x118 | 0x8002FE7C | size: 0x40
//  */
// void 0x8002FEBC..0x8002FED4 | size : 0x18
// {
// }

// /**
//  * Offset/Address/Size: 0x30 | 0x8002FD94 | size: 0xE8
//  */
// void Detail::LexicalCastImpl<BasicString<char, Detail::TempStringAllocator>, const char*>::Do(const char*)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8002FD64 | size: 0x30
//  */
// void LexicalCast<BasicString<char, Detail::TempStringAllocator>, const char*>(const char* const&)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8002FD5C | size: 0x8
//  */
// void cNet::GetPostRadius()
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8002FD14 | size: 0x48
//  */
// void Function1<void, EmissionController&>::FunctorBase::~FunctorBase()
// {
// }

/**
 * Offset/Address/Size: 0x8654 | 0x8002F18C | size: 0xB88
 */
void cFielder::asmRunning()
{
    FORCE_DONT_INLINE;
}

/**
 * Offset/Address/Size: 0x7F3C | 0x8002EA74 | size: 0x718
 */
void cFielder::asmRunningWB(float)
{
    FORCE_DONT_INLINE;
}

/**
 * Offset/Address/Size: 0x7F18 | 0x8002EA50 | size: 0x24
 */
void cFielder::EndAction()
{
    SetAction(ACTION_NEED_ACTION);
}

/**
 * Offset/Address/Size: 0x7D0C | 0x8002E844 | size: 0x20C
 */
void GetClosestWallPoint(const nlVector3&)
{
}

/**
 * Offset/Address/Size: 0x77D8 | 0x8002E310 | size: 0x534
 */
void cFielder::InitActionDeke(ePadActions)
{
}

/**
 * Offset/Address/Size: 0x74A8 | 0x8002DFE0 | size: 0x330
 */
void cFielder::ActionDeke(float)
{
}

/**
 * Offset/Address/Size: 0x71BC | 0x8002DCF4 | size: 0x2EC
 */
void cFielder::InitActionElectrocution(const nlVector3&, const nlVector3&)
{
}

/**
 * Offset/Address/Size: 0x6F6C | 0x8002DAA4 | size: 0x250
 */
void cFielder::ActionElectrocution(float)
{
}

/**
 * Offset/Address/Size: 0x6AF4 | 0x8002D62C | size: 0x478
 */
void cFielder::InitActionHit(cFielder*)
{
}

/**
 * Offset/Address/Size: 0x6A8C | 0x8002D5C4 | size: 0x68
 */
void cFielder::ActionHit(float)
{
}

/**
 * Offset/Address/Size: 0x66F4 | 0x8002D22C | size: 0x398
 */
void cFielder::InitActionHitReact(cPlayer*, unsigned short, bool)
{
}

/**
 * Offset/Address/Size: 0x6658 | 0x8002D190 | size: 0x9C
 */
void cFielder::ActionHitReact(float)
{
}

/**
 * Offset/Address/Size: 0x653C | 0x8002D074 | size: 0x11C
 */
void cFielder::InitActionIdleTurn(unsigned short)
{
}

/**
 * Offset/Address/Size: 0x64A4 | 0x8002CFDC | size: 0x98
 */
void cFielder::ActionIdleTurn(float)
{
}

/**
 * Offset/Address/Size: 0x61A0 | 0x8002CCD8 | size: 0x304
 */
void cFielder::InitActionLateOneTimerFromVolley()
{
}

/**
 * Offset/Address/Size: 0x615C | 0x8002CC94 | size: 0x44
 */
void cFielder::ActionLateOneTimerFromVolley(float)
{
}

/**
 * Offset/Address/Size: 0x5DF0 | 0x8002C928 | size: 0x36C
 */
void cFielder::DoCommonInitActionLooseBall(const nlVector3&)
{
}

/**
 * Offset/Address/Size: 0x5BEC | 0x8002C724 | size: 0x204
 */
void cFielder::InitActionLooseBallPass(cFielder*, bool)
{
}

/**
 * Offset/Address/Size: 0x5B40 | 0x8002C678 | size: 0xAC
 */
void cFielder::ActionLooseBallPass(float)
{
}

/**
 * Offset/Address/Size: 0x5924 | 0x8002C45C | size: 0x21C
 */
void cFielder::InitActionLooseBallShot(bool)
{
}

/**
 * Offset/Address/Size: 0x58E0 | 0x8002C418 | size: 0x44
 */
void cFielder::ActionLooseBallShot(float)
{
}

/**
 * Offset/Address/Size: 0x57BC | 0x8002C2F4 | size: 0x124
 */
void cFielder::InitActionOneTimer(int, nlVector3&, float, bool)
{
}

/**
 * Offset/Address/Size: 0x5778 | 0x8002C2B0 | size: 0x44
 */
void cFielder::ActionOneTimer(float)
{
}

/**
 * Offset/Address/Size: 0x5518 | 0x8002C050 | size: 0x260
 */
void cFielder::InitActionOneTouchPassFromVolley(cPlayer*)
{
}

/**
 * Offset/Address/Size: 0x54D4 | 0x8002C00C | size: 0x44
 */
void cFielder::ActionOneTouchPassFromVolley(float)
{
}

/**
 * Offset/Address/Size: 0x530C | 0x8002BE44 | size: 0x1C8
 */
bool cFielder::DoCalcCanDoPerfectPass(cFielder*, const nlVector3&)
{
    return false;
}

/**
 * Offset/Address/Size: 0x50A4 | 0x8002BBDC | size: 0x268
 */
void cFielder::InitActionPass(cPlayer*, bool, bool)
{
}

/**
 * Offset/Address/Size: 0x5020 | 0x8002BB58 | size: 0x84
 */
void cFielder::ActionPass(float)
{
}

/**
 * Offset/Address/Size: 0x4F98 | 0x8002BAD0 | size: 0x88
 */
void cFielder::InitActionPostWhistle()
{
}

/**
 * Offset/Address/Size: 0x4F94 | 0x8002BACC | size: 0x4
 */
void cFielder::ActionPostWhistle(float)
{
}

/**
 * Offset/Address/Size: 0x4C38 | 0x8002B770 | size: 0x35C
 */
void cFielder::InitActionBombReact(const nlVector3&, float)
{
}

/**
 * Offset/Address/Size: 0x4968 | 0x8002B4A0 | size: 0x2D0
 */
void cFielder::InitActionBombHitReact(const nlVector3&)
{
}

/**
 * Offset/Address/Size: 0x46D0 | 0x8002B208 | size: 0x298
 */
void cFielder::InitActionBananaReact(const nlVector3&)
{
}

/**
 * Offset/Address/Size: 0x4468 | 0x8002AFA0 | size: 0x268
 */
void cFielder::InitActionShellReact(const nlVector3&, const nlVector3&)
{
}

/**
 * Offset/Address/Size: 0x4400 | 0x8002AF38 | size: 0x68
 */
void cFielder::InitActionRunning()
{
    m_pHeadTrack->m_bTrackOOI = true;

    if (m_eActionState != ACTION_RUNNING)
    {
        mActionRunningVars.eLastStrafeDirection = STRAFE_IDLE;
        m_aActualMovementDirection = m_aActualFacingDirection;
        m_aDesiredFacingDirection = m_aActualFacingDirection;
        m_aDesiredMovementDirection = m_aActualMovementDirection;
        m_fDesiredSpee = m_fActualSpeed;
        mActionRunningVars.bFirstCycleOfTurbo = false;
    }

    SetAction(ACTION_RUNNING);
}

/**
 * Offset/Address/Size: 0x435C | 0x8002AE94 | size: 0xA4
 */
void cFielder::ActionRunning(float dt)
{
    if (m_pBall != nullptr)
    {
        SetAction(ACTION_RUNNING_WB);
        mActionRunningWBVars.bWaitForAnimToFinish = false;
        mActionRunningVars.eLastStrafeDirection = STRAFE_IDLE;
        m_aActualMovementDirection = m_aActualFacingDirection;
    }
    else
    {
        asmRunning();

        if (CanPickupBall(g_pBall))
        {
            PickupBall(g_pBall);
            SetAction(ACTION_RUNNING_WB);
            mActionRunningWBVars.bWaitForAnimToFinish = false;
            mActionRunningVars.eLastStrafeDirection = STRAFE_IDLE;
            m_aActualMovementDirection = m_aActualFacingDirection;
        }
    }
}

/**
 * Offset/Address/Size: 0x430C | 0x8002AE44 | size: 0x50
 */
void cFielder::InitActionRunningWB(bool bWaitForAnimToFinish)
{
    SetAction(ACTION_RUNNING_WB);
    mActionRunningWBVars.bWaitForAnimToFinish = bWaitForAnimToFinish;
    mActionRunningVars.eLastStrafeDirection = STRAFE_IDLE;
    m_aActualMovementDirection = m_aActualFacingDirection; // m_aDesiredMovementDirection
}

/**
 * Offset/Address/Size: 0x42D4 | 0x8002AE0C | size: 0x38
 */
void cFielder::ActionRunningWB(float dt)
{
    if (m_pBall == nullptr)
    {
        SetAction(ACTION_NEED_ACTION);
    }
    else
    {
        asmRunningWB(dt);
    }
}

/**
 * Offset/Address/Size: 0x3F28 | 0x8002AA60 | size: 0x3AC
 */
void cFielder::ActionRunningWBTurbo(float)
{
}

/**
 * Offset/Address/Size: 0x3CA8 | 0x8002A7E0 | size: 0x280
 */
void cFielder::ActionRunningWBTurboTurn(float)
{
}

/**
 * Offset/Address/Size: 0x383C | 0x8002A374 | size: 0x46C
 */
void cFielder::InitActionShot(bool)
{
}

/**
 * Offset/Address/Size: 0x36B8 | 0x8002A1F0 | size: 0x184
 */
void cFielder::ActionShot(float)
{
}

/**
 * Offset/Address/Size: 0x3180 | 0x80029CB8 | size: 0x538
 */
void cFielder::InitActionShootToScore()
{
}

/**
 * Offset/Address/Size: 0x3158 | 0x80029C90 | size: 0x28
 */
void MatrixCamFinishedCallback(MatrixEffectCam*)
{
    const float timeScale = 1.0f;
    FixedUpdateTask::mTimeScale = timeScale;
    ParticleUpdateTask::SetTimeScale(timeScale);
}

/**
 * Offset/Address/Size: 0x2D08 | 0x80029840 | size: 0x450
 */
void cFielder::SetupCaptainSTSAnimCam(bool)
{
}

/**
 * Offset/Address/Size: 0x2D04 | 0x8002983C | size: 0x4
 */
void OtherMatrixCamFinishedCallback(MatrixEffectCam*)
{
    // EMPTY
}

/**
 * Offset/Address/Size: 0x2C4C | 0x80029784 | size: 0xB8
 */
void HyperStrikeEffectUpdate(EmissionController& controller)
{
    if (ReplayManager::Instance()->mRender != nullptr)
    {
        const u32 characterIndex = controller.m_uUserData;
        {
            DrawableCharacter& character = ReplayManager::Instance()->mRender->mCharacters[characterIndex];
            controller.SetPoseAccumulator(*character.mPoseAccumulator);
        }
        {
            DrawableCharacter& character = ReplayManager::Instance()->mRender->mCharacters[characterIndex];
            controller.SetAnimController(character.GetAnimController());
        }
    }

    nlVector3 viewVector;
    viewVector.f.x = cCameraManager::m_matView.f.m31;
    viewVector.f.y = cCameraManager::m_matView.f.m32;
    viewVector.f.z = cCameraManager::m_matView.f.m33;
    cCameraManager::GetViewVector(viewVector);
    controller.SetDirection(viewVector);
}

/**
 * Offset/Address/Size: 0x17D0 | 0x80028308 | size: 0x147C
 */
void cFielder::ActionShootToScore(float)
{
}

/**
 * Offset/Address/Size: 0x13C8 | 0x80027F00 | size: 0x408
 */
void cFielder::InitActionSlideAttack(cFielder*, float)
{
}

/**
 * Offset/Address/Size: 0xE2C | 0x80027964 | size: 0x59C
 */
void cFielder::ActionSlideAttack(float)
{
}

/**
 * Offset/Address/Size: 0xC2C | 0x80027764 | size: 0x200
 */
void cFielder::InitActionSlideAttackFailReact()
{
}

/**
 * Offset/Address/Size: 0xBE8 | 0x80027720 | size: 0x44
 */
void cFielder::ActionSlideAttackFailReact(float)
{
    if (ShouldStartCrossBlend(7))
    {
        SetAction(ACTION_NEED_ACTION);
    }
}

/**
 * Offset/Address/Size: 0x93C | 0x80027474 | size: 0x2AC
 */
void cFielder::InitActionSquishReact(const nlVector3&)
{
}

/**
 * Offset/Address/Size: 0x8A0 | 0x800273D8 | size: 0x9C
 */
void cFielder::DoSlideAttackStats()
{
    const Event* pEvent = g_pEventManager->CreateValidEvent(0x19, 0x28);
    PlayerAttackData* pData = new ((u8*)pEvent + 0x10) PlayerAttackData();

    pData->pAttacker = this;

    bool bHasGlobalPad = GetGlobalPad() != nullptr;
    pData->nAttackerPadID = bHasGlobalPad ? GetGlobalPad()->m_padIndex : -1;

    pData->pTarget = nullptr;
}

/**
 * Offset/Address/Size: 0x5C0 | 0x800270F8 | size: 0x2E0
 */
void cFielder::InitActionSlideAttackReact(cPlayer*, bool)
{
}

/**
 * Offset/Address/Size: 0x3BC | 0x80026EF4 | size: 0x204
 */
void cFielder::InitActionSTSHitReact(cPlayer*)
{
}

/**
 * Offset/Address/Size: 0x378 | 0x80026EB0 | size: 0x44
 */
void cFielder::ActionSlideAttackReact(float)
{
    if (ShouldStartCrossBlend(7))
    {
        SetAction(ACTION_NEED_ACTION);
    }
}

/**
 * Offset/Address/Size: 0x334 | 0x80026E6C | size: 0x44
 */
void cFielder::ActionBombReact(float)
{
    if (ShouldStartCrossBlend(7))
    {
        SetAction(ACTION_NEED_ACTION);
    }
}

/**
 * Offset/Address/Size: 0x2AC | 0x80026DE4 | size: 0x88
 */
void cFielder::ActionSTSHitReact(float)
{
    m_pCurrentAnimController->TestFrameTrigger(3.0f);

    if (m_pCurrentAnimController->TestFrameTrigger(4.0f))
    {
        FireCameraRumbleFilter(0.0f, 0.2f);
        BeginRumbleAction(RUMBLE_SOLID_CONTACT, GetGlobalPad());
    }

    if (ShouldStartCrossBlend(7))
    {
        SetAction(ACTION_NEED_ACTION);
    }
}

/**
 * Offset/Address/Size: 0x268 | 0x80026DA0 | size: 0x44
 */
void cFielder::ActionShellReact(float)
{
    if (ShouldStartCrossBlend(7))
    {
        SetAction(ACTION_NEED_ACTION);
    }
}

/**
 * Offset/Address/Size: 0x224 | 0x80026D5C | size: 0x44
 */
void cFielder::ActionBananaReact(float)
{
    if (ShouldStartCrossBlend(7))
    {
        SetAction(ACTION_NEED_ACTION);
    }
}

/**
 * Offset/Address/Size: 0x1E0 | 0x80026D18 | size: 0x44
 */
void cFielder::ActionSquishReact(float)
{
    if (ShouldStartCrossBlend(7))
    {
        SetAction(ACTION_NEED_ACTION);
    }
}

/**
 * Offset/Address/Size: 0x118 | 0x80026C50 | size: 0xC8
 */
void cFielder::InitActionReceivePass(int animID, nlVector3& v3TargetPos, float fAdjustEndTime)
{
    SetAction(ACTION_RECEIVE_PASS);
    SetAnimState(animID, true, 0.2f, false, false);

    nlVector3 v3Direction;
    nlVec3Set(v3Direction,
        v3TargetPos.f.x - m_v3Position.f.x,
        v3TargetPos.f.y - m_v3Position.f.y,
        v3TargetPos.f.z - m_v3Position.f.z);

    InitMovementFromAnim(0, v3Direction, fAdjustEndTime, false);
    m_aDesiredFacingDirection = m_aActualFacingDirection;
}

/**
 * Offset/Address/Size: 0x68 | 0x80026BA0 | size: 0xB0
 */
void cFielder::ActionReceivePass(float)
{
    if (CanPickupBallFromPass(g_pBall))
    {
        bool bSetPerfectPass = false;
        if (g_pBall->mbHyperSTS)
        {
            if (m_DesireReceivePassSharedVars.iAttemptOneTouchShot != 0)
            {
                if (m_eAnimID != 60)
                {
                    bSetPerfectPass = true;
                }
            }
        }

        PickupBall(g_pBall);

        if (bSetPerfectPass)
        {
            g_pBall->SetPerfectPass(true, true);
        }
    }

    if (ShouldStartCrossBlend(7))
    {
        SetAction(ACTION_NEED_ACTION);
    }
}

/**
 * Offset/Address/Size: 0x4 | 0x80026B3C | size: 0x64
 */
void cFielder::InitActionWait()
{
    SetAction(ACTION_WAIT);
    SetAnimState(0, true, 0.0f, false, false);
    InitMovementNone(0.0f, 0.0f);
    m_aDesiredFacingDirection = m_aActualFacingDirection;
}

/**
 * Offset/Address/Size: 0x0 | 0x80026B38 | size: 0x4
 */
void cFielder::ActionWait(float)
{
    // EMPTY
}
