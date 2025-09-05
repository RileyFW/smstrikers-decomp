#include "Game/Physics/PhysicsCharacterBase.h"

/**
 * Offset/Address/Size: 0x0 | 0x801FEAFC | size: 0x80
 */
void PhysicsCharacterBase::GetBoneIDForSubObject(const PhysicsObject*) const
{
}

/**
 * Offset/Address/Size: 0x80 | 0x801FEB7C | size: 0x280
 */
void PhysicsCharacterBase::AddBoneVolumes(PhysicsWorld*, CollisionSpace*, cPoseAccumulator*, const CharacterPhysicsData*, unsigned long,
    unsigned long)
{
}

/**
 * Offset/Address/Size: 0x300 | 0x801FEDFC | size: 0x160
 */
void PhysicsCharacterBase::UpdatePose(cPoseAccumulator*, float)
{
}

/**
 * Offset/Address/Size: 0x460 | 0x801FEF5C | size: 0x60
 */
void PhysicsCharacterBase::SetFacingDirection(unsigned short)
{
}

/**
 * Offset/Address/Size: 0x4C0 | 0x801FEFBC | size: 0x24
 */
void PhysicsCharacterBase::ReleaseObject()
{
}

/**
 * Offset/Address/Size: 0x4E4 | 0x801FEFE0 | size: 0x34
 */
void PhysicsCharacterBase::ContainObject(PhysicsObject*)
{
}

/**
 * Offset/Address/Size: 0x518 | 0x801FF014 | size: 0xC
 */
void PhysicsCharacterBase::BasePreCollide()
{
}

/**
 * Offset/Address/Size: 0x524 | 0x801FF020 | size: 0x130
 */
void PhysicsCharacterBase::BaseSetContactInfo(dContact*, PhysicsObject*, bool)
{
}

/**
 * Offset/Address/Size: 0x654 | 0x801FF150 | size: 0x48
 */
void PhysicsCharacterBase::SetCharacterPosition(const nlVector3&)
{
}

/**
 * Offset/Address/Size: 0x69C | 0x801FF198 | size: 0xE8
 */
PhysicsCharacterBase::~PhysicsCharacterBase()
{
}

/**
 * Offset/Address/Size: 0x784 | 0x801FF280 | size: 0xE0
 */
PhysicsCharacterBase::PhysicsCharacterBase(CollisionSpace* collisionSpace, PhysicsWorld* physicsWorld, float)
    : PhysicsCompositeObject(physicsWorld)
{
}

/**
 * Offset/Address/Size: 0x864 | 0x801FF360 | size: 0x16C
 */
void PhysicsCharacterBase::GetBoneVolumePoints(nlVector3*, bool)
{
}

/**
 * Offset/Address/Size: 0x9D0 | 0x801FF4CC | size: 0x30
 */
void PhysicsCharacterBase::GetNumBoneVolumePoints(bool) const
{
}

/**
 * Offset/Address/Size: 0x0 | 0x801FF4FC | size: 0x8
 */
int PhysicsCharacterBase::GetObjectType() const
{
    return 0x08;
}

/**
 * Offset/Address/Size: 0x8 | 0x801FF504 | size: 0x8
 */
// void PhysicsCharacterBase::PhysicsCapsuleBone::GetObjectType() const
// {
// }

/**
 * Offset/Address/Size: 0x10 | 0x801FF50C | size: 0x70
 */
// void PhysicsCharacterBase::PhysicsSphereBone::~PhysicsSphereBone()
// {
// }

/**
 * Offset/Address/Size: 0x80 | 0x801FF57C | size: 0x8
 */
// void PhysicsCharacterBase::PhysicsSphereBone::GetObjectType() const
// {
// }

/**
 * Offset/Address/Size: 0x0 | 0x801FF584 | size: 0x24
 */
// void ListContainerBase<PhysicsCharacterBase::PhysicsBoneVolume*, NewAdapter<ListEntry<PhysicsCharacterBase::PhysicsBoneVolume*>>>::
//     DeleteEntry(ListEntry<PhysicsCharacterBase::PhysicsBoneVolume*>*)
// {
// }

/**
 * Offset/Address/Size: 0x0 | 0x801FF5A8 | size: 0x70
 */
// void PhysicsCharacterBase::PhysicsCapsuleBone::~PhysicsCapsuleBone()
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x801FF618 | size: 0x68
//  */
// void nlWalkList<
//     ListEntry<PhysicsCharacterBase::PhysicsBoneVolume*>,
//     ListContainerBase<PhysicsCharacterBase::PhysicsBoneVolume*, NewAdapter<ListEntry<PhysicsCharacterBase::PhysicsBoneVolume*>>>>(
//     ListEntry<PhysicsCharacterBase::PhysicsBoneVolume*>*,
//     ListContainerBase<PhysicsCharacterBase::PhysicsBoneVolume*, NewAdapter<ListEntry<PhysicsCharacterBase::PhysicsBoneVolume*>>>*,
//     void (ListContainerBase<PhysicsCharacterBase::PhysicsBoneVolume*, NewAdapter<ListEntry<PhysicsCharacterBase::PhysicsBoneVolume*>>>::*)(
//         ListEntry<PhysicsCharacterBase::PhysicsBoneVolume*>*))
// {
// }

// /**
//  * Offset/Address/Size: 0x68 | 0x801FF680 | size: 0x28
//  */
// void nlListAddStart<ListEntry<PhysicsCharacterBase::PhysicsBoneVolume*>>(ListEntry<PhysicsCharacterBase::PhysicsBoneVolume*>**,
//                                                                          ListEntry<PhysicsCharacterBase::PhysicsBoneVolume*>*,
//                                                                          ListEntry<PhysicsCharacterBase::PhysicsBoneVolume*>**)
// {
// }
