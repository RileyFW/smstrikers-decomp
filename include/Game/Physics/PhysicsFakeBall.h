#ifndef _PHYSICSFAKEBALL_H_
#define _PHYSICSFAKEBALL_H_

#include "Game/Ball.h"
#include "Game/Physics/PhysicsBall.h"
#include "Game/Physics/PhysicsPlane.h"
#include "Game/Physics/PhysicsWorld.h"
#include "Game/Physics/CollisionSpace.h"

class FakePhysicsBall;

class FakeBallWorld
{
public:
    void FindBallIntercept(const nlVector3&, float, float, nlVector3&, nlVector3&, float&, float&, float);
    void GetNextBallPosition(nlVector3&);
    void ResetBallIterator();
    void GetPredictedPosAtDistance(float, nlVector3&, nlVector3&);
    void GetPredictedHeightLimitTime(float, float, nlVector3&, nlVector3&, bool);
    void GetPredictedPlaneIntersectTime(const nlVector4&, nlVector3&, nlVector3&);
    void GetPredictedBallPosition(float, nlVector3&, nlVector3&);
    static void InvalidateBallCache();
    void Destroy();
    static void Init(cBall*);

    /* 0x00 */ cBall* mpBall;                    // offset 0x0, size 0x4
    /* 0x04 */ float mfElapsedTime;              // offset 0x4, size 0x4
    /* 0x08 */ FakePhysicsBall* mpPhysicsBall;   // offset 0x8, size 0x4
    /* 0x0C */ CollisionSpace* mpCollisionSpace; // offset 0xC, size 0x4
    /* 0x10 */ PhysicsWorld* mpPhysicsWorld;     // offset 0x10, size 0x4
    /* 0x14 */ PhysicsPlane* mpGroundPlane;      // offset 0x14, size 0x4
    /* 0x18 */ bool mbHitSuccess;                // offset 0x18, size 0x1
    /* 0x1C */ dContactGeom mContactInfo;        // offset 0x1C, size 0x2C
}; // total size: 0x48

class FakePhysicsBall : public PhysicsBall
{
public:
    virtual int Contact(PhysicsObject*, dContact*, int);
    virtual ~FakePhysicsBall();
    virtual int GetObjectType() const;

    /* 0x40 */ FakeBallWorld& mWorld;
}; // total size: 0x44

#endif // _PHYSICSFAKEBALL_H_
