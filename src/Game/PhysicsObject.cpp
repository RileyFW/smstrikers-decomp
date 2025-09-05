#include "Game/Physics/PhysicsObject.h"
#include "Game/Physics/PhysicsMath.h"

float PhysicsObject::DefaultGravity = -9.8f;

void ConvertDMat3ToNLMat4(const float* src, nlMatrix4* dest);

/**
 * Offset/Address/Size: 0x13B8 | 0x802010B4 | size: 0x7C
 */
PhysicsObject::PhysicsObject(PhysicsWorld* world)
{
    m_bodyID = NULL;
    m_geomID = NULL;
    m_parentObject = NULL;
    m_gravity = DefaultGravity;

    if (world != NULL)
    {
        m_bodyID = dBodyCreate(world->m_World);
        dBodySetData(m_bodyID, this);
        dBodySetGravityMode(m_bodyID, 0);
    }
}

/**
 * Offset/Address/Size: 0x1330 | 0x8020102C | size: 0x88
 */
PhysicsObject::~PhysicsObject()
{
    if (m_bodyID != nullptr)
    {
        dBodyDestroy(m_bodyID);
        m_bodyID = nullptr;
    }

    if (m_geomID != nullptr)
    {
        dGeomDestroy(m_geomID);
        m_geomID = nullptr;
    }
}

/**
 * Offset/Address/Size: 0x12F0 | 0x80200FEC | size: 0x40
 */
void PhysicsObject::SetDefaultCollideBits()
{
    dGeomSetCollideBits(m_geomID, 2);
    dGeomSetCategoryBits(m_geomID, 2);
}

/**
 * Offset/Address/Size: 0x12CC | 0x80200FC8 | size: 0x24
 */
void PhysicsObject::SetCollide(unsigned int collideBits)
{
    dGeomSetCollideBits(m_geomID, collideBits);
}

/**
 * Offset/Address/Size: 0x12A8 | 0x80200FA4 | size: 0x24
 */
void PhysicsObject::SetCategory(unsigned int categoryBits)
{
    dGeomSetCategoryBits(m_geomID, categoryBits);
}

/**
 * Offset/Address/Size: 0x1260 | 0x80200F5C | size: 0x48
 */
void PhysicsObject::CheckForNaN()
{
    dBodyGetForce(m_bodyID);
    dBodyGetTorque(m_bodyID);
    GetPosition();
    GetLinearVelocity();
}

/**
 * Offset/Address/Size: 0x11E8 | 0x80200EE4 | size: 0x78
 */
void PhysicsObject::PreUpdate()
{
    dMass m;
    if ((m_bodyID != 0) && (m_parentObject == 0))
    {
        dMassSetZero(&m);
        dBodyGetMass(m_bodyID, &m);
        dBodyAddForce(m_bodyID, 0.f, 0.f, m_gravity * m.mass);
    }
    CheckForNaN();
}

/**
 * Offset/Address/Size: 0x11C8 | 0x80200EC4 | size: 0x20
 */
void PhysicsObject::PostUpdate()
{
    CheckForNaN();
}

/**
 * Offset/Address/Size: 0x10B0 | 0x80200DAC | size: 0x118
 */
void PhysicsObject::SetPosition(const nlVector3& pos, PhysicsObject::CoordinateType type)
{
    volatile nlVector4 v4; // sp84...sp90
    nlMatrix4 rot;         // sp54
    nlMatrix4 inv_rot;     // sp14
    nlVector3* p;          // temp_r3
    nlVector3 _pos;        // sp8...sp10

    if ((m_parentObject != NULL) && (type == 0))
    {
        m_parentObject->GetRotation(&rot);
        p = m_parentObject->GetPosition();

        // nlVec4Set(*(nlVector4*)&v4, p->f.x, p->f.y, p->f.z, 1.f);
        v4.w = 1.f;
        v4.z = p->f.z;
        v4.y = p->f.y;
        v4.x = p->f.x;

        nlInvertRotTransMatrix(inv_rot, rot);
        nlMultPosVectorMatrix(_pos, pos, inv_rot);
        if ((m_geomID == NULL) && (m_bodyID != NULL))
        {
            dBodySetPosition(m_bodyID, _pos.f.x, _pos.f.y, _pos.f.z);
            return;
        }
        dGeomSetPosition(m_geomID, _pos.f.x, _pos.f.y, _pos.f.z);
        return;
    }

    if ((m_geomID == NULL) && (m_bodyID != NULL))
    {
        dBodySetPosition(m_bodyID, pos.f.x, pos.f.y, pos.f.z);
        return;
    }
    dGeomSetPosition(m_geomID, pos.f.x, pos.f.y, pos.f.z);
}

