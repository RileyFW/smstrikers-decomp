#include "Game/Effects/ParticleSystem.h"
#include "Game/Sys/debug.h"
#include "NL/nlMemory.h"
#include "PowerPC_EABI_Support/Runtime/MWCPlusLib.h"
#include "types.h"

int ParticleSystem::m_nNumViews = 0;
int ParticleSystem::m_NumInstances = 0;
eGLView ParticleSystem::m_eViews[8];

efList freeParticles;

void* textureFrames[36] = { nullptr };
Particle* particleMemory;
int MaxNumParticles;

/**
 * Offset/Address/Size: 0x26F0 | 0x801F7848 | size: 0x90
 */
ParticleSystem::ParticleSystem(EffectsTemplate* pTemplate, EffectsSpec* pSpec)
{
    m_nextNode = nullptr;
    m_prevNode = nullptr;

    m_Particles.m_headNode = nullptr;
    m_Particles.m_tailNode = nullptr;
    m_Particles.m_numNodes = 0;

    m_NumInstances++;

    m_Mirror.f.x = 1.0f;
    m_Mirror.f.y = 1.0f;
    m_Mirror.f.z = 1.0f;

    m_pTemplate = pTemplate;
    m_pSpec = pSpec;

    m_fElapsedTime = 0.0f;
    m_fNumParticlesToCreate = 0.0f;
    m_fDelay = 0.0f;
    m_uLayer = 0;

    m_vVelocity.f.x = 0.0f;
    m_vVelocity.f.y = 0.0f;
    m_vVelocity.f.z = 0.0f;

    m_vPosition.f.x = 0.0f;
    m_vPosition.f.y = 0.0f;
    m_vPosition.f.z = 0.0f;

    m_vForward.f.x = 0.0f;
    m_vForward.f.y = 1.0f;
    m_vForward.f.z = 0.0f;

    m_vSourcePosition.f.x = 0.0f;
    m_vSourcePosition.f.y = 0.0f;
    m_vSourcePosition.f.z = 0.0f;

    m_aFacing = 0;
    m_bAmDying = false;
    m_bVisible = false;
}

/**
 * Offset/Address/Size: 0x2658 | 0x801F77B0 | size: 0x98
 */
ParticleSystem::~ParticleSystem()
{
    m_NumInstances = m_NumInstances - 1;
    if (m_Particles.m_headNode != nullptr)
    {
        while (m_Particles.m_headNode != nullptr)
        {
            freeParticles.Append(m_Particles.Remove());
        }
    }
}

/**
 * Offset/Address/Size: 0x264C | 0x801F77A4 | size: 0xC
 */
void ParticleSystem::ClearViews()
{
    m_nNumViews = 0;
}

/**
 * Offset/Address/Size: 0x262C | 0x801F7784 | size: 0x20
 */
void ParticleSystem::AddView(eGLView view)
{
    int numViews = m_nNumViews;
    m_nNumViews = numViews + 1;
    m_eViews[numViews] = view;
}

/**
 * Offset/Address/Size: 0x2628 | 0x801F7780 | size: 0x4
 */
void ParticleSystem::UpdateCoordSys()
{
}

/**
 * Offset/Address/Size: 0x2404 | 0x801F755C | size: 0x224
 * TODO: 89.9% match - post-nlRecipSqrt forward/mirror load ordering still differs
 * (target loads Y then X; current emits X then Y), cascading into register-allocation
 * differences in cross-product/normalization blocks.
 */
