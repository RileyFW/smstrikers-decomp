#ifndef _FEINPUT_H_
#define _FEINPUT_H_

#include "types.h"
#include "NL/globalpad.h"

class BaseSceneHandler;

enum eFEINPUT_PAD
{
    FE_PAD1_ID = 0,
    FE_PAD2_ID = 1,
    FE_PAD3_ID = 2,
    FE_PAD4_ID = 3,
    FE_PAD5_ID = 4,
    FE_PAD6_ID = 5,
    FE_PAD7_ID = 6,
    FE_PAD8_ID = 7,
    FE_ALL_PADS = 8,
};

class FEInput
{
public:
    void EnableAnalogToDPadMapping(eFEINPUT_PAD, bool);
    void SetAutoRepeatParams(eFEINPUT_PAD, int, float, float);
    void Update(float);
    bool HasInputLock(BaseSceneHandler*) const;
    void PopExclusiveInputLock(BaseSceneHandler*);
    void PushExclusiveInputLock(BaseSceneHandler*, int);
    void EnableInputIfSceneHasFocus(BaseSceneHandler*);
    void JustReleased(eFEINPUT_PAD, int, bool, eFEINPUT_PAD*);
    bool JustPressed(eFEINPUT_PAD, int, bool, eFEINPUT_PAD*);
    void IsAutoPressed(eFEINPUT_PAD, int, bool, eFEINPUT_PAD*);
    void IsPressed(eFEINPUT_PAD, int, bool, eFEINPUT_PAD*);
    void IsConnected(eFEINPUT_PAD);
    void GetGlobalPad(eFEINPUT_PAD) const;
    void Reset();
    FEInput();
    void Initialize();
    virtual ~FEInput();
};

static FEInput* g_pFEInput;

#endif // _FEINPUT_H_
