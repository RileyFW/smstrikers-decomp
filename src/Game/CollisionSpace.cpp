#include "Game/Physics/CollisionSpace.h"

#include "Game/Physics/PhysicsWorld.h"
#include "Game/Physics/PhysicsObject.h"

/**
 * Offset/Address/Size: 0x0 | 0x801FE3E8 | size: 0x60
 */
SimpleCollisionSpace::SimpleCollisionSpace(PhysicsWorld* world)
{
    m_physicsWorld = world;
    world->AddCollisionSpace(this);
    // m_spaceID = dSimpleSpaceCreate((dxSpace *)world->m_UNK0x0C);
    m_spaceID = dSimpleSpaceCreate(NULL);
}

/**
 * Offset/Address/Size: 0x60 | 0x801FE448 | size: 0x4
 */
void CollisionSpace::PreUpdate()
{
    // EMPTY
}

/**
 * Offset/Address/Size: 0x64 | 0x801FE44C | size: 0xB8
 */
void CollisionSpace::PreCollide()
{
    int (PhysicsObject::*pmf)() = &PhysicsObject::PreCollide;
    int numGeoms = dSpaceGetNumGeoms(m_spaceID);
    for (int i = 0; i < numGeoms; i++)
    {
        dGeomID geomID = dSpaceGetGeom(m_spaceID, i);
        if (dGeomGetClass(geomID) != dRayClass)
        {
            PhysicsObject* obj = (PhysicsObject*)dGeomGetData(geomID);
            (obj->*pmf)();
        }
    }
}

/**
 * Offset/Address/Size: 0x11C | 0x801FE504 | size: 0x30
 */
void CollisionSpace::CallPreCollide(PhysicsObject* object)
{
    object->PreCollide();
}

/**
 * Offset/Address/Size: 0x14C | 0x801FE534 | size: 0x24
 */
void CollisionSpace::DoCollide(void* data, dNearCallback* callback)
{
    dSpaceCollide(m_spaceID, data, callback);
}

/**
 * Offset/Address/Size: 0x170 | 0x801FE558 | size: 0x60
 */
CollisionSpace::~CollisionSpace()
{
    dSpaceDestroy(m_spaceID);
}

/**
 * Offset/Address/Size: 0x1D0 | 0x801FE5B8 | size: 0x70
 */
SimpleCollisionSpace::~SimpleCollisionSpace()
{
}
