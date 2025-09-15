#ifndef _NETMESH_H_
#define _NETMESH_H_

#include "NL/nlMath.h"
#include "Game/Sys/eventman.h"

class PhysicsSphere;

class NetMesh
{
public:
    static bool s_bAnimatedNetMeshEnabled;

    NetMesh(bool);
    void Allocate(int, int, int);
    ~NetMesh();
    void SetPositionConstraint(int, const nlVector3&);
    void SetDistanceConstraint(int, int, float);
    void UpdateUntilRelaxed();
    void Update(float, const nlVector3&, const nlVector3&, bool, PhysicsSphere*);
    void JoltNet(float);
    void SatisfyConstraints(const nlVector3&, bool);
    void AddForcesToBall(const nlVector3&, PhysicsSphere*);
    void Initialize(unsigned long);
    void SetTriStripIndices(int, const unsigned short*);
    void SetDontUseLowestNetTextureLOD(bool);
    void SetTexture(unsigned long);
};

class BallNetmeshEventData : public EventData
{
public:
    virtual u32 GetID()
    {
        return 0x118;
    };
};

#endif // _NETMESH_H_
