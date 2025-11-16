#include "Game/FE/feSceneManager.h"
#include "Game/FE/feInput.h"
#include "Game/FE/feRender.h"
#include "NL/nlDLRing.h"
#include "NL/nlDLListSlotPool.h"

extern FEInput* g_pFEInput;

static nlDLListSlotPool<PackagePushPopMessage*> m_pushPopMessageQueue;

/**
 * Offset/Address/Size: 0x0 | 0x8020D64C | size: 0xC0
 */
void FESceneManager::Update(float dt)
{
    DLListEntry<BaseSceneHandler*>* headEntry;
    DLListEntry<BaseSceneHandler*>* currentEntry;

    ProcessPushPopQueue();

    if (m_sceneHandlerStack.m_Head == nullptr)
    {
        return;
    }

    currentEntry = nlDLRingGetStart(m_sceneHandlerStack.m_Head);
    headEntry = m_sceneHandlerStack.m_Head;

    while (currentEntry != nullptr)
    {
        if (currentEntry->m_data->m_pFEScene->m_bValid != false)
        {
            g_pFEInput->EnableInputIfSceneHasFocus(currentEntry->m_data);
            currentEntry->m_data->Update(dt);
        }

        if (nlDLRingIsEnd(headEntry, currentEntry) || currentEntry == nullptr)
        {
            currentEntry = nullptr;
        }
        else
        {
            currentEntry = currentEntry->m_next;
        }
    }
}

/**
 * Offset/Address/Size: 0xC0 | 0x8020D70C | size: 0x1C4
 */
void FESceneManager::RenderActiveScenes()
{
}

/**
 * Offset/Address/Size: 0x284 | 0x8020D8D0 | size: 0x1A8
 */
void FESceneManager::QueueScenePop()
{
}

/**
 * Offset/Address/Size: 0x42C | 0x8020DA78 | size: 0x114
 */
void FESceneManager::QueueScenePush(BaseSceneHandler*, const char*)
{
}

/**
 * Offset/Address/Size: 0x540 | 0x8020DB8C | size: 0x270
 */
void FESceneManager::ProcessPushPopQueue()
{
    FORCE_DONT_INLINE;
}

/**
 * Offset/Address/Size: 0x7B0 | 0x8020DDFC | size: 0x98
 */
BaseSceneHandler* FESceneManager::GetSceneHandler(unsigned long hashID)
{
    DLListEntry<BaseSceneHandler*>* headEntry;
    DLListEntry<BaseSceneHandler*>* currentEntry;

    currentEntry = nlDLRingGetStart(m_sceneHandlerStack.m_Head);
    headEntry = m_sceneHandlerStack.m_Head;

    while (currentEntry != nullptr)
    {
        if (hashID == currentEntry->m_data->m_uHashID)
        {
            return currentEntry->m_data;
        }

        if (nlDLRingIsEnd(headEntry, currentEntry) || currentEntry == nullptr)
        {
            currentEntry = nullptr;
        }
        else
        {
            currentEntry = currentEntry->m_next;
        }
    }

    return nullptr;
}

/**
 * Offset/Address/Size: 0x848 | 0x8020DE94 | size: 0x20
 */
void FESceneManager::ForceImmediateStackProcessing()
{
    FORCE_DONT_INLINE;
    ProcessPushPopQueue();
}

/**
 * Offset/Address/Size: 0x868 | 0x8020DEB4 | size: 0xA4
 */
bool FESceneManager::AreAllScenesValid()
{
    DLListEntry<BaseSceneHandler*>* headEntry;
    DLListEntry<BaseSceneHandler*>* currentEntry;

    currentEntry = nlDLRingGetStart(m_sceneHandlerStack.m_Head);
    headEntry = m_sceneHandlerStack.m_Head;

    while (currentEntry != nullptr)
    {
        BaseSceneHandler* sceneHandler = currentEntry->m_data;
        if (sceneHandler->m_pFEScene->m_bValid == false)
        {
            return false;
        }

        if (nlDLRingIsEnd(headEntry, currentEntry) || currentEntry == nullptr)
        {
            currentEntry = nullptr;
        }
        else
        {
            currentEntry = currentEntry->m_next;
        }
    }

    return (m_pushPopMessageQueue.m_Head == nullptr);
}

