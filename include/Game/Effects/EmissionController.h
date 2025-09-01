#ifndef _EMISSIONCONTROLLER_H_
#define _EMISSIONCONTROLLER_H_

// void fxLoadEntireFileHigh(const char*, unsigned long*);
#include "NL/nlMath.h"
#include "NL/gl/gl.h"

class cPN_SAnimController;
class cPoseAccumulator;
class EffectsGroup;

class EmissionController
{
public:
    // void SetFinishedCallback(const Function1<void, EmissionController&>&);
    // void SetUpdateCallback(const Function1<void, EmissionController&>&);
    void Render();
    void Update(float);
    void IsLingering() const;
    void GetRemainingTime() const;
    void Die();
    void SetAnimController(const cPN_SAnimController&);
    void SetPoseAccumulator(const cPoseAccumulator&);
    void SetVelocity(const nlVector3&);
    void SetDirection(const nlVector3&);
    void GetPosition() const;
    void SetPosition(const nlVector3&);
    ~EmissionController();
    void InitializeSystemsFromGroup();
    EmissionController(EffectsGroup*, unsigned short, eGLView);

    /* 0x00 */ u8 pad[0x34];
    /* 0x34 */ float m_unk_0x34;
};

#endif // _EMISSIONCONTROLLER_H_
