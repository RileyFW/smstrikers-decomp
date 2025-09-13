#include "Game/GameInfo.h"

#include "NL/nlMemory.h"

// nlSingleton<GameInfoManager> GameInfoManager::s_pInstance;

// /**
//  * Offset/Address/Size: 0x0 | 0x8018151C | size: 0x44
//  */
// BasicGameInfo::BasicGameInfo()
// {
// }

// /**
//  * Offset/Address/Size: 0xA8 | 0x80181498 | size: 0x84
//  */
// void Config::TagValuePair::Get<BasicString<char, Detail::TempStringAllocator>>() const
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x801813F0 | size: 0xA8
//  */
// void Config::Get<BasicString<char, Detail::TempStringAllocator>>(const char*, BasicString<char, Detail::TempStringAllocator>)
// {
// }

// /**
//  * Offset/Address/Size: 0x1328 | 0x801813E0 | size: 0x10
//  */
// void Cup<4, 3>::GetRoundResults(int)
// {
// }

// /**
//  * Offset/Address/Size: 0x1320 | 0x801813D8 | size: 0x8
//  */
// void Cup<4, 3>::GetNumRounds()
// {
// }

// /**
//  * Offset/Address/Size: 0x1318 | 0x801813D0 | size: 0x8
//  */
// void Cup<4, 3>::GetNumTeams()
// {
// }

// /**
//  * Offset/Address/Size: 0x1304 | 0x801813BC | size: 0x14
//  */
// void Cup<4, 3>::GetTeamStats(int)
// {
// }

// /**
//  * Offset/Address/Size: 0x12E8 | 0x801813A0 | size: 0x1C
//  */
// void Cup<4, 3>::GetGameInfo(int, int)
// {
// }

// /**
//  * Offset/Address/Size: 0x12D8 | 0x80181390 | size: 0x10
//  */
// void Cup<6, 5>::GetRoundResults(int)
// {
// }

// /**
//  * Offset/Address/Size: 0x12D0 | 0x80181388 | size: 0x8
//  */
// void Cup<6, 5>::GetNumRounds()
// {
// }

// /**
//  * Offset/Address/Size: 0x12C8 | 0x80181380 | size: 0x8
//  */
// void Cup<6, 5>::GetNumTeams()
// {
// }

// /**
//  * Offset/Address/Size: 0x12B4 | 0x8018136C | size: 0x14
//  */
// void Cup<6, 5>::GetTeamStats(int)
// {
// }

// /**
//  * Offset/Address/Size: 0x1298 | 0x80181350 | size: 0x1C
//  */
// void Cup<6, 5>::GetGameInfo(int, int)
// {
// }

// /**
//  * Offset/Address/Size: 0x1288 | 0x80181340 | size: 0x10
//  */
// void Cup<8, 7>::GetRoundResults(int)
// {
// }

// /**
//  * Offset/Address/Size: 0x1280 | 0x80181338 | size: 0x8
//  */
// void Cup<8, 7>::GetNumRounds()
// {
// }

// /**
//  * Offset/Address/Size: 0x1278 | 0x80181330 | size: 0x8
//  */
// void Cup<8, 7>::GetNumTeams()
// {
// }

// /**
//  * Offset/Address/Size: 0x125C | 0x80181314 | size: 0x1C
//  */
// void Cup<8, 7>::GetGameInfo(int, int)
// {
// }

// /**
//  * Offset/Address/Size: 0x124C | 0x80181304 | size: 0x10
//  */
// void Cup<4, 6>::GetRoundResults(int)
// {
// }

// /**
//  * Offset/Address/Size: 0x1244 | 0x801812FC | size: 0x8
//  */
// void Cup<4, 6>::GetNumRounds()
// {
// }

// /**
//  * Offset/Address/Size: 0x123C | 0x801812F4 | size: 0x8
//  */
// void Cup<4, 6>::GetNumTeams()
// {
// }

// /**
//  * Offset/Address/Size: 0x1228 | 0x801812E0 | size: 0x14
//  */
// void Cup<4, 6>::GetTeamStats(int)
// {
// }

// /**
//  * Offset/Address/Size: 0x120C | 0x801812C4 | size: 0x1C
//  */
// void Cup<4, 6>::GetGameInfo(int, int)
// {
// }

