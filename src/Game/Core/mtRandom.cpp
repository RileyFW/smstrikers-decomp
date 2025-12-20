#include "Game/Core/mtRandom.h"

#include "types.h"

static unsigned long mt[624];
static int mti = 0x271;

/**
 * Offset/Address/Size: 0x0 | 0x801CDFB8 | size: 0x168
 */
void seedMT(unsigned long seed)
{
    int i;

    mt[0] = seed;
    mti = 1;

    for (i = 1; i < 624; ++i)
    {
        mt[i] = 1812433253UL * (mt[i - 1] ^ (mt[i - 1] >> 30)) + i;
    }

    mti = i;
}
