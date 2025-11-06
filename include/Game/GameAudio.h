#ifndef _GAMEAUDIO_H_
#define _GAMEAUDIO_H_

#include "types.h"
#include "Game/Sys/audio.h"

#include "NL/nlMath.h"
#include "NL/nlDLRing.h"
#include "NL/nlDLListContainer.h"

enum eClassType
{
    GAME = 0,
    CHAR = 1,
    WORLD = 2,
};

// Forward declarations
namespace Audio
{
struct SoundAttributes;
}

// void TrackedSFXPriorityCallback(SFXPlaySet*, unsigned long, cGameSFX*);
// void TrackedSFXFilterFreqTypeCheckCallback(unsigned long, cGameSFX*);
// void TrackedSFXPitchFreqTypeCheckCallback(unsigned long, cGameSFX*);
// void nlDLRingIsEnd<DLListEntry<SFXPlaySet*>>(DLListEntry<SFXPlaySet*>*, DLListEntry<SFXPlaySet*>*);
// void nlDLRingGetStart<DLListEntry<SFXPlaySet*>>(DLListEntry<SFXPlaySet*>*);
// void nlDLRingRemove<DLListEntry<SFXPlaySet*>>(DLListEntry<SFXPlaySet*>**, DLListEntry<SFXPlaySet*>*);
// void nlDLRingAddStart<DLListEntry<SFXPlaySet*>>(DLListEntry<SFXPlaySet*>**, DLListEntry<SFXPlaySet*>*);

class SFXPlaySet;
class SFXEmitter;

class SoundPropAccessor
{
public:
    virtual ~SoundPropAccessor();

    /* 0x4 */ SoundProperties* mpSoundProp;
    /* 0x8 */ unsigned char mbIsReloaded;
}; // total size: 0xC

class cGameSFX
{
public:
    enum StopFlag
    {
        SFX_STOP_ALL = 0,
        SFX_STOP_FIRST = 1,
        SFX_STOP_OLDEST = 2,
    };

    cGameSFX();
    virtual ~cGameSFX();

    virtual void Init();
    virtual void DeInit();
    virtual void SetSFX(SoundPropAccessor*);
    virtual int Play(Audio::SoundAttributes&);
    virtual eClassType GetClassType() const { return meClassType; };

    void ShutdownPlaySet();
    float GetSFXVol(unsigned long) const;
    float GetSFXVolReverb(unsigned long) const;
    bool IsKeepingTrackOf(unsigned long, SFXPlaySet**);
    void ActivateFilterOnAllTrackedSFX(bool);
    void SetFilterFreqOnAllTrackedSFX(unsigned short);
    void SetPitchBendOnAllDialogueSFX(unsigned short);
    void KeepTrack(SFXEmitter*, const Audio::SoundAttributes&, unsigned long);
    void Stop(unsigned long, cGameSFX::StopFlag);
    void StopEmitter(SFXEmitter*, unsigned long);
    void StopTrackedSFX(SFXPlaySet*);
    void StopTrackedSFX(nlDLListIterator<SFXPlaySet*>*);
    void StopPlayingAllTrackedSFX();
    void UpdateAllTrackedSFX(float);

    /* 0x04 */ bool mbInited;
    /* 0x08 */ unsigned long mNumSFX;
    /* 0x0C */ unsigned long mNumSFXTypes;
    /* 0x10 */ SoundStrToIDNode* mpSFX;
    /* 0x14 */ nlDLListContainer<SFXPlaySet*> mpCurPlaySet;
    /* 0x1C */ bool mbCurPlaySetIsValid;
    /* 0x20 */ float mfTrackedSFXCheckInterval;
    /* 0x24 */ const char** mpSoundStrTable;
    /* 0x28 */ eClassType meClassType;
    /* 0x2C */ bool mbGroupFilterOn;
    /* 0x2E */ unsigned short muGroupFilterFreq;
    /* 0x30 */ unsigned short muGroupPitch;
}; // total size: 0x34

// class DLListContainerBase<SFXPlaySet*, NewAdapter<DLListEntry<SFXPlaySet*>>>
// {
// public:
//     void DeleteEntry(DLListEntry<SFXPlaySet*>*);
// };

// class nlWalkDLRing<DLListEntry<SFXPlaySet*>, DLListContainerBase<SFXPlaySet*,
// NewAdapter<DLListEntry<SFXPlaySet*>>>>(DLListEntry<SFXPlaySet*>*, DLListContainerBase<SFXPlaySet*,
// NewAdapter<DLListEntry<SFXPlaySet*>>>*, void (DLListContainerBase<SFXPlaySet*, NewAdapter<DLListEntry<SFXPlaySet*>>>
// {
// public:
//     void *)(DLListEntry<SFXPlaySet*>*));
// };

// class nlWalkRing<DLListEntry<SFXPlaySet*>, DLListContainerBase<SFXPlaySet*,
// NewAdapter<DLListEntry<SFXPlaySet*>>>>(DLListEntry<SFXPlaySet*>*, DLListContainerBase<SFXPlaySet*,
// NewAdapter<DLListEntry<SFXPlaySet*>>>*, void (DLListContainerBase<SFXPlaySet*, NewAdapter<DLListEntry<SFXPlaySet*>>>
// {
// public:
//     void *)(DLListEntry<SFXPlaySet*>*));
// };

// class SlotPool<SFXPlaySet>
// {
// public:
//     void ~SlotPool();
// };

#endif // _GAMEAUDIO_H_
