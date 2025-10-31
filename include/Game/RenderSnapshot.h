#ifndef _RENDERSNAPSHOT_H_
#define _RENDERSNAPSHOT_H_

#include "types.h"
#include "NL/nlMath.h"

#include "Game/Drawable/DrawableBall.h"
#include "Game/Drawable/DrawableCharacter.h"
#include "Game/Drawable/DrawablePowerup.h"
#include "Game/Drawable/DrawableExplosionFragment.h"

// void Replayable<0, SaveFrame, DrawableCharacter>(SaveFrame&, DrawableCharacter&);
// void Replayable<0, SaveFrame, DrawablePowerup>(SaveFrame&, DrawablePowerup&);
// void Replayable<0, SaveFrame, DrawableExplosionFragment>(SaveFrame&, DrawableExplosionFragment&);
// void Replayable<0, SaveFrame, bool>(SaveFrame&, bool&);
// void Replayable<0, SaveFrame, DrawableBall>(SaveFrame&, DrawableBall&);
// void Replayable<1, SaveFrame, nlVector3>(SaveFrame&, nlVector3&);
// void Replayable<1, SaveFrame, bool>(SaveFrame&, bool&);
// void Replayable<1, SaveFrame, CrowdManager>(SaveFrame&, CrowdManager&);
// void Replayable<3, SaveFrame, EmissionManager>(SaveFrame&, EmissionManager&);
// void Replayable<1, SaveFrame, DrawableNetMesh>(SaveFrame&, DrawableNetMesh&);
// void Replayable<0, LoadFrame, DrawableCharacter>(LoadFrame&, DrawableCharacter&);
// void Replayable<0, LoadFrame, DrawablePowerup>(LoadFrame&, DrawablePowerup&);
// void Replayable<0, LoadFrame, DrawableExplosionFragment>(LoadFrame&, DrawableExplosionFragment&);
// void Replayable<0, LoadFrame, bool>(LoadFrame&, bool&);
// void Replayable<0, LoadFrame, DrawableBall>(LoadFrame&, DrawableBall&);
// void Replayable<1, LoadFrame, nlVector3>(LoadFrame&, nlVector3&);
// void Replayable<1, LoadFrame, bool>(LoadFrame&, bool&);
// void Replayable<1, LoadFrame, CrowdManager>(LoadFrame&, CrowdManager&);
// void Replayable<3, LoadFrame, EmissionManager>(LoadFrame&, EmissionManager&);
// void Replayable<1, LoadFrame, DrawableNetMesh>(LoadFrame&, DrawableNetMesh&);

class DrawableNetMesh;

class RenderSnapshot
{
public:
    // void Replay<SaveFrame>(SaveFrame&);
    // void Replay<LoadFrame>(LoadFrame&);
    void Initialize();
    void Free();
    void Grab();
    int NumDrawableObjects() const;
    const nlVector3& GetPositionForDrawableObject(int) const;
    void Invalidate();
    void Render(float) const;
    void RenderDebugInfo(const RenderSnapshot&, const RenderSnapshot&, float) const;
    void Blend(const float*, const RenderSnapshot&, const RenderSnapshot&);
    RenderSnapshot& GetMutable();

    /*  0x0000 */ unsigned int mEvents;
    /*  0x0004 */ bool mValid;
    /*  0x0005 */ bool mGoalLight;
    /*  0x0008 */ DrawableBall mBall;
    /*  0x004C */ DrawableCharacter mCharacters[10];
    /*  0x03BC */ DrawablePowerup mPowerups[150];
    /*  0x167C */ DrawableExplosionFragment mExplosionFragments[20];
    /*  0x19EC */ DrawableCharacter mChainChomp;
    /*  0x1A44 */ DrawableCharacter mBowser;
    /*  0x1A9C */ DrawableNetMesh* mpNetMeshPositiveX;
    /*  0x1AA0 */ DrawableNetMesh* mpNetMeshNegativeX;
    /*  0x1AA4 */ bool mDoGoalieNetTestPosX;
    /*  0x1AA5 */ bool mDoGoalieNetTestNegX;
    /*  0x1AA8 */ unsigned char* mpExplodableVisibilityRecords;
    /*  0x1AAC */ int mNumExplodables;
    /*  0x1AB0 */ nlVector3 mCameraUp;
    /*  0x1ABC */ float mFrameBlendPercent;
}; // total size: 0x1ABC

// SIZE: 0x1AC0

#endif // _RENDERSNAPSHOT_H_