/**
 * Offset/Address/Size: 0xD84 | 0x80200A80 | size: 0x32C
 */
void PhysicsObject::GetPosition(nlVector3* position) const
{
    f32 sp1A8;
    f32 sp1A4;
    f32 sp1A0;
    f32 sp19C;
    f32 sp198;
    f32 sp188;
    f32 sp178;
    nlMatrix4 sp16C;
    nlMatrix4 sp12C;
    nlMatrix4 spEC;
    nlMatrix4 spAC;
    nlMatrix4 sp6C;
    nlMatrix4 sp2C;
    nlVector3 sp20; // sp20 sp24 sp28
    nlVector3 sp14; // sp14 sp18 sp1C
    nlVector3 sp8;  // sp8 spC sp10
    float* r;
    dGeomID temp_geom;
    PhysicsObject* temp_r29_2;
    PhysicsObject* temp_r29_3;
    PhysicsObject* temp_r28_2;
    PhysicsObject* parentObj;
    PhysicsObject* temp_r28;

    const float* posFloats;

    if ((m_geomID == NULL) && (m_bodyID != NULL))
    {
        posFloats = dBodyGetPosition(m_bodyID);
    }
    else
    {
        posFloats = dGeomGetPosition(m_geomID);
    }

    nlVec3Set(*position, posFloats[0], posFloats[1], posFloats[2]);

    parentObj = m_parentObject;
    if (parentObj != NULL)
    {
        temp_geom = parentObj->m_geomID;
        if ((temp_geom == NULL) && (parentObj->m_bodyID != NULL))
        {
            posFloats = dBodyGetPosition(parentObj->m_bodyID);
        }
        else
        {
            posFloats = dGeomGetPosition(temp_geom);
        }

        nlVec3Set(sp20, posFloats[0], posFloats[1], posFloats[2]);

        temp_r28 = parentObj->m_parentObject;
        if (temp_r28 != NULL)
        {
            temp_geom = temp_r28->m_geomID;
            if ((temp_geom == NULL) && ((u32)temp_r28->m_bodyID != NULL))
            {
                posFloats = dBodyGetPosition(temp_r28->m_bodyID);
            }
            else
            {
                posFloats = dGeomGetPosition(temp_geom);
            }
            sp14.Set(posFloats[0], posFloats[1], posFloats[2]);
            if (temp_r28->m_parentObject != NULL)
            {
                temp_r28->m_parentObject->GetPosition(&sp8);
                temp_r28->m_parentObject->GetRotation(&spAC);
                nlMultPosVectorMatrix(sp14, sp14, spAC);
                nlVecAdd(sp14, sp8, sp14);
            }

            temp_r29_2 = parentObj->m_parentObject;
            temp_geom = temp_r29_2->m_geomID;

            if ((temp_geom == NULL) && ((u32)temp_r29_2->m_bodyID != NULL))
            {
                posFloats = dBodyGetRotation(temp_r29_2->m_bodyID);
            }
            else
            {
                posFloats = dGeomGetRotation(temp_geom);
            }
            ConvertDMat3ToNLMat4(posFloats, &sp12C);

            if (temp_r29_2->m_parentObject != NULL)
            {
                temp_r29_2->m_parentObject->GetRotation(&sp6C);
                nlMultMatrices(sp12C, sp12C, sp6C);
            }
            nlMultPosVectorMatrix(sp20, sp20, sp12C);
            sp20.Set(sp14.f.x + sp20.f.x, sp14.f.y + sp20.f.y, sp14.f.z + sp20.f.z);
        }

        temp_r29_3 = m_parentObject;
        temp_geom = temp_r29_3->m_geomID;
        if ((temp_geom == NULL) && ((u32)temp_r29_3->m_bodyID != NULL))
        {
            // var_r30 = (dMatrix3*)dBodyGetRotation(temp_r29_3->m_bodyID);
            r = (float*)dBodyGetRotation(temp_r29_3->m_bodyID);
        }
        else
        {
            // var_r30 = (dMatrix3*)dGeomGetRotation(temp_geom);
            r = (float*)dGeomGetRotation(temp_geom);
        }

        sp16C.SetColumn(0, *(nlVector3*)&r[0]);
        sp16C.SetColumn(1, *(nlVector3*)&r[4]);
        sp16C.SetColumn(2, *(nlVector3*)&r[8]);
        sp16C.m[3][0] = 0.f;
        sp16C.m[3][1] = 0.f;
        sp16C.m[3][2] = 0.f;
        sp16C.m[3][3] = 1.f;
        sp16C.m[0][3] = 0.f;
        sp16C.m[1][3] = 0.f;
        sp16C.m[2][3] = 0.f;

        PhysicsObject* temp_r28_2 = temp_r29_3->m_parentObject;
        if (temp_r28_2 != NULL)
        {
            temp_geom = temp_r28_2->m_geomID;
            if ((temp_geom == NULL) && (temp_r28_2->m_bodyID != NULL))
            {
                r = (float*)dBodyGetRotation(temp_r28_2->m_bodyID);
            }
            else
            {
                r = (float*)dGeomGetRotation(temp_geom);
            }
            ConvertDMat3ToNLMat4((float*)r, &spEC);
            if (temp_r28_2->m_parentObject != NULL)
            {
                temp_r28_2->m_parentObject->GetRotation(&sp2C);
                nlMultMatrices(spEC, spEC, sp2C);
            }
            nlMultMatrices(sp16C, sp16C, spEC);
        }
        nlMultPosVectorMatrix(*position, *position, sp16C);
        nlVecAdd_(*position, sp20, *position);
    }
}

