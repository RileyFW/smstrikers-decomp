#include "NL/plat/plataudio.h"
#include "NL/nlMemory.h"
#include "types.h"

extern void nlPrintf(const char*, ...);

#include <dolphin/ai.h>
#include <dolphin/arq.h>

SFXEmitter gEmitters[16];

struct _struct_stack_list_0x10
{
    /* 0x00 */ u32* unk0; /* inferred */
    /* 0x04 */ s8* unk4;  /* inferred */
    /* 0x08 */ s32 unk8;  /* inferred */
    /* 0x0C */ u32 unkC;  /* inferred */
};

static struct _struct_stack_list_0x10 stack_list[2] = {
    { NULL, (s8*)0xFFFFFFFEU, 0, 0U },
    { NULL, (s8*)0xFFFFFFFFU, 0x2B4000, 0U },
};

struct EffectSettings
{
    // todo: implement
};

static EffectSettings gDPL2AuxAEffectSettings[0x2];
static EffectSettings gDPL2AuxBEffectSettings[0x2];
static s32 gAuxAEffectSettings;
static s32 gAuxBEffectSettings;

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
 */
void InitEmitter(unsigned long)
{
}

/**
 * Offset/Address/Size: 0xF8 | 0x801C48F4 | size: 0x20
 */
void RemoveEmitter(SFXEmitter* emitter)
{
    // sndRemoveEmitter(emitter->m_sndEmitter);
    sndRemoveEmitter((SND_EMITTER*)emitter);
}

/**
 * Offset/Address/Size: 0x118 | 0x801C4914 | size: 0x30
 */
void RemoveEmitter(unsigned long)
{
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
void Update3DSFXEmitter(SFXEmitter* emitter, const nlVector3& pos, const nlVector3& dir, float volume)
{
    float var_f0;
    float temp_f6 = 127.0f * volume;

    SND_FVECTOR pos_vec = { pos.f.x, pos.f.y, pos.f.z };
    SND_FVECTOR dir_vec = { dir.f.x, dir.f.y, dir.f.z };

    if (temp_f6 < 0.0f)
    {
        var_f0 = -0.5f;
    }
    else
    {
        var_f0 = 0.5f;
    }
    // bool sndUpdateEmitter(SND_EMITTER* em, SND_FVECTOR* pos, SND_FVECTOR* dir, u8 maxVol, SND_ROOM* room);
    sndUpdateEmitter(&emitter->emitter, &pos_vec, &dir_vec, (s8)(temp_f6 + var_f0), NULL);
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
void Add3DSFXListener(SND_LISTENER*, const nlVector3&, const nlVector3&, const nlVector3&, const nlVector3&, float, float, float, float,
    bool, float)
{
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
void SetSFXVolume(unsigned long, float)
{
}

/**
 * Offset/Address/Size: 0xCD0 | 0x801C54CC | size: 0x48
 */
void StopSFX(unsigned long)
{
}

/**
 * Offset/Address/Size: 0xD18 | 0x801C5514 | size: 0x244
 */
void PlaySFX(const SFXStartInfo&)
{
}

/**
 * Offset/Address/Size: 0xF5C | 0x801C5758 | size: 0x120
 */
void UnloadAllSoundGroupsOnStack(AudioFileData&, unsigned long)
{
}

/**
 * Offset/Address/Size: 0x107C | 0x801C5878 | size: 0x150
 */
void UnloadAllSoundGroups(AudioFileData&)
{
}

/**
 * Offset/Address/Size: 0x11CC | 0x801C59C8 | size: 0x184
 */
void UnloadSoundGroup(AudioFileData&, unsigned long)
{
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
 */
void Initialize(bool)
{
}

/**
 * Offset/Address/Size: 0x1998 | 0x801C6194 | size: 0x74
 */
void PurgeSampleFileBuffer()
{
}

/**
 * Offset/Address/Size: 0x1A0C | 0x801C6208 | size: 0x14
 */
void IsEntireSampleFileInMem()
{
}

/**
 * Offset/Address/Size: 0x1A20 | 0x801C621C | size: 0x124
 */
void ReadEntireSampleFileIntoMemSync(const char*)
{
}

/**
 * Offset/Address/Size: 0x1B44 | 0x801C6340 | size: 0x100
 */
void ReadEntireSampleFileIntoMem(const char*)
{
}

/**
 * Offset/Address/Size: 0x1F1C | 0x801C6718 | size: 0x10C
 */
void UpdateAuxEffectA(MusyXEffectType, void*)
{
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
void ARAMTransferHelperLoadEntireFile::LoadEntireFileCallback(nlFile*, void*, unsigned int, unsigned long)
{
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
void ARAMTransferHelper::sndPushGroupCallback(unsigned long, unsigned long)
{
}

/**
 * Offset/Address/Size: 0x2558 | 0x801C6D54 | size: 0x278
 */
void PrintSoundStackInfo()
{
}

/**
 * Offset/Address/Size: 0x27D0 | 0x801C6FCC | size: 0x74
 */
void PrintAvailableARAMMemory()
{
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
