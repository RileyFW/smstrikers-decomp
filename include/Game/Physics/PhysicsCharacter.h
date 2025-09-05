#ifndef _PHYSICSCHARACTER_H_
#define _PHYSICSCHARACTER_H_

#include "Game/Physics/PhysicsCharacterBase.h"

class PhysicsCharacter : public PhysicsCharacterBase
{
public:
    virtual ~PhysicsCharacter();
    PhysicsCharacter(float, float);

    virtual int GetObjectType() const;
    virtual int SetContactInfo(dContact*, PhysicsObject*, bool);

    virtual void PostUpdate();
    virtual int PreCollide();
    virtual int Contact(PhysicsObject*, dContact*, int, PhysicsObject*);

    void SetCharacterVelocityXY(const nlVector3&);
    void GetCharacterVelocityXY(nlVector3*);
    void SetCharacterPositionXY(const nlVector3&);
    void GetCharacterPositionXY(nlVector3*);
    void ResolvePhysicsBoneIDFromName(const char*);
    void GetRadius(float*);
};

#endif // _PHYSICSCHARACTER_H_
