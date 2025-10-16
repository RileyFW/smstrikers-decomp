#ifndef _FIELDERDESIRES_H_
#define _FIELDERDESIRES_H_

#include "Game/AI/ScriptAction.h"

// class cFielder
// {
// public:
//     void QueueDesire(eFielderDesireState, float, FuzzyVariant, FuzzyVariant);
//     void ClearQueuedDesire();
//     void InitDesire(const sDesireParams*, float);
//     void InitDesire(eFielderDesireState, float, float, FuzzyVariant, FuzzyVariant);
//     void UpdateDesireState(float);
//     void EndDesire(bool);
//     void CleanUpDesire(eFielderDesireState);
//     void DesireInterceptBall(float);
//     void DesireMark(float);
//     void DesireSupportBall(float, bool);
//     void InitDesireGetOpen();
//     void InitDesireOneTimerFromRun(unsigned short, const nlVector3&, const nlVector3&, bool, bool);
//     void DesireOneTimer(float);
//     void InitDesireReceivePassFromIdle(const LooseBallContactAnimInfo*, unsigned short, bool);
//     void DesireReceivePassFromIdle(float);
//     void InitDesireReceivePassFromRun(const LooseBallContactAnimInfo*, const nlVector3&, bool, const nlVector3&);
//     void DesireReceivePassFromRun(float);
//     void InitDesireRunToNet();
//     void DesireSlideAttack(float);
//     void DesireUserControlled(float);
//     void DesireUsePowerup(float);
//     void DesireWindupShot(float);
// };

class CommonDesireData
{
public:
    CommonDesireData();
    ~CommonDesireData();
    CommonDesireData(const CommonDesireData&);
    float CalcFuzzyChance(float fChance);
    bool CalcBoolChance(float fChance);
    float NormalizeConfidence(float fConfidence);
};

CommonDesireData& GetCommonDesireData(eFielderDesireState desireType);

// class FilteredRandomRange
// {
// public:
//     ~FilteredRandomRange();
// };

#endif // _FIELDERDESIRES_H_
