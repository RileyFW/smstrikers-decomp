#include "Game/FE/feChooseSideComponent.h"

/**
 * Offset/Address/Size: 0x16B0 | 0x800C4AF4 | size: 0xCC
 */
IChooseSide::IChooseSide()
{
}

/**
 * Offset/Address/Size: 0x1658 | 0x800C4A9C | size: 0x58
 */
IChooseSide::~IChooseSide()
{
}

/**
 * Offset/Address/Size: 0x15D4 | 0x800C4A18 | size: 0x84
 */
void IChooseSide::Update(float, eFEINPUT_PAD*, int)
{
}

/**
 * Offset/Address/Size: 0xFD4 | 0x800C4418 | size: 0x600
 */
void IChooseSide::UpdateForFE(float, eFEINPUT_PAD*)
{
}

/**
 * Offset/Address/Size: 0xCDC | 0x800C4120 | size: 0x2F8
 */
void IChooseSide::UpdateForPause(float, eFEINPUT_PAD*)
{
}

/**
 * Offset/Address/Size: 0x820 | 0x800C3C64 | size: 0x4BC
 */
void IChooseSide::CheckControllers(int)
{
}

/**
 * Offset/Address/Size: 0x4C0 | 0x800C3904 | size: 0x360
 */
void IChooseSide::ResetAndPositionControllers(bool)
{
}

/**
 * Offset/Address/Size: 0x3DC | 0x800C3820 | size: 0xE4
 */
void IChooseSide::SetReady(int, bool)
{
}

/**
 * Offset/Address/Size: 0x2A4 | 0x800C36E8 | size: 0x138
 */
void IChooseSide::PositionController(int, bool, bool)
{
}

/**
 * Offset/Address/Size: 0x1DC | 0x800C3620 | size: 0xC8
 */
void IChooseSide::AllPlayersReady() const
{
}

/**
 * Offset/Address/Size: 0x16C | 0x800C35B0 | size: 0x70
 */
void IChooseSide::AllPluggedInAreReady() const
{
}

/**
 * Offset/Address/Size: 0x114 | 0x800C3558 | size: 0x58
 */
void IChooseSide::AtLeastOnePlayerReady() const
{
}

/**
 * Offset/Address/Size: 0xBC | 0x800C3500 | size: 0x58
 */
void IChooseSide::AllControllersAreCentred() const
{
}

/**
 * Offset/Address/Size: 0x58 | 0x800C349C | size: 0x64
 */
void IChooseSide::TweenSetPosCallback(void*, const float*)
{
}

/**
 * Offset/Address/Size: 0x0 | 0x800C3444 | size: 0x58
 */
void IChooseSide::SaveChanges()
{
}
