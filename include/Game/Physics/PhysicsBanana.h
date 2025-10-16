#ifndef _PHYSICSBANANA_H_
#define _PHYSICSBANANA_H_

#include "Game/Physics/PhysicsSphere.h"
#include "Game/Sys/eventman.h"
#include "Game/AI/Fielder.h"

class PowerupBase;

// Forward declarations for collision data structures
struct CollisionPowerupGroundData : public EventData
{
    virtual u32 GetID() { return 0x85; }

    /* 0x04 */ nlVector3 m_position;
    /* 0x10 */ float m_velocityY;
    /* 0x14 */ PowerupBase* m_pPowerupObject;
};

struct CollisionPowerupWallData : public EventData
{
    virtual u32 GetID() const { return 0x9B; }

    /* 0x04 */ PowerupBase* m_pPowerupObject;
    /* 0x08 */ cFielder* m_pThrower;
    /* 0x0C */ nlVector3 m_contactPos;
    /* 0x18 */ nlVector3 m_contactNormal;
};

class PhysicsBanana : public PhysicsSphere
{
public:
    PhysicsBanana(float);
    virtual ~PhysicsBanana();
    virtual int GetObjectType() const { return 0x14; };
    virtual bool SetContactInfo(dContact*, PhysicsObject*, bool);
    virtual void PreUpdate();
    virtual void PreCollide();
    virtual int Contact(PhysicsObject*, dContact*, int);

    /* 0x2C */ void (*m_pTriggerCallbackFunc)(class PhysicsObject*, class PhysicsObject*, class nlVector3&, void*);
    /* 0x30 */ void* m_pCallbackParam;
    /* 0x34 */ PowerupBase* m_pPowerupObject;
    /* 0x38 */ bool m_bIsSupportedByGround;
}; // total size: 0x3C

#endif // _PHYSICSBANANA_H_
