#ifndef _PHYSICS_H_
#define _PHYSICS_H_

#include "PhysicsWorld.h"
#include "Game/Physics/PhysicsObject.h"

#include "PhysicsRoundedCorner.h"

class LoadingManager;
class CharacterPhysicsData;
class LoadablePhysicsMesh;

void PhysicsUpdate(PhysicsWorld*, float);
void ODEFree(void*, unsigned long);
void ODERealloc(void*, unsigned long, unsigned long);
void ODEAlloc(unsigned long);

// void nlListAddEnd<ListEntry<PhysicsObject*>>(ListEntry<PhysicsObject*>**, ListEntry<PhysicsObject*>**, ListEntry<PhysicsObject*>*);

class PhysicsLoader
{
public:
    void DestroyPhysics();
    void ConstructStaticPhysicsPrimitives(CharacterPhysicsData*);
    void StartLoad(LoadingManager*);
};

// class PhysicsRoundedCorner : public PhysicsObject
// {
// public:
//     ~PhysicsRoundedCorner();
//     void GetObjectType() const;
// };

// class nlWalkList<ListEntry<LoadablePhysicsMesh*>, ListContainerBase<LoadablePhysicsMesh*, NewAdapter<ListEntry<LoadablePhysicsMesh*>>>>(ListEntry<LoadablePhysicsMesh*>*, ListContainerBase<LoadablePhysicsMesh*, NewAdapter<ListEntry<LoadablePhysicsMesh*>>>*, void (ListContainerBase<LoadablePhysicsMesh*, NewAdapter<ListEntry<LoadablePhysicsMesh*>>>
// {
// public:
//     void *)(ListEntry<LoadablePhysicsMesh*>*));
// };

// class nlWalkList<ListEntry<PhysicsObject*>, ListContainerBase<PhysicsObject*, NewAdapter<ListEntry<PhysicsObject*>>>>(ListEntry<PhysicsObject*>*, ListContainerBase<PhysicsObject*, NewAdapter<ListEntry<PhysicsObject*>>>*, void (ListContainerBase<PhysicsObject*, NewAdapter<ListEntry<PhysicsObject*>>>
// {
// public:
//     void *)(ListEntry<PhysicsObject*>*));
// };

// class ListContainerBase<PhysicsObject*, NewAdapter<ListEntry<PhysicsObject*>>>
// {
// public:
//     void DeleteEntry(ListEntry<PhysicsObject*>*);
// };

// class ListContainerBase<LoadablePhysicsMesh*, NewAdapter<ListEntry<LoadablePhysicsMesh*>>>
// {
// public:
//     void DeleteEntry(ListEntry<LoadablePhysicsMesh*>*);
// };

// class nlListContainer<PhysicsObject*>
// {
// public:
//     void ~nlListContainer();
// };

// class cInventory<LoadablePhysicsMesh>
// {
// public:
//     void ~cInventory();
// };

#endif // _PHYSICS_H_
