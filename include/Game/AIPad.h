#ifndef AIPAD_H
#define AIPAD_H

#include "types.h"
#include "NL/globalpad.h"

// typedef unsigned char u8;
// typedef unsigned short u16;
// typedef unsigned int u32;
// typedef float f32;

// Minimal cPad layout & vtable shape used by this TU (MWCC 2.0)
// We only define the entries/fields actually touched by AIPad.s.
// class cPad
// {
// public:
//     virtual ~cPad();                                     // 0x00
//     virtual void vf1();                                  // 0x04
//     virtual void vf2();                                  // 0x08
//     virtual void vf3();                                  // 0x0C
//     virtual void vf4();                                  // 0x10
//     virtual f32 GetHoldOrPressure(int button, int flag); // 0x14

//     // Field layout as accessed in AIPad.s
//     u32 m_unk4;      // 0x04
//     u16 m_moveDir;   // 0x08
//     u16 _pad0A;      // 0x0A (alignment)
//     f32 m_moveMag;   // 0x0C
//     u16 m_cstickDir; // 0x10
//     u16 _pad12;      // 0x12 (alignment)
//     f32 m_cstickMag; // 0x14
// };

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

// External symbols referenced by this TU
// extern u16 m_aJoystickRemap__14cCameraManager;
// extern cPad* GetPad__11cPadManagerFi(int index);

#endif // AIPAD_H
