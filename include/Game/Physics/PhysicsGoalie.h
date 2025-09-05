#ifndef _PHYSICSGOALIE_H_
#define _PHYSICSGOALIE_H_

// void 0x8028D2E4..0x8028D2E8 | size: 0x4;

class PhysicsGoalie : public PhysicsObject
{
public:
    ~PhysicsGoalie();
    void CollideGoalieWithPost();
    void SweepTestEveryBone(float, const nlVector3&, const nlVector3&, nlVector3&, nlVector3&) const;
    void SweepTestForBallContact(const nlVector3&, const nlVector3&, const nlVector3&, float, nlVector3&, nlVector3&) const;
    void PostUpdate();
};

#endif // _PHYSICSGOALIE_H_
