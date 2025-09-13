#include "NL/nlMath.h"
#include "Dolphin/mtx.h"
#include "types.h"

#define qr0 0

/**
 * Offset/Address/Size: 0x0 | 0x801C439C | size: 0x2C
 */
void nlQuatScale(nlQuaternion& out, const nlQuaternion& in, float scale)
{
    PSQUATScale((Quaternion*)&in, (Quaternion*)&out, scale);
}

/**
 * Offset/Address/Size: 0x2C | 0x801C43C8 | size: 0x20
 */
f32 nlQuatDot(const nlQuaternion& q1, const nlQuaternion& q2)
{
    return PSQUATDotProduct((Quaternion*)&q1, (Quaternion*)&q2);
}

/**
 * Offset/Address/Size: 0x4C | 0x801C43E8 | size: 0x74
 */
void nlMultQuat(nlQuaternion& out, const nlQuaternion& q1, const nlQuaternion& q2)
{
    // Field offsets: unk0=x, unk4=y, unk8=z, unkC=w
    float x2 = q1.f.x;
    float x1 = q2.f.x;
    float w2 = q2.f.w;
    float w1 = q1.f.w;
    float z2 = q2.f.z;
    float y1 = q1.f.y;
    float y2 = q2.f.y;
    float z1 = q1.f.z;

    // Quaternion multiplication formula
    out.f.w = -((z1 * z2) + ((y1 * y2) - ((w1 * w2) - (x1 * x2))));
    out.f.x = -((z1 * y2) - ((y1 * z2) + ((w1 * x2) + (x1 * w2))));
    out.f.y = (z1 * x2) + ((y1 * w2) + ((w1 * y2) - (x1 * z2)));
    out.f.z = (z1 * w2) - ((y1 * x2) - ((w1 * z2) + (x1 * y2)));
}

/**
 * Offset/Address/Size: 0xC0 | 0x801C445C | size: 0x278
 */
void nlMatrixToQuat(nlQuaternion& out, const nlMatrix4& matrix)
{
    f32 sp60;
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    f32 sp34;
    f32 sp30;
    f32 sp2C;
    f32 sp28;
    f32 sp24;
    f32 sp20;
    s32 sp10;
    s32 spC;
    s32 sp8;
    f32 temp_f10;
    f32 temp_f1;
    f32 temp_f29;
    f32 temp_f30;
    f32 temp_f31;
    f32 temp_f5;
    f32 temp_f8;
    f32 var_f1;
    s32 temp_r0;
    s32 temp_r27;
    s32 temp_r29;
    s32 temp_r30;
    s32 temp_r4;
    s32 var_r5;
    f32* temp_r25;
    f32* temp_r26;
    f32* temp_r28;
    f32 sp14[4]; // Array to store quaternion components

    temp_f30 = matrix.m[0][0]; // m00
    temp_f10 = matrix.m[1][1]; // m11
    temp_f5 = matrix.m[2][2];  // m22
    temp_f31 = matrix.m[0][1]; // m01
    temp_f29 = temp_f5 + (temp_f30 + temp_f10);
    sp24 = temp_f30;
    sp28 = temp_f31;
    sp2C = matrix.m[0][2]; // m02
    sp30 = matrix.m[0][3]; // m03
    sp34 = matrix.m[1][0]; // m10
    sp38 = temp_f10;
    sp3C = matrix.m[1][2]; // m12
    sp40 = matrix.m[1][3]; // m13
    sp44 = matrix.m[2][0]; // m20
    sp48 = matrix.m[2][1]; // m21
    sp4C = temp_f5;
    sp50 = matrix.m[2][3]; // m23
    sp54 = matrix.m[3][0]; // m30
    sp58 = matrix.m[3][1]; // m31
    sp5C = matrix.m[3][2]; // m32
    sp60 = matrix.m[3][3]; // m33
    sp8 = 1.f;
    spC = 2.f;
    sp10 = 0.f;
    if (temp_f29 > 0.0)
    {
        temp_f1 = nlSqrt(1.0f + temp_f29, 1);
        temp_f8 = 0.5f / temp_f1;
        out.f.w = temp_f1 * 0.5f;
        out.f.x = temp_f8 * (sp3C - sp48);
        out.f.y = temp_f8 * (sp44 - sp2C);
        out.f.z = temp_f8 * (temp_f31 - sp34);
        return;
    }
    var_r5 = 0;
    if (temp_f10 > temp_f30)
    {
        var_r5 = 1;
    }
    if (temp_f5 > *(&sp24 + (var_r5 * 0x14)))
    {
        var_r5 = 2;
    }
    temp_r29 = var_r5 * 4;
    temp_r0 = (&sp8)[var_r5];
    temp_r30 = temp_r0 * 4;
    temp_r4 = (&sp8)[temp_r0];
    temp_r26 = &sp24 + (temp_r0 * 0x10);
    temp_r27 = temp_r4 * 4;
    temp_r28 = &sp24 + (temp_r4 * 0x10);
    temp_r25 = &sp24 + (var_r5 * 0x10);
    var_f1 = nlSqrt(1.0f + (*(temp_r25 + temp_r29) - (*(temp_r26 + temp_r30) + *(temp_r28 + temp_r27))), 1);
    sp14[var_r5] = 0.5f * var_f1;
    if (var_f1 != 0.0f)
    {
        var_f1 = 0.5f / var_f1;
    }
    sp20 = var_f1 * (*(temp_r26 + temp_r27) - *(temp_r28 + temp_r30));
    sp14[temp_r0] = var_f1 * (*(temp_r25 + temp_r30) + *(temp_r26 + temp_r29));
    sp14[temp_r4] = var_f1 * (*(temp_r25 + temp_r27) + *(temp_r28 + temp_r29));
    out.f.x = sp14[0];
    out.f.y = sp14[1];
    out.f.z = sp14[2];
    out.f.w = sp20;
}

