#include "NL/plat/plataudio.h"
#include "NL/nlMemory.h"
#include "NL/nlFile.h"
#include "NL/nlFileGC.h"
#include "NL/gl/glMemory.h"
#include "Game/Sys/debug.h"
#include "Game/Audio/AudioLoader.h"
#include "types.h"

extern void nlPrintf(const char*, ...);
extern u32 sndStackGetAvailableSampleMemory(unsigned long id);
extern "C" u32 sndStackSetCurrent(u32 id);
extern "C" u32 sndStackGetSize(void);
extern "C" unsigned long sndStackAdd(void* buffer, u32 aramAddr, u32 size);

static void* gpEntireSampleFileBufferFirstHalf;
static void* gpEntireSampleFileBufferSecondHalf;
static unsigned long gEntireSampleFileFirstHalfAllocSize;
static unsigned long gEntireSampleFileSecondHalfAllocSize;
static void* gpEntireSampleFileMRAMXferBuffer;
static u64 gEntireSampleMarker;
static u8 gAllowSyncReadsPastLoadedData;

// ARAMTransferHelperLoadEntireFile static members
// static u32 m_uFileSize__32ARAMTransferHelperLoadEntireFile;
// static nlFile* s_pFile__32ARAMTransferHelperLoadEntireFile;

// ARAMTransferHelper static members
ARAMTransferHelper* ARAMTransferHelper::m_pARAMHelper;
unsigned char ARAMTransferHelper::m_bFileOpened;
nlFile* ARAMTransferHelper::m_pFile;
const char* ARAMTransferHelper::m_szFileName;

#include <dolphin/ai.h>
#include <dolphin/arq.h>

SFXEmitter gEmitters[16];

struct _struct_stack_list_0x10
{
    /* 0x00 */ u32* unk0;        /* inferred */
    /* 0x04 */ unsigned long id; /* stack id for sndStack functions */
    /* 0x08 */ s32 unk8;         /* inferred */
    /* 0x0C */ u32 unkC;         /* inferred */
};

static struct _struct_stack_list_0x10 stack_list[2] = {
    { NULL, 0xFFFFFFFEU, 0, 0U },
    { NULL, 0xFFFFFFFFU, 0x2B4000, 0U },
};

struct EffectSettings
{
    // todo: implement
};

static EffectSettings gDPL2AuxAEffectSettings[0x2];
static EffectSettings gDPL2AuxBEffectSettings[0x2];
static s32 gAuxAEffectSettings;
static s32 gAuxBEffectSettings;

static u32 aramMemArray[2];
static void* (*const sndHookMalloc)(size_t) = musyXAlloc;
static void (*const sndHookFree)(void*) = musyXFree;

namespace PlatAudio
{
static u32 gPrimaryStackSize;
}

