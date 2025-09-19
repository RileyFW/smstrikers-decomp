#ifndef _GAMEINFO_H_
#define _GAMEINFO_H_

#include "Game/FE/feInput.h"
#include "types.h"

#include "NL/nlSingleton.h"
#include "NL/nlConfig.h"

#include "Game/GameTweaks.h"

#include "Game/DB/UserOptions.h"

// enum eSkillLevel
// {
//     TRAINING = 0,
//     ROOKIE = 1,
//     PROFESSIONAL = 2,
//     SUPERSTAR = 3,
//     LEGEND = 4,
// };

// struct GameplaySettings
// {
//     /* 0x0 */ eSkillLevel SkillLevel;
//     /* 0x4 */ s32 GameTime;
//     /* 0x8 */ bool PowerUps;
//     /* 0x9 */ bool Shoot2Score;
//     /* 0xA */ bool BowserAttackEnabled;
//     /* 0xB */ bool RumbleEnabled;
// }; // total size: 0xC

// struct PowerupSettings
// {
//     /* 0x0 */ bool RedShells;
//     /* 0x1 */ bool GreenShells;
//     /* 0x2 */ bool BlueShells;
//     /* 0x3 */ bool SpinyShells;
//     /* 0x4 */ bool Starman;
//     /* 0x5 */ bool Twister;
//     /* 0x6 */ bool Bobombs;
//     /* 0x7 */ bool Bananas;
// }; // total size: 0x8

struct UserInfo
{
    // total size: 0x113C
    /* 0x00 */ unsigned long mSaveID;
    u8 pad04[0x2C];                               // offset 0x4, size 0x4
                                                  // struct AudioSettings mAudioOptions; // offset 0x4, size 0x20
                                                  // struct VisualSettings mVisualOptions; // offset 0x24, size 0xC
    /* 0x30 */ GameplaySettings mGameplayOptions; // offset 0x30, size 0xC
    /* 0x3C */ PowerupSettings mPowerupOptions;   // offset 0x3C, size 0x8
    u8 pad0x44[0x10F8];
    // struct CheatSettings mCheatOptions; // offset 0x44, size 0x8
    // unsigned char mTrophies[2]; // offset 0x4C, size 0x2
    // struct Spoil mSpoils[8]; // offset 0x50, size 0x10C0
    // unsigned char mIsFlowerCupUnlocked; // offset 0x1110, size 0x1
    // unsigned char mIsStarCupUnlocked; // offset 0x1111, size 0x1
    // unsigned short mNumGamesPlayed; // offset 0x1112, size 0x2
    // unsigned short mNumGoalsScored; // offset 0x1114, size 0x2
    // unsigned short mNumSTSAttempts; // offset 0x1116, size 0x2
    // unsigned short mNumPerfectPasses; // offset 0x1118, size 0x2
    // unsigned short mNumHits; // offset 0x111A, size 0x2
    // struct BasicGameInfo mBowserCupFinalRound; // offset 0x111C, size 0x20
}; // total size: 0x113C

class Spoil
{
public:
};

enum eTrophyType
{
    eTrophyType_None = 0,
    eTrophyType_Bronze = 1,
    eTrophyType_Silver = 2,
    eTrophyType_Gold = 3,
};

enum eTeamID
{
    eTeamID_None = -1,
    eTeamID_Team0 = 0,
    eTeamID_Team1 = 1,
};

enum eSidekickID
{
    SK_MYSTERY = -2,
    SK_INVALID = -1,
    SK_TOAD = 0,
    SK_KOOPA = 1,
    SK_HAMMERBROS = 2,
    SK_BIRDO = 3,
    NUM_SIDEKICKS = 4,
};

enum eStadiumID
{
    eStadiumID_None = 0,
    eStadiumID_Stadium1 = 1,
    eStadiumID_Stadium2 = 2,
};

enum eUserGameResult
{
    eUserGameResult_None = 0,
    eUserGameResult_Win = 1,
    eUserGameResult_Loss = 2,
};

