#include "Game/AI/Fuzzy.h"

#include "Game/AI/FilteredRandom.h"

static inline float GetRandomFloat()
{
    static FilteredRandomReal randgen;
    return randgen.genrand();
}

/**
 * Offset/Address/Size: 0x1E4 | 0x8003C494 | size: 0x5C
 */
float GenerateFilteredRandom()
{
    return GetRandomFloat();
}

/**
 * Offset/Address/Size: 0xF8 | 0x8003C3A8 | size: 0xEC
 */
float RandomChance(float fChance)
{
    float result;
    float random = GetRandomFloat();
    float diff = fChance - random;
    result = 0.0f;
    if (diff > 0.0f)
    {
        float scale = 1.0f - random;
        scale = (scale >= fChance) ? fChance : scale;
        scale = (scale <= 0.5f) ? scale : 0.5f;

        result = diff / scale;
        result = (result >= 1.0f) ? 1.0f : result;
        result = (result <= 0.0f) ? 0.0f : result;
    }
    return result;
}

/**
 * Offset/Address/Size: 0x7C | 0x8003C32C | size: 0x7C
 */
float FGREATER(float f1, float f2)
{
    float diff = f1 - f2;
    float result = 0.0f;
    if (diff > 0.0f)
    {
        float scale = 1.0f - f2;
        scale = (scale >= f1) ? f1 : scale;
        scale = (scale <= 0.5f) ? scale : 0.5f;

        result = diff / scale;
        result = (result >= 1.0f) ? 1.0f : result;
        result = (result <= 0.0f) ? 0.0f : result;
    }
    return result;
}

/**
 * Offset/Address/Size: 0x0 | 0x8003C2B0 | size: 0x7C
 */
float FLESS(float f1, float f2)
{
    float diff = f2 - f1;
    float result = 0.0f;
    if (diff > 0.0f)
    {
        float scale = 1.0f - f1;
        scale = (scale >= f2) ? f2 : scale;
        scale = (scale <= 0.5f) ? scale : 0.5f;

        result = diff / scale;
        result = (result >= 1.0f) ? 1.0f : result;
        result = (result <= 0.0f) ? 0.0f : result;
    }
    return result;
}