namespace PlatAudio
{

bool gUsingDolbyProLogic2 = false;

/**
 * Offset/Address/Size: 0x0 | 0x801C47FC | size: 0x8
 */
u32 GetSndIDError()
{
    return -1;
}

/**
 * Offset/Address/Size: 0x8 | 0x801C4804 | size: 0x30
 */
bool IsSFXPlaying(unsigned long id)
{
    SND_VOICEID result = sndFXCheck(id);
    return result != -1;
}

/**
 * Offset/Address/Size: 0x38 | 0x801C4834 | size: 0xC0
 * TODO: 94.17% match - init procedure needs to be checked
 */
void PlatAudio::InitEmitter(unsigned long idx)
{
    SFXEmitter* emitter = &gEmitters[idx];

    emitter->bKeepTrack = true;
    SND_PARAMETER_INFO** ppInfo = &emitter->pMIDIControllerInfo;

    // emitter->Init();
    emitter->soundType = (unsigned long)-1;
    emitter->fTimeStamp = -1.0f;
    emitter->bIsStopping = 0;
    emitter->bInUse = 0;
    emitter->bIsFilterOn = 0;
    emitter->m_unk_0x5F = 0;
    emitter->pPhysObj = NULL;
    emitter->pOwner = NULL;
    emitter->pos.pvPos = NULL;
    emitter->dir.pvDir = NULL;

    emitter->pos.vPos.f.x = 0.0f;
    emitter->pos.vPos.f.y = 0.0f;
    emitter->pos.vPos.f.z = 0.0f;
    emitter->dir.vDir.f.x = 0.0f;
    emitter->dir.vDir.f.y = 0.0f;
    emitter->dir.vDir.f.z = 0.0f;
    emitter->posUpdateMethod = NONE;

    SND_PARAMETER_INFO* pInfo = *ppInfo;
    if (pInfo != NULL)
    {
        void* arr = *(void**)((char*)pInfo + 0x4);
        if (arr != NULL)
        {
            delete[] (char*)arr;
        }
        delete *ppInfo;
    }
    *ppInfo = NULL;
}

/**
 * Offset/Address/Size: 0xF8 | 0x801C48F4 | size: 0x20
 */
bool RemoveEmitter(SFXEmitter* emitter)
{
    return sndRemoveEmitter((SND_EMITTER*)emitter);
}

/**
 * Offset/Address/Size: 0x118 | 0x801C4914 | size: 0x30
 */
bool RemoveEmitter(unsigned long idx)
{
    return sndRemoveEmitter((SND_EMITTER*)&gEmitters[idx]);
}

/**
 * Offset/Address/Size: 0x148 | 0x801C4944 | size: 0x14
 */
SFXEmitter* GetSFXEmitter(unsigned long id)
{
    return &gEmitters[id];
}

/**
 * Offset/Address/Size: 0x15C | 0x801C4958 | size: 0x35C
 */
void GetFreeEmitter(unsigned long&)
{
}

/**
 * Offset/Address/Size: 0x4B8 | 0x801C4CB4 | size: 0x20
 */
SND_VOICEID GetEmitterVoiceID(SFXEmitter* emitter)
{
    return sndEmitterVoiceID((SND_EMITTER*)emitter);
}

/**
 * Offset/Address/Size: 0x4D8 | 0x801C4CD4 | size: 0x20
 */
bool IsEmitterActive(SFXEmitter* emitter)
{
    return sndCheckEmitter((SND_EMITTER*)emitter);
}

/**
 * Offset/Address/Size: 0x4F8 | 0x801C4CF4 | size: 0x90
 */
void Update3DSFXEmitter(SFXEmitter* pSFXEmitter, const nlVector3& position, const nlVector3& direction, float maxVol)
{
    float var_f0;
    float temp_f6 = 127.0f * maxVol;

    SND_FVECTOR svPos;
    svPos.x = position.f.x;
    svPos.y = position.f.y;
    svPos.z = position.f.z;

    SND_FVECTOR svDir;
    svDir.x = direction.f.x;
    svDir.y = direction.f.y;
    svDir.z = direction.f.z;

    if (temp_f6 < 0.0f)
    {
        var_f0 = -0.5f;
    }
    else
    {
        var_f0 = 0.5f;
    }
    temp_f6 += var_f0;
    sndUpdateEmitter(&pSFXEmitter->emitter, &svPos, &svDir, (u8)(s32)temp_f6, NULL);
}

/**
 * Offset/Address/Size: 0x588 | 0x801C4D84 | size: 0x2E4
 */
void Add3DSFXEmitter(const EmitterStartInfo&)
{
}

/**
 * Offset/Address/Size: 0x86C | 0x801C5068 | size: 0x20
 */
void Remove3DSFXListener(SND_LISTENER* listener)
{
    sndRemoveListener(listener);
}

/**
 * Offset/Address/Size: 0x88C | 0x801C5088 | size: 0xC8
 */
void Update3DSFXListener(SND_LISTENER*, const nlVector3&, const nlVector3&, const nlVector3&, const nlVector3&, float)
{
}

/**
 * Offset/Address/Size: 0x954 | 0x801C5150 | size: 0x10C
 */
void Add3DSFXListener(SND_LISTENER* li, const nlVector3& pos, const nlVector3& dir, const nlVector3& heading, const nlVector3& up, float front_sur, float back_sur, float vol, float volPosOffset, bool doppler, float soundSpeed)
{
    SND_FVECTOR sndPos;
    sndPos.x = pos.f.x;
    sndPos.y = pos.f.y;
    sndPos.z = pos.f.z;

    SND_FVECTOR sndDir;
    sndDir.x = dir.f.x;
    sndDir.y = dir.f.y;
    sndDir.z = dir.f.z;

    SND_FVECTOR sndHeading;
    sndHeading.x = heading.f.x;
    sndHeading.y = heading.f.y;
    sndHeading.z = heading.f.z;

    SND_FVECTOR sndUp;
    sndUp.x = up.f.x;
    sndUp.y = up.f.y;
    sndUp.z = up.f.z;

    f32 rounded = 127.0f * vol;
    f32 adj;
    if (rounded < 0.0f)
    {
        adj = -0.5f;
    }
    else
    {
        adj = 0.5f;
    }
    rounded += adj;

    u32 flags = doppler ? 1 : 0;

    sndAddListenerEx(li, &sndPos, &sndDir, &sndHeading, &sndUp, front_sur, back_sur, soundSpeed, volPosOffset, flags, (u8)(s32)rounded, NULL);
}

/**
 * Offset/Address/Size: 0xA60 | 0x801C525C | size: 0x68
 */
bool SetPitchBendOnSFX(SND_VOICEID vid, u16 value)
{
    if (vid == -1 || sndFXCheck(vid) == -1)
    {
        return true;
    }
    return sndFXCtrl14(vid, 0x80, value);
}

/**
 * Offset/Address/Size: 0xAC8 | 0x801C52C4 | size: 0x7C
 */
bool SetFilterFreqOnSFX(SND_VOICEID vid, u16 value)
{
    u16 v = value;
    if (value > 0x3FFFU)
    {
        v = 0x3FFF;
    }

    if (vid == -1 || sndFXCheck(vid) == -1)
    {
        return true;
    }
    return sndFXCtrl14(vid, 0x1, v);
}

/**
 * Offset/Address/Size: 0xB44 | 0x801C5340 | size: 0x20
 */
// void SetMIDIControllerVal14Bit(unsigned long, unsigned char, unsigned short)
bool SetMIDIControllerVal14Bit(SND_VOICEID vid, u8 ctrl, u16 value)
{
    return sndFXCtrl14(vid, ctrl, value);
}

/**
 * Offset/Address/Size: 0xB64 | 0x801C5360 | size: 0x58
 */
void SetVolGroupVolume(u8 volGroup, float volume, u16 time)
{
    f32 temp_f1;
    f32 var_f0;

    temp_f1 = 127.0f * volume;
    if (temp_f1 < 0.0f)
    {
        var_f0 = -0.5f;
    }
    else
    {
        var_f0 = 0.5f;
    }
    sndVolume((s8)(temp_f1 + var_f0), time, volGroup);
}

/**
 * Offset/Address/Size: 0xBBC | 0x801C53B8 | size: 0x24
 */
bool SetSFXVolumeGroup(u32 fid, u8 vGroup)
{
    return sndFXAssignVolGroup2FXId((SND_FXID)fid, vGroup);
}

/**
 * Offset/Address/Size: 0xBE0 | 0x801C53DC | size: 0x68
 */
bool SetSFXReverbVol(SND_VOICEID vid, float value)
{
    int v;

    // u8 ctrl = 0x5B;
    if (value == 1.0f)
    {
        value = 0.0f; // Fallback
    }

    float value2 = 255.0f * value;
    value2 += (value2 < 0.0f ? -0.5f : 0.5f);
    v = value2;
    return sndFXCtrl(vid, 0x5B, v);
}

/**
 * Offset/Address/Size: 0xC48 | 0x801C5444 | size: 0x88
 */
void SetSFXVolume(unsigned long voiceID, float volume)
{
    volume = (volume >= 0.0f) ? volume : 0.0f;
    volume = (volume <= 1.0f) ? volume : 1.0f;

    float v = 127.0f * volume;
    float r = (v < 0.0f) ? -0.5f : 0.5f;
    v = v + r;
    sndFXCtrl(voiceID, 7, (u8)(s32)v);
}

/**
 * Offset/Address/Size: 0xCD0 | 0x801C54CC | size: 0x48
 */
bool StopSFX(unsigned long handle)
{
    if (handle == 0xFFFFFFFF)
    {
        return false;
    }
    bool result = sndFXKeyOff(handle);
    if (result)
    {
        return true;
    }
    return result;
}

/**
 * Offset/Address/Size: 0xD18 | 0x801C5514 | size: 0x244
 */
void PlaySFX(const SFXStartInfo&)
{
}

/**
 * Offset/Address/Size: 0xF5C | 0x801C5758 | size: 0x120
 * TODO: 99.38% match - r6/r7 register swap for loop counter vs grp pointer
 */
bool UnloadAllSoundGroupsOnStack(AudioFileData& fileData, unsigned long stackEnum)
{
    int i;

    if (!(unsigned char)sndStackSetCurrent(stack_list[stackEnum].id))
    {
        tDebugPrintManager::Print(DC_SOUND, "sndStackSetCurrent failed for stack %d\n", stack_list[stackEnum].id);
        return 0;
    }

    for (i = 0; (unsigned long)i < stack_list[stackEnum].unkC; i++)
    {
        if (!sndPopGroup())
        {
            tDebugPrintManager::Print(DC_SOUND, "sndPopGroup failed on stack %d\n", stackEnum);
            return 0;
        }
        PrintSoundStackInfo();
    }

    stack_list[stackEnum].unkC = 0;

    {
        SndGroupData* grp;
        i = 0;
        while (i < fileData.numSoundGroups)
        {
            grp = &fileData.soundGroups[i];
            if (stackEnum == (unsigned long)grp->stackEnum)
            {
                grp->stackEnum = -1;
                grp->uLoadOrder = -1;
                grp->loadType = (LoadType)0;
            }
            i++;
        }
    }

    return true;
}

/**
 * Offset/Address/Size: 0x107C | 0x801C5878 | size: 0x150
 * TODO: 97.68% match - r29/r30 swap (fileData/offset), r26/r27 swap in pop-group
 * inner loop, and r6/r7 swap in soundGroups loops (MWCC register allocator quirk)
 */
bool UnloadAllSoundGroups(AudioFileData& fileData)
{
    unsigned long* idPtr;
    _struct_stack_list_0x10* entry;
    int i;

    sndSilence();

    char* base = (char*)stack_list;
    int stackEnum = 1;
    int offset = 0x10;

    do
    {
        entry = (_struct_stack_list_0x10*)(base + offset);
        unsigned long id = entry->id;
        idPtr = &entry->id;
        if (!(unsigned char)sndStackSetCurrent(id))
        {
            tDebugPrintManager::Print(DC_SOUND, "sndStackSetCurrent failed for stack %d\n", *idPtr);
            goto next;
        }

        {
            u32* numPtr = &entry->unkC;
            i = 0;
            while ((unsigned long)i < *numPtr)
            {
                if (!sndPopGroup())
                {
                    tDebugPrintManager::Print(DC_SOUND, "sndPopGroup failed on stack %d\n", stackEnum);
                    goto next;
                }
                PrintSoundStackInfo();
                i++;
            }

            *numPtr = 0;
        }

        {
            SndGroupData* grp;
            i = 0;
            while (i < fileData.numSoundGroups)
            {
                grp = &fileData.soundGroups[i];
                if ((unsigned long)stackEnum == (unsigned long)grp->stackEnum)
                {
                    grp->stackEnum = -1;
                    grp->uLoadOrder = -1;
                    grp->loadType = (LoadType)0;
                }
                i++;
            }
        }

    next:
        stackEnum--;
        offset -= 0x10;
    } while (stackEnum >= 0);

    {
        SndGroupData* grp;
        i = 0;
        while (i < fileData.numSoundGroups)
        {
            grp = &fileData.soundGroups[i];
            grp->stackEnum = -1;
            grp->uLoadOrder = -1;
            grp->loadType = (LoadType)0;
            i++;
        }
    }

    return true;
}

/**
 * Offset/Address/Size: 0x11CC | 0x801C59C8 | size: 0x184
 */
bool UnloadSoundGroup(AudioFileData&, unsigned long)
{
    FORCE_DONT_INLINE;
    return false;
}

/**
 * Offset/Address/Size: 0x1350 | 0x801C5B4C | size: 0x328
 */
void LoadSoundGroup(AudioFileData&, unsigned long, unsigned long, bool)
{
}

/**
 * Offset/Address/Size: 0x1678 | 0x801C5E74 | size: 0x16C
 */
void SetupSoundBuffers(AudioFileData&, bool)
{
}

/**
 * Offset/Address/Size: 0x17E4 | 0x801C5FE0 | size: 0x20
 */
void StopAllSound()
{
    sndSilence();
}

/**
 * Offset/Address/Size: 0x1804 | 0x801C6000 | size: 0x78
 */
void Shutdown()
{
    sndQuit();

    for (int i = 0; i < 2; i++)
    {
        ARFree(stack_list[i].unk0);
        delete stack_list[i].unk0;
        stack_list[i].unk0 = NULL;
    }

    AIReset();
    ARQReset();
    ARReset();
}

/**
 * Offset/Address/Size: 0x187C | 0x801C6078 | size: 0x11C
 * 99.86% match - i diffs only (sndHookMalloc/sndHookFree symbol names vs @495 anonymous label)
 */
bool Initialize(bool bUseDSP)
{
    SND_HOOKS hooks;

    tDebugPrintManager::Print(DC_SOUND, "Initializing PlatAudio\n");

    hooks.malloc = sndHookMalloc;
    hooks.free = sndHookFree;

    ARInit(aramMemArray, 2);
    ARQInit();
    AIInit(NULL);

    ARAlloc(gPrimaryStackSize);

    sndSetHooks(&hooks);

    u32 flags = 0;
    flags |= 0x2;
    if (bUseDSP)
    {
        flags |= 0x1;
    }

    if (!sndIsInstalled())
    {
        sndInit(0x40, 0, 0x40, 1, flags, gPrimaryStackSize);
    }

    _struct_stack_list_0x10* pStack = &stack_list[1];
    u32 aramAddr = ARAlloc(pStack->unk8);
    u32 stackSize = sndStackGetSize();
    u32* buffer = (u32*)nlMalloc(stackSize, 8, false);
    pStack->id = sndStackAdd(buffer, aramAddr, pStack->unk8);
    pStack->unk0 = buffer;

    sndVolume(0x7F, 0, 0xFF);
    sndOutputMode(SND_OUTPUTMODE_STEREO);
    PrintSoundStackInfo();

    return true;
}

/**
 * Offset/Address/Size: 0x1998 | 0x801C6194 | size: 0x74
 */
void PurgeSampleFileBuffer()
{
    if (gpEntireSampleFileBufferFirstHalf != NULL)
    {
        glResourceRelease(gEntireSampleMarker);
        gEntireSampleMarker = 0;
        gpEntireSampleFileBufferFirstHalf = NULL;
    }

    if (gpEntireSampleFileBufferSecondHalf != NULL)
    {
        nlVirtualFree(gpEntireSampleFileBufferSecondHalf);
        gpEntireSampleFileBufferSecondHalf = NULL;
        nlFree(gpEntireSampleFileMRAMXferBuffer);
        gpEntireSampleFileMRAMXferBuffer = NULL;
    }

    gAllowSyncReadsPastLoadedData = 0;
}

/**
 * Offset/Address/Size: 0x1A0C | 0x801C6208 | size: 0x14
 */
bool IsEntireSampleFileInMem()
{
    return gpEntireSampleFileBufferSecondHalf != NULL;
}

/**
 * Offset/Address/Size: 0x1A20 | 0x801C621C | size: 0x124
 * TODO: 99.5% match - r0/r3 register swap at offsets 0x58-0x70 (first-half alloc size min calculation). MWCC allocates freeMem-0x400 to r0 instead of keeping it in r3. Tried 20+ permutations including variable reordering, type changes, condition flips, ternaries - all produce same 8 register-only diffs.
 */
unsigned char ReadEntireSampleFileIntoMemSync(const char* sampleFile)
{
    ARAMTransferHelperLoadEntireFile::s_pFile = nlOpen(sampleFile);
    if (ARAMTransferHelperLoadEntireFile::s_pFile == NULL)
    {
        tDebugPrintManager::Print(DC_SOUND, "ReadEntireSampleFileIntoMem: Could not open file.\n");
        return 0;
    }

    gAllowSyncReadsPastLoadedData = 1;
    unsigned int allocSize;
    unsigned int fileSize = nlFileSize(ARAMTransferHelperLoadEntireFile::s_pFile, &allocSize);
    if (fileSize != 0)
    {
        gEntireSampleFileFirstHalfAllocSize = glx_GetFreeMemory() - 0x400;
        unsigned long firstHalfSize = fileSize;
        if (gEntireSampleFileFirstHalfAllocSize <= fileSize)
        {
            firstHalfSize = gEntireSampleFileFirstHalfAllocSize;
        }
        gEntireSampleFileFirstHalfAllocSize = firstHalfSize;

        gEntireSampleMarker = glResourceMark();
        gpEntireSampleFileBufferFirstHalf = glResourceAlloc(gEntireSampleFileFirstHalfAllocSize, GLM_TextureData);
        *(u32*)gpEntireSampleFileBufferFirstHalf = 0;
        nlRead(ARAMTransferHelperLoadEntireFile::s_pFile, gpEntireSampleFileBufferFirstHalf, gEntireSampleFileFirstHalfAllocSize);

        fileSize -= gEntireSampleFileFirstHalfAllocSize;
        unsigned int virtualFree = nlVirtualLargestBlock() - 0x400;
        if (virtualFree <= fileSize)
        {
            fileSize = virtualFree;
        }
        gEntireSampleFileSecondHalfAllocSize = fileSize;
        if (fileSize != 0)
        {
            gpEntireSampleFileBufferSecondHalf = nlVirtualAlloc(fileSize, true);
            *(u32*)gpEntireSampleFileBufferSecondHalf = 0;
            nlReadToVirtualMemory(ARAMTransferHelperLoadEntireFile::s_pFile, gpEntireSampleFileBufferSecondHalf, gEntireSampleFileSecondHalfAllocSize, 0x80000);
        }
    }

    nlClose(ARAMTransferHelperLoadEntireFile::s_pFile);
    ARAMTransferHelperLoadEntireFile::s_pFile = NULL;
    return 1;
}

/**
 * Offset/Address/Size: 0x1B44 | 0x801C6340 | size: 0x100
 */
unsigned char ReadEntireSampleFileIntoMem(const char* sampleFile)
{
    unsigned int allocSize;

    ARAMTransferHelperLoadEntireFile::s_pFile = nlOpen(sampleFile);
    if (ARAMTransferHelperLoadEntireFile::s_pFile == NULL)
    {
        tDebugPrintManager::Print(DC_SOUND, "ReadEntireSampleFileIntoMem: Could not open file.\n");
        return 0;
    }

    unsigned long SecondHalfSize = nlFileSize(ARAMTransferHelperLoadEntireFile::s_pFile, &allocSize);
    if (SecondHalfSize != 0)
    {
        gEntireSampleFileFirstHalfAllocSize = glx_GetFreeMemory() - 0x400;
        gEntireSampleMarker = glResourceMark();

        void* buffer = glResourceAlloc(gEntireSampleFileFirstHalfAllocSize, GLM_TextureData);
        *(u32*)buffer = 0;
        nlReadAsync(ARAMTransferHelperLoadEntireFile::s_pFile, buffer, gEntireSampleFileFirstHalfAllocSize, ARAMTransferHelperLoadEntireFile::LoadEntireFileCallback, 0);

        gpEntireSampleFileMRAMXferBuffer = nlMalloc(0x80000, 0x20, true);
        gEntireSampleFileSecondHalfAllocSize = SecondHalfSize - gEntireSampleFileFirstHalfAllocSize;
        void* vBuffer = nlVirtualAlloc(gEntireSampleFileSecondHalfAllocSize, true);
        *(u32*)vBuffer = 0;
        nlReadAsyncToVirtualMemory(ARAMTransferHelperLoadEntireFile::s_pFile, vBuffer, gEntireSampleFileSecondHalfAllocSize, ARAMTransferHelperLoadEntireFile::LoadEntireFileCallback, 1, 0x80000, gpEntireSampleFileMRAMXferBuffer);
    }

    return 1;
}

/**
 * Offset/Address/Size: 0x1F1C | 0x801C6718 | size: 0x10C
 */
bool UpdateAuxEffectA(MusyXEffectType type, void* auxEffectSettings)
{
    bool result;

    switch (type)
    {
    case MUSYX_EFFECT_NONE:
        return true;
    case MUSYX_EFFECT_REVERB:
        result = sndAuxCallbackUpdateSettingsReverbSTD((SND_AUX_REVERBSTD*)auxEffectSettings);
        if (!result)
        {
            nlPrintf("UpdateAuxEffectA: sndAuxCallbackUpdateSettingsReverbSTD failed.\n");
            return false;
        }
        break;
    case MUSYX_EFFECT_REVERB_HI:
        result = sndAuxCallbackUpdateSettingsReverbHI((SND_AUX_REVERBHI*)auxEffectSettings);
        if (!result)
        {
            nlPrintf("UpdateAuxEffectA: sndAuxCallbackUpdateSettingsReverbHI failed.\n");
            return false;
        }
        break;
    case MUSYX_EFFECT_CHORUS:
        result = sndAuxCallbackUpdateSettingsChorus((SND_AUX_CHORUS*)auxEffectSettings);
        if (!result)
        {
            nlPrintf("UpdateAuxEffectA: sndAuxCallbackUpdateSettingsChorus failed.\n");
            return false;
        }
        break;
    case MUSYX_EFFECT_DELAY:
        result = sndAuxCallbackUpdateSettingsDelay((SND_AUX_DELAY*)auxEffectSettings);
        if (!result)
        {
            nlPrintf("UpdateAuxEffectA: sndAuxCallbackUpdateSettingsDelay failed.\n");
            return false;
        }
        break;
    default:
        nlPrintf("UpdateAuxEffectA: Unrecognized effect type.\n");
        return false;
    }

    return true;
}

} // namespace PlatAudio

