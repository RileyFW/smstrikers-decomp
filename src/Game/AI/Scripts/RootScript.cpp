#include "Game/AI/Scripts/RootScript.h"

// /**
//  * Offset/Address/Size: 0x8CC | 0x8007CE14 | size: 0x228
//  */
// cDecisionEntity::cDecisionEntity(const cDecisionEntity&)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8007C538 | size: 0x10
//  */
// SaveConfidence::SaveConfidence(float*)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8007C480 | size: 0xB8
//  */
// void FuzzyVariant::FuzzyVariant<float>(const float&)
// {
// }

/**
 * Offset/Address/Size: 0x1E8C | 0x8007C478 | size: 0x8
 */
int GetNumDecisionEntities()
{
    return 0x2C;
}

/**
 * Offset/Address/Size: 0x0 | 0x8007A5EC | size: 0x1E8C
 */
void StrategyChoosePlay(cDecisionEntity* pDecision)
{
}
