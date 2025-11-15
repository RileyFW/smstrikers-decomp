#ifndef _FESCENEMANAGER_H_
#define _FESCENEMANAGER_H_

#include "types.h"

#include "NL/nlSingleton.h"
#include "NL/nlDLListSlotPool.h"
#include "NL/nlDLRing.h"

#include "Game/BaseSceneHandler.h"
#include "Game/FE/feScene.h"

// void nlDLRingRemoveStart<DLListEntry<PackagePushPopMessage*>>(DLListEntry<PackagePushPopMessage*>**);
// void nlDLRingIsEnd<DLListEntry<PackagePushPopMessage*>>(DLListEntry<PackagePushPopMessage*>*, DLListEntry<PackagePushPopMessage*>*);
// void nlDLRingIsEnd<DLListEntry<BaseSceneHandler*>>(DLListEntry<BaseSceneHandler*>*, DLListEntry<BaseSceneHandler*>*);
// void nlDLRingGetStart<DLListEntry<PackagePushPopMessage*>>(DLListEntry<PackagePushPopMessage*>*);
// void nlDLRingGetStart<DLListEntry<BaseSceneHandler*>>(DLListEntry<BaseSceneHandler*>*);
// void nlDLRingRemove<DLListEntry<PackagePushPopMessage*>>(DLListEntry<PackagePushPopMessage*>**, DLListEntry<PackagePushPopMessage*>*);
// void nlDLRingRemove<DLListEntry<BaseSceneHandler*>>(DLListEntry<BaseSceneHandler*>**, DLListEntry<BaseSceneHandler*>*);
// void nlDLRingAddEnd<DLListEntry<PackagePushPopMessage*>>(DLListEntry<PackagePushPopMessage*>**, DLListEntry<PackagePushPopMessage*>*);
// void nlDLRingAddStart<DLListEntry<PackagePushPopMessage*>>(DLListEntry<PackagePushPopMessage*>**, DLListEntry<PackagePushPopMessage*>*);
// void nlDLRingAddStart<DLListEntry<BaseSceneHandler*>>(DLListEntry<BaseSceneHandler*>**, DLListEntry<BaseSceneHandler*>*);

class BaseSceneHandler;

class FESceneManager : public nlSingleton<FESceneManager>
{
public:
    void Update(float);
    void RenderActiveScenes();
    void QueueScenePop();
    void QueueScenePush(BaseSceneHandler*, const char*);
    static void ProcessPushPopQueue();
    BaseSceneHandler* GetSceneHandler(unsigned long);
    void ForceImmediateStackProcessing();
    bool AreAllScenesValid();

    ~FESceneManager();
    FESceneManager();

    /* 0x00 */ nlDLListSlotPool<BaseSceneHandler*> m_sceneHandlerStack;
    /* 0x1C */ BaseSceneHandler* m_topMostScene;
    /* 0x20 */ unsigned long m_uDefaultRenderView;

    // /* 0x00 */ s32 m_unk_0x00;
    // /* 0x04 */ s32 m_unk_0x04;
    // /* 0x08 */ char pad8[4];
    // /* 0x0C */ DLListEntry<BaseSceneHandler*>* m_unk_0x0C;
    // /* 0x10 */ char pad10[8];
    // /* 0x18 */ DLListEntry<BaseSceneHandler*>* m_unk_0x18;
    // /* 0x1C */ FEScene* m_unk_0x1C;
    // /* 0x20 */ s32 m_unk_0x20;

    // static nlSingleton<FESceneManager> s_pInstance;
};

// class DLListContainerBase<BaseSceneHandler*, BasicSlotPool<DLListEntry<BaseSceneHandler*>>>
// {
// public:
//     void DeleteEntry(DLListEntry<BaseSceneHandler*>*);
// };

// class DLListContainerBase<PackagePushPopMessage*, BasicSlotPool<DLListEntry<PackagePushPopMessage*>>>
// {
// public:
//     void DeleteEntry(DLListEntry<PackagePushPopMessage*>*);
// };

// class nlDLListSlotPool<PackagePushPopMessage*>
// {
// public:
//     void ~nlDLListSlotPool();
// };

// class SlotPool<PackagePushPopMessage>
// {
// public:
//     void ~SlotPool();
// };

// class nlWalkDLRing<DLListEntry<BaseSceneHandler*>, DLListContainerBase<BaseSceneHandler*,
// BasicSlotPool<DLListEntry<BaseSceneHandler*>>>>(DLListEntry<BaseSceneHandler*>*, DLListContainerBase<BaseSceneHandler*,
// BasicSlotPool<DLListEntry<BaseSceneHandler*>>>*, void (DLListContainerBase<BaseSceneHandler*,
// BasicSlotPool<DLListEntry<BaseSceneHandler*>>>
// {
// public:
//     void *)(DLListEntry<BaseSceneHandler*>*));
// };

// class nlWalkDLRing<DLListEntry<PackagePushPopMessage*>, DLListContainerBase<PackagePushPopMessage*,
// BasicSlotPool<DLListEntry<PackagePushPopMessage*>>>>(DLListEntry<PackagePushPopMessage*>*, DLListContainerBase<PackagePushPopMessage*,
// BasicSlotPool<DLListEntry<PackagePushPopMessage*>>>*, void (DLListContainerBase<PackagePushPopMessage*,
// BasicSlotPool<DLListEntry<PackagePushPopMessage*>>>
// {
// public:
//     void *)(DLListEntry<PackagePushPopMessage*>*));
// };

// class nlWalkRing<DLListEntry<BaseSceneHandler*>, DLListContainerBase<BaseSceneHandler*,
// BasicSlotPool<DLListEntry<BaseSceneHandler*>>>>(DLListEntry<BaseSceneHandler*>*, DLListContainerBase<BaseSceneHandler*,
// BasicSlotPool<DLListEntry<BaseSceneHandler*>>>*, void (DLListContainerBase<BaseSceneHandler*,
// BasicSlotPool<DLListEntry<BaseSceneHandler*>>>
// {
// public:
//     void *)(DLListEntry<BaseSceneHandler*>*));
// };

// class nlWalkRing<DLListEntry<PackagePushPopMessage*>, DLListContainerBase<PackagePushPopMessage*,
// BasicSlotPool<DLListEntry<PackagePushPopMessage*>>>>(DLListEntry<PackagePushPopMessage*>*, DLListContainerBase<PackagePushPopMessage*,
// BasicSlotPool<DLListEntry<PackagePushPopMessage*>>>*, void (DLListContainerBase<PackagePushPopMessage*,
// BasicSlotPool<DLListEntry<PackagePushPopMessage*>>>
// {
// public:
//     void *)(DLListEntry<PackagePushPopMessage*>*));
// };

#endif // _FESCENEMANAGER_H_
