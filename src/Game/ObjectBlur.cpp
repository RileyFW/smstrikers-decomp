#include "Game/ObjectBlur.h"

/**
 * Offset/Address/Size: 0x0 | 0x801627D4 | size: 0x3C
 */
void BlurManager::Shutdown()
{
}

/**
 * Offset/Address/Size: 0x3C | 0x80162810 | size: 0x128
 */
void BlurManager::Update(float)
{
}

/**
 * Offset/Address/Size: 0x164 | 0x80162938 | size: 0x78
 */
void BlurManager::DestroyHandler(BlurHandler*, float)
{
}

/**
 * Offset/Address/Size: 0x1DC | 0x801629B0 | size: 0xD0
 */
BlurHandler* BlurManager::GetNewHandler(const char*, float, int, bool)
{
    return NULL;
}

/**
 * Offset/Address/Size: 0x2AC | 0x80162A80 | size: 0x514
 */
void BlurHandler::RenderMesh(unsigned long)
{
}

/**
 * Offset/Address/Size: 0x7C0 | 0x80162F94 | size: 0x14
 */
void BlurHandler::Die(float)
{
}

/**
 * Offset/Address/Size: 0x7D4 | 0x80162FA8 | size: 0x1B0
 */
void BlurHandler::AddViewOrientedPoint(const nlVector3&, const nlVector3&)
{
}

/**
 * Offset/Address/Size: 0x984 | 0x80163158 | size: 0x1C4
 */
void BlurHandler::ConstructViewOrientedPoints(nlVector3&, nlVector3&, nlVector3, const nlVector3&)
{
}

// /**
//  * Offset/Address/Size: 0x0 | 0x8016331C | size: 0x20
//  */
// void nlDeleteDLRing<BlurHandler>(BlurHandler**)
// {
// }

// /**
//  * Offset/Address/Size: 0x20 | 0x8016333C | size: 0x20
//  */
// void nlDLRingIsEnd<BlurHandler>(BlurHandler*, BlurHandler*)
// {
// }

// /**
//  * Offset/Address/Size: 0x40 | 0x8016335C | size: 0x18
//  */
// void nlDLRingGetStart<BlurHandler>(BlurHandler*)
// {
// }

// /**
//  * Offset/Address/Size: 0x58 | 0x80163374 | size: 0x44
//  */
// void nlDLRingRemove<BlurHandler>(BlurHandler**, BlurHandler*)
// {
// }

// /**
//  * Offset/Address/Size: 0x9C | 0x801633B8 | size: 0x3C
//  */
// void nlDLRingAddEnd<BlurHandler>(BlurHandler**, BlurHandler*)
// {
// }

// /**
//  * Offset/Address/Size: 0xD8 | 0x801633F4 | size: 0x38
//  */
// void nlDLRingAddStart<BlurHandler>(BlurHandler**, BlurHandler*)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8016342C | size: 0x94
//  */
// void nlDeleteRing<BlurHandler>(BlurHandler**)
// {
// }

// /**
//  * Offset/Address/Size: 0xFC | 0x80163528 | size: 0x64
//  */
// void SlotPool<BlurHandler>::~SlotPool()
// {
// }
