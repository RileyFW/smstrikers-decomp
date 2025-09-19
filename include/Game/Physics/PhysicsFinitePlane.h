#ifndef _PHYSICSFINITEPLANE_H_
#define _PHYSICSFINITEPLANE_H_

#include "NL/nlMath.h"
#include "Game/Physics/CollisionSpace.h"
#include "Game/Physics/PhysicsObject.h"

class PhysicsFinitePlane : public PhysicsObject
{
public:
    PhysicsFinitePlane(CollisionSpace*, nlVector3&, nlVector3&, nlVector3&, bool, float);
    virtual int GetObjectType() const;

    /* 0x2C */ float xMin;
    /* 0x30 */ float xMax;
    /* 0x34 */ float yMin;
    /* 0x38 */ float yMax;
    /* 0x3C */ float mErrorCorrectionDepth;
    /* 0x40 */ struct dxJoint* m_CharMoveJoint;

    // u8 m_padding[18];
    // nlVector4 m_vec4;
    // float m_param;
};

#endif // _PHYSICSFINITEPLANE_H_
