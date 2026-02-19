#include "Game/GameAudio.h"
#include "Game/Sys/debug.h"
#include "NL/nlString.h"
#include "types.h"

/**
 * Offset/Address/Size: 0x2128 | 0x8015366C | size: 0x30
 */
bool TrackedSFXPitchFreqTypeCheckCallback(unsigned long sfxID, cGameSFX* pGameSFX)
{
    const int volGrp = pGameSFX->mpSFX[sfxID].volGrp;
    return (bool)(volGrp >= 5 && volGrp <= 19);
}

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
    if (!mbCurPlaySetIsValid)
    {
        return;
    }

    DLListEntry<SFXPlaySet*>* start = nlDLRingGetStart(mpCurPlaySet.m_Head);
    DLListEntry<SFXPlaySet*>* head = mpCurPlaySet.m_Head;
    DLListEntry<SFXPlaySet*>* current = start;

    while (current != NULL)
    {
        struct
        {
            DLListEntry<SFXPlaySet*>* m_head;
            DLListEntry<SFXPlaySet*>* m_current;
        } iter;

        iter.m_head = head;
        iter.m_current = current;

        if (nlDLRingIsEnd(head, current) || current == NULL)
        {
            current = NULL;
        }
        else
        {
            current = current->m_next;
        }

        StopTrackedSFX(reinterpret_cast<nlDLListIterator<SFXPlaySet*>*>(&iter));
    }
}

/**
 * Offset/Address/Size: 0x974 | 0x80151EB8 | size: 0x24C
 * TODO: ~98% match - r28/r29 register allocation swapped for pPlaySet/pEmitter
 */
bool cGameSFX::StopTrackedSFX(nlDLListIterator<SFXPlaySet*>* pIterator)
{
    struct EntryIterator
    {
        DLListEntry<SFXPlaySet*>* m_head;    // Not used, but part of caller's struct
        DLListEntry<SFXPlaySet*>* m_current; // The entry we're operating on
    };
    EntryIterator* pIter = reinterpret_cast<EntryIterator*>(pIterator);

    DLListEntry<SFXPlaySet*>* pEntry = pIter->m_current;
    if (pEntry == NULL)
    {
        return false;
    }
    SFXPlaySet* pPlaySet = pEntry->m_data;

    if (!(pPlaySet->delay >= 0.0f))
    {
        int delayedIndex = Audio::IsDelayedCharSFX(pPlaySet->type, this);
        if (delayedIndex == -1)
        {
            goto cleanup_list;
        }
        Audio::RemoveDelayedSFX(delayedIndex);
        return true;
    }

    if (pPlaySet->bIs3D != 0)
    {
        SFXEmitter* pEmitter = pPlaySet->emitter;
        if (pEmitter != NULL && pEmitter->soundType == pPlaySet->type && pEmitter->pOwner == this)
        {
            bool removed = Audio::Remove3DSFXEmitter(pEmitter);
            pEmitter->bIsStopping = true;

            if (!removed)
            {
                goto cleanup_list;
            }

            if (Audio::IsEmitterActive(pEmitter))
            {
                goto cleanup_list;
            }

            pEmitter->bKeepTrack = true;
            pEmitter->soundType = (unsigned long)-1;
            pEmitter->fTimeStamp = -1.0f;
            pEmitter->bIsStopping = false;
            pEmitter->bInUse = false;
            pEmitter->bIsFilterOn = false;
            pEmitter->m_unk_0x5F = false;
            pEmitter->pPhysObj = NULL;
            pEmitter->pOwner = NULL;
            pEmitter->pos.pvPos = NULL;
            pEmitter->dir.pvDir = NULL;
            pEmitter->pos.vPos.f.x = 0.0f;
            pEmitter->pos.vPos.f.y = 0.0f;
            pEmitter->pos.vPos.f.z = 0.0f;
            pEmitter->dir.vDir.f.x = 0.0f;
            pEmitter->dir.vDir.f.y = 0.0f;
            pEmitter->dir.vDir.f.z = 0.0f;
            pEmitter->posUpdateMethod = NONE;

            // Free MIDI controller info
            if (pEmitter->pMIDIControllerInfo != NULL)
            {
                if (pEmitter->pMIDIControllerInfo->paraArray != NULL)
                {
                    delete[] pEmitter->pMIDIControllerInfo->paraArray;
                }
                delete pEmitter->pMIDIControllerInfo;
            }
            pEmitter->pMIDIControllerInfo = NULL;
            goto cleanup_list;
        }
        // Emitter not valid, try stopping by voice ID
        if (pPlaySet->voiceID != Audio::GetSndIDError())
        {
            Audio::StopSFX(pPlaySet->voiceID);
            goto cleanup_list;
        }
        nlPrintf("Stopping stop sound type %d\n which no longer has a valid emitter.\n", pPlaySet->type);
        goto cleanup_list;
    }
    else
    {
        // 2D SFX - stop by voice ID
        Audio::StopSFX(pPlaySet->voiceID);
    }

cleanup_list:
    // Update iterator and remove entry from list
    DLListEntry<SFXPlaySet*>* pNextEntry = pIter->m_current;
    DLListEntry<SFXPlaySet*>* pHead = mpCurPlaySet.m_Head;
    pPlaySet = pNextEntry->m_data;

    // Advance iterator
    if (nlDLRingIsEnd(pHead, pNextEntry) || pIter->m_current == NULL)
    {
        pIter->m_current = NULL;
    }
    else
    {
        pIter->m_current = pIter->m_current->m_next;
    }

    // Remove from list
    nlDLRingRemove(&mpCurPlaySet.m_Head, pNextEntry);
    delete pNextEntry;

    // Reset play set
    pPlaySet->type = (unsigned long)-1;
    pPlaySet->voiceID = Audio::GetSndIDError();
    pPlaySet->bIs3D = false;
    pPlaySet->emitter = NULL;
    pPlaySet->delay = -1.0f;
    pPlaySet->timeStamp = -1.0f;
    pPlaySet->sfxPriority = 0;
    pPlaySet->groupPriority = -1;

    // Return to free pool
    SlotPoolEntry* pFreeEntry = (SlotPoolEntry*)pPlaySet;
    pFreeEntry->m_next = SFXPlaySet::m_TrackedSFXSlotPool.m_FreeList;
    SFXPlaySet::m_TrackedSFXSlotPool.m_FreeList = pFreeEntry;

    return true;
}

