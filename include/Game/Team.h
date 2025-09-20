#ifndef _CTEAM_H_
#define _CTEAM_H_

#include <types.h>

#include "NL/nlMath.h"
#include "NL/globalpad.h"

#include "Game/GameTweaks.h"
#include "Game/Fielder.h"
#include "Game/AI/Powerups.h"
#include "Game/Goalie.h"
#include "Game/Player.h"
#include "Game/Net.h"
#include "Game/Formation.h"

enum eSituation
{
    SITUATION_OFFENSE = 0,
    SITUATION_DEFENSE = 1,
    SITUATION_LOOSE = 2,
    NUM_SITUATIONS = 3,
};

enum eTeamStyle
{
    TEAM_STYLE_AGGRESSIVE = 0,
    TEAM_STYLE_MODERATE = 1,
    TEAM_STYLE_PASSIVE = 2,
    NUM_TEAM_STYLES = 3,
};

enum eTeamSide
{
    NO_SIDE = -1,
    HOME = 0,
    AWAY = 1,
    HOME_AWAY = 2,
};

void MostDefensivePlayer(const void*, const void*);
void MostOffensiveThreat(const void*, const void*);
void BestAbleToInterceptBall(const void*, const void*);

class cTeam
{
public:
    cTeam(int);
    ~cTeam();
    void SetDifficulty(eDifficultyID);
    void ClearAllPowerUps();
    void ClearCurrentPowerUp();
    void TogglePowerup(bool);
    bool IncrementPowerupMeter(float);
    void GetCurrentPowerUp() const;
    void IsCurrentNoPowerup() const;
    void IsCurrentMushroom() const;
    void IsCurrentStar() const;
    void GetPowerUpByIndex(int) const;
    void SetIsPowerUpNew(int, bool);
    void SetCurrentPowerUp(ePowerUpType, int);
    void SetPlayer(cPlayer*, int);
    void SetGoalie(Goalie*);
    Goalie* GetGoalie();
    cPlayer* GetControlledPlayer(cGlobalPad*);
    void GetNumAssignedControllers();
    cFielder* GetFielder(int);
    cPlayer* GetPlayer(int);
    cTeam* GetOtherTeam();
    cNet* GetOtherNet();
    void PreUpdate(float);
    void Update(float);
    void UpdateControllers();
    void ResetCharacters();
    void StopGameplayEffectsAndSounds();
    void CalculateFormationPosition(nlVector3&, cFielder*, bool, float);
    void UpdateTeamAI(float);
    void AssignMarks(bool);
    cFielder* GetCaptain();
    cFielder* GetStriker() const;
    cFielder* GetMidfield() const;
    cFielder* GetDefence() const;
    cFielder* GetFrontMostFielder();
    cFielder* GetRearMostFielder();

    /* 0x0, */ int m_nSide;
    /* ------------------------------------ */

    /* 0x4, */ cFielder* m_pPlayers[4];
    /* 0x14, */ Goalie* m_pGoalie;
    // /* 0x18, */ cFielder* m_pStriker;
    // /* 0x18, */ cFielder* m_pFielders[5];

    /* ------------------------------------ */
    // /* 0x4, */ cPlayer* m_pPlayers[5];
    /* 0x18 */ cFielder* m_pAIOrderedFielders[4];
    /* 0x28 */ cFielder* m_pBallInterceptOrderedFielders[4];
    /* ------------------------------------ */
    /* 0x38 */ cNet* m_pNet;
    /* 0x3C */ int m_nScore;
    /* 0x40 */ int m_nCurrentPowerUp;
    /* 0x44 */ PowerUpTeamType m_ePowerupList[2];
    /* 0x5C */ float mfPowerupMeter;
    /* 0x60 */ float mfPowerupTimer;
    /* 0x64 */ eSituation mpCurrentSituation;
    /* 0x68 */ eTeamStyle meCurrentTeamStyle;
    /* 0x6C */ FormationManager* m_pFormationManager;
    /* 0x70 */ Timer mtTeamStyleTimer;
    /* 0x74 */ Timer mtMarkTimer;
    /* 0x78 */ Timer mtRoleTimer;
    /* 0x7C */ Timer mtDefensiveZoneTimer;
    /* 0x80 */ bool mbHasToggledPowerup;
    /* 0x84 */ float mfBallInterceptTimes[4];
    /* 0x94 */ Timer mtBallInterceptTimer;
}; // total size: 0x98

// extern cTeam* g_pTeams[2];

#endif // _CTEAM_H_
