#include "Game/AI/Scripts/ScriptQuestions.h"
#include "Game/FormationDefines.h"
#include "Game/AI/AiUtil.h"
#include "Game/AI/ShotMeter.h"
#include "Game/Game.h"
#include "Game/GameInfo.h"
#include "Game/Goalie.h"

extern cTeam* g_pCurrentlyUpdatingTeam;
extern cBall* g_pScriptBall;
extern cBall* g_pBall;
extern cFielder* g_pScriptCurrentFielder;
extern nlVector2 g_vStallingConfidenceTime;
extern nlVector2 g_vPassCloseToDoneConfidence;

inline float max_float(float a, float b)
{
    return (a >= b) ? a : b;
}

inline float min_float(float a, float b)
{
    return (a <= b) ? a : b;
}

static inline float IsPassInPlay(cBall* pBall)
{
    if (pBall->m_fTotalPassTime > 0.0f)
    {
        float fElapsedTime = pBall->m_tPassTargetTimer.GetSeconds() / pBall->m_fTotalPassTime;
        return (1.0f - fElapsedTime);
    }
    return 0.0f;
}

/**
 * Offset/Address/Size: 0x5E44 | 0x800848CC | size: 0x30
 */
void CalcSelectChance(float, float)
{
}

/**
 * Offset/Address/Size: 0x5E18 | 0x800848A0 | size: 0x2C
 */
void BallOwner(cPlayer*)
{
}

/**
 * Offset/Address/Size: 0x5DCC | 0x80084854 | size: 0x4C
 */
void BallOwnerT(cTeam*)
{
}

/**
 * Offset/Address/Size: 0x5D9C | 0x80084824 | size: 0x30
 */
void LastBallOwner(cPlayer*)
{
}

/**
 * Offset/Address/Size: 0x5D58 | 0x800847E0 | size: 0x44
 */
void Striker(cFielder*)
{
}

/**
 * Offset/Address/Size: 0x5D14 | 0x8008479C | size: 0x44
 */
void Winger(cFielder*)
{
}

/**
 * Offset/Address/Size: 0x5CD0 | 0x80084758 | size: 0x44
 */
void Midfield(cFielder*)
{
}

/**
 * Offset/Address/Size: 0x5C8C | 0x80084714 | size: 0x44
 */
void Defence(cFielder*)
{
}

/**
 * Offset/Address/Size: 0x5C48 | 0x800846D0 | size: 0x44
 */
void Captain(cFielder*)
{
}

/**
 * Offset/Address/Size: 0x5C1C | 0x800846A4 | size: 0x2C
 */
void GoalieType(cPlayer*)
{
}

/**
 * Offset/Address/Size: 0x5BE0 | 0x80084668 | size: 0x3C
 */
void Marking(cFielder*, cPlayer*)
{
}

/**
 * Offset/Address/Size: 0x5BB0 | 0x80084638 | size: 0x30
 */
void OnTheirTeam(cFielder*)
{
}

/**
 * Offset/Address/Size: 0x5B20 | 0x800845A8 | size: 0x90
 */
void OnScreen(cPlayer*)
{
}

/**
 * Offset/Address/Size: 0x5AD0 | 0x80084558 | size: 0x50
 */
void OnTheGround(cPlayer*)
{
}

/**
 * Offset/Address/Size: 0x59EC | 0x80084474 | size: 0xE4
 */
void StrategicBallOwner(cFielder*)
{
}

/**
 * Offset/Address/Size: 0x59A0 | 0x80084428 | size: 0x4C
 */
float UserControlled(cFielder* pFielder)
{
    if (pFielder == NULL)
    {
        return 0.0f;
    }

    u32 pad = (u32)pFielder->GetGlobalPad();
    // if (pFielder->GetGlobalPad() != NULL)
    if (((-pad | pad) >> 0x1F) != 0) // TODO: matches but is not clean...
    {
        return 1.0f;
    }

    return 0.0f;
}

/**
 * Offset/Address/Size: 0x5838 | 0x800842C0 | size: 0x168
 */
void InPassingLane(cFielder*)
{
}

/**
 * Offset/Address/Size: 0x581C | 0x800842A4 | size: 0x1C
 */
void Aggressive(cFielder*)
{
}

/**
 * Offset/Address/Size: 0x5800 | 0x80084288 | size: 0x1C
 */
void Shooter(cFielder*)
{
}

/**
 * Offset/Address/Size: 0x57E4 | 0x8008426C | size: 0x1C
 */
void Passer(cFielder*)
{
}

/**
 * Offset/Address/Size: 0x57C8 | 0x80084250 | size: 0x1C
 */
void Deker(cFielder*)
{
}

/**
 * Offset/Address/Size: 0x579C | 0x80084224 | size: 0x2C
 */
