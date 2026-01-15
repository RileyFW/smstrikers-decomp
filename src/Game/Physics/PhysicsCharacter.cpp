#include "Game/Physics/PhysicsCharacter.h"
#include "Game/Physics/PhysicsColumn.h"
#include "Game/Ball.h"
#include "NL/nlMemory.h"

extern CollisionSpace* g_CollisionSpace;
extern PhysicsWorld* g_PhysicsWorld;
extern cBall* g_pBall;

static bool sbDoDKBallStuckHack = true;
static float sfBallStuckHackShoveMagnitude = 10.0f;

#define SET_BIT(dest, src, shift, bit) \
    asm { rlwimi dest, src, shift, bit, bit }
/**
 * Offset/Address/Size: 0x10D0 | 0x801372E8 | size: 0xFC
 * TODO: this is a hack... should also work with the bitfields
 */
PhysicsCharacter::PhysicsCharacter(float radius, float heightScale)
    : PhysicsCharacterBase(g_CollisionSpace, g_PhysicsWorld, radius + (heightScale / 2.0f))
{
    register unsigned int flags;
    register int one = 1;

    unsigned int* flagsPtr = (unsigned int*)((char*)this + 0x80);

    flags = *flagsPtr;
    SET_BIT(flags, one, 31, 0);
    *flagsPtr = flags;

    flags = *flagsPtr;
    SET_BIT(flags, one, 30, 1);
    *flagsPtr = flags;

    flags = *flagsPtr;
    SET_BIT(flags, one, 28, 3);
    *flagsPtr = flags;

    // m_CanCollideWithWall = true;
    // m_CanCollideWithBall = true;
    // m_CanCollidedWithGoalLine = true;

    m_nDKBallStuckHackCounter = 0;
    m_pAICharacter = NULL;

    m_gravity = 0.0f;
    SetMass(17.5f);

    PhysicsColumn* column = (PhysicsColumn*)nlMalloc(0x30, 8, false);
    column = new (column) PhysicsColumn(g_CollisionSpace, g_PhysicsWorld, radius);
    m_pPlayerPlayerColumn = column;
    m_pPlayerPlayerColumn->SetCategory(0x40);
    m_pPlayerPlayerColumn->SetCollide(0x5F);
    AddObject(m_pPlayerPlayerColumn);
}

/**
 * Offset/Address/Size: 0x10AC | 0x801372C4 | size: 0x24
 */
void PhysicsCharacter::GetRadius(float* radius)
{
    m_pPlayerPlayerColumn->GetRadius(radius);
}

/**
 * Offset/Address/Size: 0x103C | 0x80137254 | size: 0x70
 */
bool PhysicsCharacter::SetContactInfo(dContact* contact, PhysicsObject* other, bool first)
{
    bool result = BaseSetContactInfo(contact, other, first);
    int objectType = other->GetObjectType();
    if (objectType == 0xF || objectType == 0x10)
    {
        contact->surface.bounce = 0.0f;
    }
    return result;
}

/**
 * Offset/Address/Size: 0xB24 | 0x80136D3C | size: 0x518
 */
ContactType PhysicsCharacter::Contact(PhysicsObject*, dContact*, int, PhysicsObject*)
{
    return NO_CONTACT;
}

/**
 * Offset/Address/Size: 0xA8C | 0x80136CA4 | size: 0x98
 */
void PhysicsCharacter::PreCollide()
{
    BasePreCollide();
    m_HasCollidedWithBall = 0;

    nlVector3 force = { 0.f, 0.0f, 0.0f };
    force.f.y = -sfBallStuckHackShoveMagnitude;

    if (sbDoDKBallStuckHack && m_nDKBallStuckHackCounter > 5)
    {
        g_pBall->m_pPhysicsBall->AddForceAtCentreOfMass(force);
    }
    m_unk88 = 0;
}

/**
 * Offset/Address/Size: 0x708 | 0x80136920 | size: 0x384
 */
void PhysicsCharacter::ResolvePhysicsBoneIDFromName(const char*)
{
}

/**
 * Offset/Address/Size: 0x100 | 0x80136318 | size: 0x608
 */
void PhysicsCharacter::PostUpdate()
{
}

/**
 * Offset/Address/Size: 0xBC | 0x801362D4 | size: 0x44
 */
void PhysicsCharacter::GetCharacterPositionXY(nlVector3* pos)
{
    float z = pos->f.z;
    GetPosition(pos);
    pos->f.z = z;
}

/**
 * Offset/Address/Size: 0x80 | 0x80136298 | size: 0x3C
 */
void PhysicsCharacter::SetCharacterPositionXY(const nlVector3& pos)
{
    nlVector3 v;
    v.f.x = pos.f.x;
    v.f.y = pos.f.y;
    v.f.z = 0.0f;
    SetCharacterPosition(v);
}

/**
 * Offset/Address/Size: 0x3C | 0x80136254 | size: 0x44
 */
void PhysicsCharacter::GetCharacterVelocityXY(nlVector3* vel)
{
    float z = vel->f.z;
    GetLinearVelocity(vel);
    vel->f.z = z;
}

/**
 * Offset/Address/Size: 0x0 | 0x80136218 | size: 0x3C
 */
void PhysicsCharacter::SetCharacterVelocityXY(const nlVector3& vel)
{
    nlVector3 v;
    v.f.x = vel.f.x;
    v.f.y = vel.f.y;
    v.f.z = 0.0f;
    SetLinearVelocity(v);
}
