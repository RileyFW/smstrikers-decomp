#ifndef _PHYSICSCOMPOSITEOBJECT_H_
#define _PHYSICSCOMPOSITEOBJECT_H_

#include "NL/nlMath.h"
#include "Game/Physics/PhysicsObject.h"

// void nlDLRingIsEnd<DLListEntry<PhysicsTransform*>>(DLListEntry<PhysicsTransform*>*, DLListEntry<PhysicsTransform*>*);
// void nlDLRingGetStart<DLListEntry<PhysicsTransform*>>(DLListEntry<PhysicsTransform*>*);
// void nlDLRingAddEnd<DLListEntry<PhysicsTransform*>>(DLListEntry<PhysicsTransform*>**, DLListEntry<PhysicsTransform*>*);
// void nlDLRingAddStart<DLListEntry<PhysicsTransform*>>(DLListEntry<PhysicsTransform*>**, DLListEntry<PhysicsTransform*>*);

class PhysicsObject;
class PhysicsWorld;

class PhysicsCompositeObject : public PhysicsObject
{
public:
    PhysicsCompositeObject(PhysicsWorld*);
    virtual ~PhysicsCompositeObject();

    virtual int GetObjectType() const;

    void AdjustTransform(int, nlMatrix4&);
    void AddObject(PhysicsObject*);
};

// class DLListContainerBase<PhysicsTransform*, NewAdapter<DLListEntry<PhysicsTransform*>>>
// {
// public:
//     void DeleteEntry(DLListEntry<PhysicsTransform*>*);
// };

// class nlWalkDLRing<DLListEntry<PhysicsTransform*>, DLListContainerBase<PhysicsTransform*, NewAdapter<DLListEntry<PhysicsTransform*>>>>(DLListEntry<PhysicsTransform*>*, DLListContainerBase<PhysicsTransform*, NewAdapter<DLListEntry<PhysicsTransform*>>>*, void (DLListContainerBase<PhysicsTransform*, NewAdapter<DLListEntry<PhysicsTransform*>>>
// {
// public:
//     void *)(DLListEntry<PhysicsTransform*>*));
// };

// class nlWalkRing<DLListEntry<PhysicsTransform*>, DLListContainerBase<PhysicsTransform*, NewAdapter<DLListEntry<PhysicsTransform*>>>>(DLListEntry<PhysicsTransform*>*, DLListContainerBase<PhysicsTransform*, NewAdapter<DLListEntry<PhysicsTransform*>>>*, void (DLListContainerBase<PhysicsTransform*, NewAdapter<DLListEntry<PhysicsTransform*>>>
// {
// public:
//     void *)(DLListEntry<PhysicsTransform*>*));
// };

#endif // _PHYSICSCOMPOSITEOBJECT_H_
