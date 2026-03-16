#include "Game/Debug/ShapeRender.h"

#include "Game/GL/gluMeshWriter.h"

#include "NL/gl/glDraw2.h"
#include "NL/gl/glMemory.h"
#include "NL/gl/glMatrix.h"
#include "NL/gl/glState.h"

extern const u32 WhiteTexture;

/**
 * Offset/Address/Size: 0x149C | 0x801FC72C | size: 0x418
 */
void ShapeRender::CreateHemisphereGeometry(PrimitiveShape&)
{
}

/**
 * Offset/Address/Size: 0x11C0 | 0x801FC450 | size: 0x2DC
 * TODO: 66.07% match - register allocation and constant ordering in the segment loop still differ.
 */
void ShapeRender::CreateFlatCylinderEndGeometry(PrimitiveShape& prim)
{
    nlVector3 vNormal;
    int nSegment;
    nlVector3* pdst;
    nlVector3* ndst;
    nlVector2* tdst;
    float x0;
    float y0;
    float x1;
    float y1;

    prim.vertCount = 0x20;
    prim.position = (nlVector3*)glResourceAlloc(0x180, GLM_VertexData);
    prim.normal = (nlVector3*)glResourceAlloc(0x180, GLM_VertexData);
    prim.texcoord = (nlVector2*)glResourceAlloc(0x100, GLM_VertexData);

    pdst = prim.position;
    ndst = prim.normal;
    tdst = prim.texcoord;

    for (nSegment = 0; nSegment < 0x10; nSegment++)
    {
        u16 angle = (u16)(10430.378f * ((float)nSegment * 0.3926991f));

        x0 = 2.0f * (0.5f * nlSin(angle));
        y0 = 2.0f * (0.5f * nlSin((u16)(angle + 0x4000)));
        x1 = 2.0f * (1.0f * nlSin(angle));
        y1 = 2.0f * (1.0f * nlSin((u16)(angle + 0x4000)));

        pdst->f.x = x0;
        pdst->f.y = y0;
        pdst->f.z = 0.5f;

        {
            float invLen = nlRecipSqrt((0.5f * 0.5f) + (x0 * x0 + y0 * y0), true);
            vNormal.f.x = invLen * x0;
            vNormal.f.y = invLen * y0;
            vNormal.f.z = invLen * 0.5f;
        }
        *ndst = vNormal;

        tdst->f.x = (float)nSegment / 16.0f;
        tdst->f.y = 0.5f;

        pdst[1].f.x = x1;
        pdst[1].f.y = y1;
        pdst[1].f.z = 0.5f;

        {
            float invLen = nlRecipSqrt((0.5f * 0.5f) + (x1 * x1 + y1 * y1), true);
            vNormal.f.x = invLen * x1;
            vNormal.f.y = invLen * y1;
            vNormal.f.z = invLen * 0.5f;
        }
        ndst[1] = vNormal;

        tdst[1].f.x = (float)nSegment / 16.0f;
        tdst[1].f.y = 1.0f;

        pdst += 2;
        ndst += 2;
        tdst += 2;
    }
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
void ShapeRender::DrawLine3D(const nlVector3& p0, const nlVector3& p1, const nlColour& colour, bool bWithDepth) const
{
    GLMeshWriter writer;

    glSetDefaultState(bWithDepth);
    glSetCurrentMatrix(glGetIdentityMatrix());
    glSetCurrentTexture(WhiteTexture, GLTT_Diffuse);
    glSetCurrentProgram(glGetProgram("3d unlit"));

    const eGLStream streams[3] = { GLStream_Position, GLStream_Colour, GLStream_Diffuse };

    if (writer.Begin(2, GLP_LineList, 3, streams, false))
    {
        nlVector2 uv0;
        nlVector2 uv1;

        writer.Colour(colour);
        uv0.f.x = 0.0f;
        uv0.f.y = 0.0f;
        ((GLMeshWriterCore*)&writer)->Texcoord(uv0);
        writer.Vertex(p0);

        writer.Colour(colour);
        uv1.f.x = 0.0f;
        uv1.f.y = 0.0f;
        ((GLMeshWriterCore*)&writer)->Texcoord(uv1);
        writer.Vertex(p1);

        if (!writer.End())
        {
            return;
        }

        glViewAttachModel(m_eView, 2, writer.GetModel());
    }
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
