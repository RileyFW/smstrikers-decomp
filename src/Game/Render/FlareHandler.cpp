#include "Game/Render/FlareHandler.h"

#include "Game/Game.h"

#include "NL/nlMath.h"
#include "NL/nlMemory.h"
#include "NL/gl/glView.h"

#include "NL/gl/gluMeshWriter.h"

FlareHandler FlareHandler::instance;

nlVector3 v191 = { 0x00000000, 0x00000002, 0x00000003 };

/**
 * Offset/Address/Size: 0x818 | 0x8016A93C | size: 0x4
 */
void FlareHandler::Initialize()
{
    // EMPTY
}

/**
 * Offset/Address/Size: 0x7B8 | 0x8016A8DC | size: 0x60
 */
void FlareHandler::Cleanup()
{
    while (halos.m_headNode != 0)
    {
        efBaseNode* obj = halos.Remove();
        delete obj;
    }

    while (glows.m_headNode != 0)
    {
        efBaseNode* obj = glows.Remove();
        delete obj;
    }
}

/**
 * Offset/Address/Size: 0x6C4 | 0x8016A7E8 | size: 0xF4
 */
void FlareHandler::AddHalo(const nlMatrix4& mat)
{
    FlareStruct* p = new (nlMalloc(0x20, 8, false)) FlareStruct();

    p->type = Flare_Halo;

    nlVector3 out, dir;
    nlVec3Set(dir, 1.0f, 0.0f, 0.0f);
    nlMultDirVectorMatrix(out, dir, mat);

    float xx = out.f.x * out.f.x;
    float yy = out.f.y * out.f.y;
    float zz = out.f.z * out.f.z;
    p->size = nlSqrt(xx + yy + zz, true);

    p->colour.c[0] = 0xFF;
    p->colour.c[1] = 0xFF;
    p->colour.c[2] = 0xFF;
    p->colour.c[3] = 0xFF;

    p->worldPosition = *(nlVector3*)&mat.f.m41;

    halos.Insert(p);
}

/**
 * Offset/Address/Size: 0x5D0 | 0x8016A6F4 | size: 0xF4
 */
void FlareHandler::AddGlow(const nlMatrix4& mat)
{
    FlareStruct* p = new (nlMalloc(0x20, 8, false)) FlareStruct();

    p->type = Flare_Glow;

    nlVector3 out, dir;
    nlVec3Set(dir, 1.0f, 0.0f, 0.0f);
    nlMultDirVectorMatrix(out, dir, mat);

    float xx = out.f.x * out.f.x;
    float yy = out.f.y * out.f.y;
    float zz = out.f.z * out.f.z;
    p->size = nlSqrt(xx + yy + zz, true);

    p->colour.c[0] = 0xFF;
    p->colour.c[1] = 0xFF;
    p->colour.c[2] = 0xFF;
    p->colour.c[3] = 0xFF;

    p->worldPosition = *(nlVector3*)&mat.f.m41;

    halos.Insert(p);
}

/**
 * Offset/Address/Size: 0x290 | 0x8016A3B4 | size: 0x340
 */
