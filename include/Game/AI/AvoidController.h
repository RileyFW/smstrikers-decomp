#ifndef _AVOIDCONTROLLER_H_
#define _AVOIDCONTROLLER_H_


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