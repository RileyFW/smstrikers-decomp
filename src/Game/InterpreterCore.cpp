#include "Game/InterpreterCore.h"

#include "NL/nlDebug.h"
#include "NL/nlMemory.h"

/**
 * Offset/Address/Size: 0x68C | 0x802137D4 | size: 0x4C
 */
InterpreterCore::InterpreterCore(unsigned int size)
{
    m_StackSegment = (u32*)nlMalloc(size * 4);
    m_Header = NULL;
}

/**
 * Offset/Address/Size: 0x62C | 0x80213774 | size: 0x60
 */
InterpreterCore::~InterpreterCore()
{
    nlFree(m_StackSegment);
}

/**
 * Offset/Address/Size: 0x5A4 | 0x802136EC | size: 0x88
 */
void InterpreterCore::LoadByteCode(void* data)
{
    m_Header = (ByteCodeHeader*)data;
    m_Header->m_FunctionTable = (FunctionEntryPoint*)((u8*)m_Header + sizeof(ByteCodeHeader));
    m_Header->m_DataSegment = (u32*)((u8*)m_Header->m_FunctionTable + (m_Header->numFunctions * sizeof(FunctionEntryPoint)));
    m_Header->m_CodeSegment = (u16*)((u8*)m_Header->m_DataSegment + m_Header->dataSegmentSize);
    m_Header->m_StringSegment = ((u8*)m_Header->m_CodeSegment) + m_Header->codeSegmentSize;

    m_SP = m_StackSegment;
    m_SavedSP = m_SP;
    m_IP = m_Header->m_CodeSegment;
    m_BP = m_SP;

    m_Stop = m_Stop & ~0x60;
}

/**
 * Offset/Address/Size: 0x4C4 | 0x8021360C | size: 0xE0
 */
void InterpreterCore::CallFunction(unsigned long id)
{
    u32 sp8;
    u32 temp_r0;

    FunctionEntryPoint* fnc_ptr = (FunctionEntryPoint*)nlBSearch<FunctionEntryPoint, u32>(id, m_Header->m_FunctionTable, m_Header->numFunctions);
    m_IP = (u16*)((u8*)m_Header->m_CodeSegment + fnc_ptr->offset);

    // m_unk_0x10 = this->unk8->unk1C + (nlBSearch<18FunctionEntryPoint,Ul>__FRCUlP18FunctionEntryPointi(&sp8, temp_r5->unk14, temp_r5->unk4))->unk4;
    m_SP = m_StackSegment;
    m_SavedSP = m_SP;
    m_BP = m_SP;
    m_Stop &= ~0x60;
    temp_r0 = ((u8)m_Stop >> 5U) & 3;
    if (temp_r0 != 2)
    {
        if (temp_r0 == 0)
        {
            *m_SP = 0;
            m_SP++;
            m_Stop = (m_Stop & ~0x60) | 0x20;
        }
        m_Stop &= ~0x80;

        while (!(((u8)m_Stop >> 7U) & 1))
        {
            Step();
        }
        // loop_5:
        //         if (!(((u8) m_unk_0x20 >> 7U) & 1)) {
        //             Step__15InterpreterCoreFv(this);
        //             goto loop_5;
        //         }
    }
}

/**
 * Offset/Address/Size: 0x400 | 0x80213548 | size: 0xC4
 */
void InterpreterCore::CallFunctionAt(unsigned long offset)
{
    u32 temp_r0;
    m_IP = (u16*)((u8*)m_Header->m_CodeSegment + offset);
    m_SP = m_StackSegment;
    m_SavedSP = m_SP;
    m_BP = m_SP;
    m_Stop &= ~0x60;
    temp_r0 = ((u8)m_Stop >> 5U) & 3;
    if (temp_r0 != 2)
    {
        if (temp_r0 == 0)
        {
            *m_SP = 0;
            m_SP++;
            m_Stop = (m_Stop & ~0x60) | 0x20;
        }
        m_Stop &= ~0x80;

        while (!(((u8)m_Stop >> 7U) & 1))
        {
            Step();
        }
    }
}

/**
 * Offset/Address/Size: 0x3C0 | 0x80213508 | size: 0x40
 */
bool InterpreterCore::FunctionExists(unsigned long id)
{
    FunctionEntryPoint* temp_r3;
    ByteCodeHeader* temp_r5;

    temp_r5 = m_Header;
    temp_r3 = nlBSearch<FunctionEntryPoint, u32>(id, temp_r5->m_FunctionTable, temp_r5->numFunctions);
    return temp_r3 != NULL;
}

/**
 * Offset/Address/Size: 0x330 | 0x80213478 | size: 0x90
 */
