#include "Game/CameraLoader.h"
#include "Game/CameraMan.h"

CameraLoader TheCameraLoader;

/**
 * Offset/Address/Size: 0x0 | 0x801A6654 | size: 0x24
 */
bool CameraLoader::StartLoad(LoadingManager*)
{
    cCameraManager::Startup();
    return true;
}
