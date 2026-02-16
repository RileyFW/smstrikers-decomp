#include "Game/Player.h"
#include "Game/Character.h"
#include "Game/Ball.h"
#include "Game/AnimInventory.h"
#include "Game/Net.h"

#include "Game/AI/Fielder.h"
#include "Game/AI/SpaceSearch.h"
#include "Game/AI/AiUtil.h"

#include "Game/CharacterTemplate.h"
#include "Game/SAnim/pnFeather.h"
#include "Game/SAnim/pnSingleAxisBlender.h"
#include "NL/nlString.h"

#include "Game/DB/StatsTracker.h"
#include "Game/Effects/EffectsGroup.h"
#include "Game/CharacterTriggers.h"
#include "Game/Game.h"

float g_fPassInterceptNoPickupTimer = 5.0f;

extern int g_nHeadSpinMax;
extern int g_nHeadTiltMax;
extern int g_nWarioHeadSpinMax;
extern int g_nWarioHeadTiltMax;
extern int g_nWaluigiHeadSpinMax;
extern float g_fFixedUpdateTick;
extern u16 g_aOOIConstraint;

/**
 * Offset/Address/Size: 0x0 | 0x80057550 | size: 0x20
 */
s32 cPlayer::GetUniqueID(int nTeamID) const
{
    if (nTeamID == -1)
    {
        nTeamID = *(s32*)m_pTeam;
    }
    nTeamID *= 5;
    return nTeamID + m_ID;
}

/**
 * Offset/Address/Size: 0x20 | 0x80057570 | size: 0x48
 */
void cPlayer::SetNoPickUpTime(float NewNoPickUpTime)
{
    m_pPhysicsCharacter->m_CanCollideWithBall = (NewNoPickUpTime <= 0.0f);
    m_tNoPickupTimer.SetSeconds(NewNoPickUpTime);
}

inline float max_float(float a, float b)
{
    return (a >= b) ? a : b;
}

inline float min_float(float a, float b)
{
    return (a <= b) ? a : b;
}

/**
 * Offset/Address/Size: 0x68 | 0x800575B8 | size: 0xAC
 */
nlVector3 cPlayer::GetAIDefNetLocation(const nlVector3* v3ReferencePos)
{
    nlVector3 result = m_pTeam->m_pNet->m_baseLocation;

    float yCoord;
    if (v3ReferencePos != NULL)
    {
        yCoord = v3ReferencePos->f.y;
    }
    else
    {
        yCoord = m_v3Position.f.y;
    }

    float halfNetWidth = 0.5f * cNet::m_fNetWidth;

    if (yCoord < 0.0f)
    {
        yCoord = max_float(yCoord, -1.0f * halfNetWidth);
        result.f.y = yCoord;
    }
    else
    {
        yCoord = min_float(yCoord, halfNetWidth);
    }

    result.f.y = yCoord;
    return result;
}

/**
 * Offset/Address/Size: 0x114 | 0x80057664 | size: 0xE0
 * TODO: 95.9% match - MWCC ternary register allocation: fmr f0,f3 instead of fmr f3,f0.
 * Compiler always uses f0 as ternary result dest when yCoord is in f3.
 * Tried 20+ variations: swapped args (97.3% but fcmpo order wrong), if/else (adds mfcr/rlwinm),
 * static inline helpers, const qualifiers, different variable ordering - all produce same fmr direction.
 * Same issue affects GetAIDefNetLocation. Likely inherent MWCC graph-coloring register allocator decision.
 */
nlVector3 cPlayer::GetAIOffNetLocation(const nlVector3* v3ReferencePos)
{
    nlVector3 v3NetLocation = m_pTeam->GetOtherNet()->m_baseLocation;

    float yCoord;
    if (v3ReferencePos != NULL)
    {
        yCoord = v3ReferencePos->f.y;
    }
    else
    {
        yCoord = m_v3Position.f.y;
    }

    float fNetWidth = 0.5f * cNet::m_fNetWidth;

    if (yCoord < 0.0f)
    {
        float negHalf = -1.0f * fNetWidth;
        yCoord = max_float(yCoord, negHalf);
        v3NetLocation.f.y = yCoord;
    }
    else
    {
        yCoord = min_float(yCoord, fNetWidth);
        v3NetLocation.f.y = yCoord;
    }

    return v3NetLocation;
}

