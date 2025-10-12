#include "NL/nlAVLTree.h"

#include "types.h"

/**
 * Offset/Address/Size: 0x0 | 0x801CE120 | size: 0x490
 */
AVLTreeNode* AVLTreeUntemplated::RemoveAVLNode(AVLTreeNode** root, void* key, unsigned int height)
{
    return nullptr;
}

/**
 * Offset/Address/Size: 0x490 | 0x801CE5B0 | size: 0x398
 */
u32 AVLTreeUntemplated::AddAVLNode(AVLTreeNode** rootNode, void* key, void* value, AVLTreeNode** existingNode, unsigned int height)
{
    return 0; // Add proper implementation or return 0 for now
}
