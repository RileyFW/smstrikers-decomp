#include "NL/utility.h"
#include "math.h"

static f32 CANT_COLLIDE = *(f32*)__float_max;

/**
 * Offset/Address/Size: 0x0 | 0x801F08C4 | size: 0x1A8
 */
void SolveQuadratic(float, float, float, int&, float&, float&)
{
}

/**
 * Offset/Address/Size: 0x1A8 | 0x801F0A6C | size: 0x148
 * TODO: 98.60% match - f8/f10 register swap throughout due to -inline deferred
 * flag. All instructions and offsets match, only FPR register names differ.
 */
float SweepSpheres(float rp, const nlVector3& p1, const nlVector3& p2, float rq,
    const nlVector3& q1, const nlVector3& q2)
{
    nlVector3 d, v;
    d.f.y = p1.f.y - q1.f.y;
    v.f.y = (p2.f.y - p1.f.y) - (q2.f.y - q1.f.y);
    d.f.x = p1.f.x - q1.f.x;
    v.f.x = (p2.f.x - p1.f.x) - (q2.f.x - q1.f.x);
    d.f.z = p1.f.z - q1.f.z;
    v.f.z = (p2.f.z - p1.f.z) - (q2.f.z - q1.f.z);

    float a = v.GetLengthSq3D();
    float dsq = d.GetLengthSq3D();

    if ((float)fabs(a) <= 0.00001f)
    {
        return CANT_COLLIDE;
    }

    float dot = d.f.x * v.f.x + d.f.y * v.f.y + d.f.z * v.f.z;
    float r = rp + rq;
    float rsq = r * r;

    float dotSq = dot * dot;
    float closest = dsq - dotSq / a;
    if (closest > rsq)
    {
        return CANT_COLLIDE;
    }

    if (dsq <= rsq)
    {
        return 0.0f;
    }

    float disc = dotSq - a * (dsq - rsq);
    if (disc < 0.0f)
    {
        return CANT_COLLIDE;
    }

    float t = (-dot - nlSqrt(disc, true)) / a;
    return t;
}

// /**
//  * Offset/Address/Size: 0x2F0 | 0x801F0BB4 | size: 0x10
//  */
// void 0x8028D55C..0x8028D560 | size : 0x4
// {
// }
