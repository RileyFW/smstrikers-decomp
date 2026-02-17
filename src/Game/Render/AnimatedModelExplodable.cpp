#include "Game/Render/AnimatedModelExplodable.h"

struct AnimatedModelExplodableList
{
    SidelineExplodableNode* m_pStart;
    SidelineExplodableNode* m_pEnd;
};

static AnimatedModelExplodableList sAnimatedModelExplodableList;
ExplodableCategoryData AnimatedModelExplodable::sCategoryData[NUM_ANIMATED_MODEL_EXPLODABLE_CATEGORIES];
u8 AnimatedModelExplodable::bIsModelLoaded[2];

void RemoveSidelineExplodable(SidelineExplodable*);

// /**
//  * Offset/Address/Size: 0x70 | 0x80158C4C | size: 0x128
//  */
// void 0x8028D2FC..0x8028D300 | size: 0x4
// {
// }

/**
 * Offset/Address/Size: 0x44 | 0x80158C20 | size: 0x2C
 */
// void nlListAddEnd<SidelineExplodableNode>(SidelineExplodableNode**, SidelineExplodableNode**, SidelineExplodableNode*)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x80158BDC | size: 0x44
//  */
// void nlListRemoveStart<SidelineExplodableNode>(SidelineExplodableNode**, SidelineExplodableNode**)
// {
// }

/**
 * Offset/Address/Size: 0x1C4 | 0x80158B30 | size: 0xAC
 * TODO: 98.95% match - r5 vs r12 for vtable pointer in virtual destructor dispatch
 */
void AnimatedModelExplodable::CleanUp()
{
    long zero = 0;
    SlotPoolBase* pPool = &SidelineExplodableManager::sSidelineExplodableNodeSlotPool;
    SidelineExplodableNode** pTail = &sAnimatedModelExplodableList.m_pEnd;
    SidelineExplodableNode* node;
    while ((node = sAnimatedModelExplodableList.m_pStart) != NULL)
    {
        nlListRemoveStart<SidelineExplodableNode>(&sAnimatedModelExplodableList.m_pStart, pTail);
        SidelineExplodable* pExplodable = node->mpExplodable;
        if (pExplodable != NULL)
        {
            RemoveSidelineExplodable(pExplodable);
        }
        pExplodable = node->mpExplodable;
        if (pExplodable != NULL)
        {
            typedef void (*VDtor)(SidelineExplodable*, s32);
            VDtor fn = (VDtor)((*(unsigned long**)pExplodable)[2]);
            fn(pExplodable, 1);
        }
        node->mpExplodable = (SidelineExplodable*)zero;
        ((SlotPoolEntry*)node)->m_next = pPool->m_FreeList;
        pPool->m_FreeList = (SlotPoolEntry*)node;
    }
}

/**
 * Offset/Address/Size: 0xA8 | 0x80158A14 | size: 0x11C
 */
AnimatedModelExplodable::AnimatedModelExplodable(AnimatedModelExplodableCategory, SkinAnimatedNPC*)
{
}

/**
 * Offset/Address/Size: 0x48 | 0x801589B4 | size: 0x60
 */
AnimatedModelExplodable::~AnimatedModelExplodable()
{
}

/**
 * Offset/Address/Size: 0x30 | 0x8015899C | size: 0x18
 */
ExplodableCategoryData& AnimatedModelExplodable::GetCategoryData() const
{
    return sCategoryData[mCategory];
}

/**
 * Offset/Address/Size: 0x24 | 0x80158990 | size: 0xC
 */
const nlMatrix4& AnimatedModelExplodable::GetWorldMatrix() const
{
    return mpAnimatedNPC->mWorldMatrix;
}

/**
 * Offset/Address/Size: 0x18 | 0x80158984 | size: 0xC
 */
void AnimatedModelExplodable::SetUnexplodedModelVisibility(bool)
{
}

/**
 * Offset/Address/Size: 0x0 | 0x8015896C | size: 0x18
 */
bool AnimatedModelExplodable::LoadGeometry()
{
    bIsModelLoaded[0] = 0;
    bIsModelLoaded[1] = 0;
    return true;
}
