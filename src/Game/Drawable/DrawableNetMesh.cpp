#include "Game/Drawable/DrawableNetMesh.h"
#include "Game/Replay.h"
#include "Game/Field.h"
#include "Game/Net.h"
#include "NL/gl/gl.h"
#include "NL/gl/glDraw3.h"
#include "NL/gl/glMatrix.h"
#include "NL/gl/glState.h"

static unsigned long UnlitProgram = glGetProgram("3d unlit");
static unsigned long LitProgram = glGetProgram("3d pointlit");
static unsigned long LightTexture = glGetTexture("global/lightramp");
static unsigned long BlackTexture = glGetTexture("global/black");
static unsigned long WhiteTexture = glGetTexture("global/white");
static unsigned long NetMeshTexture = glGetTexture("global/netmesh");
static unsigned long CheckerTexture = glGetTexture("global/checker");
static int siInvisiblePlaneAlpha;
/**
 * Offset/Address/Size: 0xC4C | 0x80114BA8 | size: 0x24
 */
DrawableNetMesh::DrawableNetMesh(bool isPositiveXNet)
{
    int netFlag = (u32)isPositiveXNet;
    miNetIndex = (netFlag == 0);
    mNumQuads = 0;
    mNumVertices = 0;
    mbInitialized = false;
}

/**
 * Offset/Address/Size: 0xB80 | 0x80114ADC | size: 0xCC
 */
DrawableNetMesh::~DrawableNetMesh()
{
    if (mbInitialized)
    {
        delete[] mpPosition;
    }

    if (sbStaticInitialized[miNetIndex])
    {
        delete[] spTexcoord[miNetIndex];
        delete[] spTriIndices[miNetIndex];
        delete[] spColour[miNetIndex];
        sbStaticInitialized[miNetIndex] = false;
    }

    mNumQuads = 0;
    mNumVertices = 0;
    mbInitialized = false;
}

/**
 * Offset/Address/Size: 0x91C | 0x80114878 | size: 0x264
 * TODO: 88.56% match - matrix row constant register assignment (f0/f3) and
 *       instruction scheduling around netPlaneX setup remain mismatched.
 */
void DrawableNetMesh::RenderInvisiblePlanes() const
{
    float goalLineX = cField::GetGoalLineX(1U);
    float netHeight = cNet::m_fNetHeight;
    float netWidth = cNet::m_fNetWidth;

    glSetDefaultState(true);
    glSetRasterState(GLS_DepthWrite, 1);
    glSetRasterState(GLS_AlphaBlend, 1);
    glSetRasterState(GLS_Culling, 0);
    glSetCurrentRasterState(glHandleizeRasterState());

    glSetCurrentTexture(WhiteTexture, GLTT_Diffuse);
    glSetTextureState(GLTS_DiffuseWrap, 0);
    glSetCurrentTextureState(glHandleizeTextureState());

    nlMatrix4 matrix;
    nlMakeRotationMatrixY(matrix, 1.5707964f);

    float halfHeight = 0.5f * netHeight;
    float netPlaneX;

    nlColour c = { 0xFF, 0xFF, 0xFF, 0x00 };
    c.c[3] = (u8)siInvisiblePlaneAlpha;

    glQuad3 quad;

    netPlaneX = goalLineX - 1.0f;
    matrix.m[3][0] = netPlaneX;
    matrix.m[3][1] = 0.0f;
    matrix.m[3][2] = halfHeight;
    matrix.m[3][3] = 1.0f;
    quad.SetupRotatedRectangle(netHeight, netWidth, matrix, false, false);
    quad.SetColour(c);
    glAttachQuad3(GLV_InvisiblePlane, 1, &quad, true);

    netPlaneX = 1.0f + goalLineX;
    matrix.m[3][0] = netPlaneX;
    matrix.m[3][1] = 0.0f;
    matrix.m[3][2] = halfHeight;
    matrix.m[3][3] = 1.0f;
    quad.SetupRotatedRectangle(netHeight, netWidth, matrix, false, false);
    quad.SetColour(c);
    glAttachQuad3(GLV_InvisiblePlane, 1, &quad, true);

    netPlaneX = -goalLineX - 1.0f;
    matrix.m[3][0] = netPlaneX;
    matrix.m[3][1] = 0.0f;
    matrix.m[3][2] = halfHeight;
    matrix.m[3][3] = 1.0f;
    quad.SetupRotatedRectangle(netHeight, netWidth, matrix, false, false);
    quad.SetColour(c);
    glAttachQuad3(GLV_InvisiblePlane, 1, &quad, true);

    netPlaneX = 1.0f - goalLineX;
    matrix.m[3][0] = netPlaneX;
    matrix.m[3][1] = 0.0f;
    matrix.m[3][2] = halfHeight;
    matrix.m[3][3] = 1.0f;
    quad.SetupRotatedRectangle(netHeight, netWidth, matrix, false, false);
    quad.SetColour(c);
    glAttachQuad3(GLV_InvisiblePlane, 1, &quad, true);

    glSetDefaultState(false);
}

/**
 * Offset/Address/Size: 0x4B8 | 0x80114414 | size: 0x464
 */
void DrawableNetMesh::Render() const
{
}

/**
 * Offset/Address/Size: 0x2C0 | 0x8011421C | size: 0x1F8
 */
