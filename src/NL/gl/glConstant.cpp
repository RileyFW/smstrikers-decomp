#include "NL/gl/glConstant.h"
#include "NL/nlAVLTree.h"
#include "NL/nlString.h"

int level = 0;

AVLTreeBase<unsigned long, nlVector4, NewAdapter<AVLTreeEntry<unsigned long, nlVector4> >, DefaultKeyCompare<unsigned long> >* constants[16] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL };

nlVector4 vZero = { 0.0f, 0.0f, 0.0f, 0.0f };

/**
 * Offset/Address/Size: 0x0 | 0x801DF220 | size: 0x10C
 */
nlVector4 glConstantGet(const char* arg1)
{
    nlVector4* sp8;
    nlVector4* var_r4_2;
    s32 var_ctr;
    s32 var_r0_2;
    s8 var_r0;
    u32 temp_r0;
    u32 temp_r3;
    AVLTreeBase<unsigned long, nlVector4, NewAdapter<AVLTreeEntry<unsigned long, nlVector4> >, DefaultKeyCompare<unsigned long> >** var_r5;
    AVLTreeEntry<unsigned long, nlVector4>* var_r4;

    temp_r3 = nlStringHash(arg1);
    var_r5 = &constants[level];
    var_r4_2 = NULL;

    for (int i = level; i >= 0; i--)
    {
        var_r4 = (*var_r5)->m_Root;
    loop_14:
        if (var_r4 == NULL)
        {
            var_r0 = 0;
        }
        else
        {
            temp_r0 = var_r4->GetKey();
            if (temp_r3 == temp_r0)
            {
                var_r0_2 = 0;
            }
            else if (temp_r3 < temp_r0)
            {
                var_r0_2 = -1;
            }
            else
            {
                var_r0_2 = 1;
            }
            if (var_r0_2 == 0)
            {
                if (&sp8 != NULL)
                {
                    sp8 = &var_r4->GetValue();
                }
                var_r0 = 1;
            }
            else
            {
                if (var_r0_2 < 0)
                {
                    var_r4 = var_r4->m_left;
                }
                else
                {
                    var_r4 = var_r4->m_right;
                }
                goto loop_14;
            }
        }
        if (var_r0 != 0)
        {
            var_r4_2 = sp8;
        }
        else
        {
            var_r5 = (AVLTreeBase<unsigned long, nlVector4, NewAdapter<AVLTreeEntry<unsigned long, nlVector4> >, DefaultKeyCompare<unsigned long> >**)((u8*)var_r5 - 4);
        }
    }

    if (var_r4_2 == NULL)
    {
        *var_r4_2 = vZero;
    }

    return *var_r4_2;
}

/**
 * Offset/Address/Size: 0x10C | 0x801DF32C | size: 0x10C
 */
bool glConstantGet(const char* arg0, nlVector4& arg1)
{
    nlVector4* sp8;
    nlVector4* var_r5_2;
    s32 var_ctr;
    s32 var_r0_2;
    s8 var_r0;
    u32 temp_r0;
    u32 temp_r3;
    AVLTreeBase<unsigned long, nlVector4, NewAdapter<AVLTreeEntry<unsigned long, nlVector4> >, DefaultKeyCompare<unsigned long> >** var_r5;
    AVLTreeEntry<unsigned long, nlVector4>* var_r4;

    temp_r3 = nlStringHash(arg0);
    var_r5 = &constants[level];
    var_ctr = level + 1;
    if ((s32)level >= 0)
    {
    loop_1:
        var_r4 = (*var_r5)->m_Root;
    loop_14:
        if (var_r4 == NULL)
        {
            var_r0 = 0;
        }
        else
        {
            temp_r0 = var_r4->GetKey();
            if (temp_r3 == temp_r0)
            {
                var_r0_2 = 0;
            }
            else if (temp_r3 < temp_r0)
            {
                var_r0_2 = -1;
            }
            else
            {
                var_r0_2 = 1;
            }
            if (var_r0_2 == 0)
            {
                if (&sp8 != NULL)
                {
                    sp8 = &var_r4->GetValue();
                }
                var_r0 = 1;
            }
            else
            {
                if (var_r0_2 < 0)
                {
                    var_r4 = var_r4->m_left;
                }
                else
                {
                    var_r4 = var_r4->m_right;
                }
                goto loop_14;
            }
        }
        if (var_r0 != 0)
        {
            var_r5_2 = sp8;
        }
        else
        {
            var_r5 -= 4;
            var_ctr -= 1;
            if (var_ctr == 0)
            {
                goto block_19;
            }
            goto loop_1;
        }
    }
    else
    {
    block_19:
        var_r5_2 = NULL;
    }
    if (var_r5_2 == NULL)
    {
        return 0;
    }
    arg1 = *var_r5_2;
    return 1;
}

