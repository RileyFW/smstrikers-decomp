#ifndef _PHYSICSFINITEPLANE_H_
#define _PHYSICSFINITEPLANE_H_

#include "NL/nlMath.h"
#include "CollisionSpace.h"
#include "Game/Physics/PhysicsObject.h"

class PhysicsFinitePlane : public PhysicsObject
{
public:
    PhysicsFinitePlane(CollisionSpace*, nlVector3&, nlVector3&, nlVector3&, bool, float);
    virtual int GetObjectType() const;

    u8 m_padding[18];
    nlVector4 m_vec4;
    float m_param;
};

#endif // _PHYSICSFINITEPLANE_H_
