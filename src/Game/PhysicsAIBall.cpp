#include "Game/Physics/PhysicsAIBall.h"
#include "Game/Ball.h"

extern CollisionSpace* g_CollisionSpace;
extern PhysicsWorld* g_PhysicsWorld;

/**
 * Offset/Address/Size: 0x0 | 0x80133A34 | size: 0x84
 */
bool PhysicsAIBall::IsBallOutsideNet(const nlVector3&)
{
    FORCE_DONT_INLINE;
    float dVar2 = g_pBall->m_pPhysicsBall->GetRadius();
    return false;
}

/**
 * Offset/Address/Size: 0x84 | 0x80133AB8 | size: 0x1A0
 */
bool PhysicsAIBall::DidBallJustEnterNet(const nlVector3&, nlVector3)
{
    FORCE_DONT_INLINE;
    return false;
}

/**
 * Offset/Address/Size: 0x224 | 0x80133C58 | size: 0x310
 */
bool PhysicsAIBall::CheckIfBallWentThroughGoalPost()
{
    FORCE_DONT_INLINE;
    return false;
}

/**
 * Offset/Address/Size: 0x534 | 0x80133F68 | size: 0x460
 */
bool PhysicsAIBall::CheckIfBallWentThroughGoalie()
{
    FORCE_DONT_INLINE;
    return false;
}

/**
 * Offset/Address/Size: 0x994 | 0x801343C8 | size: 0x3A4
 */
void PhysicsAIBall::PostUpdate()
{
}

/**
 * Offset/Address/Size: 0xD38 | 0x8013476C | size: 0x4C
 */
void PhysicsAIBall::PreUpdate()
{
}

/**
 * Offset/Address/Size: 0xD84 | 0x801347B8 | size: 0x47C
 */
ContactType PhysicsAIBall::Contact(PhysicsObject*, dContact*, int)
{
    return NO_CONTACT;
}

/**
 * Offset/Address/Size: 0x1200 | 0x80134C34 | size: 0x68
 */
PhysicsAIBall::PhysicsAIBall(float radius)
    : PhysicsBall(g_CollisionSpace, g_PhysicsWorld, radius)
{
    m_pAIBall = NULL;
    m_unk_0x50 = 9999;
    m_unk_0x58 = false;
    m_unk_0x44.f.x = 0.f;
    m_unk_0x44.f.y = 0.f;
    m_unk_0x44.f.z = 0.f;
}
