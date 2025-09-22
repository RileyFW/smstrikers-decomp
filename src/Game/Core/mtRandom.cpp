#include "Game/Core/mtRandom.h"

#include "types.h"

static unsigned long mt[624];
static unsigned long mti = 0x271;

/**
 * Offset/Address/Size: 0x0 | 0x801CDFB8 | size: 0x168
 */
void seedMT(unsigned long seed)
{
    unsigned long i;

    mt[0] = seed;
    mti = 1;

    /* mt[i] = 1812433253 * (mt[i-1] ^ (mt[i-1] >> 30)) + i, for i=1..623 */
    for (i = 1; i < 624; ++i)
    {
        unsigned long x = mt[i - 1];
        x ^= (x >> 30);
        mt[i] = 1812433253UL * x + i;
    }

    /* assembly stores the current index into mti; ends up as 624 (0x270) */
    mti = i;
}
