#ifndef _DRAWABLEOBJ_H_
#define _DRAWABLEOBJ_H_

#include "NL/nlMath.h"

class AABBDimensions {
public:
    float unk0;   // 0x00
    float unk4;   // 0x04
    float unk8;   // 0x08
    float unkC;   // 0x0C
    float unk10;  // 0x10
    float unk14;  // 0x14
    float unk18;  // 0x18
    float unk1C;  // 0x1C
    float unk20;  // 0x20
};

class DrawableObject
{
public:
    virtual void Clone();
    virtual void __Something() = 0;
    virtual void DrawPlanarShadow();
    virtual bool IsDrawableModel();
    virtual void AsDrawableModel();
    virtual void GetAABBDimensions(AABBDimensions&, bool) const;
    
    nlMatrix4* GetWorldMatrix() const;

    virtual ~DrawableObject();
    DrawableObject();

    /* 0x04 */ nlMatrix4 m_worldMatrix;
    /* 0x44 */ u8 m_unk_0x44;
    /* 0x45 */ u8 m_unk_0x45;
    /* 0x46 */ u8 m_unk_0x46;
    /* 0x47 */ u8 m_unk_0x47;
    /* 0x48 */ nlQuaternion m_quat_0x48;
    /* 0x58 */ nlVector3 m_position;
    /* 0x64 */ float m_scaling_0x64;
    /* 0x68 */ float m_unk_0x68;

    /* 0x6C */ void *m_objref_0x6C;

    /* 0x70 */ void *m_unk_0x70;
    /* 0x74 */ void *m_unk_0x74;
    /* 0x78 */ void *m_unk_0x78;
    /* 0x7C */ void *m_unk_0x7C;
    /* 0x80 */ void *m_unk_0x80;
    /* 0x84 */ void *m_unk_0x84;
    /* 0x88 */ void *m_unk_0x88;
    /* 0x8C */ u32 m_visibility; // or flag if a bit field...
    /* 0x90 */ u32 m_unk_0x90;
    /* 0x94 */ bool m_unk_0x94;
    /* 0x98 */ u32 m_unk_0x98;
};

#endif // _DRAWABLEOBJ_H_