// void RepeatingLastDesire(cFielder*, eScriptFielderDesire)
// {
// }

/**
 * Offset/Address/Size: 0x54B4 | 0x80083F3C | size: 0x2E8
 */
float AbleToInterceptBall(cPlayer*)
{
    return 0.0f;
}

/**
 * Offset/Address/Size: 0x52B0 | 0x80083D38 | size: 0x204
 */
void AbleToInterceptBallForSwapController(cFielder*)
{
}

/**
 * Offset/Address/Size: 0x5228 | 0x80083CB0 | size: 0x88
 */
void AbleToUsePowerup(cFielder*, int)
{
}

/**
 * Offset/Address/Size: 0x50E8 | 0x80083B70 | size: 0x140
 */
void LikelyToUsePowerup(cFielder*, int)
{
}

/**
 * Offset/Address/Size: 0x5080 | 0x80083B08 | size: 0x68
 */
void CloseToBall(cPlayer*)
{
}

/**
 * Offset/Address/Size: 0x5018 | 0x80083AA0 | size: 0x68
 */
void NearToBall(cPlayer*)
{
}

/**
 * Offset/Address/Size: 0x4FB0 | 0x80083A38 | size: 0x68
 */
void FarToBall(cPlayer*)
{
}

/**
 * Offset/Address/Size: 0x4F34 | 0x800839BC | size: 0x7C
 */
void CloseToMyNet(cPlayer*)
{
}

/**
 * Offset/Address/Size: 0x4EB8 | 0x80083940 | size: 0x7C
 */
void NearToMyNet(cPlayer*)
{
}

/**
 * Offset/Address/Size: 0x4E3C | 0x800838C4 | size: 0x7C
 */
void FarToMyNet(cPlayer*)
{
}

/**
 * Offset/Address/Size: 0x4DC0 | 0x80083848 | size: 0x7C
 */
void CloseToTheirNet(cPlayer*)
{
}

/**
 * Offset/Address/Size: 0x4D44 | 0x800837CC | size: 0x7C
 */
void NearToTheirNet(cPlayer*)
{
}

/**
 * Offset/Address/Size: 0x4CC8 | 0x80083750 | size: 0x7C
 */
void FarToTheirNet(cPlayer*)
{
}

/**
 * Offset/Address/Size: 0x4934 | 0x800833BC | size: 0x394
 */
void Pressured(cFielder*)
{
}

/**
 * Offset/Address/Size: 0x4490 | 0x80082F18 | size: 0x4A4
 */
void Attacked(cFielder*)
{
}

/**
 * Offset/Address/Size: 0x440C | 0x80082E94 | size: 0x84
 */
void AvoidingPowerups(cFielder*)
{
}

/**
 * Offset/Address/Size: 0x43C8 | 0x80082E50 | size: 0x44
 */
void Invincible(cFielder*)
{
}

/**
 * Offset/Address/Size: 0x4294 | 0x80082D1C | size: 0x134
 */
void Incapacitated(cPlayer*)
{
}

/**
 * Offset/Address/Size: 0x4250 | 0x80082CD8 | size: 0x44
 */
void Frozen(cFielder*)
{
}

/**
 * Offset/Address/Size: 0x4208 | 0x80082C90 | size: 0x48
 */
void FallenDown(cFielder*)
{
}

/**
 * Offset/Address/Size: 0x3FA0 | 0x80082A28 | size: 0x268
 */
float LikelyToScoreFromPosition(const nlVector3&, const nlVector3&, const cNet*, bool)
{
    return 0.0f;
}

/**
 * Offset/Address/Size: 0x3F28 | 0x800829B0 | size: 0x78
 */
void PlayerShotDistance(cFielder*)
{
}

/**
 * Offset/Address/Size: 0x3E9C | 0x80082924 | size: 0x8C
 */
void LikelyToScore(cFielder*)
{
}

/**
 * Offset/Address/Size: 0x3D40 | 0x800827C8 | size: 0x15C
 */
void GoalieOutOfPosition(cFielder*)
{
}

/**
 * Offset/Address/Size: 0x3C18 | 0x800826A0 | size: 0x128
 */
float PositionIsInFrontOfNet(const nlVector3&, const cNet*)
{
    return 0.0f;
}

/**
 * Offset/Address/Size: 0x3ACC | 0x80082554 | size: 0x14C
 */
void InFrontOfTheirNet(cFielder*)
{
}

/**
 * Offset/Address/Size: 0x36FC | 0x80082184 | size: 0x3D0
 */
void OnBreakaway(cFielder*)
{
}

/**
 * Offset/Address/Size: 0x32DC | 0x80081D64 | size: 0x420
 */
float OpenToPosition(const nlVector3&, const nlVector3&, const cTeam*, const cPlayer*, const cPlayer*, bool)
{
    return 0.0f;
}