/**
 * Offset/Address/Size: 0x90C | 0x8020DF58 | size: 0xB8
 */
FESceneManager::~FESceneManager()
{
    ForceImmediateStackProcessing();
    FERender::Cleanup();

    nlWalkDLRing<DLListEntry<BaseSceneHandler*>, DLListContainerBase<BaseSceneHandler*, BasicSlotPool<DLListEntry<BaseSceneHandler*> > > >(
        m_sceneHandlerStack.m_Head,
        &m_sceneHandlerStack,
        &DLListContainerBase<BaseSceneHandler*, BasicSlotPool<DLListEntry<BaseSceneHandler*> > >::DeleteEntry);
}

/**
 * Offset/Address/Size: 0x9C4 | 0x8020E010 | size: 0x70
 */
FESceneManager::FESceneManager()
// : m_sceneHandlerStack()
{
    // new (&m_sceneHandlerStack.m_Allocator) SlotPoolBase();
    // m_sceneHandlerStack.m_Head = nullptr;
    // m_sceneHandlerStack.m_Allocator.m_Initial = 0x14;
    // SlotPoolBase::BaseAddNewBlock(&m_sceneHandlerStack.m_Allocator, sizeof(DLListEntry<BaseSceneHandler*>));
    // m_sceneHandlerStack.m_Allocator.m_Delta = 0;
    // m_uDefaultRenderView = -1;
    // m_topMostScene = nullptr;
    // FERender::Initialize();
}

// /**
//  * Offset/Address/Size: 0x0 | 0x8020E080 | size: 0x10
//  */
// void DLListContainerBase<BaseSceneHandler*, BasicSlotPool<DLListEntry<BaseSceneHandler*>>>::DeleteEntry(DLListEntry<BaseSceneHandler*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0xD0 | 0x8020E150 | size: 0x10
//  */
// void DLListContainerBase<PackagePushPopMessage*,
// BasicSlotPool<DLListEntry<PackagePushPopMessage*>>>::DeleteEntry(DLListEntry<PackagePushPopMessage*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0xE0 | 0x8020E160 | size: 0xA8
//  */
// void nlDLListSlotPool<PackagePushPopMessage*>::~nlDLListSlotPool()
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8020E208 | size: 0x64
//  */
// void SlotPool<PackagePushPopMessage>::~SlotPool()
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8020E26C | size: 0x3C
//  */
// void nlWalkDLRing<DLListEntry<BaseSceneHandler*>, DLListContainerBase<BaseSceneHandler*,
// BasicSlotPool<DLListEntry<BaseSceneHandler*>>>>(DLListEntry<BaseSceneHandler*>*, DLListContainerBase<BaseSceneHandler*,
// BasicSlotPool<DLListEntry<BaseSceneHandler*>>>*, void (DLListContainerBase<BaseSceneHandler*,
// BasicSlotPool<DLListEntry<BaseSceneHandler*>>>::*)(DLListEntry<BaseSceneHandler*>*))
// {
// }

// /**
//  * Offset/Address/Size: 0x3C | 0x8020E2A8 | size: 0x38
//  */
// void nlDLRingRemoveStart<DLListEntry<PackagePushPopMessage*>>(DLListEntry<PackagePushPopMessage*>**)
// {
// }

