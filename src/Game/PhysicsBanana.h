#ifndef _PHYSICSBANANA_H_
#define _PHYSICSBANANA_H_

#include "Game/Physics/PhysicsObject.h"

class PhysicsBanana // : public PhysicsObject
{
public:
    ~PhysicsBanana();
    virtual int SetContactInfo(dContact*, PhysicsObject*, bool);
    virtual int Contact(PhysicsObject*, dContact*, int);
    virtual int PreCollide();
    virtual void PreUpdate();
    PhysicsBanana(float);
    virtual int GetObjectType() const;
};

class CollisionPowerupGroundData
{
public:
    void GetID();
};

#endif // _PHYSICSBANANA_H_