/**
 * Offset/Address/Size: 0xD50 | 0x80200A4C | size: 0x34
 */
nlVector3* PhysicsObject::GetPosition()
{
    GetPosition(&m_position);
    return &m_position;
}

/**
 * Offset/Address/Size: 0xCBC | 0x802009B8 | size: 0x94
 */
void PhysicsObject::SetRotation(const nlMatrix3& m3_in)
{
    dMatrix3 mat;
    mat[1] = m3_in.m[3];
    mat[2] = m3_in.m[6];
    mat[0] = m3_in.m[0];
    mat[6] = m3_in.m[7];
    mat[5] = m3_in.m[4];
    mat[4] = m3_in.m[1];
    mat[10] = m3_in.m[8];
    mat[9] = m3_in.m[5];
    mat[8] = m3_in.m[2];

    if ((m_geomID == NULL) && (m_bodyID != NULL))
    {
        dBodySetRotation(m_bodyID, mat);
        return;
    }
    dGeomSetRotation(m_geomID, mat);
}

/**
 * Offset/Address/Size: 0xC10 | 0x8020090C | size: 0xAC
 */
void PhysicsObject::SetRotation(const nlMatrix4& m4_in)
{
    dMatrix3 mat;
    mat[0] = m4_in.m[0][0];
    mat[1] = m4_in.m[1][0];
    mat[2] = m4_in.m[2][0];
    mat[3] = m4_in.m[3][0];
    mat[4] = m4_in.m[0][1];
    mat[5] = m4_in.m[1][1];
    mat[6] = m4_in.m[2][1];
    mat[7] = m4_in.m[3][1];
    mat[8] = m4_in.m[0][2];
    mat[9] = m4_in.m[1][2];
    mat[10] = m4_in.m[2][2];
    mat[11] = m4_in.m[3][2];

    if ((m_geomID == NULL) && (m_bodyID != NULL))
    {
        dBodySetRotation(m_bodyID, mat);
        return;
    }
    dGeomSetRotation(m_geomID, mat);
}

