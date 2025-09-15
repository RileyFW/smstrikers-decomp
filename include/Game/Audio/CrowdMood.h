#ifndef _CROWDMOOD_H_
#define _CROWDMOOD_H_

// #include "NL/nlStrChr.h"

struct CROWD_VOCAL_DEFINITION
{
    float Volume;      // offset 0x0, size 0x4
    float VolumeRange; // offset 0x4, size 0x4
    float Delay;       // offset 0x8, size 0x4
    float DelayRange;  // offset 0xC, size 0x4
}; // total size: 0x10

struct MOOD_DEFINITION
{
    float NeutralVol;       // offset 0x0, size 0x4
    float NegativeVol;      // offset 0x4, size 0x4
    float PositiveVol;      // offset 0x8, size 0x4
    float SaturationVolume; // offset 0xC, size 0x4
    union
    {                                  // inferred
        float SaturationStart;         // offset 0x10, size 0x4
        unsigned long SaturationSFXId; // offset 0x10, size 0x4
    };
    struct CROWD_VOCAL_DEFINITION Chant;  // offset 0x14, size 0x10
    struct CROWD_VOCAL_DEFINITION Heckle; // offset 0x24, size 0x10
}; // total size: 0x34

void UpdateTiming(float);
void PlayMoodDef(MOOD_DEFINITION&);
void MoodDefFromBlend(float*, MOOD_DEFINITION&);
void ChangeCrowdVolume(float);
// void ___blank(const char*, ...);
// void NDimDistance<4>(float*, float*);

// void nlStrNCmp<char>(const char*, const char*, unsigned long);

class CrowdMood
{
public:
    enum CROWD_MOOD
    {
        CM_Positive = 0,
        CM_Negative = 1,
        CM_Bored = 2,
        CM_Frustrated = 3,
        CM_Neutral = 4,
        CM_END = 5,
    };

    void RestartLoops();
    void EnableCrowdDecay(bool);
    void UnlockStream();
    void LockStream();
    void SetLPF(unsigned short);
    void ActivateLPF(bool);
    void SetCrowdVolume(unsigned long, unsigned long);
    void InitiateFastCrowdTransition();
    void SetMood(CrowdMood::CROWD_MOOD, unsigned long);
    void AdjustMood(CrowdMood::CROWD_MOOD, unsigned long);
    void Update(float);
    void Purge(bool);
    void Init();
    void ReadConfig();
    void IsStreamLocked();
};

// class PlayVocal(const CROWD_VOCAL_DEFINITION&, CROWD_STATE
// {
// public:
//     void VOCALIZATION_STATE&, GCAudioStreaming::AudioStream*);
// };

// class WarmRandomStream<GCAudioStreaming
// {
// public:
//     void MonoAudioStream>(const RANDOM_STREAMS&, GCAudioStreaming::MonoAudioStream*);
//     void StereoAudioStream>(const RANDOM_STREAMS&, GCAudioStreaming::StereoAudioStream*);
// };

// class Increment<CrowdMood
// {
// public:
//     void CROWD_MOOD>(CrowdMood::CROWD_MOOD&);
// };

// class GCAudioStreaming
// {
// public:
//     void MonoAudioStream::SafeToPurge();
//     void StereoAudioStream::SafeToPurge();
//     void MonoAudioStream::~MonoAudioStream();
//     void StereoAudioStream::Purge();
//     void MonoAudioStream::Purge();
// };

#endif // _CROWDMOOD_H_
