#include "Game/Effects/EffectsGroup.h"
#include "Game/Effects/EmissionController.h"
#include "Game/Effects/EmissionManager.h"
#include "NL/nlAVLTree.h"
#include "NL/nlMain.h"
#include "NL/nlString.h"

nlAVLTree<unsigned long, EffectsGroup*, DefaultKeyCompare<unsigned long> >* pGroupMap = nullptr;
nlAVLTree<unsigned long, EffectsTerrainSpec*, DefaultKeyCompare<unsigned long> >* pTerrainSpecMap = nullptr;

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
 * TODO: 98.6% match - r3/r5 register swap for pTerrainIDs pointer (leaf function register allocation artifact)
 */
bool EffectsTerrainSpec::HasTerrain(unsigned long terrainID) const
{
    u32 count = m_uNumTerrains;
    u32* pTerrainIDs = m_pTerrainIDs;

    for (u32 i = 0; i < count; i++)
    {
        if (pTerrainIDs[i] == terrainID)
        {
            return true;
        }
    }

    return false;
}

/**
 * Offset/Address/Size: 0xF70 | 0x801F39B8 | size: 0x58
 */
EffectsSpec::EffectsSpec()
{
    m_uHashID = 0;
    m_pTemplate = nullptr;
    m_eAttach = FXBind_Emitter;
    m_uJointID = 0;
    m_fDelay = 0.0f;
    m_uLayer = 0;
    m_eJointBinding = JB_Normal;
    m_fJointVelocity = 0.0f;
    m_bInFront = false;
    m_bGround = false;
    m_bLight = false;
    m_fOffset = 0.0f;
    m_pTerrainSpec = nullptr;
    m_fLingerStart = 1.0f;
    m_fLingerEnd = 1.0f;
    m_vLocalOffset.f.x = 0.0f;
    m_vLocalOffset.f.y = 0.0f;
    m_vLocalOffset.f.z = 0.0f;
}

/**
 * Offset/Address/Size: 0xA30 | 0x801F3478 | size: 0x540
 */
bool parse_spec(SimpleParser*, EffectsSpec&)
{
    FORCE_DONT_INLINE;
    return false;
}

/**
 * Offset/Address/Size: 0x80C | 0x801F3254 | size: 0x224
 * TODO: 86.9% match - MWCC strength reduction converts base+offset to pointer walk (stw vs target stwx),
 * cascading into: CSE of numTerrains*4 into r30, hashID r0->r4, found r0->r28 + extra node==nullptr check,
 * existingSpec r30->r28, stack offset shift. Root cause: -inline deferred (original) vs -inline auto (decomp.me).
 */
EffectsTerrainSpec* parse_terrain_spec(SimpleParser* parser)
{
    unsigned long terrainIDs[256];
    unsigned long offset = 0;
    unsigned long numTerrains = 0;
    SimpleParser* p = parser;
    unsigned long* terrainBase = terrainIDs;

    while (true)
    {
        char* token = p->NextTokenOnLine(true);
        if (token == nullptr)
        {
            break;
        }

        *(unsigned long*)((char*)terrainBase + offset) = nlStringLowerHash(token);
        numTerrains++;
        offset += 4;
    }

    EffectsTerrainSpec* pSpec = (EffectsTerrainSpec*)nlMalloc(8, 8, false);
    if (pSpec != nullptr)
    {
        pSpec->m_pTerrainIDs = nullptr;
        pSpec->m_uNumTerrains = 0;
    }

    pSpec->m_uNumTerrains = numTerrains;
    pSpec->m_pTerrainIDs = (unsigned long*)nlMalloc(numTerrains * 4, 8, false);
    memcpy(pSpec->m_pTerrainIDs, terrainIDs, numTerrains * 4);

    RunningChecksum checksum;
    checksum.ChecksumInt(pSpec->m_uNumTerrains);
    checksum.ChecksumData(pSpec->m_pTerrainIDs, pSpec->m_uNumTerrains * 4);

    AVLTreeEntry<unsigned long, EffectsTerrainSpec*>* node = pTerrainSpecMap->m_Root;
    unsigned long hashID = ~checksum.m_unk_0x00;
    unsigned char found;
    EffectsTerrainSpec** foundValue;

    while (node != nullptr)
    {
        int cmpResult;

        if (hashID == node->key)
        {
            cmpResult = 0;
        }
        else if (hashID < node->key)
        {
            cmpResult = -1;
        }
        else
        {
            cmpResult = 1;
        }

        if (cmpResult == 0)
        {
            if (&foundValue != nullptr)
            {
                foundValue = &node->value;
            }

            found = true;
            break;
        }

        if (cmpResult < 0)
        {
            node = (AVLTreeEntry<unsigned long, EffectsTerrainSpec*>*)node->node.left;
        }
        else
        {
            node = (AVLTreeEntry<unsigned long, EffectsTerrainSpec*>*)node->node.right;
        }
    }

    if (node == nullptr)
    {
        found = false;
    }

    EffectsTerrainSpec* existingSpec;
    if (found)
    {
        existingSpec = *foundValue;
    }
    else
    {
        existingSpec = nullptr;
    }

    if (existingSpec == nullptr)
    {
        EffectsTerrainSpec* pNewSpec = pSpec;
        RunningChecksum checksum2;

        checksum2.ChecksumInt(pSpec->m_uNumTerrains);
        checksum2.ChecksumData(pSpec->m_pTerrainIDs, pSpec->m_uNumTerrains * 4);

        unsigned long key = ~checksum2.m_unk_0x00;
        AVLTreeNode* existingNode;

        pTerrainSpecMap->AddAVLNode((AVLTreeNode**)&pTerrainSpecMap->m_Root, &key, &pNewSpec, &existingNode, pTerrainSpecMap->m_NumElements);

        if (existingNode == nullptr)
        {
            pTerrainSpecMap->m_NumElements++;
        }

        return pSpec;
    }

    if (pSpec != nullptr)
    {
        if (pSpec->m_pTerrainIDs != nullptr)
        {
            delete[] pSpec->m_pTerrainIDs;
            pSpec->m_pTerrainIDs = nullptr;
        }

        delete pSpec;
    }

    return existingSpec;
}

