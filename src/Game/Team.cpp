#include "Game/Team.h"

cTeam* g_pTeams[2] = { NULL, NULL };

/**
 * Offset/Address/Size: 0x1CF0 | 0x8006609C | size: 0x138
 */
cTeam::cTeam(int)
{
}

/**
 * Offset/Address/Size: 0x1C8C | 0x80066038 | size: 0x64
 */
cTeam::~cTeam()
{
    delete m_pNet;
    delete m_pFormationManager;
}

/**
 * Offset/Address/Size: 0x1C1C | 0x80065FC8 | size: 0x70
 */
void cTeam::SetDifficulty(eDifficultyID)
{
}

/**
 * Offset/Address/Size: 0x1C00 | 0x80065FAC | size: 0x1C
 */
void cTeam::ClearAllPowerUps()
{
}

/**
 * Offset/Address/Size: 0x1B94 | 0x80065F40 | size: 0x6C
 */
void cTeam::ClearCurrentPowerUp()
{
}

/**
 * Offset/Address/Size: 0x1A4C | 0x80065DF8 | size: 0x148
 */
void cTeam::TogglePowerup(bool)
{
}

/**
 * Offset/Address/Size: 0x1910 | 0x80065CBC | size: 0x13C
 */
bool cTeam::IncrementPowerupMeter(float)
{
    return false;
}

/**
 * Offset/Address/Size: 0x18D0 | 0x80065C7C | size: 0x40
 */
void cTeam::GetCurrentPowerUp() const
{
}

/**
 * Offset/Address/Size: 0x18BC | 0x80065C68 | size: 0x14
 */
void cTeam::IsCurrentNoPowerup() const
{
}

/**
 * Offset/Address/Size: 0x18A8 | 0x80065C54 | size: 0x14
 */
void cTeam::IsCurrentMushroom() const
{
}

/**
 * Offset/Address/Size: 0x1894 | 0x80065C40 | size: 0x14
 */
void cTeam::IsCurrentStar() const
{
}

/**
 * Offset/Address/Size: 0x183C | 0x80065BE8 | size: 0x58
 */
void cTeam::GetPowerUpByIndex(int) const
{
}

/**
 * Offset/Address/Size: 0x1824 | 0x80065BD0 | size: 0x18
 */
void cTeam::SetIsPowerUpNew(int, bool)
{
}

/**
 * Offset/Address/Size: 0x17D0 | 0x80065B7C | size: 0x54
 */
void cTeam::SetCurrentPowerUp(ePowerUpType, int)
{
}

/**
 * Offset/Address/Size: 0x17B0 | 0x80065B5C | size: 0x20
 */
void cTeam::SetPlayer(cPlayer*, int)
{
}

/**
 * Offset/Address/Size: 0x17A8 | 0x80065B54 | size: 0x8
 */
void cTeam::SetGoalie(Goalie* goalie)
{
    m_pGoalie = goalie;
}

/**
 * Offset/Address/Size: 0x17A0 | 0x80065B4C | size: 0x8
 */
Goalie* cTeam::GetGoalie()
{
    return m_pGoalie;
}

/**
 * Offset/Address/Size: 0x1734 | 0x80065AE0 | size: 0x6C
 */
cPlayer* cTeam::GetControlledPlayer(cGlobalPad*)
{
    return nullptr;
}

/**
 * Offset/Address/Size: 0x16B4 | 0x80065A60 | size: 0x80
 */
void cTeam::GetNumAssignedControllers()
{
}

/**
 * Offset/Address/Size: 0x16A4 | 0x80065A50 | size: 0x10
 */
cFielder* cTeam::GetFielder(int index)
{
    return m_pPlayers[index];
}

/**
 * Offset/Address/Size: 0x1694 | 0x80065A40 | size: 0x10
 */
cPlayer* cTeam::GetPlayer(int index)
{
    return m_pPlayers[index];
}

/**
 * Offset/Address/Size: 0x167C | 0x80065A28 | size: 0x18
 */
cTeam* cTeam::GetOtherTeam()
{
    return g_pTeams[m_nSide == HOME ? AWAY : HOME];
}

/**
 * Offset/Address/Size: 0x1660 | 0x80065A0C | size: 0x1C
 */
