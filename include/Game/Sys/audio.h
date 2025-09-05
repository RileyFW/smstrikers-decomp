#ifndef _AUDIO_H_
#define _AUDIO_H_

#include "types.h"
#include "NL/nlMath.h"
#include "NL/plat/plataudio.h"

// void ReadVolGroupSettings();
// void nlDeleteList<FadeAudioData>(FadeAudioData**);
// void nlListRemoveElement<FadeAudioData>(FadeAudioData**, FadeAudioData*, FadeAudioData**);
// void nlListAddStart<FadeAudioData>(FadeAudioData**, FadeAudioData*, FadeAudioData**);

class PhysicsObject;

namespace Audio
{
// class SoundAttributes
struct SoundAttributes
{
    /* 0x00 */ s32 m_unk_0x00;
    /* 0x04 */ u32 m_soundType;
    /* 0x08 */ s32 m_unk_0x08;
    /* 0x0C */ s32 m_unk_0x0C;
    /* 0x10 */ f32 m_unk_0x10;
    /* 0x14 */ f32 m_unk_0x14;
    /* 0x18 */ f32 m_unk_0x18;
    /* 0x1C */ f32 m_unk_0x1C;
    /* 0x20 */ f32 m_unk_0x20;
    /* 0x24 */ f32 m_unk_0x24;
    /* 0x28 */ f32 m_unk_0x28;
    /* 0x2C */ bool m_unk_0x2C;
    /* 0x2D */ bool m_unk_0x2D;
    /* 0x2E */ bool m_unk_0x2E;
    /* 0x2F */ bool m_unk_0x2F;
    /* 0x30 */ bool m_unk_0x30;
    /* 0x31 */ bool m_unk_0x31;
    /* 0x32 */ bool m_unk_0x32;
    /* 0x33 */ bool m_unk_0x33;
    /* 0x34 */ bool m_unk_0x34;
    /* 0x35 */ char m_pad_0x35[3];
    /* 0x38 */ f32 m_unk_0x38;
    /* 0x3C */ s32 m_unk_0x3C;
    /* 0x40 */ PhysicsObject* m_physicsObject;

    union
    {
        nlVector3 m_vec_0x44;
        const nlVector3* m_vecPtr_0x44;
    };
    union
    {
        nlVector3 m_vec_0x50;
        const nlVector3* m_vecPtr_0x50;
    };

    /* 0x5C */ s32 m_unk_0x5C;
    /* 0x60 */ s32 m_unk_0x60;
    /* 0x64 */ s32 m_unk_0x64;
    /* 0x68 */ s32 m_unk_0x68;
    /* 0x6C */ s32 m_unk_0x6C;
    /* 0x70 */ s32 m_unk_0x70;
    /* 0x74 */ s8 m_unk_0x74;
    /* 0x75 */ char m_pad_0x75[1];
    /* 0x76 */ s16 m_unk_0x76;
    /* 0x78 */ s16 m_unk_0x78;
    /* 0x7A */ s8 m_unk_0x7A;
    /* 0x7B */ s8 m_unk_0x7B;
    /* 0x7C */ s8 m_unk_0x7C;

    void UseStationaryPosVector(const nlVector3&);
    void UseVectors(const nlVector3&, const nlVector3&);
    void UseVectorPtrs(const nlVector3*, const nlVector3*);
    void UsePhysObj(PhysicsObject*);
    void SetSoundType(unsigned long, bool);
    void Init();
};

class MasterVolume
{
public:
    enum VOLUME_GROUP
    {
        VOLUME_GROUP_0 = 0,
    };

