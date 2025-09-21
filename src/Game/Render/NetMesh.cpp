#include "Game/Render/NetMesh.h"

#include "Dolphin/types.h"
#include "NL/glx/glxTexture.h"
#include "NL/nlMemory.h"

unsigned long NetMesh::sNetTextureHandle = 0;
bool NetMesh::sbDontUseLowestNetTextureLOD = false;
bool NetMesh::s_bAnimatedNetMeshEnabled = false;
NetMesh* NetMesh::spPositiveXNetMesh = nullptr;
NetMesh* NetMesh::spNegativeXNetMesh = nullptr;

extern f32 g_fFixedUpdateTick;

static nlVector3 v3Zero = { 0.0f, 0.0f, 0.0f };

/**
 * Offset/Address/Size: 0x1178 | 0x8012FF98 | size: 0x84
 */
NetMesh::NetMesh(bool positiveEnd)
{
    mbInitialized = false;
    mbFirstUpdate = true;
    m_v3Position = NULL;
    m_v3PrevPosition = NULL;
    m_v3Accel = NULL;
    m_TriStripIndices = NULL;
    m_v2TextureCoords = NULL;
    m_v3Normal = NULL;
    mNetMeshDrawableObjectID = 0;
    mbPositiveEnd = positiveEnd;
    m_NumParticles = 0;
    m_fBallPenetrationDepth = 0.0f;
    mfMinX = 0.0f;
    mfMaxX = 0.0f;
    mfMinY = 0.0f;
    mfMaxY = 0.0f;
    m_NumPositionConstraints = 0;
    m_NumDistanceConstraints = 0;
    mbIsActive = true;
    mbBallIsInsideNet = false;
    mfMotion = 0.0f;
    m_aDistanceConstraints = NULL;
    m_aPositionConstraints = NULL;

    if (positiveEnd != 0)
    {
        spPositiveXNetMesh = this;
    }
    if (positiveEnd == 0)
    {
        spNegativeXNetMesh = this;
    }
}

/**
 * Offset/Address/Size: 0xFE8 | 0x8012FE08 | size: 0x190
 */
#pragma push
// #pragma optimization_level 1
// #pragma optimize_for_size on
void NetMesh::Allocate(int numParticles, int numDistanceConstraints, int numPositionConstraints)
{
    m_v3Position = (nlVector3*)nlMalloc(numParticles * sizeof(nlVector3), 8, false);
    m_v3PrevPosition = (nlVector3*)nlMalloc(numParticles * sizeof(nlVector3), 8, false);
    m_v3Accel = (nlVector3*)nlMalloc(numParticles * sizeof(nlVector3), 8, false);
    m_v3Normal = (nlVector3*)nlMalloc(numParticles * sizeof(nlVector3), 8, false);
    m_v2TextureCoords = (shortVector2*)nlMalloc(numParticles * sizeof(shortVector2), 8, false);
    m_bIsParticleFixed = (bool*)nlMalloc(numParticles, 8, false);
    m_aDistanceConstraints = (cDistanceConstraint*)nlMalloc(numDistanceConstraints * sizeof(cDistanceConstraint), 8, false);
    m_aPositionConstraints = (cPositionConstraint*)nlMalloc(numPositionConstraints * sizeof(cPositionConstraint), 8, false);

    if (numParticles > 0)
    {
        int i = 0;
        int numParticlesMinus8 = numParticles - 8;
        if (numParticles > 8)
        {
            if (numParticlesMinus8 > 0)
            {
                for (; i < numParticlesMinus8; i += 8)
                {
                    m_bIsParticleFixed[i] = false;
                    m_bIsParticleFixed[i + 1] = false;
                    m_bIsParticleFixed[i + 2] = false;
                    m_bIsParticleFixed[i + 3] = false;
                    m_bIsParticleFixed[i + 4] = false;
                    m_bIsParticleFixed[i + 5] = false;
                    m_bIsParticleFixed[i + 6] = false;
                    m_bIsParticleFixed[i + 7] = false;
                }
            }
        }

        if (i < numParticles)
        {
            for (; i < numParticles; i++)
            {
                m_bIsParticleFixed[i] = false;
            }
        }
    }
}
#pragma pop

/**
 * Offset/Address/Size: 0xF54 | 0x8012FD74 | size: 0x94
 */
