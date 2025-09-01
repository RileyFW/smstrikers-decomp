#include "PhysicsCapsule.h"
#include "PhysicsObject.h"

/**
 * Offset/Address/Size: 0x0 | 0x801FE7A0 | size: 0xE8
 */
PhysicsCapsule::PhysicsCapsule(CollisionSpace* collisionSpace, PhysicsWorld* world, float radius, float length)
    : PhysicsObject(world)
{
    dMass m;
    dMassSetZero(&m);

    dSpaceID spaceID = NULL;
    if (collisionSpace != NULL)
    {
        spaceID = collisionSpace->m_spaceID;
    }

    m_geomID = dCreateCCylinder(spaceID, radius, length);

    if (m_bodyID != NULL)
    {
        dGeomSetBody(m_geomID, m_bodyID);
        dMassSetCappedCylinderTotal(&m, 1.0f, 3, radius, length);
        dBodySetMass(m_bodyID, &m);
    }

    dGeomSetData(m_geomID, this);
    SetDefaultCollideBits();
}