void ParticleSystem::UpdateCoordSys(nlMatrix4& mCoordSys)
{
    float rightX, rightY, rightZ;
    float gravY, gravX, gravZ;
    float negGravX;
    float upX;

    float rsqrt = nlRecipSqrt(
        m_vForward.f.x * m_vForward.f.x + m_vForward.f.y * m_vForward.f.y + m_vForward.f.z * m_vForward.f.z, true);

    gravY = rsqrt * m_vForward.f.y;
    gravX = rsqrt * m_vForward.f.x;
    gravZ = rsqrt * m_vForward.f.z;
    gravY *= m_Mirror.f.y;
    gravX *= m_Mirror.f.x;
    gravZ *= m_Mirror.f.z;

    float refX = 0.0f;
    float refZ = 1.0f;
    float refY = refX;

    float dot = refX * gravY + refX * gravX + refZ * gravZ;
    if ((float)__fabs(dot) > 0.999f)
    {
        refY = refZ;
        refZ = refX;
    }

    negGravX = -gravX;

    rightX = gravY * refZ - gravZ * refY;
    rightY = negGravX * refZ + gravZ * refX;
    rightZ = gravX * refY - gravY * refX;

    rsqrt = nlRecipSqrt(
        rightX * rightX + rightY * rightY + rightZ * rightZ, true);
    rightZ *= rsqrt;
    rightX = rsqrt * rightX;
    rightY *= rsqrt;

    float upY = rightZ * gravX - rightX * gravZ;
    upX = rightY * gravZ - rightZ * gravY;
    float upZ = rightX * gravY - rightY * gravX;

    rsqrt = nlRecipSqrt(
        upY * upY + upX * upX + upZ * upZ, true);

    mCoordSys.e[0] = rightX;
    mCoordSys.e[1] = rightY;
    mCoordSys.e[2] = rightZ;
    mCoordSys.e[4] = rsqrt * upX;
    mCoordSys.e[5] = rsqrt * upY;
    mCoordSys.e[6] = rsqrt * upZ;
    mCoordSys.e[8] = negGravX;
    mCoordSys.e[9] = -gravY;
    mCoordSys.e[10] = -gravZ;
    mCoordSys.e[12] = m_vPosition.f.x;
    mCoordSys.e[13] = m_vPosition.f.y;
    mCoordSys.e[14] = m_vPosition.f.z;
    mCoordSys.e[15] = 1.0f;
    mCoordSys.e[11] = 0.0f;
    mCoordSys.e[7] = 0.0f;
    mCoordSys.e[3] = 0.0f;
}

/**
 * Offset/Address/Size: 0x22F4 | 0x801F744C | size: 0x110
 */
void EmitCircularPosition(nlVector3& vPosition, nlVector3& vDirection, EffectsTemplate* pTemplate, EffectsSpec* pSpec, const nlMatrix4& mLocalToWorld)
{
    float randomAngle = RandomizedValue(0.0f, 6.2831855f);

    float sinVal;
    float cosVal;
    nlSinCos(&sinVal, &cosVal, (unsigned short)(int)(10430.378f * randomAngle));

    float radius = RandomizedValue(pTemplate->m_rRadius.base, pTemplate->m_rRadius.range);

    nlVector3 localPos;
    localPos.f.x = cosVal * radius;
    localPos.f.y = -sinVal * radius;
    localPos.f.z = 0.0f;

    if (pSpec != nullptr)
    {
        nlVec3Set(localPos,
            localPos.f.x + pSpec->m_vLocalOffset.f.x,
            localPos.f.y + pSpec->m_vLocalOffset.f.y,
            localPos.f.z + pSpec->m_vLocalOffset.f.z);
    }

    if (pTemplate->m_bLocalSpace)
    {
        vPosition = localPos;
    }
    else
    {
        nlMultPosVectorMatrix(vPosition, localPos, mLocalToWorld);
    }
}

/**
 * Offset/Address/Size: 0x2168 | 0x801F72C0 | size: 0x18C
 */
void EmitSphericalPosition(nlVector3& vPosition, nlVector3& vDirection, EffectsTemplate* pTemplate, EffectsSpec* pSpec, const nlMatrix4& mLocalToWorld)
{
    float randomZ = RandomizedValue(0.0f, 2.0f);
    float randomAngleValue = RandomizedValue(65536.0f);

    float xyRadius = nlSqrt(1.0f - (randomZ * randomZ), true);

    float sinVal;
    float cosVal;
    nlSinCos(&sinVal, &cosVal, (unsigned short)(int)(10430.378f * randomAngleValue));

    nlVector3 localPos;
    nlVector3 localDir;

    float x = xyRadius * cosVal;
    float y = xyRadius * sinVal;
    float z = randomZ;

    float radius = RandomizedValue(pTemplate->m_rRadius.base, pTemplate->m_rRadius.range);

    nlVec3Set(localDir, x, y, z);
    nlVec3Set(localPos, radius * localDir.f.x, radius * localDir.f.y, radius * localDir.f.z);

    if (pSpec != nullptr)
    {
        nlVec3Set(localPos,
            localPos.f.x + pSpec->m_vLocalOffset.f.x,
            localPos.f.y + pSpec->m_vLocalOffset.f.y,
            localPos.f.z + pSpec->m_vLocalOffset.f.z);
    }

    if (pTemplate->m_bLocalSpace)
    {
        vPosition = localPos;
        vDirection = localDir;
    }
    else
    {
        nlMultPosVectorMatrix(vPosition, localPos, mLocalToWorld);
        nlMultDirVectorMatrix(vDirection, localDir, mLocalToWorld);
    }
}

