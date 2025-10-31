#ifndef _CLOCK_H_
#define _CLOCK_H_

#include "NL/nlDLRing.h"

typedef void (*ClockCallback)(unsigned long, unsigned long);

class Clock
{
public:
    Clock(float, float, float, unsigned long, ClockCallback);
    virtual ~Clock();
    void Start();
    void Reset(float, float, float);
    void Stop();

    /* 0x04 */ float m_unk_0x04;
    /* 0x08 */ float m_unk_0x08;
    /* 0x0C */ float m_unk_0x0C;
    /* 0x10 */ ClockCallback m_callback;
    /* 0x14 */ unsigned long m_unk_0x14;
    /* 0x18 */ s32 m_unk_0x18;

    /* 0x1C */ unsigned long m_unk_0x1C;
    /* 0x20 */ unsigned long m_unk_0x20;

    /* 0x24 */ Clock* m_next;
    /* 0x28 */ Clock* m_prev;
};

class ClockManager
{
public:
    static void Initialize();
    static void Update(float dt);

    /* 0x00 */ static Clock* m_inactiveList;
    /* 0x04 */ static Clock* m_activeList;
    /* 0x08 */ static Clock* m_pendingActiveList;
    /* 0x0C */ static bool m_bUpdatingClocks;
};

#endif // _CLOCK_H_