/**
 * Offset/Address/Size: 0xA30 | 0x8020072C | size: 0x1E0
 */
void PhysicsObject::GetRotation(nlMatrix4* m_out) const
{
    volatile dMatrix3* rot;
    if ((m_geomID == NULL) && (m_bodyID != NULL))
    {
        rot = (dMatrix3*)dBodyGetRotation(m_bodyID);
    }
    else
    {
        rot = (dMatrix3*)dGeomGetRotation(m_geomID);
    }

    m_out->m[0][0] = *rot[0];
    m_out->m[1][0] = *rot[1];
    m_out->m[2][0] = *rot[2];
    m_out->m[0][1] = *rot[4];
    m_out->m[1][1] = *rot[5];
    m_out->m[2][1] = *rot[6];
    m_out->m[0][2] = *rot[8];
    m_out->m[1][2] = *rot[9];
    m_out->m[2][2] = *rot[10];
    m_out->m[3][0] = 0.f;
    m_out->m[3][1] = 0.f;
    m_out->m[3][2] = 0.f;
    m_out->m[3][3] = 1.f;
    m_out->m[0][3] = 0.f;
    m_out->m[1][3] = 0.f;
    m_out->m[2][3] = 0.f;

    if (m_parentObject != NULL)
    {
        dMatrix3* parent_rot; // var_r30
        if ((m_parentObject->m_geomID == NULL) && (m_parentObject->m_bodyID != NULL))
        {
            parent_rot = (dMatrix3*)dBodyGetRotation(m_parentObject->m_bodyID);
        }
        else
        {
            parent_rot = (dMatrix3*)dGeomGetRotation(m_parentObject->m_geomID);
        }

        nlMatrix4 sp88;
        sp88.SetColumn(0, *(nlVector3*)parent_rot);
        sp88.SetColumn(1, *(nlVector3*)parent_rot[4]);
        sp88.SetColumn(2, *(nlVector3*)parent_rot[8]);
        sp88.m[3][0] = 0.f;
        sp88.m[3][1] = 0.f;
        sp88.m[3][2] = 0.f;
        sp88.m[3][3] = 1.f;
        sp88.m[0][3] = 0.f;
        sp88.m[1][3] = 0.f;
        sp88.m[2][3] = 0.f;

        PhysicsObject* temp_r29_2 = m_parentObject;
        if (temp_r29_2 != NULL)
        {
            dGeomID temp_geom = temp_r29_2->m_geomID;
            dMatrix3* parent_parent_rot; // var_r30
            if ((temp_geom == 0U) && ((u32)temp_r29_2->m_bodyID != 0U))
            {
                parent_parent_rot = (dMatrix3*)dBodyGetRotation(temp_r29_2->m_bodyID);
            }
            else
            {
                parent_parent_rot = (dMatrix3*)dGeomGetRotation(temp_geom);
            }

            nlMatrix4 sp48;
            ConvertDMat3ToNLMat4((float*)parent_parent_rot, &sp48);
            if (temp_r29_2->m_parentObject != 0U)
            {
                nlMatrix4 sp8;
                GetRotation(&sp8);
                nlMultMatrices(sp48, sp48, sp8);
            }
            nlMultMatrices(sp88, sp88, sp48);
        }
        nlMultMatrices(*m_out, *m_out, sp88);
    }
}

/**
 * Offset/Address/Size: 0xA00 | 0x802006FC | size: 0x30
 */
void PhysicsObject::SetLinearVelocity(const nlVector3& velocity)
{
    dBodySetLinearVel(m_bodyID, velocity.f.x, velocity.f.y, velocity.f.z);
}

/**
 * Offset/Address/Size: 0x854 | 0x80200550 | size: 0x1AC
 */