/**
 * Offset/Address/Size: 0x1FDC | 0x801F7134 | size: 0x18C
 */
void EmitHemisphericalPosition(nlVector3& vPosition, nlVector3& vDirection, EffectsTemplate* pTemplate, EffectsSpec* pSpec, const nlMatrix4& mLocalToWorld)
{
    float randomZ = RandomizedValue(-0.5f, 1.0f);
    float randomAngleValue = RandomizedValue(6.2831855f);

    float xyRadius = nlSqrt(1.0f - (randomZ * randomZ), true);

    float sinVal;
    float cosVal;
    nlSinCos(&sinVal, &cosVal, (unsigned short)(int)(10430.378f * randomAngleValue));

    nlVector3 localPos;
    nlVector3 localDir;

    float x = xyRadius * cosVal;
    float y = xyRadius * sinVal;
    float z = randomZ;

    float radius = RandomizedValue(pTemplate->m_rRadius.base, pTemplate->m_rRadius.range);

    nlVec3Set(localDir, x, y, z);
    nlVec3Set(localPos, radius * localDir.f.x, radius * localDir.f.y, radius * localDir.f.z);

    if (pSpec != nullptr)
    {
        nlVec3Set(localPos,
            localPos.f.x + pSpec->m_vLocalOffset.f.x,
            localPos.f.y + pSpec->m_vLocalOffset.f.y,
            localPos.f.z + pSpec->m_vLocalOffset.f.z);
    }

    if (pTemplate->m_bLocalSpace)
    {
        vPosition = localPos;
        vDirection = localDir;
    }
    else
    {
        nlMultPosVectorMatrix(vPosition, localPos, mLocalToWorld);
        nlMultDirVectorMatrix(vDirection, localDir, mLocalToWorld);
    }
}

/**
 * Offset/Address/Size: 0x1C90 | 0x801F6DE8 | size: 0x34C
 */
void EmitSpindularPosition(nlVector3& vPosition, nlVector3& vDirection, EffectsTemplate* pTemplate, EffectsSpec* pSpec, const nlMatrix4& mLocalToWorld)
{
    nlVector3 localDir;
    nlVector3 localPos;
    float sin;
    float cos;
    float randomAngle = RandomizedValue(0.0f, 6.2831855f);

    nlSinCos(&sin, &cos, (unsigned short)(int)(10430.378f * randomAngle));

    float radius = RandomizedValue(pTemplate->m_rRadius.base, pTemplate->m_rRadius.range);

    float x = cos * radius;
    float y = -sin * radius;
    float z = 0.0f;
    nlVec3Set(localDir, x, y, z);

    float tilt = RandomizedValue(pTemplate->m_rAngle.base, pTemplate->m_rAngle.range);
    if (tilt <= -1.0f)
    {
        tilt = -1.0f;
    }
    else if (tilt >= 1.0f)
    {
        tilt = 1.0f;
    }

    float tiltAngle = -tilt * 10430.378f;
    // float tanTilt = nlTan((unsigned short)(int)tiltAngle);

    nlVec3Set(localDir, localPos.f.x, localPos.f.y, nlTan((unsigned short)(int)tiltAngle));

    float length = nlRecipSqrt((localDir.f.x * localDir.f.x) + (localDir.f.y * localDir.f.y) + (localDir.f.z * localDir.f.z), false);

    nlVec3Set(localDir,
        length * localDir.f.x,
        length * localDir.f.y,
        length * localDir.f.z);

    float tiltRotation = RandomizedValue(pTemplate->m_rTilt.base, pTemplate->m_rTilt.range);

    if (tiltRotation != 0.0f)
    {
        nlSinCos(&sin, &cos, (unsigned short)(int)(10430.378f * tiltRotation));

        float dirX = localDir.f.x;
        float dirZ = localDir.f.z;
        float posX = localPos.f.x;
        float posZ = localPos.f.z;

        localDir.f.x = (dirX * sin) + (dirZ * cos);
        localDir.f.z = (-dirX * cos) + (dirZ * sin);

        localPos.f.x = (posX * sin) + (posZ * cos);
        localPos.f.z = (-posX * cos) + (posZ * sin);
    }

    if (pSpec != nullptr)
    {
        nlVec3Set(localPos,
            localPos.f.x + pSpec->m_vLocalOffset.f.x,
            localPos.f.y + pSpec->m_vLocalOffset.f.y,
            localPos.f.z + pSpec->m_vLocalOffset.f.z);
    }

    if (pTemplate->m_bLocalSpace)
    {
        vPosition = localPos;
        vDirection = localDir;
    }
    else
    {
        nlMultPosVectorMatrix(vPosition, localPos, mLocalToWorld);
        nlMultDirVectorMatrix(vDirection, localDir, mLocalToWorld);

        extern unsigned short hackyFacingAngle;
        if (hackyFacingAngle != 0)
        {
            nlSinCos(&sin, &cos, hackyFacingAngle);

            float dirX = vDirection.f.x;
            float dirY = vDirection.f.y;
            vDirection.f.x = (vDirection.f.x * cos) + (-dirY * sin);
            vDirection.f.y = (vDirection.f.x * sin) + (dirY * cos);

            float posX = vPosition.f.x;
            float posY = vPosition.f.y;
            vPosition.f.x = (posX * cos) + (-posY * sin);
            vPosition.f.y = (posX * sin) + (posY * cos);
        }

        vPosition.f.x += mLocalToWorld.m[0][3];
        vPosition.f.y += mLocalToWorld.m[1][3];
        vPosition.f.z += mLocalToWorld.m[2][3];
    }
}