// /**
//  * Offset/Address/Size: 0x11FC | 0x801812B4 | size: 0x10
//  */
// void Cup<6, 10>::GetRoundResults(int)
// {
// }

// /**
//  * Offset/Address/Size: 0x11F4 | 0x801812AC | size: 0x8
//  */
// void Cup<6, 10>::GetNumRounds()
// {
// }

// /**
//  * Offset/Address/Size: 0x11EC | 0x801812A4 | size: 0x8
//  */
// void Cup<6, 10>::GetNumTeams()
// {
// }

// /**
//  * Offset/Address/Size: 0x11D8 | 0x80181290 | size: 0x14
//  */
// void Cup<6, 10>::GetTeamStats(int)
// {
// }

// /**
//  * Offset/Address/Size: 0x11BC | 0x80181274 | size: 0x1C
//  */
// void Cup<6, 10>::GetGameInfo(int, int)
// {
// }

// /**
//  * Offset/Address/Size: 0x11AC | 0x80181264 | size: 0x10
//  */
// void Cup<8, 14>::GetRoundResults(int)
// {
// }

// /**
//  * Offset/Address/Size: 0x11A4 | 0x8018125C | size: 0x8
//  */
// void Cup<8, 14>::GetNumRounds()
// {
// }

// /**
//  * Offset/Address/Size: 0x119C | 0x80181254 | size: 0x8
//  */
// void Cup<8, 14>::GetNumTeams()
// {
// }

// /**
//  * Offset/Address/Size: 0x1180 | 0x80181238 | size: 0x1C
//  */
// void Cup<8, 14>::GetGameInfo(int, int)
// {
// }

// /**
//  * Offset/Address/Size: 0x1170 | 0x80181228 | size: 0x10
//  */
// void Knockout<4>::GetRoundResults(int)
// {
// }

// /**
//  * Offset/Address/Size: 0x1168 | 0x80181220 | size: 0x8
//  */
// void Knockout<4>::GetNumRounds()
// {
// }

// /**
//  * Offset/Address/Size: 0x1160 | 0x80181218 | size: 0x8
//  */
// void Knockout<4>::GetNumTeams()
// {
// }

// /**
//  * Offset/Address/Size: 0x114C | 0x80181204 | size: 0x14
//  */
// void Knockout<4>::GetTeamStats(int)
// {
// }

// /**
//  * Offset/Address/Size: 0x1024 | 0x801810DC | size: 0x128
//  */
// void Knockout<4>::GetGameInfo(int, int)
// {
// }

/**
 * Offset/Address/Size: 0x101C | 0x801810D4 | size: 0x8
 */
int BaseCup::GetSaveDataSize() const
{
    return 0x1B;
}

/**
 * Offset/Address/Size: 0xF64 | 0x8018101C | size: 0xB8
 */
void BaseCup::DeserializeData(void* src)
{
    unsigned char* p = (unsigned char*)src;
    memcpy(&mUserSelectedTeam, p, 4);
    p += 4;
    memcpy(&mUserSelectedSidekick, p, 4);
    p += 4;
    memcpy(&mRoundNumber, p, 2);
    p += 2;
    memcpy(&mGameNumber, p, 2);
    p += 2;
    memcpy(&mHumanTeams, p, 2);
    p += 2;
    memcpy(&mCupStarted, p, 1);
    p += 1;
    memcpy(&mCupSettings, p, 0x0C);
}

/**
 * Offset/Address/Size: 0xEA4 | 0x80180F5C | size: 0xC0
 */
void BaseCup::SerializeData(void* dst) const
{
    unsigned char* p = (unsigned char*)dst;
    memcpy(p, &mUserSelectedTeam, 4);
    p += 4;
    memcpy(p, &mUserSelectedSidekick, 4);
    p += 4;
    memcpy(p, &mRoundNumber, 2);
    p += 2;
    memcpy(p, &mGameNumber, 2);
    p += 2;
    memcpy(p, &mHumanTeams, 2);
    p += 2;
    memcpy(p, &mCupStarted, 1);
    p += 1;
    memcpy(p, &mCupSettings, 0x0C);
}

// /**
//  * Offset/Address/Size: 0xE54 | 0x80180F0C | size: 0x50
//  */
// CupRecord::CupRecord()
// {
// }

