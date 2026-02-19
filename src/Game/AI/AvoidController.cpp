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

/**
 * Offset/Address/Size: 0x2188 | 0x800097DC | size: 0xB8
 */
nlVector3& AvoidController::GetLastRepulsionVector(eAvoidableThings things)
{
    int index;

    if (things == AVOID_EVERYTHING) // 0x1F
    {
        index = 5;
    }
    else if ((AVOID_FIELDERS)&things) // 0x01
    {
        index = 0;
    }
    else if (AVOID_GOALIES & things) // 0x02
    {
        index = 1;
    }
    else if (AVOID_POWERUPS & things) // 0x04
    {
        index = 2;
    }
    else if (AVOID_SIDELINES & things) // 0x08
    {
        index = 3;
    }
    else if (AVOID_BOWSER & things) // 0x10
    {
        index = 4;
    }
    else if (0x20 & things) // bit 5 - also maps to index 5
    {
        index = 5;
    }
    else
    {
        index = -1;
    }

    return m_LastRepulsionVector[index];
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
bool AvoidController::CalcDesiredVelocityToAvoidSideline(nlVector2&, const nlVector2&, const nlVector2&, const nlVector2&, const nlVector2&)
{
    return false;
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
