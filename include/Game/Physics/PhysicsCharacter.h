#ifndef _PHYSICSCHARACTER_H_
#define _PHYSICSCHARACTER_H_

#include "Game/Physics/PhysicsCharacterBase.h"

class PhysicsCharacter : public PhysicsCharacterBase
{
public:
    virtual ~PhysicsCharacter() { };
    PhysicsCharacter(float, float);

    virtual int GetObjectType() const;
    virtual bool SetContactInfo(dContact* contact, PhysicsObject* other, bool first);

    virtual void PostUpdate();
    virtual void PreCollide();
    virtual int Contact(PhysicsObject*, dContact*, int, PhysicsObject*);

    void SetCharacterVelocityXY(const nlVector3&);
    void GetCharacterVelocityXY(nlVector3*);
    void SetCharacterPositionXY(const nlVector3&);
    void GetCharacterPositionXY(nlVector3*);
    virtual void ResolvePhysicsBoneIDFromName(const char*);
    void GetRadius(float*);

    /* 0x80 */ unsigned int m_CanCollideWithWall : 1;
    /* 0x81 */ unsigned int m_CanCollideWithBall : 1;
    /* 0x82 */ unsigned int m_HasCollidedWithBall : 1;
    /* 0x83 */ unsigned int m_CanCollidedWithGoalLine : 1;
    /* 0x84 */ class cCharacter* m_pAICharacter;
    /* 0x88 */ class PhysicsColumn* m_pPlayerPlayerColumn;
}; // total size: 0x8C

#endif // _PHYSICSCHARACTER_H_
