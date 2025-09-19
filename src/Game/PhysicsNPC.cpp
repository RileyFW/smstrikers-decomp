#include "Game/Physics/PhysicsNPC.h"

extern CollisionSpace* g_CollisionSpace;

/**
 * Offset/Address/Size: 0x440 | 0x8013B8F8 | size: 0x68
 */
PhysicsNPC::PhysicsNPC(float radius)
    : PhysicsSphere(g_CollisionSpace, (PhysicsWorld*)0, radius)
{
    mpTriggerCallbackFunc = NULL;
    mpAINPC = NULL;

    SetCollide(0x00);
    SetCategory(0xFF);
}

/**
 * Offset/Address/Size: 0x438 | 0x8013B8F0 | size: 0x8
 */
void PhysicsNPC::SetCallbackFunction(CallbackFn cb)
{
    mpTriggerCallbackFunc = cb;
}

/**
 * Offset/Address/Size: 0xC0 | 0x8013B578 | size: 0x378
 */
int PhysicsNPC::Contact(PhysicsObject* other, dContact* contact, int what)
{
    nlVector3 myPos;
    GetPosition(&myPos);

    switch (other->GetObjectType())
    {
    case 4:
    case 13:
    case 14:
    {
        // other->m_parentObject;
        // cPlayer* oPlayer = other->m_parentObject ? *(cPlayer**)((char*)p0C + 0x8C) : NULL;

        return 0;
    }
    case 15:
    {
        return 0;
    }
    case 19:
    {
        return 0;
    }
    case 20:
    {
        return 0;
    }
    }

    // TODO
    // class nlVector3 myPos; // r1+0x44
    // class cFielder * pFielder; // r28
    // unsigned char bDoCallback; // r27
    // class nlVector3 v3Pos; // r1+0x38
    // class nlVector3 v3Pos; // r1+0x2C
    // class nlVector3 v3Pos; // r1+0x20
    // class PhysicsShell * pShell; // r0
    // class nlVector3 v3Pos; // r1+0x14
    // class PhysicsBanana * pBanana; // r0
    // class nlVector3 v3Pos; // r1+0x8

    if (mpAINPC && mpAINPC->GetObjectType() == 4)
    {
        return 2;
    }

    return 0;
}

/**
 * Offset/Address/Size: 0x70 | 0x8013B528 | size: 0x50
 */
bool PhysicsNPC::SetContactInfo(dContact* contact, PhysicsObject* /*other*/, bool first)
{
    if (first)
    {
        SetDefaultContactInfo(contact);
    }

    contact->surface.bounce = 0.01f;
    contact->surface.bounce_vel = 0.0f;
    contact->surface.mu = 5.0f;

    return true;
}

// /**
//  * Offset/Address/Size: 0x0 | 0x8013B4B8 | size: 0x70
//  */
// PhysicsNPC::~PhysicsNPC()
// {
// }