    float GetVoiceVolume();
    void SetVoiceVolume(float, int);
    void SetVolume(VOLUME_GROUP, float);
    void GetVolume(VOLUME_GROUP);
};

// void MasterVolume::GetVoiceVolume();
// void MasterVolume::SetVoiceVolume(float, int);
// void MasterVolume::SetVolume(Audio::MasterVolume::VOLUME_GROUP, float);
// void MasterVolume::GetVolume(Audio::MasterVolume::VOLUME_GROUP);

// void FadeFilterFromCurrentToZero();
// void FadeFilterToFullStrength();
// void PitchBend(float, float, float, float);
// void FadeFilter(float, float, float, float);
void ClearFadeData();
bool IsEmitterActive(SFXEmitter*);
u32 GetEmitterVoiceID(SFXEmitter*);
void Remove3DSFXEmitter(SFXEmitter*);
void Add3DSFXEmitter(const EmitterStartInfo&);
void GetFreeEmitter(unsigned long&);
SFXEmitter* GetEmitter(unsigned long);
void SetListenerActive(bool);
bool IsListenerActive();
void SetOutputMode(MusyXOutputType);
// void SetPitchBendOnSFX(unsigned long, unsigned short);
// void SetFilterFreqOnSFX(unsigned long, unsigned short);
// void ActivateFilterOnSFX(unsigned long, bool);
// void SetPitchBendOnAllDialogueSFX(unsigned short);
// void ActivateFilterOnAllCurrentSFX(bool);
// void SetVolGroupVolume(int, float, int);
// void SetSFXVolumeGroup(unsigned long, int);
// void SetSFXVolume(unsigned long, float);
// void Update3DSFXEmitters();
// void UpdateFades(float);
void Update(float);
int GetSndIDError();
// void IsSFXPlaying(unsigned long);
// void StopSFX(unsigned long);
// void PlaySFXEventFromScript(const SoundEventData&, const char*, float, float);
// void StopCharSFXbyStr(const char*, NisCharacterClass);
// void StopWorldSFXbyStr(const char*);
// void PlayCharSFXbyStr(const char*, NisCharacterClass, float, float, bool, bool, const nlVector3*, const nlVector3*, unsigned long*);
// void PlayWorldSFXbyStr(const char*, float, float, bool, bool, const nlVector3*, const nlVector3*, unsigned long*);
// void RemoveDelayedSFX(unsigned long);
// void IsDelayedCharSFX(unsigned long, cGameSFX*);
// void AddDelayedSFX(const Audio::SoundAttributes&, unsigned long, float, float, cGameSFX*);
// void PlaySFXbyID(const Audio::SoundAttributes&, unsigned long, float, float, int);
// void PlaySFX(const SFXStartInfo&);
// void GetAudioTimer();
void Shutdown();
void Silence();
void ResetForNewGame();
void ResetPauseStatus();
void UnloadWorldSFX();
bool IsWorldSFXLoaded();
void LoadWorldSFX();
void UnloadInGameSFX();
void LoadInGameSFX();
bool IsInited();
// void ShutdownReverb();
// void InitializeReverb(eStadiumID, unsigned char);
// void Initialize(bool);
// void CreateTrackMgr<3>();
}; // namespace Audio

// class cGameSFX
// {
// public:
//     void GetClassType() const;
// };

// class nlBSearch<nlSortedSlot<AudioStreamTrack
// {
// public:
//     void StreamTrack, 3>::EntryLookup<AudioStreamTrack::StreamTrack>, unsigned long>(const unsigned long&,
//     nlSortedSlot<AudioStreamTrack::StreamTrack, 3>::EntryLookup<AudioStreamTrack::StreamTrack>*, int);
// };

// class nlWalkDLRing<DLListEntry<AudioStreamTrack
// {
// public:
//     void TrackManagerBase::FadeManager::STREAM_FADE_CTRL>,
//     DLListContainerBase<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL,
//     BasicSlotPool<DLListEntry<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL>>>>(DLListEntry<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL>*,
//     DLListContainerBase<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL,
//     BasicSlotPool<DLListEntry<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL>>>*, void
//     (DLListContainerBase<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL,
//     BasicSlotPool<DLListEntry<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL>>>::*)(DLListEntry<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL>*));
//     void StreamTrack::QUEUED_STREAM>, DLListContainerBase<AudioStreamTrack::StreamTrack::QUEUED_STREAM,
//     nlStaticArrayAllocator<DLListEntry<AudioStreamTrack::StreamTrack::QUEUED_STREAM>,
//     4>>>(DLListEntry<AudioStreamTrack::StreamTrack::QUEUED_STREAM>*, DLListContainerBase<AudioStreamTrack::StreamTrack::QUEUED_STREAM,
//     nlStaticArrayAllocator<DLListEntry<AudioStreamTrack::StreamTrack::QUEUED_STREAM>, 4>>*, void
//     (DLListContainerBase<AudioStreamTrack::StreamTrack::QUEUED_STREAM,
//     nlStaticArrayAllocator<DLListEntry<AudioStreamTrack::StreamTrack::QUEUED_STREAM>,
//     4>>::*)(DLListEntry<AudioStreamTrack::StreamTrack::QUEUED_STREAM>*)); void TrackManagerBase::FadeManager::STREAM_FADE_CTRL>,
//     WalkHelper<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL,
//     DLListEntry<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL>,
//     AudioStreamTrack::TrackManagerBase::FadeManager>>(DLListEntry<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL>*,
//     WalkHelper<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL,
//     DLListEntry<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL>, AudioStreamTrack::TrackManagerBase::FadeManager>*,
//     void (WalkHelper<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL,
//     DLListEntry<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL>,
//     AudioStreamTrack::TrackManagerBase::FadeManager>::*)(DLListEntry<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL>*));
// };

// class nlWalkDLRing<DLListEntry<GCAudioStreaming
// {
// public:
//     void StereoAudioStream*>, DLListContainerBase<GCAudioStreaming::StereoAudioStream*,
//     BasicSlotPool<DLListEntry<GCAudioStreaming::StereoAudioStream*>>>>(DLListEntry<GCAudioStreaming::StereoAudioStream*>*,
//     DLListContainerBase<GCAudioStreaming::StereoAudioStream*, BasicSlotPool<DLListEntry<GCAudioStreaming::StereoAudioStream*>>>*, void
//     (DLListContainerBase<GCAudioStreaming::StereoAudioStream*,
//     BasicSlotPool<DLListEntry<GCAudioStreaming::StereoAudioStream*>>>::*)(DLListEntry<GCAudioStreaming::StereoAudioStream*>*));
// };

