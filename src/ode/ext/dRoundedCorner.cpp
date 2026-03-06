#include "ode/ext/dRoundedCorner.h"
#include "ode/ext/dColumn.h"
#include "math.h"

s32 dRoundedCornerClassUser = -1;
extern s32 dColumnClassUser;

struct RoundedCornerData
{
    float param;
    u8 flag1;
    u8 flag2;
};

struct AABBDimensions
{
    float minX;
    float maxX;
    float minY;
    float maxY;
    float minZ;
    float maxZ;
};

/**
 * Offset/Address/Size: 0x520 | 0x8021DFE8 | size: 0xD4
 */
void dRoundedCornerAABB(dxGeom* geomID, float* aabb)
{
    float temp_f31;
    float p_x;
    float p_y;
    float var_f2;
    float var_f3;
    u32 temp_r31;
    u32 temp_r30;
    RoundedCornerData* data;
    float* position;

    data = (RoundedCornerData*)dGeomGetClassData(geomID);
    temp_f31 = data->param;
    temp_r31 = data->flag1;
    temp_r30 = data->flag2;
    position = (float*)dGeomGetPosition(geomID);
    p_x = position[0];
    p_y = position[1];
    var_f2 = p_x;
    var_f3 = p_y;
    if (temp_r31 != 0)
    {
        var_f2 = p_x + temp_f31;
    }
    if (temp_r31 == 0)
    {
        p_x -= temp_f31;
    }
    if (temp_r30 != 0)
    {
        var_f3 += temp_f31;
    }
    if (temp_r30 == 0)
    {
        p_y -= temp_f31;
    }

    aabb[0] = p_x;
    aabb[1] = var_f2;
    aabb[2] = p_y;
    aabb[3] = var_f3;
    aabb[4] = -*(float*)&__float_max;
    aabb[5] = *(float*)&__float_max;
}

/**
 * Offset/Address/Size: 0x30C | 0x8021DDD4 | size: 0x214
 */
