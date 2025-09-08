#include "NL/nlMemory.h"
#include "NL/nlTask.h"

#include "Game/WorldManager.h"
#include "Game/BasicStadium.h"

World* WorldManager::s_World = NULL;

/**
 * Offset/Address/Size: 0x0 | 0x8019AC60 | size: 0x44
 */
void WorldManager::DestroyWorld()
{
    delete s_World;
    s_World = NULL;
}

/**
 * Offset/Address/Size: 0x44 | 0x8019ACA4 | size: 0x68
 */
void WorldManager::LoadWorld(const char* arg0, bool arg1)
{
    void* this_00 = nlMalloc(0x18C, 8, FALSE);
    this_00 = new (this_00) BasicStadium(arg0);
    s_World = (World*)this_00;
    s_World->Load(arg1);
}

/**
 * Offset/Address/Size: 0xAC | 0x8019AD0C | size: 0x90
 */
void WorldManager::UpdateWorld(float dt)
{
    u32 temp_r3;
    World::m_uCurrentFrameCount += 1;
    if (0.f != dt)
    {
        temp_r3 = nlTaskManager::m_pInstance->m_CurrState;
        if ((temp_r3 != 0x10U) && ((u32)(temp_r3 + 0xFFFE0000) != 0U))
        {
            s_World->Update(dt);
        }
        s_World->UpdateInReplay(dt);
    }
}

/**
 * Offset/Address/Size: 0x13C | 0x8019AD9C | size: 0x30
 */
void WorldManager::RenderWorld()
{
    s_World->Render();
}
