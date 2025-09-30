#ifndef _COLOURBLENDSCREENTRANSITION_H_
#define _COLOURBLENDSCREENTRANSITION_H_

#include "Game/Sys/simpleparser.h"

#include "Game/Transitions/ScreenTransitionManager.h"

class ColourBlendScreenTransition : public ScreenTransition
{
public:
    virtual ~ColourBlendScreenTransition();
    virtual void Update(float);
    virtual void Render(eGLView);
    virtual bool IsFinished();
    virtual float Time() const;
    virtual void Reset();
    virtual void Cancel();
    virtual float GetTransitionLength();
    ColourBlendScreenTransition* GetFromParser(SimpleParser*);
};

#endif // _COLOURBLENDSCREENTRANSITION_H_
