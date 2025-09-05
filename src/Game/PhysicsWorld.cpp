#include "Game/Physics/PhysicsWorld.h"
#include "Game/Physics/CollisionSpace.h"
#include "Game/Physics/PhysicsObject.h"

#include "ode/NLGAdditions.h"

/**
 * Offset/Address/Size: 0x0 | 0x80201700 | size: 0x78
 */
// PhysicsWorld::DoCollisions(PhysicsObject*, nlListContainer<PhysicsObject*>&)
// {
// }

/**
 * Offset/Address/Size: 0x78 | 0x80201778 | size: 0x224
 */
void PhysicsWorld::SpaceCollideCallback(void*, dxGeom*, dxGeom*)
{
}

/**
 * Offset/Address/Size: 0x29C | 0x8020199C | size: 0x60
 */
void PhysicsWorld::Update(float quickStepSize, bool doClear)
{
    int pp = (u32)(-doClear | doClear) >> 0x1FU; // a convoluted way to convert a boolean to an integer
    dWorldSetClearAccumulators(m_worldID, pp);
    dWorldQuickStep(m_worldID, quickStepSize);
    dJointGroupEmpty(m_jointGroupID);
}

/**
 * Offset/Address/Size: 0x2FC | 0x802019FC | size: 0x90
 */
void PhysicsWorld::PostUpdate()
{
    void (PhysicsObject::*pmf)() = &PhysicsObject::PostUpdate;
    for (dBodyID bodyID = dWorldGetFirstBody(m_worldID); bodyID != NULL; bodyID = dBodyGetNextBody(bodyID))
    {
        PhysicsObject* obj = (PhysicsObject*)dBodyGetData(bodyID);
        (obj->*pmf)();
    }
}

/**
 * Offset/Address/Size: 0x38C | 0x80201A8C | size: 0xD8
 */
void PhysicsWorld::PreUpdate()
{
}

/**
 * Offset/Address/Size: 0x464 | 0x80201B64 | size: 0x120
 */
void PhysicsWorld::Collide()
{
}

/**
 * Offset/Address/Size: 0x584 | 0x80201C84 | size: 0x34
 */
void PhysicsWorld::DoCollide(CollisionSpace* collisionSpace)
{
    collisionSpace->DoCollide(this, &SpaceCollideCallback);
}

/**
 * Offset/Address/Size: 0x5B8 | 0x80201CB8 | size: 0x30
 */
void PhysicsWorld::PostUpdate(PhysicsObject* object)
{
    object->PostUpdate();
}

/**
 * Offset/Address/Size: 0x5E8 | 0x80201CE8 | size: 0x30
 */
void PhysicsWorld::PreUpdate(PhysicsObject* object)
{
    object->PreUpdate();
}

/**
 * Offset/Address/Size: 0x618 | 0x80201D18 | size: 0x24
 */
void PhysicsWorld::PreUpdate(CollisionSpace* collisionSpace)
{
    collisionSpace->PreUpdate();
}

/**
 * Offset/Address/Size: 0x63C | 0x80201D3C | size: 0x30
 */
void PhysicsWorld::PreCollide(PhysicsObject* object)
{
    object->PreCollide();
}

/**
 * Offset/Address/Size: 0x66C | 0x80201D6C | size: 0x24
 */
void PhysicsWorld::PreCollide(CollisionSpace* collisionSpace)
{
    collisionSpace->PreCollide();
}

/**
 * Offset/Address/Size: 0x690 | 0x80201D90 | size: 0x10
 */
void PhysicsWorld::AddCollisionSpace(CollisionSpace* collisionSpace)
{
    collisionSpace->m_nextCollisionSpace = m_collisionSpace;
    m_collisionSpace = collisionSpace;
}

/**
 * Offset/Address/Size: 0x6A0 | 0x80201DA0 | size: 0x24
 */
void PhysicsWorld::SetERP(float erp)
{
    dWorldSetERP(m_worldID, erp);
}

/**
 * Offset/Address/Size: 0x6C4 | 0x80201DC4 | size: 0x24
 */
void PhysicsWorld::SetCFM(float cfm)
{
    dWorldSetCFM(m_worldID, cfm);
}

/**
 * Offset/Address/Size: 0x6E8 | 0x80201DE8 | size: 0x5C
 */
PhysicsWorld::~PhysicsWorld()
{
    dJointGroupDestroy(m_jointGroupID);
    dWorldDestroy(m_worldID);
}

/**
 * Offset/Address/Size: 0x744 | 0x80201E44 | size: 0x4C
 */
PhysicsWorld::PhysicsWorld()
{
    m_worldID = dWorldCreate();
    m_jointGroupID = dJointGroupCreate(0);
    m_collisionSpace = NULL;
    m_UNK0x0C = NULL;
}