/**
 * Offset/Address/Size: 0x3030 | 0x80081AB8 | size: 0x2AC
 */
float OpenPosition(const nlVector3&, cTeam*, cPlayer*, const nlVector2*)
{
    return 0.0f;
}

/**
 * Offset/Address/Size: 0x2D84 | 0x8008180C | size: 0x2AC
 */
float WideOpenPosition(const nlVector3&, cTeam*, cPlayer*)
{
    return 0.0f;
}

/**
 * Offset/Address/Size: 0x2B10 | 0x80081598 | size: 0x274
 */
void Open(cFielder*)
{
}

/**
 * Offset/Address/Size: 0x2854 | 0x800812DC | size: 0x2BC
 */
void WideOpen(cFielder*)
{
}

/**
 * Offset/Address/Size: 0x27E0 | 0x80081268 | size: 0x74
 */
void OpenToTheirNet(cFielder*)
{
}

/**
 * Offset/Address/Size: 0x2780 | 0x80081208 | size: 0x60
 */
void OpenToMyNet(cFielder*)
{
}

/**
 * Offset/Address/Size: 0x25DC | 0x80081064 | size: 0x1A4
 */
void InBetweenMyNetAnd(cFielder*, cFielder*)
{
}

/**
 * Offset/Address/Size: 0x2438 | 0x80080EC0 | size: 0x1A4
 */
void InBetweenMyNetAnd(cFielder*, cBall*)
{
}

/**
 * Offset/Address/Size: 0x23D8 | 0x80080E60 | size: 0x60
 */
void OpenTo(cPlayer*, cPlayer*)
{
}

/**
 * Offset/Address/Size: 0x2298 | 0x80080D20 | size: 0x140
 */
void CloseTo(cPlayer*, cPlayer*)
{
}

/**
 * Offset/Address/Size: 0x2158 | 0x80080BE0 | size: 0x140
 */
void NearTo(cPlayer*, cPlayer*)
{
}

/**
 * Offset/Address/Size: 0x2018 | 0x80080AA0 | size: 0x140
 */
void FarTo(cPlayer*, cPlayer*)
{
}

/**
 * Offset/Address/Size: 0x1FBC | 0x80080A44 | size: 0x5C
 */
float NearToGoaliePosition(const nlVector3&, const nlVector3&)
{
    return 0.0f;
}

/**
 * Offset/Address/Size: 0x1F50 | 0x800809D8 | size: 0x6C
 */
void CloseToTheirGoalie(cPlayer*)
{
}

/**
 * Offset/Address/Size: 0x1EE4 | 0x8008096C | size: 0x6C
 */
void NearToTheirGoalie(cPlayer*)
{
}

/**
 * Offset/Address/Size: 0x1E78 | 0x80080900 | size: 0x6C
 */
void FarToTheirGoalie(cPlayer*)
{
}

/**
 * Offset/Address/Size: 0x1D08 | 0x80080790 | size: 0x170
 */
float CloseToSideline(const nlVector3&, const nlVector2*, bool)
{
    return 0.0f;
}

/**
 * Offset/Address/Size: 0x1BD4 | 0x8008065C | size: 0x134
 */
float NearToSideline(const nlVector3&)
{
    return 0.0f;
}

/**
 * Offset/Address/Size: 0x1AB8 | 0x80080540 | size: 0x11C
 */
void CloseToSideline(cFielder*)
{
}

/**
 * Offset/Address/Size: 0x1A18 | 0x800804A0 | size: 0xA0
 */
void FacingSideline(cFielder*)
{
}

/**
 * Offset/Address/Size: 0x187C | 0x80080304 | size: 0x19C
 */
void StuckOnSidelines(cFielder*)
{
}

/**
 * Offset/Address/Size: 0x17E8 | 0x80080270 | size: 0x94
 */
void AtIdealDistanceForTackling(cPlayer*, cPlayer*)
{
}

/**
 * Offset/Address/Size: 0x1774 | 0x800801FC | size: 0x74
 */
float PositionIsAtIdealDistanceForShooting(const nlVector3&, const nlVector3&)
{
    return 0.0f;
}

/**
 * Offset/Address/Size: 0x1660 | 0x800800E8 | size: 0x114
 */
void Facing(cPlayer*, cPlayer*)
{
}

/**
 * Offset/Address/Size: 0x15C0 | 0x80080048 | size: 0xA0
 */
void UpfieldFrom(cPlayer*, cPlayer*)
{
}

/**
 * Offset/Address/Size: 0x1520 | 0x8007FFA8 | size: 0xA0
 */
void DownfieldFrom(cPlayer*, cPlayer*)
{
}

/**
 * Offset/Address/Size: 0x14B8 | 0x8007FF40 | size: 0x68
 */
void ClosingTo(cPlayer*, cPlayer*)
{
}

