#ifndef _CROWDMOOD_H_
#define _CROWDMOOD_H_

#include "NL/nlStrChr.h"

// void UpdateTiming(float);
// void PlayMoodDef(MOOD_DEFINITION&);
// void MoodDefFromBlend(float*, MOOD_DEFINITION&);
// void ChangeCrowdVolume(float);
// void ___blank(const char*, ...);
// void NDimDistance<4>(float*, float*);

void nlStrNCmp<char>(const char*, const char*, unsigned long);

class CrowdMood
{
public:
    void RestartLoops();
    void EnableCrowdDecay(bool);
    void UnlockStream();
    void LockStream();
    void SetLPF(unsigned short);
    void ActivateLPF(bool);
    void SetCrowdVolume(unsigned long, unsigned long);
    void InitiateFastCrowdTransition();
    // void SetMood(CrowdMood::CROWD_MOOD, unsigned long);
    // void AdjustMood(CrowdMood::CROWD_MOOD, unsigned long);
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
