#include "NL/nlMath.h"

/**
 * Offset/Address/Size: 0x540 | 0x801F083C | size: 0x88
 */
void nlCartesianToPolar(nlPolar& out, float x, float y)
{
    float lenSq = x * x + y * y;
    out.r = nlSqrt(lenSq, true);
    float angle = nlATan2f(y, x);
    out.a = (u16)(s32)(angle * 10430.378f);
}

/**
 * Offset/Address/Size: 0x4D4 | 0x801F07D0 | size: 0x6C
 */
void nlPolarToCartesian(float& x, float& y, unsigned short angle, float radius)
{
    float* x_ptr = &x;
    float* y_ptr = &y;
    nlSinCos(y_ptr, x_ptr, angle);
    *x_ptr *= radius;
    *y_ptr *= radius;
}

/**
 * Offset/Address/Size: 0x46C | 0x801F0768 | size: 0x68
 * TODO: 84.4% match - MWCC register coalescing/scheduling difference: target
 * copies polar ptr to r5 and loads float before u16; our compiler uses r6 for
 */
void nlPolarToCartesian(nlVector3& v, const nlPolar& polar)
{
    f32 radius = polar.r;
    nlSinCos(&v.f.y, &v.f.x, polar.a);
    v.f.x *= radius;
    v.f.y *= radius;
}
/**
 * Offset/Address/Size: 0x3EC | 0x801F06E8 | size: 0x80
 * TODO: 96.2% match - MWCC instruction scheduling: target loads lfs (polar.r)
 * before lhz (polar.a), our compiler schedules lhz before lfs
 */
void nlAddPolarToCartesian(nlVector3& result, const nlPolar& polar)
{
    f32 radius = polar.r;
    f32 cos_val, sin_val;
    nlSinCos(&sin_val, &cos_val, polar.a);
    cos_val *= radius;
    sin_val *= radius;
    result.f.x += cos_val;
    result.f.y += sin_val;
}

/**
 * Offset/Address/Size: 0x364 | 0x801F0660 | size: 0x88
 */
void nlCartesianToPolar(nlPolar& out, const nlVector3& in)
{
    float x = in.f.x;
    float y = in.f.y;
    float lenSq = x * x + y * y;
    out.r = nlSqrt(lenSq, true);
    float angle = nlATan2f(y, x);
    out.a = (u16)(s32)(angle * 10430.378f);
}

/**
 * Offset/Address/Size: 0x2B8 | 0x801F05B4 | size: 0xAC
 */
void nlMakeQuat(nlQuaternion& out, const nlVector3& v3RotationAxis, float ang_rad)
{
    f32 temp_f31;
    f32 temp_f1;
    s32 temp_r31;

    temp_r31 = 0.5f * (ang_rad * 10430.378f);

    temp_f31 = nlSin((u16)temp_r31 + 0x4000);
    temp_f1 = nlSin((u16)temp_r31);

    out.f.x = v3RotationAxis.f.x * temp_f1;
    out.f.y = v3RotationAxis.f.y * temp_f1;
    out.f.z = v3RotationAxis.f.z * temp_f1;
    out.f.w = temp_f31;
}

/**
 * Offset/Address/Size: 0x268 | 0x801F0564 | size: 0x50
 */
void nlQuatNormalize(nlQuaternion& out, const nlQuaternion& in)
{
    float fLenSquared = nlQuatDot(in, in);
    float fOneOverSqrt = nlRecipSqrt(fLenSquared, true);
    nlQuatScale(out, in, fOneOverSqrt);
}
/**
 * Offset/Address/Size: 0x1E8 | 0x801F04E4 | size: 0x80
 */
void nlQuatInverse(nlQuaternion& out, const nlQuaternion& in)
{
    float fOneOverSqrt = nlRecipSqrt(nlQuatDot(in, in), true);

    out.f.x = -in.f.x * fOneOverSqrt;
    out.f.y = -in.f.y * fOneOverSqrt;
    out.f.z = -in.f.z * fOneOverSqrt;
    out.f.w = in.f.w * fOneOverSqrt;
}

/**
 * Offset/Address/Size: 0xA8 | 0x801F03A4 | size: 0x140
 */
void nlQuatNLerp(nlQuaternion& out, const nlQuaternion& q1, const nlQuaternion& q2, float t)
{
    float dot = nlQuatDot(q1, q2);
    if (dot > 0.0f)
    {
        out.f.x = t * (q2.f.x - q1.f.x) + q1.f.x;
        out.f.y = t * (q2.f.y - q1.f.y) + q1.f.y;
        out.f.z = t * (q2.f.z - q1.f.z) + q1.f.z;
        out.f.w = t * (q2.f.w - q1.f.w) + q1.f.w;
    }
    else
    {
        out.f.x = t * (-q2.f.x - q1.f.x) + q1.f.x;
        out.f.y = t * (-q2.f.y - q1.f.y) + q1.f.y;
        out.f.z = t * (-q2.f.z - q1.f.z) + q1.f.z;
        out.f.w = t * (-q2.f.w - q1.f.w) + q1.f.w;
    }
    float fOneOverSqrt = nlRecipSqrt(nlQuatDot(out, out), true);
    nlQuatScale(out, out, fOneOverSqrt);
}

/**
 * Offset/Address/Size: 0x0 | 0x801F02FC | size: 0xA8
 */
void nlInvertRotTransMatrix(nlMatrix4& out, const nlMatrix4& in)
{
    nlVector3 negResult;
    nlVector3 translation;
    ((u32*)&translation)[0] = *(u32*)&in.m[3][0];
    ((u32*)&translation)[1] = *(u32*)&in.m[3][1];
    ((u32*)&translation)[2] = *(u32*)&in.m[3][2];

    nlTransposeMatrix(out, in);

    out.m[2][3] = 0.0f;
    out.m[1][3] = 0.0f;
    out.m[0][3] = 0.0f;

    nlMultPosVectorMatrix(negResult, translation, out);

    nlVec3Set(negResult, -1.0f * negResult.f.x, -1.0f * negResult.f.y, -1.0f * negResult.f.z);

    out.m[3][0] = negResult.f.x;
    out.m[3][1] = negResult.f.y;
    out.m[3][2] = negResult.f.z;
    out.m[3][3] = 1.0f;
}
