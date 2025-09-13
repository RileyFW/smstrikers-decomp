#ifndef _DRAWABLEOBJ_H_
#define _DRAWABLEOBJ_H_

#include "NL/nlMath.h"
#include "NL/gl/gl.h"

#include "Game/World.h"

class glModel;

class AABBDimensions
{
public:
    /* 0x00 */ nlVector3 mMin;
    /* 0x0C */ nlVector3 mMax;
    /* 0x18 */ nlVector3 mDim;
}; // total size: 0x24

class DrawableObject
{
public:
    DrawableObject();
    /* 0x04 */ virtual ~DrawableObject();
    /* 0x08 */ virtual void Clone() const { };
    /* 0x0C */ virtual void Draw() = 0;
    /* 0x10 */ virtual void DrawPlanarShadow() { };
    /* 0x14 */ virtual bool IsDrawableModel() { return false; };
    /* 0x18 */ virtual DrawableModel* AsDrawableModel() { return NULL; };
    /* 0x1C */ virtual void GetAABBDimensions(AABBDimensions&, bool) const;

    nlMatrix4& GetWorldMatrix() const;

    /* 0x4, */ nlMatrix4 m_worldMatrix;
    /* 0x44 */ bool m_worldMatrixUpToDate;
    /* 0x48 */ nlQuaternion m_orientation;
    /* 0x58 */ nlVector3 m_translation;
    /* 0x64 */ float m_scale;
    /* 0x68 */ float m_translucency;
    /* 0x6C */ AABBDimensions* m_pCachedAABB;
    /* 0x70 */ unsigned long m_uHashID;
    /* 0x74 */ unsigned long m_uRenderLayer;
    /* 0x78 */ unsigned long m_uObjectCreationFlags;
    /* 0x7C */ nlVector3 m_v3Offset;
    /* 0x88 */ World* m_pWorldContext;
    /* 0x8C */ u32 m_uObjectFlags;
    /* 0x90 */ f32 m_fBoundingRadius;
    /* 0x94 */ bool m_bRenderPlanarShadow;
    /* 0x98 */ glModel* (*m_CB)(struct glModel*, enum eGLView&, unsigned long&);

    // /* 0x04 */ nlMatrix4 m_worldMatrix;
    // /* 0x44 */ u8 m_unk_0x44;
    // /* 0x45 */ u8 m_unk_0x45;
    // /* 0x46 */ u8 m_unk_0x46;
    // /* 0x47 */ u8 m_unk_0x47;
    // /* 0x48 */ nlQuaternion m_quat_0x48;
    // /* 0x58 */ nlVector3 m_position;
    // /* 0x64 */ float m_scaling_0x64;
    // /* 0x68 */ float m_unk_0x68;

    // /* 0x6C */ void* m_objref_0x6C;

    // /* 0x70 */ void* m_unk_0x70;
    // /* 0x74 */ void* m_unk_0x74;
    // /* 0x78 */ void* m_unk_0x78;
    // /* 0x7C */ void* m_unk_0x7C;
    // /* 0x80 */ void* m_unk_0x80;
    // /* 0x84 */ void* m_unk_0x84;
    // /* 0x88 */ void* m_unk_0x88;
    // /* 0x8C */ u32 m_visibility; // or flag if a bit field...
    // /* 0x90 */ u32 m_unk_0x90;
    // /* 0x94 */ bool m_unk_0x94;
    // /* 0x98 */ u32 m_unk_0x98;
}; // total size: 0x9C

#endif // _DRAWABLEOBJ_H_
