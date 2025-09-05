#include "Game/InterpreterCore.h"

#include "NL/nlDebug.h"
#include "NL/nlMemory.h"

/**
 * Offset/Address/Size: 0x68C | 0x802137D4 | size: 0x4C
 */
InterpreterCore::InterpreterCore(unsigned int size)
{
    m_unk_0x0C = (s32*)nlMalloc(size * 4);
    m_unk_0x08 = NULL;
}

/**
 * Offset/Address/Size: 0x62C | 0x80213774 | size: 0x60
 */
InterpreterCore::~InterpreterCore()
{
    nlFree(m_unk_0x0C);
}

/**
 * Offset/Address/Size: 0x5A4 | 0x802136EC | size: 0x88
 */
void InterpreterCore::LoadByteCode(void* arg0)
{
    m_unk_0x08 = (FunctionEntryPoint*)arg0;
    m_unk_0x08->current = (FunctionEntryPoint*)((u8*)m_unk_0x08 + 0x24);
    m_unk_0x08->next = (FunctionEntryPoint*)((u8*)m_unk_0x08->current + (m_unk_0x08->size * 8));
    m_unk_0x08->unk_0x1C = (FunctionEntryPoint*)((u8*)m_unk_0x08->next + m_unk_0x08->unk_0x08);
    m_unk_0x08->unk_0x20 = (FunctionEntryPoint*)((u8*)m_unk_0x08->unk_0x1C + m_unk_0x08->unk_0x0C);

    m_unk_0x14 = m_unk_0x0C;
    m_unk_0x1C = m_unk_0x14;
    m_unk_0x10 = (u32*)(m_unk_0x08->unk_0x1C);
    m_unk_0x18 = m_unk_0x14;

    m_unk_0x20 = m_unk_0x20 & ~0x60;
}

/**
 * Offset/Address/Size: 0x4C4 | 0x8021360C | size: 0xE0
 */
