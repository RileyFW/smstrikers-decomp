#include "Game/FE/feHelpFuncs.h"

#include "Game/FE/FEAudio.h"
#include "Game/GameInfo.h"
#include "NL/nlMath.h"

enum nlLanguage
{
    LangEnglish = 0,
    LangFrench = 1,
    LangGerman = 2,
    LangSpanish = 3,
    LangItalian = 4,
    LangJapanese = 5,
    LangUKEnglish = 6,
    LangLongestStrings = 7,
    LangBob = 8,
    LangEnd = 9,
};

extern nlLanguage g_Language;

unsigned long TrophyTypeToStringName[13] = {
    0x3F93A700,
    0x68141335,
    0x7902D2A0,
    0xE384D5B8,
    0x88EAF9AE,
    0xFC7AE263,
    0x3D6FFE4E,
    0x77EBA4E6,
    0x51C47AC0,
    0x09FB969C,
    0xB520A8AF,
    0x185EC17B,
    0x99FCEA51,
};

unsigned long ModeToStandingsStringName[10] = {
    0xF17CCCFC,
    0x9B697E0A,
    0x61949FBF,
    0xF302B4AA,
    0xDD056242,
    0xDB4C7038,
    0x6E192E6D,
    0xE617BFD8,
    0xE989F0F0,
    0x14183216,
};

unsigned long ModeToStringName[10] = {
    0xF17CCCFC,
    0x3F93A700,
    0x68141335,
    0x7902D2A0,
    0xE384D5B8,
    0x88EAF9AE,
    0xFC7AE263,
    0x3D6FFE4E,
    0x77EBA4E6,
    0x1A97A58C,
};

unsigned long CCToStringName[13] = {
    0x35D90F6F,
    0x35F8B919,
    0x11761DAE,
    0x4298E9EF,
    0x367F2AF9,
    0x36947319,
    0x369BBA97,
    0x36D3EC80,
    0x477D2527,
    0x4DD51191,
    0x3750AFA1,
    0x377C920B,
    0x848890BC,
};

long TeamID2CharacterClassTable[9][2] = {
    { 0x00000000, 0x00000001 },
    { 0x00000001, 0x00000002 },
    { 0x00000002, 0x00000005 },
    { 0x00000003, 0x00000006 },
    { 0x00000004, 0x00000007 },
    { 0x00000005, 0x00000009 },
    { 0x00000006, 0x0000000A },
    { 0x00000007, 0x0000000B },
    { 0x00000008, 0x0000000C },
};

/**
 * Offset/Address/Size: 0x0 | 0x800A30BC | size: 0x58
 */
void MakeTextBoxReallyWide(TLTextInstance& textInstance)
{
    nlVector2& boxSize = ((textInstance.m_OverloadFlags & 0x4) != 0) ? textInstance.m_OverloadedAttributes.BoxSize : textInstance.m_component->m_BoxSize;
    nlVector2 bb = boxSize;
    bb.f.x = 999.9f;
    textInstance.m_OverloadedAttributes.BoxSize = bb;
    textInstance.m_OverloadFlags |= 0x4;
}

static const char* TrophyStreamNames[8] = {
    "FE_Cup_Win_Battle_Mush",
    "FE_Cup_Win_Battle_Flow",
    "FE_Cup_Win_Battle_Star",
    "FE_Cup_Win_Battle_Bows",
    "FE_Cup_Win_Super_Mush",
    "FE_Cup_Win_Super_Flow",
    "FE_Cup_Win_Super_Star",
    "FE_Cup_Win_Super_Bows",
};

/**
 * Offset/Address/Size: 0x58 | 0x800A3114 | size: 0x14
 */
const char* GetCupStreamName(eTrophyType trophyType)
{
    return TrophyStreamNames[trophyType];
}

/**
 * Offset/Address/Size: 0x6C | 0x800A3128 | size: 0x84
 */
const char* GetMemCardDescription()
{
    switch (g_Language)
    { /* irregular */
    case LangEnglish:
        return "Save File";
    case LangFrench:
        return "Fichier de Sauvegarde";
    case LangGerman:
        return "Spieldatei";
    case LangSpanish:
        return "Archivo Guardado";
    case LangItalian:
        return "File di Dati";
    case LangJapanese:
        return "\x83\x74\x83\x40\x83\x8B\x82\xF0\x8F\x9C\x82\xAF\x82\xCE"; // Japanese: "セーブファイル"
    case LangUKEnglish:
        return "Save File";
    default:
        return "Save File";
    }
}