// /**
//  * Offset/Address/Size: 0xDF0 | 0x80180EA8 | size: 0x64
//  */
// Spoil::Spoil()
// {
// }

// /**
//  * Offset/Address/Size: 0xCF4 | 0x80180DAC | size: 0xFC
//  */
// void Cup<4, 3>::SerializeData(void*) const
// {
// }

// /**
//  * Offset/Address/Size: 0xBF8 | 0x80180CB0 | size: 0xFC
//  */
// void Cup<6, 5>::SerializeData(void*) const
// {
// }

// /**
//  * Offset/Address/Size: 0xAFC | 0x80180BB4 | size: 0xFC
//  */
// void Cup<8, 7>::SerializeData(void*) const
// {
// }

// /**
//  * Offset/Address/Size: 0xA00 | 0x80180AB8 | size: 0xFC
//  */
// void Knockout<4>::SerializeData(void*) const
// {
// }

// /**
//  * Offset/Address/Size: 0x904 | 0x801809BC | size: 0xFC
//  */
// void Cup<4, 6>::SerializeData(void*) const
// {
// }

// /**
//  * Offset/Address/Size: 0x808 | 0x801808C0 | size: 0xFC
//  */
// void Cup<6, 10>::SerializeData(void*) const
// {
// }

// /**
//  * Offset/Address/Size: 0x70C | 0x801807C4 | size: 0xFC
//  */
// void Cup<8, 14>::SerializeData(void*) const
// {
// }

// /**
//  * Offset/Address/Size: 0x618 | 0x801806D0 | size: 0xF4
//  */
// void Cup<4, 3>::DeserializeData(void*)
// {
// }

// /**
//  * Offset/Address/Size: 0x610 | 0x801806C8 | size: 0x8
//  */
// void Cup<4, 3>::GetSaveDataSize() const
// {
// }

// /**
//  * Offset/Address/Size: 0x51C | 0x801805D4 | size: 0xF4
//  */
// void Cup<6, 5>::DeserializeData(void*)
// {
// }

// /**
//  * Offset/Address/Size: 0x514 | 0x801805CC | size: 0x8
//  */
// void Cup<6, 5>::GetSaveDataSize() const
// {
// }

// /**
//  * Offset/Address/Size: 0x420 | 0x801804D8 | size: 0xF4
//  */
// void Cup<8, 7>::DeserializeData(void*)
// {
// }

// /**
//  * Offset/Address/Size: 0x418 | 0x801804D0 | size: 0x8
//  */
// void Cup<8, 7>::GetSaveDataSize() const
// {
// }

// /**
//  * Offset/Address/Size: 0x324 | 0x801803DC | size: 0xF4
//  */
// void Knockout<4>::DeserializeData(void*)
// {
// }

// /**
//  * Offset/Address/Size: 0x31C | 0x801803D4 | size: 0x8
//  */
// void Knockout<4>::GetSaveDataSize() const
// {
// }

// /**
//  * Offset/Address/Size: 0x228 | 0x801802E0 | size: 0xF4
//  */
// void Cup<4, 6>::DeserializeData(void*)
// {
// }

// /**
//  * Offset/Address/Size: 0x220 | 0x801802D8 | size: 0x8
//  */
// void Cup<4, 6>::GetSaveDataSize() const
// {
// }

// /**
//  * Offset/Address/Size: 0x12C | 0x801801E4 | size: 0xF4
//  */
// void Cup<6, 10>::DeserializeData(void*)
// {
// }

// /**
//  * Offset/Address/Size: 0x124 | 0x801801DC | size: 0x8
//  */
// void Cup<6, 10>::GetSaveDataSize() const
// {
// }

// /**
//  * Offset/Address/Size: 0x30 | 0x801800E8 | size: 0xF4
//  */
// void Cup<8, 14>::DeserializeData(void*)
// {
// }

// /**
//  * Offset/Address/Size: 0x28 | 0x801800E0 | size: 0x8
//  */
// void Cup<8, 14>::GetSaveDataSize() const
// {
// }

// /**
//  * Offset/Address/Size: 0x14 | 0x801800CC | size: 0x14
//  */
// void Cup<8, 7>::GetTeamStats(int)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x801800B8 | size: 0x14
//  */
// void Cup<8, 14>::GetTeamStats(int)
// {
// }

