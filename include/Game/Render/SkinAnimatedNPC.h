#ifndef _SKINANIMATEDNPC_H_
#define _SKINANIMATEDNPC_H_

#include "Game/SHierarchy.h"
#include "Game/PoseAccumulator.h"
#include "Game/SHierarchy.h"
#include "Game/SAnim.h"
#include "NL/gl/glModel.h"
#include "NL/nlMath.h"

enum ePlayMode
{
    PM_CYCLIC = 0,
    PM_HOLD = 1,
};

class SkinAnimatedNPC
{
public:
    SkinAnimatedNPC(cSHierarchy&, int);
    ~SkinAnimatedNPC();
    void Update(float);
    void Render();
    void RenderFromReplay(const cPoseAccumulator&, const nlMatrix4*);
    void SendToGL() const;
    void DrawShadow(const cPoseAccumulator&, const nlMatrix4&);
    void SetAnimState(cSAnim&, float, ePlayMode);
    void DrawShadow(const glModel*, const nlMatrix4&);

    /* 0x04 */ nlMatrix4 mWorldMatrix;                // offset 0x4, size 0x40
    /* 0x44 */ cPN_SAnimController* mpAnimController; // offset 0x44, size 0x4
    /* 0x48 */ cPoseAccumulator* mpPoseAccumulator;   // offset 0x48, size 0x4
    /* 0x4C */ GLSkinMesh* mpSkinMesh;                // offset 0x4C, size 0x4
    /* 0x50 */ cPoseNode* mpPoseTree;                 // offset 0x50, size 0x4
    /* 0x54 */ bool mbIsVisible;                      // offset 0x54, size 0x1
    /* 0x58 */ glModel* mpLastModel;                  // offset 0x58, size 0x4
}; // total size: 0x5C

#endif // _SKINANIMATEDNPC_H_
