#include "Game/AI/Scripts/CommonScript.h"

#include "Game/Team.h"
#include "Game/Player.h"
#include "Game/AI/Fielder.h"

// /**
//  * Offset/Address/Size: 0x654 | 0x8007A56C | size: 0x80
//  */
// void std::__red_black_tree<1>::rotate_left(std::__red_black_tree<1>::node_base*, std::__red_black_tree<1>::node_base*&)
// {
// }

// /**
//  * Offset/Address/Size: 0x5D4 | 0x8007A4EC | size: 0x80
//  */
// void std::__red_black_tree<1>::rotate_right(std::__red_black_tree<1>::node_base*, std::__red_black_tree<1>::node_base*&)
// {
// }

// /**
//  * Offset/Address/Size: 0x3E4 | 0x8007A2FC | size: 0x1F0
//  */
// void std::__red_black_tree<1>::balance_insert(std::__red_black_tree<1>::node_base*, std::__red_black_tree<1>::node_base*)
// {
// }

// /**
//  * Offset/Address/Size: 0x234 | 0x8007A14C | size: 0x1B0
//  */
// void std::__tree<std::pair<const unsigned long, FuzzyVariant>, std::map<unsigned long, FuzzyVariant, std::less<unsigned long>, std::allocator<std::pair<const unsigned long, FuzzyVariant>>>::value_compare, std::allocator<std::pair<const unsigned long, FuzzyVariant>>>::insert_node_at(std::__tree<std::pair<const unsigned long, FuzzyVariant>, std::map<unsigned long, FuzzyVariant, std::less<unsigned long>, std::allocator<std::pair<const unsigned long, FuzzyVariant>>>::value_compare, std::allocator<std::pair<const unsigned long, FuzzyVariant>>>::node*, bool, bool, const std::pair<const unsigned long, FuzzyVariant>&)
// {
// }

// /**
//  * Offset/Address/Size: 0x1D0 | 0x8007A0E8 | size: 0x64
//  */
// void std::__tree<std::pair<const unsigned long, FuzzyVariant>, std::map<unsigned long, FuzzyVariant, std::less<unsigned long>, std::allocator<std::pair<const unsigned long, FuzzyVariant>>>::value_compare, std::allocator<std::pair<const unsigned long, FuzzyVariant>>>::find<unsigned long>(const unsigned long&)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x80079F18 | size: 0x1D0
//  */
// void std::__tree<std::pair<const unsigned long, FuzzyVariant>, std::map<unsigned long, FuzzyVariant, std::less<unsigned long>, std::allocator<std::pair<const unsigned long, FuzzyVariant>>>::value_compare, std::allocator<std::pair<const unsigned long, FuzzyVariant>>>::find_or_insert<unsigned long, FuzzyVariant>(const unsigned long&)
// {
// }

struct StdMapNodeBase
{
    void* left;
    void* right;
    void* parent;
};

struct StdMapTree
{
    unsigned long x0;
    StdMapNodeBase x4;
};

struct StdMapNode
{
    StdMapNodeBase base;
    unsigned long key;
    FuzzyVariant value;
};

extern "C" void __find(StdMapNode** outNode, void* tree, const unsigned long* key);

/**
 * Offset/Address/Size: 0xE4 | 0x80079D64 | size: 0x1B4
 * TODO: Remaining diff is std::tree find call symbol (__find wrapper vs templated std::__tree::find<Ul>)
 */
unsigned char ScriptQuestionCache::Lookup(unsigned long hash, FuzzyVariant& returnVal, const char* name)
{
    FuzzyVariant* pValue;
    StdMapNode* stdNode;

    mTotalLookups++;

    if (g_bScriptQuestionCachingUseSTD)
    {
        __find(&stdNode, &mQuestionCacheMapSTD, &hash);

        StdMapNode* stdFound = stdNode;
        if ((StdMapNodeBase*)stdFound != &((StdMapTree*)&mQuestionCacheMapSTD)->x4)
        {
            mCacheHits++;
            returnVal = stdFound->value;
            return 1;
        }
    }
    else
    {
        AVLTreeEntry<unsigned long, FuzzyVariant>* node = mQuestionCacheMap.m_Root;
        unsigned long key = hash;
        unsigned char found;

        while (node != NULL)
        {
            int cmpResult;
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
                if (&pValue != NULL)
                {
                    pValue = &node->value;
                }
                found = 1;
                goto found_done;
            }
            if (cmpResult < 0)
            {
                node = (AVLTreeEntry<unsigned long, FuzzyVariant>*)node->node.left;
            }
            else
            {
                node = (AVLTreeEntry<unsigned long, FuzzyVariant>*)node->node.right;
            }
        }

        found = 0;

    found_done:

        if (found)
        {
            mCacheHits++;
            returnVal = *pValue;
            return 1;
        }
    }

    return 0;
}

// Stub for find_or_insert result (std::pair<const unsigned long, FuzzyVariant> in map)
struct FuzzyMapPair
{
    unsigned long key;
    FuzzyVariant value;
};

extern "C" FuzzyMapPair* __find_or_insert(void* tree, const unsigned long* key);

/**
 * Offset/Address/Size: 0x0 | 0x80079C80 | size: 0xE4
 */
