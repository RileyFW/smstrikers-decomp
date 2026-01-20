#include "NL/glx/glxMatrix.h"
#include "math.h"

#include <stddef.h>
void* memcpy(void* dest, const void* src, size_t num);

// s8 init_near = 0;
// s8 init_far = 0;
// f32 fNear = 0.0f;
// f32 fFar = 0.0f;

/**
 * Offset/Address/Size: 0x0 | 0x801B6568 | size: 0x64
 */
void glxCopyMatrix(float (&arg0)[3][4], const nlMatrix4& arg1)
{
    // Row 0: copy from nlMatrix4 row 0 to target row 0
    arg0[0][0] = arg1.m[0][0]; // offset 0x00
    arg0[0][1] = arg1.m[1][0]; // offset 0x04
    arg0[0][2] = arg1.m[2][0]; // offset 0x08
    arg0[0][3] = arg1.m[3][0]; // offset 0x0C

    // Row 1: copy from nlMatrix4 row 1 to target row 1
    arg0[1][0] = arg1.m[0][1]; // offset 0x10
    arg0[1][1] = arg1.m[1][1]; // offset 0x14
    arg0[1][2] = arg1.m[2][1]; // offset 0x18
    arg0[1][3] = arg1.m[3][1]; // offset 0x1C

    // Row 2: copy from nlMatrix4 row 2 to target row 2
    arg0[2][0] = arg1.m[0][2]; // offset 0x20
    arg0[2][1] = arg1.m[1][2]; // offset 0x24
    arg0[2][2] = arg1.m[2][2]; // offset 0x28
    arg0[2][3] = arg1.m[3][2]; // offset 0x2C
}

/**
 * Offset/Address/Size: 0x64 | 0x801B65CC | size: 0x24
 */
void glxCopyMatrix(float (&arg0)[4][4], const nlMatrix4& arg1)
{
    memcpy(arg0, arg1.m, sizeof(arg1.m));
}

/**
 * Offset/Address/Size: 0x88 | 0x801B65F0 | size: 0x1CC
 */
void glplatMatrixLookAt(nlMatrix4& arg0, const nlVector3& arg1, const nlVector3& arg2, const nlVector3& arg3)
{
    // Calculate the forward vector (from eye to target)
    float dx = arg1.f.x - arg2.f.x;
    float dy = arg1.f.y - arg2.f.y;
    float dz = arg1.f.z - arg2.f.z;

    // Normalize the forward vector
    float length = nlRecipSqrt(dx * dx + dy * dy + dz * dz, true);
    float forward_x = length * dx;
    float forward_y = length * dy;
    float forward_z = length * dz;

    // Calculate the right vector using cross product of up and forward
    float up_x = arg3.f.x;
    float up_y = arg3.f.y;
    float up_z = arg3.f.z;

    // Cross product: right = up × forward
    float right_x = up_y * forward_z - up_z * forward_y;
    float right_y = up_z * forward_x - up_x * forward_z;
    float right_z = up_x * forward_y - up_y * forward_x;

    // Normalize the right vector
    float right_length = nlRecipSqrt(right_x * right_x + right_y * right_y + right_z * right_z, true);
    right_x *= right_length;
    right_y *= right_length;
    right_z *= right_length;

    // Calculate the up vector using cross product of forward and right
    float up_new_x = forward_y * right_z - forward_z * right_y;
    float up_new_y = forward_z * right_x - forward_x * right_z;
    float up_new_z = forward_x * right_y - forward_y * right_x;

    // Build the look-at matrix (transposed for this implementation)
    // Row 0: right vector
    arg0.m[0][0] = right_x;
    arg0.m[0][1] = right_y;
    arg0.m[0][2] = right_z;
    arg0.m[0][3] = 0.0f;

    // Row 1: up vector
    arg0.m[1][0] = up_new_x;
    arg0.m[1][1] = up_new_y;
    arg0.m[1][2] = up_new_z;
    arg0.m[1][3] = 0.0f;

    // Row 2: forward vector (negated for look-at)
    arg0.m[2][0] = -forward_x;
    arg0.m[2][1] = -forward_y;
    arg0.m[2][2] = -forward_z;
    arg0.m[2][3] = 0.0f;

    // Row 3: translation (negative dot product with eye position)
    arg0.m[3][0] = -(right_x * arg1.f.x + right_y * arg1.f.y + right_z * arg1.f.z);
    arg0.m[3][1] = -(up_new_x * arg1.f.x + up_new_y * arg1.f.y + up_new_z * arg1.f.z);
    arg0.m[3][2] = -(-forward_x * arg1.f.x - forward_y * arg1.f.y - forward_z * arg1.f.z);
    arg0.m[3][3] = 1.0f;
}

/**
 * Offset/Address/Size: 0x254 | 0x801B67BC | size: 0xB8
 */
void glplatMatrixPerspective(nlMatrix4& matrix, float fovY, float aspect, float near, float far)
{
    f32 temp_f2 = tan(0.5f * fovY);
    f32 atanVal = (f32)atan((1.0f / aspect) / (1.0f / temp_f2));
    C_MTXPerspective(matrix.m, (2.f * atanVal * 180.0f) / 3.1415927f, aspect, near, far);
}

/**
 * Offset/Address/Size: 0x30C | 0x801B6874 | size: 0x48
 */
void glplatMatrixOrthographicCentered(nlMatrix4& matrix, float width, float height, float near, float far)
{
    C_MTXOrtho(matrix.m, 0.5f * height, 0.5f * -height, 0.5f * -width, 0.5f * width, near, far);
}

/**
 * Offset/Address/Size: 0x354 | 0x801B68BC | size: 0x6C
 */
void glplatMatrixOrthographic(nlMatrix4& matrix, float width, float height)
{
    static float fNear = 0.0f;
    static float fFar = 16777215.0f;
    C_MTXOrtho(matrix.m, 0.f, height, 0.f, width, fNear, fFar);
}