/**
 * Offset/Address/Size: 0x2028 | 0x801C6824 | size: 0x244
 */
bool AddAuxEffect(MusyXEffectType type, void* data, bool arg2, unsigned char arg3)
{
    FORCE_DONT_INLINE;

    if ((arg2 == 0) && (PlatAudio::gUsingDolbyProLogic2) && (type != 0))
    {
        return false;
    }

    // if (PlatAudio::gUsingDolbyProLogic2)
    // {
    //     if (arg2 != 0)
    //     {
    //         var_r31 = &gDPL2AuxAEffectSettings;
    //         var_r30 = &gDPL2AuxAEffect;
    //     }
    //     else
    //     {
    //         var_r31 = &gDPL2AuxBEffectSettings;
    //         var_r30 = &gDPL2AuxBEffect;
    //     }
    // }
    // else if (arg2 != 0)
    // {
    //     var_r31 = &gAuxAEffectSettings;
    //     var_r30 = &gAuxAEffect;
    // }
    // else
    // {
    //     var_r31 = &gAuxBEffectSettings;
    //     var_r30 = &gAuxBEffect;
    // }

    switch (type)
    {
    case MUSYX_EFFECT_NONE:
        // var_r25 = NULL;
        // temp_ret = nlPrintf("InitAuxEffect: MUSYX_EFFECT_NONE passed in, callback return is NULL.\n");
        // var_f1 = (bitwise f32)temp_ret;
        // var_r4 = temp_ret;
        nlPrintf("InitAuxEffect: MUSYX_EFFECT_NONE passed in, callback return is NULL.\n");
        break;
    }

    return true;
}