/**
 * Offset/Address/Size: 0x1450 | 0x8007FED8 | size: 0x68
 */
void ClosingTo(cPlayer*, cBall*)
{
}

/**
 * Offset/Address/Size: 0x13E4 | 0x8007FE6C | size: 0x6C
 */
void SeparatingFrom(cPlayer*, cPlayer*)
{
}

/**
 * Offset/Address/Size: 0x1350 | 0x8007FDD8 | size: 0x94
 */
void OutOfNet(Goalie*)
{
}

/**
 * Offset/Address/Size: 0x1324 | 0x8007FDAC | size: 0x2C
 */
float Stunned(Goalie* pGoalie)
{
    if (pGoalie == NULL)
    {
        return 0.0f;
    }

    if (pGoalie->mGoalieActionState == GOALIEACTION_STS_RECOVER)
    {
        return 1.0f;
    }

    return 0.0f;
}

/**
 * Offset/Address/Size: 0x12A8 | 0x8007FD30 | size: 0x7C
 */
float FarToTheirNetB(cBall* pBall)
{
    if (pBall == NULL)
    {
        return 0.0f;
    }

    const nlVector3& netLocation = g_pScriptCurrentFielder->GetAIOffNetLocation(&pBall->m_v3Position);

    float dx = pBall->m_v3Position.f.x - netLocation.f.x;
    float dy = pBall->m_v3Position.f.y - netLocation.f.y;

    return NormalizeVal(nlSqrt(dx * dx + dy * dy, true), g_pGame->m_pFuzzyTweaks->vFarBallNetConfidenceDistance);
}

/**
 * Offset/Address/Size: 0x1220 | 0x8007FCA8 | size: 0x88
 */
float NearToPlayersNet(cBall* pBall, cPlayer* pPlayer)
{
    if (pBall == NULL)
    {
        return 0.0f;
    }

    if (pPlayer == NULL)
    {
        return 0.0f;
    }

    const nlVector3& netLocation = pPlayer->GetAIDefNetLocation(&pBall->m_v3Position);

    float dx = pBall->m_v3Position.f.x - netLocation.f.x;
    float dy = pBall->m_v3Position.f.y - netLocation.f.y;

    return NormalizeVal(nlSqrt(dx * dx + dy * dy, true), g_pGame->m_pFuzzyTweaks->vNearBallNetConfidenceDistance);
}

/**
 * Offset/Address/Size: 0x11A4 | 0x8007FC2C | size: 0x7C
 */
float InControlOfBall(cFielder* pFielder)
{
    if (pFielder == NULL)
    {
        return 0.0f;
    }

    if (pFielder != g_pScriptBall->m_pOwner)
    {
        return 0.0f;
    }

    float dx = g_pScriptBall->m_v3Position.f.x - pFielder->m_v3Position.f.x;
    float dy = g_pScriptBall->m_v3Position.f.y - pFielder->m_v3Position.f.y;
    float distance = nlSqrt(dx * dx + dy * dy, true);

    return NormalizeVal(distance, g_pGame->m_pFuzzyTweaks->vControlConfidenceDistance);
}

static inline bool IsShotMeterActive(eShotMeterState state)
{
    return (state == SHOT_METER_ACTIVE || state == SHOT_METER_STS_ACTIVE || state == SHOT_METER_STS_TRANSISTION);
}

/**
 * Offset/Address/Size: 0x1118 | 0x8007FBA0 | size: 0x8C
 */
float WindingUpForShot(cFielder* pFielder)
{
    if (pFielder == NULL)
    {
        return 0.0f;
    }

    if (IsShotMeterActive(pFielder->m_pShotMeter->m_eShotMeterState) || pFielder->IsPreparingForOneTimer() || pFielder->m_eActionState == ACTION_SHOOT_TO_SCORE)
    {
        return 1.0f;
    }

    return 0.0f;
}

/**
 * Offset/Address/Size: 0x10FC | 0x8007FB84 | size: 0x1C
 */
float OnMushrooms(cFielder* pFielder)
{
    if (pFielder->m_ePowerup == POWER_UP_MUSHROOM)
    {
        return 1.0f;
    }
    return 0.0f;
}

/**
 * Offset/Address/Size: 0xFF4 | 0x8007FA7C | size: 0x108
 */