NetMesh::~NetMesh()
{
    delete[] m_v3Position;
    delete[] m_v3PrevPosition;
    delete[] m_v3Accel;
    delete[] m_v3Normal;
    delete[] m_v2TextureCoords;
    delete[] m_TriStripIndices;
    delete[] m_aDistanceConstraints;
    delete[] m_aPositionConstraints;
    delete[] m_bIsParticleFixed;
}

/**
 * Offset/Address/Size: 0xEF4 | 0x8012FD14 | size: 0x60
 */
int NetMesh::SetPositionConstraint(int particleIndex, const nlVector3& v3Position)
{
    m_aPositionConstraints[m_NumPositionConstraints].nParticle = particleIndex;
    m_aPositionConstraints[m_NumPositionConstraints].v3Position = v3Position;
    m_NumPositionConstraints += 1;
    m_bIsParticleFixed[particleIndex] = true;
    return m_NumPositionConstraints - 1;
}

/**
 * Offset/Address/Size: 0xEAC | 0x8012FCCC | size: 0x48
 */
void NetMesh::SetDistanceConstraint(int nParticleA, int nParticleB, float fDistance)
{
    m_aDistanceConstraints[m_NumDistanceConstraints].nParticleA = nParticleA;
    m_aDistanceConstraints[m_NumDistanceConstraints].nParticleB = nParticleB;
    m_aDistanceConstraints[m_NumDistanceConstraints].fDistance = fDistance;
    m_NumDistanceConstraints += 1;
}

/**
 * Offset/Address/Size: 0xE40 | 0x8012FC60 | size: 0x6C
 */
void NetMesh::UpdateUntilRelaxed()
{
    mbIsActive = true;
    while (mbIsActive)
    {
        Update(g_fFixedUpdateTick, v3Zero, v3Zero, false, nullptr);
    }
    // loop_2:
    //     if (this->unk70 != 0)
    //     {
    //         Update__7NetMeshFfRC9nlVector3RC9nlVector3bP13PhysicsSphere(this, g_fFixedUpdateTick, &v3Zero, &v3Zero, 0, NULL);
    //         goto loop_2;
    //     }
}

/**
 * Offset/Address/Size: 0xAA8 | 0x8012F8C8 | size: 0x398
 */
void NetMesh::Update(float, const nlVector3&, const nlVector3&, bool, PhysicsSphere*)
{
    FORCE_DONT_INLINE;
}

/**
 * Offset/Address/Size: 0xA60 | 0x8012F880 | size: 0x48
 */
void NetMesh::JoltNet(float zDisplacement)
{
    mJolt = zDisplacement;
    for (s32 i = 0; i < m_NumParticles; i++)
    {
        m_v3Position[i].f.z += zDisplacement;
    }

    mbIsActive = true;
    mbFirstUpdate = true;
}

/**
 * Offset/Address/Size: 0x550 | 0x8012F370 | size: 0x510
 */
void NetMesh::SatisfyConstraints(const nlVector3&, bool)
{
}

/**
 * Offset/Address/Size: 0x220 | 0x8012F040 | size: 0x330
 */
void NetMesh::AddForcesToBall(const nlVector3&, PhysicsSphere*)
{
}

/**
 * Offset/Address/Size: 0xBC | 0x8012EEDC | size: 0x164
 */
void NetMesh::Initialize(unsigned long)
{
}

/**
 * Offset/Address/Size: 0x54 | 0x8012EE74 | size: 0x68
 */
void NetMesh::SetTriStripIndices(int numIndices, const unsigned short* indices)
{
    m_NumTriStripIndices = numIndices;
    m_TriStripIndices = (u16*)nlMalloc(numIndices * 2, 8, false);
    memcpy(m_TriStripIndices, indices, numIndices * 2);
}

/**
 * Offset/Address/Size: 0x4C | 0x8012EE6C | size: 0x8
 */
void NetMesh::SetDontUseLowestNetTextureLOD(bool value)
{
    sbDontUseLowestNetTextureLOD = value;
}

/**
 * Offset/Address/Size: 0x0 | 0x8012EE20 | size: 0x4C
 */
void NetMesh::SetTexture(unsigned long texture)
{
    sNetTextureHandle = texture;
    if (sbDontUseLowestNetTextureLOD != 0)
    {
        PlatTexture* tex = glx_GetTex(texture, true, true);
        tex->m_unk9 = tex->m_unk8 - 1;
        tex->Prepare();
    }
}
