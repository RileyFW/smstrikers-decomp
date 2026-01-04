#include "Game/Formation.h"

#include "Game/AI/Fielder.h"
#include "Game/AI/FuzzyVariant.h"
#include "Game/AI/Scripts/FormationScript.h"
#include "Game/Game.h"
#include "Game/Team.h"
#include "Game/FormationDefines.h"
#include "NL/nlMath.h"

FormationSet* FormationManager::m_FormationSetArray = nullptr;
int FormationManager::m_NumFormationSets = 0;

/**
 * Offset/Address/Size: 0x5C | 0x8003ADB4 | size: 0x5C
 */
FormationDefensive::~FormationDefensive()
{
}

/**
 * Offset/Address/Size: 0x0 | 0x8003AD58 | size: 0x5C
 */
FormationOffensive::~FormationOffensive()
{
}

// /**
//  * Offset/Address/Size: 0x0 | 0x8003ACEC | size: 0x6C
//  */
// FormationSet::~FormationSet()
// {
// }

/**
 * Offset/Address/Size: 0x0 | 0x8003ACA4 | size: 0x48
 */
FormationEval::~FormationEval()
{
}

/**
 * Offset/Address/Size: 0x29F4 | 0x8003AC44 | size: 0x60
 */
FormationManager::FormationManager(cTeam* pTeam)
{
    m_pTeam = pTeam;
    m_tSelectFormationsTimer.SetSeconds(0.0f);
    m_pFormations[0] = nullptr;
    m_pFormations[1] = nullptr;
    m_pFormations[2] = nullptr;
    m_CachedPositions[0].bCacheIsValid = false;
    m_CachedPositions[1].bCacheIsValid = false;
    m_CachedPositions[2].bCacheIsValid = false;
    m_CachedPositions[3].bCacheIsValid = false;
    m_tSelectFormationsTimer.m_uPackedTime = 0;
}

/**
 * Offset/Address/Size: 0x2974 | 0x8003ABC4 | size: 0x80
 */
FormationManager::~FormationManager()
{
    s32 i = 0;
    FormationEval** pp = (FormationEval**)this;
    FormationEval* null = (FormationEval*)i;
    do {
        FormationEval* p = pp[1];
        delete p;
        i++;
        *++pp = null;
    } while (i < 3);
}

/**
 * Offset/Address/Size: 0x281C | 0x8003AA6C | size: 0x158
 */
void FormationManager::LoadFormationSets()
{
}

/**
 * Offset/Address/Size: 0x275C | 0x8003A9AC | size: 0xC0
 */
void FormationManager::UnloadFormationSets()
{
}

/**
 * Offset/Address/Size: 0x26E4 | 0x8003A934 | size: 0x78
 */
FormationSpec* FormationManager::GetFormationSpec(eFormation formation)
{
    FORCE_DONT_INLINE;
    FormationSpec* result = nullptr;
    int offset = 0;
    eFormation id = (eFormation)(int)this;
    int i = 0;

    while (i < m_NumFormationSets)
    {
        result = m_FormationSetArray[i].GetFormationSpecFromID(id);
        if (result != nullptr)
        {
            break;
        }
        offset += 0x10;
        i++;
    }

    return result;
}

/**
 * Offset/Address/Size: 0x2558 | 0x8003A7A8 | size: 0x18C
 */
void FormationManager::Update(float dt)
{
    if (!g_pGame->IsGameplayOrOvertime())
    {
        return;
    }

    m_tSelectFormationsTimer.Countdown(dt, 0.0f);

    if (m_tSelectFormationsTimer.m_uPackedTime == 0)
    {
        ChooseNewFormations();
        float randomTime = nlRandomf(0.2f, &nlDefaultSeed);
        m_tSelectFormationsTimer.SetSeconds(10.0f + randomTime);
    }

    m_v2AIFielderCenter.f.x = 0.0f;
    m_v2AIFielderCenter.f.y = 0.0f;

    for (int i = 0; i < 4; i++)
    {
        cFielder* pFielder = m_pTeam->GetFielder(i);
        float newX = m_v2AIFielderCenter.f.x + pFielder->m_v3Position.f.x;
        float newY = m_v2AIFielderCenter.f.y + pFielder->m_v3Position.f.y;
        m_v2AIFielderCenter.f.x = newX;
        m_v2AIFielderCenter.f.y = newY;
    }

    float cx = m_v2AIFielderCenter.f.x * 0.25f;
    float cy = m_v2AIFielderCenter.f.y * 0.25f;
    m_v2AIFielderCenter.f.x = cx;
    m_v2AIFielderCenter.f.y = cy;

    if (m_pTeam->m_nSide == AWAY)
    {
        m_v2AIFielderCenter.f.x = -m_v2AIFielderCenter.f.x;
        m_v2AIFielderCenter.f.y = -m_v2AIFielderCenter.f.y;
    }

    for (int i = 0; i < 3; i++)
    {
        if (m_pFormations[i] != nullptr)
        {
            m_pFormations[i]->Update(dt);
        }
    }

    m_CachedPositions[0].bCacheIsValid = false;
    m_CachedPositions[1].bCacheIsValid = false;
    m_CachedPositions[2].bCacheIsValid = false;
    m_CachedPositions[3].bCacheIsValid = false;
}

