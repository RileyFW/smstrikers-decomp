#ifndef _GAMEAUDIO_H_
#define _GAMEAUDIO_H_

#include "types.h"
#include "Game/Sys/audio.h"

#include "NL/nlMath.h"
#include "NL/nlDLRing.h"

// void TrackedSFXPriorityCallback(SFXPlaySet*, unsigned long, cGameSFX*);
// void TrackedSFXFilterFreqTypeCheckCallback(unsigned long, cGameSFX*);
// void TrackedSFXPitchFreqTypeCheckCallback(unsigned long, cGameSFX*);
// void nlDLRingIsEnd<DLListEntry<SFXPlaySet*>>(DLListEntry<SFXPlaySet*>*, DLListEntry<SFXPlaySet*>*);
// void nlDLRingGetStart<DLListEntry<SFXPlaySet*>>(DLListEntry<SFXPlaySet*>*);
// void nlDLRingRemove<DLListEntry<SFXPlaySet*>>(DLListEntry<SFXPlaySet*>**, DLListEntry<SFXPlaySet*>*);
// void nlDLRingAddStart<DLListEntry<SFXPlaySet*>>(DLListEntry<SFXPlaySet*>**, DLListEntry<SFXPlaySet*>*);

class SFXPlaySet;
class SFXEmitter;

struct SoundPropAccessor
{
};

class cGameSFX
{
public:
    cGameSFX();
    virtual ~cGameSFX();

    virtual void Init();
    virtual void DeInit();
    virtual void SetSFX(SoundPropAccessor*);
    virtual int Play(Audio::SoundAttributes&);
    virtual u32 GetClassType() const;

    enum StopFlag
    {
        StopFlag_0 = 0,
        StopFlag_1, // Immediate?
    };

    void ShutdownPlaySet();
    void GetSFXVol(unsigned long) const;
    void GetSFXVolReverb(unsigned long) const;
    void IsKeepingTrackOf(unsigned long, SFXPlaySet**);
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

    /* 0x04 */ bool m_unk_0x04;
    /* 0x05 */ char pad5[3];
    /* 0x08 */ u32 m_unk_0x08;
    /* 0x0C */ u32 m_unk_0x0C;
    /* 0x10 */ SFXEmitter* m_unk_0x10;
    /* 0x14 */ u32 m_unk_0x14;
    /* 0x18 */ DLListEntry<SFXPlaySet*>* m_unk_0x18;
    /* 0x1C */ bool m_unk_0x1C;
    /* 0x1D */ char pad1D[3];
    /* 0x20 */ f32 m_unk_0x20;
    /* 0x24 */ s32 m_unk_0x24;
    /* 0x28 */ s32 m_classType;
    /* 0x2C */ bool m_unk_0x2C;
    /* 0x2D */ char pad2D[1];
    /* 0x2E */ u16 m_unk_0x2E;
    /* 0x30 */ u16 m_unk_0x30;

    // /* 0x04 */ u8 m_padding_0x04[0x24];
    // /* 0x28 */ u32 m_classType;

    /* 0x32 */ u8 m_padding_0x2C[0x335E]; // obscure padding
};

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
