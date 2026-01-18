#include "NL/nlPrint.h"

#include "printf.h"

/**
 * Offset/Address/Size: 0x0 | 0x801D22F8 | size: 0x48
 */
int nlVSNPrintf(char* s, unsigned long n, const char* format, va_list arg)
{
    return vsnprintf(s, n, format, arg);
}

/**
 * Offset/Address/Size: 0x48 | 0x801D2340 | size: 0xB8
 * TODO: 99.78% match - r4/r3 register diff in final pointer calculation
 */
void nlSNPrintf(char* buffer, unsigned long size, const char* format, ...)
{
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, size - 1, format, args);
    va_end(args);
    buffer[size - 1] = '\0';
}