/**
 * Offset/Address/Size: 0xF0 | 0x800A31AC | size: 0x40
 */
const char* GetMemCardTitle()
{
    switch (g_Language)
    {
    case LangEnglish:
        return "Super Mario Strikers";
    case LangJapanese:
        return "Super Mario Strikers";
    default:
        return "Mario Smash Football";
    }
}

// /**
//  * Offset/Address/Size: 0x130 | 0x800A31EC | size: 0x504
//  */
// void TakeGameMemSnapshot::WriteToDisk()
// {
// }

// /**
//  * Offset/Address/Size: 0x634 | 0x800A36F0 | size: 0x14
//  */
// void TakeGameMemSnapshot::ResetTimers()
// {
// }

// /**
//  * Offset/Address/Size: 0x648 | 0x800A3704 | size: 0x50
//  */
// void TakeGameMemSnapshot::Update(float)
// {
// }

static const char* CAPTAIN_SLIDE_SOUNDS[] = {
    "sfx_focus_daisy",
    "sfx_focus_dk",
    "sfx_focus_luigi",
    "sfx_focus_mario",
    "sfx_focus_peach",
    "sfx_focus_waluigi",
    "sfx_focus_wario",
    "sfx_focus_yoshi",
    "sfx_focus_mystery",
};

/**
 * Offset/Address/Size: 0x698 | 0x800A3754 | size: 0x34
 */
void FECharacterSound::PlayCaptainSlideIn(eTeamID teamID)
{
    FEAudio::PlayAnimAudioEvent(CAPTAIN_SLIDE_SOUNDS[teamID], false);
}

static const char* SIDEKICK_SOUNDS[] = {
    "sfx_accept_toad",
    "sfx_accept_koopa",
    "sfx_accept_ham",
    "sfx_accept_birdo",
};

/**
 * Offset/Address/Size: 0x6CC | 0x800A3788 | size: 0x34
 */
void FECharacterSound::PlaySidekickName(eSidekickID sidekickID)
{
    FEAudio::PlayAnimAudioEvent(SIDEKICK_SOUNDS[sidekickID], false);
}

static const char* CHARACTER_ACCEPT_SOUNDS[] = {
    "sfx_accept_daisy",
    "sfx_accept_dk",
    "sfx_accept_luigi",
    "sfx_accept_mario",
    "sfx_accept_peach",
    "sfx_accept_waluigi",
    "sfx_accept_wario",
    "sfx_accept_yoshi",
    "sfx_accept_mystery",
};

/**
 * Offset/Address/Size: 0x700 | 0x800A37BC | size: 0x48
 */
const char* FECharacterSound::PlayCaptainName(eTeamID teamID)
{
    FEAudio::PlayAnimAudioEvent(CHARACTER_ACCEPT_SOUNDS[teamID], true);
    return CHARACTER_ACCEPT_SOUNDS[teamID];
}

/**
 * Offset/Address/Size: 0x748 | 0x800A3804 | size: 0x94
 */
void EnableAutoPressed()
{
    g_pFEInput->Reset();
    g_pFEInput->EnableAnalogToDPadMapping(FE_ALL_PADS, true);
    g_pFEInput->SetAutoRepeatParams(FE_ALL_PADS, 0xe, 0.7f, 0.3f);
    g_pFEInput->SetAutoRepeatParams(FE_ALL_PADS, 0xd, 0.7f, 0.3f);
    g_pFEInput->SetAutoRepeatParams(FE_ALL_PADS, 0xb, 0.7f, 0.3f);
    g_pFEInput->SetAutoRepeatParams(FE_ALL_PADS, 0xc, 0.7f, 0.3f);
}

// /**
//  * Offset/Address/Size: 0x7DC | 0x800A3898 | size: 0x1B4
//  */
// void CaptainSidekickFilename::Build(CaptainSidekickFilename::Type, char*, int, int, int)
// {
// }

// /**
//  * Offset/Address/Size: 0x990 | 0x800A3A4C | size: 0x120
//  */
// void SingleHighlite::CloseItem(TLComponentInstance*)
// {
// }

// /**
//  * Offset/Address/Size: 0xAB0 | 0x800A3B6C | size: 0x144
//  */
// void SingleHighlite::OpenItem(TLComponentInstance*)
// {
// }

