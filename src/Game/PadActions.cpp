#include "Game/PadActions.h"

#include "NL/platpad.h"
#include "NL/nlConfig.h"

#include "NL/nlMemory.h"

#include "Game/PadMonkey.h"
#include "NL/globalpad.h"

extern bool g_bEnableGamecubePadMonkey;

s32 g_pPadRemapArray[40] = {
    0x00000020, 0x00000040, 0x00000008, 0x00000004, 0x00000004, 0x00000040, 0x00000020, 0x00000100,
    0x00000010, 0x00000100, 0x00000200, 0x00000001, 0x00000002, 0x00000008, 0x00000004, 0x00000100,
    0x00000200, 0x00000400, 0x00000800, 0x00001000, 0x00000020, 0x00000040, 0x00000400, 0x00000010,
    0x00000800, 0x00000200, 0x00000100, 0x00000100, 0x00000200, 0x00000800, 0x00000800, 0x00000800,
    0x00000020, 0x00001000, 0x00000010, 0x00000010, 0x00001000, 0x00001000
};

// /**
//  * Offset/Address/Size: 0x128 | 0x80193720 | size: 0xD74
//  */
// void FormatImpl<BasicString<char, Detail::TempStringAllocator>>::operator%<int>(const int&)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x801935F8 | size: 0x128
//  */
// void Format<BasicString<char, Detail::TempStringAllocator>, int, int>(const BasicString<char, Detail::TempStringAllocator>&, const int&, const int&)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x801935B0 | size: 0x48
//  */
// cGlobalPad::~cGlobalPad()
// {
// }

/**
 * Offset/Address/Size: 0x10F8 | 0x80193418 | size: 0x198
 */
void InitPads()
{
    g_bEnableGamecubePadMonkey = GetConfigBool(Config::Global(), "enable_pad_monkey", false);

    InitPlatPad();

    if (!g_bEnableGamecubePadMonkey)
    {
        for (int i = 0; i < 4; i++)
        {
            cPadManager::m_aPads[i] = new (nlMalloc(0x1C, 8, false)) cPlatPad(i);
        }
    }
    else
    {
        for (int i = 0; i < 4; i++)
        {
            cPadManager::m_aPads[i] = new (nlMalloc(0xD8, 8, false)) PadMonkey(i);
        }
    }

    UpdateMonkeyState(0);
    cPadManager::m_pRemapArray = g_pPadRemapArray;
    if (g_bEnableGamecubePadMonkey)
    {
        cPlatPad::m_bDisableRumble = true;
    }
}

/**
 * Offset/Address/Size: 0x0 | 0x80192320 | size: 0x10F8
 */
void UpdateMonkeyState(int)
{
    FORCE_DONT_INLINE;
}
