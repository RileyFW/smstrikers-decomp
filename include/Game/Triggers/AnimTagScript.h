#ifndef _ANIMTAGSCRIPT_H_
#define _ANIMTAGSCRIPT_H_

class AnimTagScriptInterpreter
{
public:
    void AnimControllerCB(unsigned int);
    // void SetupAnimationTriggers(const char*, cInventory<cSAnim>*);

    // total size: 0xC0
    class SlotPool m_AnimTagSlotPool; // offset 0x24, size 0x18
    void* m_ppBytecode[32];           // offset 0x3C, size 0x80
    int m_BytecodeCount;              // offset 0xBC, size 0x4
};

// class nlBSearch<BinaryTriggerFile
// {
// public:
//     void ANIM_RECORD, unsigned long>(const unsigned long&, BinaryTriggerFile::ANIM_RECORD*, int);
// };

#endif // _ANIMTAGSCRIPT_H_
