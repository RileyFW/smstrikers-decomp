#ifndef _WIPER_H_
#define _WIPER_H_

#include "Game/Transitions/ScreenTransitionManager.h"

struct WiperCallback : public ScreenTransitionCallback
{
    virtual void TransitionProgressed(float) { };
    virtual void TransitionFinished() { };

    /* 0x04 */ bool mTransitionActive;
}; // total size: 0x8

class Wiper
{
public:
    void Reset();
    void Initialize();
    void WipeInProgress() const;
    void CutHasOccured() const;
    void Instance();
    void DoWipe(const char*);
    void Render(float);
};

#endif // _WIPER_H_
