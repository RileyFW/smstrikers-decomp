#ifndef _PHYSICSBOX_H_
#define _PHYSICSBOX_H_

#include "Game/Physics/PhysicsObject.h"

#include "Game/Physics/CollisionSpace.h"

class PhysicsBox : public PhysicsObject
{
public:
    void SetDensity(float);
    PhysicsBox(CollisionSpace*, PhysicsWorld*, float, float, float);
    virtual int GetObjectType() const { return 0x1; };
}; // total size: 0x2C

#endif // _PHYSICSBOX_H_
