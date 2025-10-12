#include "NL/gl/glConstant.h"
#include "NL/nlAVLTree.h"
#include "NL/nlString.h"

int level = 0;

// AVLTreeBase<unsigned long, nlVector4, NewAdapter<AVLTreeEntry<unsigned long, nlVector4> >, DefaultKeyCompare<unsigned long> >* constants[16] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL };
// nlAVLTree<unsigned long, nlVector4, NewAdapter<AVLTreeEntry<unsigned long, nlVector4> >, DefaultKeyCompare<unsigned long> >* constants[16] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL };
nlAVLTree<unsigned long, nlVector4, DefaultKeyCompare<unsigned long> >* constants[16] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL };

nlVector4 vZero = { 0.0f, 0.0f, 0.0f, 0.0f };

/**
 * Offset/Address/Size: 0x0 | 0x801DF220 | size: 0x10C
 */
nlVector4 glConstantGet(const char* constantName)
{
    u32 hash = nlStringHash(constantName);
    nlVector4* result = NULL;

    // Search through levels from current level down to 0
    for (int i = level; i >= 0; i--)
    {
        AVLTreeEntry<unsigned long, nlVector4>* node = constants[i]->m_Root;

        // Binary search within the AVL tree
        while (node != NULL)
        {
            if (hash == node->key)
            {
                result = &node->value;
                break;
            }
            else if (hash < node->key)
            {
                node = (AVLTreeEntry<unsigned long, nlVector4>*)node->node.left;
            }
            else
            {
                node = (AVLTreeEntry<unsigned long, nlVector4>*)node->node.right;
            }
        }

        if (result != NULL)
        {
            break; // Found the constant, exit the level loop
        }
    }

    // If not found, use the zero vector
    if (result == NULL)
    {
        result = &vZero;
    }

    return *result;
}

/**
 * Offset/Address/Size: 0x10C | 0x801DF32C | size: 0x10C
 */
bool glConstantGet(const char* constantName, nlVector4& result)
{
    u32 hash = nlStringHash(constantName);
    nlVector4* foundValue = nullptr;

    // Search through levels from current level down to 0
    for (int i = level; i >= 0; i--)
    {
        AVLTreeEntry<unsigned long, nlVector4>* node = constants[i]->m_Root;

        // Binary search within the AVL tree
        while (node != nullptr)
        {
            if (hash == node->key)
            {
                foundValue = &node->value;
                break;
            }
            else if (hash < node->key)
            {
                node = (AVLTreeEntry<unsigned long, nlVector4>*)node->node.left;
            }
            else
            {
                node = (AVLTreeEntry<unsigned long, nlVector4>*)node->node.right;
            }
        }

        if (foundValue != nullptr)
        {
            break; // Found the constant, exit the level loop
        }
    }

    // If not found, return false
    if (foundValue == nullptr)
    {
        return false;
    }

    // Copy the found value to the result parameter
    result = *foundValue;
    return true;
}

/**
 * Offset/Address/Size: 0x218 | 0x801DF438 | size: 0x14C
 */
void glConstantSet(const char* constantName, const nlVector4& value)
{
    u32 hash = nlStringHash(constantName);
    nlVector4* foundValue = nullptr;

    // Search through levels from current level down to 0
    for (int i = level; i >= 0; i--)
    {
        AVLTreeEntry<unsigned long, nlVector4>* node = constants[i]->m_Root;

        // Binary search within the AVL tree
        while (node != nullptr)
        {
            if (hash == node->key)
            {
                foundValue = &node->value;
                break;
            }
            else if (hash < node->key)
            {
                node = (AVLTreeEntry<unsigned long, nlVector4>*)node->node.left;
            }
            else
            {
                node = (AVLTreeEntry<unsigned long, nlVector4>*)node->node.right;
            }
        }

        if (foundValue != nullptr)
        {
            break; // Found the constant, exit the level loop
        }
    }

    if (foundValue == nullptr)
    {
        // Constant not found, add it to the current level's tree
        AVLTreeNode* newNode;
        constants[level]->AddAVLNode((AVLTreeNode**)&constants[level]->m_Root, &hash, (void*)&value, &newNode, 0);

        if (newNode == nullptr)
        {
            // Increment the element count
            constants[level]->m_NumElements++;
        }
    }
    else
    {
        // Constant found, update its value
        *foundValue = value;
    }
}

/**
 * Offset/Address/Size: 0x364 | 0x801DF584 | size: 0x60
 */