/**
 * Offset/Address/Size: 0x24B8 | 0x8003A708 | size: 0xA0
 */
void FormationManager::ChooseNewFormations()
{
    FORCE_DONT_INLINE;
    s32 defensiveFormation;
    s32 offensiveFormation;
    s32 ballFormationSet;

    defensiveFormation = Fuzzy::GetBestDefensiveFormation(m_pTeam).mData.i;
    offensiveFormation = Fuzzy::GetBestOffensiveFormation(m_pTeam).mData.i;
    ballFormationSet = Fuzzy::GetBestBallFormationSet(m_pTeam).mData.i;

    SetNewFormationEval(FTYPE_DEFENSIVE, (eFormation)defensiveFormation);
    SetNewFormationEval(FTYPE_OFFENSIVE, (eFormation)offensiveFormation);
    SetNewFormationEval(FTYPE_BALLPOSITION, (eFormationSet)ballFormationSet);
}

/**
 * Offset/Address/Size: 0x23DC | 0x8003A62C | size: 0xDC
 */
void FormationManager::SetNewFormationEval(eFormationType, eFormation)
{
    FORCE_DONT_INLINE;
}

/**
 * Offset/Address/Size: 0x2300 | 0x8003A550 | size: 0xDC
 */
void FormationManager::SetNewFormationEval(eFormationType, eFormationSet)
{
    FORCE_DONT_INLINE;
}

/**
 * Offset/Address/Size: 0x202C | 0x8003A27C | size: 0x2D4
 */
void FormationManager::CalculateFielderPosition(nlVector3&, cFielder*, bool, float)
{
}

/**
 * Offset/Address/Size: 0x1E00 | 0x8003A050 | size: 0x22C
 */
void FormationEval::Create(FormationManager*, eFormationType, eFormationSet, eFormation)
{
}

/**
 * Offset/Address/Size: 0x1D40 | 0x80039F90 | size: 0xC0
 */
void FormationEval::Update(float)
{
}

/**
 * Offset/Address/Size: 0x1D24 | 0x80039F74 | size: 0x1C
 */
void FormationEval::GetWeight()
{
}

/**
 * Offset/Address/Size: 0x1A14 | 0x80039C64 | size: 0x310
 */
void FormationEval::AssignPositionsToFielders(unsigned int*, float (*)[4])
{
}

/**
 * Offset/Address/Size: 0x1798 | 0x800399E8 | size: 0x27C
 */
void FormationEval::SortPlayers(const nlVector2*)
{
}

/**
 * Offset/Address/Size: 0x1630 | 0x80039880 | size: 0x168
 */
void FormationEval::GetKeyPlayer()
{
}

/**
 * Offset/Address/Size: 0x1488 | 0x800396D8 | size: 0x1A8
 */
void FormationEval::GetKeyPositions(cFielder*, nlVector3&, nlVector3*, bool)
{
}

/**
 * Offset/Address/Size: 0x1330 | 0x80039580 | size: 0x158
 */
void FormationEval::CalculateDesiredLocation(nlVector3&, cFielder*, bool)
{
}

/**
 * Offset/Address/Size: 0x1150 | 0x800393A0 | size: 0x1E0
 */
void FormationEval::IsFielderInPosition(cFielder*, nlVector3, bool)
{
}

/**
 * Offset/Address/Size: 0xE70 | 0x800390C0 | size: 0x2E0
 */
void FormationDefensive::IsFielderInPosition(cFielder*, nlVector3, bool)
{
}

/**
 * Offset/Address/Size: 0xE40 | 0x80039090 | size: 0x30
 */
void FormationDefensive::GetWeight()
{
}

/**
 * Offset/Address/Size: 0xB60 | 0x80038DB0 | size: 0x2E0
 */
void FormationOffensive::IsFielderInPosition(cFielder*, nlVector3, bool)
{
}

/**
 * Offset/Address/Size: 0xB30 | 0x80038D80 | size: 0x30
 */
void FormationOffensive::GetWeight()
{
}

/**
 * Offset/Address/Size: 0xA98 | 0x80038CE8 | size: 0x98
 */
FormationBallPosition::~FormationBallPosition()
{
}

/**
 * Offset/Address/Size: 0x930 | 0x80038B80 | size: 0x168
 */
void FormationBallPosition::Update(float)
{
}

/**
 * Offset/Address/Size: 0x618 | 0x80038868 | size: 0x318
 */
void FormationBallPosition::SelectClosestBallFormations(const nlVector2&)
{
}

/**
 * Offset/Address/Size: 0x2C0 | 0x80038510 | size: 0x358
 */
void FormationBallPosition::CalculateDesiredLocation(nlVector3&, cFielder*, bool)
{
}

/**
 * Offset/Address/Size: 0x0 | 0x80038250 | size: 0x2C0
 */
void FormationBallPosition::GetWeight()
{
}