void InterpreterCore::CallFunction(unsigned long id)
{
    u32 sp8;
    u32 temp_r0;
    // void *temp_r5;

    // temp_r5 = m_unk_0x08;
    FunctionEntryPoint* fnc_ptr = (FunctionEntryPoint*)nlBSearch<FunctionEntryPoint, u32>(id, m_unk_0x08->current, m_unk_0x08->size);
    m_unk_0x10 = (u32*)((u8*)m_unk_0x08->unk_0x1C + fnc_ptr->size);

    // m_unk_0x10 = this->unk8->unk1C + (nlBSearch<18FunctionEntryPoint,Ul>__FRCUlP18FunctionEntryPointi(&sp8, temp_r5->unk14, temp_r5->unk4))->unk4;
    m_unk_0x14 = m_unk_0x0C;
    m_unk_0x1C = m_unk_0x14;
    m_unk_0x18 = m_unk_0x14;
    m_unk_0x20 &= ~0x60;
    temp_r0 = ((u8)m_unk_0x20 >> 5U) & 3;
    if (temp_r0 != 2)
    {
        if (temp_r0 == 0)
        {
            *m_unk_0x14 = 0;
            m_unk_0x14++;
            m_unk_0x20 = (m_unk_0x20 & ~0x60) | 0x20;
        }
        m_unk_0x20 &= ~0x80;

        while (!(((u8)m_unk_0x20 >> 7U) & 1))
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
    m_unk_0x10 = (u32*)((u8*)m_unk_0x08->unk_0x1C + offset);
    m_unk_0x14 = m_unk_0x0C;
    m_unk_0x1C = m_unk_0x14;
    m_unk_0x18 = m_unk_0x14;
    m_unk_0x20 &= ~0x60;
    temp_r0 = ((u8)m_unk_0x20 >> 5U) & 3;
    if (temp_r0 != 2)
    {
        if (temp_r0 == 0)
        {
            *m_unk_0x14 = 0;
            m_unk_0x14++;
            m_unk_0x20 = (m_unk_0x20 & ~0x60) | 0x20;
        }
        m_unk_0x20 &= ~0x80;

        while (!(((u8)m_unk_0x20 >> 7U) & 1))
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
    FunctionEntryPoint* temp_r5;

    temp_r5 = (FunctionEntryPoint*)m_unk_0x08;
    temp_r3 = nlBSearch<FunctionEntryPoint, u32>(id, temp_r5->current, temp_r5->size);
    return temp_r3 != NULL;
}

/**
 * Offset/Address/Size: 0x330 | 0x80213478 | size: 0x90
 */
void InterpreterCore::Run()
{
    u32 temp_r0;

    temp_r0 = (m_unk_0x20 >> 5U) & 3;
    if (temp_r0 != 2)
    {
        if (temp_r0 == 0)
        {
            *m_unk_0x14 = 0;
            m_unk_0x14++;
            m_unk_0x20 = (m_unk_0x20 & ~0x60) | 0x20;
        }
        m_unk_0x20 &= ~0x80;

        do
        {
            Step();
        } while (!(((u8)m_unk_0x20 >> 7U) & 1));
    }
}

/**
 * Offset/Address/Size: 0x308 | 0x80213450 | size: 0x28
 */
void InterpreterCore::StopWithUndo()
{
    m_unk_0x10 -= 2;
    m_unk_0x14 = m_unk_0x1C;
    m_unk_0x20 |= 0x80;
}

/**
 * Offset/Address/Size: 0x18 | 0x80213160 | size: 0x2F0
 */
void InterpreterCore::Step()
{
    u16 instr = *(u32*)m_unk_0x10;
    u16 op_high = instr & 0xFC00;
    u16 op_low = instr & 0x03FF;

    switch (op_high)
    {
    case 0x0000:
    { // opcode 0
        s32* dst = (s32*)m_unk_0x18;
        s32* stack = (s32*)m_unk_0x14;
        s32* table = (s32*)((u8*)m_unk_0x08 + 0x18);
        *stack = table[op_low];
        m_unk_0x14 = stack + 1;
        break;
    }

    case 0x4000:
    { // opcode 1
        s32* dst = (s32*)m_unk_0x14;
        u8* base = (u8*)m_unk_0x08 + 0x20;
        dst[0] = *(s32*)(base + op_low);
        m_unk_0x14 = dst + 1;
        break;
    }

    case 0x8000:
    { // opcode 2 (call virtual Run)
        m_unk_0x1C = m_unk_0x14;
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
            s32* dst = (s32*)m_unk_0x14;
            *dst = *(s32*)m_unk_0x18;
            m_unk_0x14 = dst + 1;
            m_unk_0x18 = m_unk_0x14;
            m_unk_0x14 += (instr & 0xFF);
            break;
        }

        case 0x1:
        { // pop
            m_unk_0x14 -= (instr & 0xFF);
            m_unk_0x14--;
            m_unk_0x18 = m_unk_0x14;
            break;
        }

        case 0x2:
        { // pop, store to m_unk_0x10
            m_unk_0x14--;
            m_unk_0x10 = *(u32**)m_unk_0x14;
            m_unk_0x14 -= (instr & 0xFF);
            if (!m_unk_0x10)
            {
                m_unk_0x20 |= 0x80;                       // stop
                m_unk_0x20 = (m_unk_0x20 & ~0x60) | 0x40; // set state to 2
                return;
            }
            break;
        }

        case 0x3:
        { // load indirect
            s8 offset = (s8)(instr & 0xFF);
            s32 value = ((s32*)m_unk_0x18)[offset];
            *(s32*)m_unk_0x14 = value;
            m_unk_0x14 += 4;
            break;
        }

        case 0x4:
        { // store indirect
            s8 offset = (s8)(instr & 0xFF);
            m_unk_0x14--;
            ((s32*)m_unk_0x18)[offset] = *(s32*)m_unk_0x14;
            break;
        }

        case 0x5:
        { // pop to temp
            m_unk_0x14--;
            *(s32*)&m_pad_0x04 = *(s32*)m_unk_0x14;
            break;
        }

        case 0x6:
        { // push temp
            *(s32*)m_unk_0x14 = *(s32*)&m_pad_0x04;
            m_unk_0x14 += 4;
            break;
        }

        case 0x7:
        { // store to indirect
            s8 offset = (s8)(instr & 0xFF);
            ((s32*)m_unk_0x18)[offset] = *(s32*)&m_pad_0x04;
            break;
        }

        case 0x8:
        { // load from indirect
            s8 offset = (s8)(instr & 0xFF);
            *(s32*)&m_pad_0x04 = ((s32*)m_unk_0x18)[offset];
            break;
        }

        case 0x9:
        { // push immediate
            *(s32*)m_unk_0x14 = (s32)(instr & 0xFF);
            m_unk_0x14 += 4;
            break;
        }

        case 0xA:
        { // call function
            *(s32*)m_unk_0x14 = *(s32*)m_unk_0x10;
            m_unk_0x14 += 4;
            s32* funcTable = (s32*)((u8*)m_unk_0x08 + 0x14);
            u8* base = (u8*)m_unk_0x08 + 0x1C;
            u32 index = ((u16*)m_unk_0x10)[1];
            m_unk_0x10 = (u32*)(base + (funcTable[index] & ~1));
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

    m_unk_0x10 += 2;
}

/**
 * Offset/Address/Size: 0x0 | 0x80213148 | size: 0x18
 */
bool InterpreterCore::IsFinished() const
{
    return ((m_unk_0x20 >> 5U) & 3) == 2;
}
