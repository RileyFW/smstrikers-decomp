#include "Game/Core/mtRandom.h"

#include "types.h"

static unsigned long mt[624];
static int mti = 0x271;

/**
 * Offset/Address/Size: 0x0 | 0x801CDFB8 | size: 0x168
 */
void seedMT(unsigned long seed)
{
    mt[0] = seed;

    for (mti = 1; mti < 624; ++mti)
    {
        mt[mti] = 1812433253UL * (mt[mti - 1] ^ (mt[mti - 1] >> 30)) + mti;
    }
}