/**
 * Offset/Address/Size: 0x218 | 0x801DF438 | size: 0x14C
 */
void glConstantSet(const char* arg0, const nlVector4& arg1)
{
    nlVector4* sp8;
    nlVector4* var_r4_2;
    s32 var_ctr;
    s32 var_r0_2;
    s8 var_r0;
    u32 temp_r0;
    u32 temp_r3;
    AVLTreeBase<unsigned long, nlVector4, NewAdapter<AVLTreeEntry<unsigned long, nlVector4> >, DefaultKeyCompare<unsigned long> >** var_r5;
    AVLTreeEntry<unsigned long, nlVector4>* var_r4;

    temp_r3 = nlStringHash(arg0);
    var_r5 = &constants[level];
    var_ctr = level + 1;
    if ((s32)level >= 0)
    {
    loop_1:
        var_r4 = (*var_r5)->m_Root;
    loop_14:
        if (var_r4 == NULL)
        {
            var_r0 = 0;
        }
        else
        {
            temp_r0 = var_r4->GetKey();
            if (temp_r3 == temp_r0)
            {
                var_r0_2 = 0;
            }
            else if (temp_r3 < temp_r0)
            {
                var_r0_2 = -1;
            }
            else
            {
                var_r0_2 = 1;
            }
            if (var_r0_2 == 0)
            {
                if (&sp8 != NULL)
                {
                    sp8 = &var_r4->GetValue();
                }
                var_r0 = 1;
            }
            else
            {
                if (var_r0_2 < 0)
                {
                    var_r4 = var_r4->m_left;
                }
                else
                {
                    var_r4 = var_r4->m_right;
                }
                goto loop_14;
            }
        }
        if (var_r0 != 0)
        {
            var_r4_2 = sp8;
        }
        else
        {
            var_r5 -= 4;
            var_ctr -= 1;
            if (var_ctr == 0)
            {
                goto block_19;
            }
            goto loop_1;
        }
    }
    else
    {
    block_19:
        var_r4_2 = NULL;
    }
    if (var_r4_2 == NULL)
    {
        // Create new entry in the AVL tree
        AVLTreeNode* newNode;
        (*var_r5)->AddAVLNode(&(*var_r5)->m_root_node_0x10, &temp_r3, (void*)&arg1, &newNode, 0);
        if (newNode == NULL)
        {
            (*var_r5)->m_root_node_0x10 = (AVLTreeNode*)((u32)(*var_r5)->m_root_node_0x10 + 1);
        }
    }
    else
    {
        *var_r4_2 = arg1;
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
    s32 var_r26;
    void* temp_r3;
    for (var_r26 = 0; var_r26 < 0x10; var_r26++)
    {
        temp_r3 = nlMalloc(0x14, 8, 0);
        constants[var_r26] = (AVLTreeBase<unsigned long, nlVector4, NewAdapter<AVLTreeEntry<unsigned long, nlVector4> >, DefaultKeyCompare<unsigned long> >*)new (temp_r3) AVLTreeBase<unsigned long, nlVector4, NewAdapter<AVLTreeEntry<unsigned long, nlVector4> >, DefaultKeyCompare<unsigned long> >();
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
