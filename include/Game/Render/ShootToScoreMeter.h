#ifndef _SHOOTTOSCOREMETER_H_
#define _SHOOTTOSCOREMETER_H_

// void 0x8028D314..0x8028D318 | size : 0x4;

#include "NL/nlMath.h"
#include "NL/nlColour.h"

class ShootToScoreMeter
{
public:
    enum STSMeterType
    {
        REGULAR_SHOOT_TO_SCORE_PHASE1 = 0,
        REGULAR_SHOOT_TO_SCORE_PHASE2 = 1,
    };

    void TurnOnMeter(ShootToScoreMeter::STSMeterType, float);
    void RumbleMeter(float, float, float);
    void DrawMeter();
    void DrawColouredRegion(float, float, const nlColour&, const nlColour&, nlMatrix4, float);
    void UpdateAndRender(float);
    void SetWhiteBarPosition(float);
    void SetSavedWhiteBarPosition(float);
    void SetGreenBarPosition(float);
    void SetGreenRegionWidth(float);
    void DrawCaptainMeter();
};

#endif // _SHOOTTOSCOREMETER_H_