float ChasingBall(cPlayer* pPlayer)
{
    float fScore;

    if (pPlayer == NULL)
    {
        return 0.0f;
    }

    cFielder* pFielder = (cFielder*)pPlayer;
    fScore = 0.0f;

    if (pPlayer->m_eClassType != GOALIE && pPlayer->m_eClassType == FIELDER)
    {
        eFielderDesireState desireState = pFielder->m_eFielderDesireState;

        if (desireState == FIELDERDESIRE_INTERCEPT_BALL)
        {
            return 1.0f;
        }
        else if (desireState == FIELDERDESIRE_USER_CONTROLLED)
        {
            float fScore_;
            if (pPlayer == NULL)
            {
                fScore_ = 0.0f;
            }
            else
            {
                int index = -1;
                cTeam* pTeam = ((cFielder*)pPlayer)->m_pTeam;
                if (pTeam->m_pBallInterceptOrderedFielders[0] == pPlayer)
                {
                    index = 0;
                }
                else if (pTeam->m_pBallInterceptOrderedFielders[1] == pPlayer)
                {
                    index = 1;
                }
                else if (pTeam->m_pBallInterceptOrderedFielders[2] == pPlayer)
                {
                    index = 2;
                }
                else if (pTeam->m_pBallInterceptOrderedFielders[3] == pPlayer)
                {
                    index = 3;
                }

                fScore_ = (3 - index) / 3.0f;
            }
            fScore = fScore_;
        }
        else if (desireState == FIELDERDESIRE_MARK)
        {
            if (pFielder->m_pMark != NULL && pFielder->m_pMark->m_pBall != NULL)
            {
                fScore = 0.5f;
            }
        }
    }

    return fScore;
}

/**
 * Offset/Address/Size: 0xFBC | 0x8007FA44 | size: 0x38
 */
float ReceivingPass(cFielder* pFielder)
{
    if (pFielder == NULL)
    {
        return 0.0f;
    }

    eFielderDesireState desireState = pFielder->m_eFielderDesireState;
    float fScore = 0.0f;
    if (((s32)desireState == FIELDERDESIRE_RECEIVE_PASS_FROM_IDLE || (desireState == FIELDERDESIRE_RECEIVE_PASS_FROM_RUN) || desireState == FIELDERDESIRE_ONETIMER))
    {
        fScore = 1.0f;
    }

    return fScore;
}

/**
 * Offset/Address/Size: 0xF5C | 0x8007F9E4 | size: 0x60
 */
float ReceivingVolleyPass(cPlayer* pPlayer)
{
    if (pPlayer == NULL)
    {
        return 0.0f;
    }

    float fScore = 0.0f;
    if (pPlayer->m_eClassType == FIELDER)
    {
        if (((cFielder*)pPlayer)->IsReceivingVolleyPass())
        {
            fScore = 1.0f;
        }
    }

    return fScore;
}

/**
 * Offset/Address/Size: 0xE80 | 0x8007F908 | size: 0xDC
 */
float ReceivingPassDelayed(cFielder* pFielder)
{
    if (pFielder == NULL)
    {
        return 0.0f;
    }

    eFielderDesireState desireState = pFielder->m_eFielderDesireState;
    float fScore = 0.0f;
    if (((s32)desireState == FIELDERDESIRE_RECEIVE_PASS_FROM_IDLE || (desireState == FIELDERDESIRE_RECEIVE_PASS_FROM_RUN) || desireState == FIELDERDESIRE_ONETIMER))
    {
        FuzzyTweaks* pFuzzyTweaks = g_pGame->m_pFuzzyTweaks;
        SkillTweaks* pSkillTweaks = SkillTweaks::GetSkillTweaks(g_pCurrentlyUpdatingTeam->m_nSide);

        float fTemp = pFuzzyTweaks->fPassDeadZone * (1.0f - pSkillTweaks->Off_Reaction);
        float fMaxValue = (0.1f >= fTemp) ? 0.1f : fTemp;

        float fProgress = IsPassInPlay(g_pBall);

        fScore = NormalizeVal(fProgress, 0.0f, fMaxValue);
    }
    return fScore;
}

/**
 * Offset/Address/Size: 0xDF8 | 0x8007F880 | size: 0x88
 */
float PassReceiveCloseToDone(cFielder* pFielder)
{
    float fScore;
    if (pFielder == NULL)
    {
        return 0.0f;
    }

    eFielderDesireState desireState = pFielder->m_eFielderDesireState;
    fScore = 0.0f;

    if (((s32)desireState == FIELDERDESIRE_RECEIVE_PASS_FROM_IDLE || (desireState == FIELDERDESIRE_RECEIVE_PASS_FROM_RUN) || desireState == FIELDERDESIRE_ONETIMER))
    {
        float fProgress = IsPassInPlay(g_pBall);
        fScore = NormalizeVal(fProgress, g_vPassCloseToDoneConfidence);
    }
    return fScore;
}

/**
 * Offset/Address/Size: 0xD18 | 0x8007F7A0 | size: 0xE0
 */
