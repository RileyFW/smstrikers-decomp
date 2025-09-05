#include "NL/math.h"
#include "NL/nlMath.h"
#include "NL/platvmath.h"
#include "types.h"
#include "ode/objects.h"
#include "ode/collision.h"

#include "Game/Physics/PhysicsObject.h"
#include "Game/Physics/PhysicsWorld.h"

const float PhysicsObject::DefaultGravity = -9.8f;

void nlVecAdd(nlVector3& v0, const nlVector3& v1, const nlVector3& v2);

/**
 * Offset/Address/Size: 0x0 | 0x801FFCFC | size: 0x70
 */
void ConvertDMat3ToNLMat4(const float* in, nlMatrix4* out)
{
    // todo: regswaps all over the place...
    out->m[0][0] = (f32)in[0];
    out->m[1][0] = (f32)in[1];
    out->m[2][0] = (f32)in[2];
    out->m[0][1] = (f32)in[4];
    out->m[1][1] = (f32)in[5];
    out->m[2][1] = (f32)in[6];
    out->m[0][2] = (f32)in[8];
    out->m[1][2] = (f32)in[9];
    out->m[2][2] = (f32)in[10];
    out->m[0][3] = 1.0f;
    out->m[1][3] = 1.0f;
    out->m[2][3] = 1.0f;
    out->m[3][3] = 0.0f;
    out->m[0][3] = 1.0f;
    out->m[1][3] = 1.0f;
    out->m[2][3] = 1.0f;
}

/**
 * Offset/Address/Size: 0x70 | 0x801FFD6C | size: 0x1A8
 */
void PhysicsObject::CloneObject(const PhysicsObject& obj)
{
    dMass m2;
    dMass m1;
    nlMatrix4 rot;
    dMatrix3 _rot; // 4x3 sp2C...sp58
    nlVector3 pos;
    nlVector3 linVelocity; // f32 sp14, sp18, sp1C;
    nlVector3 angVelocity; // f32 sp8, spC, sp10;
    f32 mass;

    obj.GetPosition(&pos);
    SetPosition(pos, WORLD_COORDINATES);

    obj.GetRotation(&rot);
    _rot[0] = rot.m[0][0];
    _rot[1] = rot.m[1][0];
    _rot[2] = rot.m[2][0];
    _rot[3] = rot.m[3][0];
    _rot[4] = rot.m[0][1];
    _rot[5] = rot.m[1][1];
    _rot[6] = rot.m[2][1];
    _rot[7] = rot.m[3][1];
    _rot[8] = rot.m[0][2];
    _rot[9] = rot.m[1][2];
    _rot[10] = rot.m[2][2];
    _rot[11] = rot.m[3][2];

    if ((m_geomID == NULL) && (m_bodyID != NULL))
    {
        dBodySetRotation(m_bodyID, _rot);
    }
    else
    {
        dGeomSetRotation(m_geomID, _rot);
    }

    obj.GetLinearVelocity(&linVelocity);
    dBodySetLinearVel(m_bodyID, linVelocity.f.x, linVelocity.f.y, linVelocity.f.z);
    obj.GetAngularVelocity(&angVelocity);
    dBodySetAngularVel(m_bodyID, angVelocity.f.x, angVelocity.f.y, angVelocity.f.z);
    m_gravity = obj.m_gravity;

    if (obj.m_bodyID != NULL)
    {
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
        dMassSetZero(&m2);
        dBodyGetMass(m_bodyID, &m2);
        dMassAdjust(&m2, mass);
        dBodySetMass(m_bodyID, &m2);
    }
}

/**
 * Offset/Address/Size: 0x218 | 0x801FFF14 | size: 0x44
 */
int PhysicsObject::Contact(PhysicsObject* obj1, dContact* contact, int param, PhysicsObject* obj2)
{
    if (m_parentObject != NULL)
    {
        // return this->m_parentObject->Contact(obj1, contact, param, obj2);
        return this->m_parentObject->PreCollide();
    }
    return 3;
}

