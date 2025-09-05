#ifndef _PHYSICSFAKEBALL_H_
#define _PHYSICSFAKEBALL_H_

#include "Game/Ball.h"
#include "Game/Physics/PhysicsBall.h"

// void nlDLRingRemoveStart<DLListEntry<BallCacheInfo*>>(DLListEntry<BallCacheInfo*>**);
// void nlDLRingIsStart<DLListEntry<BallCacheInfo*>>(DLListEntry<BallCacheInfo*>*, DLListEntry<BallCacheInfo*>*);
// void nlDLRingIsEnd<DLListEntry<BallCacheInfo*>>(DLListEntry<BallCacheInfo*>*, DLListEntry<BallCacheInfo*>*);
// void nlDLRingGetEnd<DLListEntry<BallCacheInfo*>>(DLListEntry<BallCacheInfo*>*);
// void nlDLRingGetStart<DLListEntry<BallCacheInfo*>>(DLListEntry<BallCacheInfo*>*);
// void nlDLRingRemove<DLListEntry<BallCacheInfo*>>(DLListEntry<BallCacheInfo*>**, DLListEntry<BallCacheInfo*>*);
// void nlDLRingAddEnd<DLListEntry<BallCacheInfo*>>(DLListEntry<BallCacheInfo*>**, DLListEntry<BallCacheInfo*>*);
// void nlDLRingAddStart<DLListEntry<BallCacheInfo*>>(DLListEntry<BallCacheInfo*>**, DLListEntry<BallCacheInfo*>*);

class FakePhysicsBall : public PhysicsBall
{
public:
    virtual int Contact(PhysicsObject*, dContact*, int);
    virtual ~FakePhysicsBall();
    virtual int GetObjectType() const;
};

class FakeBallWorld
{
public:
    void FindBallIntercept(const nlVector3&, float, float, nlVector3&, nlVector3&, float&, float&, float);
    void GetNextBallPosition(nlVector3&);
    void ResetBallIterator();
    void GetPredictedPosAtDistance(float, nlVector3&, nlVector3&);
    void GetPredictedHeightLimitTime(float, float, nlVector3&, nlVector3&, bool);
    void GetPredictedPlaneIntersectTime(const nlVector4&, nlVector3&, nlVector3&);
    void GetPredictedBallPosition(float, nlVector3&, nlVector3&);
    static void InvalidateBallCache();
    void Destroy();
    void Init(cBall*);
};

// class DLListContainerBase<BallCacheInfo*, BasicSlotPool<DLListEntry<BallCacheInfo*>>>
// {
// public:
//     void DeleteEntry(DLListEntry<BallCacheInfo*>*);
// };

// class nlWalkDLRing<DLListEntry<BallCacheInfo*>, DLListContainerBase<BallCacheInfo*, BasicSlotPool<DLListEntry<BallCacheInfo*>>>>(DLListEntry<BallCacheInfo*>*, DLListContainerBase<BallCacheInfo*, BasicSlotPool<DLListEntry<BallCacheInfo*>>>*, void (DLListContainerBase<BallCacheInfo*, BasicSlotPool<DLListEntry<BallCacheInfo*>>>
// {
// public:
//     void *)(DLListEntry<BallCacheInfo*>*));
// };

// class nlWalkRing<DLListEntry<BallCacheInfo*>, DLListContainerBase<BallCacheInfo*, BasicSlotPool<DLListEntry<BallCacheInfo*>>>>(DLListEntry<BallCacheInfo*>*, DLListContainerBase<BallCacheInfo*, BasicSlotPool<DLListEntry<BallCacheInfo*>>>*, void (DLListContainerBase<BallCacheInfo*, BasicSlotPool<DLListEntry<BallCacheInfo*>>>
// {
// public:
//     void *)(DLListEntry<BallCacheInfo*>*));
// };

// class nlDLListSlotPool<BallCacheInfo*>
// {
// public:
//     void ~nlDLListSlotPool();
// };

// class SlotPool<BallCacheInfo>
// {
// public:
//     void ~SlotPool();
// };

#endif // _PHYSICSFAKEBALL_H_
