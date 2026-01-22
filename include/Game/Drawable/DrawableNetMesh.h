#ifndef _DRAWABLENETMESH_H_
#define _DRAWABLENETMESH_H_

#include "Game/Drawable/DrawableObj.h"
#include "Game/Render/NetMesh.h"

class LoadFrame;
class SaveFrame;

class DrawableNetMesh
{
public:
    DrawableNetMesh(bool);
    ~DrawableNetMesh();

    void Replay(SaveFrame&);
    void Replay(LoadFrame&);
    void Blend(float, const DrawableNetMesh&, const DrawableNetMesh&);
    void Grab(NetMesh&);
    void Render() const;
    void RenderInvisiblePlanes() const;

    /* 0x00 */ nlVector3* mpPosition; // offset 0x0, size 0x4
    /* 0x04 */ int miNetIndex;        // offset 0x4, size 0x4
    /* 0x08 */ int mNumQuads;         // offset 0x8, size 0x4
    /* 0x0C */ int mNumVertices;      // offset 0xC, size 0x4
    /* 0x10 */ int mNumTriIndices;    // offset 0x10, size 0x4
    /* 0x14 */ float mJolt;           // offset 0x14, size 0x4
    /* 0x18 */ bool mbInitialized;    // offset 0x18, size 0x4
    /* 0x1C */ float mJoltCache;      // offset 0x1C, size 0x4
    /* 0x20 */ NetMesh* mpNetMesh;    // offset 0x20, size 0x4
}; // total size: 0x24

#endif // _DRAWABLENETMESH_H_
