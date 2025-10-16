#ifndef _DEFAULTDEFENSIVE_H_
#define _DEFAULTDEFENSIVE_H_

#include "Game/AI/DecisionEntity.h"
#include "Game/Team.h"

class Fuzzy
{
public:
    void AbortDefencePlay(cDecisionEntity*);
    void DefaultDefencePlay(cDecisionEntity*);
    void DefendPassInPlay(float, cDecisionEntity*);
    void TryAttacking(float, cDecisionEntity*);
    void AttackBallOwner(float, cDecisionEntity*);
    void UsePowerupDefensive(float, cDecisionEntity*);
    void GetPowerupTargetDefensive(cTeam*);
};

#endif // _DEFAULTDEFENSIVE_H_
