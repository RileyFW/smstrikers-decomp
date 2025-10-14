#include "Game/GameInfo.h"
#include "NL/nlMemory.h"

extern bool g_e3_Build;

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
    mUserInfo.mSaveID = sizeof(mCustomTournamentInfo);
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
u16 GameInfoManager::GetNumPlayingTeams() const
{
    if (mCurrentMode == 0x4 || mCurrentMode == 0x8)
    {
        return 8;
    }

    return mCurrentCup->GetNumTeams();
}

/**
 * Offset/Address/Size: 0x9CF4 | 0x8017F398 | size: 0x30
 */
u16 GameInfoManager::GetNumRounds() const
{
    return mCurrentCup->GetNumRounds();
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
eStadiumID GameInfoManager::GetStadium() const
{
    return mGameInfo[mCurrentMode]->mStadiumIndex;
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
    mCurrentCup->mUserSelectedTeam = team;

    if (team != TEAM_INVALID)
    {
        mCurrentCup->mRoundNumber = 0;
        mCurrentCup->mRoundNumber = (s32)(mCurrentCup->mRoundNumber | (1 << team));
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
bool GameInfoManager::IsLegendSkillUnlocked() const
{
    return true;
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
bool GameInfoManager::IsPerfectStrikesOn() const
{
    return false;
}

/**
 * Offset/Address/Size: 0x14C | 0x801757F0 | size: 0x30
 */
bool GameInfoManager::IsBowserAttackEnabled() const
{
    if (g_e3_Build)
    {
        return false;
    }

    if (mIsInStrikers101Mode)
    {
        return false;
    }

    return mCurGameGameplayOptions.BowserAttackEnabled;
}

/**
 * Offset/Address/Size: 0xF8 | 0x8017579C | size: 0x54
 */
eSkillLevel GameInfoManager::GetSkillLevel()
{
    if (mIsInStrikers101Mode)
        return TRAINING;

    const eSkillLevel* p;

    if (mUseCurGameSettings)
    {
        p = &mCurGameGameplayOptions.SkillLevel;
    }
    else
    {
        if ((mCurrentMode == GM_FRIENDLY) || (mCurrentMode == GM_DEMO))
        {
            p = &mUserInfo.mGameplayOptions.SkillLevel;
        }
        else
        {
            p = &mCurrentCup->mCupSettings.SkillLevel;
        }
    }

    return *p;
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
CustomPowerups GameInfoManager::GetCustomPowerups() const
{
    if (mIsInStrikers101Mode)
    {
        return CP_OFF;
    }

    bool useCheatSettings;
    eGameModes currentMode = mCurrentMode;
    if ((currentMode == GM_FRIENDLY) || (currentMode == GM_TOURNAMENT))
    {
        useCheatSettings = false;
        if ((currentMode == GM_FRIENDLY) || (currentMode == GM_TOURNAMENT))
        {
            useCheatSettings = true;
        }
        if (useCheatSettings)
        {
            return mUserInfo.mCheatOptions.mCustomPowerups;
        }
        return CP_OFF;
    }
    return CP_OFF;
}
