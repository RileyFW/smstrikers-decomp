#include "Game/Physics/PhysicsAIBall.h"
#include "Game/Ball.h"
#include "Game/Field.h"
#include "Game/FixedUpdateTask.h"
#include "Game/Physics/PhysicsFakeBall.h"
#include "Game/Physics/PhysicsNet.h"

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
 * TODO: 96.37% match - sweep-contact bool live range still spills through r0,
 * and FP register allocation differs slightly in the reflection math block.
 */
bool PhysicsAIBall::CheckIfBallWentThroughGoalPost()
{
    if (m_parentObject == NULL)
    {
        nlVector3 oldPosition;
        nlVector3 newPosition;

        GetPosition(&newPosition);
        oldPosition = m_unk_0x44;

        nlVector3 ballPosition = { 0.0f, 0.0f, 0.0f };
        nlVector3 contactNormal = { 0.0f, 0.0f, 0.0f };
        bool contact;
        PhysicsObject* physicsObject = NULL;
        nlVector3 v3ExitVel;
        nlVector3 v3AngVel;

        if (oldPosition.f.x > 0.0f)
        {
            PhysicsNet* pNet = PhysicsNet::spPhysNetPositiveX;
            float radius = GetRadius();
            contact = pNet->SweepTestForBallContact(oldPosition, newPosition, GetLinearVelocity(), radius, ballPosition, contactNormal, &physicsObject);
        }
        else
        {
            PhysicsNet* pNet = PhysicsNet::spPhysNetNegativeX;
            float radius = GetRadius();
            contact = pNet->SweepTestForBallContact(oldPosition, newPosition, GetLinearVelocity(), radius, ballPosition, contactNormal, &physicsObject);
        }

        if ((contact != 0) && (m_unk_0x59 == 0))
        {
            ballPosition.f.z = (0.005f * contactNormal.f.z) + ballPosition.f.z;
            ballPosition.f.y = (0.005f * contactNormal.f.y) + ballPosition.f.y;
            ballPosition.f.x = (0.005f * contactNormal.f.x) + ballPosition.f.x;

            const nlVector3& v3BallVel = GetLinearVelocity();
            float velY = v3BallVel.f.y;
            float normalY = contactNormal.f.y;
            float velX = v3BallVel.f.x;
            float velYSq = velY * velY;
            float velYNormalY = velY * normalY;
            float normalX = contactNormal.f.x;
            float normalYSq = normalY * normalY;
            float velZ = v3BallVel.f.z;
            float velXSq = velX * velX;
            float dotXY = (velX * normalX) + velYNormalY;
            float normalZ = contactNormal.f.z;
            float normalLenXY = (normalX * normalX) + normalYSq;
            float velZSq = velZ * velZ;
            float velDotNormal = (velZ * normalZ) + dotXY;
            float normalLengthSq = (normalZ * normalZ) + normalLenXY;
            float reflectScale = velDotNormal / normalLengthSq;

            v3ExitVel.f.x = (-2.0f * (reflectScale * normalX)) + velX;
            v3ExitVel.f.y = (-2.0f * (reflectScale * normalY)) + velY;
            v3ExitVel.f.z = (-2.0f * (reflectScale * normalZ)) + velZ;

            float velocitySq = velZSq + (velXSq + velYSq);

            v3ExitVel.f.x = 0.35f * v3ExitVel.f.x;
            v3ExitVel.f.y = 0.35f * v3ExitVel.f.y;
            v3ExitVel.f.z = 0.35f * v3ExitVel.f.z;

            if (velocitySq < 1.0f)
            {
                if (ballPosition.f.x > 0.0f)
                {
                    v3ExitVel.f.x = v3ExitVel.f.x - 0.3f;
                }
                else
                {
                    v3ExitVel.f.x = v3ExitVel.f.x + 0.3f;
                }

                float physicsTick = FixedUpdateTask::GetPhysicsUpdateTick();
                float dt = 0.3f * physicsTick;

                ballPosition.f.z = (dt * v3ExitVel.f.z) + ballPosition.f.z;
                ballPosition.f.y = (dt * v3ExitVel.f.y) + ballPosition.f.y;
                ballPosition.f.x = (dt * v3ExitVel.f.x) + ballPosition.f.x;
            }

            GetAngularVelocity(&v3AngVel);

            v3AngVel.f.z = 0.8f * v3AngVel.f.z;
            v3AngVel.f.x = 0.8f * v3AngVel.f.x;
            v3AngVel.f.y = 0.8f * v3AngVel.f.y;

            SetPosition(ballPosition, PhysicsObject::WORLD_COORDINATES);
            SetLinearVelocity(v3ExitVel);
            SetAngularVelocity(v3AngVel);

            m_bUseMagnusEffect = false;
            FakeBallWorld::InvalidateBallCache();

            m_pAIBall->m_bBallPathChangeCount += 1;
            m_pAIBall->m_unk_0xA6 = false;
            m_pAIBall->mpDamageTarget = NULL;
        }
    }
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
