#include "Game/World/worldanim.h"
#include "NL/nlString.h"
#include "NL/nlSlotPool.h"
#include "Game/SAnim.h"

template <>
nlAVLTree<unsigned long, AnimationSet*, DefaultKeyCompare<unsigned long> >::~nlAVLTree()
{
    FORCE_DONT_INLINE;
}

/**
 * Offset/Address/Size: 0x5C8 | 0x8019B394 | size: 0x94
 */
WorldAnimManager::WorldAnimManager()
{
    cInventory<cSHierarchy>* inv = (cInventory<cSHierarchy>*)nlMalloc(sizeof(cInventory<cSHierarchy>), 8, 0);
    if (inv != NULL)
    {
        inv->m_lItemList.m_Head = NULL;
        inv->m_lItemList.m_Tail = NULL;
        inv->m_lMemList.m_Head = NULL;
        inv->m_lMemList.m_Tail = NULL;
        inv->m_nItemCount = 0;
    }
    m_pHierarchyInventory = inv;
}

/**
 * Offset/Address/Size: 0x14C | 0x8019AF18 | size: 0x41C
 */
WorldAnimManager::~WorldAnimManager()
{
    // TODO: Implement
}

/**
 * Offset/Address/Size: 0x58 | 0x8019AE24 | size: 0xF4
 */
void WorldAnimController::SetAnimation(const char* szAnimationName, ePlayMode playMode)
{
    u32 hash = nlStringLowerHash(szAnimationName);
    cSAnim* anim = m_pAnimationSet->FindAnimationByHash(hash);

    if (m_pPoseTree != NULL)
    {
        delete m_pPoseTree;
    }

    cPN_SAnimController* newController = AllocateSAnimController();
    newController = new (newController) cPN_SAnimController(anim, NULL, playMode, NULL, 0, false);
    m_pPoseTree = newController;
}

/**
 * Offset/Address/Size: 0x44 | 0x8019AE10 | size: 0x14
 */
void WorldAnimController::SetAnimationTime(float fTime)
{
    cPN_SAnimController* cntrl = m_pPoseTree;
    cntrl->m_fPrevTime = cntrl->m_fTime;
    cntrl->m_fTime = fTime;
}

/**
 * Offset/Address/Size: 0x38 | 0x8019AE04 | size: 0xC
 */
float WorldAnimController::GetAnimationTime()
{
    return m_pPoseTree->m_fTime;
}

/**
 * Offset/Address/Size: 0x0 | 0x8019ADCC | size: 0x38
 */
float WorldAnimController::GetAnimationDuration()
{
    return (float)m_pPoseTree->m_pSAnim->m_nNumKeys / 30.0f;
}
