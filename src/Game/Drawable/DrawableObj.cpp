#include "Game/Drawable/DrawableObj.h"

// nlMatrix4 m3Ident = { 1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f };

/**
 * Offset/Address/Size: 0x0 | 0x8011FC70 | size: 0x2C
 */
void DrawableObject::GetAABBDimensions(AABBDimensions& dim, bool param) const
{
    dim.unk0 = 0.f;
    dim.unk4 = 0.f;
    dim.unk8 = 0.f;
    dim.unkC = 0.f;
    dim.unk10 = 0.f;
    dim.unk14 = 0.f;
    dim.unk18 = 0.f;
    dim.unk1C = 0.f;
    dim.unk20 = 0.f;
}

/**
 * Offset/Address/Size: 0x2C | 0x8011FC9C | size: 0x90
 */
nlMatrix4* DrawableObject::GetWorldMatrix() const
{
    nlMatrix4 rot_mtx;
    nlMatrix4 scale_mtx;
    f32 temp_f1;

    if (m_unk_0x44 == 0)
    {
        nlQuatToMatrix(rot_mtx, m_quat_0x48);
        rot_mtx.m[3][0] = m_position.f.x;
        rot_mtx.m[3][1] = m_position.f.y;
        rot_mtx.m[3][2] = m_position.f.z;
        rot_mtx.m[3][3] = 1.f;
        temp_f1 = m_scaling_0x64;
        nlMakeScaleMatrix(scale_mtx, temp_f1, temp_f1, temp_f1);
        nlMultMatrices(*(nlMatrix4*)&m_worldMatrix, scale_mtx, rot_mtx);
        *(u8*)&m_unk_0x44 = 1U;
    }
    return (nlMatrix4*)&m_worldMatrix;
}

/**
 * Offset/Address/Size: 0xBC | 0x8011FD2C | size: 0x68
 */
DrawableObject::~DrawableObject()
{
    if (m_objref_0x6C != 0)
    {
        delete m_objref_0x6C;
    }
}

/**
 * Offset/Address/Size: 0x124 | 0x8011FD94 | size: 0x6C
 */
DrawableObject::DrawableObject()
{
    m_unk_0x44 = 1;
    m_scaling_0x64 = 1.f;

    m_objref_0x6C = NULL;

    m_unk_0x78 = 0;
    m_unk_0x88 = 0;
    m_visibility = 0;
    m_unk_0x94 = 0;

    m_quat_0x48.z = 0.f;
    m_quat_0x48.y = 0.f;
    m_quat_0x48.x = 0.f;
    m_quat_0x48.w = 1.f;

    m_position.f.x = 0.f;
    m_position.f.y = 0.f;
    m_position.f.z = 0.f;

    m_unk_0x68 = 1.f;
    m_unk_0x98 = 0;
    m_visibility = (m_visibility | 1);
}

/**
 * Offset/Address/Size: 0x0 | 0x8011FE00 | size: 0x4
 */
void DrawableObject::DrawPlanarShadow()
{
}

/**
 * Offset/Address/Size: 0x4 | 0x8011FE04 | size: 0x8
 */
bool DrawableObject::IsDrawableModel()
{
    return false;
}
