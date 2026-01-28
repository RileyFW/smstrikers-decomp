#include "Game/Triggers/AnimTagScript.h"

// /**
//  * Offset/Address/Size: 0x0 | 0x80214594 | size: 0x8C
//  */
// void nlBSearch<BinaryTriggerFile::ANIM_RECORD, unsigned long>(const unsigned long&, BinaryTriggerFile::ANIM_RECORD*, int)
// {
// }

/**
 * Offset/Address/Size: 0x0 | 0x80214530 | size: 0x64
 */
void AnimTagScriptInterpreter::AnimControllerCB(unsigned int)
{
    InterpreterCore* pVtbl = *(InterpreterCore**)this;
    unsigned long address = (unsigned long)m_Header;
    if ((address + 0x10000) != 0xFFFF)
    {
        pVtbl->CallFunctionAt(address);
    }
    pVtbl->DoFunctionCall(m_Return);
}

/**
 * Offset/Address/Size: 0x0 | 0x80214354 | size: 0x1DC
 */
void AnimTagScriptInterpreter::SetupAnimationTriggers(const char*, cInventory<cSAnim>*)
{
}