// class nlDLRingIsEnd<DLListEntry<AudioStreamTrack
// {
// public:
//     void
//     TrackManagerBase::FadeManager::STREAM_FADE_CTRL>>(DLListEntry<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL>*,
//     DLListEntry<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL>*);
// };

// class nlDLRingGetStart<DLListEntry<AudioStreamTrack
// {
// public:
//     void StreamTrack::QUEUED_STREAM>>(DLListEntry<AudioStreamTrack::StreamTrack::QUEUED_STREAM>*);
//     void
//     TrackManagerBase::FadeManager::STREAM_FADE_CTRL>>(DLListEntry<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL>*);
// };

// class AudioStreamTrack
// {
// public:
//     void TrackManagerBase::~TrackManagerBase();
//     void TrackManager<3>::~TrackManager();
//     void TrackManager<3>::OnMasterVolumeChange(Audio::MasterVolume::VOLUME_GROUP);
//     void TrackManager<3>::GetTrack(unsigned long);
//     void TrackManager<3>::StopAllTracks(unsigned long);
//     void TrackManager<3>::Update(float);
//     void TrackManager<3>::DestroyAllTracks();
//     void TrackManager<3>::CreateTrack(const char*, Audio::MasterVolume::VOLUME_GROUP);
// };

// class nlStaticSortedSlot<AudioStreamTrack
// {
// public:
//     void StreamTrack, 3>::ExpandLookup();
//     void StreamTrack, 3>::FreeLookup();
//     void StreamTrack, 3>::FreeEntry(AudioStreamTrack::StreamTrack*);
//     void StreamTrack, 3>::GetNewEntry();
// };

// class nlWalkRing<DLListEntry<GCAudioStreaming
// {
// public:
//     void StereoAudioStream*>, DLListContainerBase<GCAudioStreaming::StereoAudioStream*,
//     BasicSlotPool<DLListEntry<GCAudioStreaming::StereoAudioStream*>>>>(DLListEntry<GCAudioStreaming::StereoAudioStream*>*,
//     DLListContainerBase<GCAudioStreaming::StereoAudioStream*, BasicSlotPool<DLListEntry<GCAudioStreaming::StereoAudioStream*>>>*, void
//     (DLListContainerBase<GCAudioStreaming::StereoAudioStream*,
//     BasicSlotPool<DLListEntry<GCAudioStreaming::StereoAudioStream*>>>::*)(DLListEntry<GCAudioStreaming::StereoAudioStream*>*));
// };

// class nlWalkRing<DLListEntry<AudioStreamTrack
// {
// public:
//     void TrackManagerBase::FadeManager::STREAM_FADE_CTRL>,
//     DLListContainerBase<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL,
//     BasicSlotPool<DLListEntry<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL>>>>(DLListEntry<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL>*,
//     DLListContainerBase<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL,
//     BasicSlotPool<DLListEntry<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL>>>*, void
//     (DLListContainerBase<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL,
//     BasicSlotPool<DLListEntry<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL>>>::*)(DLListEntry<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL>*));
//     void TrackManagerBase::FadeManager::STREAM_FADE_CTRL>, WalkHelper<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL,
//     DLListEntry<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL>,
//     AudioStreamTrack::TrackManagerBase::FadeManager>>(DLListEntry<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL>*,
//     WalkHelper<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL,
//     DLListEntry<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL>, AudioStreamTrack::TrackManagerBase::FadeManager>*,
//     void (WalkHelper<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL,
//     DLListEntry<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL>,
//     AudioStreamTrack::TrackManagerBase::FadeManager>::*)(DLListEntry<AudioStreamTrack::TrackManagerBase::FadeManager::STREAM_FADE_CTRL>*));
//     void StreamTrack::QUEUED_STREAM>, DLListContainerBase<AudioStreamTrack::StreamTrack::QUEUED_STREAM,
//     nlStaticArrayAllocator<DLListEntry<AudioStreamTrack::StreamTrack::QUEUED_STREAM>,
//     4>>>(DLListEntry<AudioStreamTrack::StreamTrack::QUEUED_STREAM>*, DLListContainerBase<AudioStreamTrack::StreamTrack::QUEUED_STREAM,
//     nlStaticArrayAllocator<DLListEntry<AudioStreamTrack::StreamTrack::QUEUED_STREAM>, 4>>*, void
//     (DLListContainerBase<AudioStreamTrack::StreamTrack::QUEUED_STREAM,
//     nlStaticArrayAllocator<DLListEntry<AudioStreamTrack::StreamTrack::QUEUED_STREAM>,
//     4>>::*)(DLListEntry<AudioStreamTrack::StreamTrack::QUEUED_STREAM>*));
// };

#endif // _AUDIO_H_