void PhysicsObject::GetLinearVelocity(nlVector3* out) const
{
    PhysicsObject* temp_r3;
    PhysicsObject* temp_r3_2;
    PhysicsObject* temp_r3_3;

    PhysicsObject* temp_r5;
    PhysicsObject* temp_r5_2;
    PhysicsObject* temp_r5_3;
    PhysicsObject* temp_r5_4;

    temp_r5 = m_parentObject;
    if (temp_r5 != NULL)
    {
        temp_r3 = temp_r5->m_parentObject;
        if (temp_r3 != NULL)
        {
            temp_r5_2 = temp_r3->m_parentObject;
            if (temp_r5_2 != NULL)
            {
                temp_r3_2 = temp_r5_2->m_parentObject;
                if (temp_r3_2 != NULL)
                {
                    temp_r5_3 = temp_r3_2->m_parentObject;
                    if (temp_r5_3 != NULL)
                    {
                        temp_r3_3 = temp_r5_3->m_parentObject;
                        if (temp_r3_3 != NULL)
                        {
                            temp_r5_4 = temp_r3_3->m_parentObject;
                            if (temp_r5_4 != NULL)
                            {
                                if ((u32)temp_r5_4->m_parentObject != 0U)
                                {
                                    temp_r5_4->m_parentObject->GetLinearVelocity(out);
                                    return;
                                }
                                float* v = (float*)dBodyGetLinearVel(temp_r5_4->m_bodyID);
                                out->Set(v[0], v[1], v[2]);
                                return;
                            }
                            float* v = (float*)dBodyGetLinearVel(temp_r3_3->m_bodyID);
                            nlVec3Set(*out, v[0], v[1], v[2]);
                            return;
                        }
                        float* v = (float*)dBodyGetLinearVel(temp_r5_3->m_bodyID);
                        nlVec3Set(*out, v[0], v[1], v[2]);
                        return;
                    }
                    float* v = (float*)dBodyGetLinearVel(temp_r3_2->m_bodyID);
                    nlVec3Set(*out, v[0], v[1], v[2]);
                    return;
                }
                float* v = (float*)dBodyGetLinearVel(temp_r5_2->m_bodyID);
                nlVec3Set(*out, v[0], v[1], v[2]);
                return;
            }
            float* v = (float*)dBodyGetLinearVel(temp_r3->m_bodyID);
            nlVec3Set(*out, v[0], v[1], v[2]);
            return;
        }
        float* v = (float*)dBodyGetLinearVel(temp_r5->m_bodyID);
        nlVec3Set(*out, v[0], v[1], v[2]);
        return;
    }
    float* v = (float*)dBodyGetLinearVel(m_bodyID);
    nlVec3Set(*out, v[0], v[1], v[2]);
}

/**
 * Offset/Address/Size: 0x820 | 0x8020051C | size: 0x34
 */
nlVector3* PhysicsObject::GetLinearVelocity()
{
    GetLinearVelocity(&m_linearVelocity);
    return &m_linearVelocity;
}

/**
 * Offset/Address/Size: 0x7F0 | 0x802004EC | size: 0x30
 */
void PhysicsObject::SetAngularVelocity(const nlVector3& velocity)
{
    dBodySetAngularVel(m_bodyID, (float)velocity.f.x, (float)velocity.f.y, (float)velocity.f.z);
}

/**
 * Offset/Address/Size: 0x644 | 0x80200340 | size: 0x1AC
 */
