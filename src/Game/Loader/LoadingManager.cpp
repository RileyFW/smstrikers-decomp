#include "Game/Loader/LoadingManager.h"

/**
 * Offset/Address/Size: 0x338 | 0x801E855C | size: 0x70
 */
LoadingManager::LoadingManager(unsigned int maxEntries)
{
}

/**
 * Offset/Address/Size: 0x32C | 0x801E8550 | size: 0xC
 */
const char* LoadingManager::GetName()
{
    return "LoadingManager";
}

/**
 * Offset/Address/Size: 0xE0 | 0x801E8304 | size: 0x24C
 */
void LoadingManager::Run(float dt)
{
}

/**
 * Offset/Address/Size: 0x0 | 0x801E8224 | size: 0xE0
 */
void LoadingManager::QueueLoader(Loader* loader)
{
}
