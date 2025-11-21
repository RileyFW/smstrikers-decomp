#include "Game/Effects/ParticleSystem.h"
#include "Game/Sys/debug.h"
#include "NL/nlMemory.h"
#include "PowerPC_EABI_Support/Runtime/MWCPlusLib.h"
#include "types.h"

int ParticleSystem::m_nNumViews = 0;
int ParticleSystem::m_NumInstances = 0;
eGLView ParticleSystem::m_eViews[8];

efList freeParticles;

void* textureFrames[36];
Particle* particleMemory;
unsigned int MaxNumParticles;

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
 */
void ParticleSystem::UpdateCoordSys(nlMatrix4&)
{
}

/**
 * Offset/Address/Size: 0x22F4 | 0x801F744C | size: 0x110
 */
void EmitCircularPosition(nlVector3&, nlVector3&, EffectsTemplate*, EffectsSpec*, const nlMatrix4&)
{
}

/**
 * Offset/Address/Size: 0x2168 | 0x801F72C0 | size: 0x18C
 */
void EmitSphericalPosition(nlVector3&, nlVector3&, EffectsTemplate*, EffectsSpec*, const nlMatrix4&)
{
}

/**
 * Offset/Address/Size: 0x1FDC | 0x801F7134 | size: 0x18C
 */
void EmitHemisphericalPosition(nlVector3&, nlVector3&, EffectsTemplate*, EffectsSpec*, const nlMatrix4&)
{
}

/**
 * Offset/Address/Size: 0x1C90 | 0x801F6DE8 | size: 0x34C
 */
void EmitSpindularPosition(nlVector3&, nlVector3&, EffectsTemplate*, EffectsSpec*, const nlMatrix4&)
{
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
 */
bool fxParticleStartup(int maxNumParticles)
{
    MaxNumParticles = maxNumParticles;
    BuildFrameTable();

    particleMemory = new (nlMalloc(MaxNumParticles * 0x4C + 0x10, 8, false)) Particle[MaxNumParticles];

    tDebugPrintManager::Print(DC_RENDER, "%dKB used by Particle pool\n", (MaxNumParticles * 0x4C) >> 10);

    Particle* p;
    for (int i = 0; i < MaxNumParticles; i++)
    {
        // efList& particles = freeParticles;
        p = &particleMemory[i];
        freeParticles.Insert(p);
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