/**
 * Offset/Address/Size: 0x338 | 0x801F2D80 | size: 0x4D4
 */
EffectsGroup* parse_group(SimpleParser*)
{
    FORCE_DONT_INLINE;
    return nullptr;
}

/**
 * Offset/Address/Size: 0x30C | 0x801F2D54 | size: 0x2C
 */
bool fxLoadGroupBundle(const char* filename)
{
    unsigned long fileSize;
    void* data = fxLoadEntireFileHigh(filename, &fileSize);
    return fxLoadGroupBundle(data, fileSize);
}

/**
 * Offset/Address/Size: 0x178 | 0x801F2BC0 | size: 0x194
 */
bool fxLoadGroupBundle(void* data, unsigned long size)
{

    if (data == nullptr)
    {
        return false;
    }

    pGroupMap = new (nlMalloc(0x14, 8, false)) nlAVLTree<unsigned long, EffectsGroup*, DefaultKeyCompare<unsigned long> >();
    pTerrainSpecMap = new (nlMalloc(0x14, 8, false)) nlAVLTree<unsigned long, EffectsTerrainSpec*, DefaultKeyCompare<unsigned long> >();

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
            unsigned long hashID;
            EffectsGroup* group;
            nlAVLTree<unsigned long, EffectsGroup*, DefaultKeyCompare<unsigned long> >* map;
            AVLTreeNode* existingNode;

            group = parse_group(&parser);
            hashID = group->m_hashID;

            map = pGroupMap;

            map->AddAVLNode((AVLTreeNode**)&map->m_Root, &hashID, &group, &existingNode, map->m_NumElements);

            if (existingNode == nullptr)
            {
                map->m_NumElements++;
            }
        }
        else
        {
            EmissionManager::AddError("EffectsGroup: unrecognized token '%s'\n", token);
        }
    }

    nlFree(data);
    return true;
}

/**
 * Offset/Address/Size: 0xA4 | 0x801F2AEC | size: 0x74
 */
bool fxUnloadGroups()
{
    if ((pGroupMap == NULL) && (pTerrainSpecMap == NULL))
    {
        return true;
    }

    pGroupMap->DeleteValues();
    delete pGroupMap;
    pGroupMap = nullptr;

    pTerrainSpecMap->DeleteValues();
    delete pTerrainSpecMap;
    pTerrainSpecMap = nullptr;

    return true;
}

/**
 * Helper struct for inlining FindGet with bool return to match target assembly.
 * The target uses a bool found flag pattern (li r0,1 / li r0,0 / clrlwi.)
 * which the native AVLTreeBase::FindGet (returning ValueType*) does not produce.
 */
struct GroupMapFindHelper
{
    char pad[0x8];
    AVLTreeEntry<unsigned long, EffectsGroup*>* m_Root;

    inline bool FindGet(unsigned long key, EffectsGroup*** foundValue) const
    {
        AVLTreeEntry<unsigned long, EffectsGroup*>* node = m_Root;
        while (node != NULL)
        {
            int cmpResult;
            if (key == node->key)
                cmpResult = 0;
            else if (key < node->key)
                cmpResult = -1;
            else
                cmpResult = 1;
            if (cmpResult == 0)
            {
                if (foundValue != NULL)
                    *foundValue = &node->value;
                return true;
            }
            else
            {
                if (cmpResult < 0)
                    node = (AVLTreeEntry<unsigned long, EffectsGroup*>*)node->node.left;
                else
                    node = (AVLTreeEntry<unsigned long, EffectsGroup*>*)node->node.right;
            }
        }
        return false;
    }
};

/**
 * Offset/Address/Size: 0x0 | 0x801F2A48 | size: 0xA4
 */
EffectsGroup* fxGetGroup(const char* name)
{
    EffectsGroup** foundValue;
    bool found = ((GroupMapFindHelper*)pGroupMap)->FindGet(nlStringHash(name), &foundValue);
    if (found)
        return *foundValue;
    return nullptr;
}
