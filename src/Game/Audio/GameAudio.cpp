#include "Game/GameAudio.h"
#include "types.h"

inline bool IsVolGrpInRange(unsigned long sfxID, cGameSFX* pGameSFX)
{
    const int volGrp = pGameSFX->mpSFX[sfxID].volGrp;
    return (volGrp >= 5 && volGrp <= 19);
}

/**
 * Offset/Address/Size: 0x0 | 0x80151544 | size: 0x8D8
 */
void cGameSFX::UpdateAllTrackedSFX(float)
{
}

/**
 * Offset/Address/Size: 0x8D8 | 0x80151E1C | size: 0x9C
 */
void cGameSFX::StopPlayingAllTrackedSFX()
{
    // todo: implement
    FORCE_DONT_INLINE;
}

/**
 * Offset/Address/Size: 0x974 | 0x80151EB8 | size: 0x24C
 */
void cGameSFX::StopTrackedSFX(nlDLListIterator<SFXPlaySet*>*)
{
    FORCE_DONT_INLINE;
}

/**
 * Offset/Address/Size: 0xBC0 | 0x80152104 | size: 0xC4
 */
bool cGameSFX::StopTrackedSFX(SFXPlaySet* pPlaySet)
{
    FORCE_DONT_INLINE;

    // Not found
    return false;
}

/**
 * Offset/Address/Size: 0xC84 | 0x801521C8 | size: 0x150
 */
void cGameSFX::StopEmitter(SFXEmitter*, unsigned long)
{
}

/**
 * Offset/Address/Size: 0xDD4 | 0x80152318 | size: 0x12C
 */
void cGameSFX::Stop(unsigned long, cGameSFX::StopFlag)
{
}

/**
 * Offset/Address/Size: 0xF00 | 0x80152444 | size: 0x204
 */
void cGameSFX::KeepTrack(SFXEmitter*, const Audio::SoundAttributes&, unsigned long)
{
}

/**
 * Offset/Address/Size: 0x1104 | 0x80152648 | size: 0xACC
 */
unsigned long cGameSFX::Play(Audio::SoundAttributes& attributes)
{
    return 0;
}

/**
 * Offset/Address/Size: 0x1BD0 | 0x80153114 | size: 0xA8
 */
bool TrackedSFXPriorityCallback(SFXPlaySet* pPlaySet, unsigned long priority, cGameSFX* pGameSFX)
{
    if (pPlaySet->bIs3D != 0)
    {
        if (Audio::IsEmitterActive(pPlaySet->emitter) && pPlaySet->sfxPriority > priority)
        {
            return pGameSFX->StopTrackedSFX(pPlaySet);
        }
    }
    else
    {
        if (Audio::IsSFXPlaying(pPlaySet->voiceID) && pPlaySet->sfxPriority > priority)
        {
            return pGameSFX->StopTrackedSFX(pPlaySet);
        }
    }
    return true;
}

/**
 * Offset/Address/Size: 0x1C78 | 0x801531BC | size: 0x154
 */
void cGameSFX::SetPitchBendOnAllDialogueSFX(unsigned short)
{
}

/**
 * Offset/Address/Size: 0x1DCC | 0x80153310 | size: 0x194
 */
void cGameSFX::SetFilterFreqOnAllTrackedSFX(unsigned short)
{
}

/**
 * Offset/Address/Size: 0x1F60 | 0x801534A4 | size: 0x12C
 */
bool cGameSFX::ActivateFilterOnAllTrackedSFX(bool bActivate)
{
    return false;
}

/**
 * Offset/Address/Size: 0x208C | 0x801535D0 | size: 0x9C
 */
bool TrackedSFXFilterFreqTypeCheckCallback(unsigned long sfxID, cGameSFX* pGameSFX)
{
    if (pGameSFX->GetClassType() == WORLD && sfxID == 0xBB)
    {
        return false;
    }

    if (IsVolGrpInRange(sfxID, pGameSFX))
    {
        return false;
    }
    return true;
}

/**
 * Offset/Address/Size: 0x2128 | 0x8015366C | size: 0x30
 */
bool TrackedSFXPitchFreqTypeCheckCallback(unsigned long sfxID, cGameSFX* pGameSFX)
{
    const int volGrp = pGameSFX->mpSFX[sfxID].volGrp;
    return (bool)(volGrp >= 5 && volGrp <= 19);
}

/**
 * Offset/Address/Size: 0x2158 | 0x8015369C | size: 0x150
 */
bool cGameSFX::IsKeepingTrackOf(unsigned long sfxID, SFXPlaySet** pPlaySet)
{
    return false;
}

/**
 * Offset/Address/Size: 0x22A8 | 0x801537EC | size: 0x14
 */
float cGameSFX::GetSFXVolReverb(unsigned long index) const
{
    return mpSFX[index].fVolReverb;
}

/**
 * Offset/Address/Size: 0x22BC | 0x80153800 | size: 0x14
 */
float cGameSFX::GetSFXVol(unsigned long index) const
{
    return mpSFX[index].fVolume;
}

/**
 * Offset/Address/Size: 0x22D0 | 0x80153814 | size: 0x218
 */
