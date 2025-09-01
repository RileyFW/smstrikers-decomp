#include "Game/Effects/EffectsGroup.h"

// /**
//  * Offset/Address/Size: 0x60 | 0x801F5120 | size: 0x38
//  */
// void nlRingCountElements<DLListEntry<UserEffectSpec*>>(DLListEntry<UserEffectSpec*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x801F50C0 | size: 0x60
//  */
// void nlWalkRing<DLListEntry<UserEffectSpec*>, DLListContainerBase<UserEffectSpec*, NewAdapter<DLListEntry<UserEffectSpec*>>>>(DLListEntry<UserEffectSpec*>*, DLListContainerBase<UserEffectSpec*, NewAdapter<DLListEntry<UserEffectSpec*>>>*, void (DLListContainerBase<UserEffectSpec*, NewAdapter<DLListEntry<UserEffectSpec*>>>::*)(DLListEntry<UserEffectSpec*>*))
// {
// }

// /**
//  * Offset/Address/Size: 0xD0 | 0x801F5088 | size: 0x38
//  */
// void nlDLRingAddStart<DLListEntry<UserEffectSpec*>>(DLListEntry<UserEffectSpec*>**, DLListEntry<UserEffectSpec*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x94 | 0x801F504C | size: 0x3C
//  */
// void nlDLRingAddEnd<DLListEntry<UserEffectSpec*>>(DLListEntry<UserEffectSpec*>**, DLListEntry<UserEffectSpec*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x7C | 0x801F5034 | size: 0x18
//  */
// void nlDLRingGetStart<DLListEntry<UserEffectSpec*>>(DLListEntry<UserEffectSpec*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x5C | 0x801F5014 | size: 0x20
//  */
// void nlDLRingIsEnd<DLListEntry<UserEffectSpec*>>(DLListEntry<UserEffectSpec*>*, DLListEntry<UserEffectSpec*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x3C | 0x801F4FF4 | size: 0x20
//  */
// void nlDLRingCountElements<DLListEntry<UserEffectSpec*>>(DLListEntry<UserEffectSpec*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x801F4FB8 | size: 0x3C
//  */
// void nlWalkDLRing<DLListEntry<UserEffectSpec*>, DLListContainerBase<UserEffectSpec*, NewAdapter<DLListEntry<UserEffectSpec*>>>>(DLListEntry<UserEffectSpec*>*, DLListContainerBase<UserEffectSpec*, NewAdapter<DLListEntry<UserEffectSpec*>>>*, void (DLListContainerBase<UserEffectSpec*, NewAdapter<DLListEntry<UserEffectSpec*>>>::*)(DLListEntry<UserEffectSpec*>*))
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x801F4F94 | size: 0x24
//  */
// void DLListContainerBase<UserEffectSpec*, NewAdapter<DLListEntry<UserEffectSpec*>>>::DeleteEntry(DLListEntry<UserEffectSpec*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x24 | 0x801F4F70 | size: 0x24
//  */
// void NewAdapter<AVLTreeEntry<unsigned long, EffectsTerrainSpec*>>::Delete(AVLTreeEntry<unsigned long, EffectsTerrainSpec*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x801F4F4C | size: 0x24
//  */
// void NewAdapter<AVLTreeEntry<unsigned long, EffectsGroup*>>::Delete(AVLTreeEntry<unsigned long, EffectsGroup*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x14A0 | 0x801F4EE8 | size: 0x64
//  */
// void AVLTreeBase<unsigned long, EffectsGroup*, NewAdapter<AVLTreeEntry<unsigned long, EffectsGroup*>>, DefaultKeyCompare<unsigned long>>::AllocateEntry(void*, void*)
// {
// }

// /**
//  * Offset/Address/Size: 0x143C | 0x801F4E84 | size: 0x64
//  */
// void AVLTreeBase<unsigned long, EffectsTerrainSpec*, NewAdapter<AVLTreeEntry<unsigned long, EffectsTerrainSpec*>>, DefaultKeyCompare<unsigned long>>::AllocateEntry(void*, void*)
// {
// }

// /**
//  * Offset/Address/Size: 0x1410 | 0x801F4E58 | size: 0x2C
//  */
// void AVLTreeBase<unsigned long, EffectsTerrainSpec*, NewAdapter<AVLTreeEntry<unsigned long, EffectsTerrainSpec*>>, DefaultKeyCompare<unsigned long>>::CompareKey(void*, AVLTreeNode*)
// {
// }

// /**
//  * Offset/Address/Size: 0x13E4 | 0x801F4E2C | size: 0x2C
//  */
// void AVLTreeBase<unsigned long, EffectsTerrainSpec*, NewAdapter<AVLTreeEntry<unsigned long, EffectsTerrainSpec*>>, DefaultKeyCompare<unsigned long>>::CompareNodes(AVLTreeNode*, AVLTreeNode*)
// {
// }

