#include "Game/Audio/CrowdMood.h"

static bool g_DoDecay;

/**
 * Offset/Address/Size: 0x0 | 0x8014D714 | size: 0xFC
 */
void CrowdMood::RestartLoops()
{
}

/**
 * Offset/Address/Size: 0xFC | 0x8014D810 | size: 0x8
 * TODO: 97.5% match - register mismatch (r3 vs r4) due to unused 'this'
 */
void CrowdMood::EnableCrowdDecay(bool enable)
{
    g_DoDecay = enable;
}

/**
 * Offset/Address/Size: 0x104 | 0x8014D818 | size: 0x1B0
 */
void CrowdMood::UnlockStream()
{
}

/**
 * Offset/Address/Size: 0x2B4 | 0x8014D9C8 | size: 0x20
 */
void CrowdMood::LockStream()
{
}

/**
 * Offset/Address/Size: 0x2D4 | 0x8014D9E8 | size: 0x1BC
 */
void CrowdMood::SetLPF(unsigned short)
{
}

/**
 * Offset/Address/Size: 0x490 | 0x8014DBA4 | size: 0x1CC
 */
void CrowdMood::ActivateLPF(bool)
{
}

/**
 * Offset/Address/Size: 0x65C | 0x8014DD70 | size: 0x18C
 */
void CrowdMood::SetCrowdVolume(unsigned long, unsigned long)
{
}

/**
 * Offset/Address/Size: 0x7E8 | 0x8014DEFC | size: 0x1C
 */
void CrowdMood::InitiateFastCrowdTransition()
{
}

/**
 * Offset/Address/Size: 0x804 | 0x8014DF18 | size: 0x128
 */
void CrowdMood::SetMood(CrowdMood::CROWD_MOOD, unsigned long)
{
}

/**
 * Offset/Address/Size: 0x92C | 0x8014E040 | size: 0xCC
 */
void CrowdMood::AdjustMood(CrowdMood::CROWD_MOOD, unsigned long)
{
}

/**
 * Offset/Address/Size: 0x9F8 | 0x8014E10C | size: 0x554
 */
void CrowdMood::Update(float)
{
}

/**
 * Offset/Address/Size: 0xF4C | 0x8014E660 | size: 0x3B4
 */
void CrowdMood::Purge(bool)
{
}

/**
 * Offset/Address/Size: 0x1300 | 0x8014EA14 | size: 0x3E4
 */
void CrowdMood::Init()
{
}

/**
 * Offset/Address/Size: 0x16E4 | 0x8014EDF8 | size: 0x1328
 */
void CrowdMood::ReadConfig()
{
}

/**
 * Offset/Address/Size: 0x2A0C | 0x80150120 | size: 0x270
 */
void UpdateTiming(float)
{
}

/**
 * Offset/Address/Size: 0x2C7C | 0x80150390 | size: 0x224
 */
void PlayMoodDef(MOOD_DEFINITION&)
{
}

/**
 * Offset/Address/Size: 0x2EA0 | 0x801505B4 | size: 0x358
 */
// void PlayVocal(const CROWD_VOCAL_DEFINITION&, CROWD_STATE::VOCALIZATION_STATE&, GCAudioStreaming::AudioStream*)
// {
// }

/**
 * Offset/Address/Size: 0x31F8 | 0x8015090C | size: 0x588
 */
void MoodDefFromBlend(float*, MOOD_DEFINITION&)
{
}

/**
 * Offset/Address/Size: 0x3780 | 0x80150E94 | size: 0x1C8
 */
void ChangeCrowdVolume(float)
{
}

/**
 * Offset/Address/Size: 0x3948 | 0x8015105C | size: 0x10
 */
void CrowdMood::IsStreamLocked()
{
}

/**
 * Offset/Address/Size: 0x3958 | 0x8015106C | size: 0x50
 */
void ___blank(const char*, ...)
{
}

// /**
//  * Offset/Address/Size: 0x39A8 | 0x801510BC | size: 0x134
//  */
// void WarmRandomStream<GCAudioStreaming::MonoAudioStream>(const RANDOM_STREAMS&, GCAudioStreaming::MonoAudioStream*)
// {
// }

// /**
//  * Offset/Address/Size: 0x3ADC | 0x801511F0 | size: 0x134
//  */
// void WarmRandomStream<GCAudioStreaming::StereoAudioStream>(const RANDOM_STREAMS&, GCAudioStreaming::StereoAudioStream*)
// {
// }

// /**
//  * Offset/Address/Size: 0x3C10 | 0x80151324 | size: 0x68
//  */
// void NDimDistance<4>(float*, float*)
// {
// }

// /**
//  * Offset/Address/Size: 0x3C78 | 0x8015138C | size: 0x10
//  */
// void Increment<CrowdMood::CROWD_MOOD>(CrowdMood::CROWD_MOOD&)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8015139C | size: 0x4C
//  */
// void GCAudioStreaming::MonoAudioStream::SafeToPurge()
// {
// }

// /**
//  * Offset/Address/Size: 0x4C | 0x801513E8 | size: 0x4C
//  */
// void GCAudioStreaming::StereoAudioStream::SafeToPurge()
// {
// }

// /**
//  * Offset/Address/Size: 0x98 | 0x80151434 | size: 0x70
//  */
// void GCAudioStreaming::MonoAudioStream::~MonoAudioStream()
// {
// }

// /**
//  * Offset/Address/Size: 0x108 | 0x801514A4 | size: 0x2C
//  */
// void GCAudioStreaming::StereoAudioStream::Purge()
// {
// }

// /**
//  * Offset/Address/Size: 0x134 | 0x801514D0 | size: 0x2C
//  */
// void GCAudioStreaming::MonoAudioStream::Purge()
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x801514FC | size: 0x48
//  */
// void nlStrNCmp<char>(const char*, const char*, unsigned long)
// {
// }
