#ifndef _PHYSICSTRANSFORM_H_
#define _PHYSICSTRANSFORM_H_

#include "NL/nlMath.h"

#include "ode/objects.h"
#include "ode/collision.h"

#include "Game/Physics/PhysicsObject.h"

class PhysicsTransform : public PhysicsObject
{
public:
    PhysicsTransform();
    virtual ~PhysicsTransform();
    virtual int GetObjectType() const { return m_SubObject->GetObjectType(); };

    void SetSubObjectTransform(const nlMatrix4&, PhysicsObject::CoordinateType);
    void SetSubObjectPosition(const nlVector3&, PhysicsObject::CoordinateType);
    void Release();
    void Attach(PhysicsObject*, PhysicsObject*);

    /* 0x2c */ PhysicsObject* m_SubObject;
};

#endif // _PHYSICSTRANSFORM_H_
