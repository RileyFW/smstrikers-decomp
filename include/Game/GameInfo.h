#ifndef _GAMEINFO_H_
#define _GAMEINFO_H_

#include "types.h"

#include "NL/nlSingleton.h"
#include "NL/nlConfig.h"

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

class BaseCup
{
public:
    // 5 pure-virtuals (nulls in BaseCup vtable)
    virtual void GetGameInfo(int team, int round) = 0;
    virtual void* GetTeamStats(int team) = 0;
    virtual int GetNumTeams() = 0;
    virtual int GetNumRounds() = 0;
    virtual void GetRoundResults(int round) = 0;

    // Implemented in BaseCup (present in BaseCup vtable)
    virtual void SerializeData(void* dst) const;
    virtual void DeserializeData(void* src);
    virtual int GetSaveDataSize() const;

    /* 0x00 */ s32 m_unk_0x00;
    /* 0x04 */ s32 m_unk_0x04;
    /* 0x08 */ s16 m_unk_0x08;
    /* 0x0A */ s16 m_unk_0x0A;
    /* 0x0C */ s16 m_unk_0x0C;
    /* 0x0D */ bool m_unk_0x0D;
    /* 0x0E */ u8 m_unk_0x0E[0x0C];

    // /* 0x08 */ s32 m_unk_0x08;
    // /* 0x0C */ s32 m_unk_0x0C;
    // /* 0x10 */ s32 m_unk_0x10;
    // /* 0x14 */ s16 m_unk_0x14;
    // /* 0x16 */ s16 m_unk_0x16;
    // /* 0x18 */ s16 m_unk_0x18;
    // /* 0x1A */ s16 m_unk_0x1A;
    // /* 0x1C */ s16 m_unk_0x1C;
    // /* 0x1E */ s16 m_unk_0x1E;
};

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

// typedef struct BasicGameInfo
// {
//     /* 0x00 */ s32 unk0;  /* inferred */
//     /* 0x04 */ s32 unk4;  /* inferred */
//     /* 0x08 */ s32 unk8;  /* inferred */
//     /* 0x0C */ s32 unkC;  /* inferred */
//     /* 0x10 */ s32 unk10; /* inferred */
//     /* 0x14 */ s16 unk14; /* inferred */
//     /* 0x16 */ s16 unk16; /* inferred */
//     /* 0x18 */ s16 unk18; /* inferred */
//     /* 0x1A */ s16 unk1A; /* inferred */
//     /* 0x1C */ s16 unk1C; /* inferred */
//     /* 0x1E */ s16 unk1E; /* inferred */
// } BasicGameInfo;

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

class GameplaySettings
{
public:
};

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

