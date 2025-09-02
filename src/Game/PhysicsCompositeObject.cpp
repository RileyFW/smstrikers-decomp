#include "PhysicsCompositeObject.h"

#include "PhysicsWorld.h"
#include "Game/Physics/PhysicsObject.h"

/**
 * Offset/Address/Size: 0x0 | 0x801FF6A8 | size: 0xA8
 */
void PhysicsCompositeObject::AdjustTransform(int, nlMatrix4&)
{
}

/**
 * Offset/Address/Size: 0xA8 | 0x801FF750 | size: 0xBC
 */
void PhysicsCompositeObject::AddObject(PhysicsObject*)
{
}

/**
 * Offset/Address/Size: 0x164 | 0x801FF80C | size: 0x110
 */
PhysicsCompositeObject::~PhysicsCompositeObject()
{
}

/**
 * Offset/Address/Size: 0x274 | 0x801FF91C | size: 0x54
 */
PhysicsCompositeObject::PhysicsCompositeObject(PhysicsWorld* physicsWorld)
    : PhysicsObject(physicsWorld)
{
}

/**
 * Offset/Address/Size: 0x0 | 0x801FF970 | size: 0x8
 */
int PhysicsCompositeObject::GetObjectType() const
{
    return 0x9;
}

// /**
//  * Offset/Address/Size: 0x0 | 0x801FF978 | size: 0x24
//  */
// void DLListContainerBase<PhysicsTransform*, NewAdapter<DLListEntry<PhysicsTransform*>>>::DeleteEntry(DLListEntry<PhysicsTransform*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x801FF99C | size: 0x3C
//  */
// void nlWalkDLRing<DLListEntry<PhysicsTransform*>, DLListContainerBase<PhysicsTransform*,
// NewAdapter<DLListEntry<PhysicsTransform*>>>>(DLListEntry<PhysicsTransform*>*, DLListContainerBase<PhysicsTransform*,
// NewAdapter<DLListEntry<PhysicsTransform*>>>*, void (DLListContainerBase<PhysicsTransform*,
// NewAdapter<DLListEntry<PhysicsTransform*>>>::*)(DLListEntry<PhysicsTransform*>*))
// {
// }

// /**
//  * Offset/Address/Size: 0x3C | 0x801FF9D8 | size: 0x20
//  */
// void nlDLRingIsEnd<DLListEntry<PhysicsTransform*>>(DLListEntry<PhysicsTransform*>*, DLListEntry<PhysicsTransform*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x5C | 0x801FF9F8 | size: 0x18
//  */
// void nlDLRingGetStart<DLListEntry<PhysicsTransform*>>(DLListEntry<PhysicsTransform*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x74 | 0x801FFA10 | size: 0x3C
//  */
// void nlDLRingAddEnd<DLListEntry<PhysicsTransform*>>(DLListEntry<PhysicsTransform*>**, DLListEntry<PhysicsTransform*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0xB0 | 0x801FFA4C | size: 0x38
//  */
// void nlDLRingAddStart<DLListEntry<PhysicsTransform*>>(DLListEntry<PhysicsTransform*>**, DLListEntry<PhysicsTransform*>*)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x801FFA84 | size: 0x60
//  */
// void nlWalkRing<DLListEntry<PhysicsTransform*>, DLListContainerBase<PhysicsTransform*,
// NewAdapter<DLListEntry<PhysicsTransform*>>>>(DLListEntry<PhysicsTransform*>*, DLListContainerBase<PhysicsTransform*,
// NewAdapter<DLListEntry<PhysicsTransform*>>>*, void (DLListContainerBase<PhysicsTransform*,
// NewAdapter<DLListEntry<PhysicsTransform*>>>::*)(DLListEntry<PhysicsTransform*>*))
// {
// }
