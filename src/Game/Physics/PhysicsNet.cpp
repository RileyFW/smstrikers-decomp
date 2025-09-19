#include "Game/Physics/PhysicsNet.h"

/**
 * Offset/Address/Size: 0x9A8 | 0x8013AD98 | size: 0x6F8
 */
PhysicsNet::PhysicsNet(CollisionSpace*, bool)
{
}

/**
 * Offset/Address/Size: 0x7BC | 0x8013ABAC | size: 0x12C
 */
PhysicsNet::~PhysicsNet()
{
}

/**
 * Offset/Address/Size: 0x75C | 0x8013AB4C | size: 0x60
 */
void PhysicsNet::IsAGoalPost(PhysicsObject*)
{
}

/**
 * Offset/Address/Size: 0x6FC | 0x8013AAEC | size: 0x60
 */
void PhysicsNet::IsAGoalWall(PhysicsObject*)
{
}

/**
 * Offset/Address/Size: 0xD0 | 0x8013A4C0 | size: 0x62C
 */
void PhysicsNet::SweepTestForBallContact(const nlVector3&, const nlVector3&, const nlVector3&, float, nlVector3&, nlVector3&, PhysicsObject**) const
{
}

/**
 * Offset/Address/Size: 0x5C | 0x8013A44C | size: 0x74
 */
void PhysicsNet::StaticInit(CollisionSpace*)
{
}

/**
 * Offset/Address/Size: 0x0 | 0x8013A3F0 | size: 0x5C
 */
void PhysicsNet::StaticDestroy()
{
}
