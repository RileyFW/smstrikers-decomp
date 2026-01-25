#include "Game/FE/FEResourceManager.h"
#include "NL/nlMemory.h"
#include "NL/nlString.h"

static BundleFile* s_pOnDemandBundle;

// /**
//  * Offset/Address/Size: 0x0 | 0x8020D5A8 | size: 0x60
//  */
// void nlWalkRing<DLListEntry<FEResourceHandle*>, DLListContainerBase<FEResourceHandle*,
// BasicSlotPool<DLListEntry<FEResourceHandle*>>>>(DLListEntry<FEResourceHandle*>*, DLListContainerBase<FEResourceHandle*,
// BasicSlotPool<DLListEntry<FEResourceHandle*>>>*, void (DLListContainerBase<FEResourceHandle*,
// BasicSlotPool<DLListEntry<FEResourceHandle*>>>::*)(DLListEntry<FEResourceHandle*>*))
// {
// }

// /**
//  * Offset/Address/Size: 0xA8 | 0x8020D548 | size: 0x60
//  */
// void nlAVLTreeSlotPool<unsigned long, FEResourceHandle*, DefaultKeyCompare<unsigned long>>::~nlAVLTreeSlotPool()
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8020D4A0 | size: 0xA8
//  */
// void nlDLListSlotPool<FEResourceHandle*>::~nlDLListSlotPool()
// {
// }

// /**
//  * Offset/Address/Size: 0xFC | 0x8020D490 | size: 0x10
//  */
// void DLListContainerBase<FEResourceHandle*, BasicSlotPool<DLListEntry<FEResourceHandle*>>>::DeleteEntry(DLListEntry<FEResourceHandle*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x108 | 0x8020D358 | size: 0x3C
//  */
// void nlWalkDLRing<DLListEntry<FEResourceHandle*>, DLListContainerBase<FEResourceHandle*,
// BasicSlotPool<DLListEntry<FEResourceHandle*>>>>(DLListEntry<FEResourceHandle*>*, DLListContainerBase<FEResourceHandle*,
// BasicSlotPool<DLListEntry<FEResourceHandle*>>>*, void (DLListContainerBase<FEResourceHandle*,
// BasicSlotPool<DLListEntry<FEResourceHandle*>>>::*)(DLListEntry<FEResourceHandle*>*))
// {
// }

// /**
//  * Offset/Address/Size: 0xD0 | 0x8020D320 | size: 0x38
//  */
// void nlDLRingAddStart<DLListEntry<FEResourceHandle*>>(DLListEntry<FEResourceHandle*>**, DLListEntry<FEResourceHandle*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x94 | 0x8020D2E4 | size: 0x3C
//  */
// void nlDLRingAddEnd<DLListEntry<FEResourceHandle*>>(DLListEntry<FEResourceHandle*>**, DLListEntry<FEResourceHandle*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x50 | 0x8020D2A0 | size: 0x44
//  */
// void nlDLRingRemove<DLListEntry<FEResourceHandle*>>(DLListEntry<FEResourceHandle*>**, DLListEntry<FEResourceHandle*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x38 | 0x8020D288 | size: 0x18
//  */
// void nlDLRingGetStart<DLListEntry<FEResourceHandle*>>(DLListEntry<FEResourceHandle*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8020D250 | size: 0x38
//  */
// void nlDLRingRemoveStart<DLListEntry<FEResourceHandle*>>(DLListEntry<FEResourceHandle*>**)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8020D244 | size: 0xC
//  */
// void FEResourceManager::GetName()
// {
// }

// /**
//  * Offset/Address/Size: 0x900 | 0x8020D1A4 | size: 0xA0
//  */
// void AVLTreeBase<unsigned long, FEResourceHandle*, BasicSlotPool<AVLTreeEntry<unsigned long, FEResourceHandle*>>,
//                  DefaultKeyCompare<unsigned long>>::AllocateEntry(void*, void*)
// {
// }

// /**
//  * Offset/Address/Size: 0x8D4 | 0x8020D178 | size: 0x2C
//  */
// void AVLTreeBase<unsigned long, FEResourceHandle*, BasicSlotPool<AVLTreeEntry<unsigned long, FEResourceHandle*>>,
//                  DefaultKeyCompare<unsigned long>>::CompareKey(void*, AVLTreeNode*)
// {
// }

// /**
//  * Offset/Address/Size: 0x8A8 | 0x8020D14C | size: 0x2C
//  */
// void AVLTreeBase<unsigned long, FEResourceHandle*, BasicSlotPool<AVLTreeEntry<unsigned long, FEResourceHandle*>>,
//                  DefaultKeyCompare<unsigned long>>::CompareNodes(AVLTreeNode*, AVLTreeNode*)
// {
// }

// /**
//  * Offset/Address/Size: 0x82C | 0x8020D0D0 | size: 0x7C
//  */
// void AVLTreeBase<unsigned long, FEResourceHandle*, BasicSlotPool<AVLTreeEntry<unsigned long, FEResourceHandle*>>,
//                  DefaultKeyCompare<unsigned long>>::~AVLTreeBase()
// {
// }