class GameInfoManager
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
    void GetGameplayOptions() const;
    void GetPowerupOptions() const;
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

    /* 0x0004 */ u8 pad0[0x495C];
    /* 0x4960 */ SomeClass* m_unk_0x4960;

    // /* 0x0004 */ s32 unk4;         /* inferred */
    // /* 0x0008 */ s32 unk8;         /* inferred */
    // /* 0x000C */ u8 unkC;          /* inferred */
    // /* 0x000D */ u8 unkD;          /* inferred */
    // /* 0x000E */ u8 unkE;          /* inferred */
    // /* 0x000F */ u8 unkF;          /* inferred */
    // /* 0x0010 */ Config* unk10;    /* inferred */
    // /* 0x0014 */ s32 unk14;        /* inferred */
    // /* 0x0018 */ s32 unk18;        /* inferred */
    // /* 0x001C */ s32 unk1C;        /* inferred */
    // /* 0x0020 */ s32 unk20;        /* inferred */
    // /* 0x0024 */ s32 unk24;        /* inferred */
    // /* 0x0028 */ s32 unk28;        /* inferred */
    // /* 0x002C */ s32 unk2C;        /* inferred */
    // /* 0x0030 */ s32 unk30;        /* inferred */
    // /* 0x0034 */ s32 unk34;        /* inferred */
    // /* 0x0038 */ Config* unk38;    /* inferred */
    // /* 0x003C */ char pad3C[0x2C]; /* maybe part of unk38[0xC]? */
    // /* 0x0068 */ s32 unk68;        /* inferred */
    // /* 0x006C */ u8 unk6C;         /* inferred */
    // /* 0x006D */ s8 unk6D;         /* inferred */
    // /* 0x006E */ char pad6E[2];    /* maybe part of unk6D[3]? */
    // /* 0x0070 */ Config* unk70;    /* inferred */
    // /* 0x0074 */ s32 unk74;        /* inferred */
    // /* 0x0078 */ BaseCup* unk78;   /* inferred */
    // /* 0x0078 */ char pad78[4];
    // /* 0x007C */ s32 unk7C; /* inferred */
    // /* 0x0080 */ s16 unk80; /* inferred */
    // /* 0x0082 */ s16 unk82; /* inferred */
    // /* 0x0084 */ s16 unk84; /* inferred */
    // /* 0x0086 */ s8 unk86;  /* inferred */
    // /* 0x0087 */ char pad87[1];
    // /* 0x0088 */ GameplaySettings unk88; /* inferred */
    // /* 0x0088 */ char pad88[0xC];
    // /* 0x0094 */ struct __vt__7BaseCup* vtable94;   /* inferred */
    // /* 0x0098 */ CupRecord* unk98(CupRecord* this); /* inferred */
    // /* 0x0098 */ char pad98[0xC0];
    // /* 0x0158 */ CupRecord* unk158(CupRecord* this); /* inferred */
    // /* 0x0158 */ char pad158[0x104];
    // /* 0x025C */ BaseCup unk25C; /* inferred */
    // /* 0x025C */ char pad25C[4];
    // /* 0x0260 */ s32 unk260; /* inferred */
    // /* 0x0264 */ s16 unk264; /* inferred */
    // /* 0x0266 */ s16 unk266; /* inferred */
    // /* 0x0268 */ s16 unk268; /* inferred */
    // /* 0x026A */ s8 unk26A;  /* inferred */
    // /* 0x026B */ char pad26B[1];
    // /* 0x026C */ GameplaySettings unk26C; /* inferred */
    // /* 0x026C */ char pad26C[0xC];
    // /* 0x0278 */ struct __vt__7BaseCup* vtable278;   /* inferred */
    // /* 0x027C */ CupRecord* unk27C(CupRecord* this); /* inferred */
    // /* 0x027C */ char pad27C[0x1E0];
    // /* 0x045C */ CupRecord* unk45C(CupRecord* this); /* inferred */
    // /* 0x045C */ char pad45C[0x188];
    // /* 0x05E4 */ BaseCup unk5E4; /* inferred */
    // /* 0x05E4 */ char pad5E4[4];
    // /* 0x05E8 */ s32 unk5E8; /* inferred */
    // /* 0x05EC */ s16 unk5EC; /* inferred */
    // /* 0x05EE */ s16 unk5EE; /* inferred */
    // /* 0x05F0 */ s16 unk5F0; /* inferred */
    // /* 0x05F2 */ s8 unk5F2;  /* inferred */
    // /* 0x05F3 */ char pad5F3[1];
    // /* 0x05F4 */ GameplaySettings unk5F4; /* inferred */
    // /* 0x05F4 */ char pad5F4[0xC];
    // /* 0x0600 */ struct __vt__7BaseCup* vtable600;   /* inferred */
    // /* 0x0604 */ CupRecord* unk604(CupRecord* this); /* inferred */
    // /* 0x0604 */ char pad604[0x380];
    // /* 0x0984 */ CupRecord* unk984(CupRecord* this); /* inferred */
    // /* 0x0984 */ char pad984[0x208];
    // /* 0x0B8C */ s32 unkB8C; /* inferred */
    // /* 0x0B90 */ s32 unkB90; /* inferred */
    // /* 0x0B94 */ s16 unkB94; /* inferred */
    // /* 0x0B96 */ s16 unkB96; /* inferred */
    // /* 0x0B98 */ s16 unkB98; /* inferred */
    // /* 0x0B9A */ s8 unkB9A;  /* inferred */
    // /* 0x0B9B */ char padB9B[1];
    // /* 0x0B9C */ GameplaySettings unkB9C; /* inferred */
    // /* 0x0B9C */ char padB9C[0xC];
    // /* 0x0BA8 */ struct __vt__7BaseCup* vtableBA8;   /* inferred */
    // /* 0x0BAC */ CupRecord* unkBAC(CupRecord* this); /* inferred */
    // /* 0x0BAC */ char padBAC[0x380];
    // /* 0x0F2C */ CupRecord* unkF2C(CupRecord* this); /* inferred */
    // /* 0x0F2C */ char padF2C[0x208];
    // /* 0x1134 */ s32 unk1134; /* inferred */
    // /* 0x1138 */ s32 unk1138; /* inferred */
    // /* 0x113C */ s16 unk113C; /* inferred */
    // /* 0x113E */ s16 unk113E; /* inferred */
    // /* 0x1140 */ s16 unk1140; /* inferred */
    // /* 0x1142 */ s8 unk1142;  /* inferred */
    // /* 0x1143 */ char pad1143[1];
    // /* 0x1144 */ GameplaySettings unk1144; /* inferred */
    // /* 0x1144 */ char pad1144[0xC];
    // /* 0x1150 */ struct __vt__7BaseCup* vtable1150;   /* inferred */
    // /* 0x1154 */ CupRecord* unk1154(CupRecord* this); /* inferred */
    // /* 0x1154 */ char pad1154[0x60];
    // /* 0x11B4 */ CupRecord* unk11B4(CupRecord* this); /* inferred */
    // /* 0x11B4 */ char pad11B4[0x104];
    // /* 0x12B8 */ BaseCup unk12B8; /* inferred */
    // /* 0x12B8 */ char pad12B8[4];
    // /* 0x12BC */ s32 unk12BC; /* inferred */
    // /* 0x12C0 */ s16 unk12C0; /* inferred */
    // /* 0x12C2 */ s16 unk12C2; /* inferred */
    // /* 0x12C4 */ s16 unk12C4; /* inferred */
    // /* 0x12C6 */ s8 unk12C6;  /* inferred */
    // /* 0x12C7 */ char pad12C7[1];
    // /* 0x12C8 */ GameplaySettings unk12C8; /* inferred */
    // /* 0x12C8 */ char pad12C8[0xC];
    // /* 0x12D4 */ struct __vt__7BaseCup* vtable12D4;   /* inferred */
    // /* 0x12D8 */ CupRecord* unk12D8(CupRecord* this); /* inferred */
    // /* 0x12D8 */ char pad12D8[0x180];
    // /* 0x1458 */ CupRecord* unk1458(CupRecord* this); /* inferred */
    // /* 0x1458 */ char pad1458[0x108];
    // /* 0x1560 */ BaseCup unk1560; /* inferred */
    // /* 0x1560 */ char pad1560[4];
    // /* 0x1564 */ s32 unk1564; /* inferred */
    // /* 0x1568 */ s16 unk1568; /* inferred */
    // /* 0x156A */ s16 unk156A; /* inferred */
    // /* 0x156C */ s16 unk156C; /* inferred */
    // /* 0x156E */ s8 unk156E;  /* inferred */
    // /* 0x156F */ char pad156F[1];
    // /* 0x1570 */ GameplaySettings unk1570; /* inferred */
    // /* 0x1570 */ char pad1570[0xC];
    // /* 0x157C */ struct __vt__7BaseCup* vtable157C;   /* inferred */
    // /* 0x1580 */ CupRecord* unk1580(CupRecord* this); /* inferred */
    // /* 0x1580 */ char pad1580[0x3C0];
    // /* 0x1940 */ CupRecord* unk1940(CupRecord* this); /* inferred */
    // /* 0x1940 */ char pad1940[0x18C];
    // /* 0x1ACC */ BaseCup unk1ACC; /* inferred */
    // /* 0x1ACC */ char pad1ACC[4];
    // /* 0x1AD0 */ s32 unk1AD0; /* inferred */
    // /* 0x1AD4 */ s16 unk1AD4; /* inferred */
    // /* 0x1AD6 */ s16 unk1AD6; /* inferred */
    // /* 0x1AD8 */ s16 unk1AD8; /* inferred */
    // /* 0x1ADA */ s8 unk1ADA;  /* inferred */
    // /* 0x1ADB */ char pad1ADB[1];
    // /* 0x1ADC */ GameplaySettings unk1ADC; /* inferred */
    // /* 0x1ADC */ char pad1ADC[0xC];
    // /* 0x1AE8 */ struct __vt__7BaseCup* vtable1AE8;   /* inferred */
    // /* 0x1AEC */ CupRecord* unk1AEC(CupRecord* this); /* inferred */
    // /* 0x1AEC */ char pad1AEC[0x700];
    // /* 0x21EC */ CupRecord* unk21EC(CupRecord* this); /* inferred */
    // /* 0x21EC */ char pad21EC[0x210];
    // /* 0x23FC */ s32 unk23FC; /* inferred */
    // /* 0x2400 */ s32 unk2400; /* inferred */
    // /* 0x2404 */ s16 unk2404; /* inferred */
    // /* 0x2406 */ s16 unk2406; /* inferred */
    // /* 0x2408 */ s16 unk2408; /* inferred */
    // /* 0x240A */ s8 unk240A;  /* inferred */
    // /* 0x240B */ char pad240B[1];
    // /* 0x240C */ GameplaySettings unk240C; /* inferred */
    // /* 0x240C */ char pad240C[0xC];
    // /* 0x2418 */ struct __vt__7BaseCup* vtable2418;   /* inferred */
    // /* 0x241C */ CupRecord* unk241C(CupRecord* this); /* inferred */
    // /* 0x241C */ char pad241C[0x700];
    // /* 0x2B1C */ CupRecord* unk2B1C(CupRecord* this); /* inferred */
    // /* 0x2B1C */ char pad2B1C[0x210];
    // /* 0x2D2C */ s32 unk2D2C; /* inferred */
    // /* 0x2D30 */ s32 unk2D30; /* inferred */
    // /* 0x2D34 */ s16 unk2D34; /* inferred */
    // /* 0x2D36 */ s16 unk2D36; /* inferred */
    // /* 0x2D38 */ s16 unk2D38; /* inferred */
    // /* 0x2D3A */ s8 unk2D3A;  /* inferred */
    // /* 0x2D3B */ char pad2D3B[1];
    // /* 0x2D3C */ GameplaySettings unk2D3C; /* inferred */
    // /* 0x2D3C */ char pad2D3C[0xC];
    // /* 0x2D48 */ struct __vt__7BaseCup* vtable2D48;   /* inferred */
    // /* 0x2D4C */ CupRecord* unk2D4C(CupRecord* this); /* inferred */
    // /* 0x2D4C */ char pad2D4C[0x60];
    // /* 0x2DAC */ CupRecord* unk2DAC(CupRecord* this); /* inferred */
    // /* 0x2DAC */ char pad2DAC[0x128];
    // /* 0x2ED4 */ s32 unk2ED4;           /* inferred */
    // /* 0x2ED8 */ AudioSettings unk2ED8; /* inferred */
    // /* 0x2ED8 */ char pad2ED8[0x20];
    // /* 0x2EF8 */ VisualSettings unk2EF8; /* inferred */
    // /* 0x2EF8 */ char pad2EF8[0xC];
    // /* 0x2F04 */ s32 unk2F04;             /* inferred */
    // /* 0x2F08 */ char pad2F08[8];         /* maybe part of unk2F04[3]? */
    // /* 0x2F10 */ PowerupSettings unk2F10; /* inferred */
    // /* 0x2F10 */ char pad2F10[8];
    // /* 0x2F18 */ s32 unk2F18;                         /* inferred */
    // /* 0x2F1C */ u8 unk2F1C;                          /* inferred */
    // /* 0x2F1D */ u8 unk2F1D;                          /* inferred */
    // /* 0x2F1E */ u8 unk2F1E;                          /* inferred */
    // /* 0x2F1F */ u8 unk2F1F;                          /* inferred */
    // /* 0x2F20 */ u8 unk2F20;                          /* inferred */
    // /* 0x2F21 */ u8 unk2F21;                          /* inferred */
    // /* 0x2F22 */ char pad2F22[2];                     /* maybe part of unk2F21[3]? */
    // /* 0x2F24 */ CupRecord* unk2F24(CupRecord* this); /* inferred */
    // /* 0x2F24 */ char pad2F24[0x208];
    // /* 0x312C */ s8 unk312C; /* inferred */
    // /* 0x312D */ char pad312D[1];
    // /* 0x312E */ s16 unk312E; /* inferred */
    // /* 0x3130 */ s16 unk3130; /* inferred */
    // /* 0x3132 */ char pad3132[2];
    // /* 0x3134 */ s32 unk3134;         /* inferred */
    // /* 0x3138 */ char pad3138[0x20C]; /* maybe part of unk3134[0x84]? */
    // /* 0x3344 */ s8 unk3344;          /* inferred */
    // /* 0x3345 */ char pad3345[1];
    // /* 0x3346 */ s16 unk3346; /* inferred */
    // /* 0x3348 */ s16 unk3348; /* inferred */
    // /* 0x334A */ char pad334A[2];
    // /* 0x334C */ s32 unk334C;         /* inferred */
    // /* 0x3350 */ char pad3350[0x20C]; /* maybe part of unk334C[0x84]? */
    // /* 0x355C */ s8 unk355C;          /* inferred */
    // /* 0x355D */ char pad355D[1];
    // /* 0x355E */ s16 unk355E; /* inferred */
    // /* 0x3560 */ s16 unk3560; /* inferred */
    // /* 0x3562 */ char pad3562[2];
    // /* 0x3564 */ s32 unk3564;         /* inferred */
    // /* 0x3568 */ char pad3568[0x20C]; /* maybe part of unk3564[0x84]? */
    // /* 0x3774 */ s8 unk3774;          /* inferred */
    // /* 0x3775 */ char pad3775[1];
    // /* 0x3776 */ s16 unk3776; /* inferred */
    // /* 0x3778 */ s16 unk3778; /* inferred */
    // /* 0x377A */ char pad377A[2];
    // /* 0x377C */ s32 unk377C;         /* inferred */
    // /* 0x3780 */ char pad3780[0x20C]; /* maybe part of unk377C[0x84]? */
    // /* 0x398C */ s8 unk398C;          /* inferred */
    // /* 0x398D */ char pad398D[1];
    // /* 0x398E */ s16 unk398E; /* inferred */
    // /* 0x3990 */ s16 unk3990; /* inferred */
    // /* 0x3992 */ char pad3992[2];
    // /* 0x3994 */ s32 unk3994;         /* inferred */
    // /* 0x3998 */ char pad3998[0x20C]; /* maybe part of unk3994[0x84]? */
    // /* 0x3BA4 */ s8 unk3BA4;          /* inferred */
    // /* 0x3BA5 */ char pad3BA5[1];
    // /* 0x3BA6 */ s16 unk3BA6; /* inferred */
    // /* 0x3BA8 */ s16 unk3BA8; /* inferred */
    // /* 0x3BAA */ char pad3BAA[2];
    // /* 0x3BAC */ s32 unk3BAC;         /* inferred */
    // /* 0x3BB0 */ char pad3BB0[0x20C]; /* maybe part of unk3BAC[0x84]? */
    // /* 0x3DBC */ s8 unk3DBC;          /* inferred */
    // /* 0x3DBD */ char pad3DBD[1];
    // /* 0x3DBE */ s16 unk3DBE; /* inferred */
    // /* 0x3DC0 */ s16 unk3DC0; /* inferred */
    // /* 0x3DC2 */ char pad3DC2[2];
    // /* 0x3DC4 */ s32 unk3DC4;         /* inferred */
    // /* 0x3DC8 */ char pad3DC8[0x20C]; /* maybe part of unk3DC4[0x84]? */
    // /* 0x3FD4 */ s8 unk3FD4;          /* inferred */
    // /* 0x3FD5 */ char pad3FD5[1];
    // /* 0x3FD6 */ s16 unk3FD6; /* inferred */
    // /* 0x3FD8 */ s16 unk3FD8; /* inferred */
    // /* 0x3FDA */ char pad3FDA[2];
    // /* 0x3FDC */ s32 unk3FDC; /* inferred */
    // /* 0x3FE0 */ char pad3FE0[4];
    // /* 0x3FE4 */ u8 unk3FE4;               /* inferred */
    // /* 0x3FE5 */ u8 unk3FE5;               /* inferred */
    // /* 0x3FE6 */ u16 unk3FE6;              /* inferred */
    // /* 0x3FE8 */ u16 unk3FE8;              /* inferred */
    // /* 0x3FEA */ u16 unk3FEA;              /* inferred */
    // /* 0x3FEC */ u16 unk3FEC;              /* inferred */
    // /* 0x3FEE */ u16 unk3FEE;              /* inferred */
    // /* 0x3FF0 */ s32 unk3FF0;              /* inferred */
    // /* 0x3FF4 */ s32 unk3FF4;              /* inferred */
    // /* 0x3FF8 */ s32 unk3FF8;              /* inferred */
    // /* 0x3FFC */ s32 unk3FFC;              /* inferred */
    // /* 0x4000 */ s32 unk4000;              /* inferred */
    // /* 0x4004 */ s32 unk4004;              /* inferred */
    // /* 0x4008 */ s32 unk4008;              /* inferred */
    // /* 0x400C */ s32 unk400C;              /* inferred */
    // /* 0x4010 */ CustomTournament unk4010; /* inferred */
    // /* 0x4010 */ char pad4010[0x938];
    // /* 0x4948 */ s32 unk4948;     /* inferred */
    // /* 0x494C */ char pad494C[8]; /* maybe part of unk4948[3]? */
    // /* 0x4954 */ s32 unk4954;     /* inferred */
    // /* 0x4958 */ s8 unk4958;      /* inferred */
    // /* 0x4959 */ u8 unk4959;      /* inferred */
    // /* 0x495A */ s8 unk495A;      /* inferred */
    // /* 0x495B */ char pad495B[1];
    // /* 0x495C */ s32 unk495C;                         /* inferred */
    // /* 0x4960 */ s32* unk4960;                        /* inferred */
    // /* 0x4964 */ s32* unk4964;                        /* inferred */
    // /* 0x4968 */ char pad4968[0xD0];                  /* maybe part of unk4964[0x35]? */
    // /* 0x4A38 */ CupRecord* unk4A38(CupRecord* this); /* inferred */
    // /* 0x4A38 */ char pad4A38[4];
    // /* 0x4A3C */ u16 unk4A3C;           /* inferred */
    // /* 0x4A3E */ u16 unk4A3E;           /* inferred */
    // /* 0x4A40 */ u16 unk4A40;           /* inferred */
    // /* 0x4A42 */ u16 unk4A42;           /* inferred */
    // /* 0x4A44 */ s32 unk4A44;           /* inferred */
    // /* 0x4A48 */ s32 unk4A48;           /* inferred */
    // /* 0x4A4C */ s32 unk4A4C;           /* inferred */
    // /* 0x4A50 */ s32 unk4A50;           /* inferred */
    // /* 0x4A54 */ s32 unk4A54;           /* inferred */
    // /* 0x4A58 */ s32 unk4A58;           /* inferred */
    // /* 0x4A5C */ s32 unk4A5C;           /* inferred */
    // /* 0x4A60 */ s32 unk4A60;           /* inferred */
    // /* 0x4A64 */ s32 unk4A64;           /* inferred */
    // /* 0x4A68 */ s32 unk4A68;           /* inferred */
    // /* 0x4A6C */ s32 unk4A6C;           /* inferred */
    // /* 0x4A70 */ s32 unk4A70;           /* inferred */
    // /* 0x4A74 */ s32 unk4A74;           /* inferred */
    // /* 0x4A78 */ char pad4A78[0x1C0];   /* maybe part of unk4A74[0x71]? */
    // /* 0x4C38 */ u8 unk4C38;            /* inferred */
    // /* 0x4C39 */ s8 unk4C39;            /* inferred */
    // /* 0x4C3A */ char pad4C3A[0x22];    /* maybe part of unk4C39[0x23]? */
    // /* 0x4C5C */ s32 unk4C5C;           /* inferred */
    // /* 0x4C60 */ AudioSettings unk4C60; /* inferred */
    // /* 0x4C60 */ char pad4C60[1];

    static nlSingleton<GameInfoManager> s_pInstance;
};

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