// /**
//  * Offset/Address/Size: 0xBF4 | 0x800A3CB0 | size: 0xC
//  */
// void SingleHighlite::TempDisableSound()
// {
// }

// /**
//  * Offset/Address/Size: 0xC00 | 0x800A3CBC | size: 0xB4
//  */
// void DoubleHighlite::CloseItem(TLComponentInstance*)
// {
// }

// /**
//  * Offset/Address/Size: 0xCB4 | 0x800A3D70 | size: 0x1B0
//  */
// void DoubleHighlite::OpenItem(TLComponentInstance*)
// {
// }

// /**
//  * Offset/Address/Size: 0xE64 | 0x800A3F20 | size: 0xC
//  */
// void DoubleHighlite::TempDisableSound()
// {
// }

/**
 * Offset/Address/Size: 0xE70 | 0x800A3F2C | size: 0x6C
 */
void FindComponent(TLSlide*, const char*)
{
}

/**
 * Offset/Address/Size: 0xEDC | 0x800A3F98 | size: 0x14
 */
void GetLOCRank(int)
{
}

/**
 * Offset/Address/Size: 0xEF0 | 0x800A3FAC | size: 0x84
 */
void ConvertToSidekickID(const char*)
{
}

/**
 * Offset/Address/Size: 0xF74 | 0x800A4030 | size: 0x84
 */
void ConvertToTeamID(const char*)
{
}

/**
 * Offset/Address/Size: 0xFF8 | 0x800A40B4 | size: 0x28
 */
void GetSidekickName(eSidekickID)
{
}

/**
 * Offset/Address/Size: 0x1020 | 0x800A40DC | size: 0x14
 */
char* GetTeamName(eTeamID)
{
    return nullptr;
}

/**
 * Offset/Address/Size: 0x1034 | 0x800A40F0 | size: 0x64
 */
void ConvertToCharacterClass(eSidekickID)
{
}

/**
 * Offset/Address/Size: 0x1098 | 0x800A4154 | size: 0x4C
 */
void ConvertToCharacterClass(eTeamID)
{
}

/**
 * Offset/Address/Size: 0x10E4 | 0x800A41A0 | size: 0x64
 */
// void GetLOCDifficultyName(GameplaySettings::eSkillLevel)
// {
// }

/**
 * Offset/Address/Size: 0x1148 | 0x800A4204 | size: 0x14
 */
unsigned long GetLOCTrophyName(eTrophyType trophyType)
{
    return TrophyTypeToStringName[trophyType];
}

/**
 * Offset/Address/Size: 0x115C | 0x800A4218 | size: 0x14
 */
unsigned long GetLOCStandingsName(GameInfoManager::eGameModes mode)
{
    return ModeToStandingsStringName[mode];
}

/**
 * Offset/Address/Size: 0x1170 | 0x800A422C | size: 0x14
 */
unsigned long GetLOCModeName(GameInfoManager::eGameModes mode)
{
    return ModeToStringName[mode];
}

/**
 * Offset/Address/Size: 0x1184 | 0x800A4240 | size: 0x70
 */
unsigned long GetLOCTeamName(eTeamID teamID)
{
    int i = 0;
    do
    {
        if (teamID == TeamID2CharacterClassTable[i][0])
        {
            int characterClass = TeamID2CharacterClassTable[i][1];
            return CCToStringName[characterClass];
        }
        i++;
    } while (i < 9);
    return 0x094D126F;
}

/**
 * Offset/Address/Size: 0x11F4 | 0x800A42B0 | size: 0x88
 */
unsigned long GetLOCSidekickName(eSidekickID sidekickid)
{
    s32 cc;

    switch (sidekickid)
    {
    case 3:
        cc = 0;
        break;
    case 2:
        cc = 3;
        break;
    case 1:
        cc = 4;
        break;
    case 0:
        cc = 8;
        break;
    case -2:
        cc = 0xC;
        break;
    default:
        cc = -1;
        break;
    }
    if (cc != -1)
    {
        return CCToStringName[cc];
    }
    return 0x094D126F;
}

/**
 * Offset/Address/Size: 0x127C | 0x800A4338 | size: 0xDC
 */
