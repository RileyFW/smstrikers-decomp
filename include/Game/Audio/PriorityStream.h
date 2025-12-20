#ifndef _PRIORITYSTREAM_H_
#define _PRIORITYSTREAM_H_

#include "Game/Audio/StreamTrack.h"

// namespace AudioStreamTrack
// {
// class StreamTrack;
// }

enum VOLUME_GROUP
{
    VG_Special = 0,
    VG_Music = 1,
    VG_SFX = 2,
    VG_Voice = 3,
};

class PLAY_RECORD
{
public:
    /* 0x00 */ unsigned long m_StreamId;
    /* 0x04 */ unsigned long m_OrigStreamId;
    /* 0x08 */ float m_Volume;
    /* 0x0C */ unsigned long m_FadeIn : 15;
    /* 0x0C */ unsigned long m_ExistingFadeOut : 15;
    /* 0x0F */ unsigned char m_Looping : 1;
    /* 0x10 */ char m_StreamParam[32];
    /* 0x30 */ AudioStreamTrack::StreamTrack& m_Track;
    /* 0x34 */ VOLUME_GROUP m_VolGroup;

    static bool s_BowserAttackNext;
    static bool s_SuddenDeathNext;
}; // total size: 0x38

class PriorityStream
{
public:
    PriorityStream(AudioStreamTrack::StreamTrack&);
    void Reset();
    void PlayStream(unsigned long, float, bool, unsigned long, unsigned long, const char*);
    void Stop(unsigned long, unsigned long);
    void FakePause(unsigned long);
    void FakeResume(bool);
    void TrackIdleCB();
    void GrabCrowdStream(unsigned long);

    /* 0x00 */ bool m_InPause : 8;
    /* 0x01 */ bool m_BowserAttackNext;
    /* 0x02 */ bool m_SuddenDeathNext;
    /* 0x04 */ AudioStreamTrack::StreamTrack& m_Track;
    /* 0x08 */ bool m_HasCrowdStream;
    /* 0x0C */ PLAY_RECORD m_PStream;
    /* 0x44 */ PLAY_RECORD m_CapChant;
}; // total size: 0x7C

#endif // _PRIORITYSTREAM_H_