// /**
//  * Offset/Address/Size: 0x13B8 | 0x801F4E00 | size: 0x2C
//  */
// void AVLTreeBase<unsigned long, EffectsGroup*, NewAdapter<AVLTreeEntry<unsigned long, EffectsGroup*>>, DefaultKeyCompare<unsigned long>>::CompareKey(void*, AVLTreeNode*)
// {
// }

// /**
//  * Offset/Address/Size: 0x138C | 0x801F4DD4 | size: 0x2C
//  */
// void AVLTreeBase<unsigned long, EffectsGroup*, NewAdapter<AVLTreeEntry<unsigned long, EffectsGroup*>>, DefaultKeyCompare<unsigned long>>::CompareNodes(AVLTreeNode*, AVLTreeNode*)
// {
// }

// /**
//  * Offset/Address/Size: 0x1334 | 0x801F4D7C | size: 0x58
//  */
// void AVLTreeBase<unsigned long, EffectsGroup*, NewAdapter<AVLTreeEntry<unsigned long, EffectsGroup*>>, DefaultKeyCompare<unsigned long>>::DeleteValues()
// {
// }

// /**
//  * Offset/Address/Size: 0x132C | 0x801F4D74 | size: 0x8
//  */
// void AVLTreeBase<unsigned long, EffectsGroup*, NewAdapter<AVLTreeEntry<unsigned long, EffectsGroup*>>, DefaultKeyCompare<unsigned long>>::CastUp(AVLTreeNode*) const
// {
// }

// /**
//  * Offset/Address/Size: 0xBD4 | 0x801F461C | size: 0x758
//  */
// void AVLTreeBase<unsigned long, EffectsGroup*, NewAdapter<AVLTreeEntry<unsigned long, EffectsGroup*>>, DefaultKeyCompare<unsigned long>>::PostorderTraversal(AVLTreeEntry<unsigned long, EffectsGroup*>*, void (AVLTreeBase<unsigned long, EffectsGroup*, NewAdapter<AVLTreeEntry<unsigned long, EffectsGroup*>>, DefaultKeyCompare<unsigned long>>::*)(AVLTreeEntry<unsigned long, EffectsGroup*>*))
// {
// }

// /**
//  * Offset/Address/Size: 0xB70 | 0x801F45B8 | size: 0x64
//  */
// void AVLTreeBase<unsigned long, EffectsGroup*, NewAdapter<AVLTreeEntry<unsigned long, EffectsGroup*>>, DefaultKeyCompare<unsigned long>>::DestroyTree(void (AVLTreeBase<unsigned long, EffectsGroup*, NewAdapter<AVLTreeEntry<unsigned long, EffectsGroup*>>, DefaultKeyCompare<unsigned long>>::*)(AVLTreeEntry<unsigned long, EffectsGroup*>*))
// {
// }

// /**
//  * Offset/Address/Size: 0xB18 | 0x801F4560 | size: 0x58
//  */
// void AVLTreeBase<unsigned long, EffectsGroup*, NewAdapter<AVLTreeEntry<unsigned long, EffectsGroup*>>, DefaultKeyCompare<unsigned long>>::Clear()
// {
// }

// /**
//  * Offset/Address/Size: 0xABC | 0x801F4504 | size: 0x5C
//  */
// void AVLTreeBase<unsigned long, EffectsGroup*, NewAdapter<AVLTreeEntry<unsigned long, EffectsGroup*>>, DefaultKeyCompare<unsigned long>>::~AVLTreeBase()
// {
// }

// /**
//  * Offset/Address/Size: 0xA5C | 0x801F44A4 | size: 0x60
//  */
// void nlAVLTree<unsigned long, EffectsGroup*, DefaultKeyCompare<unsigned long>>::~nlAVLTree()
// {
// }

// /**
//  * Offset/Address/Size: 0xA04 | 0x801F444C | size: 0x58
//  */
// void AVLTreeBase<unsigned long, EffectsTerrainSpec*, NewAdapter<AVLTreeEntry<unsigned long, EffectsTerrainSpec*>>, DefaultKeyCompare<unsigned long>>::DeleteValues()
// {
// }

// /**
//  * Offset/Address/Size: 0x9FC | 0x801F4444 | size: 0x8
//  */
// void AVLTreeBase<unsigned long, EffectsTerrainSpec*, NewAdapter<AVLTreeEntry<unsigned long, EffectsTerrainSpec*>>, DefaultKeyCompare<unsigned long>>::CastUp(AVLTreeNode*) const
// {
// }

// /**
//  * Offset/Address/Size: 0x2A4 | 0x801F3CEC | size: 0x758
//  */
// void AVLTreeBase<unsigned long, EffectsTerrainSpec*, NewAdapter<AVLTreeEntry<unsigned long, EffectsTerrainSpec*>>, DefaultKeyCompare<unsigned long>>::PostorderTraversal(AVLTreeEntry<unsigned long, EffectsTerrainSpec*>*, void (AVLTreeBase<unsigned long, EffectsTerrainSpec*, NewAdapter<AVLTreeEntry<unsigned long, EffectsTerrainSpec*>>, DefaultKeyCompare<unsigned long>>::*)(AVLTreeEntry<unsigned long, EffectsTerrainSpec*>*))
// {
// }