unsigned long GetLOCCharacterName(eTeamID teamid, bool useShortSuperTeam, bool useLockedSuperTeam)
{
    if ((useShortSuperTeam != 0) && (teamid == 8))
    {
        return 0xFA6F322B;
    }
    if ((useLockedSuperTeam != 0) && (teamid == 8) && (GameInfoManager::Instance()->IsSuperTeamUnlocked() == 0))
    {
        return 0x387952CD;
    }

    return 0x094D126F;
}

/**
 * Offset/Address/Size: 0x1358 | 0x800A4414 | size: 0x80
 */
unsigned long GetStadiumStringID(eStadiumID stadiumID)
{
    switch (stadiumID)
    {
    case STAD_MARIO_STADIUM:
        return 0x8FFCBC02;
    case STAD_PEACH_TOAD_STADIUM:
        return 0x9034EDEB;
    case STAD_DK_DAISY:
        return 0xBDD19EF9;
    case STAD_WARIO_STADIUM:
        return 0x90B1B10C;
    case STAD_YOSHI_STADIUM:
        return 0x90DD9376;
    case STAD_SUPER_STADIUM:
        return 0x90743D99;
    case STAD_FORBIDDEN_DOME:
        return 0xC7B104A1;
    default:
        return 0x094D126F;
    }
}

// /**
//  * Offset/Address/Size: 0x0 | 0x800A4494 | size: 0x38
//  */
// void FEFinder<TLImageInstance, 2>::Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher,
//     InlineHasher)
// {
// }

// /**
//  * Offset/Address/Size: 0x38 | 0x800A44CC | size: 0x84
//  */
// void FEFinder<TLImageInstance, 2>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long,
//     unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0xBC | 0x800A4550 | size: 0x15C
//  */
// void FEFinder<TLImageInstance, 2>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long,
//     unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x218 | 0x800A46AC | size: 0x38
//  */
// void FEFinder<TLComponentInstance, 4>::Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher,
//     InlineHasher)
// {
// }

// /**
//  * Offset/Address/Size: 0x250 | 0x800A46E4 | size: 0x84
//  */
// void FEFinder<TLComponentInstance, 4>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long,
//     unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x2D4 | 0x800A4768 | size: 0x15C
//  */
// void FEFinder<TLComponentInstance, 4>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long,
//     unsigned long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x800A48C4 | size: 0x13C
//  */
// void TakeGameMemSnapshot::Format<BasicString<char, Detail::TempStringAllocator>, unsigned long, unsigned int, unsigned int>(
//     const BasicString<char, Detail::TempStringAllocator>&, const unsigned long&, const unsigned int&, const unsigned int&)
// {
// }

// /**
//  * Offset/Address/Size: 0x13C | 0x800A4A00 | size: 0x28
//  */
// void TakeGameMemSnapshot::FormatImpl<BasicString<char, Detail::TempStringAllocator> >::operator BasicString<
//     char, Detail::TempStringAllocator>() const
// {
// }

// /**
//  * Offset/Address/Size: 0x164 | 0x800A4A28 | size: 0xD74
//  */
// void TakeGameMemSnapshot::FormatImpl<BasicString<char, Detail::TempStringAllocator> >::operator% <unsigned int>(const unsigned int&)
// {
// }

// /**
//  * Offset/Address/Size: 0xED8 | 0x800A579C | size: 0xD74
//  */
// void TakeGameMemSnapshot::FormatImpl<BasicString<char, Detail::TempStringAllocator> >::operator% <unsigned long>(const unsigned long&)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x800A6510 | size: 0x30
//  */
// void TakeGameMemSnapshot::LexicalCast<BasicString<char, Detail::TempStringAllocator>, unsigned long>(const unsigned long&)
// {
// }

// /**
//  * Offset/Address/Size: 0x30 | 0x800A6540 | size: 0x100
//  */
// void TakeGameMemSnapshot::Detail::LexicalCastImpl<BasicString<char, Detail::TempStringAllocator>, unsigned long>::Do(unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x130 | 0x800A6640 | size: 0x30
//  */
// void TakeGameMemSnapshot::LexicalCast<BasicString<char, Detail::TempStringAllocator>, unsigned int>(const unsigned int&)
// {
// }

// /**
//  * Offset/Address/Size: 0x160 | 0x800A6670 | size: 0x100
//  */
// void TakeGameMemSnapshot::Detail::LexicalCastImpl<BasicString<char, Detail::TempStringAllocator>, unsigned int>::Do(unsigned int)
// {
// }
