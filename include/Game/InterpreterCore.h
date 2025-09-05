#ifndef _INTERPRETERCORE_H_
#define _INTERPRETERCORE_H_

#include "types.h"
#include "NL/nlBSearch.h"

struct FunctionEntryPoint // size 24
{
    /* 0x00 */ u32 key;
    /* 0x04 */ u32 size;
    /* 0x08 */ u32 unk_0x08;
    /* 0x0C */ u32 unk_0x0C;   
    /* 0x10 */ u32 instr;
    /* 0x14 */ FunctionEntryPoint *current;
    /* 0x18 */ FunctionEntryPoint *next;
    /* 0x1C */ FunctionEntryPoint *unk_0x1C; // or an instruction?
    /* 0x20 */ FunctionEntryPoint *unk_0x20;
};

struct Instruction // size 8
{
    /* 0x00 */ u16 m_unk_0x00;
    /* 0x02 */ u16 m_pad_0x02;
    /* 0x04 */ u32 m_data;
};

class InterpreterCore
{
public:
    InterpreterCore(unsigned int stackSize);
    virtual ~InterpreterCore();

    void LoadByteCode(void* byteCode);
    void CallFunction(unsigned long id);
    void CallFunctionAt(unsigned long address);
    bool FunctionExists(unsigned long id);
    virtual void Run();
    void StopWithUndo();
    void Step();
    bool IsFinished() const;

    /* 0x04 */ char      m_pad_0x04[4];
    /* 0x08 */ FunctionEntryPoint* m_unk_0x08;
    /* 0x0C */ s32*      m_unk_0x0C;
    /* 0x10 */ u32*      m_unk_0x10; // is this an instruction?
    /* 0x14 */ s32*      m_unk_0x14;
    /* 0x18 */ s32*      m_unk_0x18;
    /* 0x1C */ s32*      m_unk_0x1C;
    /* 0x20 */ u8        m_unk_0x20;
};

#endif // _INTERPRETERCORE_H_
