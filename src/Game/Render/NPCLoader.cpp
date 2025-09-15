#include "Game/Render/NPCLoader.h"

#include "NL/nlMemory.h"

#include "Game/Render/NPCManager.h"
#include "Game/BasicStadium.h"

/**
 * Offset/Address/Size: 0x0 | 0x80165E64 | size: 0x50
 */
bool NPCLoader::StartLoad(LoadingManager*)
{
    void* this_00 = nlMalloc(0x74, 8, false);
    if (this_00 != NULL)
    {
        this_00 = new (this_00) NPCManager();
    }
    BasicStadium::GetCurrentStadium()->mpNPCManager = (NPCManager*)this_00;

    return true;
}
