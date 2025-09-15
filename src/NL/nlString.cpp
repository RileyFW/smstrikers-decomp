#include "NL/nlString.h"
#include <string.h>

/**
 * Offset/Address/Size: 0x0 | 0x801D2638 | size: 0x48
 */
void nlStrToWcs(const char* arg0, unsigned short* arg1, unsigned long arg2)
{
    char* var_r3;
    s16* var_r7;
    u8 temp_cr0_eq;
    u32 var_r8;
    u8 temp_r0;

    var_r3 = (char*)arg0;
    var_r8 = arg2;
    var_r7 = (s16*)arg1;
loop_2:
    // temp_cr0_eq = var_r8 == 0;
    // var_r8 -= 1;
    // if (temp_cr0_eq != 0) {
    if (var_r8-- != 0)
    {
        temp_r0 = *var_r3;
        *var_r7 = (s16)temp_r0;
        if (temp_r0 != 0)
        {
            var_r7++;
            var_r3++;
            goto loop_2;
        }
    }
    arg1[arg2 - 1] = 0;
}

/**
 * Offset/Address/Size: 0x48 | 0x801D2680 | size: 0x140
 */
void nlZeroMemory(void* buffer, unsigned long size)
{
    memset(buffer, 0, size);
}

/**
 * Offset/Address/Size: 0x188 | 0x801D27C0 | size: 0x64
 */
u32 nlStringLowerHash(const char* str)
{
    u32 h = -1;
    while (*str)
    {
        h += (h << 5);
        h += (u32)nlToLower<unsigned char>(*str++);
    }
    return h;
}

/**
 * Offset/Address/Size: 0x1EC | 0x801D2824 | size: 0x30
 */
u32 nlStringHash(const char* str)
{
    u32 h = -1;
    while (*str)
    {
        h += (h << 5);
        h += (unsigned char)*str++;
    }
    return h;
}
