#ifndef _PHYSICSNET_H_
#define _PHYSICSNET_H_

#include "Game/Physics/PhysicsObject.h"
#include "CollisionSpace.h"

class PhysicsNet : public PhysicsObject
{
public:
    void StaticDestroy();
    void StaticInit(CollisionSpace*);
    void SweepTestForBallContact(const nlVector3&, const nlVector3&, const nlVector3&, float, nlVector3&, nlVector3&, PhysicsObject**) const;
    void IsAGoalWall(PhysicsObject*);
    void IsAGoalPost(PhysicsObject*);
    ~PhysicsNet();
    PhysicsNet(CollisionSpace*, bool);
    virtual int GetObjectType() const;
};

#endif // _PHYSICSNET_H_
