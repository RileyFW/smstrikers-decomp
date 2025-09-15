#ifndef _NLSTRING_H_
#define _NLSTRING_H_

#include "types.h"

#ifndef nlPrintf
extern void nlPrintf(const char*, ...);
#endif

struct nlString
{
    char* data;
    u32 length;
    u32 capacity;
    u32 refcount;
};

void nlStrToWcs(const char*, unsigned short*, unsigned long);
void nlZeroMemory(void*, unsigned long);
u32 nlStringLowerHash(const char*);
u32 nlStringHash(const char*);

template <typename CharT>
s32 nlStrLen(const CharT* str)
{
    s32 len = 0;
    while (str[len] != 0)
    {
        len++;
    }
    return len;
}

template <typename CharT>
CharT* nlStrChr(const CharT* str, CharT ch)
{
    // if (!str) return nullptr;
    while (*str != static_cast<CharT>(0))
    {
        if (*str == ch)
            return const_cast<CharT*>(str);
        ++str;
    }
    return nullptr;
}

/**
 * Offset/Address/Size: 0x0 | 0x801514FC | size: 0x48
 * CrowdMood: void nlStrNCmp<char>(const char*, const char*, unsigned long)
 */
template <typename CharT>
int nlStrNCmp(const CharT* str1, const CharT* str2, unsigned long len)
{
    CharT cVar1;
    CharT cVar2;

    while (true)
    {
        len -= 1;
        cVar1 = *str1;
        cVar2 = *str2;
        str1++;
        str2++;
        if (len == 0)
            break;
        if (((cVar1 == '\0') || (cVar2 == '\0')) || (cVar1 != cVar2))
            break;
    }
    return (int)cVar1 - (int)cVar2;
}

/**
 * Offset/Address/Size: 0x0 | 0x801D2854 | size: 0x20
 * void nlToLower<unsigned char>(unsigned char)
 */

// Single character version (current implementation)
template <typename CharT>
CharT nlToLower(CharT c)
{
    if (((u8)c >= 0x41) && ((u8)c <= 0x5A))
    {
        c = (CharT)((u8)c | 0x20);
    }
    return c;
}

// String version (new addition)
template <typename CharT>
CharT nlToLower(CharT* str)
{
    while (*str)
    {
        *str = nlToLower<CharT>(*str);
        str++;
    }
}

/**
 * Offset/Address/Size: 0x0 | 0x8000DEFC | size: 0x40
 * Ball: void nlStrNCpy<char>(char*, const char*, unsigned long)
 */
template <typename CharT>
void nlStrNCpy(CharT* str1, const CharT* str2, unsigned long len)
// void nlStrNCpy<c>__FPcPCcUl(u8 *arg0, u8 *arg1, u32 arg2)
{
    //     s32 temp_cr0_eq;
    //     u32 var_r8;
    //     CharT *var_r4;
    //     CharT *var_r6;
    //     CharT temp_r7;

    //     var_r4 = str2;
    //     var_r8 = len;
    //     var_r6 = str1;
    // loop_2:
    //     temp_cr0_eq = var_r8 == 0U;
    //     var_r8 -= 1;
    //     if (temp_cr0_eq == 0) {
    //         temp_r7 = *var_r4;
    //         *var_r6 = temp_r7;
    //         if ((s8) temp_r7 != 0) {
    //             var_r6 += 1;
    //             var_r4 += 1;
    //             goto loop_2;
    //         }
    //     }
    //     *(str1 + len - 1) = 0;

    bool bVar1;
    CharT cVar2;
    CharT* pcVar3;
    int iVar4;

    pcVar3 = str1;
    iVar4 = len;
    while (true)
    {
        bVar1 = iVar4 == 0;
        iVar4 = iVar4 + -1;
        if (bVar1)
            break;
        cVar2 = *str2;
        *pcVar3 = cVar2;
        if (cVar2 == '\0')
            break;
        pcVar3 = pcVar3 + 1;
        str2 = str2 + 1;
    }
    str1[len + -1] = '\0';
    return;
}

/**
 * Offset/Address/Size: 0x0 | 0x8000DEFC | size: 0x40
 * void nlStrNCat<char>(char*, const char*, const char*, unsigned long)
 */
template <typename CharT>
void nlStrNCat(CharT* dest, const CharT* src1, const CharT* src2, unsigned long maxLen)
// void nlStrNCat<c>__FPcPCcPCcUl(u8 *arg0, u8 *arg1, u8 *arg2, u32 arg3)
{
    unsigned long count = 0;
    CharT* destPtr = dest;
    const CharT* src1Ptr = src1;
    const CharT* src2Ptr = src2;
    CharT* destWritePtr;
    CharT tempChar;

    // Copy characters from src1
    while (*src1Ptr != static_cast<CharT>(0))
    {
        tempChar = *src1Ptr;
        count++;
        src1Ptr++;
        *destPtr = tempChar;
        destPtr++;
        if (count >= maxLen)
        {
            dest[maxLen - 1] = static_cast<CharT>(0);
            return;
        }
    }

    // Copy characters from src2
    destWritePtr = &dest[count];
    while (*src2Ptr != static_cast<CharT>(0))
    {
        tempChar = *src2Ptr;
        count++;
        src2Ptr++;
        *destWritePtr = tempChar;
        destWritePtr++;
        if (count >= maxLen)
        {
            dest[maxLen - 1] = static_cast<CharT>(0);
            return;
        }
    }

    // Null terminate
    dest[count] = static_cast<CharT>(0);
}

#endif // _NLSTRING_H_
