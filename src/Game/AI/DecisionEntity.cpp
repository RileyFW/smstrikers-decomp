#include "Game/AI/DecisionEntity.h"

#include "Game/AI/ScriptAction.h"
#include "Game/AI/Scripts/RootScript.h"
#include "Game/AI/Scripts/ScriptDefines.h"

cFielder* g_pScriptCurrentFielder = NULL;
cDecisionEntity g_pDecisionEntities[44] = {
    cDecisionEntity(DECISION_ENTITY_STRATEGY, 0, NULL, NULL),
    cDecisionEntity(DECISION_ENTITY_PLAY, 0, NULL, NULL),
    cDecisionEntity(DECISION_ENTITY_PLAY, 1, NULL, NULL),
    cDecisionEntity(DECISION_ENTITY_PLAY, 2, NULL, NULL),
    cDecisionEntity(DECISION_ENTITY_PLAY, 3, NULL, NULL),
    cDecisionEntity(DECISION_ENTITY_PLAY, 4, NULL, NULL),
    cDecisionEntity(DECISION_ENTITY_PLAY, 5, NULL, NULL),
    cDecisionEntity(DECISION_ENTITY_PLAY, 6, NULL, NULL),
    cDecisionEntity(DECISION_ENTITY_PLAY, 7, NULL, NULL),
    cDecisionEntity(DECISION_ENTITY_PLAY, 8, NULL, NULL),
    cDecisionEntity(DECISION_ENTITY_PLAY, 9, NULL, NULL),
    cDecisionEntity(DECISION_ENTITY_PLAY, 10, NULL, NULL),
    cDecisionEntity(DECISION_ENTITY_PLAY, 11, NULL, NULL),
    cDecisionEntity(DECISION_ENTITY_PLAY, 12, NULL, NULL),
    cDecisionEntity(DECISION_ENTITY_PLAY, 13, NULL, NULL),
    cDecisionEntity(DECISION_ENTITY_PLAY, 14, NULL, NULL),
    cDecisionEntity(DECISION_ENTITY_PLAY, 15, NULL, NULL),
    cDecisionEntity(DECISION_ENTITY_PLAY, 16, NULL, NULL),
    cDecisionEntity(DECISION_ENTITY_PLAY, 17, NULL, NULL),
    cDecisionEntity(DECISION_ENTITY_PLAY, 18, NULL, NULL),
    cDecisionEntity(DECISION_ENTITY_PLAY, 19, NULL, NULL),
    cDecisionEntity(DECISION_ENTITY_PLAY, 20, NULL, NULL),
    cDecisionEntity(DECISION_ENTITY_PLAY, 21, NULL, NULL),
    cDecisionEntity(DECISION_ENTITY_PLAY, 22, NULL, NULL),
    cDecisionEntity(DECISION_ENTITY_PLAY, 23, NULL, NULL),
    cDecisionEntity(DECISION_ENTITY_PLAY, 24, NULL, NULL),
    cDecisionEntity(DECISION_ENTITY_PLAY, 25, NULL, NULL),
    cDecisionEntity(DECISION_ENTITY_PLAY, 26, NULL, NULL),
    cDecisionEntity(DECISION_ENTITY_PLAY, 27, NULL, NULL),
    cDecisionEntity(DECISION_ENTITY_PLAY, 28, NULL, NULL),
    cDecisionEntity(DECISION_ENTITY_PLAY, 29, NULL, NULL),
    cDecisionEntity(DECISION_ENTITY_PLAY, 30, NULL, NULL),
    cDecisionEntity(DECISION_ENTITY_PLAY, 31, NULL, NULL),
    cDecisionEntity(DECISION_ENTITY_PLAY, 32, NULL, NULL),
    cDecisionEntity(DECISION_ENTITY_PLAY, 33, NULL, NULL),
    cDecisionEntity(DECISION_ENTITY_PLAY, 34, NULL, NULL),
    cDecisionEntity(DECISION_ENTITY_PLAY, 35, NULL, NULL),
    cDecisionEntity(DECISION_ENTITY_PLAY, 36, NULL, NULL),
    cDecisionEntity(DECISION_ENTITY_PLAY, 37, NULL, NULL),
    cDecisionEntity(DECISION_ENTITY_PLAY, 38, NULL, NULL),
    cDecisionEntity(DECISION_ENTITY_PLAY, 39, NULL, NULL),
    cDecisionEntity(DECISION_ENTITY_PLAY, 40, NULL, NULL),
    cDecisionEntity(DECISION_ENTITY_PLAY, 41, NULL, NULL),
    cDecisionEntity(DECISION_ENTITY_PLAY, 42, NULL, NULL)
};

// /**
//  * Offset/Address/Size: 0x10C | 0x800190BC | size: 0x28
//  */
// void nlListAddStart<ScriptAction>(ScriptAction**, ScriptAction*, ScriptAction**)
// {
// }