namespace PlatAudio
{

/**
 * Offset/Address/Size: 0x226C | 0x801C6A68 | size: 0x28
 */
bool AddAuxEffectA(MusyXEffectType type, void* data, unsigned char arg)
{
    return AddAuxEffect(type, data, true, arg);
}

/**
 * Offset/Address/Size: 0x2294 | 0x801C6A90 | size: 0x21C
 */
void ShutdownAuxEffectA()
{
}

/**
 * Offset/Address/Size: 0x24B0 | 0x801C6CAC | size: 0x24
 */
bool DeactivateDPL2()
{
    if (gUsingDolbyProLogic2 == false)
    {
        return true;
    }
    gUsingDolbyProLogic2 = false;
    return true;
}

/**
 * Offset/Address/Size: 0x24D4 | 0x801C6CD0 | size: 0x24
 */
bool ActivateDPL2()
{
    if (gUsingDolbyProLogic2)
    {
        return true;
    }
    gUsingDolbyProLogic2 = true;
    return true;
}

/**
 * Offset/Address/Size: 0x24F8 | 0x801C6CF4 | size: 0x60
 */
void SetOutputMode(MusyXOutputType outputType)
{
    switch (outputType)
    {
    case MusyXOutputType_MONO:
        sndOutputMode(SND_OUTPUTMODE_MONO);
        return;
    case MusyXOutputType_STEREO:
        sndOutputMode(SND_OUTPUTMODE_STEREO);
        return;
    case MusyXOutputType_SURROUND:
        sndOutputMode(SND_OUTPUTMODE_SURROUND);
        return;
    }
}

} // namespace PlatAudio

