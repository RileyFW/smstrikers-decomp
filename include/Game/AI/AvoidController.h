#ifndef _AVOIDCONTROLLER_H_
#define _AVOIDCONTROLLER_H_

#include "Game/AI/Fielder.h"
#include "Game/Player.h"
#include "Game/AI/Powerups.h"
#include "Game/AI/ScriptAction.h"
#include "Game/Field.h"

enum eAvoidableThings
{
    AVOID_NOTHING = 0,
    AVOID_FIELDERS = 1,
    AVOID_GOALIES = 2,
    AVOID_POWERUPS = 4,
    AVOID_SIDELINES = 8,
    AVOID_BOWSER = 16,
    AVOID_EVERYTHING = 31,
    NUM_AVOIDABLES = 6,
};

class AvoidController
{
public:
    AvoidController(cFielder*);
    void SetThingsToAvoid(int);
    void UseMinimumAvoidance(cPlayer*);
    void GetLastRepulsionVector(eAvoidableThings);
    void Update(float);
    void CalcFielderRepulsionVector(nlVector3&);
    void CalcPowerupRepulsionVector(nlVector3&);
    void CalcDesiredVelocityToAvoidSideline(nlVector2&, const nlVector2&, const nlVector2&, const nlVector2&, const nlVector2&);
    void CalcDesiredVelocityToAvoidCorner(nlVector2&, const sCornerSegment&, const nlVector2&, const nlVector2&);
    void AvoidSidelines();
    void ApplyRepulsionVector(nlVector3);
};

#endif // _AVOIDCONTROLLER_H_
