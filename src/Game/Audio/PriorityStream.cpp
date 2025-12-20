#include "Game/Audio/PriorityStream.h"

bool PLAY_RECORD::s_BowserAttackNext = true;
bool PLAY_RECORD::s_SuddenDeathNext = true;

/**
 * Offset/Address/Size: 0xEA8 | 0x8015895C | size: 0x10
 */
void PriorityStream::Reset()
{
    PLAY_RECORD::s_BowserAttackNext = true;
    PLAY_RECORD::s_SuddenDeathNext = true;
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
void PriorityStream::FakePause(unsigned long Fadeout)
{
    // Assembly stores byte at offset 0x00 (pause flag)
    // Header shows m_InPause at 0x02, but assembly uses 0x00
    // reinterpret_cast<unsigned char*>(this)[0] = 1;
    m_InPause = true;
    m_Track.Stop(Fadeout);
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
