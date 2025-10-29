#include "Game/Physics/PhysicsBall.h"
#include "Game/Physics/CollisionSpace.h"

#include "NL/nlFont.h"
#include "NL/nlMath.h"
#include "Game/Physics/PhysicsObject.h"
#include "Game/Physics/PhysicsFakeBall.h"

#include "Game/FixedUpdateTask.h"

#include "Game/Ball.h"

float g_BallFriction = 3.f;
float g_BallFrictionWall = 4.f;
float g_BallBounce = 0.25f;
float g_BallBounceGround = 0.375f;
float g_BallBounceWall = 0.45f;
float g_BallRollingResistance = 5.f;
float g_BallAirResistance = 0.1f;

/**
 * Offset/Address/Size: 0x0 | 0x80134D14 | size: 0xD4
 */
void PhysicsBall::CalcAngularFromLinearVelocity(nlVector3& v)
{
    nlVector3 velocity;
    GetLinearVelocity(&velocity);

    nlVector3 t1 = { 0.f, 0.f, 0.f };
    float dVar1 = 1.f / GetRadius();
    nlVector3 t2 = { 0.f, 0.f, 0.f };

    v.f.x = (t1.f.y * t2.f.z) - (dVar1 * velocity.f.y);
    v.f.y = (-t1.f.x * t2.f.z) + (dVar1 * velocity.f.x);
    v.f.z = (t1.f.x * velocity.f.y) - (t1.f.y * velocity.f.x);
}

/**
 * Offset/Address/Size: 0xD4 | 0x80134DE8 | size: 0x28
 */
void PhysicsBall::SetUseAngularVelocity(bool param_1)
{
    m_bUseAngularVel = 0;
    if (param_1)
    {
        m_fSpinTimer = 0.08f;
        return;
    }
    m_fSpinTimer = 0.f;
}

/**
 * Offset/Address/Size: 0xFC | 0x80134E10 | size: 0x80
 */
void PhysicsBall::ScaleAngularVelocity(float scale)
{
    nlVector3 v;
    if (m_bUseAngularVel != 0)
    {
        GetAngularVelocity(&v);
        v.f.z = scale * v.f.z;
        v.f.x = scale * v.f.x;
        v.f.y = scale * v.f.y;
        SetAngularVelocity(v);
    }
}

// const uint vec_zero[3] __attribute__((section(".rodata"))) = {0, 0, 0};
// const nlVector3 vec_zero __attribute__((section(".rodata"))) = nlVector3(0.f, 0.f, 0.f);

/**
 * Offset/Address/Size: 0x17C | 0x80134E90 | size: 0x51C
 */
