#ifndef _PHYSICSOBJECT_H_
#define _PHYSICSOBJECT_H_

#include "NL/nlMath.h"

#include "ode/objects.h"
#include "ode/collision.h"

#include "Game/Physics/PhysicsWorld.h"

class PhysicsObject
{
public:
    static float DefaultGravity;

    enum CoordinateType
    {
        WORLD_COORDINATES = 0,
        RELATIVE_TO_PARENT = 1,
    };

    virtual ~PhysicsObject();
    PhysicsObject(PhysicsWorld*);

    void CloneObject(const PhysicsObject&);
    virtual int GetObjectType() const = 0;                               // 0x0C
    virtual int SetContactInfo(dContact*, PhysicsObject*, bool);         // 0x10
    virtual void PreUpdate();                                            // 0x14
    virtual void PostUpdate();                                           // 0x18
    virtual int PreCollide();                                            // 0x1c
    virtual int Contact(PhysicsObject*, dContact*, int);                 // 0x20
    virtual int Contact(PhysicsObject*, dContact*, int, PhysicsObject*); // 0x24
    void MakeStatic();
    void SetMass(float);
    void Reconnect(dSpaceID);
    dSpaceID Disconnect();
    void EnableCollisions();
    void DisableCollisions();
    void SetWorldMatrix(const nlMatrix4&);
    void SetDefaultContactInfo(dContact*);
    void ZeroForceAccumulators();
    void AddForceAtCentreOfMass(const nlVector3&);
    void GetAngularVelocity(nlVector3*) const;
    void SetAngularVelocity(const nlVector3&);
    nlVector3* GetLinearVelocity();
    void GetLinearVelocity(nlVector3*) const;
    void SetLinearVelocity(const nlVector3&);
    void GetRotation(nlMatrix4*) const;
    void SetRotation(const nlMatrix4&);
    void SetRotation(const nlMatrix3&);
    nlVector3* GetPosition();
    void GetPosition(nlVector3*) const;
    void SetPosition(const nlVector3&, CoordinateType);
    void CheckForNaN();
    void SetCategory(unsigned int);
    void SetCollide(unsigned int);
    void SetDefaultCollideBits();

    /* 0x04 */ dBodyID m_bodyID;
    /* 0x08 */ dGeomID m_geomID;
    /* 0x0c */ PhysicsObject* m_parentObject;
    /* 0x10 */ float m_gravity;
    /* 0x14 */ nlVector3 m_position;
    /* 0x20 */ nlVector3 m_linearVelocity;
};

#endif // _PHYSICSOBJECT_H_