struct BaseCup
{
public:
    // 5 pure-virtuals (nulls in BaseCup vtable)
    void GetGameInfo(int team, int round);
    void* GetTeamStats(int team);
    int GetNumTeams();
    int GetNumRounds();
    void GetRoundResults(int round);

    // Implemented in BaseCup (present in BaseCup vtable)
    void SerializeData(void* dst) const;
    void DeserializeData(void* src);
    int GetSaveDataSize() const;

    /* 0x0, */ eTeamID mUserSelectedTeam;         // offset 0x0, size 0x4
    /* 0x4, */ eSidekickID mUserSelectedSidekick; // offset 0x4, size 0x4
    /* 0x8, */ s16 mRoundNumber;                  // offset 0x8, size 0x2
    /* 0xA, */ s16 mGameNumber;                   // offset 0xA, size 0x2
    /* 0xC, */ u16 mHumanTeams;                   // offset 0xC, size 0x2
    /* 0xE, */ bool mCupStarted;                  // offset 0xE, size 0x1
    /* 0x10 */ GameplaySettings mCupSettings;     // offset 0x10, size 0xC

    // /* 0x00 */ s32 m_unk_0x00;
    // /* 0x04 */ s32 m_unk_0x04;
    // /* 0x08 */ s16 m_unk_0x08;
    // /* 0x0A */ s16 m_unk_0x0A;
    // /* 0x0C */ s16 m_unk_0x0C;
    // /* 0x0D */ bool m_unk_0x0D;
    // /* 0x0E */ u8 m_unk_0x0E[0x0C];

    // /* 0x08 */ s32 m_unk_0x08;
    // /* 0x0C */ s32 m_unk_0x0C;
    // /* 0x10 */ s32 m_unk_0x10;
    // /* 0x14 */ s16 m_unk_0x14;
    // /* 0x16 */ s16 m_unk_0x16;
    // /* 0x18 */ s16 m_unk_0x18;
    // /* 0x1A */ s16 m_unk_0x1A;
    // /* 0x1C */ s16 m_unk_0x1C;
    // /* 0x1E */ s16 m_unk_0x1E;
}; // total size: 0x20

template <int NumTeams, int NumRounds>
class Cup : public BaseCup
{
public:
    virtual void GetGameInfo(int team, int round);
    virtual void* GetTeamStats(int team);
    virtual int GetNumTeams() { return NumTeams; }
    virtual int GetNumRounds() { return NumRounds; }
    virtual void GetRoundResults(int round);
};

template <int NumTeams>
class Knockout : public BaseCup
{
public:
    virtual void GetGameInfo(int team, int round);
    virtual void* GetTeamStats(int team);
    virtual int GetNumTeams() { return NumTeams; }
    virtual int GetNumRounds() { return 0; }
    virtual void GetRoundResults(int round);
};

// typedef struct BaseCup
// {
//     /* 0x00 */ s32 unk0;  /* inferred */
//     /* 0x04 */ s32 unk4;  /* inferred */
//     /* 0x08 */ s32 unk8;  /* inferred */
//     /* 0x0C */ s32 unkC;  /* inferred */
//     /* 0x10 */ s32 unk10; /* inferred */
// } BaseCup;                /* size >= 0x14 */

typedef struct BasicGameInfo
{
    /* 0x00 */ s32 unk0;  /* inferred */
    /* 0x04 */ s32 unk4;  /* inferred */
    /* 0x08 */ s32 unk8;  /* inferred */
    /* 0x0C */ s32 unkC;  /* inferred */
    /* 0x10 */ s32 unk10; /* inferred */
    /* 0x14 */ s16 unk14; /* inferred */
    /* 0x16 */ s16 unk16; /* inferred */
    /* 0x18 */ s16 unk18; /* inferred */
    /* 0x1A */ s16 unk1A; /* inferred */
    /* 0x1C */ s16 unk1C; /* inferred */
    /* 0x1E */ s16 unk1E; /* inferred */
} BasicGameInfo;

