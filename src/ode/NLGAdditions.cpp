#include "ode/NLGAdditions.h"

#include "NL/nlMath.h"
#include "ode/matrix.h"
#include "objects.h"
#include "joint.h"
#include "collision_kernel.h"

static dxJoint* createJoint(dWorldID w, dJointGroupID group, dxJoint::Vtable* vtable);

/**
 * Offset/Address/Size: 0x0 | 0x802242C8 | size: 0x140
 */
void dGeomCollideAABBs(dxGeom* arg0, dxGeom* arg1, void* arg2, void (*arg3)(void*, dxGeom*, dxGeom*))
{
    u8 var_r4;
    dBodyID temp_r3;
    float* aabb_0;
    float* aabb_1;

    temp_r3 = arg0->body;
    if ((temp_r3 != arg1->body) || (temp_r3 == 0U))
    {
        var_r4 = 0;
        if ((arg0->category_bits & arg1->collide_bits) || (arg1->category_bits & arg0->collide_bits))
        {
            var_r4 = 1;
        }
        if (var_r4 != 0)
        {
            aabb_0 = arg0->aabb;
            aabb_1 = arg1->aabb;
            if (!(aabb_0[0] > aabb_1[1])
                && !(aabb_0[1] < aabb_1[0])
                && !(aabb_0[2] > aabb_1[3])
                && !(aabb_0[3] < aabb_1[2])
                && !(aabb_0[4] > aabb_1[5])
                && !(aabb_0[5] < aabb_1[4])
                && (arg0->AABBTest(arg1, aabb_1) != 0)
                && (arg1->AABBTest(arg0, aabb_0) != 0))
            {
                arg3(arg2, arg0, arg1);
            }
        }
    }
}

/**
 * Offset/Address/Size: 0x140 | 0x80224408 | size: 0x10
 */
void dGeomMarkAABBAsValid(dxGeom* geomID)
{
    geomID->gflags = geomID->gflags & 0xFFFFFFFC;
}

/**
 * Offset/Address/Size: 0x150 | 0x80224418 | size: 0x44
 */
void dGeomComputeAABB(dxGeom* geomID)
{
    geomID->computeAABB();
    geomID->gflags = (s32)(geomID->gflags & 0xFFFFFFFC);
}

/**
 * Offset/Address/Size: 0x194 | 0x8022445C | size: 0x34
 */
void dVector3Add(float* __restrict v1, const float* __restrict v2)
{
    v1[0] += v2[0];
    v1[1] += v2[1];
    v1[2] += v2[2];
}

/**
 * Offset/Address/Size: 0x1C8 | 0x80224490 | size: 0x28
 */
void dVectorScale(float* v1, float arg8)
{
    v1[0] = (f32)(v1[0] * arg8);
    v1[1] = (f32)(v1[1] * arg8);
    v1[2] = (f32)(v1[2] * arg8);
}

/**
 * Offset/Address/Size: 0x1F0 | 0x802244B8 | size: 0x14
 */
void dVector4Set(float* v, float x, float y, float z, float w)
{
    v[0] = x;
    v[1] = y;
    v[2] = z;
    v[3] = w;
}

/**
 * Offset/Address/Size: 0x204 | 0x802244CC | size: 0x10
 */
void dVector3Set(float* v, float x, float y, float z)
{
    v[0] = x;
    v[1] = y;
    v[2] = z;
}

/**
 * Offset/Address/Size: 0x214 | 0x802244DC | size: 0x24
 */
void dExtractColumn3(float* __restrict arg0, const float* __restrict arg1, int col)
{
    float v0;

    v0 = arg1[col];
    arg1 += col;
    arg0[0] = v0;
    arg0[1] = arg1[4];
    arg0[2] = arg1[8];
}

/**
 * Offset/Address/Size: 0x238 | 0x80224500 | size: 0xDC
 * TODO: 93.91% match - prologue instruction scheduling: target interleaves
 * lfs f0/f1 loads at offsets 8/18 (during prologue setup), our compiler
 * places them at 24/28 (after prologue). Same instructions, different order.
 * Likely -inline auto,deferred scheduling pass difference.
 */
void dInvertRigidTransformation(float* param_1, const float* param_2, const float* param_3)
{
    float a = param_2[0], b = param_2[4];
    float v[3];

    param_1[0] = a;
    a = param_2[8];
    param_1[1] = b;
    b = param_2[1];
    param_1[2] = a;
    a = param_2[5];
    param_1[4] = b;
    b = param_2[9];
    param_1[5] = a;
    a = param_2[2];
    param_1[6] = b;
    b = param_2[6];
    param_1[8] = a;
    a = param_2[10];
    param_1[9] = b;
    param_1[10] = a;

    dMultiply0(v, param_1, param_3, 3, 3, 1);

    float neg = -1.0f;
    v[0] *= neg;
    v[1] *= neg;
    v[2] *= neg;

    param_1[3] = v[0];
    param_1[7] = v[1];
    param_1[11] = v[2];
    param_1[12] = 0.0f;
    param_1[13] = 0.0f;
    param_1[14] = 0.0f;
    param_1[15] = 1.0f;
}

/**
 * Offset/Address/Size: 0x314 | 0x802245DC | size: 0x2C
 */
void dMultiplyMatrix4Vector4(float* m1, const float* m2, const float* m3)
{
    dMultiply0(m1, m2, m3, 4, 4, 1);
}

