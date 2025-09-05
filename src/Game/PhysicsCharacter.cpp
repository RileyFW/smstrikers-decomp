#include "Game/Physics/PhysicsCharacter.h"

extern CollisionSpace* g_CollisionSpace;
extern PhysicsWorld* g_PhysicsWorld;

/**
 * Offset/Address/Size: 0x0 | 0x80136218 | size: 0x3C
 */
void PhysicsCharacter::SetCharacterVelocityXY(const nlVector3&)
{
}

/**
 * Offset/Address/Size: 0x3C | 0x80136254 | size: 0x44
 */
void PhysicsCharacter::GetCharacterVelocityXY(nlVector3*)
{
}

/**
 * Offset/Address/Size: 0x80 | 0x80136298 | size: 0x3C
 */
void PhysicsCharacter::SetCharacterPositionXY(const nlVector3&)
{
}

/**
 * Offset/Address/Size: 0xBC | 0x801362D4 | size: 0x44
 */
void PhysicsCharacter::GetCharacterPositionXY(nlVector3*)
{
}

/**
 * Offset/Address/Size: 0x100 | 0x80136318 | size: 0x608
 */
void PhysicsCharacter::PostUpdate()
{
}

/**
 * Offset/Address/Size: 0x708 | 0x80136920 | size: 0x384
 */
void PhysicsCharacter::ResolvePhysicsBoneIDFromName(const char*)
{
}

/**
 * Offset/Address/Size: 0xA8C | 0x80136CA4 | size: 0x98
 */
int PhysicsCharacter::PreCollide()
{
    return 0;
}

/**
 * Offset/Address/Size: 0xB24 | 0x80136D3C | size: 0x518
 */
int PhysicsCharacter::Contact(PhysicsObject*, dContact*, int, PhysicsObject*)
{
    return 0;
}

/**
 * Offset/Address/Size: 0x103C | 0x80137254 | size: 0x70
 */
int PhysicsCharacter::SetContactInfo(dContact*, PhysicsObject*, bool)
{
    return 0;
}

/**
 * Offset/Address/Size: 0x10AC | 0x801372C4 | size: 0x24
 */
void PhysicsCharacter::GetRadius(float*)
{
}

/**
 * Offset/Address/Size: 0x10D0 | 0x801372E8 | size: 0xFC
 */
PhysicsCharacter::PhysicsCharacter(float arg0, float arg1)
    : PhysicsCharacterBase(g_CollisionSpace, g_PhysicsWorld, arg0)
{
}

/**
 * Offset/Address/Size: 0x0 | 0x801373E4 | size: 0x8
 */
int PhysicsCharacter::GetObjectType() const
{
    return 0x08;
}
