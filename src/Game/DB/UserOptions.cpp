#include "types.h"
#pragma pool_data off

#include "Game/DB/UserOptions.h"

#include "dolphin/os.h"
#include "NL/nlMemory.h"
#include "NL/nlBasicString.h"

#include "Game/AI/AiUtil.h"
#include "Game/Audio/AudioLoader.h"
#include "Game/GameInfo.h"

extern bool g_e3_Build;

static const char* POWERUPS_DEFAULT_CONFIG_FILE = "DefaultPowerupOptions.ini";
static const char* AUDIO_DEFAULT_CONFIG_FILE = "DefaultAudioOptions.ini";

// /**
//  * Offset/Address/Size: 0xA8 | 0x801907F8 | size: 0x84
//  */
// void Config::TagValuePair::Get<BasicString<char, Detail::TempStringAllocator> >() const
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x80190750 | size: 0xA8
//  */
// void Config::Get<BasicString<char, Detail::TempStringAllocator> >(const char*, BasicString<char, Detail::TempStringAllocator>)
// {
// }

/**
 * Offset/Address/Size: 0xFE8 | 0x801906F4 | size: 0x5C
 */
AudioSettings::AudioSettings()
{
    memset(this, 0, 0x20);
    MusicVolume = 0xA;
    SFXVolume = 0xA;
    VoiceVolume = 0xA;
    DefaultMusicVolume = 0xA;
    DefaultSFXVolume = 0xA;
    DefaultVoiceVolume = 0xA;
    DefaultMode = STEREO;
}

/**
 * Offset/Address/Size: 0xBB0 | 0x801902BC | size: 0x438
 */
void AudioSettings::InitializeDefaults()
{
    Config cfg(Config::ALLOCATE_HIGH);
    cfg.LoadFromFile(AUDIO_DEFAULT_CONFIG_FILE);

    MusicVolume = GetConfigInt(cfg, "Music Volume", 0xA);
    SFXVolume = GetConfigInt(cfg, "SFX Volume", 0xA);
    VoiceVolume = GetConfigInt(cfg, "Voice Volume", 0xA);

    // temp_r3_4 = nlMalloc__FUlUib(0x10, 8, 1);
    // if (temp_r3_4 != NULL)
    // {
    //     temp_r3_4->unk0 = NULL;
    //     var_r30 = @1371;
    //     var_r4 = @1371;
    //     temp_r3_4->unk4 = 0;
    //     temp_r3_4->unk8 = 0;
    // loop_36:
    //     temp_r0_4 = *var_r4;
    //     var_r4 += 1;
    //     if (temp_r0_4 != 0)
    //     {
    //         temp_r3_4->unk4 = temp_r3_4->unk4 + 1;
    //         goto loop_36;
    //     }
    //     temp_r3_4->unk4 = temp_r3_4->unk4 + 1;
    //     temp_r3_4->unk0 = nlMalloc__FUlUib(temp_r3_4->unk4 + 1, 8, 1);
    //     var_r4_2 = 0;
    //     temp_r3_4->unk8 = temp_r3_4->unk4;
    // loop_39:
    //     if (var_r4_2 < temp_r3_4->unk4)
    //     {
    //         temp_r0_5 = *var_r30;
    //         var_r30 += 1;
    //         *(temp_r3_4->unk0 + var_r4_2) = temp_r0_5;
    //         var_r4_2 += 1;
    //         goto loop_39;
    //     }
    //     temp_r3_4->unkC = 1;
    // }
    // spC = temp_r3_4;
    // Get < 45BasicString < c, Q26Detail19TempStringAllocator >> __6ConfigFPCc45BasicString<c, Q26Detail19TempStringAllocator>(&sp8, &sp14.unk0, "Mode");
    // if (sp8 != NULL)
    // {
    //     (sp8)->unkC = (sp8)->unkC + 1;
    //     var_r0 = sp8;
    // }
    // else
    // {
    //     var_r0 = NULL;
    // }
    // sp10 = var_r0;
    // if (sp8 != NULL)
    // {
    //     temp_r0_6 = (sp8)->unkC - 1;
    //     (sp8)->unkC = temp_r0_6;
    //     if (temp_r0_6 == 0)
    //     {
    //         temp_cr0_eq = sp8 == NULL;
    //         if (temp_cr0_eq == 0)
    //         {
    //             if (temp_cr0_eq == 0)
    //             {
    //                 __dla__FPv((sp8)->unk0);
    //             }
    //             if (sp8 != NULL)
    //             {
    //                 nlFree__FPv(sp8);
    //             }
    //         }
    //     }
    // }
    // if (spC != NULL)
    // {
    //     temp_r0_7 = spC->unkC - 1;
    //     spC->unkC = temp_r0_7;
    //     if (temp_r0_7 == 0)
    //     {
    //         temp_cr0_eq_2 = spC == NULL;
    //         if (temp_cr0_eq_2 == 0)
    //         {
    //             if (temp_cr0_eq_2 == 0)
    //             {
    //                 __dla__FPv(spC->unk0);
    //             }
    //             if (spC != NULL)
    //             {
    //                 nlFree__FPv(spC);
    //             }
    //         }
    //     }
    // }

    // if (__eq<c, Q26Detail19TempStringAllocator> __FRC45BasicString<c, Q26Detail19TempStringAllocator> PCc(&sp10, "STEREO") != 0)
    // {
    //     this->unkC = 0;
    // }
    // else if (__eq<c, Q26Detail19TempStringAllocator> __FRC45BasicString<c, Q26Detail19TempStringAllocator> PCc(&sp10, "MONO") != 0)
    // {
    //     this->unkC = 1;
    // }
    // else if (__eq<c, Q26Detail19TempStringAllocator> __FRC45BasicString<c, Q26Detail19TempStringAllocator> PCc(&sp10, "DOLBY") != 0)
    // {
    //     this->unkC = 2;
    // }
    // else
    // {
    //     this->unkC = OSGetSoundMode() == 0;
    // }

    // if (sp10 != NULL)
    // {
    //     temp_r0_8 = sp10->unkC - 1;
    //     sp10->unkC = temp_r0_8;
    //     if (temp_r0_8 == 0)
    //     {
    //         temp_cr0_eq_3 = sp10 == NULL;
    //         if (temp_cr0_eq_3 == 0)
    //         {
    //             if (temp_cr0_eq_3 == 0)
    //             {
    //                 __dla__FPv(sp10->unk0);
    //             }
    //             if (sp10 != NULL)
    //             {
    //                 nlFree__FPv(sp10);
    //             }
    //         }
    //     }
    // }

    FORCE_DONT_INLINE;
}

