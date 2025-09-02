#include "PhysicsGroundPlane.h"

#include "NL/nlMath.h"
#include "PhysicsPlane.h"

/**
 * Offset/Address/Size: 0x0 | 0x8013C390 | size: 0x4C
 */
PhysicsGroundPlane::PhysicsGroundPlane(CollisionSpace* collision_space)
    : PhysicsPlane(collision_space, 0.f, 0.f, 1.f, 0.f)
{
}

/**
 * Offset/Address/Size: 0x0 | 0x8013C3DC | size: 0x70
 */
// PhysicsGroundPlane::~PhysicsGroundPlane()
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8013C44C | size: 0x8
//  */
// int PhysicsGroundPlane::GetObjectType() const
// {
//     return 0x11;
// }
