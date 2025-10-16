#ifndef _ANIMTAGSCRIPT_H_
#define _ANIMTAGSCRIPT_H_

#include "NL/nlSlotPool.h"
#include "Game/Inventory.h"
#include "Game/SAnim.h"

class AnimTagScriptInterpreter
{
public:
    void AnimControllerCB(unsigned int);
    void SetupAnimationTriggers(const char*, cInventory<cSAnim>*);

    /* 0x24 */ SlotPool<unsigned long> m_AnimTagSlotPool; // size 0x18
    /* 0x3C */ void* m_ppBytecode[32];                    // size 0x80
    /* 0xBC */ int m_BytecodeCount;                       // size 0x4
}; // total size: 0xC0

// class nlBSearch<BinaryTriggerFile
// {
// public:
//     void ANIM_RECORD, unsigned long>(const unsigned long&, BinaryTriggerFile::ANIM_RECORD*, int);
// };

#endif // _ANIMTAGSCRIPT_H_