/**
 * Offset/Address/Size: 0xB20 | 0x8019022C | size: 0x90
 */
void AudioSettings::ForceApplySettings(bool bUpdateMode)
{
    if (AudioLoader::gbDisableAudio == false)
    {
        u32 curr_mode = OSGetSoundMode();
        u32 our_mode = Mode;

        if (curr_mode == 0)
        {
            Mode = MONO;
        }
        else
        {
            if (our_mode == (u32)MONO)
            {
                Mode = STEREO;
            }
        }

        DefaultMusicVolume = -1;
        DefaultSFXVolume = -1;
        DefaultVoiceVolume = -1;
        DefaultMode = INVALID;

        ApplySettings(true, bUpdateMode);
    }
}

/**
 * Offset/Address/Size: 0x7D0 | 0x8018FEDC | size: 0x350
 */
void AudioSettings::ApplySettings(bool bApplyMode, bool bUpdateMode)
{
    if (AudioLoader::gbDisableAudio == false)
    {
        float musicVolume = (float)MusicVolume / 10.0f;
        if (musicVolume != ((float)DefaultMusicVolume / 10.0f))
        {
            float adjustedMusicVolume = 0.0f;
            if (musicVolume != adjustedMusicVolume)
            {
                adjustedMusicVolume = Interpolate(0.2f, 1.0f, musicVolume);
            }

            musicVolume = adjustedMusicVolume;
            Audio::MasterVolume::SetVolume(Audio::MasterVolume::VG_Music, adjustedMusicVolume);
            DefaultMusicVolume = MusicVolume;
            g_pTrackManager->OnMasterVolumeChange(Audio::MasterVolume::VG_Music);
        }

        float sfxVolume = (float)SFXVolume / 10.0f;
        if (sfxVolume != ((float)DefaultSFXVolume / 10.0f))
        {
            const float sfxScale = 0.8f;
            sfxVolume *= sfxScale;
            Audio::SetVolGroupVolume(30, sfxVolume, 0);
            Audio::MasterVolume::SetVolume(Audio::MasterVolume::VG_SFX, sfxVolume);
            DefaultSFXVolume = SFXVolume;
            g_pTrackManager->OnMasterVolumeChange(Audio::MasterVolume::VG_SFX);
        }

        float voiceVolume = (float)VoiceVolume / 10.0f;
        if (voiceVolume != ((float)DefaultVoiceVolume / 10.0f))
        {
            Audio::MasterVolume::SetVoiceVolume(voiceVolume, 0);
            DefaultVoiceVolume = VoiceVolume;
            g_pTrackManager->OnMasterVolumeChange(Audio::MasterVolume::VG_Voice);
        }

        if ((Mode != DefaultMode) && bApplyMode)
        {
            switch (Mode)
            {
            case MONO:
                AudioLoader::ActivateDPL2(false, bUpdateMode);
                Audio::SetOutputMode((MusyXOutputType)0);
                break;
            case STEREO:
                AudioLoader::ActivateDPL2(false, bUpdateMode);
                Audio::SetOutputMode((MusyXOutputType)1);
                break;
            case DOLBY:
                AudioLoader::ActivateDPL2(true, bUpdateMode);
                break;
            default:
                break;
            }

            DefaultMode = Mode;
            OSSetSoundMode(Mode != MONO);

            Audio::MasterVolume::SetVolume(Audio::MasterVolume::VG_Music, musicVolume);
            g_pTrackManager->OnMasterVolumeChange(Audio::MasterVolume::VG_Music);

            Audio::SetVolGroupVolume(30, sfxVolume, 0);
            Audio::MasterVolume::SetVolume(Audio::MasterVolume::VG_SFX, sfxVolume);
            g_pTrackManager->OnMasterVolumeChange(Audio::MasterVolume::VG_SFX);

            Audio::MasterVolume::SetVoiceVolume(voiceVolume, 0);
            g_pTrackManager->OnMasterVolumeChange(Audio::MasterVolume::VG_Voice);
        }

        GameInfoManager* pGameInfo = GameInfoManager::s_pInstance;
        pGameInfo->mCurGameAudioSettings.MusicVolume = MusicVolume;
        pGameInfo->mCurGameAudioSettings.SFXVolume = SFXVolume;
        pGameInfo->mCurGameAudioSettings.VoiceVolume = VoiceVolume;
        pGameInfo->mCurGameAudioSettings.Mode = Mode;
    }
}