void gl_ConstantMarkerBackup(int arg)
{
    while (level != arg)
    {
        constants[level]->Clear();
        level--;
    }
}

/**
 * Offset/Address/Size: 0x3C4 | 0x801DF5E4 | size: 0x10
 */
void gl_ConstantMarkerAdvance()
{
    level++;
}

/**
 * Offset/Address/Size: 0x3D4 | 0x801DF5F4 | size: 0x98
 */
void gl_ConstantStartup()
{
    // for (int i = 0; i < 16; i++)
    // {
    //     constants[i] = new (nlMalloc(0x14, 8, 0)) AVLTreeBase<unsigned long, nlVector4, NewAdapter<AVLTreeEntry<unsigned long, nlVector4> >, DefaultKeyCompare<unsigned long> >();
    // }
    for (int i = 0; i < 16; i++)
    {
        constants[i] = new (nlMalloc(0x14, 8, 0)) nlAVLTree<unsigned long, nlVector4, DefaultKeyCompare<unsigned long> >();
    }
    level = 0;
}

// /*
// // Fake template specialization implementations - these were never in the original code
// // They are decompiler artifacts from template instantiation

// /**
//  * Offset/Address/Size: 0x0 | 0x801DF68C | size: 0x24
//  */
// void AVLTreeBase<unsigned long, nlVector4, NewAdapter<AVLTreeEntry<unsigned long, nlVector4>>, DefaultKeyCompare<unsigned long>>::DeleteEntry(AVLTreeEntry<unsigned long, nlVector4>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x24 | 0x801DF6B0 | size: 0x58
//  */
// void AVLTreeBase<unsigned long, nlVector4, NewAdapter<AVLTreeEntry<unsigned long, nlVector4>>, DefaultKeyCompare<unsigned long>>::Clear()
// {
// }

// /**
//  * Offset/Address/Size: 0x7C | 0x801DF708 | size: 0x64
//  */
// void AVLTreeBase<unsigned long, nlVector4, NewAdapter<AVLTreeEntry<unsigned long, nlVector4>>, DefaultKeyCompare<unsigned long>>::DestroyTree(void (AVLTreeBase<unsigned long, nlVector4, NewAdapter<AVLTreeEntry<unsigned long, nlVector4>>, DefaultKeyCompare<unsigned long>>::*)(AVLTreeEntry<unsigned long, nlVector4>*))
// {
// }

// /**
//  * Offset/Address/Size: 0xE0 | 0x801DF76C | size: 0x758
//  */
// void AVLTreeBase<unsigned long, nlVector4, NewAdapter<AVLTreeEntry<unsigned long, nlVector4>>, DefaultKeyCompare<unsigned long>>::PostorderTraversal(AVLTreeEntry<unsigned long, nlVector4>*, void (AVLTreeBase<unsigned long, nlVector4, NewAdapter<AVLTreeEntry<unsigned long, nlVector4>>, DefaultKeyCompare<unsigned long>>::*)(AVLTreeEntry<unsigned long, nlVector4>*))
// {
// }

// /**
//  * Offset/Address/Size: 0x838 | 0x801DFEC4 | size: 0x8
//  */
// void AVLTreeBase<unsigned long, nlVector4, NewAdapter<AVLTreeEntry<unsigned long, nlVector4>>, DefaultKeyCompare<unsigned long>>::CastUp(AVLTreeNode*) const
// {
// }

// /**
//  * Offset/Address/Size: 0x840 | 0x801DFECC | size: 0x2C
//  */
// void AVLTreeBase<unsigned long, nlVector4, NewAdapter<AVLTreeEntry<unsigned long, nlVector4>>, DefaultKeyCompare<unsigned long>>::CompareNodes(AVLTreeNode*, AVLTreeNode*)
// {
// }

// /**
//  * Offset/Address/Size: 0x86C | 0x801DFEF8 | size: 0x2C
//  */
// void AVLTreeBase<unsigned long, nlVector4, NewAdapter<AVLTreeEntry<unsigned long, nlVector4>>, DefaultKeyCompare<unsigned long>>::CompareKey(void*, AVLTreeNode*)
// {
// }

// /**
//  * Offset/Address/Size: 0x898 | 0x801DFF24 | size: 0x7C
//  */
// void AVLTreeBase<unsigned long, nlVector4, NewAdapter<AVLTreeEntry<unsigned long, nlVector4>>, DefaultKeyCompare<unsigned long>>::AllocateEntry(void*, void*)
// {
// }
// */
