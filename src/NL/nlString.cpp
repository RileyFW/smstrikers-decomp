#include "NL/nlString.h"
#include <string.h>

/**
 * Offset/Address/Size: 0x0 | 0x801D2638 | size: 0x48
 */
void nlStrToWcs(const char* str, unsigned short* wstr, unsigned long maxLen)
{
    unsigned short* dest;
    unsigned long remaining;

    remaining = maxLen;
    dest = wstr;

    while (remaining-- != 0 && (*dest = (s16)*str) != 0)
    {
        dest++;
        str++;
    }
    wstr[maxLen - 1] = 0;
}

/**
 * Offset/Address/Size: 0x48 | 0x801D2680 | size: 0x140
 * TODO: implement without memset
 */
void nlZeroMemory(void* buffer, unsigned long size)
{
    memset(buffer, 0, size);
}

/**
 * Offset/Address/Size: 0x188 | 0x801D27C0 | size: 0x64
 * TODO: 97.4% match - lbz/slwi instruction scheduling diff (compiler hoists load)
 */
u32 nlStringLowerHash(const char* str)
{
    unsigned long h = -1;
    while (*str)
    {
        h = h + (h << 5);
        h = h + nlToLower<unsigned char>(*(++str));
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
