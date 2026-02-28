#include "Game/Audio/PriorityStream.h"
#include "Game/Audio/CrowdMood.h"
#include "NL/nlPrint.h"
#include "NL/nlString.h"

unsigned char PLAY_RECORD::s_BowserAttackNext = true;
unsigned char PLAY_RECORD::s_SuddenDeathNext = true;

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
 * TODO: 95.8% match - remaining diffs in switch/control-flow shape:
 *   r3/r4 compare register swap, literal load via mr r5, and default-path store/branch placement
 */
void PriorityStream::TrackIdleCB()
{
    char StreamName[64];
    unsigned char* pCounter;
    const char* Format;

    if (m_InPause)
    {
        return;
    }

    if (m_PStream.m_OrigStreamId)
    {
        m_PStream.m_OrigStreamId = 0;

        if (m_HasCrowdStream)
        {
            if (m_HasCrowdStream && m_PStream.m_Active)
            {
                switch (m_PStream.m_StreamId)
                {
                case 0x436E3953:
                    pCounter = &PLAY_RECORD::s_BowserAttackNext;
                    Format = "bowser_attack_%d";
                    break;
                case 0x57CB5A12:
                    pCounter = &PLAY_RECORD::s_SuddenDeathNext;
                    Format = "sudden_death_%d";
                    break;
                default:
                    m_HasCrowdStream = m_PStream.m_StreamId;
                    goto after_switch;
                }

                nlSNPrintf(StreamName, 64, Format, *pCounter);
                *pCounter = *pCounter + 1;
                if (*pCounter == 4)
                {
                    *pCounter = 1;
                }
                m_HasCrowdStream = nlStringLowerHash(StreamName);

            after_switch:
                if (m_PStream.m_Queue)
                {
                    m_PStream.m_Queue = 0;
                    m_PStream.m_Track.QueueStream(
                        m_HasCrowdStream, m_PStream.m_Volume, (m_PStream.m_Looping & 1), m_PStream.m_FadeIn, m_PStream.m_StreamParam[0] ? m_PStream.m_StreamParam : (const char*)0, (MasterVolume::VOLUME_GROUP)m_PStream.m_VolGroup);
                }
                else
                {
                    m_PStream.m_Track.PlayStream(
                        m_HasCrowdStream, m_PStream.m_Volume, (m_PStream.m_Looping & 1), m_PStream.m_FadeIn, m_PStream.m_ExistingFadeOut, m_PStream.m_StreamParam[0] ? m_PStream.m_StreamParam : (const char*)0, (MasterVolume::VOLUME_GROUP)m_PStream.m_VolGroup);
                }
                return;
            }
            return;
        }
    }

    if (m_HasCrowdStream)
    {
        m_HasCrowdStream = 0;
    }
    CrowdMood::UnlockStream();
}

/**
 * Offset/Address/Size: 0x0 | 0x80157AB4 | size: 0x380
 */
void PriorityStream::GrabCrowdStream(unsigned long)
{
}
