#ifndef _PHYSICSMATH_H_
#define _PHYSICSMATH_H_

#include "NL/nlMath.h"

inline void nlVecAdd_(nlVector3& v0, const nlVector3& v1, const nlVector3& v2)
{
    nlVec3Set(v0, v1.f.x + v2.f.x, v1.f.y + v2.f.y, v1.f.z + v2.f.z); // v0.x = v1.x + v2.x;
}

void nlVecAdd(nlVector3& v0, const nlVector3& v1, const nlVector3& v2)
{
    FORCE_DONT_INLINE;
    nlVec3Set(v0, v1.f.x + v2.f.x, v1.f.y + v2.f.y, v1.f.z + v2.f.z); // v0.x = v1.x + v2.x;
}

#endif // _PHYSICSMATH_H_
