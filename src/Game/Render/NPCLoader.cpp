#include "Game/Render/NPCLoader.h"

#include "NL/nlMemory.h"

#include "Game/Render/NPCManager.h"
#include "Game/BasicStadium.h"

NPCLoader TheNPCLoader;

/**
 * Offset/Address/Size: 0x0 | 0x80165E64 | size: 0x50
 */
bool NPCLoader::StartLoad(LoadingManager*)
{
    BasicStadium::GetCurrentStadium()->mpNPCManager = new (nlMalloc(0x74, 8, false)) NPCManager();
    return true;
}