float ReceivingVolleyPassDelayed(cPlayer* pPlayer)
{
    if (pPlayer == NULL)
    {
        return 0.0f;
    }

    float fScore = 0.0f;
    if (pPlayer->m_eClassType == FIELDER && ((cFielder*)pPlayer)->IsReceivingVolleyPass())
    {
        FuzzyTweaks* pFuzzyTweaks = g_pGame->m_pFuzzyTweaks;

        float _fScore;

        SkillTweaks* pSkillTweaks = SkillTweaks::GetSkillTweaks(g_pCurrentlyUpdatingTeam->m_nSide);
        float fTemp = pFuzzyTweaks->fPassDeadZone * (1.0f - pSkillTweaks->Off_Reaction);

        _fScore = (0.1f >= fTemp) ? 0.1f : fTemp;

        float fProgress = IsPassInPlay(g_pBall);

        fScore = NormalizeVal(fProgress, 0.0f, _fScore);
    }
    return fScore;
}

/**
 * Offset/Address/Size: 0xCD4 | 0x8007F75C | size: 0x44
 */
float High(cBall* pBall)
{
    if (pBall == NULL)
    {
        return 0.0f;
    }

    return NormalizeVal(g_pScriptBall->m_v3Position.f.z, g_pGame->m_pFuzzyTweaks->vHighBallConfidenceDistance);
}

/**
 * Offset/Address/Size: 0xCA8 | 0x8007F730 | size: 0x2C
 */
float Ownerless(cBall* pBall)
{
    if (pBall == NULL)
    {
        return 0.0f;
    }

    if (pBall->m_pOwner == NULL)
    {
        return 1.0f;
    }

    return 0.0f;
}

/**
 * Offset/Address/Size: 0xC7C | 0x8007F704 | size: 0x2C
 */
float AggressiveT(cTeam* pTeam)
{
    if (pTeam == NULL)
    {
        return 0.0f;
    }

    if (pTeam->meCurrentTeamStyle == TEAM_STYLE_AGGRESSIVE)
    {
        return 1.0f;
    }

    return 0.0f;
}

/**
 * Offset/Address/Size: 0xC50 | 0x8007F6D8 | size: 0x2C
 */
float Moderate(cTeam* pTeam)
{
    if (pTeam == NULL)
    {
        return 0.0f;
    }

    if (pTeam->meCurrentTeamStyle == TEAM_STYLE_MODERATE)
    {
        return 1.0f;
    }

    return 0.0f;
}

/**
 * Offset/Address/Size: 0xC24 | 0x8007F6AC | size: 0x2C
 */
float Passive(cTeam* pTeam)
{
    if (pTeam == NULL)
    {
        return 0.0f;
    }

    if (pTeam->meCurrentTeamStyle == TEAM_STYLE_PASSIVE)
    {
        return 1.0f;
    }

    return 0.0f;
}

// static

/**
 * Offset/Address/Size: 0xBD8 | 0x8007F660 | size: 0x4C
 */
float UserControlledT(cTeam* pTeam)
{
    if (!pTeam)
    {
        return 0.0f;
    }

    s32 numControllers = pTeam->GetNumAssignedControllers();

    if ((((u32)(-numControllers & ~numControllers)) >> 0x1F) != 0) // TODO: matches but is not clean...
    // if ((u32)numControllers != 0)
    {
        return 1.0f;
    }

    return 0.0f;
}

/**
 * Offset/Address/Size: 0x744 | 0x8007F1CC | size: 0x494
 */
void GonnaGetBall(cTeam*)
{
}

/**
 * Offset/Address/Size: 0x6CC | 0x8007F154 | size: 0x78
 */
float Losing(cTeam* pTeam)
{
    if (pTeam == NULL)
    {
        return 0.0f;
    }

    cTeam* pOtherTeam = pTeam->GetOtherTeam();
    int scoreDiff = pTeam->m_nScore - pOtherTeam->m_nScore;

    return NormalizeVal((float)scoreDiff, 0.0f, -g_pGame->m_pFuzzyTweaks->fLosingScoreDelta);
}

/**
 * Offset/Address/Size: 0x64C | 0x8007F0D4 | size: 0x80
 */
float Tied(cTeam* pTeam)
{
    if (pTeam == NULL)
    {
        return 0.0f;
    }

    cTeam* pOtherTeam = pTeam->GetOtherTeam();
    int scoreDiff = pTeam->m_nScore - pOtherTeam->m_nScore;
    int absScoreDiff = (scoreDiff < 0) ? -scoreDiff : scoreDiff;

    return NormalizeVal((float)absScoreDiff, g_pGame->m_pFuzzyTweaks->fTiedScoreDelta, 0.0f);
}

/**
 * Offset/Address/Size: 0x5D8 | 0x8007F060 | size: 0x74
 */
float Winning(cTeam* pTeam)
{
    if (pTeam == NULL)
    {
        return 0.0f;
    }

    cTeam* pOtherTeam = pTeam->GetOtherTeam();
    int scoreDiff = pTeam->m_nScore - pOtherTeam->m_nScore;

    return NormalizeVal((float)scoreDiff, 0.0f, g_pGame->m_pFuzzyTweaks->fWinningScoreDelta);
}

