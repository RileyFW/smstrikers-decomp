#include "NL/nlMath.h"

/**
 * Offset/Address/Size: 0x540 | 0x801F083C | size: 0x88
 */
void nlCartesianToPolar(nlPolar&, float, float)
{
}

/**
 * Offset/Address/Size: 0x4D4 | 0x801F07D0 | size: 0x6C
 */
void nlPolarToCartesian(float&, float&, unsigned short, float)
{
}

/**
 * Offset/Address/Size: 0x46C | 0x801F0768 | size: 0x68
 */
void nlPolarToCartesian(nlVector3&, const nlPolar&)
{
}

/**
 * Offset/Address/Size: 0x3EC | 0x801F06E8 | size: 0x80
 */
void nlAddPolarToCartesian(nlVector3&, const nlPolar&)
{
}

/**
 * Offset/Address/Size: 0x364 | 0x801F0660 | size: 0x88
 */
void nlCartesianToPolar(nlPolar& out, const nlVector3& in)
{
}

/**
 * Offset/Address/Size: 0x2B8 | 0x801F05B4 | size: 0xAC
 */
void nlMakeQuat(nlQuaternion& out, const nlVector3& in, float ang_rad)
{
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
void nlQuatNLerp(nlQuaternion&, const nlQuaternion&, const nlQuaternion&, float)
{
}

/**
 * Offset/Address/Size: 0x0 | 0x801F02FC | size: 0xA8
 */
void nlInvertRotTransMatrix(nlMatrix4&, const nlMatrix4&)
{
}
