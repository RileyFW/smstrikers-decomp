#include "Game/AI/FielderDesires.h"

/**
 * Offset/Address/Size: 0x0 | 0x80037FD8 | size: 0x3C
 */
CommonDesireData::~CommonDesireData()
{
}

/**
 * Offset/Address/Size: 0xA84 | 0x80037F0C | size: 0xCC
 */
CommonDesireData::CommonDesireData(const CommonDesireData&)
{
}

// /**
//  * Offset/Address/Size: 0x0 | 0x8003744C | size: 0x3C
//  */
// FilteredRandomRange::~FilteredRandomRange()
// {
// }

/**
 * Offset/Address/Size: 0x668C | 0x80037410 | size: 0x3C
 */
float CommonDesireData::CalcFuzzyChance(float)
{
    return 0.0f;
}

/**
 * Offset/Address/Size: 0x6668 | 0x800373EC | size: 0x24
 */
bool CommonDesireData::CalcBoolChance(float)
{
    return false;
}

/**
 * Offset/Address/Size: 0x660C | 0x80037390 | size: 0x5C
 */
float CommonDesireData::NormalizeConfidence(float)
{
    return 0.0f;
}

/**
 * Offset/Address/Size: 0x65F8 | 0x8003737C | size: 0x14
 */
CommonDesireData& GetCommonDesireData(eFielderDesireState)
{
    static CommonDesireData commonDesireData;
    return commonDesireData;
}

// /**
//  * Offset/Address/Size: 0x6484 | 0x80037208 | size: 0x174
//  */
// void cFielder::QueueDesire(eFielderDesireState, float, FuzzyVariant, FuzzyVariant)
// {
// }

// /**
//  * Offset/Address/Size: 0x63C8 | 0x8003714C | size: 0xBC
//  */
// void cFielder::ClearQueuedDesire()
// {
// }

// /**
//  * Offset/Address/Size: 0x620C | 0x80036F90 | size: 0x1BC
//  */
// void cFielder::InitDesire(const sDesireParams*, float)
// {
// }

// /**
//  * Offset/Address/Size: 0x54DC | 0x80036260 | size: 0xD30
//  */
// void cFielder::InitDesire(eFielderDesireState, float, float, FuzzyVariant, FuzzyVariant)
// {
// }

// /**
//  * Offset/Address/Size: 0x4700 | 0x80035484 | size: 0xDDC
//  */
// void cFielder::UpdateDesireState(float)
// {
// }

// /**
//  * Offset/Address/Size: 0x469C | 0x80035420 | size: 0x64
//  */
// void cFielder::EndDesire(bool)
// {
// }

// /**
//  * Offset/Address/Size: 0x45C8 | 0x8003534C | size: 0xD4
//  */
// void cFielder::CleanUpDesire(eFielderDesireState)
// {
// }

// /**
//  * Offset/Address/Size: 0x4204 | 0x80034F88 | size: 0x3C4
//  */
// void cFielder::DesireInterceptBall(float)
// {
// }

// /**
//  * Offset/Address/Size: 0x39EC | 0x80034770 | size: 0x818
//  */
// void cFielder::DesireMark(float)
// {
// }

// /**
//  * Offset/Address/Size: 0x35E4 | 0x80034368 | size: 0x408
//  */
// void cFielder::DesireSupportBall(float, bool)
// {
// }

// /**
//  * Offset/Address/Size: 0x33A0 | 0x80034124 | size: 0x244
//  */
// void cFielder::InitDesireGetOpen()
// {
// }

// /**
//  * Offset/Address/Size: 0x30B4 | 0x80033E38 | size: 0x2EC
//  */
// void cFielder::InitDesireOneTimerFromRun(unsigned short, const nlVector3&, const nlVector3&, bool, bool)
// {
// }

// /**
//  * Offset/Address/Size: 0x2E60 | 0x80033BE4 | size: 0x254
//  */
// void cFielder::DesireOneTimer(float)
// {
// }

// /**
//  * Offset/Address/Size: 0x2D08 | 0x80033A8C | size: 0x158
//  */
// void cFielder::InitDesireReceivePassFromIdle(const LooseBallContactAnimInfo*, unsigned short, bool)
// {
// }

// /**
//  * Offset/Address/Size: 0x2080 | 0x80032E04 | size: 0xC88
//  */
// void cFielder::DesireReceivePassFromIdle(float)
// {
// }

// /**
//  * Offset/Address/Size: 0x1DE8 | 0x80032B6C | size: 0x298
//  */
// void cFielder::InitDesireReceivePassFromRun(const LooseBallContactAnimInfo*, const nlVector3&, bool, const nlVector3&)
// {
// }

// /**
//  * Offset/Address/Size: 0x130C | 0x80032090 | size: 0xADC
//  */
// void cFielder::DesireReceivePassFromRun(float)
// {
// }

// /**
//  * Offset/Address/Size: 0xEE4 | 0x80031C68 | size: 0x428
//  */
// void cFielder::InitDesireRunToNet()
// {
// }

// /**
//  * Offset/Address/Size: 0xCA8 | 0x80031A2C | size: 0x23C
//  */
// void cFielder::DesireSlideAttack(float)
// {
// }

// /**
//  * Offset/Address/Size: 0x794 | 0x80031518 | size: 0x514
//  */
// void cFielder::DesireUserControlled(float)
// {
// }

// /**
//  * Offset/Address/Size: 0x41C | 0x800311A0 | size: 0x378
//  */
// void cFielder::DesireUsePowerup(float)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x80030D84 | size: 0x41C
//  */
// void cFielder::DesireWindupShot(float)
// {
// }
