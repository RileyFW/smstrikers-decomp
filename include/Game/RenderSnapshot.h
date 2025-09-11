#ifndef _RENDERSNAPSHOT_H_
#define _RENDERSNAPSHOT_H_

#include "types.h"
#include "NL/nlMath.h"

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
    void GetMutable();

    /* 0x00 */ char pad1AC0[0x1AC0];
}; // SIZE: 0x1AC0

#endif // _RENDERSNAPSHOT_H_