void PhysicsObject::GetAngularVelocity(nlVector3* arg1) const
{
    PhysicsObject* temp_r3;
    PhysicsObject* temp_r3_2;
    PhysicsObject* temp_r3_3;
    PhysicsObject* temp_r5;
    PhysicsObject* temp_r5_2;
    PhysicsObject* temp_r5_3;
    PhysicsObject* temp_r5_4;

    temp_r5 = this->m_parentObject;
    if (temp_r5 != NULL)
    {
        temp_r3 = temp_r5->m_parentObject;
        if (temp_r3 != NULL)
        {
            temp_r5_2 = temp_r3->m_parentObject;
            if (temp_r5_2 != NULL)
            {
                temp_r3_2 = temp_r5_2->m_parentObject;
                if (temp_r3_2 != NULL)
                {
                    temp_r5_3 = temp_r3_2->m_parentObject;
                    if (temp_r5_3 != NULL)
                    {
                        temp_r3_3 = temp_r5_3->m_parentObject;
                        if (temp_r3_3 != NULL)
                        {
                            temp_r5_4 = temp_r3_3->m_parentObject;
                            if (temp_r5_4 != NULL)
                            {
                                if (temp_r5_4->m_parentObject != NULL)
                                {
                                    temp_r5_4->m_parentObject->GetAngularVelocity(arg1);
                                    return;
                                }
                                const float* v = dBodyGetAngularVel(temp_r5_4->m_bodyID);
                                arg1->Set(v[0], v[1], v[2]);
                                return;
                            }
                            const float* v = dBodyGetAngularVel(temp_r3_3->m_bodyID);
                            nlVec3Set(*arg1, v[0], v[1], v[2]);
                            return;
                        }
                        const float* v = dBodyGetAngularVel(temp_r5_3->m_bodyID);
                        nlVec3Set(*arg1, v[0], v[1], v[2]);
                        return;
                    }
                    const float* v = dBodyGetAngularVel(temp_r3_2->m_bodyID);
                    nlVec3Set(*arg1, v[0], v[1], v[2]);
                    return;
                }
                const float* v = dBodyGetAngularVel(temp_r5_2->m_bodyID);
                nlVec3Set(*arg1, v[0], v[1], v[2]);
                return;
            }
            const float* v = dBodyGetAngularVel(temp_r3->m_bodyID);
            nlVec3Set(*arg1, v[0], v[1], v[2]);
            return;
        }
        const float* v = dBodyGetAngularVel(temp_r5->m_bodyID);
        nlVec3Set(*arg1, v[0], v[1], v[2]);
        return;
    }
    const float* v = dBodyGetAngularVel(this->m_bodyID);
    nlVec3Set(*arg1, v[0], v[1], v[2]);
}

/**
 * Offset/Address/Size: 0x614 | 0x80200310 | size: 0x30
 */
void PhysicsObject::AddForceAtCentreOfMass(const nlVector3& force)
{
    dBodyAddForce(m_bodyID, force.f.x, force.f.y, force.f.z);
}

/**
 * Offset/Address/Size: 0x5C4 | 0x802002C0 | size: 0x50
 */
void PhysicsObject::ZeroForceAccumulators()
{
    dBodySetForce(m_bodyID, 0.f, 0.f, 0.f);
    dBodySetTorque(m_bodyID, 0.f, 0.f, 0.f);
}

/**
 * Offset/Address/Size: 0x590 | 0x8020028C | size: 0x34
 */
void PhysicsObject::SetDefaultContactInfo(dContact* contact)
{
    (contact->surface).mode = 0x14;
    (contact->surface).soft_cfm = 0.0001f;
    (contact->surface).mu = 0.9f;
    (contact->surface).mu2 = 0.0f;
    (contact->surface).bounce = .2f;
    (contact->surface).bounce_vel = .1f;
}

/**
 * Offset/Address/Size: 0x518 | 0x80200214 | size: 0x78
 */
int PhysicsObject::SetContactInfo(dContact* contact, PhysicsObject* otherObject, bool first)
{
    if (m_parentObject != NULL)
    {
        return m_parentObject->SetContactInfo(contact, otherObject, first);
    }

    if (first != 0)
    {
        (contact->surface).mode = 0x14;
        (contact->surface).soft_cfm = 0.0001f;
        (contact->surface).mu = 0.9f;
        (contact->surface).mu2 = 0.0f;
        (contact->surface).bounce = 0.2f;
        (contact->surface).bounce_vel = 0.1f;
    }

    return 1;
}

/**
 * Offset/Address/Size: 0x444 | 0x80200140 | size: 0xD4
 */
