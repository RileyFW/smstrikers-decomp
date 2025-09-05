#include "Game/Physics/PhysicsWall.h"

/**
 * Offset/Address/Size: 0x0 | 0x8013C454 | size: 0x48
 */
PhysicsWall::PhysicsWall(CollisionSpace* collision_space, float a, float b, float c)
    : PhysicsPlane(collision_space, a, b, 0.f, -c)
{
}

// /**
//  * Offset/Address/Size: 0x0 | 0x8013C49C | size: 0x70
//  */
// PhysicsWall::~PhysicsWall()
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8013C50C | size: 0x8
//  */
// int PhysicsWall::GetObjectType() const
// {
//     return 0x19;
// }
