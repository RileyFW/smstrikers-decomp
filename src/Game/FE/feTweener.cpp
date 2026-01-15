#include "Game/FE/feTweener.h"

/**
 * Offset/Address/Size: 0x0 | 0x800A2254 | size: 0x9C
 */
void FETweenManager::startTween(FETweener*)
{
}

/**
 * Offset/Address/Size: 0x9C | 0x800A22F0 | size: 0x104
 */
void FETweenManager::clearTweensOnObj(void*)
{
}

/**
 * Offset/Address/Size: 0x1A0 | 0x800A23F4 | size: 0xE8
 */
void FETweenManager::clearTweens()
{
}

/**
 * Offset/Address/Size: 0x288 | 0x800A24DC | size: 0x468
 */
void FETweenManager::Update(float)
{
}

/**
 * Offset/Address/Size: 0x6F0 | 0x800A2944 | size: 0x160
 */
FETweener* FETweenManager::createTween(float*, float*, float, float, unsigned char, float (*)(float, float, float, float), void*,
    void (*)(void*, const float*))
{
    return NULL;
}

/**
 * Offset/Address/Size: 0x850 | 0x800A2AA4 | size: 0x18C
 */
FETweenManager::~FETweenManager()
{
}

/**
 * Offset/Address/Size: 0x9DC | 0x800A2C30 | size: 0x9C
 */
FETweenManager::FETweenManager()
{
}

/**
 * Offset/Address/Size: 0xA78 | 0x800A2CCC | size: 0xC
 */
void FETweener::setDoneCallFunc(void (*doneFunc)(void*), void* doneFuncParam)
{
    m_doneFunc = doneFunc;
    m_doneFuncParam = doneFuncParam;
}

/**
 * Offset/Address/Size: 0xA84 | 0x800A2CD8 | size: 0x8
 */
void FETweener::setNextTween(FETweener* next)
{
    m_nextTween = next;
}

/**
 * Offset/Address/Size: 0xA8C | 0x800A2CE0 | size: 0x48
 */
FETweener::~FETweener()
{
}

// /**
//  * Offset/Address/Size: 0x0 | 0x800A2D28 | size: 0x10
//  */
// void DLListContainerBase<FETweener*, BasicSlotPool<DLListEntry<FETweener*>>>::DeleteEntry(DLListEntry<FETweener*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x800A2D38 | size: 0x3C
//  */
// void nlWalkDLRing<DLListEntry<FETweener*>, DLListContainerBase<FETweener*,
// BasicSlotPool<DLListEntry<FETweener*>>>>(DLListEntry<FETweener*>*, DLListContainerBase<FETweener*,
// BasicSlotPool<DLListEntry<FETweener*>>>*, void (DLListContainerBase<FETweener*,
// BasicSlotPool<DLListEntry<FETweener*>>>::*)(DLListEntry<FETweener*>*))
// {
// }

// /**
//  * Offset/Address/Size: 0x3C | 0x800A2D74 | size: 0x20
//  */
// void nlDLRingIsEnd<DLListEntry<FETweener*>>(DLListEntry<FETweener*>*, DLListEntry<FETweener*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x5C | 0x800A2D94 | size: 0x18
//  */
// void nlDLRingGetStart<DLListEntry<FETweener*>>(DLListEntry<FETweener*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x74 | 0x800A2DAC | size: 0x44
//  */
// void nlDLRingRemove<DLListEntry<FETweener*>>(DLListEntry<FETweener*>**, DLListEntry<FETweener*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0xB8 | 0x800A2DF0 | size: 0x3C
//  */
// void nlDLRingAddEnd<DLListEntry<FETweener*>>(DLListEntry<FETweener*>**, DLListEntry<FETweener*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0xF4 | 0x800A2E2C | size: 0x38
//  */
// void nlDLRingAddStart<DLListEntry<FETweener*>>(DLListEntry<FETweener*>**, DLListEntry<FETweener*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x800A2E64 | size: 0x60
//  */
// void nlWalkRing<DLListEntry<FETweener*>, DLListContainerBase<FETweener*,
// BasicSlotPool<DLListEntry<FETweener*>>>>(DLListEntry<FETweener*>*, DLListContainerBase<FETweener*,
// BasicSlotPool<DLListEntry<FETweener*>>>*, void (DLListContainerBase<FETweener*,
// BasicSlotPool<DLListEntry<FETweener*>>>::*)(DLListEntry<FETweener*>*))
// {
// }
