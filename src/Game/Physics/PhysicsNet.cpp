#include "Game/Physics/PhysicsNet.h"

#include "NL/nlMemory.h"
#include "types.h"

PhysicsNet* PhysicsNet::spPhysNetPositiveX = nullptr;
PhysicsNet* PhysicsNet::spPhysNetNegativeX = nullptr;
/**
 * Offset/Address/Size: 0x9A8 | 0x8013AD98 | size: 0x6F8
 */
PhysicsNet::PhysicsNet(CollisionSpace*, bool)
{
    FORCE_DONT_INLINE;
}

/**
 * Offset/Address/Size: 0x7BC | 0x8013ABAC | size: 0x12C
 */
PhysicsNet::~PhysicsNet()
{
    delete mpBackWall;
    delete mpSideWall1;
    delete mpSideWall2;
    delete mpSideGoalPost1;
    delete mpSideGoalPost2;
    delete mpTopGoalPost;

    if (mpNetMesh != nullptr)
    {
        delete mpNetMesh;
    }
}

/**
 * Offset/Address/Size: 0x75C | 0x8013AB4C | size: 0x60
 */
bool PhysicsNet::IsAGoalPost(PhysicsObject* obj)
{
    if ((obj == spPhysNetNegativeX->mpSideGoalPost1)
        || (obj == spPhysNetNegativeX->mpSideGoalPost2)
        || (obj == spPhysNetNegativeX->mpTopGoalPost)
        || (obj == spPhysNetPositiveX->mpSideGoalPost1)
        || (obj == spPhysNetPositiveX->mpSideGoalPost2)
        || (obj == spPhysNetPositiveX->mpTopGoalPost))
    {
        return true;
    }
    return false;
}

/**
 * Offset/Address/Size: 0x6FC | 0x8013AAEC | size: 0x60
 */
bool PhysicsNet::IsAGoalWall(PhysicsObject* obj)
{
    if ((obj == spPhysNetNegativeX->mpSideWall1)
        || (obj == spPhysNetNegativeX->mpSideWall2)
        || (obj == spPhysNetNegativeX->mpBackWall)
        || (obj == spPhysNetPositiveX->mpSideWall1)
        || (obj == spPhysNetPositiveX->mpSideWall2)
        || (obj == spPhysNetPositiveX->mpBackWall))
    {
        return true;
    }
    return false;
}

/**
 * Offset/Address/Size: 0xD0 | 0x8013A4C0 | size: 0x62C
 */
bool PhysicsNet::SweepTestForBallContact(const nlVector3&, const nlVector3&, const nlVector3&, float, nlVector3&, nlVector3&, PhysicsObject**) const
{
    return false;
}

/**
 * Offset/Address/Size: 0x5C | 0x8013A44C | size: 0x74
 */
void PhysicsNet::StaticInit(CollisionSpace*)
{
    PhysicsNet* tmp_netPositiveX = (PhysicsNet*)nlMalloc(sizeof(PhysicsNet), 8, false);
    tmp_netPositiveX = new (tmp_netPositiveX) PhysicsNet(g_CollisionSpace, true);
    spPhysNetPositiveX = tmp_netPositiveX;

    PhysicsNet* tmp_netNegativeX = (PhysicsNet*)nlMalloc(sizeof(PhysicsNet), 8, false);
    tmp_netNegativeX = new (tmp_netNegativeX) PhysicsNet(g_CollisionSpace, false);
    spPhysNetNegativeX = tmp_netNegativeX;
}

/**
 * Offset/Address/Size: 0x0 | 0x8013A3F0 | size: 0x5C
 */
void PhysicsNet::StaticDestroy()
{
    delete spPhysNetNegativeX;
    delete spPhysNetPositiveX;
}
