#ifndef _PHYSICSGOALIE_H_
#define _PHYSICSGOALIE_H_

#include "NL/nlMath.h"
#include "Game/Physics/PhysicsCharacter.h"

class PhysicsGoalie : public PhysicsCharacter
{
public:
    virtual ~PhysicsGoalie() { };
    virtual void PostUpdate();

    virtual void SweepTestForBallContact(const nlVector3&, const nlVector3&, const nlVector3&, float, nlVector3&, nlVector3&) const;
    virtual void SweepTestEveryBone(float, const nlVector3&, const nlVector3&, nlVector3&, nlVector3&) const;
    virtual void CollideGoalieWithPost();
};

#endif // _PHYSICSGOALIE_H_