const FuzzyVariant& ScriptQuestionCache::AddToCache(unsigned long key, const FuzzyVariant& variant, const char* name)
{
    if (g_bScriptQuestionCachingOn)
    {
        if (g_bScriptQuestionCachingUseSTD)
        {
            // TODO: Implement all this std stuff..
            FuzzyMapPair* pair = __find_or_insert(&mQuestionCacheMapSTD, &key);
            pair->value = variant;
        }
        else
        {
            AVLTreeNode* existingNode;
            mQuestionCacheMap.AddAVLNode((AVLTreeNode**)&mQuestionCacheMap.m_Root, (void*)&key, (void*)&variant, &existingNode, mQuestionCacheMap.m_NumElements);
            if (existingNode == NULL)
            {
                mQuestionCacheMap.m_NumElements++;
            }
        }
    }
    return variant;
}

/**
 * Offset/Address/Size: 0x0 | 0x80079C38 | size: 0x48
 */
SaveConfidence::~SaveConfidence()
{
}

/**
 * Offset/Address/Size: 0x0 | 0x80079B54 | size: 0xE4
 */
// FuzzyVariant::FuzzyVariant(const FuzzyVariant&)
// {
// }

/**
 * Offset/Address/Size: 0xF1B0 | 0x80079380 | size: 0x7D4
 */
void Fuzzy::GetStrategicBallCarrier(cTeam*)
{
}

/**
 * Offset/Address/Size: 0xE9DC | 0x80078BAC | size: 0x7D4
 */
void Fuzzy::GetBestBallInterceptor(cTeam*)
{
}

/**
 * Offset/Address/Size: 0xE40C | 0x800785DC | size: 0x5D0
 */
void Fuzzy::GetSwapControllerScore(cPlayer*)
{
}

/**
 * Offset/Address/Size: 0xDC78 | 0x80077E48 | size: 0x794
 */
void Fuzzy::ShouldIStrafeBall(cFielder*)
{
}

/**
 * Offset/Address/Size: 0xD92C | 0x80077AFC | size: 0x34C
 */
void Fuzzy::ShouldIStrafeMark(cFielder*)
{
}

/**
 * Offset/Address/Size: 0xD188 | 0x80077358 | size: 0x7A4
 */
void Fuzzy::ShouldIMarkBallOwner(cFielder*)
{
}

/**
 * Offset/Address/Size: 0xC144 | 0x80076314 | size: 0x1044
 */
void Fuzzy::ShouldIAttemptOneTimer(cFielder*)
{
}

/**
 * Offset/Address/Size: 0xB89C | 0x80075A6C | size: 0x8A8
 */
void Fuzzy::GetBestLooseBallPassTarget(cFielder*)
{
}

/**
 * Offset/Address/Size: 0xAC34 | 0x80074E04 | size: 0xC68
 */
void Fuzzy::GetBestPassTarget(cPlayer*)
{
}

/**
 * Offset/Address/Size: 0xA138 | 0x80074308 | size: 0xAFC
 */
void Fuzzy::GoodPassTargetFrom(cFielder*, cFielder*)
{
}

/**
 * Offset/Address/Size: 0x95A0 | 0x80073770 | size: 0xB98
 */
void Fuzzy::GetBestHitTarget(cFielder*)
{
}

/**
 * Offset/Address/Size: 0x8D80 | 0x80072F50 | size: 0x820
 */
void Fuzzy::GetPassDirection(cPlayer*, cPlayer*)
{
}

/**
 * Offset/Address/Size: 0x801C | 0x800721EC | size: 0xD64
 */
void Fuzzy::GoodToShoot(cFielder*)
{
}

/**
 * Offset/Address/Size: 0x71F4 | 0x800713C4 | size: 0xE28
 */
void Fuzzy::GoodToChipShot(cFielder*)
{
}

/**
 * Offset/Address/Size: 0x57C4 | 0x8006F994 | size: 0x1A30
 */
void Fuzzy::GetBestPassReceiveAction(cFielder*)
{
}

/**
 * Offset/Address/Size: 0x3FD0 | 0x8006E1A0 | size: 0x17F4
 */
void Fuzzy::GetBestLooseBallAction(cFielder*)
{
}

/**
 * Offset/Address/Size: 0x2CB4 | 0x8006CE84 | size: 0x131C
 */
void Fuzzy::GetBestWindupShotAction(cFielder*)
{
}

/**
 * Offset/Address/Size: 0x1A48 | 0x8006BC18 | size: 0x126C
 */
void Fuzzy::GetPowerupToUseForPassReceiveDefence(cFielder*)
{
}

/**
 * Offset/Address/Size: 0x1620 | 0x8006B7F0 | size: 0x428
 */
void Fuzzy::GetPowerupToUseForWindupDefence(cFielder*)
{
}

/**
 * Offset/Address/Size: 0xE64 | 0x8006B034 | size: 0x7BC
 */
void Fuzzy::InDanger(cFielder*)
{
}

/**
 * Offset/Address/Size: 0x3B4 | 0x8006A584 | size: 0xAB0
 */
void Fuzzy::InDangerDelayed(cFielder*)
{
}

/**
 * Offset/Address/Size: 0x0 | 0x8006A1D0 | size: 0x3B4
 */
void Fuzzy::GoalieAndGonnaPickupBall(cPlayer*)
{
}