/**
 * Offset/Address/Size: 0x764 | 0x8018FE70 | size: 0x6C
 */
GameplaySettings::GameplaySettings()
{
    memset(this, 0, 0xC);

    SkillLevel = ROOKIE;
    GameTime = 0x12C;
    PowerUps = true;
    Shoot2Score = true;
    RumbleEnabled = true;
    BowserAttackEnabled = true;
    if (g_e3_Build != 0)
    {
        BowserAttackEnabled = false;
    }
}

/**
 * Offset/Address/Size: 0x760 | 0x8018FE6C | size: 0x4
 */
void GameplaySettings::InitializeDefaults()
{
}

/**
 * Offset/Address/Size: 0x75C | 0x8018FE68 | size: 0x4
 */
void GameplaySettings::OnSettingsUpdated() const
{
}

/**
 * Offset/Address/Size: 0x700 | 0x8018FE0C | size: 0x5C
 */
PowerupSettings::PowerupSettings()
{
    memset(this, 0, 8);
    RedShells = true;
    GreenShells = true;
    BlueShells = true;
    SpinyShells = true;
    Starman = true;
    Twister = true;
    Bobombs = true;
    Bananas = true;
}

/**
 * Offset/Address/Size: 0x234 | 0x8018F940 | size: 0x4CC
 */
void PowerupSettings::InitializeDefaults()
{
    Config cfg(Config::ALLOCATE_HIGH);
    cfg.LoadFromFile(POWERUPS_DEFAULT_CONFIG_FILE);

    RedShells = GetConfigBool(cfg, "Red Shells", true);
    GreenShells = GetConfigBool(cfg, "Green Shells", true);
    BlueShells = GetConfigBool(cfg, "Blue Shells", true);
    SpinyShells = GetConfigBool(cfg, "Spiny Shells", true);
    Starman = GetConfigBool(cfg, "Starman", true);
    Twister = GetConfigBool(cfg, "Twister", true);
    Bobombs = GetConfigBool(cfg, "Bobombs", true);
    Bananas = GetConfigBool(cfg, "Bananas", true);
}

/**
 * Offset/Address/Size: 0x230 | 0x8018F93C | size: 0x4
 */
void PowerupSettings::OnSettingsUpdated() const
{
}

/**
 * Offset/Address/Size: 0x1E0 | 0x8018F8EC | size: 0x50
 */
CheatSettings::CheatSettings()
{
    memset(this, 0, 8);
    mCustomPowerups = CP_OFF;
    mStunnedGoalies = false;
    mInfinitePowerups = false;
    mCheatTBD1Enabled = false;
    mCheatTBD2Enabled = false;
}

/**
 * Offset/Address/Size: 0x1C4 | 0x8018F8D0 | size: 0x1C
 */
void CheatSettings::InitializeDefaults()
{
    mCustomPowerups = CP_OFF;
    mStunnedGoalies = false;
    mInfinitePowerups = false;
    mCheatTBD1Enabled = false;
    mCheatTBD2Enabled = false;
}

/**
 * Offset/Address/Size: 0x1C0 | 0x8018F8CC | size: 0x4
 */
void CheatSettings::OnSettingsUpdated() const
{
}

/**
 * Offset/Address/Size: 0xD8 | 0x8018F7E4 | size: 0xE8
 */
VisualSettings::VisualSettings()
{
    memset(this, 0, 0x0C);
    mIsAutoZoomCamera = true;
    mCameraZoomLevel = 0.5f;
    mIsWidescreen = GetConfigBool(Config::Global(), "widescreen", false);
}

/**
 * Offset/Address/Size: 0x0 | 0x8018F70C | size: 0xD8
 */
void VisualSettings::InitializeDefaults()
{
    mIsAutoZoomCamera = true;
    mCameraZoomLevel = 0.5f;
    mIsWidescreen = GetConfigBool(Config::Global(), "widescreen", false);
}
