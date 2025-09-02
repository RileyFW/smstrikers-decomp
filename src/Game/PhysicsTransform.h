#ifndef _PHYSICSTRANSFORM_H_
#define _PHYSICSTRANSFORM_H_

#include "NL/nlMath.h"

#include "ode/objects.h"
#include "ode/collision.h"

#include "Game/Physics/PhysicsObject.h"

class PhysicsTransform : public PhysicsObject
{
public:
    void SetSubObjectTransform(const nlMatrix4&, PhysicsObject::CoordinateType);
    void SetSubObjectPosition(const nlVector3&, PhysicsObject::CoordinateType);
    void Release();
    void Attach(PhysicsObject*, PhysicsObject*);
    virtual int GetObjectType() const;

    virtual ~PhysicsTransform();
    PhysicsTransform();

    /* 0x2c */ PhysicsObject* m_unk_2c;
};

#endif // _PHYSICSTRANSFORM_H_
