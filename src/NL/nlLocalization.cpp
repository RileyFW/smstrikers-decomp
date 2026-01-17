#include "NL/nlLocalization.h"
#include "NL/nlMemory.h"

extern void* g_pLocalization;

/**
 * Offset/Address/Size: 0x0 | 0x802107AC | size: 0x148
 */
void nlLocalization::Load(nlLocalization::nlLanguage, bool)
{
}

/**
 * Offset/Address/Size: 0x148 | 0x802108F4 | size: 0x48
 */
void nlLocalization::Initialize()
{
    void* ptr = nlMalloc(16, 8, false);
    if (ptr != 0) {
        ((unsigned long*)ptr)[0] = 0;
        ((unsigned long*)ptr)[1] = 0;
        ((unsigned long*)ptr)[2] = 0;
    }
    g_pLocalization = ptr;
}
