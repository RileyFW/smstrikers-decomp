#ifndef _OBJECTBLUR_H_
#define _OBJECTBLUR_H_

#include "NL/nlMath.h"
#include "NL/nlSlotPool.h"
#include "NL/nlDLRing.h"

// void nlDeleteDLRing<BlurHandler>(BlurHandler**);
// void nlDLRingIsEnd<BlurHandler>(BlurHandler*, BlurHandler*);
// void nlDLRingGetStart<BlurHandler>(BlurHandler*);
// void nlDLRingRemove<BlurHandler>(BlurHandler**, BlurHandler*);
// void nlDLRingAddEnd<BlurHandler>(BlurHandler**, BlurHandler*);
// void nlDLRingAddStart<BlurHandler>(BlurHandler**, BlurHandler*);
// void nlDeleteRing<BlurHandler>(BlurHandler**);

struct BlurPointEntry
{
    class nlVector3 v3Top;    // offset 0x0, size 0xC
    class nlVector3 v3Bottom; // offset 0xC, size 0xC
}; // total size: 0x18

class BlurHandler
{
public:
    void RenderMesh(unsigned long);
    void Die(float);
    void AddViewOrientedPoint(const nlVector3& position, const nlVector3& forwardVector);
    bool ConstructViewOrientedPoints(nlVector3& topPoint, nlVector3& bottomPoint, nlVector3 position, const nlVector3& forwardVector);

public:
    /* 0x00 */ BlurHandler* m_next;
    /* 0x04 */ BlurHandler* m_prev;
    /* 0x08 */ bool m_bAdditive;
    /* 0x0C */ u32 m_uTexHashID;
    /* 0x10 */ float m_fLineWidth;
    /* 0x14 */ BlurPointEntry m_pointFinal;
    /* 0x2C */ BlurPointEntry* m_pLastPoint;
    /* 0x30 */ bool m_bDying;
    /* 0x34 */ float m_fDyingTimer;
    /* 0x38 */ float m_fTimeToDie;
    /* 0x3C */ int m_maxPositionEntries;
    /* 0x40 */ BlurPointEntry* m_pointRingBuffer;
    /* 0x44 */ int m_nInsertIndex;
    /* 0x48 */ int m_nTrailEndPointer;
}; // total size: 0x4C

class BlurManager
{
public:
    void Shutdown();
    void Update(float);
    static void DestroyHandler(BlurHandler*, float);
    static BlurHandler* GetNewHandler(const char*, float, int, bool);

    static SlotPool<BlurHandler> m_BlurHandlerSlotPool;
    static BlurHandler* m_activeBlurHandler;
};

// class SlotPool<BlurHandler>
// {
// public:
//     void ~SlotPool();
// };

#endif // _OBJECTBLUR_H_