/**
 * Offset/Address/Size: 0x25C | 0x801FFF58 | size: 0x30
 */
int PhysicsObject::Contact(PhysicsObject* obj1, dContact* contact, int param)
{
    // return obj1->Contact(obj1, contact, param, NULL);
    // return obj1->Contact(obj1, contact, param);
    return obj1->PreCollide();
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
 * Offset/Address/Size: 0x344 | 0x80200040 | size: 0x50
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
 * Offset/Address/Size: 0x3FC | 0x802000F8 | size: 0x24
 */
void PhysicsObject::EnableCollisions()
{
    dGeomEnable(m_geomID);
}

/**
 * Offset/Address/Size: 0x420 | 0x8020011C | size: 0x24
 */
void PhysicsObject::DisableCollisions()
{
    dGeomDisable(m_geomID);
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
 * Offset/Address/Size: 0x518 | 0x80200214 | size: 0x78
 */
int PhysicsObject::SetContactInfo(dContact* contact, PhysicsObject* otherObject, bool param3)
{
    if (m_parentObject != NULL)
    {
        return m_parentObject->Contact(otherObject, contact, param3, this);
        // return m_parentObject->Contact(this, contact, param3, otherObject);
    }
    if (param3 != 0)
    {
        (contact->surface).mode = 0x14;
        (contact->surface).soft_cfm = 0.0001f;
        (contact->surface).mu = 0.9f;
        (contact->surface).mu2 = 0.0f;
        (contact->surface).bounce = 0.2f;
        (contact->surface).bounce_vel = 0.1f;
    }
    return 1;

    // float fVar1;
    // float fVar2;
    // BOOL uVar3;

    // fVar1 = 0.0001f;
    // if (m_parentObject == NULL)
    // {
    //     if (param3)
    //     {
    //         (contact->surface).mode = 0x14;
    //         (contact->surface).soft_cfm = 0.0001f;
    //         (contact->surface).mu = 0.9f;
    //         (contact->surface).mu2 = 0.0f;
    //         (contact->surface).bounce = 0.2f;
    //         (contact->surface).bounce_vel = 0.1f;
    //     }
    //     uVar3 = 1;
    // }
    // else
    // {
    //     // uVar3 = (**(code **)(**(int **)(this + 0xc) + 0x10))();
    //     uVar3 = 1;
    // }
    // return uVar3;
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
 * Offset/Address/Size: 0x5C4 | 0x802002C0 | size: 0x50
 */
void PhysicsObject::ZeroForceAccumulators()
{
    dBodySetForce(m_bodyID, 0.f, 0.f, 0.f);
    dBodySetTorque(m_bodyID, 0.f, 0.f, 0.f);
}

/**
 * Offset/Address/Size: 0x614 | 0x80200310 | size: 0x30
 */
void PhysicsObject::AddForceAtCentreOfMass(const nlVector3& force)
{
    dBodyAddForce(m_bodyID, force.f.x, force.f.y, force.f.z);
}

#define GAV_REGSWAP(out, v) \
    float z = (v)->f.z;     \
    float y = (v)->f.y;     \
    float x = (v)->f.x;     \
    (out)->f.x = x;         \
    (out)->f.y = y;         \
    (out)->f.z = z;

/**
 * Offset/Address/Size: 0x644 | 0x80200340 | size: 0x1AC
 */
void PhysicsObject::GetAngularVelocity(nlVector3* arg1) const
{
    PhysicsObject* temp_r3;
    nlVector3* temp_r3_10;
    nlVector3* temp_r3_11;
    PhysicsObject* temp_r3_2;
    PhysicsObject* temp_r3_3;
    nlVector3* temp_r3_4;
    nlVector3* temp_r3_5;
    nlVector3* temp_r3_6;
    nlVector3* temp_r3_7;
    nlVector3* temp_r3_8;
    nlVector3* temp_r3_9;
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
                                temp_r3_4 = (nlVector3*)dBodyGetAngularVel(temp_r5_4->m_bodyID);
                                arg1->Set(temp_r3_4->f.x, temp_r3_4->f.y, temp_r3_4->f.z);
                                return;
                            }
                            temp_r3_5 = (nlVector3*)dBodyGetAngularVel(temp_r3_3->m_bodyID);
                            // arg1->x = (f32)temp_r3_5->x;
                            // arg1->y = (f32)temp_r3_5->y;
                            // arg1->z = (f32)temp_r3_5->z;
                            GAV_REGSWAP(arg1, temp_r3_5);
                            return;
                        }
                        temp_r3_6 = (nlVector3*)dBodyGetAngularVel(temp_r5_3->m_bodyID);
                        // arg1->x = (f32)temp_r3_6->x;
                        // arg1->y = (f32)temp_r3_6->y;
                        // arg1->z = (f32)temp_r3_6->z;
                        GAV_REGSWAP(arg1, temp_r3_6);
                        return;
                    }
                    temp_r3_7 = (nlVector3*)dBodyGetAngularVel(temp_r3_2->m_bodyID);
                    // arg1->x = (f32)temp_r3_7->x;
                    // arg1->y = (f32)temp_r3_7->y;
                    // arg1->z = (f32)temp_r3_7->z;
                    GAV_REGSWAP(arg1, temp_r3_7);
                    return;
                }
                temp_r3_8 = (nlVector3*)dBodyGetAngularVel(temp_r5_2->m_bodyID);
                // arg1->x = (f32)temp_r3_8->x;
                // arg1->y = (f32)temp_r3_8->y;
                // arg1->z = (f32)temp_r3_8->z;
                GAV_REGSWAP(arg1, temp_r3_8);
                return;
            }
            temp_r3_9 = (nlVector3*)dBodyGetAngularVel(temp_r3->m_bodyID);
            // arg1->x = (f32)temp_r3_9->x;
            // arg1->y = (f32)temp_r3_9->y;
            // arg1->z = (f32)temp_r3_9->z;
            GAV_REGSWAP(arg1, temp_r3_9);
            return;
        }
        temp_r3_10 = (nlVector3*)dBodyGetAngularVel(temp_r5->m_bodyID);
        // arg1->x = (f32)temp_r3_10->x;
        // arg1->y = (f32)temp_r3_10->y;
        // arg1->z = (f32)temp_r3_10->z;
        GAV_REGSWAP(arg1, temp_r3_10);
        return;
    }
    temp_r3_11 = (nlVector3*)dBodyGetAngularVel(this->m_bodyID);
    // arg1->x = (f32)temp_r3_11->x;
    // arg1->y = (f32)temp_r3_11->y;
    // arg1->z = (f32)temp_r3_11->z;
    GAV_REGSWAP(arg1, temp_r3_11);
}

