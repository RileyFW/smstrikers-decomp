#include "Game/Physics/PhysicsAIBall.h"
#include "Game/Ball.h"
#include "Game/Field.h"

extern CollisionSpace* g_CollisionSpace;
extern PhysicsWorld* g_PhysicsWorld;

/**
 * Offset/Address/Size: 0x0 | 0x80133A34 | size: 0x84
 */
bool PhysicsAIBall::IsBallOutsideNet(const nlVector3& v3Pos)
{
    f32 radius = g_pBall->m_pPhysicsBall->GetRadius();
    f64 absX = (float)fabs(v3Pos.f.x);
    f32 threshold = cField::GetGoalLineX((unsigned int)1);
    f32 sum;
    f32 fAbsX;
    sum = radius + threshold;
    fAbsX = (f32)absX;
    threshold = sum - 0.2f;
    return fAbsX < threshold;
}

/**
 * Offset/Address/Size: 0x84 | 0x80133AB8 | size: 0x1A0
 */
bool PhysicsAIBall::DidBallJustEnterNet(const nlVector3& oldPos, nlVector3 newPos)
{
    f64 absOldX = (float)fabs(oldPos.f.x);
    f32 absNewX = (float)fabs(newPos.f.x);
    f32 radius = g_pBall->m_pPhysicsBall->GetRadius();
    f32 goalLineX = cField::GetGoalLineX((unsigned int)1);
    f32 threshold = (goalLineX + radius) - 0.2f;
    nlVector3 impactPos;

    if (((f32)absOldX < threshold) && (absNewX >= threshold))
    {
        f32 xDelta = newPos.f.x - oldPos.f.x;

        if ((float)fabs(xDelta) > 0.001f)
        {
            f32 planeX;
            if (newPos.f.x > 0.0f)
            {
                planeX = threshold;
            }
            else
            {
                planeX = -threshold;
            }

            f32 oldX = oldPos.f.x;
            f32 t = (planeX - oldX) / xDelta;
            xDelta = 1.0f - t;

            impactPos.f.x = (xDelta * oldX) + (t * newPos.f.x);
            impactPos.f.y = (xDelta * oldPos.f.y) + (t * newPos.f.y);
            impactPos.f.z = (xDelta * oldPos.f.z) + (t * newPos.f.z);
        }
        else
        {
            impactPos = newPos;
        }

        if ((impactPos.f.z > 0.0f) && (impactPos.f.z < cNet::m_fNetHeight))
        {
            f32 netWidth = cNet::m_fNetWidth;
            f32 halfScale = 0.5f;
            if ((impactPos.f.y > (halfScale * -netWidth)) && (impactPos.f.y < (halfScale * netWidth)))
            {
                return true;
            }
        }
    }

    /**
     * TODO: 97.40% match - function prologue keeps `mr r31, r4` before
     * first `lfs` instead of the target's interleaved argument save/load order.
     */
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
    PhysicsBall::PreUpdate();
    m_unk_0x44 = GetPosition();
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
