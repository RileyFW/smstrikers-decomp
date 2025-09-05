#ifndef _GOALIE_H_
#define _GOALIE_H_

#include "Game/Player.h"
#include "NL/nlMath.h"

#include "ode/collision.h"

class cFielder;
class cPlayer;
class cSHierarchy;
class cAnimInventory;
class CharacterPhysicsData;
class GoalieTweaks;
class AnimRetargetList;
class Event;
class cPN_SAnimController;
class CollisionPlayerPlayerData;
class cBall;

enum eGoalieActionState
{
    eGoalieActionState_0 = 0
};

enum eGoalieCrouchType
{
    eGoalieCrouchType_0 = 0
};

class Goalie //: public cPlayer
{
public:
    enum eNaviMode
    {
        eNaviMode_0 = 0
    };

    void InitActionPostWhistle();
    void WhackSTSPlayer(cFielder*);
    void StealBall(cPlayer*);
    void TacklePlayer(cPlayer*);
    void TrackTarget(const nlVector3&, float);
    void SetDesiredSaveFacing(const nlVector3&);
    void GetPhysicsGoalie();
    void FindSTSSpinData(bool);
    void FindSTSMissData(const nlVector3&);
    void FindSTSStunData();
    void EventHandler(Event*, void*);
    void DoPassRelease();
    void ChooseSwatAnim(int);
    void ChooseRunAnim(short, const nlVector3&, float);
    void CanInterceptPass();
    void CalcTimeToPlane();
    void CalcSaveParameters(float, unsigned int, bool, bool);
    void CalcBestSave(float, const nlVector3&, const nlVector3&, unsigned int, bool);
    void InitActionGrabBall();
    void IsTeammateHoardingBall();
    void InitActionSTSAttack();
    void InitActionDiveRecover();
    void InitActionChipShotStumble();
    void InitActionSTSRecover();
    void InitActionSTS();
    void InitActionSTSSetup();
    void InitActionSave();
    void InitActionSaveSetup(bool);
    void InitActionMoveWB();
    void InitActionMove(bool);
    void InitActionLooseBallSetup();
    void InitActionLooseBallCatch();
    void CleanGoalieAction();
    void PlayNewAnim(int);
    void PlayBlendedAnims(float, int);
    void SetupBlender(bool, const float*, int, int);
    void SaveBlendCallback(unsigned int, cPN_SAnimController*);
    void SetGoalieAction(eGoalieActionState, int);
    void UpdateActionState(float);
    void MakeSaveEvent(bool);
    void IsPassThreat();
    void IsOpponentInSTS();
    void IsOpponentBallCarrierInRange();
    void IsWithinPounceRange();
    void IsLooseBallClose(float);
    void CheckForSTSAttack();
    void CheckForLooseBallShotInProgress();
    void CheckForDelflectAwayFromNet();
    void IsInsideGoalieBox(const nlVector3&, float, float);
    void IsCloseToPlane(const nlVector3&, const nlVector3&, float);
    void InitiatePanicGrab(cPlayer*);
    void InitiatePickup();
    void HandleSTSContact(cBall*);
    void ShouldReposition();
    void FindDesiredGoaliePosition(nlVector3&, nlVector3&, nlVector3&, unsigned short&, const nlVector3*);
    void DoNavigation(float, float, Goalie::eNaviMode);
    void InitActionPursueRecover();
    void InitActionPursueBallPounce();
    void InitActionPursueBallCarrier();
    void InitActionPreCrouch(eGoalieCrouchType);
    void InitActionPassInterceptSave();
    void InitActionPassIntercept();
    void InitActionPass(bool);
    void ExecutePounce(cPlayer*, bool);
    void PreCollideWithBallCallback(const dContact&);
    void CollideWithCharacterCallback(CollisionPlayerPlayerData*);
    void CollideWithBallCallback(cBall*);
    void Update(float);
    ~Goalie();
    Goalie(eCharacterClass, const int*, cSHierarchy*, cAnimInventory*, const CharacterPhysicsData*, GoalieTweaks*, AnimRetargetList*);
};

class GoalieSaveData
{
public:
    void GetID();
};

#endif // _GOALIE_H_
