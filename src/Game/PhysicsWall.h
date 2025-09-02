#ifndef _PHYSICSWALL_H_
#define _PHYSICSWALL_H_

// #include "NL/nlMath.h"
#include "CollisionSpace.h"
#include "PhysicsPlane.h"

class PhysicsWall : public PhysicsPlane
{
public:
    PhysicsWall(CollisionSpace*, float, float, float);

    virtual ~PhysicsWall() {
        // EMPTY
    };

    virtual int GetObjectType() const
    {
        return 0x19;
    };
};

#endif // _PHYSICSWALL_H_
