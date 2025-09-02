#ifndef _PHYSICSPLANE_H_
#define _PHYSICSPLANE_H_

#include "PhysicsObject.h"
#include "CollisionSpace.h"

class CollisionSpace;

class PhysicsPlane : public PhysicsObject
{
public:
    virtual int GetObjectType() const;
    PhysicsPlane(CollisionSpace*, float, float, float, float);
    virtual ~PhysicsPlane() {
        // EMPTY
    };
};

#endif // _PHYSICSPLANE_H_