/**
 * Offset/Address/Size: 0x1F4 | 0x80057744 | size: 0x90
 */
bool cPlayer::CanPickupBallFromPass(cBall* pBall)
{
    bool result = false;
    if (pBall->m_pOwner == NULL)
    {
        int jointIdx = m_nBallJointIndex;
        result = TestCollision(0.18f, GetPrevJointPosition(jointIdx), GetJointPosition(jointIdx), 0.18f, pBall->m_v3PrevPosition, pBall->m_v3Position);
    }
    return result;
}

/**
 * Offset/Address/Size: 0x284 | 0x800577D4 | size: 0x1B0
 */
bool cPlayer::CanPickupBall(cBall* pBall)
{
    return false;
}

/**
 * Offset/Address/Size: 0x434 | 0x80057984 | size: 0x20
 */
void cPlayer::PostPhysicsUpdate()
{
    cCharacter::PostPhysicsUpdate();
}

/**
 * Offset/Address/Size: 0x454 | 0x800579A4 | size: 0x34
 */
void cPlayer::PreUpdate(float dt)
{
    cCharacter::PreUpdate(dt);
    m_bCanTestController = true;
}

/**
 * Offset/Address/Size: 0x488 | 0x800579D8 | size: 0x148
 */
void cPlayer::PrePhysicsUpdate(float)
{
}

/**
 * Offset/Address/Size: 0x5D0 | 0x80057B20 | size: 0x148
 */
void cPlayer::PlayerHeadTrackCallback(unsigned int nSelf, unsigned int, cPoseAccumulator* pPoseAccumulator, unsigned int nJointIndex, int)
{
    cPlayer& self = *(cPlayer*)(void*)nSelf;
    nlMatrix4 m4HeadMatrix;

    nlMultMatrices(m4HeadMatrix, pPoseAccumulator->GetNodeMatrix(nJointIndex), self.m_m4WorldMatrix);

    int nHeadSpinMax = g_nHeadSpinMax;
    int nHeadTiltMax = g_nHeadTiltMax;
    eCharacterClass cc = self.m_eCharacterClass;

    if (cc == WARIO)
    {
        nHeadSpinMax = g_nWarioHeadSpinMax;
        nHeadTiltMax = g_nWarioHeadTiltMax;
    }
    else if (cc == WALUIGI)
    {
        nHeadSpinMax = g_nWaluigiHeadSpinMax;
    }

    eClassTypes classType = self.m_eClassType;
    float fSmoothTime;
    if (classType == GOALIE)
    {
        fSmoothTime = 0.1f;
    }
    else
    {
        fSmoothTime = 0.1f;
    }

    if (classType == GOALIE)
    {
        self.m_pHeadTrack->Update(m4HeadMatrix, m4HeadMatrix, g_fFixedUpdateTick, g_aOOIConstraint, nHeadSpinMax, nHeadTiltMax, fSmoothTime);

        cHeadTrack* pHeadTrack = self.m_pHeadTrack;
        u16 headSpin = (u16)(int)pHeadTrack->m_fHeadSpin;
        u16 headTilt = (u16)(int)pHeadTrack->m_fHeadTilt;
        CalcHeadTrackMatrix(headSpin, headTilt, pPoseAccumulator, nJointIndex);
    }
    else
    {
        nlMatrix4 m4ConstraintMatrix;
        nlMultMatrices(m4ConstraintMatrix, pPoseAccumulator->GetNodeMatrix(self.m_nSpine1JointIndex), self.m_m4WorldMatrix);

        self.m_pHeadTrack->Update(m4HeadMatrix, m4HeadMatrix, g_fFixedUpdateTick, g_aOOIConstraint, nHeadSpinMax, nHeadTiltMax, fSmoothTime);
    }
}

/**
 * Offset/Address/Size: 0x718 | 0x80057C68 | size: 0x140
 */