void PhysicsBall::AddResistanceForces()
{
    nlVector3 local_88;
    nlVector3 local_7c; // 7c, 80, 84
    nlVector3 local_94; // 94, 98, 9c
    nlVector3 local_b8;
    // nlVector3 local_ac;
    nlVector3 local_a0;
    nlVector3 local_58;
    nlVector3 local_d0;
    nlVector3 local_c4;
    nlVector3 local_64;
    nlVector3 local_70;
    nlVector3 sp98; // sp98 sp9C spA0
    nlVector3 sp8C; // sp8C sp90 sp94
    nlVector3 sp38; // sp38 sp3C sp40
    nlVector3 sp2C; // sp2C sp30 sp34
    nlVector3 sp20; // sp20 sp24 sp28
    f32 temp_f1;
    f32 temp_f1_2;
    f32 temp_f1_3;
    f32 temp_f29;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f2_3;
    f32 temp_f3;
    f32 temp_f3_2;
    s8 var_r3;

    // nlVector3* temp_r3 = GetLinearVelocity();
    // sp98.f.x = temp_r3->f.x;
    // sp98.f.y = temp_r3->f.y;
    // sp98.f.z = temp_r3->f.z;
    sp98 = GetLinearVelocity();
    if (m_parentObject == NULL)
    {
        if ((m_bIsSupportedByGround != 0) && (m_bUseAngularVel == 0))
        {
            temp_f2 = sp98.f.z * sp98.f.z;
            temp_f1 = nlSqrt(temp_f2 + ((sp98.f.x * sp98.f.x) + (sp98.f.y * sp98.f.x)), 1);
            if (temp_f1 > 0.01f)
            {
                temp_f3 = -g_BallRollingResistance / temp_f1;
                temp_f2_2 = temp_f3 * sp98.f.x;
                temp_f1_2 = temp_f3 * sp98.f.y;
                sp8C.f.x = temp_f2_2;
                sp8C.f.y = temp_f1_2;
                sp8C.f.z = temp_f3 * sp98.f.z;
                AddForceAtCentreOfMass(sp8C);
            }
        }
        temp_f3_2 = -g_BallAirResistance;
        temp_f2_3 = temp_f3_2 * sp98.f.x;
        temp_f1_3 = temp_f3_2 * sp98.f.y;
        sp8C.f.x = temp_f2_3;
        sp8C.f.y = temp_f1_3;
        sp8C.f.z = temp_f3_2 * sp98.f.z; // sp94=z
        AddForceAtCentreOfMass(sp8C);
    }

    if ((m_bUseTiltForce != 0) && (g_pBall->m_pShooter == NULL))
    {
        var_r3 = 0;
        if ((g_pBall->m_tShotTimer.m_uPackedTime != 0) && (g_pBall->mbCanDamage != 0))
        {
            var_r3 = 1;
        }
        if (var_r3 == 0)
        {
            AddForceAtCentreOfMass(m_v3TiltForce);
        }
    }

    if (m_fSpinTimer > 0.f)
    {
        m_fSpinTimer = m_fSpinTimer - FixedUpdateTask::GetPhysicsUpdateTick();
        if (m_fSpinTimer <= 0.f)
        {
            m_bUseAngularVel = 1;
        }
    }

    if ((m_parentObject == NULL) && (m_bUseAngularVel != 0))
    {
        temp_f29 = 0.02 + GetRadius();
        if (GetPosition().f.z < temp_f29)
        {
            float dVar4 = GetRadius();
            dVar4 = 0.02f + dVar4;
            nlVector3& iVar2 = GetPosition();
            if (iVar2.f.z < dVar4)
            {
                GetLinearVelocity((nlVector3*)&local_b8); // b8 bc c0

                // local_ac.f.z = 0.0;
                // local_ac.f.y = 0.0;
                // local_ac.f.x = 0.0; // ac, b0, b4
                nlVector3 local_ac = { 0.f, 0.f, 0.f };

                dVar4 = GetRadius();

                local_ac.f.x = 1.f / dVar4;

                local_a0.f.x = 0; // a0, a4, a8
                float dVar7 = (local_ac.f.y * 0.0 - local_ac.f.x * local_b8.f.y);
                float dVar6 = (-local_ac.f.z * 0.0 + local_ac.f.x * local_b8.f.z);
                float dVar4 = (local_ac.f.z * local_b8.f.y - local_ac.f.y * local_b8.f.z);
                local_a0.f.z = local_b8.f.z;
                local_a0.f.y = local_b8.f.y;

                GetAngularVelocity(&local_58); // 58, 5c, 60

                float dVar5 = (0.25f * (float)(dVar4 - local_58.f.x));
                dVar6 = (0.25f * (float)(dVar6 - local_58.f.y));
                dVar7 = (0.25f * (float)(dVar7 - local_58.f.z));
                dBodyAddTorque(m_bodyID, dVar5, dVar6, dVar7);

                GetAngularVelocity(&local_d0); // d0, d4, d8
                local_d0.f.x = 0.f;

                local_c4.f.z = 0.f;
                local_c4.f.y = 0.f;
                local_c4.f.x = GetRadius(); // c4, c8, cc

                local_64.f.x = local_d0.f.z * local_c4.f.y - local_d0.f.y * local_c4.f.z;
                local_64.f.y = -local_d0.f.z * local_c4.f.x + local_d0.f.x * local_c4.f.z;
                local_64.f.z = local_d0.f.y * local_c4.f.x - local_d0.f.x * local_c4.f.y;

                GetLinearVelocity(&local_70); // 70 74 78
                local_64.f.x = 5.f * (local_64.f.x - local_70.f.x);
                local_64.f.y = 5.f * (local_64.f.y - local_70.f.y);
                local_64.f.z = 5.f * (local_64.f.z - local_70.f.z);

                AddForceAtCentreOfMass(local_64); // 64, 68, 6c

                local_64.f.x = 0.f;
                if (((dVar5 * dVar5) + (dVar7 * dVar7) + (dVar6 * dVar6) < 0.0001f)
                    && ((local_64.f.x * local_64.f.x) + (local_64.f.z * local_64.f.z) + (local_64.f.y * local_64.f.y) < 0.00003f))
                {
                    m_bUseAngularVel = 0;
                }
            }
        }
    }

    if ((m_parentObject == NULL) && (m_bUseMagnusEffect != 0))
    {
        float dVar4 = GetRadius();
        dVar4 = 0.02f + dVar4;

        nlVector3& iVar2 = GetPosition();
        if ((dVar4 < iVar2.f.z)
            && (GetLinearVelocity(&local_7c), 1.f < local_7c.f.x * local_7c.f.x + local_7c.f.z * local_7c.f.z + local_7c.f.y * local_7c.f.y)
            && (GetAngularVelocity(&local_94), 1.f < local_94.f.x * local_94.f.x + local_94.f.z * local_94.f.z + local_94.f.y * local_94.f.y))
        {
            local_88.f.x = (local_94.f.z * local_7c.f.y - local_94.f.y * local_7c.f.z) * 0.04f;
            local_88.f.z = (local_94.f.y * local_7c.f.x - local_94.f.x * local_7c.f.y) * 0.075f;
            local_88.f.y = (-local_94.f.z * local_7c.f.x + local_94.f.x * local_7c.f.z) * 0.075f;
            AddForceAtCentreOfMass(local_88);
        }
    }
}