int dCollideRoundedCornerSphere(dxGeom* cornerGeomID, dxGeom* sphereGeomID, int, dContactGeom* contact, int)
{
    f32 sp8;
    f32 s_radius;
    f32 c_param;
    f32 temp_f3;
    f32 temp_f4;
    f32 temp_f5;
    f32 temp_f5_2;
    f32 temp_f6;
    f32 var_f7;
    f64 temp_f1;
    f64 temp_f1_2;
    f64 temp_f1_3;
    s32 temp_r4;
    s32 var_r0;
    s32 var_r0_2;
    u32 c_flag2;
    u32 c_flag1;
    float* c_pos;
    RoundedCornerData* cornerData;
    float* s_pos;

    cornerData = (RoundedCornerData*)dGeomGetClassData(cornerGeomID);
    c_param = cornerData->param;
    c_flag1 = cornerData->flag1;
    c_flag2 = cornerData->flag2;
    s_radius = dGeomSphereGetRadius(sphereGeomID);
    c_pos = (float*)dGeomGetPosition(cornerGeomID);
    s_pos = (float*)dGeomGetPosition(sphereGeomID);
    temp_f5 = s_pos[1] - c_pos[1];
    temp_f6 = s_pos[0] - c_pos[0];

    if (((u32)(temp_f6 > 0.0f) != c_flag1) || ((u32)(temp_f5 > 0.0f) != c_flag2))
    {
        var_r0 = 0;
    }
    else
    {
        temp_f4 = c_param - s_radius;
        var_f7 = (temp_f6 * temp_f6) + (temp_f5 * temp_f5);
        // M2C_ERROR(/* unknown instruction: cror eq, gt, eq */);
        if (var_f7 == (temp_f4 * temp_f4))
        {
            if (var_f7 > 0.0f)
            {
                temp_f1 = __frsqrte(var_f7);
                temp_f1_2 = 0.5 * temp_f1 * -(((f64)var_f7 * (temp_f1 * temp_f1)) - 3.0);
                temp_f1_3 = 0.5 * temp_f1_2 * -(((f64)var_f7 * (temp_f1_2 * temp_f1_2)) - 3.0);
                var_f7 = (f32)((f64)var_f7 * (0.5 * temp_f1_3 * -(((f64)var_f7 * (temp_f1_3 * temp_f1_3)) - 3.0)));
            }
            else if (var_f7 < 0.0)
            {
                var_f7 = *(float*)&__float_nan;
            }
            else
            {
                sp8 = var_f7;
                temp_r4 = *(s32*)&sp8 & 0x7F800000;
                switch (temp_r4)
                { /* irregular */
                case 0x7F800000:
                    if (*(s32*)&sp8 & 0x7FFFFF)
                    {
                        var_r0_2 = 1;
                    }
                    else
                    {
                        var_r0_2 = 2;
                    }
                    break;
                case 0x0:
                    if (*(s32*)&sp8 & 0x7FFFFF)
                    {
                        var_r0_2 = 5;
                    }
                    else
                    {
                        var_r0_2 = 3;
                    }
                    break;
                default:
                    var_r0_2 = 4;
                    break;
                }
                if (var_r0_2 == 1)
                {
                    var_f7 = *(float*)&__float_nan;
                }
            }

            temp_f3 = temp_f6 / var_f7;
            var_r0 = 1;
            temp_f5_2 = temp_f5 / var_f7;

            contact->pos[0] = (f32)((c_param * temp_f3) + c_pos[0]);
            contact->pos[1] = (f32)((c_param * temp_f5_2) + c_pos[1]);
            contact->pos[2] = (f32)c_pos[2];
            contact->normal[0] = temp_f3;
            contact->normal[1] = temp_f5_2;
            contact->normal[2] = 0.0f;
            contact->depth = (f32)(var_f7 - temp_f4);
            contact->g1 = cornerGeomID;
            contact->g2 = sphereGeomID;
        }
        else
        {
            var_r0 = 0;
        }
    }
    return var_r0;
}

/**
 * Offset/Address/Size: 0x104 | 0x8021DBCC | size: 0x208
 */