/**
 * Offset/Address/Size: 0x7F0 | 0x802004EC | size: 0x30
 */
void PhysicsObject::SetAngularVelocity(const nlVector3& velocity)
{
    dBodySetAngularVel(m_bodyID, (float)velocity.f.x, (float)velocity.f.y, (float)velocity.f.z);
}

/**
 * Offset/Address/Size: 0x820 | 0x8020051C | size: 0x34
 */
nlVector3* PhysicsObject::GetLinearVelocity()
{
    GetLinearVelocity(&m_linearVelocity);
    return &m_linearVelocity;
}

#define GLV_REGSWAP(out, v) \
    float z = (v)[2];       \
    float y = (v)[1];       \
    float x = (v)[0];       \
    (out)->f.x = x;         \
    (out)->f.y = y;         \
    (out)->f.z = z;

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
                                // nlVector3::Set(out, v[0], v[1], v[2]);
                                out->Set(v[0], v[1], v[2]);
                                return;
                            }
                            float* v = (float*)dBodyGetLinearVel(temp_r3_3->m_bodyID);
                            // just to fix regswap
                            // out->x = v[0];
                            // out->y = v[1];
                            // out->z = v[2];
                            GLV_REGSWAP(out, v);
                            return;
                        }
                        float* v = (float*)dBodyGetLinearVel(temp_r5_3->m_bodyID);
                        // out->x = v[0];
                        // out->y = v[1];
                        // out->z = v[2];
                        GLV_REGSWAP(out, v);
                        return;
                    }
                    float* v = (float*)dBodyGetLinearVel(temp_r3_2->m_bodyID);
                    // out->x = v[0];
                    // out->y = v[1];
                    // out->z = v[2];
                    GLV_REGSWAP(out, v);
                    return;
                }
                float* v = (float*)dBodyGetLinearVel(temp_r5_2->m_bodyID);
                // out->x = v[0];
                // out->y = v[1];
                // out->z = v[2];
                GLV_REGSWAP(out, v);
                return;
            }
            float* v = (float*)dBodyGetLinearVel(temp_r3->m_bodyID);
            // out->x = v[0];
            // out->y = v[1];
            // out->z = v[2];
            GLV_REGSWAP(out, v);
            return;
        }
        float* v = (float*)dBodyGetLinearVel(temp_r5->m_bodyID);
        // out->x = v[0];
        // out->y = v[1];
        // out->z = v[2];
        GLV_REGSWAP(out, v);
        return;
    }
    float* v = (float*)dBodyGetLinearVel(m_bodyID);
    // out->x = v[0];
    // out->y = v[1];
    // out->z = v[2];
    GLV_REGSWAP(out, v);
}

