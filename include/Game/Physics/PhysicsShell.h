#ifndef _PHYSICSSHELL_H_
#define _PHYSICSSHELL_H_

#include "Game/Physics/PhysicsSphere.h"

class PhysicsShell : public PhysicsSphere
{
public:
    PhysicsShell(float);
    virtual int GetObjectType() const { return 0x13; };
    virtual bool SetContactInfo(dContact* contact, PhysicsObject* other, bool first);
    virtual void PostUpdate();
    virtual ContactType Contact(PhysicsObject*, dContact*, int);

    /* 0x2c */ void* m_unk_0x2c;
    /* 0x30 */ void* m_unk_0x30;
    /* 0x34 */ void* m_unk_0x34;
    /* 0x38 */ u8 m_unk_0x38;
    /* 0x39 */ u8 m_unk_0x39;
};

#endif // _PHYSICSSHELL_H_