/**
 * Offset/Address/Size: 0xBC0 | 0x80152104 | size: 0xC4
 */
bool cGameSFX::StopTrackedSFX(SFXPlaySet* pPlaySet)
{
    if (!mbCurPlaySetIsValid)
    {
        return true;
    }

    struct
    {
        DLListEntry<SFXPlaySet*>* m_head;
        DLListEntry<SFXPlaySet*>* m_current;
    } iter;

    DLListEntry<SFXPlaySet*>* start = nlDLRingGetStart(mpCurPlaySet.m_Head);
    iter.m_head = mpCurPlaySet.m_Head;
    iter.m_current = start;

    while (iter.m_current != NULL)
    {
        if (pPlaySet == iter.m_current->m_data)
        {
            return StopTrackedSFX(reinterpret_cast<nlDLListIterator<SFXPlaySet*>*>(&iter));
        }

        if (nlDLRingIsEnd(iter.m_head, iter.m_current) || iter.m_current == NULL)
        {
            iter.m_current = NULL;
        }
        else
        {
            iter.m_current = iter.m_current->m_next;
        }
    }

    return false;
}

/**
 * Offset/Address/Size: 0xC84 | 0x801521C8 | size: 0x150
 */
void cGameSFX::StopEmitter(SFXEmitter* pSFXEmitter, unsigned long type)
{
    if (pSFXEmitter == NULL)
    {
        return;
    }

    for (s32 i = 0; i < 0x40; i++)
    {
        SFXEmitter* pEmitter = Audio::GetEmitter(i);
        if (pEmitter == NULL || pSFXEmitter != pEmitter)
        {
            continue;
        }

        if ((type != 0 && pSFXEmitter->soundType != type) || pSFXEmitter->pOwner != this)
        {
            tDebugPrintManager::Print(DC_SOUND, "StopEmitter - emitter found but wrong owner or type\n");
            return;
        }

        // Match found
        pSFXEmitter->bIsStopping = true;
        unsigned char bResult = Audio::Remove3DSFXEmitter(pSFXEmitter);
        if (!bResult)
        {
            return;
        }

        pSFXEmitter->bKeepTrack = true;
        pSFXEmitter->soundType = (unsigned long)-1;
        pSFXEmitter->fTimeStamp = -1.0f;
        pSFXEmitter->bIsStopping = false;
        pSFXEmitter->bInUse = false;
        pSFXEmitter->bIsFilterOn = false;
        pSFXEmitter->m_unk_0x5F = false;
        pSFXEmitter->pPhysObj = NULL;
        pSFXEmitter->pOwner = NULL;
        pSFXEmitter->pos.pvPos = NULL;
        pSFXEmitter->dir.pvDir = NULL;
        pSFXEmitter->pos.vPos.f.x = 0.0f;
        pSFXEmitter->pos.vPos.f.y = 0.0f;
        pSFXEmitter->pos.vPos.f.z = 0.0f;
        pSFXEmitter->dir.vDir.f.x = 0.0f;
        pSFXEmitter->dir.vDir.f.y = 0.0f;
        pSFXEmitter->dir.vDir.f.z = 0.0f;
        pSFXEmitter->posUpdateMethod = (PosUpdateMethod)0;

        if (pSFXEmitter->pMIDIControllerInfo != NULL)
        {
            if (pSFXEmitter->pMIDIControllerInfo->paraArray != NULL)
            {
                delete[] pSFXEmitter->pMIDIControllerInfo->paraArray;
            }
            delete pSFXEmitter->pMIDIControllerInfo;
        }
        pSFXEmitter->pMIDIControllerInfo = NULL;
        return;
    }
}