/**
 * Offset/Address/Size: 0x1C44 | 0x801C6440 | size: 0x54
 */
void ARAMTransferHelperLoadEntireFile::LoadEntireFileCallback(nlFile* pFile, void* pBuffer, unsigned int size, unsigned long halfIndex)
{
    unsigned int fileSize;
    if (halfIndex == 0)
    {
        gpEntireSampleFileBufferFirstHalf = (void*)((char*)pBuffer - size);
    }
    else
    {
        gpEntireSampleFileBufferSecondHalf = (void*)((char*)pBuffer - size);
        ARAMTransferHelperLoadEntireFile::m_uFileSize = nlFileSize(pFile, &fileSize);
        nlClose(ARAMTransferHelperLoadEntireFile::s_pFile);
        ARAMTransferHelperLoadEntireFile::s_pFile = NULL;
    }
}

/**
 * Offset/Address/Size: 0x1C98 | 0x801C6494 | size: 0x13C
 */
void ARAMTransferHelperLoadEntireFile::sndPushGroupCallback(unsigned long, unsigned long)
{
}

/**
 * Offset/Address/Size: 0x1DD4 | 0x801C65D0 | size: 0x148
 */
void* ARAMTransferHelper::sndPushGroupCallback(unsigned long arg0, unsigned long arg1)
{
    unsigned long uSize = arg1;
    unsigned char* pARAMBlock = ARAMTransferHelper::m_pARAMHelper->m_pARAMXferBlockBaseAddress;
    unsigned long uOffset = arg0;

    while (uSize != 0)
    {
        if (uOffset >= ARAMTransferHelper::m_pARAMHelper->m_uCachedDataOffset && uOffset < ARAMTransferHelper::m_pARAMHelper->m_uCachedDataOffset + 0x20000)
        {
            if (!ARAMTransferHelper::m_bFileOpened)
            {
                ARAMTransferHelper::m_pFile = nlOpen(ARAMTransferHelper::m_szFileName);
                ARAMTransferHelper::m_bFileOpened = 1;
            }

            unsigned long uOffsetInBlock = uOffset - ARAMTransferHelper::m_pARAMHelper->m_uCachedDataOffset;
            unsigned long uRemainingInCache = 0x20000 - uOffsetInBlock;
            unsigned long uCopySize = uSize;
            if (uRemainingInCache <= uSize)
                uCopySize = uRemainingInCache;

            memcpy(pARAMBlock, ARAMTransferHelper::m_pARAMHelper->m_pDiskCacheBaseAddress + uOffsetInBlock, uCopySize);
            uSize -= uCopySize;
            uOffset += uCopySize;
            pARAMBlock += uCopySize;
        }
        else
        {
            if (!ARAMTransferHelper::m_bFileOpened)
            {
                ARAMTransferHelper::m_pFile = nlOpen(ARAMTransferHelper::m_szFileName);
                ARAMTransferHelper::m_bFileOpened = 1;
            }

            unsigned long uSeekPosition = uOffset & ~0x1FFFF;
            nlSeek(ARAMTransferHelper::m_pFile, uSeekPosition, 0);

            nlFile* pFile = ARAMTransferHelper::m_pFile;
            unsigned long uFileRemaining = ARAMTransferHelper::m_pARAMHelper->m_uFileSize - uSeekPosition;
            unsigned char* pDiskCache = ARAMTransferHelper::m_pARAMHelper->m_pDiskCacheBaseAddress;
            unsigned long uReadSize = uFileRemaining < 0x20000 ? uFileRemaining : (unsigned long)0x20000;
            nlRead(pFile, pDiskCache, uReadSize);
            ARAMTransferHelper::m_pARAMHelper->m_uCachedDataOffset = uSeekPosition;
        }
    }

    return ARAMTransferHelper::m_pARAMHelper->m_pARAMXferBlockBaseAddress;
}

/**
 * Offset/Address/Size: 0x2558 | 0x801C6D54 | size: 0x278
 */
void PrintSoundStackInfo()
{
    FORCE_DONT_INLINE;
}

/**
 * Offset/Address/Size: 0x27D0 | 0x801C6FCC | size: 0x74
 */
void PrintAvailableARAMMemory()
{
    for (int i = 0; i < 2; i++)
    {
        u32 available = sndStackGetAvailableSampleMemory(stack_list[i].id);
        tDebugPrintManager::Print(DC_MEMORY, "Available ARAM: %d\n", available);
    }
}

/**
 * Offset/Address/Size: 0x2844 | 0x801C7040 | size: 0x20
 */
void musyXFree(void* ptr)
{
    nlFree(ptr);
}

/**
 * Offset/Address/Size: 0x2864 | 0x801C7060 | size: 0x28
 */
void* musyXAlloc(u32 size)
{
    return nlMalloc(size, 0x20, false);
}

// /**
//  * Offset/Address/Size: 0x288C | 0x801C7088 | size: 0x3C
//  */
// void 0x8028D524..0x8028D528 | size: 0x4
// {
// }
