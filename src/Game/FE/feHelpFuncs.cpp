#include "Game/FE/feHelpFuncs.h"

#include "Game/GameInfo.h"

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
void MakeTextBoxReallyWide(TLTextInstance&)
{
}

/**
 * Offset/Address/Size: 0x58 | 0x800A3114 | size: 0x14
 */
void GetCupStreamName(eTrophyType)
{
}

/**
 * Offset/Address/Size: 0x6C | 0x800A3128 | size: 0x84
 */
void GetMemCardDescription()
{
}

/**
 * Offset/Address/Size: 0xF0 | 0x800A31AC | size: 0x40
 */
void GetMemCardTitle()
{
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

// /**
//  * Offset/Address/Size: 0x698 | 0x800A3754 | size: 0x34
//  */
// void FECharacterSound::PlayCaptainSlideIn(eTeamID)
// {
// }

// /**
//  * Offset/Address/Size: 0x6CC | 0x800A3788 | size: 0x34
//  */
// void FECharacterSound::PlaySidekickName(eSidekickID)
// {
// }

// /**
//  * Offset/Address/Size: 0x700 | 0x800A37BC | size: 0x48
//  */
// void FECharacterSound::PlayCaptainName(eTeamID)
// {
// }

/**
 * Offset/Address/Size: 0x748 | 0x800A3804 | size: 0x94
 */
void EnableAutoPressed()
{
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
    s32 var_r0;

    switch (sidekickid)
    { /* irregular */
    case 3:
        var_r0 = 0;
        break;
    case 2:
        var_r0 = 3;
        break;
    case 1:
        var_r0 = 4;
        break;
    case 0:
        var_r0 = 8;
        break;
    case -2:
        var_r0 = 0xC;
        break;
    default:
        var_r0 = -1;
        break;
    }
    if (var_r0 != -1)
    {
        return CCToStringName[var_r0];
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
