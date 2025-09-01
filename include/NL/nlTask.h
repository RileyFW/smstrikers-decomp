#ifndef _NLTASK_H_
#define _NLTASK_H_

#include "types.h"

// Global task time bounds

// bool nlDLRingIsEnd<nlTask>(nlTask*, nlTask*);
// void nlDLRingGetStart<nlTask>(nlTask*);
// void nlDLRingAddStart<nlTask>(nlTask**, nlTask*);
// void nlDLRingInsert<nlTask>(nlTask**, nlTask*, nlTask*);

class nlTask
{
public:
    virtual void Run(float) = 0;
    virtual const char* GetName() = 0;
    virtual void StateTransition(unsigned int, unsigned int);

    /* 0x04 */ nlTask* m_next;
    /* 0x08 */ nlTask* m_prev;
    /* 0x0C */ u32 m_unk_0x0C;
    /* 0x10 */ u32 m_unk_0x10;
    /* 0x14 */ u32 m_unk_0x14; // current ticker value
}; // size 0x18

class nlTaskManager
{
public:
    static void SetTimeDilation(float);
    static void SetNextState(unsigned int state);
    static void RunAllTasks();
    static void AddTask(nlTask*, unsigned int, unsigned int);
    static void Startup(unsigned int);

    static nlTaskManager* m_pInstance;

    /* 0x00 */ float m_timeDilation;
    /* 0x04 */ nlTask* m_taskRingHead; // Head of the task DLRing
    /* 0x08 */ u32 m_unk_0x08;
    /* 0x0C */ u32 m_nextState;
    /* 0x10 */ u32 m_taskCount;
    /* 0x14 */ float m_unk_0x14;
    /* 0x18 */ u8 m_flags;
};

#endif // _NLTASK_H_
