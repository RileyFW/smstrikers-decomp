#ifndef _PARTICLESYSTEM_H_
#define _PARTICLESYSTEM_H_

// void 0x8028D560..0x8028D564 | size: 0x4;

#include "NL/nlMath.h"
#include "NL/nlColour.h"
#include "Game/Effects/efList.h"
#include "Game/Effects/EffectsTemplate.h"
#include "Game/Effects/EffectsGroup.h"
#include "NL/gl/gl.h"

struct ParticleReturn
{
    /* 0x00 */ s16 texcoord[4][2];
    /* 0x10 */ nlVector3 position[4];
    /* 0x40 */ nlColour c;
}; // size: 0x44

class Particle : public efNode
{
public:
    Particle();

public:
    /* 0x8, */ f32 timeElapsed;
    /* 0xC, */ f32 lifeSpan;
    /* 0x10 */ nlVector3 position;
    /* 0x1C */ nlVector3 velDir;
    /* 0x28 */ f32 mass;
    /* 0x2C */ f32 size;
    /* 0x30 */ f32 dSize;
    /* 0x34 */ f32 rot;
    /* 0x38 */ f32 dRot;
    /* 0x3C */ f32 velocity;
    /* 0x40 */ f32 acceleration;
    /* 0x44 */ f32 frame;
    /* 0x48 */ f32 FPS;
};

class ParticleSystem
{
public:
    ParticleSystem(EffectsTemplate*, EffectsSpec*);
    ~ParticleSystem();
    void ClearViews();
    void AddView(eGLView);
    void UpdateCoordSys();
    void UpdateCoordSys(nlMatrix4&);
    void CreateNewParticles(int);
    void UpdateParticle(ParticleReturn*, Particle*, EffectsTemplate*, const nlVector3&, const nlVector3&, const nlMatrix4*);
    void RenderAllParticles(eGLView);
    void Die();
    void Update(float);
    float GetRemainingTime() const;
};

void fxParticleShutdown();
void fxParticleStartup(int);
void BuildFrameTable();
void EmitSpindularPosition(nlVector3&, nlVector3&, EffectsTemplate*, EffectsSpec*, const nlMatrix4&);
void EmitHemisphericalPosition(nlVector3&, nlVector3&, EffectsTemplate*, EffectsSpec*, const nlMatrix4&);
void EmitSphericalPosition(nlVector3&, nlVector3&, EffectsTemplate*, EffectsSpec*, const nlMatrix4&);
void EmitCircularPosition(nlVector3&, nlVector3&, EffectsTemplate*, EffectsSpec*, const nlMatrix4&);

#endif // _PARTICLESYSTEM_H_