cPN_SingleAxisBlender* cPlayer::CreateSingleAxisBlender(const int* pSABAnims, int nNumSABAnims, int nPrimaryAnim, void (*fWeightCB)(unsigned int, cPN_SingleAxisBlender*), float fWeightSeek, cPN_SAnimController* pSynchingController)
{
    cPN_SAnimController* pNewCurrentAnimController;
    pNewCurrentAnimController = NULL;

    cPN_SingleAxisBlender* pSAB = new (AllocateSingleAxisBlender()) cPN_SingleAxisBlender(nNumSABAnims, fWeightCB, (unsigned int)this, fWeightSeek);

    const int* pAnims = pSABAnims;
    for (int i = 0; i < nNumSABAnims; i++)
    {
        cPN_SAnimController* pNewController = NewAnimController(*pAnims, false, false, NULL, 0);
        if (pSynchingController != NULL)
        {
            pNewController->m_bIsSynchronized = true;
            pSynchingController->m_pSynchronizedController = pNewController;
            pSynchingController = pNewController;
        }
        pSAB->SetChild(i, pNewController);
        if (i == nPrimaryAnim)
        {
            pNewCurrentAnimController = pNewController;
        }
        pAnims++;
    }

    SetAnimID(pSABAnims[nPrimaryAnim]);
    m_pCurrentAnimController = pNewCurrentAnimController;

    return pSAB;
}

/**
 * Offset/Address/Size: 0x858 | 0x80057DA8 | size: 0x38
 */
void cPlayer::CollideWithWallCallback(const CollisionPlayerWallData*)
{
    if (this != g_pBall->m_pOwner)
    {
        return;
    }

    if (m_eBallRotationMode != BRM_ANIMATED)
    {
        return;
    }

    m_eBallRotationMode = BRM_MATCH_VELOCITY;

    if (m_pBall != NULL)
    {
        m_ResetBaseBallOrientation = true;
    }
}

/**
 * Offset/Address/Size: 0x890 | 0x80057DE0 | size: 0xE8
 */
void cPlayer::SetPowerupAnimState(int animID)
{
    s32 nodeIndex;
    cPN_SAnimController* pController = NewAnimController(animID, false, false, nullptr, 0);
    if (animID == 0x5F || animID == 0x61)
    {
        cSHierarchy* pHierarchy = m_pPoseAccumulator->m_BaseSHierarchy;
        nodeIndex = pHierarchy->GetNodeIndexByID(nlStringLowerHash("bip01 l clavicle"));
    }
    else
    {
        cSHierarchy* pHierarchy = m_pPoseAccumulator->m_BaseSHierarchy;
        nodeIndex = pHierarchy->GetNodeIndexByID(nlStringLowerHash("bip01 r clavicle"));
    }

    m_pPowerupLayer->ClearNodeWeights();
    m_pPowerupLayer->SetNodeWeight(nodeIndex, 1.0f, 0.2f);
    m_pPowerupLayer->SetChild(1, pController);
    m_pPowerupLayer->BeginBlendIn(0.067f);
}

/**
 * Offset/Address/Size: 0x978 | 0x80057EC8 | size: 0x18
 */
void cPlayer::ClearSwapControllerTimer()
{
    m_tSwapControllerTimer[0].m_uPackedTime = 0;
    m_tSwapControllerTimer[1].m_uPackedTime = 0;
    m_tSwapControllerTimer[2].m_uPackedTime = 0;
    m_tSwapControllerTimer[3].m_uPackedTime = 0;
}

/**
 * Offset/Address/Size: 0x990 | 0x80057EE0 | size: 0x80
 */
void cPlayer::ClearPowerupAnimState(bool bIsEndGame)
{
    bool bRemovePowerup = false;
    if ((bIsEndGame != 0) && (m_pPowerupLayer->GetChild(1) != 0))
    {
        bRemovePowerup = 1;
    }

    m_pPowerupLayer->BeginBlendOut(0.1f);
    if (m_eClassType == FIELDER)
    {
        cFielder* pFielder = (cFielder*)this;
        pFielder->m_nPowerupAnimID = -1;
        if (bRemovePowerup != 0)
        {
            pFielder->m_ePowerup = POWER_UP_NONE;
        }
    }
}

/**
 * Offset/Address/Size: 0xA10 | 0x80057F60 | size: 0xBCC
 */
void cPlayer::DoRegularPassing(cPlayer*, bool, bool, bool, bool)
{
}

/**
 * Offset/Address/Size: 0x15DC | 0x80058B2C | size: 0x34
 */
