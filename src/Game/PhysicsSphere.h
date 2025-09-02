#ifndef _PHYSICSSPHERE_H_
#define _PHYSICSSPHERE_H_

#include "Game/Physics/PhysicsObject.h"

class CollisionSpace;
class PhysicsWorld;

class PhysicsSphere : public PhysicsObject
{
public:
    void SetRadius(float);
    float GetRadius();
    virtual int GetObjectType() const;
    PhysicsSphere(CollisionSpace*, PhysicsWorld*, float);
    virtual ~PhysicsSphere();
};

#endif // _PHYSICSSPHERE_H_