// /**
//  * Offset/Address/Size: 0xE0 | 0x80019090 | size: 0x2C
//  */
// void nlListAddEnd<ScriptAction>(ScriptAction**, ScriptAction**, ScriptAction*)
// {
// }

// /**
//  * Offset/Address/Size: 0x9C | 0x8001904C | size: 0x44
//  */
// void nlListRemoveStart<ScriptAction>(ScriptAction**, ScriptAction**)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x80018FB0 | size: 0x9C
//  */
// void nlListRemoveElement<ScriptAction>(ScriptAction**, ScriptAction*, ScriptAction**)
// {
// }

/**
 * Offset/Address/Size: 0xF98 | 0x80018EF4 | size: 0xBC
 */
cDecisionEntity* GetDecisionEntity(eDecisionEntity type, unsigned long id)
{
    cDecisionEntity* return_entity = NULL;
    if (GetNumDecisionEntities() == 0x2C)
    {
        if (type == DECISION_ENTITY_STRATEGY)
        {
            return_entity = &g_pDecisionEntities[0];
        }
        else if (type == DECISION_ENTITY_PLAY)
        {
            return_entity = &g_pDecisionEntities[id + 1];
        }
    }
    else
    {
        for (int i = 0; i < GetNumDecisionEntities(); i++)
        {
            cDecisionEntity* p = &g_pDecisionEntities[i];
            if ((type == p->m_type) && (id == p->m_id))
            {
                return_entity = p;
                break;
            }
        }
    }
    return return_entity;
}

/**
 * Offset/Address/Size: 0xF28 | 0x80018E84 | size: 0x70
 */
cDecisionEntity::cDecisionEntity(eDecisionEntity type, unsigned long id, FuzzyVariant (*dtf)(cDecisionEntity*), FuzzyVariant (*af)(cDecisionEntity*))
    : m_LastSelectedAction(SAT_NONE, 0.0f)
{
    m_lQueuedActions.m_pEnd = NULL;
    m_lQueuedActions.m_pStart = NULL;
    m_type = type;
    m_id = id;
    m_pDTF = dtf;
    m_pAF = af;
    m_iNumDTFCalls = 0;
    m_pLastQueuedAction = NULL;
}

/**
 * Offset/Address/Size: 0xE5C | 0x80018DB8 | size: 0xCC
 */
float cDecisionEntity::CallDTF(cFielder* pFielder)
{
    float result = 0.0f;
    m_iNumDTFCalls++;

    if (m_pDTF != NULL)
    {
        cFielder* pSavedFielder = g_pScriptCurrentFielder;
        if (g_pScriptCurrentFielder != pFielder)
        {
            FuzzyScriptSetCurrentFielder(pFielder);
        }

        m_pDTF(this);

        if (SelectAction(SAS_BEST_CHANCE, 1.0f))
        {
            result = m_LastSelectedAction.m_fConfidence;
        }
        else
        {
            result = 0.0f;
        }

        if (pSavedFielder != pFielder)
        {
            FuzzyScriptSetCurrentFielder(pSavedFielder);
        }
    }

    return result;
}

/**
 * Offset/Address/Size: 0xDC4 | 0x80018D20 | size: 0x98
 */
bool cDecisionEntity::DoAbort(cFielder* pFielder)
{
    cFielder* pSavedFielder; // r30;

    bool bAbort = false;
    if (m_pAF != NULL)
    {
        pSavedFielder = g_pScriptCurrentFielder;
        if (g_pScriptCurrentFielder != pFielder)
        {
            FuzzyScriptSetCurrentFielder(pFielder);
        }
        bAbort = m_pAF(this).mData.b;
        if (pSavedFielder != pFielder)
        {
            FuzzyScriptSetCurrentFielder(g_pScriptCurrentFielder);
        }
    }
    return bAbort;
}

/**
 * Offset/Address/Size: 0xDBC | 0x80018D18 | size: 0x8
 */
sDesireParams& cDecisionEntity::GetLastDesireParams()
{
    return m_LastSelectedAction.m_sDesireParams;
}

/**
 * Offset/Address/Size: 0xDB4 | 0x80018D10 | size: 0x8
 */
sPlayParams& cDecisionEntity::GetLastPlayParams()
{
    return m_LastSelectedAction.m_sPlayParams;
}

/**
 * Offset/Address/Size: 0x9D4 | 0x80018930 | size: 0x3E0
 */
void cDecisionEntity::QueueActionSetDesire(int, float, float, FuzzyVariant, FuzzyVariant)
{
}

/**
 * Offset/Address/Size: 0x830 | 0x8001878C | size: 0x1A4
 */
void cDecisionEntity::QueueActionSetPlay(int, float, float)
{
}

/**
 * Offset/Address/Size: 0x304 | 0x80018260 | size: 0x52C
 */
void cDecisionEntity::FindDesireAction(int, FuzzyVariant, FuzzyVariant)
{
}

/**
 * Offset/Address/Size: 0x0 | 0x80017F5C | size: 0x304
 */
bool cDecisionEntity::SelectAction(eScriptActionSelection, float)
{
    return false;
}