/**
 * Offset/Address/Size: 0x340 | 0x80224608 | size: 0x88
 */
void dMultiplyMatrix3Vector3(float* result, const float* R, const float* v, bool transposeMatrix)
{
    if (!transposeMatrix)
    {
        dMultiply0(result, R, v, 3, 3, 1);
    }
    if (transposeMatrix)
    {
        dMultiply1(result, R, v, 3, 3, 1);
    }
}

/**
 * Offset/Address/Size: 0x3C8 | 0x80224690 | size: 0x8
 */
void dGeomSetGFlags(dxGeom* geom, int flags)
{
    geom->gflags = flags;
}

/**
 * Offset/Address/Size: 0x3D0 | 0x80224698 | size: 0x8
 */
int dGeomGetGFlags(dxGeom* geom)
{
    return geom->gflags;
}

/**
 * Offset/Address/Size: 0x3D8 | 0x802246A0 | size: 0x1C
 */
void dJointSetCharacterNoMotionDirection(dxJoint* joint, nlVector3* v3)
{
    // *(undefined4 *)(param_1 + 0x50) = *param_2;
    // *(undefined4 *)(param_1 + 0x54) = param_2[1];
    // *(undefined4 *)(param_1 + 0x58) = param_2[2];
    // joint->node[0].
}

extern dxJoint::Vtable __dcharacter_vtable;

/**
 * Offset/Address/Size: 0x3F4 | 0x802246BC | size: 0x28
 */
dxJoint* dJointCreateCharacter(dxWorld* world, dxJointGroup* jointGroup)
{
    return createJoint(world, jointGroup, &__dcharacter_vtable);
}

static inline dReal nlgDot(const dReal* a, const dReal* b)
{
    return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

/**
 * Offset/Address/Size: 0x41C | 0x802246E4 | size: 0x160
 */
void characterGetInfo2(dxJointCharacter* j, dxJoint::Info2* info)
{
    // Row 0: angular identity
    info->J1a[0] = 1;
    info->c[0] = 0;
    info->lo[0] = -dInfinity;
    info->hi[0] = dInfinity;

    // Row 1
    {
        int row = info->rowskip + 1;
        info->J1a[row] = 1;
    }
    info->c[1] = 0;
    info->lo[1] = -dInfinity;
    info->hi[1] = dInfinity;

    // Row 2
    {
        int row = info->rowskip * 2 + 2;
        info->J1a[row] = 1;
    }
    info->c[2] = 0;
    info->lo[2] = -dInfinity;
    info->hi[2] = dInfinity;

    // Row 3: linear Jacobian = body R * direction
    dxBody* body = ((dxJoint*)j)->node[0].body;
    dReal* R = (dReal*)((u8*)body + 0xB8);
    unsigned int jStart = info->rowskip * 3;

    dReal v0 = nlgDot(R, j->m_unk_0x50);
    dReal v1 = nlgDot(R + 4, j->m_unk_0x50);
    dReal v2 = nlgDot(R + 8, j->m_unk_0x50);

    info->J1l[jStart] = v0;
    {
        unsigned int idx = jStart + 1;
        info->J1l[idx] = v1;
    }
    {
        unsigned int idx = jStart + 2;
        info->J1l[idx] = v2;
    }

    info->c[3] = 0;
    info->lo[3] = -dInfinity;
    info->hi[3] = dInfinity;
}

/**
 * Offset/Address/Size: 0x57C | 0x80224844 | size: 0x14
 */
static void characterGetInfo1(dxJointCharacter* joint, dxJoint::Info1* info)
{
    info->m = 4;
    info->nub = 0;
}

/**
 * Offset/Address/Size: 0x590 | 0x80224858 | size: 0x14
 */
void characterInit(dxJointCharacter* character)
{
    // character->unk50 = 0.f;
    // character->unk54 = 0.f;
    // character->unk58 = 0.f;
    character->m_unk_0x50[0] = 0.f;
    character->m_unk_0x50[1] = 0.f;
    character->m_unk_0x50[2] = 0.f;
}

/**
 * Offset/Address/Size: 0x5A4 | 0x8022486C | size: 0x4
 */
void dClearCachedData()
{
}

/**
 * Offset/Address/Size: 0x5A8 | 0x80224870 | size: 0x8
 */
void dWorldSetClearAccumulators(dxWorld* world, int flags)
{
    world->clear_accumulators = flags;
}

/**
 * Offset/Address/Size: 0x5B0 | 0x80224878 | size: 0x8
 */
dxBody* dBodyGetNextBody(dxBody* body)
{
    return (dxBody*)body->next;
}

/**
 * Offset/Address/Size: 0x5B8 | 0x80224880 | size: 0x8
 */
dxBody* dWorldGetFirstBody(dxWorld* world)
{
    return world->firstbody;
}

/**
 * Offset/Address/Size: 0x5C0 | 0x80224888 | size: 0x38
 */
void dBodySetUpdateMode(dxBody* body, int arg1, int arg2)
{
    body->flags = (s32)(body->flags & 0xFFFFFF9F);
    if (arg1 == 0)
    {
        body->flags = (s32)(body->flags | 0x20);
    }
    if (arg2 == 0)
    {
        body->flags = (s32)(body->flags | 0x40);
    }
}