/**
 * Offset/Address/Size: 0xA00 | 0x802006FC | size: 0x30
 */
void PhysicsObject::SetLinearVelocity(const nlVector3& velocity)
{
    dBodySetLinearVel(m_bodyID, velocity.f.x, velocity.f.y, velocity.f.z);
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
            dGeomID temp_r0_3 = temp_r29_2->m_geomID;
            dMatrix3* parent_parent_rot; // var_r30
            if ((temp_r0_3 == 0U) && ((u32)temp_r29_2->m_bodyID != 0U))
            {
                parent_parent_rot = (dMatrix3*)dBodyGetRotation(temp_r29_2->m_bodyID);
            }
            else
            {
                parent_parent_rot = (dMatrix3*)dGeomGetRotation(temp_r0_3);
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
 * Offset/Address/Size: 0xD50 | 0x80200A4C | size: 0x34
 */
nlVector3* PhysicsObject::GetPosition()
{
    GetPosition(&m_position);
    return &m_position;
}

#define GP_REGSWAP(out, v) \
    float z = (v)->z;      \
    float y = (v)->y;      \
    float x = (v)->x;      \
    (out)->x = x;          \
    (out)->y = y;          \
    (out)->z = z;

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
    dGeomID temp_r0_2;
    dGeomID temp_r0_3;
    dGeomID temp_r0_4;
    dGeomID temp_r0_5;
    dGeomID temp_r0_6;
    PhysicsObject* temp_r28;
    PhysicsObject* temp_r28_2;
    PhysicsObject* temp_r29;
    PhysicsObject* temp_r29_2;
    PhysicsObject* temp_r29_3;
    nlVector3* var_r3;
    nlVector3* var_r3_2;
    nlVector3* var_r4;

    if ((m_geomID == NULL) && (m_bodyID != NULL))
    {
        var_r3 = (nlVector3*)dBodyGetPosition(m_bodyID);
    }
    else
    {
        var_r3 = (nlVector3*)dGeomGetPosition(m_geomID);
    }
    temp_r29 = m_parentObject;

    // just for regswap fixing...
    // position->x = var_r3->x;
    // position->y = var_r3->y;
    // position->z = var_r3->z;
    // GP_REGSWAP(position, var_r3);
    float x = var_r3->f.x;
    float y = var_r3->f.y;
    float z = var_r3->f.z;
    position->f.x = x;
    position->f.y = y;
    position->f.z = z;

    if (temp_r29 != NULL)
    {
        temp_r0_2 = temp_r29->m_geomID;
        if ((temp_r0_2 == NULL) && (temp_r29->m_bodyID != NULL))
        {
            var_r3_2 = (nlVector3*)dBodyGetPosition(temp_r29->m_bodyID);
        }
        else
        {
            var_r3_2 = (nlVector3*)dGeomGetPosition(temp_r0_2);
        }

        // just for regswap fixing...
        // sp20.z = var_r3_2->z;
        // sp20.y = var_r3_2->y;
        // sp20.x = var_r3_2->x;
        // GP_REGSWAP(&sp20, var_r3_2);
        float y = var_r3_2->f.y;
        float x = var_r3_2->f.x;
        float z = var_r3_2->f.z;
        sp20.f.x = x;
        sp20.f.y = y;
        sp20.f.z = z;

        temp_r28 = temp_r29->m_parentObject;
        if (temp_r28 != NULL)
        {
            temp_r0_3 = temp_r28->m_geomID;
            if ((temp_r0_3 == NULL) && ((u32)temp_r28->m_bodyID != NULL))
            {
                var_r4 = (nlVector3*)dBodyGetPosition(temp_r28->m_bodyID);
            }
            else
            {
                var_r4 = (nlVector3*)dGeomGetPosition(temp_r0_3);
            }
            sp14.Set(var_r4->f.x, var_r4->f.y, var_r4->f.z);
            if (temp_r28->m_parentObject != NULL)
            {
                temp_r28->m_parentObject->GetPosition(&sp8);
                temp_r28->m_parentObject->GetRotation(&spAC);
                nlMultPosVectorMatrix(sp14, sp14, spAC);
                nlVecAdd(sp14, sp8, sp14);
            }
            temp_r29_2 = temp_r29->m_parentObject;
            temp_r0_4 = temp_r29_2->m_geomID;

            if ((temp_r0_4 == NULL) && ((u32)temp_r29_2->m_bodyID != NULL))
            {
                r = (float*)dBodyGetRotation(temp_r29_2->m_bodyID);
            }
            else
            {
                r = (float*)dGeomGetRotation(temp_r0_4);
            }
            ConvertDMat3ToNLMat4(r, &sp12C);

            if (temp_r29_2->m_parentObject != NULL)
            {
                temp_r29_2->m_parentObject->GetRotation(&sp6C);
                nlMultMatrices(sp12C, sp12C, sp6C);
            }
            nlMultPosVectorMatrix(sp20, sp20, sp12C);
            sp20.Set(sp14.f.x + sp20.f.x, sp14.f.y + sp20.f.y, sp14.f.z + sp20.f.z);
        }
        temp_r29_3 = m_parentObject;
        temp_r0_5 = temp_r29_3->m_geomID;
        if ((temp_r0_5 == NULL) && ((u32)temp_r29_3->m_bodyID != NULL))
        {
            // var_r30 = (dMatrix3*)dBodyGetRotation(temp_r29_3->m_bodyID);
            r = (float*)dBodyGetRotation(temp_r29_3->m_bodyID);
        }
        else
        {
            // var_r30 = (dMatrix3*)dGeomGetRotation(temp_r0_5);
            r = (float*)dGeomGetRotation(temp_r0_5);
        }

        // sp16C.SetColumn(0, *(nlVector3*)var_r30);
        // sp16C.SetColumn(1, *(nlVector3*)var_r30[4]);
        // sp16C.SetColumn(2, *(nlVector3*)var_r30[8]);
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

        temp_r28_2 = temp_r29_3->m_parentObject;
        if (temp_r28_2 != NULL)
        {
            temp_r0_6 = temp_r28_2->m_geomID;
            if ((temp_r0_6 == NULL) && (temp_r28_2->m_bodyID != NULL))
            {
                r = (float*)dBodyGetRotation(temp_r28_2->m_bodyID);
            }
            else
            {
                r = (float*)dGeomGetRotation(temp_r0_6);
            }
            ConvertDMat3ToNLMat4(r, &spEC);
            if (temp_r28_2->m_parentObject != NULL)
            {
                temp_r28_2->m_parentObject->GetRotation(&sp2C);
                nlMultMatrices(spEC, spEC, sp2C);
            }
            nlMultMatrices(sp16C, sp16C, spEC);
        }
        nlMultPosVectorMatrix(*position, *position, sp16C);
        // just for regswap fixing...
        // position->x += sp20.x;
        // position->y += sp20.y;
        // position->z += sp20.z;
        float z1 = position->f.z;
        float y1 = position->f.y;
        float x1 = position->f.x;
        x = sp20.f.x;
        y = sp20.f.y;
        z = sp20.f.z;
        position->f.x = x + x1;
        position->f.z = z + z1;
        position->f.y = y + y1;
    }
}

/**
 * Offset/Address/Size: 0x10B0 | 0x80200DAC | size: 0x118
 */
void PhysicsObject::SetPosition(const nlVector3& pos, PhysicsObject::CoordinateType type)
{
    nlMatrix4 rot;         // sp54
    nlMatrix4 inv_rot;     // sp14
    nlVector3* p;          // temp_r3
    volatile nlVector4 v4; // sp84...sp90
    nlVector3 _pos;        // sp8...sp10

    if ((m_parentObject != NULL) && (type == 0))
    {
        m_parentObject->GetRotation(&rot);
        p = m_parentObject->GetPosition();
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
 * Offset/Address/Size: 0x11C8 | 0x80200EC4 | size: 0x20
 */
void PhysicsObject::PostUpdate()
{
    CheckForNaN();
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
 * Offset/Address/Size: 0x12A8 | 0x80200FA4 | size: 0x24
 */
void PhysicsObject::SetCategory(unsigned int categoryBits)
{
    dGeomSetCategoryBits(m_geomID, categoryBits);
}

/**
 * Offset/Address/Size: 0x12CC | 0x80200FC8 | size: 0x24
 */
void PhysicsObject::SetCollide(unsigned int collideBits)
{
    dGeomSetCollideBits(m_geomID, collideBits);
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
        m_bodyID = dBodyCreate(world->m_worldID);
        dBodySetData(m_bodyID, this);
        dBodySetGravityMode(m_bodyID, 0);
    }
}

/**
 * Offset/Address/Size: 0x0 | 0x80201130 | size: 0x10
 */
void nlVector3::Set(float x, float y, float z)
{
    this->f.x = x;
    this->f.y = y;
    this->f.z = z;
}

/**
 * Offset/Address/Size: 0x10 | 0x80201140 | size: 0x24
 */
void nlMatrix4::SetColumn(int col, const nlVector3& v)
{
    m[0][col] = v.f.x;
    m[1][col] = v.f.y;
    m[2][col] = v.f.z;
}

/**
 * Offset/Address/Size: 0x34 | 0x80201164 | size: 0x34
 */
void nlVecAdd(nlVector3& v0, const nlVector3& v1, const nlVector3& v2)
{
    // v0.x = v1.x + v2.x;
    // v0.y = v1.y + v2.y;
    // v0.z = v1.z + v2.z;
    float x1 = v1.f.x;
    float y1 = v1.f.y;
    float x2 = v2.f.x;
    float z1 = v1.f.z;
    float y2 = v2.f.y;
    float z2 = v2.f.z;
    v0.f.x = x1 + x2;
    v0.f.y = y1 + y2;
    v0.f.z = z1 + z2;
}
