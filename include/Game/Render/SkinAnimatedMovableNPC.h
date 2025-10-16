#ifndef _SKINANIMATEDMOVABLENPC_H_
#define _SKINANIMATEDMOVABLENPC_H_

#include "Game/Render/SkinAnimatedNPC.h"

#include "Game/SHierarchy.h"
#include "Game/Physics/PhysicsNPC.h"
#include "Game/PoseAccumulator.h"

class SkinAnimatedMovableNPC : public SkinAnimatedNPC
{
public:
    SkinAnimatedMovableNPC(cSHierarchy& pHierarchy, int nModelID, PhysicsNPC& mpPhysObj);
    virtual ~SkinAnimatedMovableNPC();
    virtual SkinAnimatedNPC_Type GetSkinAnimatedNPC_Type() const { return SkinAnimatedNPC_MOVABLE; };
    virtual void Render();
    virtual void RenderFromReplay(const cPoseAccumulator&, const nlMatrix4*);
    virtual void Update(float);
    void AnimTranslate(float, bool);
    void AnimMove(float, bool);
    void AnimMoveSeek(float, float, float, bool);
    void SetPosition(const nlVector3&);

    /* 0x5C */ nlVector3 mv3Position;
    /* 0x68 */ nlVector3 mv3Velocity;
    /* 0x74 */ u16 maFacingDirection;
    /* 0x76 */ u16 maDesiredFacingDirection;
    /* 0x78 */ float mfDesiredSpeed;
    /* 0x7C */ PhysicsNPC* mpPhysObj;
}; // total size: 0x80

#endif // _SKINANIMATEDMOVABLENPC_H_
