#ifndef _PHYSICSBOX_H_
#define _PHYSICSBOX_H_

#include "Game/Physics/PhysicsObject.h"

#include "Game/Physics/CollisionSpace.h"

class PhysicsBox : PhysicsObject
{
public:
    void SetDensity(float);
    PhysicsBox(CollisionSpace*, PhysicsWorld*, float, float, float);
};

#endif // _PHYSICSBOX_H_
