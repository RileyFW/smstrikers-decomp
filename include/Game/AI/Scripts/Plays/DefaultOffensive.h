#ifndef _DEFAULTOFFENSIVE_H_
#define _DEFAULTOFFENSIVE_H_

#include "Game/AI/DecisionEntity.h"
#include "Game/AI/Fielder.h"
#include "Game/Team.h"

// void PositionOf<cFielder*>(cFielder*);

class Fuzzy
{
public:
    void AbortOffensivePlay(cDecisionEntity*);
    void DefaultOffensivePlay(cDecisionEntity*);
    void DoPassing(float, cDecisionEntity*);
    void GoodBallCarrier(cFielder*);
    void InGoodWindupPosition(cFielder*);
    void CutAndBreak(cFielder*);
    void DoShooting(float, cDecisionEntity*);
    void FurthestBackOnMyTeam(cFielder*);
    void UsePowerupOffensive(float, cDecisionEntity*);
    void GetPowerupTargetOffensive(cTeam*);
};

#endif // _DEFAULTOFFENSIVE_H_
