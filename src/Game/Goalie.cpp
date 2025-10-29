#include "Game/Goalie.h"
#include "Game/AI/GoalieLooseBall.h"
#include "Game/Ball.h"
#include "Game/AI/Fielder.h"
#include "Game/SAnim.h"
#include "types.h"

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
void Goalie::StealBall(cPlayer*)
{
}

/**
 * Offset/Address/Size: 0x304 | 0x80042E00 | size: 0xC0
 */
void Goalie::TacklePlayer(cPlayer*)
{
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
void Goalie::SetDesiredSaveFacing(const nlVector3&)
{
}

/**
 * Offset/Address/Size: 0x93C | 0x80043438 | size: 0x8
 */
void Goalie::GetPhysicsGoalie()
{
}

/**
 * Offset/Address/Size: 0x944 | 0x80043440 | size: 0x50
 */
void Goalie::FindSTSSpinData(bool)
{
}

/**
 * Offset/Address/Size: 0x994 | 0x80043490 | size: 0xF0
 */
void Goalie::FindSTSMissData(const nlVector3&)
{
}

/**
 * Offset/Address/Size: 0xA84 | 0x80043580 | size: 0x4C
 */
void Goalie::FindSTSStunData()
{
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
void Goalie::ChooseSwatAnim(int)
{
}

/**
 * Offset/Address/Size: 0x1810 | 0x8004430C | size: 0xB8
 */
void Goalie::ChooseRunAnim(short, const nlVector3&, float)
{
}

/**
 * Offset/Address/Size: 0x18C8 | 0x800443C4 | size: 0x4AC
 */
void Goalie::CanInterceptPass()
{
}

/**
 * Offset/Address/Size: 0x1D74 | 0x80044870 | size: 0xF4
 */
void Goalie::CalcTimeToPlane()
{
}

/**
 * Offset/Address/Size: 0x1E68 | 0x80044964 | size: 0x138
 */
void Goalie::CalcSaveParameters(float, unsigned int, bool, bool)
{
}

/**
 * Offset/Address/Size: 0x1FA0 | 0x80044A9C | size: 0xE4
 */
void Goalie::CalcBestSave(float, const nlVector3&, const nlVector3&, unsigned int, bool)
{
}

/**
 * Offset/Address/Size: 0x2084 | 0x80044B80 | size: 0xC8
 */
void Goalie::InitActionGrabBall()
{
}

/**
 * Offset/Address/Size: 0x214C | 0x80044C48 | size: 0x100
 */
void Goalie::IsTeammateHoardingBall()
{
}

/**
 * Offset/Address/Size: 0x224C | 0x80044D48 | size: 0xD8
 */
void Goalie::InitActionSTSAttack()
{
}

/**
 * Offset/Address/Size: 0x2324 | 0x80044E20 | size: 0x2DC
 */
void Goalie::InitActionDiveRecover()
{
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
}

/**
 * Offset/Address/Size: 0x29A4 | 0x800454A0 | size: 0x3A8
 */
void Goalie::InitActionSTS()
{
}

/**
 * Offset/Address/Size: 0x2D4C | 0x80045848 | size: 0x250
 */
void Goalie::InitActionSTSSetup()
{
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
}

/**
 * Offset/Address/Size: 0x3AA4 | 0x800465A0 | size: 0x12C
 */
void Goalie::InitActionMove(bool)
{
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
    FORCE_DONT_INLINE;
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
void Goalie::UpdateActionState(float)
{
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
void Goalie::IsPassThreat()
{
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
void Goalie::CheckForSTSAttack()
{
}

/**
 * Offset/Address/Size: 0x6D80 | 0x8004987C | size: 0x268
 */
void Goalie::CheckForLooseBallShotInProgress()
{
}

/**
 * Offset/Address/Size: 0x6FE8 | 0x80049AE4 | size: 0x268
 */
void Goalie::CheckForDelflectAwayFromNet()
{
}

/**
 * Offset/Address/Size: 0x7250 | 0x80049D4C | size: 0xD8
 */
void Goalie::IsInsideGoalieBox(const nlVector3&, float, float)
{
}

/**
 * Offset/Address/Size: 0x7328 | 0x80049E24 | size: 0xBC
 */
void Goalie::IsCloseToPlane(const nlVector3&, const nlVector3&, float)
{
}

/**
 * Offset/Address/Size: 0x73E4 | 0x80049EE0 | size: 0x1D0
 */
void Goalie::InitiatePanicGrab(cPlayer*)
{
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
}

/**
 * Offset/Address/Size: 0x957C | 0x8004C078 | size: 0x80
 */
void Goalie::InitActionPursueBallPounce()
{
}

/**
 * Offset/Address/Size: 0x95FC | 0x8004C0F8 | size: 0x88
 */
void Goalie::InitActionPursueBallCarrier()
{
}

/**
 * Offset/Address/Size: 0x9684 | 0x8004C180 | size: 0xD0
 */
void Goalie::InitActionPreCrouch(eGoalieCrouchType)
{
}

/**
 * Offset/Address/Size: 0x9754 | 0x8004C250 | size: 0x128
 */
void Goalie::InitActionPassInterceptSave()
{
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