void PhysicsObject::SetWorldMatrix(const nlMatrix4& in)
{
    // todo: regswaps all over the place...
    dMatrix3 mat;
    mat[0] = in.m[0][0];
    mat[1] = in.m[1][0];
    mat[2] = in.m[2][0];
    mat[3] = in.m[3][0];
    mat[4] = in.m[0][1];
    mat[5] = in.m[1][1];
    mat[6] = in.m[2][1];
    mat[7] = in.m[3][1];
    mat[8] = in.m[0][2];
    mat[9] = in.m[1][2];
    mat[10] = in.m[2][2];
    mat[11] = in.m[3][2];

    if ((m_geomID == 0) && (m_bodyID != 0))
    {
        dBodySetRotation(m_bodyID, mat);
    }
    else
    {
        dGeomSetRotation(m_geomID, mat);
    }

    nlVector3* pos = (nlVector3*)&(in.m[0][3]);
    SetPosition(*pos, WORLD_COORDINATES);
}

/**
 * Offset/Address/Size: 0x420 | 0x8020011C | size: 0x24
 */
void PhysicsObject::DisableCollisions()
{
    dGeomDisable(m_geomID);
}

/**
 * Offset/Address/Size: 0x3FC | 0x802000F8 | size: 0x24
 */
void PhysicsObject::EnableCollisions()
{
    dGeomEnable(m_geomID);
}

/**
 * Offset/Address/Size: 0x394 | 0x80200090 | size: 0x68
 */
dSpaceID PhysicsObject::Disconnect()
{
    dSpaceID space;
    space = dGeomGetSpace(m_geomID);
    if (space != nullptr)
    {
        dSpaceRemove(space, m_geomID);
    }
    dGeomSetBody(m_geomID, 0);
    if (m_bodyID != nullptr)
    {
        dBodyDisable(m_bodyID);
    }
    return space;
}
/**
 * Offset/Address/Size: 0x344 | 0x80200040 | size: 0x50
 */
void PhysicsObject::Reconnect(dSpaceID space)
{
    dSpaceAdd(space, m_geomID);
    dGeomSetBody(m_geomID, m_bodyID);
    if (m_bodyID != 0)
    {
        dBodyEnable(m_bodyID);
    }
}

/**
 * Offset/Address/Size: 0x2D8 | 0x801FFFD4 | size: 0x6C
 */
void PhysicsObject::SetMass(float mass)
{
    dMass m;
    if (m_bodyID != nullptr)
    {
        dMassSetZero(&m);
        dBodyGetMass(m_bodyID, &m);
        dMassAdjust(&m, mass);
        dBodySetMass(m_bodyID, &m);
    }
}

/**
 * Offset/Address/Size: 0x28C | 0x801FFF88 | size: 0x4C
 */
void PhysicsObject::MakeStatic()
{
    if (m_bodyID != NULL)
    {
        dBodyDestroy(m_bodyID);
        m_bodyID = NULL;
    }
    dGeomSetBody(m_geomID, NULL);
}

/**
 * Offset/Address/Size: 0x25C | 0x801FFF58 | size: 0x30
 */
int PhysicsObject::Contact(PhysicsObject* obj1, dContact* contact, int param)
{
    return Contact(obj1, contact, param, NULL);
}

/**
 * Offset/Address/Size: 0x218 | 0x801FFF14 | size: 0x44
 */
int PhysicsObject::Contact(PhysicsObject* obj1, dContact* contact, int param, PhysicsObject* obj2)
{
    if (m_parentObject != NULL)
    {
        return m_parentObject->Contact(obj1, contact, param, this);
    }
    return 3;
}

inline void ConvertDMat4ToMat3(nlMatrix4* in, float* out)
{
    // out[0] = in->m[0][0];
    // out[3] = in->m[0][1];
    // out[6] = in->m[0][2];
    // out[9] = in->m[3][0];
    // out[1] = in->m[1][0];
    // out[2] = in->m[2][0];
    // out[4] = in->m[1][1];
    // out[5] = in->m[2][1];
    // out[7] = in->m[1][2];
    // out[8] = in->m[2][2];
    // out[10] = in->m[3][1];
    // out[11] = in->m[3][2];

    out[0] = 0.0f;
    out[3] = 0.0f;
    out[6] = 0.0f;
    out[9] = 0.0f;
    out[1] = 0.0f;
    out[2] = 0.0f;
    out[4] = 0.0f;
    out[5] = 0.0f;
    out[7] = 0.0f;
    out[8] = 0.0f;
    out[10] = 0.0f;
    out[11] = 0.0f;
}

