#include "Game/Physics/PhysicsShell.h"

extern CollisionSpace* g_CollisionSpace;
extern PhysicsWorld* g_PhysicsWorld;

/**
 * Offset/Address/Size: 0x0 | 0x8013B968 | size: 0x94
 */
BOOL PhysicsShell::SetContactInfo(dContact*, PhysicsObject*, bool)
{
    return FALSE;
}

/**
 * Offset/Address/Size: 0x94 | 0x8013B9FC | size: 0x78
 */
void PhysicsShell::PostUpdate()
{
}

/**
 * Offset/Address/Size: 0x10C | 0x8013BA74 | size: 0x898
 */
int PhysicsShell::Contact(PhysicsObject*, dContact*, int)
{
    return 0;
}

/**
 * Offset/Address/Size: 0x9A4 | 0x8013C30C | size: 0x7C
 */
PhysicsShell::PhysicsShell(float radius)
    : PhysicsSphere(g_CollisionSpace, g_PhysicsWorld, radius)
{

    m_unk_0x2c = 0;
    m_unk_0x30 = 0;
    m_unk_0x34 = 0;
    m_unk_0x38 = 0;
    m_unk_0x39 = 0;
    SetCollide(0xef);
    SetCategory(0x20);
    m_gravity = -32.f;
}

/**
 * Offset/Address/Size: 0x0 | 0x8013C388 | size: 0x8
 */
int PhysicsShell::GetObjectType() const
{
    return 0x13;
}
