#include "Game/Debug/ShapeRender.h"

#include "NL/gl/glDraw2.h"
#include "NL/gl/glState.h"

/**
 * Offset/Address/Size: 0x149C | 0x801FC72C | size: 0x418
 */
void ShapeRender::CreateHemisphereGeometry(PrimitiveShape&)
{
}

/**
 * Offset/Address/Size: 0x11C0 | 0x801FC450 | size: 0x2DC
 */
void ShapeRender::CreateFlatCylinderEndGeometry(PrimitiveShape&)
{
}

/**
 * Offset/Address/Size: 0xE14 | 0x801FC0A4 | size: 0x3AC
 */
void ShapeRender::CreateCylinderGeometry(PrimitiveShape&)
{
}

/**
 * Offset/Address/Size: 0xAC0 | 0x801FBD50 | size: 0x354
 */
void ShapeRender::DrawSpherePrimitive(const nlMatrix4&, float, const nlColour&) const
{
}

/**
 * Offset/Address/Size: 0x930 | 0x801FBBC0 | size: 0x190
 */
void ShapeRender::DrawLine3D(const nlVector3&, const nlVector3&, const nlColour&, bool) const
{
}

/**
 * Offset/Address/Size: 0x7EC | 0x801FBA7C | size: 0x144
 */
void ShapeRender::DrawRectangle2D(float x, float y, float w, float h, float z, const nlColour& colour, int view) const
{
    glSetDefaultState(false);
    glSetRasterState(GLS_AlphaBlend, 1);
    glSetRasterState(GLS_AlphaTest, 1);
    glSetRasterState(GLS_AlphaTestRef, 0);
    glSetCurrentRasterState(glHandleizeRasterState());
    glSetCurrentTexture(glGetTexture("global/white"), GLTT_Diffuse);

    float right = y + h;
    float bottom = x + w;

    glPoly2 poly;
    poly.m_pos[0].f.x = x;
    poly.m_pos[0].f.y = y;

    glPoly2* pPoly = &poly;

    poly.m_pos[1].f.x = x;
    poly.m_pos[1].f.y = right;
    poly.m_pos[2].f.x = bottom;
    poly.m_pos[2].f.y = right;
    poly.m_pos[3].f.x = bottom;
    poly.m_pos[3].f.y = y;

    poly.m_colour[3] = colour;
    poly.m_colour[2] = colour;
    poly.m_colour[1] = colour;
    poly.m_colour[0] = colour;

    poly.depth = z;

    eGLView v = (eGLView)view;
    if (view == -1)
    {
        v = GLV_Debug;
    }
    pPoly->Attach(v, 0, NULL, -1);
}

/**
 * Offset/Address/Size: 0x0 | 0x801FB290 | size: 0x7EC
 */
void ShapeRender::Initialize()
{
}