/**
 * Offset/Address/Size: 0x9E90 | 0x8017F534 | size: 0xB84
 */
GameInfoManager::GameInfoManager()
{
}

/**
 * Offset/Address/Size: 0x9E1C | 0x8017F4C0 | size: 0x74
 */
GameInfoManager::~GameInfoManager()
{
}

/**
 * Offset/Address/Size: 0x9DEC | 0x8017F490 | size: 0x30
 */
void GameInfoManager::GetTeam(short) const
{
}

/**
 * Offset/Address/Size: 0x9DCC | 0x8017F470 | size: 0x20
 */
void GameInfoManager::SetTeam(short, eTeamID)
{
}

/**
 * Offset/Address/Size: 0x9D94 | 0x8017F438 | size: 0x38
 */
void GameInfoManager::GetSidekick(short) const
{
}

/**
 * Offset/Address/Size: 0x9D70 | 0x8017F414 | size: 0x24
 */
void GameInfoManager::SetSidekick(short, eSidekickID)
{
}

/**
 * Offset/Address/Size: 0x9D24 | 0x8017F3C8 | size: 0x4C
 */
void GameInfoManager::GetNumPlayingTeams() const
{
}

/**
 * Offset/Address/Size: 0x9CF4 | 0x8017F398 | size: 0x30
 */
void GameInfoManager::GetNumRounds() const
{
}

/**
 * Offset/Address/Size: 0x9AB8 | 0x8017F15C | size: 0x23C
 */
void GameInfoManager::GetTeamStatsByIndex(unsigned short)
{
}

/**
 * Offset/Address/Size: 0x9A38 | 0x8017F0DC | size: 0x80
 */
void GameInfoManager::pGetTeamStatsByIndex(unsigned short)
{
}

/**
 * Offset/Address/Size: 0x96B4 | 0x8017ED58 | size: 0x384
 */
void GameInfoManager::SetPreviousTeamStats()
{
}

/**
 * Offset/Address/Size: 0x969C | 0x8017ED40 | size: 0x18
 */
void GameInfoManager::GetStadium() const
{
}

/**
 * Offset/Address/Size: 0x9574 | 0x8017EC18 | size: 0x128
 */
void GameInfoManager::GetMatchupInfo(short, unsigned short) const
{
}

/**
 * Offset/Address/Size: 0x953C | 0x8017EBE0 | size: 0x38
 */
void GameInfoManager::SetUserSelectedCupTeam(eTeamID team)
{
    s32* temp_r4;
    mCurrentCup->mUserSelectedTeam = team;
    if (team != eTeamID_None)
    {
        mCurrentCup->mRoundNumber = 0;
        mCurrentCup->mRoundNumber = mCurrentCup->mRoundNumber | (1 << team);
    }
}

/**
 * Offset/Address/Size: 0x9530 | 0x8017EBD4 | size: 0xC
 */
void GameInfoManager::SetUserSelectedCupSidekick(eSidekickID sidekick)
{
    mCurrentCup->mUserSelectedSidekick = sidekick;
}

/**
 * Offset/Address/Size: 0x951C | 0x8017EBC0 | size: 0x14
 */
void GameInfoManager::GetResultsOfLastUserGame() const
{
}

/**
 * Offset/Address/Size: 0x9508 | 0x8017EBAC | size: 0x14
 */
void GameInfoManager::SetResultsOfLastUserGame(eUserGameResult)
{
}

/**
 * Offset/Address/Size: 0x94FC | 0x8017EBA0 | size: 0xC
 */
void GameInfoManager::GetCurrentRoundNumber() const
{
}

/**
 * Offset/Address/Size: 0x9300 | 0x8017E9A4 | size: 0x1FC
 */
void GameInfoManager::GetNextRoundNumber(short) const
{
}

/**
 * Offset/Address/Size: 0x91E8 | 0x8017E88C | size: 0x118
 */
void GameInfoManager::GetPreviousRoundNumber(short) const
{
}

/**
 * Offset/Address/Size: 0x9180 | 0x8017E824 | size: 0x68
 */
void GameInfoManager::GetFirstRoundNumber() const
{
}

/**
 * Offset/Address/Size: 0x90AC | 0x8017E750 | size: 0xD4
 */
void GameInfoManager::GetNumGamesPerRound(int) const
{
}