/**
 * Offset/Address/Size: 0x698 | 0x801353AC | size: 0x250
 */
int PhysicsBall::Contact(PhysicsObject* other, dContact* contact, int param)
{
    nlVector3 pos;
    // f32 sp14;
    // f32 sp10;
    // s32 spC;

    // s32 sp8;
    nlVector3 _pos;

    f32 temp_f1;
    f32 temp_f1_2;
    f32 temp_f29;
    f32 temp_f2;
    f32 temp_f30;
    f32 temp_f31;
    s32 objType;
    s32 temp_r6;
    s32 var_ctr;
    void** temp_r3;
    nlVector3* temp_r3_2;
    void* var_r3;

    objType = other->GetObjectType();
    GetPosition(&pos);

    if (objType == 0x11)
    {
        // do {
        // if (((this_00->geom).pos.field0_0x0[2] <= local_54) &&
        //     (@632 < (this_00->geom).normal.field0_0x0[2])) {
        //     this->field_0x39 = 1;
        //     break;
        // }
        // this_00 = this_00 + 1;
        // iVar5 = iVar5 + -1;
        // } while (iVar5 != 0);

        var_r3 = (void*)contact;
        var_ctr = param;
        if (param > 0)
        {
        loop_2:
            //     M2C_ERROR(/* unknown instruction: cror eq, lt, eq */);
            if ((((dContact*)var_r3)->geom.pos[2] == pos.f.z) && (((dContact*)var_r3)->geom.normal[2] > 0.9f))
            {
                m_bIsSupportedByGround = 1;
            }
            else
            {
                // var_r3 += 0x68;
                var_r3 = (void*)((char*)var_r3 + 0x68);
                var_ctr -= 1;
                if (var_ctr != 0)
                {
                    goto loop_2;
                }
            }
        }
    }

    if (m_parentObject != NULL)
    {
        if (objType == 0x11)
        {
            GetPosition(&pos);
            if ((contact->geom.normal[2] > 0.f) && ((contact->geom.pos[2] + GetRadius()) < pos.f.z))
            {
                // u32* src = (u32*)GetPosition();
                // u32* dst = (u32*)&_pos;
                // dst[0] = src[0];
                // dst[1] = src[1];
                // dst[2] = src[2];
                _pos = GetPosition();

                temp_f2 = contact->geom.normal[2]; // unk44
                temp_f1 = contact->geom.depth;     // unk4C
                temp_f29 = temp_f2 * temp_f1;
                _pos.f.z += temp_f29;
                SetPosition(_pos, WORLD_COORDINATES); // , temp_r6, temp_f1, temp_f2

                if (contact->geom.depth > 0.95f)
                {
                    return 0;
                }

                temp_f30 = contact->geom.normal[1]; // arg2->unk40;
                temp_f31 = contact->geom.normal[0]; // arg2->unk3C;
                temp_f1_2 = nlRecipSqrt(0.f + (temp_f31 * temp_f31) + (temp_f30 * temp_f30), true);
                contact->geom.normal[0] = (f32)(temp_f1_2 * temp_f31);       //  unk3C
                contact->geom.normal[1] = (f32)(temp_f1_2 * temp_f30);       //  unk40
                contact->geom.normal[2] = (f32)(temp_f1_2 * 0.f);            //  unk44
                contact->geom.depth = (f32)(contact->geom.depth - temp_f29); //  unk4C
            }
        }
        return m_parentObject->Contact(other, contact, param);
    }

    if ((objType != 0x11) && (objType != 0xD) && (objType != 0xE) && (objType != 8))
    {
        m_bUseMagnusEffect = 0;
        FakeBallWorld::InvalidateBallCache();
        g_pBall->m_bBallPathChangeCount = g_pBall->m_bBallPathChangeCount + 1;
        g_pBall->m_bBallDeflectCount = g_pBall->m_bBallDeflectCount + 1;
        // g_pBall->m_unk_0xA6 = 0;
        // g_pBall->m_unk_0xA8 = 0;
    }

    return 3;
}

/**
 * Offset/Address/Size: 0x8E8 | 0x801355FC | size: 0x78
 */
