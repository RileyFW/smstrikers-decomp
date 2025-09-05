#ifndef _PHYSICSSPHERE_H_
#define _PHYSICSSPHERE_H_

#include "Game/Physics/PhysicsObject.h"

class CollisionSpace;
class PhysicsWorld;

class PhysicsSphere : public PhysicsObject
{
public:
    PhysicsSphere(CollisionSpace*, PhysicsWorld*, float);
    virtual ~PhysicsSphere() { };
    virtual int GetObjectType() const { return 0x0A; };
    void SetRadius(float);
    float GetRadius();
};

#endif // _PHYSICSSPHERE_H_