void cGameSFX::SetSFX(SoundPropAccessor* pSoundPropAccessor)
{
}

/**
 * Offset/Address/Size: 0x24E8 | 0x80153A2C | size: 0x6C
 */
void cGameSFX::ShutdownPlaySet()
{
    FORCE_DONT_INLINE;
    mbCurPlaySetIsValid = false;
    StopPlayingAllTrackedSFX();

    nlWalkDLRing<DLListEntry<SFXPlaySet*>, nlDLListContainer<SFXPlaySet*> >(
        mpCurPlaySet.m_Head, &mpCurPlaySet, &nlDLListContainer<SFXPlaySet*>::DeleteEntry);

    mpCurPlaySet.m_Head = NULL;
}

/**
 * Offset/Address/Size: 0x2554 | 0x80153A98 | size: 0x4C
 */
void cGameSFX::DeInit()
{
    ShutdownPlaySet();
    mpSFX = NULL;
    mpSoundStrTable = 0;
    mbGroupFilterOn = false;
    muGroupFilterFreq = 0;
    muGroupPitch = 0x2000;
    mbInited = false;
}

/**
 * Offset/Address/Size: 0x25A0 | 0x80153AE4 | size: 0x10
 */
void cGameSFX::Init()
{
    mbInited = true;
    mbCurPlaySetIsValid = true;
}

/**
 * Offset/Address/Size: 0x25B0 | 0x80153AF4 | size: 0xB0
 */
cGameSFX::~cGameSFX()
{
    DeInit();
    if (mpCurPlaySet.m_Head != NULL)
    {
        nlWalkDLRing<DLListEntry<SFXPlaySet*>, nlDLListContainer<SFXPlaySet*> >(mpCurPlaySet.m_Head, &mpCurPlaySet, &nlDLListContainer<SFXPlaySet*>::DeleteEntry);
        mpCurPlaySet.m_Head = NULL;
    }
}

/**
 * Offset/Address/Size: 0x2660 | 0x80153BA4 | size: 0x4C
 */
cGameSFX::cGameSFX()
{
    mbInited = false;
    mNumSFX = 0;
    mNumSFXTypes = 0;
    mpSFX = NULL;
    mpCurPlaySet.m_Head = NULL;
    mbCurPlaySetIsValid = false;
    mfTrackedSFXCheckInterval = 0.0f;
    mpSoundStrTable = NULL;
    meClassType = GAME;
    mbGroupFilterOn = false;
    muGroupFilterFreq = 0;
    muGroupPitch = 0x2000;
}

// /**
//  * Offset/Address/Size: 0x0 | 0x80153BF0 | size: 0x24
//  */
// void DLListContainerBase<SFXPlaySet*, NewAdapter<DLListEntry<SFXPlaySet*>>>::DeleteEntry(DLListEntry<SFXPlaySet*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x80153C14 | size: 0x3C
//  */
// void nlWalkDLRing<DLListEntry<SFXPlaySet*>, DLListContainerBase<SFXPlaySet*,
// NewAdapter<DLListEntry<SFXPlaySet*>>>>(DLListEntry<SFXPlaySet*>*, DLListContainerBase<SFXPlaySet*,
// NewAdapter<DLListEntry<SFXPlaySet*>>>*, void (DLListContainerBase<SFXPlaySet*,
// NewAdapter<DLListEntry<SFXPlaySet*>>>::*)(DLListEntry<SFXPlaySet*>*))
// {
// }

// /**
//  * Offset/Address/Size: 0x3C | 0x80153C50 | size: 0x20
//  */
// void nlDLRingIsEnd<DLListEntry<SFXPlaySet*>>(DLListEntry<SFXPlaySet*>*, DLListEntry<SFXPlaySet*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x5C | 0x80153C70 | size: 0x18
//  */
// void nlDLRingGetStart<DLListEntry<SFXPlaySet*>>(DLListEntry<SFXPlaySet*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x74 | 0x80153C88 | size: 0x44
//  */
// void nlDLRingRemove<DLListEntry<SFXPlaySet*>>(DLListEntry<SFXPlaySet*>**, DLListEntry<SFXPlaySet*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0xB8 | 0x80153CCC | size: 0x38
//  */
// void nlDLRingAddStart<DLListEntry<SFXPlaySet*>>(DLListEntry<SFXPlaySet*>**, DLListEntry<SFXPlaySet*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x80153D04 | size: 0x60
//  */
// void nlWalkRing<DLListEntry<SFXPlaySet*>, DLListContainerBase<SFXPlaySet*,
// NewAdapter<DLListEntry<SFXPlaySet*>>>>(DLListEntry<SFXPlaySet*>*, DLListContainerBase<SFXPlaySet*,
// NewAdapter<DLListEntry<SFXPlaySet*>>>*, void (DLListContainerBase<SFXPlaySet*,
// NewAdapter<DLListEntry<SFXPlaySet*>>>::*)(DLListEntry<SFXPlaySet*>*))
// {
// }

// /**
//  * Offset/Address/Size: 0x68 | 0x80153DCC | size: 0x64
//  */
// void SlotPool<SFXPlaySet>::~SlotPool()
// {
// }