/**
 * Offset/Address/Size: 0xDD4 | 0x80152318 | size: 0x12C
 */
void cGameSFX::Stop(unsigned long soundID, cGameSFX::StopFlag stopFlag)
{
    if (!mbCurPlaySetIsValid)
    {
        return;
    }

    f32 oldestTimeStamp = -1.0f;

    struct
    {
        DLListEntry<SFXPlaySet*>* m_head;
        DLListEntry<SFXPlaySet*>* m_current;
    } bestIter;

    DLListEntry<SFXPlaySet*>* start1 = nlDLRingGetStart(mpCurPlaySet.m_Head);
    bestIter.m_head = mpCurPlaySet.m_Head;
    bestIter.m_current = start1;

    struct
    {
        DLListEntry<SFXPlaySet*>* m_head;
        DLListEntry<SFXPlaySet*>* m_current;
    } iter;

    DLListEntry<SFXPlaySet*>* start2 = nlDLRingGetStart(bestIter.m_head);
    DLListEntry<SFXPlaySet*>* loopHead = mpCurPlaySet.m_Head;
    DLListEntry<SFXPlaySet*>* current = start2;

    while (current != NULL)
    {
        SFXPlaySet* playSet = current->m_data;

        iter.m_head = loopHead;
        iter.m_current = current;

        if (nlDLRingIsEnd(loopHead, current) || current == NULL)
        {
            current = NULL;
        }
        else
        {
            current = current->m_next;
        }

        if (playSet->type != soundID)
        {
            continue;
        }

        if (stopFlag == SFX_STOP_OLDEST)
        {
            if (oldestTimeStamp != -1.0f && !(playSet->timeStamp < oldestTimeStamp))
            {
                continue;
            }
            oldestTimeStamp = playSet->timeStamp;
            bestIter.m_head = iter.m_head;
            bestIter.m_current = iter.m_current;
            continue;
        }

        StopTrackedSFX(reinterpret_cast<nlDLListIterator<SFXPlaySet*>*>(&iter));

        if (stopFlag != SFX_STOP_ALL)
        {
            break;
        }
    }

    if (stopFlag == SFX_STOP_OLDEST && oldestTimeStamp != -1.0f)
    {
        StopTrackedSFX(reinterpret_cast<nlDLListIterator<SFXPlaySet*>*>(&bestIter));
    }
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
bool cGameSFX::SetPitchBendOnAllDialogueSFX(unsigned short pitch)
{
    bool result;

    if (pitch > 0x3FFF)
    {
        pitch = 0x3FFF;
    }

    if (!mbCurPlaySetIsValid)
    {
        result = true;
        goto epilogue;
    }

    {
        SFXPlaySet* pPlaySet;
        DLListEntry<SFXPlaySet*>* start = nlDLRingGetStart(mpCurPlaySet.m_Head);
        DLListEntry<SFXPlaySet*>* head = mpCurPlaySet.m_Head;
        DLListEntry<SFXPlaySet*>* current = start;
        unsigned short clampedPitch = (unsigned short)pitch;

        while (current != NULL)
        {
            pPlaySet = current->m_data;

            if (nlDLRingIsEnd(head, current) || current == NULL)
            {
                current = NULL;
            }
            else
            {
                current = current->m_next;
            }

            if (pPlaySet->type == (unsigned long)-1)
            {
                continue;
            }

            if (TrackedSFXPitchFreqTypeCheckCallback != NULL)
            {
                if (!TrackedSFXPitchFreqTypeCheckCallback(pPlaySet->type, this))
                {
                    continue;
                }
            }

            if (pPlaySet->bIs3D)
            {
                if (!Audio::IsEmitterActive(pPlaySet->emitter))
                {
                    continue;
                }
                pPlaySet->voiceID = Audio::GetEmitterVoiceID(pPlaySet->emitter);
            }

            if (pPlaySet->voiceID == Audio::GetSndIDError())
            {
                continue;
            }

            if (!Audio::IsSFXPlaying(pPlaySet->voiceID))
            {
                continue;
            }

            if (pPlaySet->pitch == clampedPitch)
            {
                continue;
            }

            pPlaySet->pitch = clampedPitch;
            Audio::SetPitchBendOnSFX(pPlaySet->voiceID, clampedPitch);
        }
    }

    result = true;

epilogue:
    muGroupPitch = pitch;
    return result;
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
    bool bParam = bActivate;
    u8 bActivateU8 = (u8)bActivate;
    u32 bNeg = (u32)(-(s32)bActivateU8);
    u32 bOr = bNeg | bActivateU8;
    u32 bNorm = bOr >> 31;
    bool result;

    if (!mbCurPlaySetIsValid)
    {
        result = true;
        goto epilogue;
    }

    {
        SFXPlaySet* pPlaySet;
        bool filterActive;
        DLListEntry<SFXPlaySet*>* start = nlDLRingGetStart(mpCurPlaySet.m_Head);
        DLListEntry<SFXPlaySet*>* head = mpCurPlaySet.m_Head;
        DLListEntry<SFXPlaySet*>* current = start;

        while (current != NULL)
        {
            pPlaySet = current->m_data;

            if (nlDLRingIsEnd(head, current) || current == NULL)
            {
                current = NULL;
            }
            else
            {
                current = current->m_next;
            }

            if (pPlaySet->type == (unsigned long)-1)
            {
                continue;
            }

            filterActive = false;
            if (bNorm == 1)
            {
                filterActive = true;
            }

            if (pPlaySet->bIs3D)
            {
                if (!Audio::IsEmitterActive(pPlaySet->emitter))
                {
                    continue;
                }
                pPlaySet->voiceID = Audio::GetEmitterVoiceID(pPlaySet->emitter);
            }

            unsigned long sndIDError = Audio::GetSndIDError();
            if (pPlaySet->voiceID != sndIDError)
            {
                if (Audio::IsSFXPlaying(pPlaySet->voiceID))
                {
                    Audio::ActivateFilterOnSFX(pPlaySet->voiceID, filterActive);
                }
            }
        }
    }

    result = true;

epilogue:
    if (bParam)
    {
        mbGroupFilterOn = true;
    }
    else
    {
        mbGroupFilterOn = false;
    }

    return result;
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
 * Offset/Address/Size: 0x2158 | 0x8015369C | size: 0x150
 */
bool cGameSFX::IsKeepingTrackOf(unsigned long type, SFXPlaySet** pGrabTrackedSFX)
{
    if (pGrabTrackedSFX != NULL) {
        *pGrabTrackedSFX = NULL;
    }

    if (!mbCurPlaySetIsValid) {
        return false;
    }

    DLListEntry<SFXPlaySet*>* head = mpCurPlaySet.m_Head;
    DLListEntry<SFXPlaySet*>* current = nlDLRingGetStart(head);
    head = mpCurPlaySet.m_Head;

    while (current != NULL) {
        SFXPlaySet* pTrackedSFX = current->m_data;

        if (pTrackedSFX->type == type) {
            if (pTrackedSFX->bIs3D && pTrackedSFX->emitter != NULL && Audio::IsEmitterActive(pTrackedSFX->emitter)) {
                pTrackedSFX->voiceID = Audio::GetEmitterVoiceID(pTrackedSFX->emitter);
            }

            if ((pTrackedSFX->delay < 0.0f && pTrackedSFX->bIs3D && pTrackedSFX->voiceID == (unsigned long)Audio::GetSndIDError()) || Audio::IsSFXPlaying(pTrackedSFX->voiceID)) {
                if (pGrabTrackedSFX != NULL) {
                    *pGrabTrackedSFX = pTrackedSFX;
                }
                return true;
            }

            if (pTrackedSFX->delay >= 0.0f) {
                if (pGrabTrackedSFX != NULL) {
                    *pGrabTrackedSFX = pTrackedSFX;
                }
                return true;
            }
        }

        if (nlDLRingIsEnd(head, current) || current == NULL) {
            current = NULL;
        } else {
            current = current->m_next;
        }
    }

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