int dCollideRoundedCornerColumn(dxGeom* cor_GeomID, dxGeom* col_GeomID, int, dContactGeom* contact, int)
{
    dVector4 spC;
    f32 sp8;
    f32 cor_param;
    f32 temp_f3;
    f32 temp_f4;
    f32 temp_f5;
    f32 temp_f5_2;
    f32 temp_f6;
    f32 var_f7;
    f64 temp_f1;
    f64 temp_f1_2;
    f64 temp_f1_3;
    s32 temp_r4;
    s32 var_r0;
    s32 var_r0_2;
    u8 cor_flag2;
    u8 cor_flag1;
    float* cor_pos;
    RoundedCornerData* c_data;
    float* col_pos;

    c_data = (RoundedCornerData*)dGeomGetClassData(cor_GeomID);
    cor_param = c_data->param;
    cor_flag1 = c_data->flag1;
    cor_flag2 = c_data->flag2;
    dGeomColumnGetParams(col_GeomID, spC);
    cor_pos = (float*)dGeomGetPosition(cor_GeomID);
    col_pos = (float*)dGeomGetPosition(col_GeomID);
    temp_f5 = col_pos[1] - cor_pos[1];
    temp_f6 = col_pos[0] - cor_pos[0];
    if (((u32)(temp_f6 > 0.0f) != cor_flag1) || ((u32)(temp_f5 > 0.0f) != cor_flag2))
    {
        var_r0 = 0;
    }
    else
    {
        temp_f4 = cor_param - spC[0];
        var_f7 = (temp_f6 * temp_f6) + (temp_f5 * temp_f5);
        // M2C_ERROR(/* unknown instruction: cror eq, gt, eq */);
        if (var_f7 == (temp_f4 * temp_f4))
        {
            if (var_f7 > 0.0f)
            {
                temp_f1 = __frsqrte(var_f7);
                temp_f1_2 = 0.5 * temp_f1 * -(((f64)var_f7 * (temp_f1 * temp_f1)) - 3.0);
                temp_f1_3 = 0.5 * temp_f1_2 * -(((f64)var_f7 * (temp_f1_2 * temp_f1_2)) - 3.0);
                var_f7 = (f32)((f64)var_f7 * (0.5 * temp_f1_3 * -(((f64)var_f7 * (temp_f1_3 * temp_f1_3)) - 3.0)));
            }
            else if (var_f7 < 0.0)
            {
                var_f7 = *(float*)&__float_nan;
            }
            else
            {
                sp8 = var_f7;
                temp_r4 = *(s32*)&sp8 & 0x7F800000;
                switch (temp_r4)
                { /* irregular */
                case 0x7F800000:
                    if (*(s32*)&sp8 & 0x7FFFFF)
                    {
                        var_r0_2 = 1;
                    }
                    else
                    {
                        var_r0_2 = 2;
                    }
                    break;
                case 0x0:
                    if (*(s32*)&sp8 & 0x7FFFFF)
                    {
                        var_r0_2 = 5;
                    }
                    else
                    {
                        var_r0_2 = 3;
                    }
                    break;
                default:
                    var_r0_2 = 4;
                    break;
                }
                if (var_r0_2 == 1)
                {
                    var_f7 = *(float*)&__float_nan;
                }
            }
            temp_f3 = temp_f6 / var_f7;
            var_r0 = 1;
            temp_f5_2 = temp_f5 / var_f7;
            contact->pos[0] = (f32)((cor_param * temp_f3) + cor_pos[0]);
            contact->pos[1] = (f32)((cor_param * temp_f5_2) + cor_pos[1]);
            contact->pos[2] = (f32)col_pos[2];
            contact->normal[0] = temp_f3;
            contact->normal[1] = temp_f5_2;
            contact->normal[2] = 0.0f;
            contact->depth = (f32)(var_f7 - temp_f4);
            contact->g1 = cor_GeomID;
            contact->g2 = col_GeomID;
        }
        else
        {
            var_r0 = 0;
        }
    }
    return var_r0;
}

/**
 * Offset/Address/Size: 0xD0 | 0x8021DB98 | size: 0x34
 */
dColliderFn* dRoundedCornerColliderFn(int num)
{
    if (num == 0)
    {
        return &dCollideRoundedCornerSphere;
    }

    if (num == dColumnClassUser)
    {
        return &dCollideRoundedCornerColumn;
    }

    return NULL;
}

/**
 * Offset/Address/Size: 0x0 | 0x8021DAC8 | size: 0xD0
 * TODO: 95% match - epilogue lwz r0 (LR restore) scheduled before register restores
 *       instead of after. All decomp.me MWCC compilers exhibit this behavior.
 */
dGeomID dCreateRoundedCorner(dxSpace* space, float param, bool flag1, bool flag2)
{
    RoundedCornerData* data;
    dGeomClass geomClass;
    dGeomID geomID;

    if ((s32)dRoundedCornerClassUser == -1)
    {
        geomClass.bytes = 8;
        geomClass.collider = &dRoundedCornerColliderFn;
        geomClass.aabb = &dRoundedCornerAABB;
        geomClass.aabb_test = 0;
        geomClass.dtor = 0;
        dRoundedCornerClassUser = dCreateGeomClass(&geomClass);
    }

    geomID = dCreateGeom(dRoundedCornerClassUser);
    if (space != 0U)
    {
        dSpaceAdd(space, geomID);
    }

    data = (RoundedCornerData*)dGeomGetClassData(geomID);
    data->param = param;
    data->flag1 = flag1;
    data->flag2 = flag2;

    return geomID;
}