/**
 * Offset/Address/Size: 0x5AC | 0x8007F034 | size: 0x2C
 */
float Offensive(cTeam* pTeam)
{
    if (pTeam == NULL)
    {
        return 0.0f;
    }

    if (pTeam->mpCurrentSituation == SITUATION_OFFENSE)
    {
        return 1.0f;
    }

    return 0.0f;
}

/**
 * Offset/Address/Size: 0x580 | 0x8007F008 | size: 0x2C
 */
float Defensive(cTeam* pTeam)
{
    if (pTeam == NULL)
    {
        return 0.0f;
    }

    if (pTeam->mpCurrentSituation == SITUATION_DEFENSE)
    {
        return 1.0f;
    }

    return 0.0f;
}

/**
 * Offset/Address/Size: 0x554 | 0x8007EFDC | size: 0x2C
 */
float Loose(cTeam* pTeam)
{
    if (pTeam == NULL)
    {
        return 0.0f;
    }

    if (pTeam->mpCurrentSituation == SITUATION_LOOSE)
    {
        return 1.0f;
    }

    return 0.0f;
}

/**
 * Offset/Address/Size: 0x518 | 0x8007EFA0 | size: 0x3C
 */
float Stalling(cTeam* pTeam)
{
    if (pTeam == NULL)
    {
        return 0.0f;
    }

    float seconds = pTeam->mtDefensiveZoneTimer.GetSeconds();
    return NormalizeVal(seconds, g_vStallingConfidenceTime);
}

/**
 * Offset/Address/Size: 0x46C | 0x8007EEF4 | size: 0xAC
 */
float IsPassInPlayDelayed()
{
    float fScore;
    cBall* pBall;
    if (g_pBall->m_pPassTarget == NULL)
    {
        return 0.0f;
    }

    cTeam* pTeam = g_pCurrentlyUpdatingTeam;

    SkillTweaks* pSkillTweaks = SkillTweaks::GetSkillTweaks(g_pCurrentlyUpdatingTeam->m_nSide);

    float fReaction = pSkillTweaks->Off_Reaction;
    float fPassDeadZone = g_pGame->m_pFuzzyTweaks->fPassDeadZone;
    float fMaxValue = fPassDeadZone * (1.0f - fReaction);

    fScore = IsPassInPlay(g_pBall);

    return NormalizeVal(fScore, 0.0f, fMaxValue);
}

/**
 * Offset/Address/Size: 0x3E0 | 0x8007EE68 | size: 0x8C
 */
float IsPerfectPassInPlay()
{
    float fInitialScore;
    if (g_pBall->m_pPassTarget != NULL)
    {
        fInitialScore = 1.0f;
    }
    else
    {
        fInitialScore = 0.0f;
    }

    float fScore = fInitialScore;
    if (fInitialScore > 0.0f)
    {
        if (g_pScriptBall->m_pPrevOwner != NULL && g_pScriptBall->m_pPrevOwner->m_eClassType == FIELDER)
        {
            if (g_pScriptBall->mbHyperSTS == false)
            {
                fScore = 0.0f;
            }
            fScore *= 2.0f;
        }
    }

    float fClampedScore = max_float(fScore, 0.0);
    fClampedScore = min_float(fClampedScore, 1.0);

    return fClampedScore;
}

/**
 * Offset/Address/Size: 0x35C | 0x8007EDE4 | size: 0x84
 */
float PerfectPassCandidateFrom(cFielder* pReceiver, cFielder* pBallOwner)
{
    bool canDoPerfectPass;

    if (pReceiver == NULL)
    {
        return 0.0f;
    }

    if (pBallOwner == NULL)
    {
        return 0.0f;
    }

    canDoPerfectPass = false;
    if ((pBallOwner->m_pBall != 0) && (pBallOwner->DoCalcCanDoPerfectPass(pReceiver, pReceiver->m_v3Position) != 0))
    {
        canDoPerfectPass = true;
    }

    if (canDoPerfectPass)
    {
        return 1.0f;
    }
    return 0.0f;
}

/**
 * Offset/Address/Size: 0x310 | 0x8007ED98 | size: 0x4C
 */
float TimeCloseToOver(cGame* pGame)
{
    if (!pGame)
    {
        return 0.0f;
    }

    FuzzyTweaks* pTweaks = g_pGame->m_pFuzzyTweaks;
    float gameTime = pGame->GetNormalizedGameTime();
    return NormalizeVal(gameTime, pTweaks->fGameTimeCloseToOver, 1.0f);
}

/**
 * Offset/Address/Size: 0x2C4 | 0x8007ED4C | size: 0x4C
 */