void InterpreterCore::Run()
{
    u32 temp_r0;

    temp_r0 = (m_Stop >> 5U) & 3;
    if (temp_r0 != 2)
    {
        if (temp_r0 == 0)
        {
            *m_SP = 0;
            m_SP++;
            m_Stop = (m_Stop & ~0x60) | 0x20;
        }
        m_Stop &= ~0x80;

        do
        {
            Step();
        } while (!(((u8)m_Stop >> 7U) & 1));
    }
}

/**
 * Offset/Address/Size: 0x308 | 0x80213450 | size: 0x28
 */
void InterpreterCore::StopWithUndo()
{
    m_IP -= 2;
    m_SP = m_SavedSP;
    m_Stop |= 0x80;
}

/**
 * Offset/Address/Size: 0x18 | 0x80213160 | size: 0x2F0
 */
void InterpreterCore::Step()
{
    u16 instr = *(u32*)m_IP;
    u16 op_high = instr & 0xFC00;
    u16 op_low = instr & 0x03FF;

    switch (op_high)
    {
    case 0x0000:
    { // opcode 0
        u32* dst = m_BP;
        u32* stack = m_SP;
        u32* table = (u32*)((u8*)m_Header + 0x18);
        *stack = table[op_low];
        m_SP = stack + 1;
        break;
    }

    case 0x4000:
    { // opcode 1
        u32* dst = m_SP;
        u8* base = (u8*)m_Header + 0x20;
        dst[0] = *(u32*)(base + op_low);
        m_SP = dst + 1;
        break;
    }

    case 0x8000:
    { // opcode 2 (call virtual Run)
        m_SavedSP = m_SP;
        Run();
        break;
    }

    case 0xC000:
    { // opcode 3 (extended)
        u8 ext_opcode = (instr >> 8) & 0xFF;
        switch (ext_opcode)
        {
        case 0x0:
        { // push m_unk_0x18
            u32* dst = m_SP;
            *dst = *m_BP;
            m_SP = dst + 1;
            m_BP = m_SP;
            m_SP += (instr & 0xFF);
            break;
        }

        case 0x1:
        { // pop
            m_SP -= (instr & 0xFF);
            m_SP--;
            m_BP = m_SP;
            break;
        }

        case 0x2:
        { // pop, store to m_unk_0x10
            m_SP--;
            m_IP = *(u16**)m_SP;
            m_SP -= (instr & 0xFF);
            if (!m_IP)
            {
                m_Stop |= 0x80;                   // stop
                m_Stop = (m_Stop & ~0x60) | 0x40; // set state to 2
                return;
            }
            break;
        }

        case 0x3:
        { // load indirect
            s8 offset = (s8)(instr & 0xFF);
            s32 value = ((s32*)m_BP)[offset];
            *(s32*)m_SP = value;
            m_SP += 4;
            break;
        }

        case 0x4:
        { // store indirect
            s8 offset = (s8)(instr & 0xFF);
            m_SP--;
            ((s32*)m_BP)[offset] = *(s32*)m_SP;
            break;
        }

        case 0x5:
        { // pop to temp
            m_SP--;
            m_Return = *m_SP;
            break;
        }

        case 0x6:
        { // push temp
            *m_SP = m_Return;
            m_SP += 4;
            break;
        }

        case 0x7:
        { // store to indirect
            s8 offset = (s8)(instr & 0xFF);
            ((u32*)m_BP)[offset] = m_Return;
            break;
        }

        case 0x8:
        { // load from indirect
            s8 offset = (s8)(instr & 0xFF);
            m_Return = ((u32*)m_BP)[offset];
            break;
        }

        case 0x9:
        { // push immediate
            *m_SP = (u32)(instr & 0xFF);
            m_SP += 4;
            break;
        }

        case 0xA:
        { // call function
            *m_SP = *m_IP;
            m_SP += 4;
            // s32* funcTable = (s32*)((u8*)m_Header + 0x14);
            FunctionEntryPoint* functionEntryPoint = m_Header->m_FunctionTable;
            // u8* base = (u8*)m_Header + 0x1C;
            u16* codeSegment = m_Header->m_CodeSegment;
            u16 index = m_IP[1];
            m_IP = (u16*)(codeSegment + (functionEntryPoint[index].offset & ~1));
            break;
        }

        default:
            nlBreak();
        }
        break;
    }

    default:
        nlBreak();
    }

    m_IP += 2;
}

/**
 * Offset/Address/Size: 0x0 | 0x80213148 | size: 0x18
 */
bool InterpreterCore::IsFinished() const
{
    return ((m_Stop >> 5U) & 3) == 2;
}
