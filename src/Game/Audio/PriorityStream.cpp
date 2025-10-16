#include "Game/Audio/PriorityStream.h"

/**
 * Offset/Address/Size: 0xEA8 | 0x8015895C | size: 0x10
 */
void PriorityStream::Reset()
{
}

/**
 * Offset/Address/Size: 0xA34 | 0x801584E8 | size: 0x474
 */
void PriorityStream::PlayStream(unsigned long, float, bool, unsigned long, unsigned long, const char*)
{
}

/**
 * Offset/Address/Size: 0x79C | 0x80158250 | size: 0x298
 */
void PriorityStream::Stop(unsigned long, unsigned long)
{
}

/**
 * Offset/Address/Size: 0x770 | 0x80158224 | size: 0x2C
 */
void PriorityStream::FakePause(unsigned long)
{
}

/**
 * Offset/Address/Size: 0x530 | 0x80157FE4 | size: 0x240
 */
void PriorityStream::FakeResume(bool)
{
}

/**
 * Offset/Address/Size: 0x380 | 0x80157E34 | size: 0x1B0
 */
void PriorityStream::TrackIdleCB()
{
}

/**
 * Offset/Address/Size: 0x0 | 0x80157AB4 | size: 0x380
 */
void PriorityStream::GrabCrowdStream(unsigned long)
{
}
