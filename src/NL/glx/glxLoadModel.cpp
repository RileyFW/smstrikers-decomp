#include "NL/glx/glxLoadModel.h"

static bool glIgnoreDuplicateModels;

/**
 * Offset/Address/Size: 0x0 | 0x801BFC20 | size: 0x24
 */
void glplatEndLoadModel(void*, unsigned long, unsigned long*)
{
}

/**
 * Offset/Address/Size: 0x24 | 0x801BFC44 | size: 0xA8
 */
void glplatBeginLoadModel(const char*, void (*)(void*, unsigned long, void*), void*)
{
}

/**
 * Offset/Address/Size: 0xCC | 0x801BFCEC | size: 0x104
 */
glModel* glplatLoadModel(const char* filename, unsigned long* pNumModels)
{
    return nullptr;
}

/**
 * Offset/Address/Size: 0x1D0 | 0x801BFDF0 | size: 0xA38
 */
void glxLoadModelFromMemory(char*, int, unsigned long*, bool)
{
}

/**
 * Offset/Address/Size: 0xC08 | 0x801C0828 | size: 0x2A0
 */
void glx_MakeSkinMesh(nlChunk*, glModel*)
{
}

/**
 * Offset/Address/Size: 0xEA8 | 0x801C0AC8 | size: 0x60
 */
// void nlAVLTree<unsigned long, unsigned long, DefaultKeyCompare<unsigned long>>::~nlAVLTree()
// {
// }

/**
 * Offset/Address/Size: 0xF08 | 0x801C0B28 | size: 0x8
 */
void glSetIgnoreDuplicateModels(bool ignore)
{
    glIgnoreDuplicateModels = ignore;
}

// /**
//  * Offset/Address/Size: 0x0 | 0x801C0B30 | size: 0x24
//  */
// void AVLTreeBase<unsigned long, unsigned long, NewAdapter<AVLTreeEntry<unsigned long, unsigned long>>, DefaultKeyCompare<unsigned
// long>>::DeleteEntry(AVLTreeEntry<unsigned long, unsigned long>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x24 | 0x801C0B54 | size: 0x5C
//  */
// void AVLTreeBase<unsigned long, unsigned long, NewAdapter<AVLTreeEntry<unsigned long, unsigned long>>, DefaultKeyCompare<unsigned
// long>>::~AVLTreeBase()
// {
// }

// /**
//  * Offset/Address/Size: 0x80 | 0x801C0BB0 | size: 0x58
//  */
// void AVLTreeBase<unsigned long, unsigned long, NewAdapter<AVLTreeEntry<unsigned long, unsigned long>>, DefaultKeyCompare<unsigned
// long>>::Clear()
// {
// }

// /**
//  * Offset/Address/Size: 0xD8 | 0x801C0C08 | size: 0x64
//  */
// void AVLTreeBase<unsigned long, unsigned long, NewAdapter<AVLTreeEntry<unsigned long, unsigned long>>, DefaultKeyCompare<unsigned
// long>>::DestroyTree(void (AVLTreeBase<unsigned long, unsigned long, NewAdapter<AVLTreeEntry<unsigned long, unsigned long>>,
// DefaultKeyCompare<unsigned long>>::*)(AVLTreeEntry<unsigned long, unsigned long>*))
// {
// }

// /**
//  * Offset/Address/Size: 0x13C | 0x801C0C6C | size: 0x758
//  */
// void AVLTreeBase<unsigned long, unsigned long, NewAdapter<AVLTreeEntry<unsigned long, unsigned long>>, DefaultKeyCompare<unsigned
// long>>::PostorderTraversal(AVLTreeEntry<unsigned long, unsigned long>*, void (AVLTreeBase<unsigned long, unsigned long,
// NewAdapter<AVLTreeEntry<unsigned long, unsigned long>>, DefaultKeyCompare<unsigned long>>::*)(AVLTreeEntry<unsigned long, unsigned
// long>*))
// {
// }

// /**
//  * Offset/Address/Size: 0x894 | 0x801C13C4 | size: 0x64
//  */
// void AVLTreeBase<unsigned long, unsigned long, NewAdapter<AVLTreeEntry<unsigned long, unsigned long>>, DefaultKeyCompare<unsigned
// long>>::AllocateEntry(void*, void*)
// {
// }

// /**
//  * Offset/Address/Size: 0x8F8 | 0x801C1428 | size: 0x2C
//  */
// void AVLTreeBase<unsigned long, unsigned long, NewAdapter<AVLTreeEntry<unsigned long, unsigned long>>, DefaultKeyCompare<unsigned
// long>>::CompareKey(void*, AVLTreeNode*)
// {
// }

// /**
//  * Offset/Address/Size: 0x924 | 0x801C1454 | size: 0x2C
//  */
// void AVLTreeBase<unsigned long, unsigned long, NewAdapter<AVLTreeEntry<unsigned long, unsigned long>>, DefaultKeyCompare<unsigned
// long>>::CompareNodes(AVLTreeNode*, AVLTreeNode*)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x801C1480 | size: 0x3C
//  */
// void nlRingAddEnd<BoneMapList>(BoneMapList**, BoneMapList*)
// {
// }

// /**
//  * Offset/Address/Size: 0x3C | 0x801C14BC | size: 0x2C
//  */
// void nlRingAddStart<BoneMapList>(BoneMapList**, BoneMapList*)
// {
// }
