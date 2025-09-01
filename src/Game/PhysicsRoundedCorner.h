#ifndef _PHYSICSROUNDEDCORNER_H_
#define _PHYSICSROUNDEDCORNER_H_

#include "NL/nlMath.h"

#include "PhysicsObject.h"
#include "CollisionSpace.h"

class PhysicsRoundedCorner : public PhysicsObject
{
public:
    PhysicsRoundedCorner(CollisionSpace*, const nlVector2&, float, bool, bool);
    ~PhysicsRoundedCorner();

    virtual int GetObjectType() const
    {
        return 0x05;
    };
};

#endif // _PHYSICSROUNDEDCORNER_H_
