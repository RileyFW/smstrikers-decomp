#include "ode/ext/dFinitePlane.h"
#include "ode/NLGAdditions.h"

s32 dFinitePlaneClassUser = -1;

struct FinitePlane
{
    float a;
    float b;
    float c;
    float d;
    bool flag;
    float param;
};

/**
 * Offset/Address/Size: 0x314 | 0x8021D718 | size: 0x3B0
 */
void dFinitePlaneAABB(dxGeom* geomID, float* aabb)
{
    dVector3 sp18[4];
    dVector3 sp8;

    f32* var_r31;
    f32* var_r3;
    f32 temp_f1;
    f32 temp_f1_10;
    f32 temp_f1_11;
    f32 temp_f1_12;
    f32 temp_f1_2;
    f32 temp_f1_3;
    f32 temp_f1_4;
    f32 temp_f1_5;
    f32 temp_f1_6;
    f32 temp_f1_7;
    f32 temp_f1_8;
    f32 temp_f1_9;
    f32 plane_param;
    f32 temp_f27_2;
    f32 plane_d;
    f32 plane_c;
    f32 plane_b;
    f32 plane_a;
    s32 var_ctr;
    s32 var_ctr_2;
    u32 plane_flag;

    float* rotation;
    float* position;

    FinitePlane* planeData;

    planeData = (FinitePlane*)dGeomGetClassData(geomID);
    plane_a = planeData->a;
    plane_b = planeData->b;
    plane_c = planeData->c;
    plane_d = planeData->d;
    plane_flag = planeData->flag;
    plane_param = planeData->param;
    rotation = (float*)dGeomGetRotation(geomID);
    position = (float*)dGeomGetPosition(geomID);

    dVector3Set(sp8, plane_a, plane_c, 0.0f);
    dMultiplyMatrix3Vector3(sp18[0], rotation, sp8, 0);
    dVector3Add(sp18[0], position);

    dVector3Set(sp8, plane_a, plane_d, 0.0f);
    // var_r31 = &sp28;
    dMultiplyMatrix3Vector3(sp18[1], rotation, sp8, 0);
    dVector3Add(sp18[1], position);

    dVector3Set(sp8, plane_b, plane_d, 0.0f);
    dMultiplyMatrix3Vector3(sp18[2], rotation, sp8, 0);
    dVector3Add(sp18[2], position);

    dVector3Set(sp8, plane_b, plane_c, 0.0f);
    dMultiplyMatrix3Vector3(sp18[3], rotation, sp8, 0);
    dVector3Add(sp18[3], position);

    aabb[0] = sp18[0][0];
    aabb[1] = sp18[0][0];
    aabb[2] = sp18[0][1];
    aabb[3] = sp18[0][1];
    aabb[4] = sp18[0][2];
    aabb[5] = sp18[0][2];

    var_r3 = sp18[1];
    for (int i = 3; i != 0; i--)
    {
        temp_f1 = var_r3[0];
        if (temp_f1 < aabb[0])
        {
            aabb[0] = temp_f1;
        }
        temp_f1_2 = var_r3[0];
        if (temp_f1_2 > aabb[1])
        {
            aabb[1] = temp_f1_2;
        }
        temp_f1_3 = var_r3[1];
        if (temp_f1_3 < aabb[2])
        {
            aabb[2] = temp_f1_3;
        }
        temp_f1_4 = var_r3[1];
        if (temp_f1_4 > aabb[3])
        {
            aabb[3] = temp_f1_4;
        }
        temp_f1_5 = var_r3[2];
        if (temp_f1_5 < aabb[4])
        {
            aabb[4] = temp_f1_5;
        }
        temp_f1_6 = var_r3[2];
        if (temp_f1_6 > aabb[5])
        {
            aabb[5] = temp_f1_6;
        }
        var_r3 += 4;
    }

    if (plane_flag != 0)
    {
        temp_f27_2 = -plane_param;
        dVector3Set(sp8, plane_a, plane_c, temp_f27_2);
        dMultiplyMatrix3Vector3(sp18[0], rotation, sp8, 0);
        dVector3Add(sp18[0], position);

        dVector3Set(sp8, plane_a, plane_d, temp_f27_2);
        dMultiplyMatrix3Vector3(sp18[1], rotation, sp8, 0);
        dVector3Add(sp18[0], position);

        dVector3Set(sp8, plane_b, plane_d, temp_f27_2);
        dMultiplyMatrix3Vector3(sp18[2], rotation, sp8, 0);
        dVector3Add(sp18[2], position);

        dVector3Set(sp8, plane_b, plane_c, temp_f27_2);
        dMultiplyMatrix3Vector3(sp18[3], rotation, sp8, 0);
        dVector3Add(sp18[3], position);

        var_r3 = sp18[1];
        for (int i = 3; i != 0; i--)
        {
            temp_f1 = var_r3[0];
            if (temp_f1 < aabb[0])
            {
                aabb[0] = temp_f1;
            }
            temp_f1_2 = var_r3[0];
            if (temp_f1_2 > aabb[1])
            {
                aabb[1] = temp_f1_2;
            }
            temp_f1_3 = var_r3[1];
            if (temp_f1_3 < aabb[2])
            {
                aabb[2] = temp_f1_3;
            }
            temp_f1_4 = var_r3[1];
            if (temp_f1_4 > aabb[3])
            {
                aabb[3] = temp_f1_4;
            }
            temp_f1_5 = var_r3[2];
            if (temp_f1_5 < aabb[4])
            {
                aabb[4] = temp_f1_5;
            }
            temp_f1_6 = var_r3[2];
            if (temp_f1_6 > aabb[5])
            {
                aabb[5] = temp_f1_6;
            }
            var_r3 += 4;
        }
    }
}

