#include "Game/AI/SpaceSearch.h"
#include "Game/AI/Fuzzy.h"
#include "Game/AI/Scripts/ScriptQuestions.h"
#include "Game/AI/AiUtil.h"

static nlVector2 g_vRunToNetDistanceConfidence = { 50.0f, 1.5f };      /* const */
static nlVector2 g_vRunToNetFormationDistConfidence = { 10.0f, 1.5f }; /* const */

/**
 * Offset/Address/Size: 0xB0 | 0x800642BC | size: 0xD8
 */
SSearchBestPass::~SSearchBestPass()
{
}

/**
 * Offset/Address/Size: 0x0 | 0x8006420C | size: 0xB0
 */
SSearchRunToNet::~SSearchRunToNet()
{
}

/**
 * Offset/Address/Size: 0x1874 | 0x800641C4 | size: 0x48
 */
SpaceSearch::~SpaceSearch()
{
}

/**
 * Offset/Address/Size: 0x1284 | 0x80063BD4 | size: 0x5F0
 */
void SpaceSearch::FindBestPosition(nlVector3&, const nlVector3&, eFieldDirection, const nlVector3*, float, unsigned short)
{
}

/**
 * Offset/Address/Size: 0x117C | 0x80063ACC | size: 0x108
 */
SSearchOpenLane::SSearchOpenLane(cPlayer* pPlayer1, cPlayer* pPlayer2)
    : SpaceSearch(pPlayer1)
{
}

/**
 * Offset/Address/Size: 0x1060 | 0x800639B0 | size: 0x11C
 */
float SSearchOpenLane::EvaluatePosition(const nlVector3& position, const nlVector3&, eFieldDirection, unsigned short)
{
    float fWeightedSum = 0.0f;
    float fTotalWeight = 0.0f;

    float fOpenToPosition;
    if (m_bOtherPosIsTarget)
    {
        fOpenToPosition = OpenToPosition(position, m_v3OtherPos, NULL, m_pBallOwner, m_pPassTarget, false);
    }
    else
    {
        fOpenToPosition = OpenToPosition(m_v3OtherPos, position, NULL, m_pBallOwner, m_pPassTarget, false);
    }

    fOpenToPosition = 0.0f + NormalizeVal(fOpenToPosition, 0.0f, 0.8f);
    fWeightedSum += fOpenToPosition;
    fTotalWeight += 1.0f;

    if (m_pPassTarget != NULL)
    {
        float fWideOpen = WideOpenPosition(position, m_pPassTarget->m_pTeam->GetOtherTeam(), NULL);
        fWeightedSum += 0.55f * fWideOpen;
        fTotalWeight += 0.55f;
    }

    float fNearToSideline = NearToSideline(position);
    float fAwayFromSideline = 1.0f - fNearToSideline;
    fWeightedSum += 0.2f * fAwayFromSideline;
    fTotalWeight += 0.2f;

    if (fTotalWeight > 0.0f)
    {
        return fWeightedSum / fTotalWeight;
    }
    return 0.0f;
}

/**
 * Offset/Address/Size: 0xF18 | 0x80063868 | size: 0x148
 */
float SSearchIdealShot::EvaluatePosition(const nlVector3& position, const nlVector3&, eFieldDirection, unsigned short)
{
    float fWeightedSum = 0.0f;
    float fTotalWeight = 0.0f;

    float fOpenToPosition = OpenToPosition(position, m_SSearchOpenLane.m_pBallOwner->GetAIOffNetLocation(NULL), NULL, m_SSearchOpenLane.m_pBallOwner, NULL, false);
    fWeightedSum += 0.5f * fOpenToPosition + 0.0f;
    fTotalWeight += 0.5f;

    float fOtherOpenToPosition = OpenPosition(position, m_SSearchOpenLane.m_pBallOwner->m_pTeam->GetOtherTeam(), m_SSearchOpenLane.m_pBallOwner, NULL);
    fWeightedSum += 0.3f * fOtherOpenToPosition;
    fTotalWeight += 0.3f;

    const cNet* pNet = m_pGoalie->m_pTeam->m_pNet;

    float fLikelyToScore = LikelyToScoreFromPosition(position, m_pGoalie->m_v3Position, pNet, false);
    fWeightedSum += 1.5f * fLikelyToScore;
    fTotalWeight += 1.5f;

    float fInFrontOfNet = PositionIsInFrontOfNet(position, pNet);
    fWeightedSum += 0.5f * fInFrontOfNet;
    fTotalWeight += 0.5f;

    float fNearToGoalie = NearToGoaliePosition(position, m_pGoalie->m_v3Position);
    fWeightedSum += 1.0f - fNearToGoalie;
    fTotalWeight += 1.0f;

    if (fTotalWeight > 0.0f)
    {
        return fWeightedSum / fTotalWeight;
    }
    return 0.0f;
}

