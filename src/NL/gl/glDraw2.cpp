#include "NL/gl/glDraw2.h"

#include "NL/nlMath.h"

#include "NL/gl/gl.h"
#include "NL/gl/glState.h"
#include "NL/gl/glView.h"
#include "NL/gl/glStruct.h"
#include "NL/gl/glMatrix.h"

#include "NL/gl/glModel.h"
#include "NL/gl/glUserData.h"

#include "Game/GL/gluMeshWriter.h"

unsigned long StripMap[4] = { 3, 0, 2, 1 };
unsigned long QuadMap[4] = { 0, 1, 2, 3 };
unsigned long TriListMap[6] = { 3, 0, 2, 0, 2, 1 };

static unsigned long _defaultProgram = glGetProgram("2d unlit");

/**
 * Offset/Address/Size: 0x610 | 0x801D7C10 | size: 0x210
 */
bool glPoly2::Attach(eGLView view, int layer, unsigned long* pMatrix, unsigned long /*user*/)
{
    eGLStream streamsDesc[3];
    streamsDesc[0] = eGLStream_0;
    streamsDesc[1] = eGLStream_2;
    streamsDesc[2] = eGLStream_3;

    GLMeshWriter writer;

    const unsigned char stateFlag = gl_GetCurrentStateBundle()->m_nFlags;

    const unsigned long prevProg = glSetCurrentProgram(_defaultProgram);
    const unsigned long mat = pMatrix ? *pMatrix : glGetIdentityMatrix();
    const unsigned long prevMat = glSetCurrentMatrix(mat);

    const bool hasQuads = (glHasQuads() & 0xFF) != 0;
    const eGLPrimitive prim = hasQuads ? eGLPrimitive_3 : eGLPrimitive_1;
    const unsigned long* map = hasQuads ? QuadMap : StripMap;

    const int streamCount = static_cast<int>(stateFlag) + 2;

    if (!writer.Begin(4, prim, streamCount, streamsDesc, false))
    {
        glSetCurrentProgram(prevProg);
        glSetCurrentMatrix(prevMat);
        return false;
    }

    for (int i = 0; i < 4; ++i)
    {
        const unsigned idx = static_cast<unsigned>(map[i]);

        writer.Colour(*reinterpret_cast<const nlColour*>(reinterpret_cast<const char*>(this) + 0x40
                                                         + (idx << 2)));

        if (stateFlag)
        {
            writer.Texcoord(*reinterpret_cast<const nlVector2*>(reinterpret_cast<const char*>(this) + 0x20
                                                                + (idx << 3)));
        }

        const float* xy = reinterpret_cast<const float*>(reinterpret_cast<const char*>(this) + (idx << 3));
        nlVector3 p;
        p.f.x = xy[0];
        p.f.y = xy[1];
        p.f.z = depth;
        writer.Position(p);
    }

    if (!writer.End())
    {
        glSetCurrentProgram(prevProg);
        glSetCurrentMatrix(prevMat);
        return false;
    }

    glViewAttachModel(view, static_cast<unsigned long>(layer), writer.GetModel());

    glSetCurrentProgram(prevProg);
    glSetCurrentMatrix(prevMat);
    return true;
}

/**
 * Offset/Address/Size: 0x33C | 0x801D793C | size: 0x2D4
 */
bool glAttachPoly2(eGLView view, unsigned long count, glPoly2* polys, unsigned long* pMatrix, const void* user)
{
    const eGLStream streamsDesc[3] = { eGLStream_0, eGLStream_2, eGLStream_3 };

    if (*(unsigned char*)((char*)gl_GetCurrentStateBundle() + 0x30) != 1)
    {
        for (unsigned long i = 0; i < count; ++i)
        {
            if (!polys[i].Attach(view, 0, 0, 0xFFFFFFFFu))
                return false;
        }
        return true;
    }

    GLMeshWriter writer;

    const unsigned long* map;
    int vertsPerPoly;
    eGLPrimitive prim;
    if (glHasQuads())
    {
        map = QuadMap;
        vertsPerPoly = 4;
        prim = (eGLPrimitive)3;
    }
    else
    {
        map = TriListMap;
        vertsPerPoly = 6;
        prim = (eGLPrimitive)0;
    }

    unsigned long oldProg = glSetCurrentProgram(_defaultProgram);
    unsigned long mat = pMatrix ? *pMatrix : glGetIdentityMatrix();
    unsigned long oldMat = glSetCurrentMatrix(mat);

    if (!writer.Begin((int)(vertsPerPoly * count), prim, 3, streamsDesc, false))
    {
        glSetCurrentMatrix(oldMat);
        glSetCurrentProgram(oldProg);
        return false;
    }

    for (unsigned long i = 0; i < count; ++i)
    {
        glPoly2* p = &polys[i];
        for (int k = 0; k < vertsPerPoly; ++k)
        {
            const unsigned long idx = map[k % (prim == (eGLPrimitive)3 ? 4 : 6)];

            const nlColour& c = *(const nlColour*)((char*)p + 0x40 + (idx << 2));
            writer.Colour(c);

            const nlVector2& uv = *(const nlVector2*)((char*)p + 0x20 + (idx << 3));
            writer.Texcoord(uv);

            const float* pos2 = (const float*)((char*)p + (idx << 3));
            nlVector3 v;
            v.f.x = pos2[0];
            v.f.y = pos2[1];
            v.f.z = p->depth;
            writer.Vertex(v);
        }
    }

    const glModel* model = writer.GetModel();

    if (!user)
    {
        glViewAttachModel(view, model);
    }
    else
    {
        const glModel* dup = glModelDupNoStreams(model, true, false);
        glModelPacket* pkt = *(glModelPacket**)((char*)dup + 0x0C);
        const int num = *(int*)((char*)dup + 0x00);
        char* it = (char*)pkt;
        char* end = it + num * 0x4A;
        while (it < end)
        {
            glUserAttach(user, (glModelPacket*)it, false);
            it += 0x4A;
        }
        glViewAttachModel(view, dup);
    }

    glSetCurrentProgram(oldProg);
    glSetCurrentMatrix(oldMat);
    return true;
}

