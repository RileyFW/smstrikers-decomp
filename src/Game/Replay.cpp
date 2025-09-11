#include "Game/Replay.h"

// /**
//  * Offset/Address/Size: 0x68 | 0x80214278 | size: 0x64
//  */
// void SlotPool<Replay::Frame>::~SlotPool()
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x802141FC | size: 0x14
//  */
// void Replay::Reel::Reel()
// {
// }

/**
 * Offset/Address/Size: 0x7C8 | 0x80214074 | size: 0x188
 */
Replay::Replay(char*, int, int)
{
}

/**
 * Offset/Address/Size: 0x740 | 0x80213FEC | size: 0x88
 */
Replay::~Replay()
{
}

// /**
//  * Offset/Address/Size: 0x714 | 0x80213FC0 | size: 0x2C
//  */
// void Replay::Frame::Frame(char*, int, Replay::Frame*)
// {
// }

/**
 * Offset/Address/Size: 0x6AC | 0x80213F58 | size: 0x68
 */
void Replay::Next(Replay::Frame*, int) const
{
}

/**
 * Offset/Address/Size: 0x618 | 0x80213EC4 | size: 0x94
 */
void Replay::TimeOfLastOccurence(unsigned int) const
{
}

/**
 * Offset/Address/Size: 0x49C | 0x80213D48 | size: 0x17C
 */
void Replay::NewFrame()
{
}

/**
 * Offset/Address/Size: 0x480 | 0x80213D2C | size: 0x1C
 */
void Replay::IsReelValid(int) const
{
}

/**
 * Offset/Address/Size: 0x3D4 | 0x80213C80 | size: 0xAC
 */
void Replay::DidOccurInLastNumSeconds(unsigned int, float) const
{
}

/**
 * Offset/Address/Size: 0x38 | 0x802138E4 | size: 0x39C
 */
void Replay::LockReel(float, int, int)
{
}

/**
 * Offset/Address/Size: 0x20 | 0x802138CC | size: 0x18
 */
void Replay::BeginTime() const
{
}

/**
 * Offset/Address/Size: 0x8 | 0x802138B4 | size: 0x18
 */
void Replay::EndTime() const
{
}

/**
 * Offset/Address/Size: 0x0 | 0x802138AC | size: 0x8
 */
void Replay::PlayReel(int)
{
}
