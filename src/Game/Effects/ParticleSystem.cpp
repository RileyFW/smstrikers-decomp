#include "Game/Effects/ParticleSystem.h"

// /**
//  * Offset/Address/Size: 0x2780 | 0x801F78D8 | size: 0x18
//  */
// void 0x8028D560..0x8028D564 | size: 0x4
// {
// }

/**
 * Offset/Address/Size: 0x26F0 | 0x801F7848 | size: 0x90
 */
ParticleSystem::ParticleSystem(EffectsTemplate*, EffectsSpec*)
{
}

/**
 * Offset/Address/Size: 0x2658 | 0x801F77B0 | size: 0x98
 */
ParticleSystem::~ParticleSystem()
{
}

/**
 * Offset/Address/Size: 0x264C | 0x801F77A4 | size: 0xC
 */
void ParticleSystem::ClearViews()
{
}

/**
 * Offset/Address/Size: 0x262C | 0x801F7784 | size: 0x20
 */
void ParticleSystem::AddView(eGLView)
{
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
void ParticleSystem::GetRemainingTime() const
{
}

/**
 * Offset/Address/Size: 0x188 | 0x801F52E0 | size: 0x558
 */
void BuildFrameTable()
{
}

/**
 * Offset/Address/Size: 0x178 | 0x801F52D0 | size: 0x10
 */
Particle::Particle()
{
}

/**
 * Offset/Address/Size: 0xAC | 0x801F5204 | size: 0xCC
 */
void fxParticleStartup(int)
{
}

/**
 * Offset/Address/Size: 0x0 | 0x801F5158 | size: 0xAC
 */
void fxParticleShutdown()
{
}
