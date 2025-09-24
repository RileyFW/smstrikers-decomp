#include "Game/Render/depthoffield.h"

#include "NL/gl/glState.h"

DepthOfFieldManager DepthOfFieldManager::instance;
u32 DOFTexture = glGetTexture("target/dof");

/**
 * Offset/Address/Size: 0x208 | 0x80163794 | size: 0x4
 */
void DepthOfFieldManager::Initialize()
{
    // EMPTY
}

/**
 * Offset/Address/Size: 0x1FC | 0x80163788 | size: 0xC
 */
void DepthOfFieldManager::TurnOn()
{
    m_bOn = true;
}

/**
 * Offset/Address/Size: 0x1F0 | 0x8016377C | size: 0xC
 */
void DepthOfFieldManager::TurnOff()
{
    m_bOn = false;
}

/**
 * Offset/Address/Size: 0x0 | 0x8016358C | size: 0x1F0
 */
void DepthOfFieldManager::Update()
{
}
