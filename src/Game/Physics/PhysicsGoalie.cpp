#include "Game/Physics/PhysicsGoalie.h"

/**
 * Offset/Address/Size: 0x8F0 | 0x8013A370 | size: 0x34
 */
void PhysicsGoalie::PostUpdate()
{
}

/**
 * Offset/Address/Size: 0x780 | 0x8013A200 | size: 0x170
 */
void PhysicsGoalie::SweepTestForBallContact(const nlVector3&, const nlVector3&, const nlVector3&, float, nlVector3&, nlVector3&) const
{
}

/**
 * Offset/Address/Size: 0x4A8 | 0x80139F28 | size: 0x2D8
 */
void PhysicsGoalie::SweepTestEveryBone(float, const nlVector3&, const nlVector3&, nlVector3&, nlVector3&) const
{
}

/**
 * Offset/Address/Size: 0x70 | 0x80139AF0 | size: 0x438
 */
void PhysicsGoalie::CollideGoalieWithPost()
{
}

/**
 * Offset/Address/Size: 0x0 | 0x80139A80 | size: 0x70
 */
PhysicsGoalie::~PhysicsGoalie()
{
}