// typedef struct Cup<4, 3>
// {
//     /* 0x000 */ s32 unk0;         /* inferred */
//     /* 0x004 */ s32 unk4;         /* inferred */
//     /* 0x008 */ s32 unk8;         /* inferred */
//     /* 0x00C */ s32 unkC;         /* inferred */
//     /* 0x010 */ s32 unk10;        /* inferred */
//     /* 0x014 */ char pad14[0xC];  /* maybe part of unk10[4]? */
//     /* 0x020 */ s32 unk20;        /* inferred */
//     /* 0x024 */ char pad24[0xBC]; /* maybe part of unk20[0x30]? */
//     /* 0x0E0 */ s32 unkE0;        /* inferred */
//     /* 0x0E4 */ char padE4[0xFC]; /* maybe part of unkE0[0x40]? */
//     /* 0x1E0 */ s32 unk1E0;       /* inferred */
// } Cup<4, 3>;

class CupRecord
{
public:
};

class SomeClass
{
public:
    /* 0x0000 */ eTeamID m_unk_0x00;
    /* 0x0004 */ eSidekickID m_unk_0x04;
    /* 0x0008 */ u32 m_unk_0x08;
    /* 0x000C */ s16 m_unk_0x0C;
};

class GameInfoManager : public nlSingleton<GameInfoManager>
{
public:
    enum eGameModes
    {
        eGameModes_None = 0,
        eGameModes_Cup = 1,
        eGameModes_Tournament = 2,
    };

public:
    GameInfoManager();
    virtual ~GameInfoManager();

    void GetTeam(short) const;
    void SetTeam(short, eTeamID);
    void GetSidekick(short) const;
    void SetSidekick(short, eSidekickID);
    void GetNumPlayingTeams() const;
    void GetNumRounds() const;
    void GetTeamStatsByIndex(unsigned short);
    void pGetTeamStatsByIndex(unsigned short);
    void SetPreviousTeamStats();
    void GetStadium() const;
    void GetMatchupInfo(short, unsigned short) const;
    void SetUserSelectedCupTeam(eTeamID);
    void SetUserSelectedCupSidekick(eSidekickID);
    void GetResultsOfLastUserGame() const;
    void SetResultsOfLastUserGame(eUserGameResult);
    void GetCurrentRoundNumber() const;
    void GetNextRoundNumber(short) const;
    void GetPreviousRoundNumber(short) const;
    void GetFirstRoundNumber() const;
    void GetNumGamesPerRound(int) const;
    void GetUserSelectedCupTeam() const;
    void SetStadium(eStadiumID);
    void PickStadium(bool, eStadiumID) const;
    void GetPlayingSide(unsigned short) const;
    void SetPlayingSide(unsigned short, short);
    void GetNumPlayers() const;
    void ResetPlayingSides();
    void SetupRoundRobinSchedule(eTeamID*, eSidekickID*);
    void SetupBowserKnockout();
    void SetupTournamentKnockout(eTeamID*, eSidekickID*);
    void SetupKnockoutRound(short);
    void DetermineNextMatchups(int);
    void IncreaseRoundNumber();
    void IncreaseGameNumber(bool);
    void GetNumHumanTeams();
    void GetCup(GameInfoManager::eGameModes);
    void IsUserQualified(GameInfoManager::eGameModes) const;
    void SetMode(GameInfoManager::eGameModes);
    void GetMemoryCardDataSize() const;
    void GetMemoryCardData(void*);
    void SetMemoryCardData(void*);
    void CheckSaveIDChanged(void*);
    void HasTrophy(eTrophyType) const;
    void GetMilestoneLevel(eTrophyType) const;
    void IsInRegularCupMode() const;
    void IsInSuperCupMode() const;
    void IsInCupMode() const;
    void IsInCupOrTournamentMode() const;
    void IsInDemoMode() const;
    void IsInFriendlyMode() const;
    void IsInTournamentMode() const;
    void GetAudioOptions();
    const GameplaySettings& GetGameplayOptions() const;
    const PowerupSettings& GetPowerupOptions() const;
    void OnPreGameState();
    void OnPostGameState();
    void ApplyDifficultySettings();
    void GetTrophyTypeByCurrentMode() const;
    void IsPossibleCupMatch() const;
    void OnPreCupGameState();
    void OnPostCupGameState();
    void DetermineNextCupScreen();
    void DetermineUserPlacement(Spoil*);
    void TimeStampCupEnd();
    void FindWinningTeam();
    void IsKongaUnlocked() const;
    void IsYoshiUnlocked() const;
    void IsForbiddenUnlocked() const;
    void IsSuperStadiumUnlocked() const;
    void IsSuperTeamUnlocked() const;
    void IsSuperCupModeUnlocked() const;
    void IsLegendSkillUnlocked() const;
    void IsAllSTSCheatUnlocked() const;
    void IsTiltCheatUnlocked() const;
    void IsGlassJawGoalieUnlocked() const;
    void IsUnlimtedPowerupsUnlocked() const;
    void IsCustomShellsUnlocked() const;
    void IsCustomEnhanceUnlocked() const;
    void IsCustomGiantUnlocked() const;
    void IsCustomExplosiveUnlocked() const;
    void IsCustomFreezingUnlocked() const;
    void HasHumanGameBeenPlayed() const;
    void SetRoundResult(bool, int);
    void IsStunnedGoaliesOn() const;
    void IsInfinitePowerupsOn() const;
    void IsTiltingFieldOn() const;
    void IsPerfectStrikesOn() const;
    void IsBowserAttackEnabled() const;
    void GetSkillLevel();
    void GetSkillLevelAsDifficultyID();
    void GetCustomPowerups() const;