/**
 * Offset/Address/Size: 0x338 | 0x801C46D4 | size: 0xF4
 */
#pragma scheduling off
void nlQuatToMatrix(nlMatrix4& out, const nlQuaternion& quat)
{
    // clang-format off
    asm {
        lfs f2, 0x4(r4)
        lfs f1, 2.0f
        lfs f29, 0x8(r4)
        fmuls f10, f1, f2
        lfs f30, 0x0(r4)
        fmuls f0, f1, f29
        lfs f3, 0xc(r4)
        fmuls f4, f1, f30
        lfs f6, 1.0f
        fmuls f3, f1, f3
        lfs f5, 0.0f
        fmuls f13, f10, f2
        fmuls f9, f0, f29
        fmuls f8, f4, f2
        fmuls f7, f3, f29
        fsubs f0, f6, f13
        fmuls f12, f4, f29
        fmuls f11, f3, f2
        fsubs f0, f0, f9
        fsubs f2, f8, f7
        fadds f1, f12, f11
        fnmsubs f31, f4, f30, f6
        stfs f0, 0x0(r3)
        fadds f0, f8, f7
        stfs f2, 0x10(r3)
        fmuls f8, f10, f29
        fmuls f7, f3, f30
        stfs f1, 0x20(r3)
        fsubs f4, f31, f9
        fsubs f2, f12, f11
        stfs f5, 0x30(r3)
        fsubs f3, f8, f7
        fadds f1, f8, f7
        stfs f0, 0x4(r3)
        fsubs f0, f31, f13
        stfs f4, 0x14(r3)
        stfs f3, 0x24(r3)
        stfs f5, 0x34(r3)
        stfs f2, 0x8(r3)
        stfs f1, 0x18(r3)
        stfs f0, 0x28(r3)
        stfs f5, 0x38(r3)
        stfs f5, 0xc(r3)
        stfs f5, 0x1c(r3)
        stfs f5, 0x2c(r3)
        stfs f6, 0x3c(r3)
    }
    // clang-format on
}
#pragma scheduling on

/**
 * Offset/Address/Size: 0x42C | 0x801C47C8 | size: 0x34
 */
void nlQuatSlerp(nlQuaternion& out, const nlQuaternion& q1, const nlQuaternion& q2, float t)
{
    C_QUATSlerp(t, (Quaternion*)&q1, (Quaternion*)&q2, (Quaternion*)&out);
}