void cPlayer::ResetUnPossessionTimer()
{
    if (m_pBall == NULL)
    {
        m_tBallUnPossessionTimer.SetSeconds(0.0f);
    }
}

/**
 * Offset/Address/Size: 0x1610 | 0x80058B60 | size: 0xD4
 */
void cPlayer::ReleaseBall()
{
    m_pPhysicsCharacter->ReleaseObject();
    m_pBall->ClearOwner();
    m_pBall = NULL;

    float fPossessionTime = m_tBallPossessionTimer.GetSeconds();
    StatsTracker::Instance()->TrackStat(STATS_POSSESION_TIME, m_pTeam->m_nSide, m_ID, 100.0f * fPossessionTime, 0, 0, 0);

    if (IsPlayingEffect(fxGetGroup("ball_sts_windup")))
    {
        StopSFX(Audio::CHARSFX_SHOT_WINDUP);
        StopSFX(Audio::CHARSFX_EFFORTS_HEAD_SHAKE);
    }

    KillWindups(this);
    StopSFX(Audio::CHARSFX_KICK_ATTEMPT);
    m_pCharacterSFX->StopMovementLoop();
}

/**
 * Offset/Address/Size: 0x16E4 | 0x80058C34 | size: 0x1C
 */
cGlobalPad* cPlayer::GetGlobalPad()
{
    if (m_pController != NULL)
    {
        return m_pController->m_pPad;
    }
    return NULL;
}

/**
 * Offset/Address/Size: 0x1700 | 0x80058C50 | size: 0x230
 */
cPlayer* cPlayer::DoFindBestPassTarget(bool bIsVolleyPass, bool bIsPassingFromVolley)
{
    return nullptr;
}

/**
 * Offset/Address/Size: 0x1930 | 0x80058E80 | size: 0x24
 */
bool cPlayer::IsCaptain() const
{
    return ::IsCaptain(m_eCharacterClass);
}

/**
 * Offset/Address/Size: 0x1954 | 0x80058EA4 | size: 0x28
 */
bool cPlayer::IsOnSameTeam(cPlayer* other)
{
    if ((other != NULL) && (other->m_pTeam == m_pTeam))
    {
        return true;
    }
    return false;
}

/**
 * Offset/Address/Size: 0x197C | 0x80058ECC | size: 0x4A4
 */
void cPlayer::SetAIPad(cAIPad*)
{
}

/**
 * Offset/Address/Size: 0x1E20 | 0x80059370 | size: 0x18C
 */
void cPlayer::PlayAttackReactionSounds(float)
{
}

/**
 * Offset/Address/Size: 0x1FAC | 0x800594FC | size: 0x2EC
 */
void cPlayer::PickupBall(cBall*)
{
}

/**
 * Offset/Address/Size: 0x2298 | 0x800597E8 | size: 0x138
 */
void cPlayer::GetClosestOpponentFielder(nlVector3*)
{
}

/**
 * Offset/Address/Size: 0x23D0 | 0x80059920 | size: 0x4
 */
void cPlayer::CollideWithCharacterCallback(CollisionPlayerPlayerData*)
{
    // EMPTY
}

/**
 * Offset/Address/Size: 0x23D4 | 0x80059924 | size: 0x64
 */
void cPlayer::CollideWithBallCallback(cBall* pBall)
{
    if (pBall->m_pPassTarget != NULL)
    {
        if (pBall->m_pPassTarget != this)
        {
            m_tNoPickupPassInterceptTimer.SetSeconds(g_fPassInterceptNoPickupTimer);
        }
    }

    if (pBall->m_pOwner == NULL)
    {
        pBall->m_pLastTouch = this;
    }
}

/**
 * Offset/Address/Size: 0x2438 | 0x80059988 | size: 0x134
 */
float cPlayer::DoFlashLight(const nlVector3&, unsigned short, float, float, float)
{
    return 0.0f;
}

/**
 * Offset/Address/Size: 0x256C | 0x80059ABC | size: 0x134
 */
