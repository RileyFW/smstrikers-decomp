#include "ScriptTuning.h"

/**
 * Offset/Address/Size: 0xC0 | 0x800855F0 | size: 0xC8
 */
void Config::Get<float>(const char*, float)
{
}

/**
 * Offset/Address/Size: 0x0 | 0x80085530 | size: 0xC0
 */
void Config::Get<int>(const char*, int)
{
}

/**
 * Offset/Address/Size: 0xBD4 | 0x800854E0 | size: 0x50
 */
FuzzyTweaks::FuzzyTweaks(const char*)
{
}

/**
 * Offset/Address/Size: 0xB74 | 0x80085480 | size: 0x60
 */
FuzzyTweaks::~FuzzyTweaks()
{
}

/**
 * Offset/Address/Size: 0x0 | 0x8008490C | size: 0xB74
 */
void FuzzyTweaks::Init()
{
}
