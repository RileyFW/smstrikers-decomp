#ifndef _FIELDER_H_
#define _FIELDER_H_

#include "types.h"
#include "NL/nlMath.h"

#include "Game/Player.h"
#include "Game/AI/Powerups.h"
#include "Game/AI/ScriptAction.h"

enum eTurboRequest
{
    eTurboRequest_0 = 0
};

enum eFielderActionState
{
    eFielderActionState_0 = 0
};

enum eAwardPowerupType
{
    eAwardPowerupType_0 = 0
};

enum ePenaltyType
{
    ePenaltyType_0 = 0
};

class cBall;

class cFielder : public cPlayer
{
public:
    void DoSpeedBoost();
    void DoAIWindupActionSelection();
    void DoAIReceivePassActionSelection();
    void DoAILooseBallActionSelection();
    void StartRunning();
    void S2SShootWasPressed();
    void GetDistanceToDesiredPos();
    void UpdatePlay(float);
    void UpdateController(float);
    void UpdateHeadTracking(float);
    void UpdateActionState(float);
    void UseTeamPowerup(cFielder*);
    void SetPowerup(ePowerUpType, int, cFielder*);
    void ThrowPowerup();
    void Update(float);
    void PostPhysicsUpdate();
    void PreUpdate(float);
    void TestButtonsRunningWB(float);
    void TestButtonsRunning();
    void TestQueuedActions();
    void TestButtonsToQueueActions(float);
    void TestCollisionForInvicibility(cFielder*);
    void ShouldIWave();
    void ShouldITurboWithoutBall();
    void ShouldIStrafe();
    void SetDesire(eFielderDesireState, float);
    void GetSlideAttackSpeed();
    void GetSpeedPowerupAdjusted(float);
    void SetDesiredSpeed(float, float);
    void SetDesiredSpeedAndDirectionToPosition(float, const nlVector3&, eTurboRequest, float, float);
    void SetPosition(const nlVector3&);
    void CanISlideAttack(const nlVector3&, const nlVector3&, float*);
    void ShouldILeadPass();
    void ShouldIClearBall();
    void SetRunningWBAnimState(float);
    void SetRunningTurboAnimState();
    void SetRunningAnimState(float);
    // void RunningSABcallback(unsigned int, cPN_SingleAxisBlender*);
    void SetIdleWBAnimState();
    void SetIdleAnimState();
    void SetIdleStrafeAnimState();
    void SetStrafeRightAnimState();
    void SetStrafeLeftAnimState();
    void SetStopWBAnimState();
    void SetStopAnimState();
    void SetBackRunningStopRecoverAnimState();
    void SetBackRunningStopStartAnimState();
    void SetBackRunningStopAnimState();
    void SetBackRunningToRunAnimState();
    void SetRunToBackRunningAnimState();
    void SetRunBackwardsAnimState();
    void SetHardStopTurnAnimState();
    void SetHardStopRecoverAnimState();
    void SetHardStopAnimState();
    void SetRunTurboAnimState(int, bool);
    void SetStartWBAnimState();
    void SetWindupWBAnimState();
    void SetStartAnimState(int);
    void GetOneTouchShotDesire();
    void SetAttemptOneTouchShot();
    void SetAttemptOneTouchPass();
    void CleanActionShootToScore();
    void ClearVolleyPass();
    void ClearTimers();
    void CalcPointOnPerimeter(nlVector3&, const nlVector3&, float);
    void CalculateStrafeDirection(unsigned short, unsigned short);
    void CanBreakOutOfSlideTackle();
    void CanBeBlownUp();
    void CanPickupBall(cBall*);
    void DoFindBestSlideAttackTarget(nlVector3&, nlVector3&);
    void SetFrozen(float);
    bool IsFrozen() const;
    bool IsDefense() const;
    bool IsMidField() const;
    bool IsWinger() const;
    bool IsStriker() const;
    bool IsSlideTackling() const;
    bool IsHitting() const;
    bool IsFallenDown(float) const;
    // void GetReceivePassBallContactOffset(nlVector3&, unsigned short, const LooseBallContactAnimInfo*);
    // void GetReceivePassBallContactAnimInfo(cBall*, const nlVector3&, unsigned short, bool, bool);
    void GetOneTimerBallContactAnimInfo(unsigned short, const nlVector3&, const nlVector3&, bool, bool);
    void GetFormationPosition(nlVector3&, float);
    void SetAction(eFielderActionState);
    bool IsActionDone() const;
    void DoResetShotMeter(float);
    void DoRegularShooting();
    void DoFindBestShotTarget(nlVector3&, float&, bool);
    void DoFindBestHitTarget();
    void DoCalcShootToScoreResult(float, float, float, float, float);
    void DoAwardPowerupStuff(eAwardPowerupType, float);
    void DoPositioningInterceptBall();
    void DoPenaltyCardBooking(cFielder*, ePenaltyType);
    // void DoLooseBallContactFromRunVolley(nlVector3&, float&, nlVector3&, float&, const LooseBallContactAnimInfo*, const nlVector3&);
    // void DoLooseBallContactFromRun(nlVector3&, float&, nlVector3&, float&, const LooseBallContactAnimInfo*, const nlVector3&);
    // void DoLooseBallContactFromIdle(nlVector3&, float&, nlVector3&, float&, unsigned short, const LooseBallContactAnimInfo*);
    void DoHandleActiveShotMeter();
    void DoClearBall();
    void ShootBallDueToContact(unsigned short);
    void ShootBallDueToContact(const nlVector3&);
    void SetDesireDuration(float, bool);
    void SetBombImpactTime(const nlVector3&, float);
    void SetKickOffWaitTime();
    void SetSlideAttackSuccessFlag();
    void CalcShootToScoreShot(nlVector3&, nlVector3&);
    void CalcRegularShot(nlVector3&, nlVector3&);
    void CleanUpPowerupEffect();
    void CleanUpAction();
    bool IsPreparingForOneTimer() const;
    bool IsReceivingVolleyPass() const;
    bool IsBallAwayFromCarrier() const;
    bool IsInvincible() const;
    bool IsRunning() const;
    void IsTurboing();
    bool IsCharacterInAir(bool) const;
    void IsPlayingPowerupAnim();
    void UsePerfectPass();
    void ClearPassTargetIfAmThePassTarget();
    // void CollideWithWallCallback(const CollisionPlayerWallData*);
    // void CollideWithBowserCallback(Bowser*);
    // void CollideWithChainCallback(ChainChomp*);
    void CollideWithBananaCallback(const nlVector3&);
    void CollideWithFreezeCallback();
    void CollideWithShellCallback(ePowerupSize, bool, const nlVector3&, const nlVector3&);
    // void CollideWithCharacterCallback(CollisionPlayerPlayerData*);
    void SetMark(cFielder*);
    void CanReceivePass();
    void CanLooseBallPass();
    void CanLooseBallShoot();
    void CanDoCaptainShootToScore();
    void CalculateNewDesire();
    void AbortPendingThoughts();
    void AbortPlay();

