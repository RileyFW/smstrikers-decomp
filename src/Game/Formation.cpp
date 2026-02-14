#include "Game/Formation.h"

#include "Game/MathHelpers.h"
#include "Game/AI/AiUtil.h"
#include "Game/AI/Fielder.h"
#include "Game/AI/FuzzyVariant.h"
#include "Game/AI/Scripts/FormationScript.h"
#include "Game/Game.h"
#include "Game/Team.h"
#include "Game/FormationDefines.h"
#include "Game/Sys/debug.h"
#include "NL/nlMath.h"

extern cTeam* g_pTeams[];

static nlVector3 v3Zero = { 0.0f, 0.0f, 0.0f };

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
    do
    {
        FormationEval* p = pp[1];
        delete p;
        i++;
        *++pp = null;
    } while (i < 3);
}

/**
 * Offset/Address/Size: 0x281C | 0x8003AA6C | size: 0x158
 * TODO: 96.3% match - register allocation differs in nested loops
 */
void FormationManager::LoadFormationSets()
{
    int numFormationSets = 0;
    FormationSet* pFormationSets = FormationSet::LoadFormationSets("FormationSets.ini", numFormationSets);

    if (numFormationSets == 0)
    {
        if (m_FormationSetArray != nullptr)
        {
            tDebugPrintManager::Print(DC_AI, "Reload of FormationSets.ini failed, but we\'ve got some loaded already.");
        }
        return;
    }

    if (g_pGame != nullptr)
    {
        if (g_pTeams[0] != nullptr && g_pTeams[1] != nullptr)
        {
            for (s32 i = 0; i < 2; i++)
            {
                FormationEval** pp = (FormationEval**)g_pTeams[i]->m_pFormationManager;
                for (s32 j = 0; j < 3; j++)
                {
                    FormationEval* pEval = pp[1];
                    delete pEval;
                    *++pp = nullptr;
                }
            }
        }
    }

    delete[] m_FormationSetArray;
    m_FormationSetArray = pFormationSets;
    m_NumFormationSets = numFormationSets;

    if (g_pGame != nullptr)
    {
        if (g_pTeams[0] != nullptr && g_pTeams[1] != nullptr)
        {
            for (s32 i = 0; i < 2; i++)
            {
                g_pTeams[i]->m_pFormationManager->ChooseNewFormations();
            }
        }
    }
}

/**
 * Offset/Address/Size: 0x275C | 0x8003A9AC | size: 0xC0
 * TODO: 98.96% match - r28/r30 register swap in nested loop
 */
