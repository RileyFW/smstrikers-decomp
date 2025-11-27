#ifndef _PHYSICSWORLD_H_
#define _PHYSICSWORLD_H_

// #include "NL/nlMath.h"

#include "NL/nlList.h"
#include "ode/common.h"
#include "ode/objects.h"
#include "ode/collision.h"

class CollisionSpace;
class PhysicsObject;
class DebugWriteCache;

class PhysicsWorld
{
public:
    PhysicsWorld();
    ~PhysicsWorld();

    void DoCollisions(PhysicsObject*, nlListContainer<PhysicsObject*>&);
    static void SpaceCollideCallback(void* data, dxGeom* geom1, dxGeom* geom2);
    void Update(float, bool);
    void PostUpdate();
    void PreUpdate();
    void Collide();
    void DoCollide(CollisionSpace*);
    void PostUpdate(PhysicsObject*);
    void PreUpdate(PhysicsObject*);
    void PreUpdate(CollisionSpace*);
    void PreCollide(PhysicsObject*);
    void PreCollide(CollisionSpace*);
    void AddCollisionSpace(CollisionSpace*);
    void SetERP(float);
    void SetCFM(float);

    /* 0x00 */ dWorldID m_World;
    /* 0x04 */ dJointGroupID m_ContactGroup;
    /* 0x08 */ CollisionSpace* m_SpaceList;
    /* 0x0C */ DebugWriteCache* m_SyncLogFile;
};

#endif // _PHYSICSWORLD_H_
