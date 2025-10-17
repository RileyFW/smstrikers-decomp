#include "Game/Render/NPCManager.h"

// /**
//  * Offset/Address/Size: 0x68 | 0x80167338 | size: 0x28
//  */
// void nlListAddStart<ListEntry<SkinAnimatedNPC*>>(ListEntry<SkinAnimatedNPC*>**, ListEntry<SkinAnimatedNPC*>*, ListEntry<SkinAnimatedNPC*>**)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x801672D0 | size: 0x68
//  */
// void nlWalkList<ListEntry<SkinAnimatedNPC*>, ListContainerBase<SkinAnimatedNPC*, NewAdapter<ListEntry<SkinAnimatedNPC*>>>>(ListEntry<SkinAnimatedNPC*>*, ListContainerBase<SkinAnimatedNPC*, NewAdapter<ListEntry<SkinAnimatedNPC*>>>*, void (ListContainerBase<SkinAnimatedNPC*, NewAdapter<ListEntry<SkinAnimatedNPC*>>>::*)(ListEntry<SkinAnimatedNPC*>*))
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x801672AC | size: 0x24
//  */
// void ListContainerBase<SkinAnimatedNPC*, NewAdapter<ListEntry<SkinAnimatedNPC*>>>::DeleteEntry(ListEntry<SkinAnimatedNPC*>*)
// {
// }

/**
 * Offset/Address/Size: 0x8AC | 0x80166770 | size: 0xB3C
 */
NPCManager::NPCManager()
{
}

/**
 * Offset/Address/Size: 0x4D8 | 0x8016639C | size: 0x3D4
 */
NPCManager::~NPCManager()
{
}

/**
 * Offset/Address/Size: 0x47C | 0x80166340 | size: 0x5C
 */
void NPCManager::UpdateNPCs(float dt)
{
    ListEntry<SkinAnimatedNPC*>* current = mNPCList.m_Head;
    while (current != nullptr)
    {
        current->data->Update(dt);
        current = current->next;
    }
}

/**
 * Offset/Address/Size: 0x430 | 0x801662F4 | size: 0x4C
 */
void NPCManager::RenderNPCs()
{
    ListEntry<SkinAnimatedNPC*>* current = mNPCList.m_Head;
    while (current != nullptr)
    {
        current->data->Render();
        current = current->next;
    }
}

/**
 * Offset/Address/Size: 0x3D0 | 0x80166294 | size: 0x60
 */
void NPCManager::UpdateAINPCs(float dt)
{
    mpChainChomp->Update(dt);
    mpBowser->Update(dt);
}

/**
 * Offset/Address/Size: 0x0 | 0x80165EC4 | size: 0x3D0
 */
void NPCManager::CreateNPCTemplate(int, bool)
{
}
