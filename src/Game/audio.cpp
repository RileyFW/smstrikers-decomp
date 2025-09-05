
#include "Game/Sys/audio.h"
#include "Game/GameAudio.h"

#include "NL/nlList.h"
#include "NL/nlMemory.h"
#include "NL/nlTimer.h"
#include "NL/plat/plataudio.h"

struct FadeAudioData // TODO: this should be a ListEntry<T>
{
    /* 0x00 */ char padding[0x28];
    /* 0x28 */ FadeAudioData* next; // Pointer to next node for nlDeleteList
};

struct DelayTimer
{
    float _unk_0x0;
    // todo: implement
};

FadeAudioData* g_pFadeList;

// extern cGame *g_pGame;
// extern cTeam *g_pTeams;

bool gbFilterOn = false;
bool gbPitchBent = false;
bool gbUseHiQualityReverb = false;
bool gbListenerInit = false;

bool g_bAudioInitialized = false;
bool g_bAudioInGameLoaded = false;
bool g_bWorldSFXInitialized = false;

static f32 gfVolumeGroups[0x18];

namespace Audio
{

DelayTimer gChantDelayTimer;
bool gbGameIsPaused = false;
bool gbStartingGame = true;
bool g_bHomeTeamHasJustScored = false;

/**
 * Offset/Address/Size: 0x0 | 0x8013C514 | size: 0x10
 */
float MasterVolume::GetVoiceVolume()
{
    return gfVolumeGroups[3];
}

/**
 * Offset/Address/Size: 0x10 | 0x8013C524 | size: 0x208
 */
void MasterVolume::SetVoiceVolume(float, int)
{
}

/**
 * Offset/Address/Size: 0x218 | 0x8013C72C | size: 0x14
 */
void MasterVolume::SetVolume(MasterVolume::VOLUME_GROUP, float)
{
}

/**
 * Offset/Address/Size: 0x22C | 0x8013C740 | size: 0x14
 */
void MasterVolume::GetVolume(MasterVolume::VOLUME_GROUP)
{
}

/**
 * Offset/Address/Size: 0x240 | 0x8013C754 | size: 0x1A0
 */
// void FadeFilterFromCurrentToZero()
// {
// }

/**
 * Offset/Address/Size: 0x3E0 | 0x8013C8F4 | size: 0x94
 */
// void FadeFilterToFullStrength()
// {
// }

/**
 * Offset/Address/Size: 0x474 | 0x8013C988 | size: 0x354
 */
// void PitchBend(float, float, float, float)
// {
// }

/**
 * Offset/Address/Size: 0x7C8 | 0x8013CCDC | size: 0x510
 */
// void FadeFilter(float, float, float, float)
// {
// }

/**
 * Offset/Address/Size: 0xCD8 | 0x8013D1EC | size: 0x2C
 */
void ClearFadeData()
{
    nlDeleteList<FadeAudioData>(&g_pFadeList);
    g_pFadeList = NULL;
}

/**
 * Offset/Address/Size: 0xD04 | 0x8013D218 | size: 0x20
 */
bool IsEmitterActive(SFXEmitter* emitter)
{
    return PlatAudio::IsEmitterActive(emitter);
}

/**
 * Offset/Address/Size: 0xD24 | 0x8013D238 | size: 0x20
 */
u32 GetEmitterVoiceID(SFXEmitter* emitter)
{
    return PlatAudio::GetEmitterVoiceID(emitter);
}

/**
 * Offset/Address/Size: 0xD44 | 0x8013D258 | size: 0x20
 */
void Remove3DSFXEmitter(SFXEmitter* emitter)
{
    PlatAudio::RemoveEmitter(emitter);
}

/**
 * Offset/Address/Size: 0xD64 | 0x8013D278 | size: 0x20
 */
void Add3DSFXEmitter(const EmitterStartInfo& emitterStartInfo)
{
    PlatAudio::Add3DSFXEmitter(emitterStartInfo);
}

/**
 * Offset/Address/Size: 0xD84 | 0x8013D298 | size: 0x20
 */
void GetFreeEmitter(unsigned long& id)
{
    return PlatAudio::GetFreeEmitter(id);
}

/**
 * Offset/Address/Size: 0xDA4 | 0x8013D2B8 | size: 0x20
 */
SFXEmitter* GetEmitter(unsigned long id)
{
    return PlatAudio::GetSFXEmitter(id);
}

/**
 * Offset/Address/Size: 0xDC4 | 0x8013D2D8 | size: 0x8
 */
void SetListenerActive(bool active)
{
    gbListenerInit = active;
}

/**
 * Offset/Address/Size: 0xDCC | 0x8013D2E0 | size: 0x8
 */
bool IsListenerActive()
{
    return gbListenerInit;
}

/**
 * Offset/Address/Size: 0xDCC | 0x8013D2E0 | size: 0x8
 */
void SetOutputMode(MusyXOutputType outputType)
{
    PlatAudio::SetOutputMode(outputType);
}

/**
 * Offset/Address/Size: 0xDF4 | 0x8013D308 | size: 0x78
 */
// void SetPitchBendOnSFX(unsigned long, unsigned short)
// {
// }

/**
 * Offset/Address/Size: 0xE6C | 0x8013D380 | size: 0x78
 */
// void SetFilterFreqOnSFX(unsigned long, unsigned short)
// {
// }

/**
 * Offset/Address/Size: 0xEE4 | 0x8013D3F8 | size: 0x88
 */
// void ActivateFilterOnSFX(unsigned long, bool)
// {
// }

/**
 * Offset/Address/Size: 0xF6C | 0x8013D480 | size: 0xBC
 */
// void SetPitchBendOnAllDialogueSFX(unsigned short)
// {
// }

/**
 * Offset/Address/Size: 0x1028 | 0x8013D53C | size: 0xE0
 */
// void ActivateFilterOnAllCurrentSFX(bool)
// {
// }

/**
 * Offset/Address/Size: 0x1108 | 0x8013D61C | size: 0x1CC
 */
// void SetVolGroupVolume(int, float, int)
// {
// }

/**
 * Offset/Address/Size: 0x12D4 | 0x8013D7E8 | size: 0x4C
 */
// void SetSFXVolumeGroup(unsigned long, int)
// {
// }

/**
 * Offset/Address/Size: 0x1320 | 0x8013D834 | size: 0x20
 */
// void SetSFXVolume(unsigned long, float)
// {
// }

/**
 * Offset/Address/Size: 0x1340 | 0x8013D854 | size: 0x25C
 */
// void Update3DSFXEmitters()
// {
// }

/**
 * Offset/Address/Size: 0x159C | 0x8013DAB0 | size: 0xA34
 */
// void UpdateFades(float)
// {
// }

/**
 * Offset/Address/Size: 0x1FD0 | 0x8013E4E4 | size: 0x354
 */
void Update(float)
{
}

/**
 * Offset/Address/Size: 0x2324 | 0x8013E838 | size: 0x20
 */
int GetSndIDError()
{
    return PlatAudio::GetSndIDError();
}

/**
 * Offset/Address/Size: 0x2344 | 0x8013E858 | size: 0x34
 */
// void IsSFXPlaying(unsigned long)
// {
// }

/**
 * Offset/Address/Size: 0x2378 | 0x8013E88C | size: 0x34
 */
// void StopSFX(unsigned long)
// {
// }

/**
 * Offset/Address/Size: 0x23AC | 0x8013E8C0 | size: 0x214
 */
// void PlaySFXEventFromScript(const SoundEventData&, const char*, float, float)
// {
// }

/**
 * Offset/Address/Size: 0x25C0 | 0x8013EAD4 | size: 0x68
 */
// void StopCharSFXbyStr(const char*, NisCharacterClass)
// {
// }

/**
 * Offset/Address/Size: 0x2628 | 0x8013EB3C | size: 0xB4
 */
// void StopWorldSFXbyStr(const char*)
// {
// }

/**
 * Offset/Address/Size: 0x26DC | 0x8013EBF0 | size: 0x104
 */
// void PlayCharSFXbyStr(const char*, NisCharacterClass, float, float, bool, bool, const nlVector3*, const nlVector3*, unsigned long*)
// {
// }

/**
 * Offset/Address/Size: 0x27E0 | 0x8013ECF4 | size: 0x144
 */
// void PlayWorldSFXbyStr(const char*, float, float, bool, bool, const nlVector3*, const nlVector3*, unsigned long*)
// {
// }

/**
 * Offset/Address/Size: 0x2924 | 0x8013EE38 | size: 0x30
 */
// void RemoveDelayedSFX(unsigned long)
// {
// }

/**
 * Offset/Address/Size: 0x2954 | 0x8013EE68 | size: 0xE8
 */
// void IsDelayedCharSFX(unsigned long, cGameSFX*)
// {
// }

/**
 * Offset/Address/Size: 0x2A3C | 0x8013EF50 | size: 0x3E4
 */
// void AddDelayedSFX(const SoundAttributes&, unsigned long, float, float, cGameSFX*)
// {
// }

/**
 * Offset/Address/Size: 0x2E20 | 0x8013F334 | size: 0x17C
 */
// void PlaySFXbyID(const SoundAttributes&, unsigned long, float, float, int)
// {
// }

/**
 * Offset/Address/Size: 0x2F9C | 0x8013F4B0 | size: 0x20
 */
// void PlaySFX(const SFXStartInfo&)
// {
// }

/**
 * Offset/Address/Size: 0x2FBC | 0x8013F4D0 | size: 0x8
 */
// void GetAudioTimer()
// {
// }

/**
 * Offset/Address/Size: 0x2FC4 | 0x8013F4D8 | size: 0x44
 */
void Shutdown()
{
}

/**
 * Offset/Address/Size: 0x3008 | 0x8013F51C | size: 0x20
 */
void Silence()
{
}

/**
 * Offset/Address/Size: 0x3028 | 0x8013F53C | size: 0x48
 */
void ResetForNewGame()
{
    gbGameIsPaused = false;
    gbStartingGame = true;
    g_bHomeTeamHasJustScored = true;
    gChantDelayTimer._unk_0x0 = 0.0f;
    nlDeleteList<FadeAudioData>(&g_pFadeList);
    g_pFadeList = NULL;
}

/**
 * Offset/Address/Size: 0x3070 | 0x8013F584 | size: 0xC
 */
void ResetPauseStatus()
{
    gbGameIsPaused = false;
}

/**
 * Offset/Address/Size: 0x307C | 0x8013F590 | size: 0x64
 */
void UnloadWorldSFX()
{
}

/**
 * Offset/Address/Size: 0x30E0 | 0x8013F5F4 | size: 0x8
 */
bool IsWorldSFXLoaded()
{
    return g_bWorldSFXInitialized;
}

/**
 * Offset/Address/Size: 0x30E8 | 0x8013F5FC | size: 0xC0
 */
void LoadWorldSFX()
{
}

/**
 * Offset/Address/Size: 0x31A8 | 0x8013F6BC | size: 0xB0
 */
void UnloadInGameSFX()
{
}

/**
 * Offset/Address/Size: 0x3258 | 0x8013F76C | size: 0x80
 */
void LoadInGameSFX()
{
}

/**
 * Offset/Address/Size: 0x32D8 | 0x8013F7EC | size: 0x8
 */
bool IsInited()
{
    return g_bAudioInitialized;
}

/**
 * Offset/Address/Size: 0x32E0 | 0x8013F7F4 | size: 0x9C
 */
// void ShutdownReverb()
// {
// }

/**
 * Offset/Address/Size: 0x337C | 0x8013F890 | size: 0x734
 */
// void InitializeReverb(eStadiumID, unsigned char)
// {
// }

/**
 * Offset/Address/Size: 0x3AB0 | 0x8013FFC4 | size: 0xF60
 */
// void ReadVolGroupSettings()
// {
// }

/**
 * Offset/Address/Size: 0x4A10 | 0x80140F24 | size: 0x15C
 */
// void Initialize(bool)
// {
// }

/**
 * Offset/Address/Size: 0x4B6C | 0x80141080 | size: 0x2C
 */
void SoundAttributes::UseStationaryPosVector(const nlVector3& position)
{
    m_vec_0x44 = position;
    m_unk_0x5C = 2;
    m_unk_0x30 = true;
}

/**
 * Offset/Address/Size: 0x4B98 | 0x801410AC | size: 0x44
 */
void SoundAttributes::UseVectors(const nlVector3& v1, const nlVector3& v2)
{
    m_vec_0x44 = v1;
    m_vec_0x50 = v2;
    m_unk_0x5C = 2;
    m_unk_0x30 = true;
}

/**
 * Offset/Address/Size: 0x4BDC | 0x801410F0 | size: 0x1C
 */
void SoundAttributes::UseVectorPtrs(const nlVector3* v1, const nlVector3* v2)
{
    // *(const nlVector3**)&m_unk_0x44 = v1;
    // *(const nlVector3**)&m_unk_0x50 = v2;
    m_vecPtr_0x44 = v1;
    m_vecPtr_0x50 = v2;
    m_unk_0x5C = 3;
    m_unk_0x30 = true;
}

/**
 * Offset/Address/Size: 0x4BF8 | 0x8014110C | size: 0x14
 */
void SoundAttributes::UsePhysObj(PhysicsObject* obj)
{
    m_physicsObject = obj;
    m_unk_0x5C = 1;
    m_unk_0x30 = true;
}

/**
 * Offset/Address/Size: 0x4C0C | 0x80141120 | size: 0xC
 */
void SoundAttributes::SetSoundType(unsigned long soundType, bool arg)
{
    m_soundType = soundType;
    m_unk_0x2C = arg;
}

/**
 * Offset/Address/Size: 0x4C18 | 0x8014112C | size: 0x100
 */
void SoundAttributes::Init()
{
    m_unk_0x00 = 0;
    m_soundType = -1;
    m_unk_0x08 = -1;
    m_unk_0x0C = PlatAudio::GetSndIDError();

    m_unk_0x10 = 1.0f;   // from "@3248"
    m_unk_0x14 = 1.0f;   // same as above
    m_unk_0x18 = 0.0f;   // from "@2159"
    m_unk_0x1C = 256.0f; // from "@1976"
    m_unk_0x20 = 1.0f;   // same as "@3248"
    m_unk_0x24 = 0.5f;   // from "@1977"
    m_unk_0x28 = 256.0f; // same as "@1976"

    m_unk_0x2C = false;
    m_unk_0x2D = false;
    m_unk_0x2E = true;
    m_unk_0x2F = false;
    m_unk_0x30 = false;
    m_unk_0x31 = false;
    m_unk_0x32 = false;
    m_unk_0x33 = false;
    m_unk_0x34 = false;

    m_unk_0x38 = 0.5f; // from "@1977"
    m_unk_0x3C = 0;
    m_physicsObject = NULL;

    // Clear both vector slots
    // m_unk_0x44.f = { 256.0f, 256.0f, 256.0f };
    // m_unk_0x50.f = { 256.0f, 256.0f, 256.0f };

    m_vecPtr_0x44 = NULL;
    m_vecPtr_0x50 = NULL;

    NL_VECTOR3_SET(m_vec_0x44, 256.0f, 256.0f, 256.0f);
    NL_VECTOR3_SET(m_vec_0x50, 256.0f, 256.0f, 256.0f);

    m_unk_0x5C = 0;
    m_unk_0x60 = 0;
    m_unk_0x64 = 0;
    m_unk_0x68 = -1;
    m_unk_0x6C = -1;
    m_unk_0x70 = 0;

    m_unk_0x74 = 0;
    m_unk_0x76 = 0;
    m_unk_0x78 = 0x2000; // li r0, 0x2000
    m_unk_0x7A = 1;
    m_unk_0x7B = 0;
    m_unk_0x7C = 1;
}

/**
 * Offset/Address/Size: 0x0 | 0x8014122C | size: 0x8
 */
u32 cGameSFX::GetClassType() const
{
    return m_classType;
}

// /**
//  * Offset/Address/Size: 0x0 | 0x80141234 | size: 0x8C
//  */
// void nlBSearch<nlSortedSlot<AudioStreamTrack::StreamTrack, 3>::EntryLookup<AudioStreamTrack::StreamTrack>, unsigned long>(const unsigned
// long&, nlSortedSlot<AudioStreamTrack::StreamTrack, 3>::EntryLookup<AudioStreamTrack::StreamTrack>*, int)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x801412C0 | size: 0x54
//  */
// void nlDeleteList<FadeAudioData>(FadeAudioData**)
// {
// }

// /**
//  * Offset/Address/Size: 0x54 | 0x80141314 | size: 0x9C
//  */
// void nlListRemoveElement<FadeAudioData>(FadeAudioData**, FadeAudioData*, FadeAudioData**)
// {
// }

// /**
//  * Offset/Address/Size: 0xF0 | 0x801413B0 | size: 0x28
//  */
// void nlListAddStart<FadeAudioData>(FadeAudioData**, FadeAudioData*, FadeAudioData**)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x801413D8 | size: 0x3C
//  */
// void nlWalkDLRing<DLListEntry<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL>,
// DLListContainerBase<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL,
// BasicSlotPool<DLListEntry<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL>>>>(DLListEntry<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL>*,
// DLListContainerBase<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL,
// BasicSlotPool<DLListEntry<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL>>>::*)(DLListEntry<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL>*))
// {
// }

// /**
//  * Offset/Address/Size: 0x3C | 0x80141414 | size: 0x3C
//  */
// void nlWalkDLRing<DLListEntry<GCAudioStreaming::StereoAudioStream*>, DLListContainerBase<GCAudioStreaming::StereoAudioStream*,
// BasicSlotPool<DLListEntry<GCAudioStreaming::StereoAudioStream*>>>>(DLListEntry<GCAudioStreaming::StereoAudioStream*>*,
// DLListContainerBase<GCAudioStreaming::StereoAudioStream*, BasicSlotPool<DLListEntry<GCAudioStreaming::StereoAudioStream*>>>*, void
// (DLListContainerBase<GCAudioStreaming::StereoAudioStream*,
// BasicSlotPool<DLListEntry<GCAudioStreaming::StereoAudioStream*>>>::*)(DLListEntry<GCAudioStreaming::StereoAudioStream*>*))
// {
// }

// /**
//  * Offset/Address/Size: 0x78 | 0x80141450 | size: 0x3C
//  */
// void nlWalkDLRing<DLListEntry<AudioStreamTrack::StreamTrack::QUEUED_STREAM>,
// DLListContainerBase<AudioStreamTrack::StreamTrack::QUEUED_STREAM,
// nlStaticArrayAllocator<DLListEntry<AudioStreamTrack::StreamTrack::QUEUED_STREAM>,
// 4>>>(DLListEntry<AudioStreamTrack::StreamTrack::QUEUED_STREAM>*, DLListContainerBase<AudioStreamTrack::StreamTrack::QUEUED_STREAM,
// nlStaticArrayAllocator<DLListEntry<AudioStreamTrack::StreamTrack::QUEUED_STREAM>, 4>>*, void
// (DLListContainerBase<AudioStreamTrack::StreamTrack::QUEUED_STREAM,
// nlStaticArrayAllocator<DLListEntry<AudioStreamTrack::StreamTrack::QUEUED_STREAM>,
// 4>>::*)(DLListEntry<AudioStreamTrack::StreamTrack::QUEUED_STREAM>*))
// {
// }

// /**
//  * Offset/Address/Size: 0xB4 | 0x8014148C | size: 0x3C
//  */
// void nlWalkDLRing<DLListEntry<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL>,
// WalkHelper<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL,
// DLListEntry<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL>,
// AudioStreamTrack::TrackManagerBase::FadeManager>>(DLListEntry<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL>*,
// WalkHelper<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL,
// DLListEntry<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL>, AudioStreamTrack::TrackManagerBase::FadeManager>*, void
// (WalkHelper<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL,
// DLListEntry<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL>,
// AudioStreamTrack::TrackManagerBase::FadeManager>::*)(DLListEntry<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL>*))
// {
// }

// /**
//  * Offset/Address/Size: 0xF0 | 0x801414C8 | size: 0x20
//  */
// void
// nlDLRingIsEnd<DLListEntry<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL>>(DLListEntry<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL>*,
// DLListEntry<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x110 | 0x801414E8 | size: 0x18
//  */
// void
// nlDLRingGetStart<DLListEntry<AudioStreamTrack::StreamTrack::QUEUED_STREAM>>(DLListEntry<AudioStreamTrack::StreamTrack::QUEUED_STREAM>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x128 | 0x80141500 | size: 0x18
//  */
// void
// nlDLRingGetStart<DLListEntry<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL>>(DLListEntry<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x80141518 | size: 0x1AC
//  */
// void CreateTrackMgr<3>()
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x801416C4 | size: 0x1F4
//  */
// void AudioStreamTrack::TrackManagerBase::~TrackManagerBase()
// {
// }

// /**
//  * Offset/Address/Size: 0x1F4 | 0x801418B8 | size: 0x204
//  */
// void AudioStreamTrack::TrackManager<3>::~TrackManager()
// {
// }

// /**
//  * Offset/Address/Size: 0x3F8 | 0x80141ABC | size: 0x1EC
//  */
// void AudioStreamTrack::TrackManager<3>::OnMasterVolumeChange(MasterVolume::VOLUME_GROUP)
// {
// }

// /**
//  * Offset/Address/Size: 0x5E4 | 0x80141CA8 | size: 0x54
//  */
// void AudioStreamTrack::TrackManager<3>::GetTrack(unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x638 | 0x80141CFC | size: 0x78
//  */
// void AudioStreamTrack::TrackManager<3>::StopAllTracks(unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x6B0 | 0x80141D74 | size: 0xF0
//  */
// void AudioStreamTrack::TrackManager<3>::Update(float)
// {
// }

// /**
//  * Offset/Address/Size: 0x7A0 | 0x80141E64 | size: 0x1D0
//  */
// void AudioStreamTrack::TrackManager<3>::DestroyAllTracks()
// {
// }

// /**
//  * Offset/Address/Size: 0x970 | 0x80142034 | size: 0x1AC
//  */
// void AudioStreamTrack::TrackManager<3>::CreateTrack(const char*, MasterVolume::VOLUME_GROUP)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x801421E0 | size: 0x14
//  */
// void nlStaticSortedSlot<AudioStreamTrack::StreamTrack, 3>::ExpandLookup()
// {
// }

// /**
//  * Offset/Address/Size: 0x14 | 0x801421F4 | size: 0xC
//  */
// void nlStaticSortedSlot<AudioStreamTrack::StreamTrack, 3>::FreeLookup()
// {
// }

// /**
//  * Offset/Address/Size: 0x20 | 0x80142200 | size: 0x10
//  */
// void nlStaticSortedSlot<AudioStreamTrack::StreamTrack, 3>::FreeEntry(AudioStreamTrack::StreamTrack*)
// {
// }

// /**
//  * Offset/Address/Size: 0x30 | 0x80142210 | size: 0x24
//  */
// void nlStaticSortedSlot<AudioStreamTrack::StreamTrack, 3>::GetNewEntry()
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x80142234 | size: 0x60
//  */
// void nlWalkRing<DLListEntry<GCAudioStreaming::StereoAudioStream*>, DLListContainerBase<GCAudioStreaming::StereoAudioStream*,
// BasicSlotPool<DLListEntry<GCAudioStreaming::StereoAudioStream*>>>>(DLListEntry<GCAudioStreaming::StereoAudioStream*>*,
// DLListContainerBase<GCAudioStreaming::StereoAudioStream*, BasicSlotPool<DLListEntry<GCAudioStreaming::StereoAudioStream*>>>*, void
// (DLListContainerBase<GCAudioStreaming::StereoAudioStream*,
// BasicSlotPool<DLListEntry<GCAudioStreaming::StereoAudioStream*>>>::*)(DLListEntry<GCAudioStreaming::StereoAudioStream*>*))
// {
// }

// /**
//  * Offset/Address/Size: 0x60 | 0x80142294 | size: 0x60
//  */
// void nlWalkRing<DLListEntry<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL>,
// DLListContainerBase<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL,
// BasicSlotPool<DLListEntry<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL>>>>(DLListEntry<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL>*,
// DLListContainerBase<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL,
// BasicSlotPool<DLListEntry<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL>>>*, void
// (DLListContainerBase<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL,
// BasicSlotPool<DLListEntry<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL>>>::*)(DLListEntry<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL>*))
// {
// }

// /**
//  * Offset/Address/Size: 0xC0 | 0x801422F4 | size: 0x60
//  */
// void nlWalkRing<DLListEntry<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL>,
// WalkHelper<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL,
// DLListEntry<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL>,
// AudioStreamTrack::TrackManagerBase::FadeManager>>(DLListEntry<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL>*,
// WalkHelper<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL,
// DLListEntry<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL>, AudioStreamTrack::TrackManagerBase::FadeManager>*, void
// (WalkHelper<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL,
// DLListEntry<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL>,
// AudioStreamTrack::TrackManagerBase::FadeManager>::*)(DLListEntry<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL>*))
// {
// }

// /**
//  * Offset/Address/Size: 0x120 | 0x80142354 | size: 0x60
//  */
// void nlWalkRing<DLListEntry<AudioStreamTrack::StreamTrack::QUEUED_STREAM>,
// DLListContainerBase<AudioStreamTrack::StreamTrack::QUEUED_STREAM,
// nlStaticArrayAllocator<DLListEntry<AudioStreamTrack::StreamTrack::QUEUED_STREAM>,
// 4>>>(DLListEntry<AudioStreamTrack::StreamTrack::QUEUED_STREAM>*, DLListContainerBase<AudioStreamTrack::StreamTrack::QUEUED_STREAM,
// nlStaticArrayAllocator<DLListEntry<AudioStreamTrack::StreamTrack::QUEUED_STREAM>, 4>>*, void
// (DLListContainerBase<AudioStreamTrack::StreamTrack::QUEUED_STREAM,
// nlStaticArrayAllocator<DLListEntry<AudioStreamTrack::StreamTrack::QUEUED_STREAM>,
// 4>>::*)(DLListEntry<AudioStreamTrack::StreamTrack::QUEUED_STREAM>*))
// {
// }

} // namespace Audio