float cPlayer::DoFlashLight(const nlVector3& Position1, const nlVector3& Position2, unsigned short aDirection, float fAngleWeighting, float fIgnoreObjectCloserThanThis, float fIgnoreObjectFartherThanThis)
{
    float dx;
    float dy = Position2.f.y - Position1.f.y;
    dx = Position2.f.x - Position1.f.x;
    float fDistBetween;
    float dist = nlSqrt(dx * dx + dy * dy, true);
    fDistBetween = dist;
    if (dist < fIgnoreObjectCloserThanThis || dist > fIgnoreObjectFartherThanThis)
    {
        fDistBetween = 0.0f;
    }

    u16 targetAngle = (u16)(s32)(10430.378f * nlATan2f(dy, dx));
    float fDistWeight = 1.0f - fAngleWeighting;
    s16 angleDiff = aDirection - targetAngle;
    u16 absAngle = (angleDiff < 0) ? -angleDiff : angleDiff;

    return fDistBetween * fDistWeight + fAngleWeighting * absAngle;
}

/**
 * Offset/Address/Size: 0x26A0 | 0x80059BF0 | size: 0x5C
 */
void cPlayer::SetAnimID(int animID)
{
    cCharacter::SetAnimID(animID);
    m_eBallRotationMode = (eBallRotationMode)m_pAnimInventory->GetBallRotationMode(animID);
    if (m_pBall != nullptr)
    {
        m_ResetBaseBallOrientation = true;
    }
}

/**
 * Offset/Address/Size: 0x26FC | 0x80059C4C | size: 0x190
 */
void cPlayer::GetAnimatedBallOrientation(nlQuaternion&)
{
}

/**
 * Offset/Address/Size: 0x288C | 0x80059DDC | size: 0x1C4
 */
void cPlayer::Update(float)
{
}

/**
 * Offset/Address/Size: 0x2A50 | 0x80059FA0 | size: 0x27C
 */
void cPlayer::SwapController()
{
}

/**
 * Offset/Address/Size: 0x2CCC | 0x8005A21C | size: 0x114
 */
void cPlayer::SetDesiredFacingDirection()
{
    if (m_pController != NULL)
    {
        if (m_pController->GetMovementStickMagnitude() > 0.1f)
        {
            if (m_tSwapFacingTimer.m_uPackedTime != 0)
            {
                GameTweaks* pGameTweaks = g_pGame->m_pGameTweaks;
                f32 t = m_tSwapFacingTimer.GetSeconds() / pGameTweaks->fSwapFacingTime;
                u16 aStickDirection = m_pController->GetMovementStickDirection();
                s16 diff = m_aSwapFacingDirection - aStickDirection;
                m_aDesiredFacingDirection = (u16)((f32)aStickDirection + (f32)diff * t);
            }
            else
            {
                m_aDesiredFacingDirection = m_pController->GetMovementStickDirection();
            }
        }
        else
        {
            m_aDesiredFacingDirection = m_aActualFacingDirection;
        }
    }

    if (m_eAnimID >= 0x5C || m_eAnimID < 0x56)
    {
        m_aDesiredMovementDirection = m_aDesiredFacingDirection;
    }
}

/**
 * Offset/Address/Size: 0x2DE0 | 0x8005A330 | size: 0x10
 */
void cPlayer::ResetDesiredDirections(unsigned short direction)
{
    m_aDesiredFacingDirection = direction;
    m_aDesiredMovementDirection = m_aDesiredFacingDirection;
}

/**
 * Offset/Address/Size: 0x2DF0 | 0x8005A340 | size: 0x5C
 */
void cPlayer::SetSpaceSearch(SpaceSearch* pSpaceSearch)
{
    if (m_pSpaceSearch != NULL)
    {
        delete m_pSpaceSearch;
    }
    m_pSpaceSearch = pSpaceSearch;
}

/**
 * Offset/Address/Size: 0x2E4C | 0x8005A39C | size: 0x160
 */
cPlayer::~cPlayer()
{
}

/**
 * Offset/Address/Size: 0x2FAC | 0x8005A4FC | size: 0x380
 */
cPlayer::cPlayer(int arg0, eCharacterClass characterClass, const int* arg2, cSHierarchy* hierarchy, cAnimInventory* animInventory, const CharacterPhysicsData* physData, PlayerTweaks* playerTweaks, AnimRetargetList* animRetargetList, eClassTypes classType)
    : cCharacter(characterClass, arg2, hierarchy, animInventory, physData, playerTweaks->fPhysCapsuleHeight, playerTweaks->fPhysCapsuleRadius, animRetargetList, classType)
{
}
