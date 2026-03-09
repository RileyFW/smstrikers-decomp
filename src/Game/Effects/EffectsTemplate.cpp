#include "Game/Effects/EffectsTemplate.h"
#include "Game/Effects/EmissionController.h"
#include "Game/Effects/EmissionManager.h"
#include "NL/nlAVLTree.h"
#include "NL/nlMath.h"
#include "NL/nlString.h"
#include "Game/Sys/simpleparser.h"

static nlAVLTree<unsigned long, EffectsTemplate*, DefaultKeyCompare<unsigned long> >* pTemplateMap = nullptr;
static unsigned int uSeed = 0x9184EB0C;

// /**
//  * Offset/Address/Size: 0x0 | 0x801F29E8 | size: 0x60
//  */
// void nlWalkRing<DLListEntry<ColourKey>, DLListContainerBase<ColourKey, NewAdapter<DLListEntry<ColourKey> > > >(DLListEntry<ColourKey>*, DLListContainerBase<ColourKey, NewAdapter<DLListEntry<ColourKey> > >*, void (DLListContainerBase<ColourKey, NewAdapter<DLListEntry<ColourKey> > >::*)(DLListEntry<ColourKey>*))
// {
// }

// /**
//  * Offset/Address/Size: 0xB0 | 0x801F29B0 | size: 0x38
//  */
// void nlDLRingAddStart<DLListEntry<ColourKey> >(DLListEntry<ColourKey>**, DLListEntry<ColourKey>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x74 | 0x801F2974 | size: 0x3C
//  */
// void nlDLRingAddEnd<DLListEntry<ColourKey> >(DLListEntry<ColourKey>**, DLListEntry<ColourKey>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x5C | 0x801F295C | size: 0x18
//  */
// void nlDLRingGetStart<DLListEntry<ColourKey> >(DLListEntry<ColourKey>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x3C | 0x801F293C | size: 0x20
//  */
// void nlDLRingIsEnd<DLListEntry<ColourKey> >(DLListEntry<ColourKey>*, DLListEntry<ColourKey>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x801F2900 | size: 0x3C
//  */
// void nlWalkDLRing<DLListEntry<ColourKey>, DLListContainerBase<ColourKey, NewAdapter<DLListEntry<ColourKey> > > >(DLListEntry<ColourKey>*, DLListContainerBase<ColourKey, NewAdapter<DLListEntry<ColourKey> > >*, void (DLListContainerBase<ColourKey, NewAdapter<DLListEntry<ColourKey> > >::*)(DLListEntry<ColourKey>*))
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x801F28DC | size: 0x24
//  */
// void DLListContainerBase<ColourKey, NewAdapter<DLListEntry<ColourKey> > >::DeleteEntry(DLListEntry<ColourKey>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x801F28B8 | size: 0x24
//  */
// void NewAdapter<AVLTreeEntry<unsigned long, EffectsTemplate*> >::Delete(AVLTreeEntry<unsigned long, EffectsTemplate*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x994 | 0x801F2854 | size: 0x64
//  */
// void AVLTreeBase<unsigned long, EffectsTemplate*, NewAdapter<AVLTreeEntry<unsigned long, EffectsTemplate*> >, DefaultKeyCompare<unsigned long> >::AllocateEntry(void*, void*)
// {
// }

// /**
//  * Offset/Address/Size: 0x968 | 0x801F2828 | size: 0x2C
//  */
// void AVLTreeBase<unsigned long, EffectsTemplate*, NewAdapter<AVLTreeEntry<unsigned long, EffectsTemplate*> >, DefaultKeyCompare<unsigned long> >::CompareKey(void*, AVLTreeNode*)
// {
// }

// /**
//  * Offset/Address/Size: 0x93C | 0x801F27FC | size: 0x2C
//  */
// void AVLTreeBase<unsigned long, EffectsTemplate*, NewAdapter<AVLTreeEntry<unsigned long, EffectsTemplate*> >, DefaultKeyCompare<unsigned long> >::CompareNodes(AVLTreeNode*, AVLTreeNode*)
// {
// }

