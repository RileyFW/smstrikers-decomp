#ifndef _PHYSICSBALL_H_
#define _PHYSICSBALL_H_

#include "NL/nlMath.h"
#include "Game/Physics/PhysicsSphere.h"

class PhysicsBall : public PhysicsSphere
{
public:
    void CalcAngularFromLinearVelocity(nlVector3&);
    void SetUseAngularVelocity(bool);
    void ScaleAngularVelocity(float);
    void AddResistanceForces();
    virtual int Contact(PhysicsObject*, dContact*, int);
    void CloneBall(const PhysicsBall&);
    virtual void PostUpdate();
    virtual void PreUpdate();
    virtual int PreCollide();
    virtual int SetContactInfo(dContact*, PhysicsObject*, bool);
    float GetBallMaxVelocity();

    PhysicsBall(CollisionSpace*, PhysicsWorld*, float);
    virtual ~PhysicsBall();

    /* 0x2c */ nlVector3 m_unk_0x2c; // change this will break constructor

    /* 0x38 */ u8 m_unk_0x38;
    /* 0x39 */ u8 m_unk_0x39;
    /* 0x3a */ u8 m_unk_0x3a;
    /* 0x3b */ u8 m_unk_0x3b;
    /* 0x3c */ float m_angularVelocity;
    /* 0x40 */ u32* m_unk_0x40; // referenced by int FakePhysicsBall::Contact(PhysicsObject* object, dContact* contact, int arg)
    /* 0x44 */ nlVector3 m_unk_0x44;
    /* 0x50 */ int m_unk_0x50;
};

#endif // _PHYSICSBALL_H_
