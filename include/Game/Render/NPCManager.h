#ifndef _NPCMANAGER_H_
#define _NPCMANAGER_H_

#include "types.h"

#include "NL/nlList.h"
#include "Game/SHierarchy.h"
#include "Game/Render/SkinAnimatedNPC.h"

// void nlListAddStart<ListEntry<SkinAnimatedNPC*>>(ListEntry<SkinAnimatedNPC*>**, ListEntry<SkinAnimatedNPC*>*, ListEntry<SkinAnimatedNPC*>**);

struct NPCTemplate
{
    /* 0x00 */ bool loaded;            // offset 0x0, size 0x1
    /* 0x04 */ s32 modelID;            // offset 0x4, size 0x4
    /* 0x08 */ cSHierarchy* hierarchy; // offset 0x8, size 0x4
}; // total size: 0xC

class cInventory;
class ChainChomp;
class Bowser;

class NPCManager
{
public:
    NPCManager();
    virtual ~NPCManager();

    void UpdateNPCs(float);
    void RenderNPCs();
    void UpdateAINPCs(float);
    void CreateNPCTemplate(int, bool);

    /* 0x04 */ cInventory* mpInventorySAnim;               // offset 0x4, size 0x4
    /* 0x08 */ cInventory* mpInventorySHierarchy;          // offset 0x8, size 0x4
    /* 0x0C */ nlListContainer<SkinAnimatedNPC*> mNPCList; // offset 0xC, size 0xC
    /* 0x18 */ ChainChomp* mpChainChomp;                   // offset 0x18, size 0x4
    /* 0x1C */ Bowser* mpBowser;                           // offset 0x1C, size 0x4
    /* 0x20 */ NPCTemplate mNPCTemplate[7];                // offset 0x20, size 0x54
}; // total size: 0x74

// class ListContainerBase<SkinAnimatedNPC*, NewAdapter<ListEntry<SkinAnimatedNPC*>>>
// {
// public:
//     void DeleteEntry(ListEntry<SkinAnimatedNPC*>*);
// };

// class nlWalkList<ListEntry<SkinAnimatedNPC*>, ListContainerBase<SkinAnimatedNPC*, NewAdapter<ListEntry<SkinAnimatedNPC*>>>>(ListEntry<SkinAnimatedNPC*>*, ListContainerBase<SkinAnimatedNPC*, NewAdapter<ListEntry<SkinAnimatedNPC*>>>*, void (ListContainerBase<SkinAnimatedNPC*, NewAdapter<ListEntry<SkinAnimatedNPC*>>>
// {
// public:
//     void *)(ListEntry<SkinAnimatedNPC*>*));
// };

#endif // _NPCMANAGER_H_
