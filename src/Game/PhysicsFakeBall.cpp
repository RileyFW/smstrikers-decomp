#include "Game/Physics/PhysicsFakeBall.h"
#include "Game/Physics/PhysicsPlane.h"

/**
 * Offset/Address/Size: 0x60 | 0x8013744C | size: 0x38
 */
int FakePhysicsBall::Contact(PhysicsObject* object, dContact* contact, int arg)
{
    if ((u8) * ((u8*)m_unk_0x40 + 0x18) != 0)
    {
        return 0;
    }
    return PhysicsBall::Contact(object, contact, arg);
}

/**
 * Offset/Address/Size: 0x98 | 0x80137484 | size: 0x3EC
 */
void FakeBallWorld::FindBallIntercept(const nlVector3&, float, float, nlVector3&, nlVector3&, float&, float&, float)
{
}

/**
 * Offset/Address/Size: 0x484 | 0x80137870 | size: 0x1E4
 */
void FakeBallWorld::GetNextBallPosition(nlVector3&)
{
}

/**
 * Offset/Address/Size: 0x668 | 0x80137A54 | size: 0xC8
 */
void FakeBallWorld::ResetBallIterator()
{
}

/**
 * Offset/Address/Size: 0x730 | 0x80137B1C | size: 0x80
 */
FakePhysicsBall::~FakePhysicsBall()
{
}

/**
 * Offset/Address/Size: 0x7B0 | 0x80137B9C | size: 0x600
 */
void FakeBallWorld::GetPredictedPosAtDistance(float, nlVector3&, nlVector3&)
{
}

/**
 * Offset/Address/Size: 0xDB0 | 0x8013819C | size: 0x3FC
 */
void FakeBallWorld::GetPredictedHeightLimitTime(float, float, nlVector3&, nlVector3&, bool)
{
}

/**
 * Offset/Address/Size: 0x11AC | 0x80138598 | size: 0x5BC
 */
void FakeBallWorld::GetPredictedPlaneIntersectTime(const nlVector4&, nlVector3&, nlVector3&)
{
}

/**
 * Offset/Address/Size: 0x1768 | 0x80138B54 | size: 0x6C0
 */
void FakeBallWorld::GetPredictedBallPosition(float, nlVector3&, nlVector3&)
{
}

/**
 * Offset/Address/Size: 0x1E28 | 0x80139214 | size: 0xEC
 */
void FakeBallWorld::InvalidateBallCache()
{
}

/**
 * Offset/Address/Size: 0x1F14 | 0x80139300 | size: 0x198
 */
void FakeBallWorld::Destroy()
{
}

/**
 * Offset/Address/Size: 0x20AC | 0x80139498 | size: 0x1D8
 */
void FakeBallWorld::Init(cBall*)
{
}

/**
 * Offset/Address/Size: 0x0 | 0x80139670 | size: 0x8
 */
int FakePhysicsBall::GetObjectType() const
{
    return 0x10;
}

/**
 * Offset/Address/Size: 0x0 | 0x80139678 | size: 0x8
 */
int PhysicsPlane::GetObjectType() const
{
    return 0x6;
}

/**
 * Offset/Address/Size: 0x0 | 0x80139680 | size: 0x10
 */
// void DLListContainerBase<BallCacheInfo*, BasicSlotPool<DLListEntry<BallCacheInfo*>>>::DeleteEntry(DLListEntry<BallCacheInfo*>*)
// {
// }

/**
 * Offset/Address/Size: 0x0 | 0x80139690 | size: 0x3C
 */
// void nlWalkDLRing<DLListEntry<BallCacheInfo*>, DLListContainerBase<BallCacheInfo*,
// BasicSlotPool<DLListEntry<BallCacheInfo*>>>>(DLListEntry<BallCacheInfo*>*, DLListContainerBase<BallCacheInfo*,
// BasicSlotPool<DLListEntry<BallCacheInfo*>>>*, void (DLListContainerBase<BallCacheInfo*,
// BasicSlotPool<DLListEntry<BallCacheInfo*>>>::*)(DLListEntry<BallCacheInfo*>*))
// {
// }

/**
 * Offset/Address/Size: 0x3C | 0x801396CC | size: 0x38
 */
// void nlDLRingRemoveStart<DLListEntry<BallCacheInfo*>>(DLListEntry<BallCacheInfo*>**)
// {
// }

/**
 * Offset/Address/Size: 0x74 | 0x80139704 | size: 0x24
 */
// void nlDLRingIsStart<DLListEntry<BallCacheInfo*>>(DLListEntry<BallCacheInfo*>*, DLListEntry<BallCacheInfo*>*)
// {
// }

/**
 * Offset/Address/Size: 0x98 | 0x80139728 | size: 0x20
 */
// void nlDLRingIsEnd<DLListEntry<BallCacheInfo*>>(DLListEntry<BallCacheInfo*>*, DLListEntry<BallCacheInfo*>*)
// {
// }

/**
 * Offset/Address/Size: 0xB8 | 0x80139748 | size: 0x10
 */
// void nlDLRingGetEnd<DLListEntry<BallCacheInfo*>>(DLListEntry<BallCacheInfo*>*)
// {
// }

/**
 * Offset/Address/Size: 0xC8 | 0x80139758 | size: 0x18
 */
// void nlDLRingGetStart<DLListEntry<BallCacheInfo*>>(DLListEntry<BallCacheInfo*>*)
// {
// }

/**
 * Offset/Address/Size: 0xE0 | 0x80139770 | size: 0x44
 */
// void nlDLRingRemove<DLListEntry<BallCacheInfo*>>(DLListEntry<BallCacheInfo*>**, DLListEntry<BallCacheInfo*>*)
// {
// }

/**
 * Offset/Address/Size: 0x124 | 0x801397B4 | size: 0x3C
 */
// void nlDLRingAddEnd<DLListEntry<BallCacheInfo*>>(DLListEntry<BallCacheInfo*>**, DLListEntry<BallCacheInfo*>*)
// {
// }

/**
 * Offset/Address/Size: 0x160 | 0x801397F0 | size: 0x38
 */
// void nlDLRingAddStart<DLListEntry<BallCacheInfo*>>(DLListEntry<BallCacheInfo*>**, DLListEntry<BallCacheInfo*>*)
// {
// }

/**
 * Offset/Address/Size: 0x0 | 0x80139828 | size: 0x60
 */
// void nlWalkRing<DLListEntry<BallCacheInfo*>, DLListContainerBase<BallCacheInfo*,
// BasicSlotPool<DLListEntry<BallCacheInfo*>>>>(DLListEntry<BallCacheInfo*>*, DLListContainerBase<BallCacheInfo*,
// BasicSlotPool<DLListEntry<BallCacheInfo*>>>*, void (DLListContainerBase<BallCacheInfo*,
// BasicSlotPool<DLListEntry<BallCacheInfo*>>>::*)(DLListEntry<BallCacheInfo*>*))
// {
// }

/**
 * Offset/Address/Size: 0x12C | 0x80139954 | size: 0xC8
 */
// void nlDLListSlotPool<BallCacheInfo*>::~nlDLListSlotPool()
// {
// }

/**
 * Offset/Address/Size: 0x0 | 0x80139A1C | size: 0x64
 */
// void SlotPool<BallCacheInfo>::~SlotPool()
// {
// }