/**
 * Offset/Address/Size: 0x90A0 | 0x8017E744 | size: 0xC
 */
void GameInfoManager::GetUserSelectedCupTeam() const
{
}

/**
 * Offset/Address/Size: 0x9088 | 0x8017E72C | size: 0x18
 */
void GameInfoManager::SetStadium(eStadiumID)
{
}

/**
 * Offset/Address/Size: 0x8C28 | 0x8017E2CC | size: 0x460
 */
void GameInfoManager::PickStadium(bool, eStadiumID) const
{
}

/**
 * Offset/Address/Size: 0x8C08 | 0x8017E2AC | size: 0x20
 */
void GameInfoManager::GetPlayingSide(unsigned short) const
{
}

/**
 * Offset/Address/Size: 0x8BE8 | 0x8017E28C | size: 0x20
 */
void GameInfoManager::SetPlayingSide(unsigned short, short)
{
}

/**
 * Offset/Address/Size: 0x8B38 | 0x8017E1DC | size: 0xB0
 */
void GameInfoManager::GetNumPlayers() const
{
}

/**
 * Offset/Address/Size: 0x8B10 | 0x8017E1B4 | size: 0x28
 */
void GameInfoManager::ResetPlayingSides()
{
}

/**
 * Offset/Address/Size: 0x8638 | 0x8017DCDC | size: 0x4D8
 */
void GameInfoManager::SetupRoundRobinSchedule(eTeamID*, eSidekickID*)
{
}

/**
 * Offset/Address/Size: 0x81CC | 0x8017D870 | size: 0x46C
 */
void GameInfoManager::SetupBowserKnockout()
{
}

/**
 * Offset/Address/Size: 0x7EF0 | 0x8017D594 | size: 0x2DC
 */
void GameInfoManager::SetupTournamentKnockout(eTeamID*, eSidekickID*)
{
}

/**
 * Offset/Address/Size: 0x78D8 | 0x8017CF7C | size: 0x618
 */
void GameInfoManager::SetupKnockoutRound(short)
{
}

/**
 * Offset/Address/Size: 0x7534 | 0x8017CBD8 | size: 0x3A4
 */
void GameInfoManager::DetermineNextMatchups(int)
{
}

/**
 * Offset/Address/Size: 0x71F4 | 0x8017C898 | size: 0x340
 */
void GameInfoManager::IncreaseRoundNumber()
{
}

/**
 * Offset/Address/Size: 0x70D8 | 0x8017C77C | size: 0x11C
 */
void GameInfoManager::IncreaseGameNumber(bool)
{
}

/**
 * Offset/Address/Size: 0x6E20 | 0x8017C4C4 | size: 0x2B8
 */
void GameInfoManager::GetNumHumanTeams()
{
}

/**
 * Offset/Address/Size: 0x6D70 | 0x8017C414 | size: 0xB0
 */
void GameInfoManager::GetCup(GameInfoManager::eGameModes)
{
}

/**
 * Offset/Address/Size: 0x6908 | 0x8017BFAC | size: 0x468
 */
void GameInfoManager::IsUserQualified(GameInfoManager::eGameModes) const
{
}

/**
 * Offset/Address/Size: 0x6794 | 0x8017BE38 | size: 0x174
 */
void GameInfoManager::SetMode(GameInfoManager::eGameModes)
{
}

/**
 * Offset/Address/Size: 0x6664 | 0x8017BD08 | size: 0x130
 */
void GameInfoManager::GetMemoryCardDataSize() const
{
}

/**
 * Offset/Address/Size: 0x642C | 0x8017BAD0 | size: 0x238
 */
void GameInfoManager::GetMemoryCardData(void*)
{
}

/**
 * Offset/Address/Size: 0x61F8 | 0x8017B89C | size: 0x234
 */
void GameInfoManager::SetMemoryCardData(void*)
{
}

/**
 * Offset/Address/Size: 0x61DC | 0x8017B880 | size: 0x1C
 */
void GameInfoManager::CheckSaveIDChanged(void*)
{
}

/**
 * Offset/Address/Size: 0x60C0 | 0x8017B764 | size: 0x11C
 */
void GameInfoManager::HasTrophy(eTrophyType) const
{
}

