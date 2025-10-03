#include "AvoidController.h"

/**
 * Offset/Address/Size: 0x22E8 | 0x8000993C | size: 0x98
 */
AvoidController::AvoidController(cFielder*)
{
}

/**
 * Offset/Address/Size: 0x2250 | 0x800098A4 | size: 0x98
 */
void AvoidController::SetThingsToAvoid(int)
{
}

/**
 * Offset/Address/Size: 0x2240 | 0x80009894 | size: 0x10
 */
void AvoidController::UseMinimumAvoidance(cPlayer*)
{
}

/**
 * Offset/Address/Size: 0x2188 | 0x800097DC | size: 0xB8
 */
void AvoidController::GetLastRepulsionVector(eAvoidableThings)
{
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
void AvoidController::CalcFielderRepulsionVector(nlVector3&)
{
}

/**
 * Offset/Address/Size: 0xE08 | 0x8000845C | size: 0x258
 */
void AvoidController::CalcPowerupRepulsionVector(nlVector3&)
{
}

/**
 * Offset/Address/Size: 0xC30 | 0x80008284 | size: 0x1D8
 */
void AvoidController::CalcDesiredVelocityToAvoidSideline(nlVector2&, const nlVector2&, const nlVector2&, const nlVector2&, const nlVector2&)
{
}

/**
 * Offset/Address/Size: 0x8C8 | 0x80007F1C | size: 0x368
 */
void AvoidController::CalcDesiredVelocityToAvoidCorner(nlVector2&, const sCornerSegment&, const nlVector2&, const nlVector2&)
{
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
