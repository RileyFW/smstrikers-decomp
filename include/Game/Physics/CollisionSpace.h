#ifndef _COLLISIONSPACE_H_
#define _COLLISIONSPACE_H_

#include "ode/collision.h"
#include "ode/common.h"

class PhysicsWorld;
class PhysicsObject;
class CollisionSpace;

class CollisionSpace
{
public:
    void PreUpdate();
    void PreCollide();
    void CallPreCollide(PhysicsObject*);
    void DoCollide(void* data, dNearCallback* callback);

    virtual ~CollisionSpace();

    /* 0x04 */ dSpaceID m_spaceID; // is this 0x04 because of the virtual tables now?
    /* 0x08 */ CollisionSpace* m_nextCollisionSpace;
    /* 0x0c */ PhysicsWorld* m_physicsWorld;
};

class SimpleCollisionSpace : public CollisionSpace
{
public:
    SimpleCollisionSpace(PhysicsWorld*);
    ~SimpleCollisionSpace();
};

#endif // _COLLISIONSPACE_H_
