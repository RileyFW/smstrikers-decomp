#include "Game/Physics/PhysicsShell.h"
#include "Game/Game.h"

extern CollisionSpace* g_CollisionSpace;
extern PhysicsWorld* g_PhysicsWorld;

/**
 * Offset/Address/Size: 0x0 | 0x8013B968 | size: 0x94
 */
bool PhysicsShell::SetContactInfo(dContact* contact, PhysicsObject* other, bool first)
{
    if (first)
    {
        SetDefaultContactInfo(contact);
    }

    if (other->GetObjectType() == 0x11)
    {
        contact->surface.bounce = g_pGame->m_pGameTweaks->fShellBounceGround;
    }
    else
    {
        contact->surface.bounce = g_pGame->m_pGameTweaks->fShellBounce;
    }

    contact->surface.bounce_vel = 5.0f;
    contact->surface.mu = 0.0f;

    return true;
}

/**
 * Offset/Address/Size: 0x94 | 0x8013B9FC | size: 0x78
 */
void PhysicsShell::PostUpdate()
{
    PhysicsObject::PostUpdate();

    nlVector3 velocity;
    GetLinearVelocity(&velocity);

    nlVector3& pos = GetPosition();
    if (pos.f.z > 20.0f && velocity.f.z > 0.0f)
    {
        velocity.f.z *= 0.9f;
        SetLinearVelocity(velocity);
    }
}

/**
 * Offset/Address/Size: 0x10C | 0x8013BA74 | size: 0x898
 */
ContactType PhysicsShell::Contact(PhysicsObject*, dContact*, int)
{
    return NO_CONTACT;
}

/**
 * Offset/Address/Size: 0x9A4 | 0x8013C30C | size: 0x7C
 */
PhysicsShell::PhysicsShell(float radius)
    : PhysicsSphere(g_CollisionSpace, g_PhysicsWorld, radius)
{

    m_pTriggerCallbackFunc = 0;
    m_pCallbackParam = 0;
    m_pPowerupObject = 0;
    mbIsInNet = false;
    m_bIsSupportedByGround = false;

    SetCollide(0xef);
    SetCategory(0x20);
    m_gravity = -32.f;
}
