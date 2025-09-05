#ifndef _CTEAM_H_
#define _CTEAM_H_

#include <types.h>

#include "NL/nlMath.h"
#include "NL/globalpad.h"

#include "Game/GameTweaks.h"
#include "Game/Fielder.h"
#include "Game/Powerups.h"
#include "Game/Goalie.h"
#include "Game/Player.h"
#include "Game/Net.h"

class cTeam
{
private:
    unknown32 unk_00;
    cFielder* captain;   // Offset 0x04, size: 0x4
    unknown8 pad_08[16]; // Offset 0x08, size: 0x10
    cFielder* striker;   // Offset 0x18, size: 0x4
    unknown32 unk_1C;
    cFielder* midfielder; // Offset 0x20, size: 0x4
    cFielder* defender;   // Offset 0x24, size: 0x4

public:
    cFielder* GetRearMostFielder();
    cFielder* GetFrontMostFielder();
    cFielder* GetDefense() const;
    cFielder* GetMidfield() const;
    cFielder* GetStriker() const;
    cFielder* GetCaptain();

    void AssignMarks(bool);
    void UpdateTeamAI(float);
    void CalculateFormationPosition(nlVector3&, cFielder*, bool, float);
    void StopGameplayEffectsAndSounds();
    void ResetCharacters();
    void Update(float);
    void PreUpdate(float);

    cNet* GetOtherNet();
    cTeam* GetOtherTeam();
    cPlayer* GetPlayer(int);
    cFielder* GetFielder(int);

    // Usages involve cmpwi of 4byte value, meaning value must be signed and is likely an int
    int GetNumAssignedControllers();

    // Looks like GetControlledPlayer returns a pointer, assuming cPlayer for now
    cPlayer* GetControlledPlayer(cGlobalPad*);
    Goalie* GetGoalie();
    void SetGoalie(Goalie*);
    void SetPlayer(cPlayer* player, int);

    void SetIsPowerUpNew(int, bool);
    PowerupBase GetPowerUpByIndex(int) const;
    // Usages match clrlwi. r0, r3, 24, which is a U8/bool
    bool IsCurrentStar() const;
    bool IsCurrentMushroom() const;
    bool IsCurrentNoPowerup() const;
    PowerupBase GetCurrentPowerUp() const;
    // Usage in Character.s: bl IncrementPowerupMeter__5cTeamFf -> clrlwi. r0, r3, 24
    // Implies that return type is U8 (could also be bool as results are 0 or 1?)
    u8 IncrementPowerupMeter(float);
    void TogglePowerup(bool);
    void ClearCurrentPowerUp();
    void ClearAllPowerUps();

    void SetDifficulty(eDifficultyID);

    ~cTeam();
    cTeam(int);
};

#endif // _CTEAM_H_