void FormationManager::UnloadFormationSets()
{
    FormationEval** pp;
    s32 j;
    s32 i;

    if (g_pGame != nullptr)
    {
        if (g_pTeams[0] != nullptr && g_pTeams[1] != nullptr)
        {
            for (i = 0; i < 2; i++)
            {
                pp = (FormationEval**)g_pTeams[i]->m_pFormationManager;
                for (j = 0; j < 3; j++)
                {
                    FormationEval* pEval = pp[1];
                    delete pEval;
                    *++pp = nullptr;
                }
            }
        }
    }

    delete[] m_FormationSetArray;
    m_FormationSetArray = nullptr;
    m_NumFormationSets = 0;
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
void FormationManager::SetNewFormationEval(eFormationType formType, eFormation formation)
{
    FORCE_DONT_INLINE;
    FormationEval* pFormation;

    if (formation == FORMATION_NONE)
    {
        pFormation = m_pFormations[formType];
        delete pFormation;
        m_pFormations[formType] = nullptr;
    }
    else
    {
        pFormation = m_pFormations[formType];
        if (pFormation != nullptr)
        {
            if ((s32)formation == pFormation->m_pFormationSpec->m_ID)
            {
                return;
            }
        }
        delete pFormation;
        m_pFormations[formType] = FormationEval::Create(this, formType, FSET_NONE, formation);
    }
}

/**
 * Offset/Address/Size: 0x2300 | 0x8003A550 | size: 0xDC
 */
void FormationManager::SetNewFormationEval(eFormationType formType, eFormationSet formSet)
{
    FORCE_DONT_INLINE;
    FormationEval* pFormation;

    if (formSet == FSET_NONE)
    {
        pFormation = m_pFormations[formType];
        delete pFormation;
        m_pFormations[formType] = nullptr;
    }
    else
    {
        pFormation = m_pFormations[formType];
        if (pFormation != nullptr)
        {
            FormationSet* pFormationSet = *(FormationSet**)((u8*)pFormation + 0x28);
            if ((s32)formSet == pFormationSet->m_ID)
            {
                return;
            }
        }
        delete pFormation;
        m_pFormations[formType] = FormationEval::Create(this, formType, formSet, FORMATION_NONE);
    }
}

/**
 * Offset/Address/Size: 0x202C | 0x8003A27C | size: 0x2D4
 * TODO: 92.1% match - register allocation off by 1 (r19-r28 vs r20-r29)
 */
bool FormationManager::CalculateFielderPosition(nlVector3& v3DestPosition, cFielder* pFielder, bool bInPosition, float fBallPosFormationWeight)
{
    int id = pFielder->m_ID;
    int offset = id << 4;
    CachedPosition* cached = (CachedPosition*)((u8*)&m_CachedPositions[0] + offset);

    // Check if we have a cached position
    if (cached->bCacheIsValid)
    {
        v3DestPosition = cached->vPosition;
        return cached->bInPosition;
    }

    // Initialize local variables
    float fWeights[3];
    nlVector3 v3FormationPosition[2][3];
    nlVector3 v3FutureDesiredPosition = v3Zero;
    float fFielderInPosition = 0.0f;

    // First loop: get weights and positions from each formation
    for (int i = 0; i < 3; i++)
    {
        FormationEval* pFormation = m_pFormations[i];
        if (pFormation != nullptr && pFormation->m_pFormationSpec != nullptr)
        {
            fWeights[i] = pFormation->GetWeight();
            pFormation->CalculateDesiredLocation(v3FormationPosition[1][i], pFielder, true);
            pFormation->CalculateDesiredLocation(v3FormationPosition[0][i], pFielder, false);
        }
        else
        {
            v3FormationPosition[0][i] = v3Zero;
            v3FormationPosition[1][i] = v3Zero;
            fWeights[i] = 0.0f;
        }
    }

    // Ensure ball position weight doesn't go below 0
    if (fWeights[2] < 0.0f)
    {
        fWeights[2] = 1.0f;
    }

    // Scale weights by fBallPosFormationWeight
    float scaledBallWeight = fWeights[2] * fBallPosFormationWeight;
    float remainingWeight = 1.0f - scaledBallWeight;
    fWeights[2] = scaledBallWeight;
    fWeights[0] *= remainingWeight;
    fWeights[1] *= remainingWeight;

    // Second loop: calculate final position
    for (int i = 0; i < 3; i++)
    {
        FormationEval* pFormation = m_pFormations[i];
        if (pFormation != nullptr && pFormation->m_pFormationSpec != nullptr)
        {
            nlVector3 pos = v3FormationPosition[0][i];
            v3FutureDesiredPosition.f.x += fWeights[i] * v3FormationPosition[1][i].f.x;
            v3FutureDesiredPosition.f.y += fWeights[i] * v3FormationPosition[1][i].f.y;
            v3FutureDesiredPosition.f.z += fWeights[i] * v3FormationPosition[1][i].f.z;
            float result = pFormation->IsFielderInPosition(pFielder, pos, bInPosition);
            fFielderInPosition += fWeights[i] * result;
        }
    }

    v3DestPosition = v3FutureDesiredPosition;
    bool inPos = fFielderInPosition >= 0.5f;

    // Cache the result
    cached->vPosition = v3DestPosition;
    cached->bInPosition = inPos;
    cached->bCacheIsValid = true;

    return inPos;
}

/**
 * Offset/Address/Size: 0x1E00 | 0x8003A050 | size: 0x22C
 */
FormationEval* FormationEval::Create(FormationManager*, eFormationType, eFormationSet, eFormation)
{
    FORCE_DONT_INLINE;
    return nullptr;
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
float FormationEval::GetWeight()
{
    if (m_pFormationSpec != NULL)
    {
        return 1.0f;
    }
    return 0.0f;
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
 * TODO: 98.78% match - float register allocation: X clamp uses f4/f5/f6 shifted by +1
 * (target: f5=minX, f6=clampX, f4=maxX; actual: f4=minX, f5=clampX, f6=maxX).
 * Y clamp uses f0/f3 swapped (target: f0=minY, f3=clampY; actual: f3=minY, f0=clampY).
 * All 16 diffs are register-only (r markers).
 */
void FormationEval::CalculateDesiredLocation(nlVector3& destPosition, cFielder* pFielder, bool bExtrapolate)
{
    nlVector3 v3KeyAIPosition;
    nlVector3 v3KeyFormationAIPosition;
    nlVector2 v2FormationMin;
    nlVector2 v2FormationMax;

    GetKeyPositions(pFielder, v3KeyAIPosition, &v3KeyFormationAIPosition, bExtrapolate);

    m_pFormationSpec->CalculateExtents(v2FormationMin, v2FormationMax, *(nlVector2*)&v3KeyFormationAIPosition);

    u32 posIndex = m_iFielderFormationPos[pFielder->m_ID];
    const FormationSpec* pSpec = m_pFormationSpec;

    f32 maxX = v2FormationMax.f.x;
    f32 minX = v2FormationMin.f.x;

    const FormationPos* pPos = &pSpec->m_Positions[posIndex];

    f32 locY = v3KeyFormationAIPosition.f.y;
    f32 locX = v3KeyFormationAIPosition.f.x;

    f32 posLocY = pPos->m_Location.f.y;
    f32 posLocX = pPos->m_Location.f.x;

    f32 dy = posLocY - locY;
    f32 dx = posLocX - locX;

    f32 clampX = v3KeyAIPosition.f.x;
    clampX = (clampX >= minX) ? clampX : minX;
    clampX = (clampX <= maxX) ? clampX : maxX;

    destPosition.f.x = dx + clampX;

    f32 maxY = v2FormationMax.f.y;
    f32 clampY = v3KeyAIPosition.f.y;
    f32 minY = v2FormationMin.f.y;

    clampY = (clampY >= minY) ? clampY : minY;
    clampY = (clampY <= maxY) ? clampY : maxY;

    destPosition.f.y = dy + clampY;
    f32 zero = 0.0f;
    destPosition.f.z = zero;

    if (pFielder->m_pTeam->m_nSide != 0)
    {
        nlVec3Set(destPosition, -destPosition.f.x, -destPosition.f.y, zero);
    }
}

/**
 * Offset/Address/Size: 0x1150 | 0x800393A0 | size: 0x1E0
 */
float FormationEval::IsFielderInPosition(cFielder*, nlVector3, bool)
{
    return 0.0f;
}

/**
 * Offset/Address/Size: 0xE70 | 0x800390C0 | size: 0x2E0
 */
float FormationDefensive::IsFielderInPosition(cFielder*, nlVector3, bool)
{
    return 0.0f;
}

/**
 * Offset/Address/Size: 0xE40 | 0x80039090 | size: 0x30
 */
float FormationDefensive::GetWeight()
{
    return NormalizeVal(m_pFormationManager->m_v2AIFielderCenter.f.x, 25.0f, -25.0f);
}

/**
 * Offset/Address/Size: 0xB60 | 0x80038DB0 | size: 0x2E0
 */
float FormationOffensive::IsFielderInPosition(cFielder*, nlVector3, bool)
{
    return 0.0f;
}

/**
 * Offset/Address/Size: 0xB30 | 0x80038D80 | size: 0x30
 */
float FormationOffensive::GetWeight()
{
    return NormalizeVal(m_pFormationManager->m_v2AIFielderCenter.f.x, -25.0f, 25.0f);
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
float FormationBallPosition::GetWeight()
{
    return 0.0f;
}
