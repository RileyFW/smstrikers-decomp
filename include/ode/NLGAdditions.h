#ifndef _NLGADDITIONS_H_
#define _NLGADDITIONS_H_

#include "ode/common.h"
#include "ode/collision.h"
// #include "ode/objects.h"
// #include "ode/collision.h"
// #include "ode/joint.h"

class dxJointCharacter
{
public:
    /* 0x00 */ u8 m_padding_0x00[0x50];
    /* 0x50 */ dVector3 m_unk_0x50;
};
void dGeomCollideAABBs(dxGeom*, dxGeom*, void*, void (*)(void*, dxGeom*, dxGeom*));
void dGeomMarkAABBAsValid(dxGeom*);
void dGeomComputeAABB(dxGeom*);
void dVector3Add(float*, const float*);
void dVectorScale(float*, float);
void dVector4Set(float*, float, float, float, float);
void dVector3Set(float*, float, float, float);
void dExtractColumn3(float* __restrict, const float* __restrict, int);
void dInvertRigidTransformation(float*, const float*, const float*);
void dMultiplyMatrix4Vector4(float*, const float*, const float*);
void dMultiplyMatrix3Vector3(float*, const float*, const float*, bool);
void dGeomSetGFlags(dxGeom*, int);
int dGeomGetGFlags(dxGeom*);
void dJointSetCharacterNoMotionDirection(dxJoint*, float*);
dxJoint* dJointCreateCharacter(dxWorld*, dxJointGroup*);
// void characterGetInfo1(dxJointCharacter*, dxJoint::Info1*);
// void characterGetInfo2(dxJointCharacter*, dxJoint::Info2*);
void characterInit(dxJointCharacter*);
void dClearCachedData();
void dWorldSetClearAccumulators(dxWorld*, int);
dxBody* dBodyGetNextBody(dxBody*);
dxBody* dWorldGetFirstBody(dxWorld*);
void dBodySetUpdateMode(dxBody*, int, int);

#endif // _NLGADDITIONS_H_
