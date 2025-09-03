#ifndef _PHYSICSNPC_H_
#define _PHYSICSNPC_H_

#include "PhysicsSphere.h"
#include "CollisionSpace.h"

class SkinAnimatedMovableNPC;

class PhysicsNPC : public PhysicsSphere
{
public:
    typedef void (*CallbackFn)(PhysicsObject*, PhysicsObject*, const nlVector3&);

    PhysicsNPC(float);
    virtual ~PhysicsNPC();
    virtual int GetObjectType() const { return 0x1A; };
    virtual int SetContactInfo(dContact*, PhysicsObject*, bool);
    virtual int Contact(PhysicsObject*, dContact*, int);

    void SetCallbackFunction(CallbackFn cb);
    // void SetCallbackFunction(void (*)(PhysicsObject*, PhysicsObject*, const nlVector3&));

    /* 0x2C */ CallbackFn mpTriggerCallbackFunc;
    /* 0x30 */ /*SkinAnimatedMovableNPC*/ PhysicsObject* mpAINPC;
};

#endif // _PHYSICSNPC_H_
