#ifndef _RAYCOLLIDER_H_
#define _RAYCOLLIDER_H_

#include "NL/nlMath.h"
#include "Game/Physics/CollisionSpace.h"
#include "Game/Physics/PhysicsObject.h"

class RayCollider
{
public:
    RayCollider(float, const nlVector3&, const nlVector3&);
    ~RayCollider();

    virtual bool DoCollide(CollisionSpace*);

    /* 0x04 */ dGeomID m_rayID;
    /* 0x08 */ PhysicsObject* m_unk_0x08;
    /* 0x08 */ u8 m_padding[28];
    /* 0x28 */ u8 m_unk_0x28;
};

#endif // _RAYCOLLIDER_H_
