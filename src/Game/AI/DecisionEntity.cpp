#include "Game/AI/DecisionEntity.h"

/**
 * Offset/Address/Size: 0x10C | 0x800190BC | size: 0x28
 */
void nlListAddStart<ScriptAction>(ScriptAction**, ScriptAction*, ScriptAction**)
{
}

/**
 * Offset/Address/Size: 0xE0 | 0x80019090 | size: 0x2C
 */
void nlListAddEnd<ScriptAction>(ScriptAction**, ScriptAction**, ScriptAction*)
{
}

/**
 * Offset/Address/Size: 0x9C | 0x8001904C | size: 0x44
 */
void nlListRemoveStart<ScriptAction>(ScriptAction**, ScriptAction**)
{
}

/**
 * Offset/Address/Size: 0x0 | 0x80018FB0 | size: 0x9C
 */
void nlListRemoveElement<ScriptAction>(ScriptAction**, ScriptAction*, ScriptAction**)
{
}

/**
 * Offset/Address/Size: 0xF98 | 0x80018EF4 | size: 0xBC
 */
void GetDecisionEntity(eDecisionEntity, unsigned long)
{
}

/**
 * Offset/Address/Size: 0xF28 | 0x80018E84 | size: 0x70
 */
cDecisionEntity::cDecisionEntity(eDecisionEntity, unsigned long, FuzzyVariant (*)(cDecisionEntity*), FuzzyVariant (*)(cDecisionEntity*))
{
}

/**
 * Offset/Address/Size: 0xE5C | 0x80018DB8 | size: 0xCC
 */
float cDecisionEntity::CallDTF(cFielder*)
{
    return 0.0f;
}

/**
 * Offset/Address/Size: 0xDC4 | 0x80018D20 | size: 0x98
 */
bool cDecisionEntity::DoAbort(cFielder*)
{
    return false;
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
void cDecisionEntity::SelectAction(eScriptActionSelection, float)
{
}