// /**
//  * Offset/Address/Size: 0x824 | 0x8020D0C8 | size: 0x8
//  */
// void AVLTreeBase<unsigned long, FEResourceHandle*, BasicSlotPool<AVLTreeEntry<unsigned long, FEResourceHandle*>>,
//                  DefaultKeyCompare<unsigned long>>::CastUp(AVLTreeNode*) const
// {
// }

// /**
//  * Offset/Address/Size: 0xCC | 0x8020C970 | size: 0x758
//  */
// void AVLTreeBase<unsigned long, FEResourceHandle*, BasicSlotPool<AVLTreeEntry<unsigned long, FEResourceHandle*>>,
//                  DefaultKeyCompare<unsigned long>>::
//     PostorderTraversal(AVLTreeEntry<unsigned long, FEResourceHandle*>*,
//                        void (AVLTreeBase<unsigned long, FEResourceHandle*, BasicSlotPool<AVLTreeEntry<unsigned long, FEResourceHandle*>>,
//                                          DefaultKeyCompare<unsigned long>>::*)(AVLTreeEntry<unsigned long, FEResourceHandle*>*))
// {
// }

// /**
//  * Offset/Address/Size: 0x68 | 0x8020C90C | size: 0x64
//  */
// void AVLTreeBase<unsigned long, FEResourceHandle*, BasicSlotPool<AVLTreeEntry<unsigned long, FEResourceHandle*>>,
//                  DefaultKeyCompare<unsigned long>>::
//     DestroyTree(void (AVLTreeBase<unsigned long, FEResourceHandle*, BasicSlotPool<AVLTreeEntry<unsigned long, FEResourceHandle*>>,
//                                   DefaultKeyCompare<unsigned long>>::*)(AVLTreeEntry<unsigned long, FEResourceHandle*>*))
// {
// }

// /**
//  * Offset/Address/Size: 0x10 | 0x8020C8B4 | size: 0x58
//  */
// void AVLTreeBase<unsigned long, FEResourceHandle*, BasicSlotPool<AVLTreeEntry<unsigned long, FEResourceHandle*>>,
//                  DefaultKeyCompare<unsigned long>>::Clear()
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8020C8A4 | size: 0x10
//  */
// void AVLTreeBase<unsigned long, FEResourceHandle*, BasicSlotPool<AVLTreeEntry<unsigned long, FEResourceHandle*>>,
//                  DefaultKeyCompare<unsigned long>>::DeleteEntry(AVLTreeEntry<unsigned long, FEResourceHandle*>*)
// {
// }

/**
 * Offset/Address/Size: 0xD48 | 0x8020C888 | size: 0x1C
 */
FEResourceManager::FEResourceManager()
    : nlTask()
{
}

/**
 * Offset/Address/Size: 0xCEC | 0x8020C82C | size: 0x5C
 */
FEResourceManager::~FEResourceManager()
{
    Cleanup();
}

/**
 * Offset/Address/Size: 0xAF4 | 0x8020C634 | size: 0x1F8
 */
void FEResourceManager::Cleanup()
{
    FORCE_DONT_INLINE;
}

/**
 * Offset/Address/Size: 0x848 | 0x8020C388 | size: 0x2AC
 */
void FEResourceManager::LoadPermanentResourceBundle(const char*)
{
}

/**
 * Offset/Address/Size: 0x7D0 | 0x8020C310 | size: 0x78
 */
bool FEResourceManager::OpenOnDemandResourceBundle(const char* szBundleFileName)
{
    nlStrNCpy(m_szOnDemandBundleFileName, szBundleFileName, 0x20);

    BundleFile* pBundle = new (nlMalloc(sizeof(BundleFile), 8, false)) BundleFile();
    s_pOnDemandBundle = pBundle;

    if (!pBundle->Open(szBundleFileName)) {
        return false;
    }
    return true;
}

/**
 * Offset/Address/Size: 0x7CC | 0x8020C30C | size: 0x4
 */
void FEResourceManager::Initialize()
{
}

/**
 * Offset/Address/Size: 0x72C | 0x8020C26C | size: 0xA0
 */
void FEResourceManager::QueueResourceLoad(FEResourceHandle*)
{
}

/**
 * Offset/Address/Size: 0x5F4 | 0x8020C134 | size: 0x138
 */
void FEResourceManager::UnloadResource(FEResourceHandle*)
{
}

/**
 * Offset/Address/Size: 0x344 | 0x8020BE84 | size: 0x2B0
 */
void FEResourceManager::UnloadPermanentResourceBundle()
{
}

/**
 * Offset/Address/Size: 0x29C | 0x8020BDDC | size: 0xA8
 */
void FEResourceManager::TextureResourceLoadComplete(void*, unsigned long, unsigned long)
{
}

/**
 * Offset/Address/Size: 0x0 | 0x8020BB40 | size: 0x29C
 */
void FEResourceManager::Update(float)
{
}
