#ifndef _FIELDERACTIONS_H_
#define _FIELDERACTIONS_H_

#include "NL/nlMath.h"
#include "Game/Effects/EmissionController.h"
#include "Game/Camera/MatrixEffectCam.h"
#include "Game/Player.h"

void HyperStrikeEffectUpdate(EmissionController&);
void OtherMatrixCamFinishedCallback(MatrixEffectCam*);
void MatrixCamFinishedCallback(MatrixEffectCam*);
void GetClosestWallPoint(const nlVector3&);
// void 0x8002FEBC..0x8002FED4 | size: 0x18;
// void nlDLRingGetStart<cBaseCamera>(cBaseCamera*);

class cFielder
{
public:
    void asmRunning();
    void asmRunningWB(float);
    void EndAction();
    void InitActionDeke(ePadActions);
    void ActionDeke(float);
    void InitActionElectrocution(const nlVector3&, const nlVector3&);
    void ActionElectrocution(float);
    void InitActionHit(cFielder*);
    void ActionHit(float);
    void InitActionHitReact(cPlayer*, unsigned short, bool);
    void ActionHitReact(float);
    void InitActionIdleTurn(unsigned short);
    void ActionIdleTurn(float);
    void InitActionLateOneTimerFromVolley();
    void ActionLateOneTimerFromVolley(float);
    void DoCommonInitActionLooseBall(const nlVector3&);
    void InitActionLooseBallPass(cFielder*, bool);
    void ActionLooseBallPass(float);
    void InitActionLooseBallShot(bool);
    void ActionLooseBallShot(float);
    void InitActionOneTimer(int, nlVector3&, float, bool);
    void ActionOneTimer(float);
    void InitActionOneTouchPassFromVolley(cPlayer*);
    void ActionOneTouchPassFromVolley(float);
    void DoCalcCanDoPerfectPass(cFielder*, const nlVector3&);
    void InitActionPass(cPlayer*, bool, bool);
    void ActionPass(float);
    void InitActionPostWhistle();
    void ActionPostWhistle(float);
    void InitActionBombReact(const nlVector3&, float);
    void InitActionBombHitReact(const nlVector3&);
    void InitActionBananaReact(const nlVector3&);
    void InitActionShellReact(const nlVector3&, const nlVector3&);
    void InitActionRunning();
    void ActionRunning(float);
    void InitActionRunningWB(bool);
    void ActionRunningWB(float);
    void ActionRunningWBTurbo(float);
    void ActionRunningWBTurboTurn(float);
    void InitActionShot(bool);
    void ActionShot(float);
    void InitActionShootToScore();
    void SetupCaptainSTSAnimCam(bool);
    void ActionShootToScore(float);
    void InitActionSlideAttack(cFielder*, float);
    void ActionSlideAttack(float);
    void InitActionSlideAttackFailReact();
    void ActionSlideAttackFailReact(float);
    void InitActionSquishReact(const nlVector3&);
    void DoSlideAttackStats();
    void InitActionSlideAttackReact(cPlayer*, bool);
    void InitActionSTSHitReact(cPlayer*);
    void ActionSlideAttackReact(float);
    void ActionBombReact(float);
    void ActionSTSHitReact(float);
    void ActionShellReact(float);
    void ActionBananaReact(float);
    void ActionSquishReact(float);
    void InitActionReceivePass(int, nlVector3&, float);
    void ActionReceivePass(float);
    void InitActionWait();
    void ActionWait(float);
};

// class Function1<void, EmissionController&>
// {
// public:
//     void FunctorBase::~FunctorBase();
// };

// class cNet
// {
// public:
//     void GetPostRadius();
// };

// class LexicalCast<BasicString<char, Detail
// {
// public:
//     void TempStringAllocator>, const char*>(const char* const&);
// };

// class Detail
// {
// public:
//     void LexicalCastImpl<BasicString<char, Detail::TempStringAllocator>, const char*>::Do(const char*);
// };

// class Format<BasicString<char, Detail
// {
// public:
//     void TempStringAllocator>, const char*>(const BasicString<char, Detail::TempStringAllocator>&, const char* const&);
// };

// class FormatImpl<BasicString<char, Detail
// {
// public:
//     void TempStringAllocator>>::operator%<const char*>(const char* const&);
//     void TempStringAllocator>>::operator BasicString<char, Detail::TempStringAllocator>() const;
// };

#endif // _FIELDERACTIONS_H_