    // /* 0x0004 */ u8 pad0[0x495C];
    // /* 0x4960 */ SomeClass* m_unk_0x4960;

    // BasicGameInfo* mGameInfo[11];                 // offset 0x10, size 0x2C
    // enum eUserGameResult mUserLastResults[11];    // offset 0x3C, size 0x2C
    // enum eUserGameResult mCupMatchRequirement;    // offset 0x68, size 0x4
    // unsigned char mDoingKnockout;                 // offset 0x6C, size 0x1
    // unsigned char mDidRoundJustEnd;               // offset 0x6D, size 0x1
    // enum eDifficultyID mCurrentDifficulty[2];     // offset 0x70, size 0x8
    // struct Cup mMushroomCupSeries;                // offset 0x78, size 0x1E4
    // struct Cup mFlowerCupSeries;                  // offset 0x25C, size 0x388
    // struct Cup mStarCupSeries;                    // offset 0x5E4, size 0x5A8
    // struct Cup mBowserCupSeries;                  // offset 0xB8C, size 0x5A8
    // struct Knockout mBowserCupKnockout;           // offset 0x1134, size 0x184
    // struct Cup mSuperMushroomCupSeries;           // offset 0x12B8, size 0x2A8
    // struct Cup mSuperFlowerCupSeries;             // offset 0x1560, size 0x56C
    // struct Cup mSuperStarCupSeries;               // offset 0x1ACC, size 0x930
    // struct Cup mSuperBowserCupSeries;             // offset 0x23FC, size 0x930
    // struct Knockout mSuperBowserCupKnockout;      // offset 0x2D2C, size 0x184
    // int mCheckpointTeamPoints[9];                 // offset 0x2EB0, size 0x24
    int mCheckpointTeamPoints[9]; // offset 0x2EB0, size 0x24
    u8 _pad0x04[0x2EAC];
    /* 0x2ED4*/ UserInfo mUserInfo; // offset 0x2ED4, size 0x113C
    // class CustomTournament mCustomTournamentInfo; // offset 0x4010, size 0x944
    u8 _padCustomTourtament[0x944];
    eGameModes mCurrentMode;         // offset 0x4954, size 0x4
    bool mDemoEnabled;               // offset 0x4958, size 0x1
    bool mIsInStrikers101Mode;       // offset 0x4959, size 0x1
    bool mGoToChooseCaptains;        // offset 0x495A, size 0x1
    eFEINPUT_PAD mMainUserPadNumber; // offset 0x495C, size 0x4
    /* 0x4960 */ BaseCup* mCurrentCup;
    /* 0x4964 */ BaseCup* mPreviousCup;
    // struct PlayerStats mUserStats[4];             // offset 0x4968, size 0xD0
    // struct TeamStats mPreviousTeamStats[8];       // offset 0x4A38, size 0x200
    // unsigned char mUseCurGameSettings;            // offset 0x4C38, size 0x1
    // unsigned char mDisplayTrophy[6];              // offset 0x4C39, size 0x6
    // enum eMilestoneColour mTrophyColourState[5];  // offset 0x4C40, size 0x14
    // unsigned int mPreGameUnlockedState;           // offset 0x4C54, size 0x4
    // unsigned int mUnlockedTriggers;               // offset 0x4C58, size 0x4
    // enum eStadiumID mLastHumanStadium;            // offset 0x4C5C, size 0x4

