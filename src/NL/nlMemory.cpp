#include "NL/nlMemory.h"
#include "NL/MemAlloc.h"

#include <types.h>

#include "dolphin/os.h"
#include "dolphin/pad.h"
#include "dolphin/dvd.h"
#include "dolphin/vm/VM.h"
#include "dolphin/vi/vifuncs.h"

static u8 s_MemoryInitialized = 0;

MemoryAllocator StandardAllocator;
MemoryAllocator VirtualAllocator;

/**
 * Offset/Address/Size: 0x0 | 0x801D1EE4 | size: 0x40
 */
void nlFree(void* ptr)
{
    if (((uint)ptr & 0x80000000) == 0)
    {
        VirtualAllocator.Free(ptr);
    }
    else
    {
        StandardAllocator.Free(ptr);
    }
}

/**
 * Offset/Address/Size: 0x40 | 0x801D1F24 | size: 0x64
 */
void* nlMalloc(unsigned long size, unsigned int alignment, bool atEnd)
{
    if (s_MemoryInitialized == 0)
    {
        nlInitMemory();
    }
    return StandardAllocator.Allocate(size, alignment, atEnd);
}

/**
 * Offset/Address/Size: 0xA4 | 0x801D1F88 | size: 0x4C
 */
void* nlMalloc(unsigned long size)
{
    if (s_MemoryInitialized == 0)
    {
        nlInitMemory();
    }
    return StandardAllocator.Allocate(size, 8, false);
}

/**
 * Offset/Address/Size: 0xF0 | 0x801D1FD4 | size: 0x4C
 */
void* operator new(unsigned long size)
{
    return nlMalloc(size);
}

/**
 * Offset/Address/Size: 0x13C | 0x801D2020 | size: 0x40
 */
void operator delete[](void* ptr)
{
    nlFree(ptr);
}

/**
 * Offset/Address/Size: 0x17C | 0x801D2060 | size: 0x40
 */
void operator delete(void* ptr)
{
    nlFree(ptr);
}

/**
 * Offset/Address/Size: 0x0 | 0x801D20A0 | size: 0x24
 */
unsigned int nlVirtualTotalFree()
{
    return VirtualAllocator.TotalFreeMemory();
}

/**
 * Offset/Address/Size: 0x24 | 0x801D20C4 | size: 0x24
 */
unsigned int nlVirtualLargestBlock()
{
    return VirtualAllocator.LargestFreeBlock();
}

/**
 * Offset/Address/Size: 0x48 | 0x801D20E8 | size: 0x28
 */
void nlVirtualFree(void* ptr)
{
    VirtualAllocator.Free(ptr);
}

/**
 * Offset/Address/Size: 0x70 | 0x801D2110 | size: 0x30
 */
void* nlVirtualAlloc(unsigned long size, bool bZero)
{
    return VirtualAllocator.Allocate(size, 0x20, bZero);
}

/**
 * Offset/Address/Size: 0xA0 | 0x801D2140 | size: 0x1B8
 */
void nlInitMemory()
{
    u32 temp_r30;
    uintptr_t temp_r31;
    uintptr_t temp_r31_2;
    uintptr_t temp_r31_3;
    uintptr_t temp_r3;
    uintptr_t temp_r3_2;
    s32 var_ctr_2;
    s8* var_r6_2;
    u32 temp_r4;
    u32 temp_r4_2;
    u32 temp_r5;
    u32 var_ctr;
    u32 var_r7;
    uintptr_t temp_r3_3;
    uintptr_t var_r6;

    if ((u8)s_MemoryInitialized == 0)
    {
        s_MemoryInitialized = 1;
        VMInit(0x100000, 0x700000, 0x900000);
        VMAlloc(0x7E000000, 0x900000);
        DVDInit();
        VIInit();
        PADInit();
        temp_r31 = (uintptr_t)OSGetArenaLo();
        temp_r3 = (uintptr_t)OSGetArenaHi();
        temp_r31_2 = (uintptr_t)OSInitAlloc((void*)temp_r31, (void*)temp_r3, 1);
        OSSetArenaLo((void*)temp_r31_2); // not sure about the parameter
        temp_r31_3 = temp_r3 & 0xFFFFFFE0;
        temp_r3_2 = (temp_r31_2 + 0x1F) & 0xFFFFFFE0;
        temp_r30 = temp_r31_3 - temp_r3_2;
        OSCreateHeap((void*)temp_r3_2, (void*)temp_r31_3);
        OSSetCurrentHeap(0); // not sure about the parameter
        OSSetArenaLo((void*)temp_r31_3);
        temp_r3_3 = (uintptr_t)OSAllocFromHeap(__OSCurrHeap, temp_r30 + 0xFFFC0000);
        temp_r4 = temp_r30 + 0xFFFC0000;
        var_r7 = 0U;
        if (temp_r4 > 0U)
        {
            temp_r5 = temp_r30 + 0xFFFBFFF8;
            if (temp_r4 > 8U)
            {
                var_r6 = temp_r3_3;
                var_ctr = (u32)(temp_r5 + 7) >> 3U;
                if (temp_r5 > 0U)
                {
                    do
                    {
                        ((u8*)var_r6)[0] = -0x33;
                        var_r7 += 8;
                        ((u8*)var_r6)[1] = -0x33;
                        ((u8*)var_r6)[2] = -0x33;
                        ((u8*)var_r6)[3] = -0x33;
                        ((u8*)var_r6)[4] = -0x33;
                        ((u8*)var_r6)[5] = -0x33;
                        ((u8*)var_r6)[6] = -0x33;
                        ((u8*)var_r6)[7] = -0x33;
                        var_r6 += 8;
                        var_ctr -= 1;
                    } while (var_ctr != 0);
                }
            }
            temp_r4_2 = temp_r30 + 0xFFFC0000;
            var_r6_2 = (s8*)(temp_r3_3 + var_r7);
            var_ctr_2 = temp_r4_2 - var_r7;
            if (var_r7 < temp_r4_2)
            {
                do
                {
                    *var_r6_2 = -0x33;
                    var_r6_2 += 1;
                    var_ctr_2 -= 1;
                } while (var_ctr_2 != 0);
            }
        }
        StandardAllocator.Initialize((void*)temp_r3_3, temp_r30 + 0xFFFC0000);
        VirtualAllocator.Initialize((void*)0x7E000000, 0x900000);
        OSReport("After nlInitMemory\n");
        OSReport("Free Memory: %u\n", StandardAllocator.TotalFreeMemory());
        OSReport("Largest Free Block: %u\n", StandardAllocator.LargestFreeBlock());
    }
}
