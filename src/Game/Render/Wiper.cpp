#include "Game/Render/Wiper.h"

/**
 * Offset/Address/Size: 0xC | 0x80127640 | size: 0x4
 */
void ScreenTransitionCallback::TransitionProgressed(float)
{
}

/**
 * Offset/Address/Size: 0x8 | 0x8012763C | size: 0x4
 */
void ScreenTransitionCallback::TransitionFinished()
{
}

/**
 * Offset/Address/Size: 0x4 | 0x80127638 | size: 0x4
 */
void ScreenTransitionCallback::SequenceSwitch()
{
}

/**
 * Offset/Address/Size: 0x0 | 0x80127634 | size: 0x4
 */
void ScreenTransitionCallback::Cut()
{
}

/**
 * Offset/Address/Size: 0x320 | 0x80127630 | size: 0x4
 */
void WiperCallback::TransitionProgressed(float)
{
}

/**
 * Offset/Address/Size: 0x314 | 0x80127624 | size: 0xC
 */
void WiperCallback::TransitionFinished()
{
}

/**
 * Offset/Address/Size: 0x2FC | 0x8012760C | size: 0x18
 */
void Wiper::Reset()
{
}

/**
 * Offset/Address/Size: 0x2F8 | 0x80127608 | size: 0x4
 */
void Wiper::Initialize()
{
}

/**
 * Offset/Address/Size: 0x2EC | 0x801275FC | size: 0xC
 */
void Wiper::WipeInProgress() const
{
}

/**
 * Offset/Address/Size: 0x2E0 | 0x801275F0 | size: 0xC
 */
void Wiper::CutHasOccured() const
{
}

/**
 * Offset/Address/Size: 0x234 | 0x80127544 | size: 0xAC
 */
void Wiper::Instance()
{
}

/**
 * Offset/Address/Size: 0xDC | 0x801273EC | size: 0x158
 */
void Wiper::DoWipe(const char*)
{
}

/**
 * Offset/Address/Size: 0x0 | 0x80127310 | size: 0xDC
 */
void Wiper::Render(float)
{
}