    u8 _pad0x4968[0x2F8];

    /* 0x4C60 */ AudioSettings mCurGameAudioSettings; // offset 0x4C60, size 0x20
}; // total size: 0x4C80

// class Cup<8, 14>
// {
// public:
//     void GetTeamStats(int);
//     void GetSaveDataSize() const;
//     void DeserializeData(void*);
//     void SerializeData(void*) const;
//     void GetGameInfo(int, int);
//     void GetNumTeams();
//     void GetNumRounds();
//     void GetRoundResults(int);
// };

// class Cup<8, 7>
// {
// public:
//     void GetTeamStats(int);
//     void GetSaveDataSize() const;
//     void DeserializeData(void*);
//     void SerializeData(void*) const;
//     void GetGameInfo(int, int);
//     void GetNumTeams();
//     void GetNumRounds();
//     void GetRoundResults(int);
// };

// class Cup<6, 10>
// {
// public:
//     void GetSaveDataSize() const;
//     void DeserializeData(void*);
//     void SerializeData(void*) const;
//     void GetGameInfo(int, int);
//     void GetTeamStats(int);
//     void GetNumTeams();
//     void GetNumRounds();
//     void GetRoundResults(int);
// };

// class Cup<4, 6>
// {
// public:
//     void GetSaveDataSize() const;
//     void DeserializeData(void*);
//     void SerializeData(void*) const;
//     void GetGameInfo(int, int);
//     void GetTeamStats(int);
//     void GetNumTeams();
//     void GetNumRounds();
//     void GetRoundResults(int);
// };

// class Knockout<4>
// {
// public:
//     void GetSaveDataSize() const;
//     void DeserializeData(void*);
//     void SerializeData(void*) const;
//     void GetGameInfo(int, int);
//     void GetTeamStats(int);
//     void GetNumTeams();
//     void GetNumRounds();
//     void GetRoundResults(int);
// };

// class Cup<6, 5>
// {
// public:
//     void GetSaveDataSize() const;
//     void DeserializeData(void*);
//     void SerializeData(void*) const;
//     void GetGameInfo(int, int);
//     void GetTeamStats(int);
//     void GetNumTeams();
//     void GetNumRounds();
//     void GetRoundResults(int);
// };

// class Cup<4, 3>
// {
// public:
//     void GetSaveDataSize() const;
//     void DeserializeData(void*);
//     void SerializeData(void*) const;
//     void GetGameInfo(int, int);
//     void GetTeamStats(int);
//     void GetNumTeams();
//     void GetNumRounds();
//     void GetRoundResults(int);
// };

// class Spoil
// {
// public:
//     Spoil();
// };

// class CupRecord
// {
// public:
//     CupRecord();
// };

// class BaseCup
// {
// public:
//     void SerializeData(void*) const;
//     void DeserializeData(void*);
//     void GetSaveDataSize() const;
// };

// class Config
// {
// public:
//     void Get<BasicString<char, Detail::TempStringAllocator>>(const char*, BasicString<char, Detail::TempStringAllocator>);
//     void TagValuePair::Get<BasicString<char, Detail::TempStringAllocator>>() const;
// };

// class BasicGameInfo
// {
// public:
//     BasicGameInfo();
// };

#endif // _GAMEINFO_H_