/**
 * Offset/Address/Size: 0x100 | 0x8021D504 | size: 0x214
 */
int dCollideFinitePlaneSphere(dxGeom* planeGeomID, dxGeom* sphereGeomID, int, dContactGeom* contact, int)
{
    dMatrix4 sp28;
    dVector3 sp18;
    dVector3 sp8;
    f32 plane_a;
    f32 plane_b;
    f32 plane_c;
    f32 plane_d;
    f32 radius;
    f32 plane_param;
    f32 var_f25;
    u32 plane_flag;
    float* plane_rot;
    float* plane_pos;
    float* sphere_pos;
    FinitePlane* planeData;

    planeData = (FinitePlane*)dGeomGetClassData(planeGeomID);
    plane_a = planeData->a;
    plane_b = planeData->b;
    plane_c = planeData->c;
    plane_d = planeData->d;
    plane_flag = planeData->flag;
    plane_param = planeData->param;
    radius = dGeomSphereGetRadius(sphereGeomID);
    plane_pos = (float*)dGeomGetPosition(planeGeomID);
    sphere_pos = (float*)dGeomGetPosition(sphereGeomID);
    plane_rot = (float*)dGeomGetRotation(planeGeomID);

    dInvertRigidTransformation(&sp28[0], plane_rot, plane_pos);
    dVector4Set(sp18, sphere_pos[0], sphere_pos[1], sphere_pos[2], 1.0f);
    dMultiplyMatrix4Vector4(&sp8[0], &sp28[0], sp18);

    if (plane_flag != 0)
    {
        var_f25 = sp8[2];
    }
    else
    {
        var_f25 = (f32)fabs(sp8[2]);
    }

    if ((var_f25 < radius) && (sp8[0] > plane_a) && (sp8[0] < plane_b) && (sp8[1] > plane_c) && (sp8[1] < plane_d))
    {
        dExtractColumn3(contact->normal, plane_rot, 2);
        if ((sp8[2] > 0.0f) || (plane_flag != 0))
        {
            dVectorScale(contact->normal, -1.0f);
        }

        contact->pos[0] = (f32)((contact->normal[0] * radius) + sphere_pos[0]);
        contact->pos[1] = (f32)((contact->normal[1] * radius) + sphere_pos[1]);
        contact->pos[2] = (f32)((contact->normal[2] * radius) + sphere_pos[2]);
        contact->depth = (f32)(radius - var_f25);

        if ((plane_param != -1.0f) && (contact->depth > plane_param))
        {
            return 0;
        }

        contact->g1 = planeGeomID;
        contact->g2 = sphereGeomID;
        return 1;
    }

    return 0;
}

/**
 * Offset/Address/Size: 0xE8 | 0x8021D4EC | size: 0x18
 */
dColliderFn* dFinitePlaneColliderFn(int num)
{
    if (num == 0)
    {
        return &dCollideFinitePlaneSphere;
    }
    return NULL;
}

/**
 * Offset/Address/Size: 0x0 | 0x8021D404 | size: 0xE8
 */
dGeomID dCreateFinitePlane(dSpaceID space, dReal a, dReal b, dReal c, dReal d, bool flag, float param)
{
    FinitePlane* planeData;
    dGeomClass geomClass;
    dGeomID geomID;

    if ((s32)dFinitePlaneClassUser == -1)
    {
        geomClass.bytes = 0x18;
        geomClass.collider = &dFinitePlaneColliderFn;
        geomClass.aabb = &dFinitePlaneAABB;
        geomClass.aabb_test = 0;
        geomClass.dtor = 0;
        dFinitePlaneClassUser = dCreateGeomClass(&geomClass);
    }

    geomID = dCreateGeom(dFinitePlaneClassUser);
    if (space != 0U)
    {
        dSpaceAdd(space, geomID);
    }

    planeData = (FinitePlane*)dGeomGetClassData(geomID);
    planeData->a = a;
    planeData->b = b;
    planeData->c = c;
    planeData->d = d;
    planeData->flag = flag;
    planeData->param = param;

    return geomID;
}