/**
 * Offset/Address/Size: 0xCEC | 0x8006363C | size: 0x22C
 */
SSearchBestPass::SSearchBestPass(cPlayer* pPlayer1, cPlayer* pPlayer2, bool, bool)
    : SpaceSearch(pPlayer1)
    , m_SSearchIdealShot(pPlayer2 ? pPlayer2->m_pTeam->GetOtherTeam()->GetGoalie() : NULL)
    , m_SSearchOpenLane(pPlayer2, NULL)
{
}

/**
 * Offset/Address/Size: 0xA10 | 0x80063360 | size: 0x2DC
 */
void CalcIdealShootingPositionScore(const nlVector3&, const nlVector3&, const nlVector2&, float)
{
}

/**
 * Offset/Address/Size: 0x594 | 0x80062EE4 | size: 0x47C
 */
float SSearchBestPass::EvaluatePosition(const nlVector3&, const nlVector3&, eFieldDirection, unsigned short)
{
    return 0.0f;
}

/**
 * Offset/Address/Size: 0x538 | 0x80062E88 | size: 0x5C
 */
SSearchOpenLane::~SSearchOpenLane()
{
}

/**
 * Offset/Address/Size: 0x4B0 | 0x80062E00 | size: 0x88
 */
SSearchIdealShot::~SSearchIdealShot()
{
}

/**
 * Offset/Address/Size: 0x380 | 0x80062CD0 | size: 0x130
 */
SSearchRunToNet::SSearchRunToNet(cPlayer* pPlayer)
    : SpaceSearch(pPlayer)
    , m_SSearchIdealShot(pPlayer ? pPlayer->m_pTeam->GetOtherTeam()->GetGoalie() : NULL)
{
}

/**
 * Offset/Address/Size: 0x194 | 0x80062AE4 | size: 0x1EC
 */
float SSearchRunToNet::EvaluatePosition(const nlVector3&, const nlVector3&, eFieldDirection, unsigned short)
{
    return 0.0f;
}

/**
 * Offset/Address/Size: 0x158 | 0x80062AA8 | size: 0x3C
 */
SSearchCutAndBreak::SSearchCutAndBreak(cPlayer* pPlayer)
    : SpaceSearch(pPlayer)
{
    m_pPlayer = pPlayer;
}

/**
 * Offset/Address/Size: 0x5C | 0x800629AC | size: 0xFC
 */
float SSearchCutAndBreak::EvaluatePosition(const nlVector3& v3TestPosition, const nlVector3&, eFieldDirection, unsigned short)
{
    float fWeightedSum = 0.0f;
    float fTotalWeight = 0.0f;

    float fInFrontOfNet = PositionIsInFrontOfNet(v3TestPosition, m_pPlayer->m_pTeam->GetOtherTeam()->m_pNet);
    fWeightedSum += 0.5f * FGREATER(fInFrontOfNet, 0.5f) + 0.0f;
    fTotalWeight += 0.5f;

    float fWideOpen = WideOpenPosition(v3TestPosition, m_pPlayer->m_pTeam->GetOtherTeam(), m_pPlayer);
    fWeightedSum += 0.4f * fWideOpen;
    fTotalWeight += 0.4f;

    float fIdealDistance = PositionIsAtIdealDistanceForShooting(v3TestPosition, m_pPlayer->GetAIOffNetLocation(NULL));
    fWeightedSum += 0.3f * fIdealDistance;
    fTotalWeight += 0.3f;

    if (fTotalWeight > 0.0f)
    {
        return fWeightedSum / fTotalWeight;
    }
    return 0.0f;
}

/**
 * Offset/Address/Size: 0x0 | 0x80062950 | size: 0x5C
 */
SSearchCutAndBreak::~SSearchCutAndBreak()
{
}
