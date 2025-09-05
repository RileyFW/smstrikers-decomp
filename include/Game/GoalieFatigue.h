#ifndef _GOALIEFATIGUE_H_
#define _GOALIEFATIGUE_H_

#include "types.h"

class GoalieFatigue
{
public:
    GoalieFatigue();
    void Reset();
    void Update(float);
    void RegisterShot(float);

    /* 0x00 */ f32 m_unk_0x00;
    /* 0x04 */ f32 m_unk_0x04;
    /* 0x08 */ f32 m_unk_0x08;
    /* 0x0C */ f32 m_unk_0x0C;
};

#endif // _GOALIEFATIGUE_H_
