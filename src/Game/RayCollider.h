#ifndef _RAYCOLLIDER_H_
#define _RAYCOLLIDER_H_

#include "NL/nlMath.h"
#include "CollisionSpace.h"
#include "Game/Physics/PhysicsObject.h"

class RayCollider
{
public:
    virtual u8 DoCollide(CollisionSpace*);
    ~RayCollider();
    RayCollider(float, const nlVector3&, const nlVector3&);

    /* 0x04 */ dGeomID m_rayID;
    /* 0x08 */ PhysicsObject* m_unk_0x08;
    /* 0x08 */ u8 m_padding[28];
    /* 0x28 */ u8 m_unk_0x28;
};

#endif // _RAYCOLLIDER_H_