void DrawableNetMesh::Grab(NetMesh& netMesh)
{
    mpNetMesh = &netMesh;

    if (!netMesh.mbInitialized)
        return;

    if (!mbInitialized)
    {
        int numTriIdx = netMesh.m_NumTriStripIndices;
        mJolt = netMesh.m_NumParticles;
        m_unk18 = numTriIdx;

        int numVerts = mJolt;
        int numIndices = m_unk18;

        mpPosition = (nlVector3*)nlMalloc(numVerts * sizeof(nlVector3), 8, false);

        if (!sbStaticInitialized[miNetIndex])
        {
            spTriIndices[miNetIndex] = (unsigned short*)nlMalloc(numIndices * 2, 8, false);

            int allocSize = numVerts * 4;

            spTexcoord[miNetIndex] = (shortVector2*)nlMalloc(allocSize, 8, false);
            spColour[miNetIndex] = (unsigned long*)nlMalloc(allocSize, 8, false);

            memset(spColour[miNetIndex], 0xFF, allocSize);

            sbStaticInitialized[miNetIndex] = true;
            sNumVertices[miNetIndex] = numVerts;
        }

        mbInitialized = true;
        mJoltCache = 0.0f;
    }

    unsigned short* pTriIndices = spTriIndices[miNetIndex];
    shortVector2* pTexcoord = spTexcoord[miNetIndex];

    for (int i = 0; i < netMesh.m_NumTriStripIndices; i++)
    {
        *pTriIndices++ = netMesh.m_TriStripIndices[i];
    }

    {
        shortVector2* pDst = pTexcoord;
        for (int i = 0; i < netMesh.m_NumParticles; i++)
        {
            mpPosition[i] = netMesh.m_v3Position[i];
            *pDst++ = netMesh.m_v2TextureCoords[i];
        }
    }
}

/**
 * Offset/Address/Size: 0xAC | 0x80114008 | size: 0x214
 * TODO: 99.51% match - lhs m_unk18/mJolt load order remains swapped in init
 *       block, and first blend loop keeps r4/r5 swapped for offset vs src ptr.
 */
void DrawableNetMesh::Blend(float blendFactor, const DrawableNetMesh& lhs, const DrawableNetMesh& rhs)
{
    nlVector3* pDst;
    nlVector3* pSrc;

    if (!lhs.mbInitialized || !rhs.mbInitialized)
        return;

    if (!mbInitialized)
    {
        int numTriIdx = lhs.m_unk18;
        mJolt = lhs.mJolt;
        m_unk18 = numTriIdx;

        int numVerts = mJolt;
        int numIndices = m_unk18;

        mpPosition = (nlVector3*)nlMalloc(numVerts * sizeof(nlVector3), 8, false);

        if (!sbStaticInitialized[miNetIndex])
        {
            spTriIndices[miNetIndex] = (unsigned short*)nlMalloc(numIndices * 2, 8, false);

            int allocSize = numVerts * 4;

            spTexcoord[miNetIndex] = (shortVector2*)nlMalloc(allocSize, 8, false);
            spColour[miNetIndex] = (unsigned long*)nlMalloc(allocSize, 8, false);

            memset(spColour[miNetIndex], 0xFF, allocSize);

            sbStaticInitialized[miNetIndex] = true;
            sNumVertices[miNetIndex] = numVerts;
        }

        mbInitialized = true;
        mJoltCache = 0.0f;
    }

    float oneMinusBlend = 1.0f - blendFactor;

    for (int i = 0; i < mJolt; i++)
    {
        pSrc = &lhs.mpPosition[i];
        pDst = &mpPosition[i];
        float x = oneMinusBlend * pSrc->f.x;
        float y = pSrc->f.y;
        float z = pSrc->f.z;
        y = oneMinusBlend * y;
        z = oneMinusBlend * z;
        pDst->f.x = x;
        pDst->f.y = y;
        pDst->f.z = z;
    }

    for (int i = 0; i < mJolt; i++)
    {
        pDst = &mpPosition[i];
        pSrc = &rhs.mpPosition[i];
        float x = pDst->f.x + blendFactor * pSrc->f.x;
        float z = pDst->f.z + blendFactor * pSrc->f.z;
        float y = pDst->f.y + blendFactor * pSrc->f.y;
        pDst->f.x = x;
        pDst->f.y = y;
        pDst->f.z = z;
    }
}

/**
 * Offset/Address/Size: 0x38 | 0x80113F94 | size: 0x74
 */
void DrawableNetMesh::Replay(LoadFrame& frame)
{
    float joltValue = 0.0f;
    Replayable<0, LoadFrame, float>(frame, joltValue);

    if (joltValue != mJoltCache)
    {
        mJoltCache = joltValue;
        if (mpNetMesh != nullptr)
        {
            if (mJoltCache > 0.0f)
            {
                mpNetMesh->JoltNet(mJoltCache);
            }
        }
    }
}

/**
 * Offset/Address/Size: 0x0 | 0x80113F5C | size: 0x38
 */
void DrawableNetMesh::Replay(SaveFrame& frame)
{
    mJoltCache = mpNetMesh->mJolt;
    Replayable<0, SaveFrame, float>(frame, mJoltCache);
}

/**
 * Offset/Address/Size: 0x0 | 0x80114BCC | size: 0x44
 */
// void Replayable<0, LoadFrame, float>(LoadFrame&, float&)
// {
// }

/**
 * Offset/Address/Size: 0x44 | 0x80114C10 | size: 0x40
 */
// void Replayable<0, SaveFrame, float>(SaveFrame&, float&)
// {
// }
