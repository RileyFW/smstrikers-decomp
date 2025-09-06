#include "Game/Physics/PhysicsAIBall.h"
#include "Game/Ball.h"

extern CollisionSpace* g_CollisionSpace;
extern PhysicsWorld* g_PhysicsWorld;

/**
 * Offset/Address/Size: 0x0 | 0x80133A34 | size: 0x84
 */
void PhysicsAIBall::IsBallOutsideNet(const nlVector3&)
{

    // uint extraout_r4;
    // undefined4 uVar1;
    float dVar2;
    // double dVar3;
    // undefined8 in_f30;
    float dVar4;
    // undefined8 in_f31;
    // undefined1 auStack_18[16];
    // undefined1 auStack_8[8];

    // uVar1 = 0;
    // __psq_st0(auStack_8, (int)((ulonglong)in_f31 >> 0x20), 0);
    // __psq_st1(auStack_8, (int)in_f31, 0);
    // __psq_st0(auStack_18, (int)((ulonglong)in_f30 >> 0x20), 0);
    // __psq_st1(auStack_18, (int)in_f30, 0);

    dVar2 = g_pBall->m_pPhysicsBall->GetRadius();

    // dVar2 = (double)PhysicsSphere::GetRadius(*(PhysicsSphere**)(Ball::g_pBall + 0x38));
    // dVar4 = ABS((double)*(float*)this);
    // dVar3 = (double)cField::GetGoalLineX((cField*)0x1, extraout_r4);
    // __psq_l0(auStack_8, uVar1);
    // __psq_l1(auStack_8, uVar1);
    // __psq_l0(auStack_18, uVar1);
    // __psq_l1(auStack_18, uVar1);
    // return ((uint)(byte)(((float)dVar4 < (float)(dVar2 + dVar3) - @875) << 3) << 0x1c) >> 0x1f;
}

/**
 * Offset/Address/Size: 0x84 | 0x80133AB8 | size: 0x1A0
 */
void PhysicsAIBall::DidBallJustEnterNet(const nlVector3&, nlVector3)
{
}

/**
 * Offset/Address/Size: 0x224 | 0x80133C58 | size: 0x310
 */
void PhysicsAIBall::CheckIfBallWentThroughGoalPost()
{
}

/**
 * Offset/Address/Size: 0x534 | 0x80133F68 | size: 0x460
 */
void PhysicsAIBall::CheckIfBallWentThroughGoalie()
{
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
int PhysicsAIBall::Contact(PhysicsObject*, dContact*, int)
{
    return 0;
}

/**
 * Offset/Address/Size: 0x1200 | 0x80134C34 | size: 0x68
 */
PhysicsAIBall::PhysicsAIBall(float radius)
    : PhysicsBall(g_CollisionSpace, g_PhysicsWorld, radius)
{
    m_unk_0x40 = 0;
    m_unk_0x50 = 9999;
    m_unk_0x58 = 0;
    m_unk_0x44.f.x = 0.f;
    m_unk_0x44.f.y = 0.f;
    m_unk_0x44.f.z = 0.f;
}

/**
 * Offset/Address/Size: 0x1268 | 0x80134C9C | size: 0x70
 */
PhysicsBall::~PhysicsBall()
{
}

/**
 * Offset/Address/Size: 0x0 | 0x80134D0C | size: 0x8
 */
int PhysicsAIBall::GetObjectType() const
{
    return 0xf;
}
