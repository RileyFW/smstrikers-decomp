#include "Game/Drawable/DrawableNetMesh.h"
#include "Game/Replay.h"
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
 */
void DrawableNetMesh::RenderInvisiblePlanes() const
{
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
 */
void DrawableNetMesh::Blend(float, const DrawableNetMesh&, const DrawableNetMesh&)
{
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