// /**
//  * Offset/Address/Size: 0x240 | 0x801F3C88 | size: 0x64
//  */
// void AVLTreeBase<unsigned long, EffectsTerrainSpec*, NewAdapter<AVLTreeEntry<unsigned long, EffectsTerrainSpec*>>, DefaultKeyCompare<unsigned long>>::DestroyTree(void (AVLTreeBase<unsigned long, EffectsTerrainSpec*, NewAdapter<AVLTreeEntry<unsigned long, EffectsTerrainSpec*>>, DefaultKeyCompare<unsigned long>>::*)(AVLTreeEntry<unsigned long, EffectsTerrainSpec*>*))
// {
// }

// /**
//  * Offset/Address/Size: 0x1E8 | 0x801F3C30 | size: 0x58
//  */
// void AVLTreeBase<unsigned long, EffectsTerrainSpec*, NewAdapter<AVLTreeEntry<unsigned long, EffectsTerrainSpec*>>, DefaultKeyCompare<unsigned long>>::Clear()
// {
// }

// /**
//  * Offset/Address/Size: 0x18C | 0x801F3BD4 | size: 0x5C
//  */
// void AVLTreeBase<unsigned long, EffectsTerrainSpec*, NewAdapter<AVLTreeEntry<unsigned long, EffectsTerrainSpec*>>, DefaultKeyCompare<unsigned long>>::~AVLTreeBase()
// {
// }

// /**
//  * Offset/Address/Size: 0x168 | 0x801F3BB0 | size: 0x24
//  */
// void AVLTreeBase<unsigned long, EffectsGroup*, NewAdapter<AVLTreeEntry<unsigned long, EffectsGroup*>>, DefaultKeyCompare<unsigned long>>::DeleteEntry(AVLTreeEntry<unsigned long, EffectsGroup*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x144 | 0x801F3B8C | size: 0x24
//  */
// void AVLTreeBase<unsigned long, EffectsTerrainSpec*, NewAdapter<AVLTreeEntry<unsigned long, EffectsTerrainSpec*>>, DefaultKeyCompare<unsigned long>>::DeleteEntry(AVLTreeEntry<unsigned long, EffectsTerrainSpec*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0xD0 | 0x801F3B18 | size: 0x74
//  */
// void AVLTreeBase<unsigned long, EffectsTerrainSpec*, NewAdapter<AVLTreeEntry<unsigned long, EffectsTerrainSpec*>>, DefaultKeyCompare<unsigned long>>::DeleteValue(AVLTreeEntry<unsigned long, EffectsTerrainSpec*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x801F3A48 | size: 0xD0
//  */
// void AVLTreeBase<unsigned long, EffectsGroup*, NewAdapter<AVLTreeEntry<unsigned long, EffectsGroup*>>, DefaultKeyCompare<unsigned long>>::DeleteValue(AVLTreeEntry<unsigned long, EffectsGroup*>*)
// {
// }

/**
 * Offset/Address/Size: 0xFC8 | 0x801F3A10 | size: 0x38
 */
bool EffectsTerrainSpec::HasTerrain(unsigned long) const
{
    return false;
}

/**
 * Offset/Address/Size: 0xF70 | 0x801F39B8 | size: 0x58
 */
EffectsSpec::EffectsSpec()
{
}

/**
 * Offset/Address/Size: 0xA30 | 0x801F3478 | size: 0x540
 */
bool parse_spec(SimpleParser*, EffectsSpec&)
{
    return false;
}

/**
 * Offset/Address/Size: 0x80C | 0x801F3254 | size: 0x224
 */
EffectsTerrainSpec* parse_terrain_spec(SimpleParser*)
{
    return nullptr;
}

/**
 * Offset/Address/Size: 0x338 | 0x801F2D80 | size: 0x4D4
 */
EffectsGroup* parse_group(SimpleParser*)
{
    return nullptr;
}

/**
 * Offset/Address/Size: 0x30C | 0x801F2D54 | size: 0x2C
 */
void fxLoadGroupBundle(const char*)
{
}

/**
 * Offset/Address/Size: 0x178 | 0x801F2BC0 | size: 0x194
 */
void fxLoadGroupBundle(void*, unsigned long)
{
}

/**
 * Offset/Address/Size: 0x118 | 0x801F2B60 | size: 0x60
 */
// void nlAVLTree<unsigned long, EffectsTerrainSpec*, DefaultKeyCompare<unsigned long>>::~nlAVLTree()
// {
// }

/**
 * Offset/Address/Size: 0xA4 | 0x801F2AEC | size: 0x74
 */
void fxUnloadGroups()
{
}

/**
 * Offset/Address/Size: 0x0 | 0x801F2A48 | size: 0xA4
 */
EffectsGroup* fxGetGroup(const char*)
{
    return nullptr;
}