    // void QueueDesire(eFielderDesireState, float, FuzzyVariant, FuzzyVariant);
    // void ClearQueuedDesire();
    void InitDesire(const sDesireParams*, float);
    // void InitDesire(eFielderDesireState, float, float, FuzzyVariant, FuzzyVariant);
    // void UpdateDesireState(float);
    // void EndDesire(bool);
    // void CleanUpDesire(eFielderDesireState);
    // void DesireInterceptBall(float);
    // void DesireMark(float);
    // void DesireSupportBall(float, bool);
    // void InitDesireGetOpen();
    // void InitDesireOneTimerFromRun(unsigned short, const nlVector3&, const nlVector3&, bool, bool);
    // void DesireOneTimer(float);
    // void InitDesireReceivePassFromIdle(const LooseBallContactAnimInfo*, unsigned short, bool);
    // void DesireReceivePassFromIdle(float);
    // void InitDesireReceivePassFromRun(const LooseBallContactAnimInfo*, const nlVector3&, bool, const nlVector3&);
    // void DesireReceivePassFromRun(float);
    // void InitDesireRunToNet();
    // void DesireSlideAttack(float);
    // void DesireUserControlled(float);
    // void DesireUsePowerup(float);
    // void DesireWindupShot(float);

    ~cFielder();
    // cFielder(int, int, eCharacterClass, const int*, cSHierarchy*, cAnimInventory*, const CharacterPhysicsData*, FielderTweaks*,
    //          AnimRetargetList*);

    u8 m_unk_0x00[0xB0];
    const char* m_unk_0xB0;

    u8 m_padding_0xB8[0x110];

    /* 0x398 */ cFielder* m_pMark;
};

// class FilteredRandomChance
// {
// public:
//     ~FilteredRandomChance();
// };

// class FilteredRandomReal
// {
// public:
//     ~FilteredRandomReal();
// };

// class cNet
// {
// public:
//     void GetNetHeight();
//     void GetNetWidth();
// };

// class PlayerAttackData
// {
// public:
//     void GetID();
// };

#endif // _FIELDER_H_