/**
 * Offset/Address/Size: 0x250 | 0x801D7850 | size: 0xEC
 */
void glPoly2::FullCoverage(const nlColour& col, float z)
{
    const float width = glGetOrthographicWidth();
    const float height = glGetOrthographicHeight();
    gl_ScreenInfo* screenInfo = glGetScreenInfo();
    const float border = screenInfo->m_unk_0x20;

    nlVec2Set(m_pos[0], -border, -border);
    nlVec2Set(m_pos[1], -border, height - border);
    nlVec2Set(m_pos[2], width - border, height - border);
    nlVec2Set(m_pos[3], width - border, -border);

    depth = z;

    nlVec2Set(m_uv[0], 0.0f, 0.0f);
    nlVec2Set(m_uv[1], 0.0f, 1.0f);
    nlVec2Set(m_uv[2], 1.0f, 1.0f);
    nlVec2Set(m_uv[3], 1.0f, 0.0f);

    m_colour[0] = col;
    m_colour[1] = col;
    m_colour[2] = col;
    m_colour[3] = col;
}

/**
 * Offset/Address/Size: 0x1EC | 0x801D77EC | size: 0x64
 */
void glPoly2::SetupRectangle(float x, float y, float w, float h, float z)
{
    f32 bottom_y;
    f32 right_x;

    nlVec2Set(m_pos[0], x, y);
    nlVec2Set(m_pos[1], x, y + h);
    nlVec2Set(m_pos[2], x + w, y + h);
    nlVec2Set(m_pos[3], x + w, y);

    nlVec2Set(m_uv[0], 0.0f, 0.0f);
    nlVec2Set(m_uv[1], 0.0f, 1.0f);
    nlVec2Set(m_uv[2], 1.0f, 1.0f);
    nlVec2Set(m_uv[3], 1.0f, 0.0f);

    if (z != 1e10f)
    {
        depth = z;
    }
}

/**
 * Offset/Address/Size: 0x18 | 0x801D7618 | size: 0x1D4
 */
void glPoly2::SetupRotatedRectangle(float cx, float cy, float w, float h, float angle, float z)
{
    nlVector2 v;
    nlMatrix3 m;
    f32 temp_f26;
    f32 temp_f25;
    f32 temp_f31;

    nlMakeRotationMatrixZ(m, angle);

    temp_f26 = -w * 0.5f;
    temp_f31 = -h * 0.5f;
    v.f.x = temp_f26;
    v.f.y = temp_f31;
    nlMultVectorMatrix(v, v, m);
    temp_f25 = h * 0.5f;
    nlVec2Set(m_pos[0], v.f.x + cx, v.f.y + cy);
    v.f.x = temp_f26;
    v.f.y = temp_f25;
    nlMultVectorMatrix(v, v, m);
    temp_f26 = w * 0.5f;
    nlVec2Set(m_pos[1], v.f.x + cx, v.f.y + cy);
    v.f.x = temp_f26;
    v.f.y = temp_f25;
    nlMultVectorMatrix(v, v, m);
    nlVec2Set(m_pos[2], v.f.x + cx, v.f.y + cy);
    v.f.x = temp_f26;
    v.f.y = temp_f31;
    nlMultVectorMatrix(v, v, m);
    nlVec2Set(m_pos[3], v.f.x + cx, v.f.y + cy);

    nlVec2Set(m_uv[0], 0.0f, 0.0f);
    nlVec2Set(m_uv[1], 0.0f, 1.0f);
    nlVec2Set(m_uv[2], 1.0f, 1.0f);
    nlVec2Set(m_uv[3], 1.0f, 0.0f);

    if (z != 1e10f)
    {
        depth = z;
    }
}

/**
 * Offset/Address/Size: 0x0 | 0x801D7600 | size: 0x18
 */
void glPoly2::SetColour(const nlColour& col)
{
    m_colour[0] = col;
    m_colour[1] = col;
    m_colour[2] = col;
    m_colour[3] = col;
}
