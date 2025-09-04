#ifndef AIPAD_H
#define AIPAD_H

#include "types.h"
#include "NL/globalpad.h"

class cAIPad
{
public:
    cAIPad() { m_pPad = NULL; };

    bool IsTurboPressed();
    u16 GetCStickMovementStickDirection();
    f32 GetCStickMovementStickMagnitude();
    u16 GetMovementStickDirection();
    f32 GetMovementStickMagnitude();

    cGlobalPad* m_pPad; // 0x00
};

struct AIPadManager
{
    static void Startup();
    static cAIPad mAIPads[4];
};

#endif // AIPAD_H
