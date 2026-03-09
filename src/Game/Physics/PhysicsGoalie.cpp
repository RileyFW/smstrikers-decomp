#include "Game/Physics/PhysicsGoalie.h"
#include "Game/Physics/PhysicsBall.h"
#include "Game/FixedUpdateTask.h"
#include "NL/utility.h"
#include "types.h"

f32 CANT_COLLIDE = *(f32*)__float_max;

float ballMaxMotionPerTick = PhysicsBall::GetBallMaxVelocity() * FixedUpdateTask::GetPhysicsUpdateTick();

/**
 * Offset / Address / Size : 0x8F0 | 0x8013A370 | size : 0x34
 */
void PhysicsGoalie::PostUpdate()
{
    PhysicsCharacter::PostUpdate();
    CollideGoalieWithPost();
}

/**
 * Offset/Address/Size: 0x780 | 0x8013A200 | size: 0x170
 */
bool PhysicsGoalie::SweepTestForBallContact(const nlVector3& ballPrevPosition, const nlVector3& ballCurrentPosition, const nlVector3& velocity, float ballRadius, nlVector3& outContactPos, nlVector3& outContactNormal) const
{
    int testsPassed = 0;
    float goalieRadius = 4.0f * m_CentreOfMassHeight;

    nlVector3 goaliePos;
    GetPosition(&goaliePos);
    goaliePos.f.z = (2.0 * m_CentreOfMassHeight) + goaliePos.f.z;

    nlVector3 tmp;
    nlVec3Set(tmp, ballPrevPosition.f.x - goaliePos.f.x, ballPrevPosition.f.y - goaliePos.f.y, ballPrevPosition.f.z - goaliePos.f.z);

    if ((nlSqrt((tmp.f.x * tmp.f.x) + (tmp.f.y * tmp.f.y) + (tmp.f.z * tmp.f.z), true) - (goalieRadius + (ballRadius + ballMaxMotionPerTick))) <= 0.0f)
    {
        testsPassed = 1;
        float temp_f1_2 = SweepSpheres(ballRadius, ballPrevPosition, ballCurrentPosition, goalieRadius, goaliePos, goaliePos);

        bool isValidSweep = false;
        if ((temp_f1_2 == CANT_COLLIDE) || (temp_f1_2 < 0.0f) || (temp_f1_2 > 1.0f))
        {
            isValidSweep = 0;
        }
        else
        {
            isValidSweep = 1;
        }

        if (isValidSweep != 0)
        {
            testsPassed = 2;
            if (SweepTestEveryBone(ballRadius, ballPrevPosition, ballCurrentPosition, outContactNormal, outContactPos) != 0)
            {
                testsPassed = 3;
            }
        }
    }

    return testsPassed == 3;
}

/**
 * Offset/Address/Size: 0x4A8 | 0x80139F28 | size: 0x2D8
 */
bool PhysicsGoalie::SweepTestEveryBone(float, const nlVector3&, const nlVector3&, nlVector3&, nlVector3&) const
{
    FORCE_DONT_INLINE;
    return false;
}

/**
 * Offset/Address/Size: 0x70 | 0x80139AF0 | size: 0x438
 */
void PhysicsGoalie::CollideGoalieWithPost()
{
    FORCE_DONT_INLINE;
}
