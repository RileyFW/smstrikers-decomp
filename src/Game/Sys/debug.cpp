#include "debug.h"
#include "Game/Sys/simpleparser.h"

#include "extras.h"
#include "NL/nlFileGC.h"
// #include "NL/nlPrint.h"

extern void nlPrintf(const char*, ...);

namespace tDebugPrintManager
{

const char* szChannelNames[DEBUG_CHANNEL_COUNT] = {
    "STARTUP",
    "GL",
    "GLPLAT",
    "RENDER",
    "AI",
    "CAMERA",
    "EVENT",
    "FE",
    "PHYSICS",
    "MEMORY",
    "SOUND",
    "TASKMAN",
    "LOADER",
    "MISC",
    "REPLAY",
    "NIS",
    "NET",
    "MULTISTREAM",
    "WORLD",
    "CONFIGSYS",
};

bool abChannels[DEBUG_CHANNEL_COUNT] = { true, false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false, false };

/**
 * Offset/Address/Size: 0x0 | 0x801D6770 | size: 0x54
 */
int Print(eDEBUG_CHANNEL, const char*, ...)
{
    return 0;
}

/**
 * Offset/Address/Size: 0x54 | 0x801D67C4 | size: 0xE8
 */
void Initialize()
{
    // Zero out all channels
    for (int i = 0; i < DEBUG_CHANNEL_COUNT; ++i)
        abChannels[i] = 0;

    // Parse file; if it fails, enable all
    if (ParseDebugChannelFile("PrintCfg.txt") == 0)
    {
        for (int i = 0; i < DEBUG_CHANNEL_COUNT; ++i)
        {
            abChannels[i] = 1;
        }
    }
}

/**
 * Offset/Address/Size: 0x13C | 0x801D68AC | size: 0xF8
 */
bool ParseDebugChannelFile(const char* path)
{
    SimpleParser parser;

    unsigned long size = 0;
    char* buffer = (char*)nlLoadEntireFile(path, &size, 0x20u, AllocateStart);
    if (!buffer)
    {
        nlPrintf("Failed to load file %s.  All print channels will be enabled.\n", path);
        return false;
    }

    if (parser.StartParsing(buffer, (int)size, true))
    {
        for (;;)
        {
            char* tok = parser.NextToken(true);
            if (!tok)
                break;

            // skip comment lines starting with '#'
            if (tok[0] == '#')
                continue;

            // scan list of known channel names and mark enabled
            for (int i = 0; i < DEBUG_CHANNEL_COUNT; ++i)
            {
                if (strcmpi(szChannelNames[i], tok) == 0)
                {
                    abChannels[i] = 1;
                }
            }
        }
    }

    delete[] buffer;
    return true;
}

} // namespace tDebugPrintManager