void FlareHandler::AddFace(const FlareStruct* pFlare, GLMeshWriter* pMeshWriter)
{
    class nlVector3 position;     // r1+0x3C
    class nlVector3 viewPosition; // r1+0x30
    class nlVector3 v[4];         // r1+0x48
    float sn;                     // r1+0xC
    float cs;                     // r1+0x8

    nlMultPosVectorMatrix(position, pFlare->worldPosition, viewMatrix);
    if (position.f.y == 0.0f)
    {
        sn = 0.0f;
        cs = 0.5f * pFlare->size;
    }
    else
    {
        nlSinCos(&sn, &cs, (u16)(8192.0f * (position.f.x / position.f.y) + 128.f));
        float temp_f2 = 0.5f * pFlare->size;
        sn *= temp_f2;
        cs *= temp_f2;
    }

    nlVector3 a; // +R*cs + U*sn
    a.f.x = cs * viewRight.f.x + sn * viewUp.f.x;
    a.f.y = cs * viewRight.f.y + sn * viewUp.f.y;
    a.f.z = cs * viewRight.f.z + sn * viewUp.f.z;

    nlVector3 b; // -R*sn + U*cs
    b.f.x = (-sn) * viewRight.f.x + cs * viewUp.f.x;
    b.f.y = (-sn) * viewRight.f.y + cs * viewUp.f.y;
    b.f.z = (-sn) * viewRight.f.z + cs * viewUp.f.z;

    const nlVector3 C = pFlare->worldPosition;
    nlVec3Set(v[0], C.f.x + a.f.x + b.f.x, C.f.y + a.f.y + b.f.y, C.f.z + a.f.z + b.f.z);
    nlVec3Set(v[1], C.f.x - a.f.x + b.f.x, C.f.y - a.f.y + b.f.y, C.f.z - a.f.z + b.f.z);
    nlVec3Set(v[2], C.f.x - a.f.x - b.f.x, C.f.y - a.f.y - b.f.y, C.f.z - a.f.z - b.f.z);
    nlVec3Set(v[3], C.f.x + a.f.x - b.f.x, C.f.y + a.f.y - b.f.y, C.f.z + a.f.z - b.f.z);

    nlVector2 uv;
    uv.f.x = 1.0f;
    uv.f.y = 0.0f;
    pMeshWriter->Texcoord(uv);
    pMeshWriter->Colour(pFlare->colour);
    pMeshWriter->Vertex(v[0]);

    uv.f.x = 1.0f;
    uv.f.y = 1.0f;
    pMeshWriter->Texcoord(uv);
    pMeshWriter->Colour(pFlare->colour);
    pMeshWriter->Vertex(v[1]);

    uv.f.x = 0.0f;
    uv.f.y = 1.0f;
    pMeshWriter->Texcoord(uv);
    pMeshWriter->Colour(pFlare->colour);
    pMeshWriter->Vertex(v[2]);

    uv.f.x = 0.0f;
    uv.f.y = 0.0f;
    pMeshWriter->Texcoord(uv);
    pMeshWriter->Colour(pFlare->colour);
    pMeshWriter->Vertex(v[3]);
}

/**
 * Offset/Address/Size: 0x0 | 0x8016A124 | size: 0x290
 */
void FlareHandler::Render()
{
    eGLStream sp8 = GLStream_Position;

    if ((g_pGame->mbCaptainShotToScoreOn == false) && ((halos.m_headNode != NULL) || (glows.m_headNode != NULL)))
    {
        glViewGetViewMatrix(GLV_Unshadowed, viewMatrix);
        nlVec3Set(viewRight, viewMatrix.f.m11, viewMatrix.f.m21, viewMatrix.f.m31); // this->unk40 = this->unk0;        // this->unk44 = this->unk10;        // this->unk48 = this->unk20;
        nlVec3Set(viewUp, viewMatrix.f.m12, viewMatrix.f.m22, viewMatrix.f.m32);
        glSetDefaultState(1);
        glSetCurrentProgram(glGetProgram("3d unlit"));
        glSetRasterState(GLS_DepthWrite, 0U);
        glSetRasterState(GLS_Culling, 0U);
        glSetRasterState(GLS_AlphaBlend, 3U);
        glSetRasterState(GLS_AlphaTest, 1U);
        glSetCurrentRasterState(glHandleizeRasterState());
        glSetCurrentTexture(glGetTexture("global/white"), GLTT_Diffuse);

        if (halos.m_headNode != NULL)
        {
            GLMeshWriter writer; // sp84
            glSetCurrentTexture(glGetTexture("global/flare_halo"), (eGLTextureType)0);
            if (writer.Begin(halos.m_numNodes * 4, (eGLPrimitive)3, 3, (eGLStream*)&sp8, 0) != 0)
            {
                FlareStruct* flare = (FlareStruct*)halos.m_headNode;
                while (flare != NULL)
                {
                    AddFace(flare, &writer);
                    flare = (FlareStruct*)flare->m_nextNode;
                }

                if (writer.End())
                {
                    glViewAttachModel((eGLView)0x13, writer.GetModel());
                }
            }
        }

        if (glows.m_headNode != NULL)
        {
            GLMeshWriter writer;
            glSetCurrentTexture(glGetTexture("global/flare_glow"), (eGLTextureType)0);
            if (writer.Begin(glows.m_numNodes * 4, (eGLPrimitive)3, 3, (eGLStream*)&sp8, 0) != 0)
            {

                FlareStruct* glow = (FlareStruct*)glows.m_headNode;
                while (glow != NULL)
                {
                    AddFace(glow, &writer);
                    glow = (FlareStruct*)glow->m_nextNode;
                }

                if (writer.End())
                {
                    glViewAttachModel((eGLView)0x13, writer.GetModel());
                }
            }
        }
    }
}