float TimeNearlyOver(cGame* pGame)
{
    if (!pGame)
    {
        return 0.0f;
    }

    FuzzyTweaks* pTweaks = g_pGame->m_pFuzzyTweaks;
    float gameTime = pGame->GetNormalizedGameTime();
    return NormalizeVal(gameTime, pTweaks->fGameTimeNearlyOver, 1.0f);
}

/**
 * Offset/Address/Size: 0x278 | 0x8007ED00 | size: 0x4C
 */
float TimeFarFromOver(cGame* pGame)
{
    if (!pGame)
    {
        return 0.0f;
    }

    FuzzyTweaks* pTweaks = g_pGame->m_pFuzzyTweaks;
    float gameTime = pGame->GetNormalizedGameTime();
    return NormalizeVal(gameTime, 1.0f, pTweaks->fGameTimeFarFromOver);
}

inline float max0(const float value)
{
    if (value >= 0.f)
    {
        return value;
    }
    return 0.0f;
}

/**
 * Offset/Address/Size: 0x1E0 | 0x8007EC68 | size: 0x98
 */
float Difficult(cTeam* pTeam)
{
    eDifficultyID diff;
    f32 fScore;

    if (pTeam == NULL)
    {
        return 0.0f;
    }

    diff = nlSingleton<GameInfoManager>::Instance()->mCurrentDifficulty[(s16)pTeam->m_nSide];
    if (diff == DIFF_HUMAN)
    {
        return 0.5f;
    }

    float fMul = 0.25f;
    fScore = max0((float)diff * fMul);
    fScore = (fScore <= 1.0f) ? fScore : 1.0f;
    return fScore;
}

/**
 * Offset/Address/Size: 0x1A0 | 0x8007EC28 | size: 0x40
 */
float InOffensiveZone(const nlVector3& position, eTeamSide teamSide)
{
    nlVector3 aiLoc;
    FieldLocToAILoc(aiLoc, position, teamSide);

    return NormalizeVal(aiLoc.f.x, g_pGame->m_pFuzzyTweaks->vOffensiveConfidenceDistances);
}

/**
 * Offset/Address/Size: 0x13C | 0x8007EBC4 | size: 0x64
 */
float InDefensiveZone(cPlayer* pPlayer)
{
    nlVector3 aiLoc;
    if (pPlayer == NULL)
    {
        return 0.0f;
    }

    eTeamSide teamSide = (eTeamSide)(pPlayer->m_pTeam->m_nSide);
    nlVector3& playerPos = PositionOf(pPlayer);
    FieldLocToAILoc(aiLoc, playerPos, teamSide);

    return NormalizeVal(aiLoc.f.x, g_pGame->m_pFuzzyTweaks->vDefensiveConfidenceDistances);
}

/**
 * Offset/Address/Size: 0xD8 | 0x8007EB60 | size: 0x64
 */
float InOffensiveZone(cPlayer* pPlayer)
{
    nlVector3 aiLoc;
    if (pPlayer == NULL)
    {
        return 0.0f;
    }

    eTeamSide teamSide = (eTeamSide)(pPlayer->m_pTeam->m_nSide);
    nlVector3& playerPos = PositionOf(pPlayer);
    FieldLocToAILoc(aiLoc, playerPos, teamSide);

    return NormalizeVal(aiLoc.f.x, g_pGame->m_pFuzzyTweaks->vOffensiveConfidenceDistances);
}

/**
 * Offset/Address/Size: 0x6C | 0x8007EAF4 | size: 0x6C
 */
float InDefensiveZoneOfPlayer(cBall* pBall, cPlayer* pPlayer)
{
    nlVector3 aiLoc;
    if ((pBall == NULL) && (pPlayer != NULL))
    {
        return 0.0f;
    }

    eTeamSide teamSide = (eTeamSide)(pPlayer->m_pTeam->m_nSide);
    nlVector3& ballPos = PositionOf(pBall);
    FieldLocToAILoc(aiLoc, ballPos, teamSide);

    return NormalizeVal(aiLoc.f.x, g_pGame->m_pFuzzyTweaks->vDefensiveConfidenceDistances);
}

/**
 * Offset/Address/Size: 0x0 | 0x8007EA88 | size: 0x6C
 */
float InOffensiveZoneOfPlayer(cBall* pBall, cPlayer* pPlayer)
{
    nlVector3 aiLoc;
    if ((pBall == NULL) && (pPlayer != NULL))
    {
        return 0.0f;
    }

    eTeamSide teamSide = (eTeamSide)(pPlayer->m_pTeam->m_nSide);
    nlVector3& ballPos = PositionOf(pBall);
    FieldLocToAILoc(aiLoc, ballPos, teamSide);

    return NormalizeVal(aiLoc.f.x, g_pGame->m_pFuzzyTweaks->vOffensiveConfidenceDistances);
}
