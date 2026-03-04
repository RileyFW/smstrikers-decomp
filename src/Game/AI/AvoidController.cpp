#include "Game/AI/AvoidController.h"

static const nlVector3 v3Zero = { 0.0f, 0.0f, 0.0f };
static const nlVector2 v2Zero = { 0.0f, 0.0f };

/**
 * Offset/Address/Size: 0x22E8 | 0x8000993C | size: 0x98
 */
AvoidController::AvoidController(cFielder* fielder)
{
    m_pFielder = fielder;
    m_pFTweaks = (const FielderTweaks*)fielder->m_pTweaks;
    m_ThingsToAvoid = 0;
    m_CurrentlyAvoiding = 0;
    m_VeryCloseToSideline = false;
    m_UseMinimumAvoidance = false;
    m_pIgnoreThisPlayer = 0;

    m_SidelineNormal.f.x = 0.0f;
    m_SidelineNormal.f.y = 0.0f;
    m_SidelineDirection.f.x = 0.0f;
    m_SidelineDirection.f.y = 0.0f;

    m_LastRepulsionVector[0] = v3Zero;
    m_LastRepulsionVector[1] = v3Zero;
    m_LastRepulsionVector[2] = v3Zero;
    m_LastRepulsionVector[3] = v3Zero;
    m_LastRepulsionVector[4] = v3Zero;
    m_LastRepulsionVector[5] = v3Zero;
}

/**
 * Offset/Address/Size: 0x2250 | 0x800098A4 | size: 0x98
 */
void AvoidController::SetThingsToAvoid(int thingsToAvoid)
{
    m_ThingsToAvoid = thingsToAvoid;
    if (m_ThingsToAvoid != 0)
    {
        return;
    }

    m_CurrentlyAvoiding = 0;
    m_VeryCloseToSideline = false;
    m_SidelineUnavoidable = false;

    m_SidelineNormal = v2Zero;
    m_SidelineDirection = v2Zero;

    m_LastRepulsionVector[0] = v3Zero;
    m_LastRepulsionVector[1] = v3Zero;
    m_LastRepulsionVector[2] = v3Zero;
    m_LastRepulsionVector[3] = v3Zero;
    m_LastRepulsionVector[4] = v3Zero;
    m_LastRepulsionVector[5] = v3Zero;
}

/**
 * Offset/Address/Size: 0x2240 | 0x80009894 | size: 0x10
 */
void AvoidController::UseMinimumAvoidance(cPlayer* player)
{
    m_UseMinimumAvoidance = true;
    m_pIgnoreThisPlayer = player;
}

static int AvoidableEnumToIndex(eAvoidableThings avoidable)
{
    if (avoidable == AVOID_EVERYTHING)
    {
        return 5;
    }
    for (int i = 0; i < NUM_AVOIDABLES; i++)
    {
        if ((1 << i) & (int)avoidable)
        {
            return i;
        }
    }
    return -1;
}

/**
 * Offset/Address/Size: 0x2188 | 0x800097DC | size: 0xB8
 */
nlVector3& AvoidController::GetLastRepulsionVector(eAvoidableThings things)
{
    return m_LastRepulsionVector[AvoidableEnumToIndex(things)];
}
/**
 * Offset/Address/Size: 0x12BC | 0x80008910 | size: 0xECC
 */
void AvoidController::Update(float)
{
}

/**
 * Offset/Address/Size: 0x1060 | 0x800086B4 | size: 0x25C
 */
bool AvoidController::CalcFielderRepulsionVector(nlVector3&)
{
    return false;
}

/**
 * Offset/Address/Size: 0xE08 | 0x8000845C | size: 0x258
 */
bool AvoidController::CalcPowerupRepulsionVector(nlVector3&)
{
    return false;
}

/**
 * Offset/Address/Size: 0xC30 | 0x80008284 | size: 0x1D8
 */
bool AvoidController::CalcDesiredVelocityToAvoidSideline(
    nlVector2& vNewDesiredVelDir,
    const nlVector2& vCurrentDesiredVelDir,
    const nlVector2& vCurrentVelDir,
    const nlVector2& vSidelinePos,
    const nlVector2& vSidelineNormal)
{
    bool bHitSideline = false;

    float fDotNormalVel = vSidelineNormal.f.x * vCurrentDesiredVelDir.f.x + vSidelineNormal.f.y * vCurrentDesiredVelDir.f.y;

    nlVector2* pPos;
    if (m_pFielder->m_pBall != NULL)
    {
        pPos = (nlVector2*)&m_pFielder->m_pBall->m_v3Position;
    }
    else
    {
        pPos = (nlVector2*)&m_pFielder->m_v3Position;
    }

    float dy = pPos->f.y - vSidelinePos.f.y;
    float dx = pPos->f.x - vSidelinePos.f.x;
    float fDistance = nlSqrt(dx * dx + dy * dy, true);

    float fMaxDistance = 5.0f;
    fDistance -= m_pFTweaks->fPhysCapsuleRadius;
    if (m_CurrentlyAvoiding & AVOID_SIDELINES)
    {
        fMaxDistance = 8.0f;
    }

    float fMinDistance = 0.5f;
    m_SidelineUnavoidable = false;
    m_VeryCloseToSideline = false;

    if (fDistance <= fMinDistance)
    {
        m_VeryCloseToSideline = true;
        m_SidelineNormal = vSidelineNormal;
        m_SidelineDirection = vNewDesiredVelDir;
    }

    if (fDistance <= fMaxDistance)
    {
        if (fDotNormalVel <= 0.0f)
        {
            if (fDotNormalVel > -0.9f)
            {
                float fCos, fSin;
                nlSinCos(&fSin, &fCos, 0x4000);

                nlVector2 vParallelVelDir;
                vParallelVelDir.f.x = vSidelineNormal.f.x * fCos - vSidelineNormal.f.y * fSin;
                vParallelVelDir.f.y = vSidelineNormal.f.y * fCos + vSidelineNormal.f.x * fSin;

                if (vParallelVelDir.f.x * vCurrentDesiredVelDir.f.x + vParallelVelDir.f.y * vCurrentDesiredVelDir.f.y < 0.0f)
                {
                    vParallelVelDir.f.y = v3Zero.f.y - vParallelVelDir.f.y;
                    vParallelVelDir.f.x = v3Zero.f.x - vParallelVelDir.f.x;
                }

                vNewDesiredVelDir = vParallelVelDir;
            }
            else
            {
                vNewDesiredVelDir = v2Zero;
                m_SidelineUnavoidable = true;
            }
            bHitSideline = true;
        }
    }

    return bHitSideline;
}

/**
 * Offset/Address/Size: 0x8C8 | 0x80007F1C | size: 0x368
 */
bool AvoidController::CalcDesiredVelocityToAvoidCorner(nlVector2&, const sCornerSegment&, const nlVector2&, const nlVector2&)
{
    return false;
}

/**
 * Offset/Address/Size: 0x41C | 0x80007A70 | size: 0x4AC
 */
void AvoidController::AvoidSidelines()
{
}

/**
 * Offset/Address/Size: 0x0 | 0x80007654 | size: 0x41C
 */
void AvoidController::ApplyRepulsionVector(nlVector3)
{
}