void PhysicsBall::CloneBall(const PhysicsBall& other)
{
    CloneObject(other);

    u32* src = (u32*)&other.m_v3TiltForce;
    u32* dst = (u32*)&m_v3TiltForce;
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];

    m_bUseTiltForce = other.m_bUseTiltForce;
    m_bIsSupportedByGround = other.m_bIsSupportedByGround;
    m_bUseAngularVel = other.m_bUseAngularVel;
    m_bUseMagnusEffect = other.m_bUseMagnusEffect;
    m_fSpinTimer = other.m_fSpinTimer;
}

/**
 * Offset/Address/Size: 0x960 | 0x80135674 | size: 0x164
 */
void PhysicsBall::PostUpdate()
{
    nlVector3 linVel;
    nlVector3 pos;

    PhysicsObject::PostUpdate();
    GetLinearVelocity(&linVel);

    float l = (linVel.f.x * linVel.f.x) + (linVel.f.y * linVel.f.y) + (linVel.f.z * linVel.f.z);
    if (l > 2500.f)
    {
        const f32 f = 50.f / nlSqrt(l, true);
        linVel.f.z = f * linVel.f.z;
        linVel.f.y = f * linVel.f.y;
        linVel.f.x = f * linVel.f.x;
        SetLinearVelocity(linVel);
    }

    if ((GetPosition().f.z > 20.f) && (linVel.f.z > 0.f))
    {
        linVel.f.z *= 0.9f;
        SetLinearVelocity(linVel);
    }

    if (GetPosition().f.z < GetRadius())
    {
        m_bIsSupportedByGround = 1;
        GetPosition(&pos);
        pos.f.z = GetRadius();
        SetPosition(pos, WORLD_COORDINATES);

        linVel.f.z = linVel.f.z * -g_BallBounceGround;
        SetLinearVelocity(linVel);
    }
}

/**
 * Offset/Address/Size: 0xAC4 | 0x801357D8 | size: 0xAC
 */
void PhysicsBall::PreUpdate()
{
    nlVector3 vec;
    GetLinearVelocity(&vec);

    float l = (vec.f.x * vec.f.x) + (vec.f.y * vec.f.y) + (vec.f.z * vec.f.z);
    if (l > 2500.f)
    {
        float n = 50.f / nlSqrt(l, true);
        nlVec3Set(vec, n * vec.f.x, n * vec.f.y, n * vec.f.z);
        SetLinearVelocity(vec);
    }
    PhysicsObject::PreUpdate();
    AddResistanceForces();
}

/**
 * Offset/Address/Size: 0xB70 | 0x80135884 | size: 0xC
 */
void PhysicsBall::PreCollide()
{
    m_bIsSupportedByGround = false;
    // return (int)m_bIsSupportedByGround;
}

/**
 * Offset/Address/Size: 0xB7C | 0x80135890 | size: 0x114
 */
bool PhysicsBall::SetContactInfo(dContact* contact, PhysicsObject* other, bool param)
{
    if (m_parentObject != NULL)
    {
        return m_parentObject->SetContactInfo(contact, other, param);
    }

    if (param != 0)
    {
        SetDefaultContactInfo(contact);
    }

    if (other->GetObjectType() != 8)
    {
        if (other->GetObjectType() == 0x11)
        {
            contact->surface.bounce = (f32)g_BallBounceGround;
        }
        else if (other->GetObjectType() == 0x19)
        {
            contact->surface.bounce = (f32)g_BallBounceWall;
        }
        else
        {
            contact->surface.bounce = (f32)g_BallBounce;
        }

        contact->surface.bounce_vel = 0.f;
        if (other->GetObjectType() == 0x19)
        {
            contact->surface.mu = (f32)g_BallFrictionWall;
        }
        else
        {
            contact->surface.mu = (f32)g_BallFriction;
        }
    }

    return true;
}

/**
 * Offset/Address/Size: 0xC90 | 0x801359A4 | size: 0x8
 */
float PhysicsBall::GetBallMaxVelocity()
{
    return 50.0;
}

/**
 * Offset/Address/Size: 0xC98 | 0x801359AC | size: 0x88
 */
PhysicsBall::PhysicsBall(CollisionSpace* space, PhysicsWorld* world, float radius)
    : PhysicsSphere(space, world, radius)
{
    m_bUseTiltForce = 0;
    m_bIsSupportedByGround = 0;
    m_bUseAngularVel = 0;
    m_bUseMagnusEffect = 0;
    m_fSpinTimer = 0.f;

    SetCategory(0x20);
    SetCollide(0xaf);

    m_gravity = -14.f;

    float temp = 0.f;
    m_v3TiltForce.f.x = temp;
    m_v3TiltForce.f.y = temp;
    m_v3TiltForce.f.z = temp;
}