cNet* cTeam::GetOtherNet()
{
    return g_pTeams[m_nSide == HOME ? AWAY : HOME]->m_pNet;
}

/**
 * Offset/Address/Size: 0x15F8 | 0x800659A4 | size: 0x68
 */
void cTeam::PreUpdate(float)
{
}

/**
 * Offset/Address/Size: 0x132C | 0x800656D8 | size: 0x2CC
 */
void cTeam::Update(float)
{
}

/**
 * Offset/Address/Size: 0x1100 | 0x800654AC | size: 0x22C
 */
void cTeam::UpdateControllers()
{
}

/**
 * Offset/Address/Size: 0xC98 | 0x80065044 | size: 0x468
 */
void cTeam::ResetCharacters()
{
}

/**
 * Offset/Address/Size: 0xAF4 | 0x80064EA0 | size: 0x1A4
 */
void cTeam::StopGameplayEffectsAndSounds()
{
}

/**
 * Offset/Address/Size: 0xAD0 | 0x80064E7C | size: 0x24
 */
void cTeam::CalculateFormationPosition(nlVector3&, cFielder*, bool, float)
{
}

/**
 * Offset/Address/Size: 0xA68 | 0x80064E14 | size: 0x68
 */
void BestAbleToInterceptBall(const void*, const void*)
{
}

/**
 * Offset/Address/Size: 0x6F0 | 0x80064A9C | size: 0x378
 */
void cTeam::UpdateTeamAI(float)
{
}

/**
 * Offset/Address/Size: 0x598 | 0x80064944 | size: 0x158
 */
void MostOffensiveThreat(const void*, const void*)
{
}

/**
 * Offset/Address/Size: 0x4D0 | 0x8006487C | size: 0xC8
 */
void MostDefensivePlayer(const void*, const void*)
{
}

/**
 * Offset/Address/Size: 0x120 | 0x800644CC | size: 0x3B0
 */
void cTeam::AssignMarks(bool)
{
}

/**
 * Offset/Address/Size: 0x118 | 0x800644C4 | size: 0x8
 */
cFielder* cTeam::GetCaptain()
{
    return m_pPlayers[0];
}

/**
 * Offset/Address/Size: 0x110 | 0x800644BC | size: 0x8
 */
cFielder* cTeam::GetStriker() const
{
    // return m_pStriker;
    return m_pAIOrderedFielders[0];
}

/**
 * Offset/Address/Size: 0x108 | 0x800644B4 | size: 0x8
 */
cFielder* cTeam::GetMidfield() const
{
    return m_pAIOrderedFielders[2];
}

/**
 * Offset/Address/Size: 0x100 | 0x800644AC | size: 0x8
 */
cFielder* cTeam::GetDefence() const
{
    return m_pAIOrderedFielders[3];
}

/**
 * Offset/Address/Size: 0x80 | 0x8006442C | size: 0x80
 */
cFielder* cTeam::GetFrontMostFielder()
{
    cFielder* best = m_pPlayers[0];
    cFielder* p;

    // index 1
    p = m_pPlayers[1];
    if (!best || (p && (p->m_v3AIPosition.f.x < best->m_v3AIPosition.f.x)))
    {
        best = p;
    }

    // index 2
    p = m_pPlayers[2];
    if (!best || (p->m_v3AIPosition.f.x < best->m_v3AIPosition.f.x))
        best = p;

    // index 3
    p = m_pPlayers[3];
    if (!best || (p->m_v3AIPosition.f.x < best->m_v3AIPosition.f.x))
        best = p;

    return best;
}

/**
 * Offset/Address/Size: 0x0 | 0x800643AC | size: 0x80
 */
cFielder* cTeam::GetRearMostFielder()
{
    cFielder* best = m_pPlayers[0];
    cFielder* p;

    // index 1
    p = m_pPlayers[1];
    if (!best || (p && (p->m_v3AIPosition.f.x < best->m_v3AIPosition.f.x)))
    {
        best = p;
    }

    // index 2
    p = m_pPlayers[2];
    if (!best || (p->m_v3AIPosition.f.x < best->m_v3AIPosition.f.x))
        best = p;

    // index 3
    p = m_pPlayers[3];
    if (!best || (p->m_v3AIPosition.f.x < best->m_v3AIPosition.f.x))
        best = p;

    return best;
}