// /**
//  * Offset/Address/Size: 0x74 | 0x8020E2E0 | size: 0x20
//  */
// void nlDLRingIsEnd<DLListEntry<PackagePushPopMessage*>>(DLListEntry<PackagePushPopMessage*>*, DLListEntry<PackagePushPopMessage*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x94 | 0x8020E300 | size: 0x20
//  */
// void nlDLRingIsEnd<DLListEntry<BaseSceneHandler*>>(DLListEntry<BaseSceneHandler*>*, DLListEntry<BaseSceneHandler*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0xB4 | 0x8020E320 | size: 0x18
//  */
// void nlDLRingGetStart<DLListEntry<PackagePushPopMessage*>>(DLListEntry<PackagePushPopMessage*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0xCC | 0x8020E338 | size: 0x18
//  */
// void nlDLRingGetStart<DLListEntry<BaseSceneHandler*>>(DLListEntry<BaseSceneHandler*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0xE4 | 0x8020E350 | size: 0x44
//  */
// void nlDLRingRemove<DLListEntry<PackagePushPopMessage*>>(DLListEntry<PackagePushPopMessage*>**, DLListEntry<PackagePushPopMessage*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x128 | 0x8020E394 | size: 0x44
//  */
// void nlDLRingRemove<DLListEntry<BaseSceneHandler*>>(DLListEntry<BaseSceneHandler*>**, DLListEntry<BaseSceneHandler*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x16C | 0x8020E3D8 | size: 0x3C
//  */
// void nlDLRingAddEnd<DLListEntry<PackagePushPopMessage*>>(DLListEntry<PackagePushPopMessage*>**, DLListEntry<PackagePushPopMessage*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x1A8 | 0x8020E414 | size: 0x38
//  */
// void nlDLRingAddStart<DLListEntry<PackagePushPopMessage*>>(DLListEntry<PackagePushPopMessage*>**, DLListEntry<PackagePushPopMessage*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x1E0 | 0x8020E44C | size: 0x38
//  */
// void nlDLRingAddStart<DLListEntry<BaseSceneHandler*>>(DLListEntry<BaseSceneHandler*>**, DLListEntry<BaseSceneHandler*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x218 | 0x8020E484 | size: 0x3C
//  */
// void nlWalkDLRing<DLListEntry<PackagePushPopMessage*>, DLListContainerBase<PackagePushPopMessage*,
// BasicSlotPool<DLListEntry<PackagePushPopMessage*>>>>(DLListEntry<PackagePushPopMessage*>*, DLListContainerBase<PackagePushPopMessage*,
// BasicSlotPool<DLListEntry<PackagePushPopMessage*>>>*, void (DLListContainerBase<PackagePushPopMessage*,
// BasicSlotPool<DLListEntry<PackagePushPopMessage*>>>::*)(DLListEntry<PackagePushPopMessage*>*))
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8020E4C0 | size: 0x60
//  */
// void nlWalkRing<DLListEntry<BaseSceneHandler*>, DLListContainerBase<BaseSceneHandler*,
// BasicSlotPool<DLListEntry<BaseSceneHandler*>>>>(DLListEntry<BaseSceneHandler*>*, DLListContainerBase<BaseSceneHandler*,
// BasicSlotPool<DLListEntry<BaseSceneHandler*>>>*, void (DLListContainerBase<BaseSceneHandler*,
// BasicSlotPool<DLListEntry<BaseSceneHandler*>>>::*)(DLListEntry<BaseSceneHandler*>*))
// {
// }

// /**
//  * Offset/Address/Size: 0x60 | 0x8020E520 | size: 0x60
//  */
// void nlWalkRing<DLListEntry<PackagePushPopMessage*>, DLListContainerBase<PackagePushPopMessage*,
// BasicSlotPool<DLListEntry<PackagePushPopMessage*>>>>(DLListEntry<PackagePushPopMessage*>*, DLListContainerBase<PackagePushPopMessage*,
// BasicSlotPool<DLListEntry<PackagePushPopMessage*>>>*, void (DLListContainerBase<PackagePushPopMessage*,
// BasicSlotPool<DLListEntry<PackagePushPopMessage*>>>::*)(DLListEntry<PackagePushPopMessage*>*))
// {
// }