// /**
//  * Offset/Address/Size: 0x8E4 | 0x801F27A4 | size: 0x58
//  */
// void AVLTreeBase<unsigned long, EffectsTemplate*, NewAdapter<AVLTreeEntry<unsigned long, EffectsTemplate*> >, DefaultKeyCompare<unsigned long> >::DeleteValues()
// {
// }

// /**
//  * Offset/Address/Size: 0x8DC | 0x801F279C | size: 0x8
//  */
// void AVLTreeBase<unsigned long, EffectsTemplate*, NewAdapter<AVLTreeEntry<unsigned long, EffectsTemplate*> >, DefaultKeyCompare<unsigned long> >::CastUp(AVLTreeNode*) const
// {
// }

// /**
//  * Offset/Address/Size: 0x184 | 0x801F2044 | size: 0x758
//  */
// void AVLTreeBase<unsigned long, EffectsTemplate*, NewAdapter<AVLTreeEntry<unsigned long, EffectsTemplate*> >, DefaultKeyCompare<unsigned long> >::PostorderTraversal(AVLTreeEntry<unsigned long, EffectsTemplate*>*, void (AVLTreeBase<unsigned long, EffectsTemplate*, NewAdapter<AVLTreeEntry<unsigned long, EffectsTemplate*> >, DefaultKeyCompare<unsigned long> >::*)(AVLTreeEntry<unsigned long, EffectsTemplate*>*))
// {
// }

// /**
//  * Offset/Address/Size: 0x120 | 0x801F1FE0 | size: 0x64
//  */
// void AVLTreeBase<unsigned long, EffectsTemplate*, NewAdapter<AVLTreeEntry<unsigned long, EffectsTemplate*> >, DefaultKeyCompare<unsigned long> >::DestroyTree(void (AVLTreeBase<unsigned long, EffectsTemplate*, NewAdapter<AVLTreeEntry<unsigned long, EffectsTemplate*> >, DefaultKeyCompare<unsigned long> >::*)(AVLTreeEntry<unsigned long, EffectsTemplate*>*))
// {
// }

// /**
//  * Offset/Address/Size: 0xC8 | 0x801F1F88 | size: 0x58
//  */
// void AVLTreeBase<unsigned long, EffectsTemplate*, NewAdapter<AVLTreeEntry<unsigned long, EffectsTemplate*> >, DefaultKeyCompare<unsigned long> >::Clear()
// {
// }

// /**
//  * Offset/Address/Size: 0x6C | 0x801F1F2C | size: 0x5C
//  */
// void AVLTreeBase<unsigned long, EffectsTemplate*, NewAdapter<AVLTreeEntry<unsigned long, EffectsTemplate*> >, DefaultKeyCompare<unsigned long> >::~AVLTreeBase()
// {
// }

// /**
//  * Offset/Address/Size: 0x48 | 0x801F1F08 | size: 0x24
//  */
// void AVLTreeBase<unsigned long, EffectsTemplate*, NewAdapter<AVLTreeEntry<unsigned long, EffectsTemplate*> >, DefaultKeyCompare<unsigned long> >::DeleteEntry(AVLTreeEntry<unsigned long, EffectsTemplate*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x801F1EC0 | size: 0x48
//  */
// void AVLTreeBase<unsigned long, EffectsTemplate*, NewAdapter<AVLTreeEntry<unsigned long, EffectsTemplate*> >, DefaultKeyCompare<unsigned long> >::DeleteValue(AVLTreeEntry<unsigned long, EffectsTemplate*>*)
// {
// }

/**
 * Offset/Address/Size: 0x12D8 | 0x801F1E9C | size: 0x24
 */
float RandomizedValue(float value)
{
    return nlRandomf(value, &uSeed);
}

/**
 * Offset/Address/Size: 0x1260 | 0x801F1E24 | size: 0x78
 */
float RandomizedValue(float base, float range)
{
    float randomOffset = nlRandomf(0.5f * range, &uSeed);
    unsigned int randomSign = nlRandom(0x7FFFFFFF, &uSeed);

    if (randomSign & 1)
    {
        return base + randomOffset;
    }
    else
    {
        return base - randomOffset;
    }
}

