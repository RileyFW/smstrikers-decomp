#include "Game/Render/StaticModelExplodable.h"
#include "Game/Drawable/DrawableObj.h"

nlList<SidelineExplodableNode> StaticModelExplodable::sStaticModelExplodableList;

// /**
//  * Offset/Address/Size: 0x0 | 0x80165D2C | size: 0x138
//  */
// void 0x8028D320..0x8028D324 | size: 0x4
// {
// }

/**
 * Offset/Address/Size: 0x5AC | 0x80165A70 | size: 0x2BC
 */
void StaticModelExplodable::CreateExplodablesFromHelperObjects()
{
}

/**
 * Offset/Address/Size: 0x500 | 0x801659C4 | size: 0xAC
 */
void StaticModelExplodable::CleanUp()
{
    long zero = 0;
    SlotPoolBase* pPool = &SidelineExplodableNode::sSidelineExplodableNodeSlotPool;
    SidelineExplodableNode** pTail = &sStaticModelExplodableList.m_pEnd;
    SidelineExplodableNode* node;
    while ((node = sStaticModelExplodableList.m_pStart) != NULL)
    {
        nlListRemoveStart<SidelineExplodableNode>(&sStaticModelExplodableList.m_pStart, pTail);
        SidelineExplodable* pExplodable = node->mpExplodable;
        if (pExplodable != NULL)
        {
            SidelineExplodableManager::RemoveSidelineExplodable(pExplodable);
            delete node->mpExplodable;
        }
        node->mpExplodable = (SidelineExplodable*)zero;
        ((SlotPoolEntry*)node)->m_next = pPool->m_FreeList;
        pPool->m_FreeList = (SlotPoolEntry*)node;
    }
}

/**
 * Offset/Address/Size: 0xC4 | 0x80165588 | size: 0x43C
 */
StaticModelExplodable::StaticModelExplodable(StaticModelExplodableCategory, const nlMatrix4&)
{
}

/**
 * Offset/Address/Size: 0x64 | 0x80165528 | size: 0x60
 */
StaticModelExplodable::~StaticModelExplodable()
{
}

/**
 * Offset/Address/Size: 0x4C | 0x80165510 | size: 0x18
 */
void StaticModelExplodable::GetCategoryData() const
{
}

/**
 * Offset/Address/Size: 0x44 | 0x80165508 | size: 0x8
 */
void StaticModelExplodable::GetWorldMatrix() const
{
}

/**
 * Offset/Address/Size: 0x18 | 0x801654DC | size: 0x2C
 */
void StaticModelExplodable::SetUnexplodedModelVisibility(bool visible)
{
    DrawableObject* obj = m_pUnexplodedModel;
    if (visible)
    {
        obj->m_uObjectFlags |= 1;
    }
    else
    {
        obj->m_uObjectFlags &= ~1;
    }
}

/**
 * Offset/Address/Size: 0x0 | 0x801654C4 | size: 0x18
 */
bool StaticModelExplodable::LoadGeometry()
{
    return false;
}
