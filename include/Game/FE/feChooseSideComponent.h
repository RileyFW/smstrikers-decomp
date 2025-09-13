#ifndef _FECHOOSESIDECOMPONENT_H_
#define _FECHOOSESIDECOMPONENT_H_
#include "Game/FE/feInput.h"

class IChooseSide
{
public:
    void SaveChanges();
    void TweenSetPosCallback(void*, const float*);
    void AllControllersAreCentred() const;
    void AtLeastOnePlayerReady() const;
    void AllPluggedInAreReady() const;
    void AllPlayersReady() const;
    void PositionController(int, bool, bool);
    void SetReady(int, bool);
    void ResetAndPositionControllers(bool);
    void CheckControllers(int);
    void UpdateForPause(float, eFEINPUT_PAD*);
    void UpdateForFE(float, eFEINPUT_PAD*);
    void Update(float, eFEINPUT_PAD*, int);
    ~IChooseSide();
    IChooseSide();
};

#endif // _FECHOOSESIDECOMPONENT_H_