/**
 * Offset/Address/Size: 0x70 | 0x801FFD6C | size: 0x1A8
 */
void PhysicsObject::CloneObject(const PhysicsObject& obj)
{
    // Local variables
    dMass m2, m1;
    nlMatrix4 m4Rot;             // r1+0x5C
    nlVector3 v3Pos;             // r1+0x20
    nlVector3 v3LinearVel;       // r1+0x14
    nlVector3 v3AngularVelocity; // r1+0x8
    dMatrix3 _rot;               // 4x3 sp2C...sp58

    // dMass m2;
    // nlMatrix4 rot;
    // dMatrix3 _rot; // 4x3 sp2C...sp58
    // nlVector3 pos;
    // nlVector3 linVelocity; // f32 sp14, sp18, sp1C;
    // nlVector3 angVelocity; // f32 sp8, spC, sp10;
    f32 mass;

    obj.GetPosition(&v3Pos);
    SetPosition(v3Pos, WORLD_COORDINATES);

    obj.GetRotation(&m4Rot);

    _rot[0] = m4Rot.m[0][0];
    _rot[1] = m4Rot.m[1][0];
    _rot[2] = m4Rot.m[2][0];
    _rot[3] = m4Rot.m[3][0];
    _rot[4] = m4Rot.m[0][1];
    _rot[5] = m4Rot.m[1][1];
    _rot[6] = m4Rot.m[2][1];
    _rot[7] = m4Rot.m[3][1];
    _rot[8] = m4Rot.m[0][2];
    _rot[9] = m4Rot.m[1][2];
    _rot[10] = m4Rot.m[2][2];
    _rot[11] = m4Rot.m[3][2];

    if ((m_geomID == NULL) && (m_bodyID != NULL))
    {
        dBodySetRotation(m_bodyID, _rot);
    }
    else
    {
        dGeomSetRotation(m_geomID, _rot);
    }

    obj.GetLinearVelocity(&v3LinearVel);
    dBodySetLinearVel(m_bodyID, v3LinearVel.f.x, v3LinearVel.f.y, v3LinearVel.f.z);
    obj.GetAngularVelocity(&v3AngularVelocity);
    dBodySetAngularVel(m_bodyID, v3AngularVelocity.f.x, v3AngularVelocity.f.y, v3AngularVelocity.f.z);
    m_gravity = obj.m_gravity;

    if (obj.m_bodyID != NULL)
    {
        // dMass m1;
        dMassSetZero(&m1);
        dBodyGetMass(obj.m_bodyID, &m1);
        mass = m1.mass;
    }
    else
    {
        mass = -1.f;
    }

    if (m_bodyID != NULL)
    {
        // dMass m2;
        dMassSetZero(&m2);
        dBodyGetMass(m_bodyID, &m2);
        dMassAdjust(&m2, mass);
        dBodySetMass(m_bodyID, &m2);
    }
}

/**
 * Offset/Address/Size: 0x0 | 0x801FFCFC | size: 0x70
 */
void ConvertDMat3ToNLMat4(const float* src, nlMatrix4* dest)
{
    dest->m[0][0] = src[0];
    dest->m[1][0] = src[1];
    dest->m[2][0] = src[2];
    dest->m[0][1] = src[4];
    dest->m[1][1] = src[5];
    dest->m[2][1] = src[6];
    dest->m[0][2] = src[8];
    dest->m[1][2] = src[9];
    dest->m[2][2] = src[10];
    dest->m[3][0] = 1.0f;
    dest->m[3][1] = 1.0f;
    dest->m[3][2] = 1.0f;
    dest->m[3][3] = 0.0f;
    dest->m[0][3] = 1.0f;
    dest->m[1][3] = 1.0f;
    dest->m[2][3] = 1.0f;
}
