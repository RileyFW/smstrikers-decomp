#ifndef _PHYSICSAIBALL_H_
#define _PHYSICSAIBALL_H_

#include "NL/nlMath.h"
#include "Game/Physics/PhysicsBall.h"

class PhysicsAIBall : public PhysicsBall
{
public:
    void IsBallOutsideNet(const nlVector3&);
    void DidBallJustEnterNet(const nlVector3&, nlVector3);
    void CheckIfBallWentThroughGoalPost();
    void CheckIfBallWentThroughGoalie();

    virtual int GetObjectType() const;                   // 0x0C
    virtual void PreUpdate();                            // 0x14
    virtual void PostUpdate();                           // 0x18
    virtual int PreCollide();                            // 0x1c
    virtual int Contact(PhysicsObject*, dContact*, int); // 0x20

    virtual ~PhysicsAIBall();
    PhysicsAIBall(float);

    /* 0x4C */ u8 m_padding[4];
    /* 0x58 */ u8 m_unk_0x58;
};

#endif // _PHYSICSAIBALL_H_
