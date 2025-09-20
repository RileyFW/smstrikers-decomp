#ifndef _NETMESH_H_
#define _NETMESH_H_

#include "NL/nlMath.h"
#include "Game/Sys/eventman.h"

class PhysicsSphere;
class nlAVLTreeSlotPool;
class cDistanceConstraint;
class cPositionConstraint;

struct shortVector2
{
    union
    {
        signed short e[2];
        struct
        {
            s16 x;
            s16 y;
        };
    };
}; // total size: 0x4

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

    /* 0x00 */ int m_numAffectedParticles;                  // offset 0x0, size 0x4
    /* 0x04 */ int m_iClosestParticle;                      // offset 0x4, size 0x4
    /* 0x08 */ bool mbInitialized;                          // offset 0x8, size 0x1
    /* 0x09 */ bool mbFirstUpdate;                          // offset 0x9, size 0x1
    /* 0x0C */ nlVector3* m_v3Position;                     // offset 0xC, size 0x4
    /* 0x10 */ nlVector3* m_v3PrevPosition;                 // offset 0x10, size 0x4
    /* 0x14 */ nlVector3* m_v3Accel;                        // offset 0x14, size 0x4
    /* 0x18 */ unsigned char* m_bIsParticleFixed;           // offset 0x18, size 0x4
    /* 0x1C */ unsigned short* m_TriStripIndices;           // offset 0x1C, size 0x4
    /* 0x20 */ int m_NumTriStripIndices;                    // offset 0x20, size 0x4
    /* 0x24 */ shortVector2* m_v2TextureCoords;             // offset 0x24, size 0x4
    /* 0x28 */ nlVector3* m_v3Normal;                       // offset 0x28, size 0x4
    /* 0x2C */ nlVector3 m_v3TempConstraint;                // offset 0x2C, size 0xC
    /* 0x38 */ unsigned long mNetMeshDrawableObjectID;      // offset 0x38, size 0x4
    /* 0x3C */ unsigned char mbPositiveEnd;                 // offset 0x3C, size 0x1
    /* 0x40 */ int m_NumParticles;                          // offset 0x40, size 0x4
    /* 0x44 */ float m_fBallPenetrationDepth;               // offset 0x44, size 0x4
    /* 0x48 */ unsigned char m_bPenetratingFixedParticle;   // offset 0x48, size 0x1
    /* 0x4C */ nlVector3 m_v3BallPenetrationNormal;         // offset 0x4C, size 0xC
    /* 0x58 */ float mfMinX;                                // offset 0x58, size 0x4
    /* 0x5C */ float mfMaxX;                                // offset 0x5C, size 0x4
    /* 0x60 */ float mfMinY;                                // offset 0x60, size 0x4
    /* 0x64 */ float mfMaxY;                                // offset 0x64, size 0x4
    /* 0x68 */ int m_NumPositionConstraints;                // offset 0x68, size 0x4
    /* 0x6C */ int m_NumDistanceConstraints;                // offset 0x6C, size 0x4
    /* 0x70 */ bool mbIsActive;                             // offset 0x70, size 0x1
    /* 0x71 */ bool mbBallIsInsideNet;                      // offset 0x71, size 0x1
    /* 0x74 */ float mfMotion;                              // offset 0x74, size 0x4
    /* 0x78 */ float mJolt;                                 // offset 0x78, size 0x4
    /* 0x7C */ nlAVLTreeSlotPool* mEdgeList;                // offset 0x7C, size 0x4
    /* 0x80 */ nlAVLTreeSlotPool* mVertexList;              // offset 0x80, size 0x4
    /* 0x84 */ cDistanceConstraint* m_aDistanceConstraints; // offset 0x84, size 0x4
    /* 0x88 */ cPositionConstraint* m_aPositionConstraints; // offset 0x88, size 0x4
}; // total size: 0x8C

class BallNetmeshEventData : public EventData
{
public:
    virtual u32 GetID()
    {
        return 0x118;
    };
};

#endif // _NETMESH_H_
