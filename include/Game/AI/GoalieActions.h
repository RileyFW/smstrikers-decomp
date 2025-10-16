#ifndef _GOALIEACTIONS_H_
#define _GOALIEACTIONS_H_

// void 0x8028D294..0x8028D298 | size: 0x4;

class cPN_SingleAxisBlender;
class cPN_SAnimController;

class Goalie
{
public:
    void ActionLooseBallCatch(float);
    void ActionLooseBallDesperate(float);
    void ActionLooseBallPickup(float);
    void ActionLooseBallPursueRolling(float);
    void ActionLooseBallSetup(float);
    void MoveDirectionCB(unsigned int, cPN_SingleAxisBlender*);
    void MoveWeightCB(unsigned int, cPN_SingleAxisBlender*);
    void StrafeSynchronizedSpeedCallback(unsigned int, cPN_SAnimController*);
    void ActionMove(float);
    void RunWeightCB(unsigned int, cPN_SingleAxisBlender*);
    void ActionMoveWB(float);
    void ActionSaveSetup(float);
    void ActionSaveReposition(float);
    void ActionSave(float);
    void ActionSTS(float);
    void ActionSTSSetup(float);
    void ActionSTSRecover(float);
    void ActionChipShotStumble(float);
    void ActionDiveRecover(float);
    void ActionPass(float);
    void ActionPassIntercept(float);
    void ActionPreCrouch(float);
    void ActionPursueBallCarrier(float);
    void ActionPursueBallPounce(float);
    void ActionOffplay(float);
    void ActionLooseBallPursueBouncing(float);
    void ActionSTSAttackSetup(float);
    void ActionSTSAttack(float);
    void ActionSnapBall(float);
    void ActionGrabBall(float);
};

#endif // _GOALIEACTIONS_H_
