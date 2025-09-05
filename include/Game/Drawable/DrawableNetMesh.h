#ifndef _DRAWABLENETMESH_H_
#define _DRAWABLENETMESH_H_

#include "Game/Drawable/DrawableObj.h"

// void Replayable<0, LoadFrame, float>(LoadFrame&, float&);
// void Replayable<0, SaveFrame, float>(SaveFrame&, float&);
// void 0x8028D2BC..0x8028D2C0 | size: 0x4;

class LoadFrame;
class SaveFrame;
class NetMesh;

class DrawableNetMesh
{
public:
    void Replay(SaveFrame&);
    void Replay(LoadFrame&);
    void Blend(float, const DrawableNetMesh&, const DrawableNetMesh&);
    void Grab(NetMesh&);
    void Render() const;
    void RenderInvisiblePlanes() const;
    ~DrawableNetMesh();
    DrawableNetMesh(bool);
};

#endif // _DRAWABLENETMESH_H_