/**
 * Offset/Address/Size: 0x5F60 | 0x8017B604 | size: 0x160
 */
void GameInfoManager::GetMilestoneLevel(eTrophyType) const
{
}

/**
 * Offset/Address/Size: 0x5F38 | 0x8017B5DC | size: 0x28
 */
void GameInfoManager::IsInRegularCupMode() const
{
}

/**
 * Offset/Address/Size: 0x5F10 | 0x8017B5B4 | size: 0x28
 */
void GameInfoManager::IsInSuperCupMode() const
{
}

/**
 * Offset/Address/Size: 0x5EC0 | 0x8017B564 | size: 0x50
 */
void GameInfoManager::IsInCupMode() const
{
}

/**
 * Offset/Address/Size: 0x5E5C | 0x8017B500 | size: 0x64
 */
void GameInfoManager::IsInCupOrTournamentMode() const
{
}

/**
 * Offset/Address/Size: 0x5E48 | 0x8017B4EC | size: 0x14
 */
void GameInfoManager::IsInDemoMode() const
{
}

/**
 * Offset/Address/Size: 0x5E38 | 0x8017B4DC | size: 0x10
 */
void GameInfoManager::IsInFriendlyMode() const
{
}

/**
 * Offset/Address/Size: 0x5E24 | 0x8017B4C8 | size: 0x14
 */
void GameInfoManager::IsInTournamentMode() const
{
}

/**
 * Offset/Address/Size: 0x5E1C | 0x8017B4C0 | size: 0x8
 */
void GameInfoManager::GetAudioOptions()
{
}

/**
 * Offset/Address/Size: 0x5DE0 | 0x8017B484 | size: 0x3C
 */
const GameplaySettings& GameInfoManager::GetGameplayOptions() const
{
    FORCE_DONT_INLINE;
    return mUserInfo.mGameplayOptions;
}

/**
 * Offset/Address/Size: 0x5DD8 | 0x8017B47C | size: 0x8
 */
const PowerupSettings& GameInfoManager::GetPowerupOptions() const
{
    FORCE_DONT_INLINE;
    return mUserInfo.mPowerupOptions;
}

/**
 * Offset/Address/Size: 0x5040 | 0x8017A6E4 | size: 0xD98
 */
void GameInfoManager::OnPreGameState()
{
}

/**
 * Offset/Address/Size: 0x500C | 0x8017A6B0 | size: 0x34
 */
void GameInfoManager::OnPostGameState()
{
}

/**
 * Offset/Address/Size: 0x4E7C | 0x8017A520 | size: 0x190
 */
void GameInfoManager::ApplyDifficultySettings()
{
}

/**
 * Offset/Address/Size: 0x4E14 | 0x8017A4B8 | size: 0x68
 */
void GameInfoManager::GetTrophyTypeByCurrentMode() const
{
}

/**
 * Offset/Address/Size: 0x4DFC | 0x8017A4A0 | size: 0x18
 */
void GameInfoManager::IsPossibleCupMatch() const
{
}

/**
 * Offset/Address/Size: 0x38E8 | 0x80178F8C | size: 0x1514
 */
void GameInfoManager::OnPreCupGameState()
{
}

/**
 * Offset/Address/Size: 0x256C | 0x80177C10 | size: 0x137C
 */
void GameInfoManager::OnPostCupGameState()
{
}

/**
 * Offset/Address/Size: 0x23FC | 0x80177AA0 | size: 0x170
 */
void GameInfoManager::DetermineNextCupScreen()
{
}

/**
 * Offset/Address/Size: 0x1DA8 | 0x8017744C | size: 0x654
 */
void GameInfoManager::DetermineUserPlacement(Spoil*)
{
}

/**
 * Offset/Address/Size: 0x196C | 0x80177010 | size: 0x43C
 */
void GameInfoManager::TimeStampCupEnd()
{
}

/**
 * Offset/Address/Size: 0x13E4 | 0x80176A88 | size: 0x588
 */
void GameInfoManager::FindWinningTeam()
{
}

/**
 * Offset/Address/Size: 0x12F8 | 0x8017699C | size: 0xEC
 */
void GameInfoManager::IsKongaUnlocked() const
{
}

/**
 * Offset/Address/Size: 0x120C | 0x801768B0 | size: 0xEC
 */