/**
 * Offset/Address/Size: 0x1900 | 0x801F6A58 | size: 0x390
 */
void ParticleSystem::CreateNewParticles(int)
{
}

/**
 * Offset/Address/Size: 0x15AC | 0x801F6704 | size: 0x354
 */
void ParticleSystem::UpdateParticle(ParticleReturn*, Particle*, EffectsTemplate*, const nlVector3&, const nlVector3&, const nlMatrix4*)
{
}

/**
 * Offset/Address/Size: 0x970 | 0x801F5AC8 | size: 0xC3C
 */
void ParticleSystem::RenderAllParticles(eGLView)
{
}

/**
 * Offset/Address/Size: 0x954 | 0x801F5AAC | size: 0x1C
 */
void ParticleSystem::Die()
{
    m_fDelay = 0.0f;
    m_fElapsedTime = 100000000000000000000.0f;
    m_bAmDying = true;
}

/**
 * Offset/Address/Size: 0x6F4 | 0x801F584C | size: 0x260
 */
void ParticleSystem::Update(float)
{
}

/**
 * Offset/Address/Size: 0x6E0 | 0x801F5838 | size: 0x14
 */
float ParticleSystem::GetRemainingTime() const
{
    return m_pTemplate->m_fFountainLife - m_fElapsedTime;
}

/**
 * Offset/Address/Size: 0x188 | 0x801F52E0 | size: 0x558
 */
void BuildFrameTable()
{
    FORCE_DONT_INLINE;
}

// /**
//  * Offset/Address/Size: 0x178 | 0x801F52D0 | size: 0x10
//  */
// Particle::Particle()
// {
// }

static void ParticleConstructor(void* ptr, int)
{
    new (ptr) Particle();
}

/**
 * Offset/Address/Size: 0xAC | 0x801F5204 | size: 0xCC
 * TODO: 94.9% match - instruction scheduling diff at loop init: li r30/mr r29 ordering
 */
bool fxParticleStartup(int maxNumParticles)
{
    MaxNumParticles = maxNumParticles;
    BuildFrameTable();

    particleMemory = new (nlMalloc(MaxNumParticles * 0x4C + 0x10, 8, false)) Particle[MaxNumParticles];

    tDebugPrintManager::Print(DC_RENDER, "%dKB used by Particle pool\n", (unsigned)(MaxNumParticles * 0x4C) >> 10);

    int i = 0;
    int offset = i;
    for (; i < MaxNumParticles; offset += sizeof(Particle), i++)
    {
        freeParticles.Insert((efBaseNode*)((u8*)particleMemory + offset));
    }

    return true;
}

/**
 * Offset/Address/Size: 0x0 | 0x801F5158 | size: 0xAC
 */
bool fxParticleShutdown()
{
    for (int i = 0; i < 36; i++)
    {
        if (textureFrames[i] != nullptr)
        {
            delete[] (u8*)textureFrames[i];
            textureFrames[i] = nullptr;
        }
    }

    while (freeParticles.m_headNode != nullptr)
    {
        freeParticles.Remove();
    }

    if (particleMemory != nullptr)
    {
        if (particleMemory != nullptr)
        {
            delete[] ((u8*)particleMemory - 0x10);
        }
        particleMemory = nullptr;
    }
    return true;
}
