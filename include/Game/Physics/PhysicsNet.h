#ifndef _PHYSICSNET_H_
#define _PHYSICSNET_H_

#include "Game/Physics/PhysicsObject.h"
#include "Game/Physics/CollisionSpace.h"

class PhysicsNet
{
public:
    PhysicsNet(CollisionSpace*, bool);
    virtual ~PhysicsNet();
    virtual int GetObjectType() const { return 0x1b; };

    void IsAGoalPost(PhysicsObject*);
    void IsAGoalWall(PhysicsObject*);
    void SweepTestForBallContact(const nlVector3&, const nlVector3&, const nlVector3&, float, nlVector3&, nlVector3&, PhysicsObject**) const;
    void StaticInit(CollisionSpace*);
    void StaticDestroy();

    class PhysicsFinitePlane* mpBackWall;  // offset 0x4, size 0x4
    class PhysicsFinitePlane* mpSideWall1; // offset 0x8, size 0x4
    class PhysicsFinitePlane* mpSideWall2; // offset 0xC, size 0x4
    class PhysicsCapsule* mpSideGoalPost1; // offset 0x10, size 0x4
    class PhysicsCapsule* mpSideGoalPost2; // offset 0x14, size 0x4
    class PhysicsCapsule* mpTopGoalPost;   // offset 0x18, size 0x4
    class NetMesh* mpNetMesh;              // offset 0x1C, size 0x4
    class cNet* mpNet;                     // offset 0x20, size 0x4
    float errorCorrectionDepth;            // offset 0x24, size 0x4

}; // total size: 0x28

#endif // _PHYSICSNET_H_