void GameInfoManager::IsYoshiUnlocked() const
{
}

/**
 * Offset/Address/Size: 0x1120 | 0x801767C4 | size: 0xEC
 */
void GameInfoManager::IsForbiddenUnlocked() const
{
}

/**
 * Offset/Address/Size: 0x1034 | 0x801766D8 | size: 0xEC
 */
void GameInfoManager::IsSuperStadiumUnlocked() const
{
}

/**
 * Offset/Address/Size: 0xF48 | 0x801765EC | size: 0xEC
 */
void GameInfoManager::IsSuperTeamUnlocked() const
{
}

/**
 * Offset/Address/Size: 0xF24 | 0x801765C8 | size: 0x24
 */
void GameInfoManager::IsSuperCupModeUnlocked() const
{
}

/**
 * Offset/Address/Size: 0xF1C | 0x801765C0 | size: 0x8
 */
void GameInfoManager::IsLegendSkillUnlocked() const
{
}

/**
 * Offset/Address/Size: 0xE30 | 0x801764D4 | size: 0xEC
 */
void GameInfoManager::IsAllSTSCheatUnlocked() const
{
}

/**
 * Offset/Address/Size: 0xD44 | 0x801763E8 | size: 0xEC
 */
void GameInfoManager::IsTiltCheatUnlocked() const
{
}

/**
 * Offset/Address/Size: 0xC58 | 0x801762FC | size: 0xEC
 */
void GameInfoManager::IsGlassJawGoalieUnlocked() const
{
}

/**
 * Offset/Address/Size: 0xB6C | 0x80176210 | size: 0xEC
 */
void GameInfoManager::IsUnlimtedPowerupsUnlocked() const
{
}

/**
 * Offset/Address/Size: 0xA80 | 0x80176124 | size: 0xEC
 */
void GameInfoManager::IsCustomShellsUnlocked() const
{
}

/**
 * Offset/Address/Size: 0x994 | 0x80176038 | size: 0xEC
 */
void GameInfoManager::IsCustomEnhanceUnlocked() const
{
}

/**
 * Offset/Address/Size: 0x8A8 | 0x80175F4C | size: 0xEC
 */
void GameInfoManager::IsCustomGiantUnlocked() const
{
}

/**
 * Offset/Address/Size: 0x7BC | 0x80175E60 | size: 0xEC
 */
void GameInfoManager::IsCustomExplosiveUnlocked() const
{
}

/**
 * Offset/Address/Size: 0x6D0 | 0x80175D74 | size: 0xEC
 */
void GameInfoManager::IsCustomFreezingUnlocked() const
{
}

/**
 * Offset/Address/Size: 0x41C | 0x80175AC0 | size: 0x2B4
 */
void GameInfoManager::HasHumanGameBeenPlayed() const
{
}

/**
 * Offset/Address/Size: 0x2FC | 0x801759A0 | size: 0x120
 */
void GameInfoManager::SetRoundResult(bool, int)
{
}

/**
 * Offset/Address/Size: 0x29C | 0x80175940 | size: 0x60
 */
void GameInfoManager::IsStunnedGoaliesOn() const
{
}

/**
 * Offset/Address/Size: 0x23C | 0x801758E0 | size: 0x60
 */
void GameInfoManager::IsInfinitePowerupsOn() const
{
}

/**
 * Offset/Address/Size: 0x1DC | 0x80175880 | size: 0x60
 */
void GameInfoManager::IsTiltingFieldOn() const
{
}

/**
 * Offset/Address/Size: 0x17C | 0x80175820 | size: 0x60
 */
void GameInfoManager::IsPerfectStrikesOn() const
{
}

/**
 * Offset/Address/Size: 0x14C | 0x801757F0 | size: 0x30
 */
void GameInfoManager::IsBowserAttackEnabled() const
{
}

/**
 * Offset/Address/Size: 0xF8 | 0x8017579C | size: 0x54
 */
void GameInfoManager::GetSkillLevel()
{
}

/**
 * Offset/Address/Size: 0x60 | 0x80175704 | size: 0x98
 */
void GameInfoManager::GetSkillLevelAsDifficultyID()
{
}

/**
 * Offset/Address/Size: 0x0 | 0x801756A4 | size: 0x60
 */
void GameInfoManager::GetCustomPowerups() const
{
}
