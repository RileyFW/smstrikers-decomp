#ifndef _CUP_H_
#define _CUP_H_

#include "types.h"
#include "Game/Team.h"
#include "Game/DB/UserOptions.h"
#include "Game/DB/StatsTracker.h"

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
    STAD_INVALID = -1,
    STAD_MARIO_STADIUM = 0,
    STAD_PEACH_TOAD_STADIUM = 1,
    STAD_DK_DAISY = 2,
    STAD_WARIO_STADIUM = 3,
    STAD_YOSHI_STADIUM = 4,
    STAD_SUPER_STADIUM = 5,
    STAD_FORBIDDEN_DOME = 6,
    MAX_STADIUMS = 7,
};

struct BasicGameInfo
{
    /* 0x00 */ eTeamID mTeamIndex[2];
    /* 0x08 */ eSidekickID mSidekickIndex[2];
    /* 0x10 */ eStadiumID mStadiumIndex;
    /* 0x14 */ s16 mPadSides[4];
    /* 0x1C */ s16 mFinalScore[2];
}; // total size: 0x20

struct CupRecord
{
    /* 0x00 */ OSCalendarTime mDate;
    /* 0x28 */ signed char mPlace;
    /* 0x2C */ eTeamID mTeam;
    /* 0x30 */ GameplaySettings::eSkillLevel mDifficulty;
}; // total size: 0x34

struct BaseCup
{
    /* 0x0, */ eTeamID mUserSelectedTeam;
    /* 0x4, */ eSidekickID mUserSelectedSidekick;
    /* 0x8, */ s16 mGameNumber;
    /* 0xA, */ u16 mHumanTeams;
    /* 0xC, */ u16 mRoundNumber;
    /* 0xE, */ bool mCupStarted;
    /* 0x10 */ GameplaySettings mCupSettings;

    virtual BasicGameInfo* GetGameInfo(int team, int round) = 0;
    virtual TeamStats* GetTeamStats(int team) = 0;
    virtual u16 GetNumTeams() = 0;
    virtual u16 GetNumRounds() = 0;
    virtual signed char* GetRoundResults(int round) = 0;
    virtual void* SerializeData(void* dst) const
    {
        u8* p = (u8*)dst;
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
        memcpy(p, &mCupSettings, sizeof(mCupSettings));
        return (p + 0x0C);
    };
    virtual void* DeserializeData(void* src)
    {
        src = (u8*)memcpy(&mUserSelectedTeam, src, 4) + 4;
        src = (u8*)memcpy(&mUserSelectedSidekick, src, 4) + 4;
        src = (u8*)memcpy(&mRoundNumber, src, 2) + 2;
        src = (u8*)memcpy(&mGameNumber, src, 2) + 2;
        src = (u8*)memcpy(&mHumanTeams, src, 2) + 2;
        src = (u8*)memcpy(&mCupStarted, src, 1) + 1;
        src = (u8*)memcpy(&mCupSettings, src, sizeof(mCupSettings)) + sizeof(mCupSettings);
        return src;
    };
    virtual int GetSaveDataSize() const { return 0x1B; };
}; // total size: 0x20

template <u16 Teams, u16 Rounds>
struct Cup : public BaseCup
{
    virtual BasicGameInfo* GetGameInfo(int team, int round) { return &mGameInfo[team][round]; };
    virtual TeamStats* GetTeamStats(int team) { return &mTeamStats[team]; };
    virtual u16 GetNumTeams() { return Teams; };
    virtual u16 GetNumRounds() { return Rounds; };
    virtual signed char* GetRoundResults(int round) { return &mRoundResults[round]; };
    virtual void* SerializeData(void* dst) const
    {
        // TODO: Implement
        return nullptr;
    }
    virtual void* DeserializeData(void* src)
    {
        // TODO: Implement
        return nullptr;
    }
    virtual int GetSaveDataSize() const { return 0x1B; };

    BasicGameInfo mGameInfo[Rounds][Teams / 2];
    TeamStats mTeamStats[Teams];
    signed char mRoundResults[Rounds];
};

template <u16 Teams>
struct Knockout : public BaseCup
{
    virtual BasicGameInfo* GetGameInfo(int team, int round);
    virtual TeamStats* GetTeamStats(int team) { return &mTeamStats[team]; };
    virtual u16 GetNumTeams() { return Teams; };
    virtual u16 GetNumRounds() { return 2; };
    virtual signed char* GetRoundResults(int round) { return &mRoundResults[round]; };
    virtual void* SerializeData(void* dst) const
    {
        // TODO: Implement
        return nullptr;
    }
    virtual void* DeserializeData(void* src)
    {
        // TODO: Implement
        return nullptr;
    }
    virtual int GetSaveDataSize() const { return 0x1B; };

    BasicGameInfo mGameInfo[3];
    TeamStats mTeamStats[Teams];
    signed char mRoundResults[3];
}; // total size: 0x184

#endif // _CUP_H_