/**
 * Offset/Address/Size: 0xFD4 | 0x801F1B98 | size: 0x28C
 */
void GetColourComponent(SimpleParser*, nlColour*, int)
{
    FORCE_DONT_INLINE;
}

/**
 * Offset/Address/Size: 0x2A8 | 0x801F0E6C | size: 0xD2C
 */
EffectsTemplate* parse_template(SimpleParser*, bool)
{
    FORCE_DONT_INLINE;
    return nullptr;
}

/**
 * Offset/Address/Size: 0x27C | 0x801F0E40 | size: 0x2C
 */
bool fxLoadTemplateBundle(const char* filename)
{
    unsigned long fileSize;
    void* data = fxLoadEntireFileHigh(filename, &fileSize);
    return fxLoadTemplateBundle(data, fileSize);
}

/**
 * Offset/Address/Size: 0x13C | 0x801F0D00 | size: 0x140
 * TODO: 99.19% match - MWCC reorders begin-branch setup (`lwz r30,pTemplateMap`
 * before `mr r5,r3`) and uses `stw r3,0xc(r1)` instead of `stw r5,0xc(r1)`.
 */
bool fxLoadTemplateBundle(void* data, unsigned long size)
{
    if (data == nullptr)
    {
        return false;
    }

    pTemplateMap = new (nlMalloc(0x14, 8, false)) nlAVLTree<unsigned long, EffectsTemplate*, DefaultKeyCompare<unsigned long> >();

    SimpleParser parser;
    parser.StartParsing((char*)data, size, true);

    for (;;)
    {
        char* token = parser.NextToken(true);
        if (token == nullptr)
        {
            break;
        }

        if (nlStrCmp<char>(token, "begin") == 0)
        {
            EffectsTemplate* template_ptr;
            nlAVLTree<unsigned long, EffectsTemplate*, DefaultKeyCompare<unsigned long> >* tree;
            AVLTreeNode* existingNode;

            template_ptr = parse_template(&parser, false);
            tree = pTemplateMap;

            tree->AddAVLNode((AVLTreeNode**)&tree->m_Root, &template_ptr->m_uHashID, &template_ptr, &existingNode, tree->m_NumElements);
            if (existingNode == nullptr)
            {
                tree->m_NumElements++;
            }
        }
        else
        {
            EmissionManager::AddError("EffectsTemplate: unrecognized token '%s'\n", token);
        }
    }

    nlFree(data);
    return true;
}

/**
 * Offset/Address/Size: 0xDC | 0x801F0CA0 | size: 0x60
 */
// void nlAVLTree<unsigned long, EffectsTemplate*, DefaultKeyCompare<unsigned long> >::~nlAVLTree()
// {
// }

/**
 * Offset/Address/Size: 0x90 | 0x801F0C54 | size: 0x4C
 */
bool fxUnloadTemplates()
{
    if (pTemplateMap == nullptr)
    {
        return true;
    }

    pTemplateMap->DeleteValues();
    delete pTemplateMap;
    pTemplateMap = nullptr;
    return true;
}

/**
 * Offset/Address/Size: 0x0 | 0x801F0BC4 | size: 0x90
 */
EffectsTemplate* fxGetTemplate(unsigned long key)
{
    EffectsTemplate** resultPtr;
    AVLTreeEntry<unsigned long, EffectsTemplate*>* node;
    int cmpResult;
    bool found;

    for (node = pTemplateMap->m_Root; node != nullptr || (found = false, false);)
    {
        if (key == node->key)
        {
            cmpResult = 0;
        }
        else if (key < node->key)
        {
            cmpResult = -1;
        }
        else
        {
            cmpResult = 1;
        }

        if (cmpResult == 0)
        {
            if (&resultPtr != nullptr)
            {
                resultPtr = &node->value;
            }
            found = true;
            break;
        }
        else if (cmpResult < 0)
        {
            node = (AVLTreeEntry<unsigned long, EffectsTemplate*>*)node->node.left;
        }
        else
        {
            node = (AVLTreeEntry<unsigned long, EffectsTemplate*>*)node->node.right;
        }
    }

    if (!found)
    {
        return nullptr;
    }

    return *resultPtr;
}
