#ifndef _PHYSICSNPC_H_
#define _PHYSICSNPC_H_

#include "Game/Physics/PhysicsObject.h"

class PhysicsNPC : public PhysicsObject
{
public:
    ~PhysicsNPC();
    virtual int SetContactInfo(dContact*, PhysicsObject*, bool);
    virtual int Contact(PhysicsObject*, dContact*, int);
    void SetCallbackFunction(void (*)(PhysicsObject*, PhysicsObject*, const nlVector3&));
    PhysicsNPC(float);
    virtual int GetObjectType() const;
};

#endif // _PHYSICSNPC_H_
