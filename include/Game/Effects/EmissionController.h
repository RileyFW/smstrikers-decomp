#ifndef _EMISSIONCONTROLLER_H_
#define _EMISSIONCONTROLLER_H_

// void fxLoadEntireFileHigh(const char*, unsigned long*);
#include "NL/nlMath.h"
#include "NL/gl/gl.h"

#include "Game/PoseAccumulator.h"
#include "Game/Effects/EffectsGroup.h"
#include "Game/Effects/efList.h"
// #include "Game/Character.h"

class cPN_SAnimController;

enum Tag
{
    EMPTY = 0,
    FREE_FUNCTION = 1,
    FUNCTOR = 2,
};

template <typename ReturnType, typename ParamType>
class Function1
{
    // total size: 0x8
    enum Tag mTag; // offset 0x0, size 0x4
    union
    {                                           // inferred
        ReturnType (*mFreeFunction)(ParamType); // offset 0x4, size 0x4
        struct FunctorBase* mFunctor;           // offset 0x4, size 0x4
    };
};

void* fxLoadEntireFileHigh(const char* filename, unsigned long* fileSize);

class EmissionController : public efNode
{
public:
    EmissionController(EffectsGroup*, unsigned short, eGLView);
    void InitializeSystemsFromGroup();
    ~EmissionController();
    void SetPosition(const nlVector3&);
    void GetPosition() const;
    void SetDirection(const nlVector3&);
    void SetVelocity(const nlVector3&);
    void SetPoseAccumulator(const cPoseAccumulator&);
    void SetAnimController(const cPN_SAnimController&);
    void Die();
    void GetRemainingTime() const;
    void IsLingering() const;
    void Update(float);
    void Render();
    void SetUpdateCallback(const Function1<void, EmissionController&>&);
    void SetFinishedCallback(const Function1<void, EmissionController&>&);

    /* 0x8, */ EffectsGroup* m_pGroup;
    /* 0xC, */ efList m_Systems;
    /* 0x18 */ Function1<void, EmissionController&> mUpdateCallback;
    /* 0x20 */ Function1<void, EmissionController&> mFinishedCallback;
    /* 0x28 */ s8 m_GlView;
    /* 0x29 */ bool m_Replaying;
    /* 0x2C */ f32 m_Age;
    /* 0x30 */ f32 m_ReplayDeltaTime;
    /* 0x34 */ f32 m_fGround;
    /* 0x38 */ u16 m_aFacing;
    /* 0x3A */ bool m_bVisible;
    /* 0x3B */ bool m_bDisabled;
    /* 0x3C */ nlVector3 m_Mirror;
    /* 0x48 */ nlVector3 m_vPosition;
    /* 0x54 */ nlVector3 m_vDirection;
    /* 0x60 */ nlVector3 m_vVelocity;
    /* 0x6C */ const cPoseAccumulator* m_pPose;
    /* 0x70 */ const cPN_SAnimController* m_pAnimController;
    /* 0x74 */ u16 m_Id;
    /* 0x78 */ u32 m_uUserData;
    /* 0x7C */ u32 m_uJointIDOverride;
    /* 0x80 */ s32 m_nUserEffects;
    /* 0x84 */ UserEffectSpec** m_pUserEffects;
    /* 0x88 */ bool m_bPoseErrorDisplayed;
};

// class EmissionController
// {
// public:
//     // void SetFinishedCallback(const Function1<void, EmissionController&>&);
//     // void SetUpdateCallback(const Function1<void, EmissionController&>&);
//     void Render();
//     void Update(float);
//     void IsLingering() const;
//     void GetRemainingTime() const;
//     void Die();
//     void SetAnimController(const cPN_SAnimController&);
//     void SetPoseAccumulator(const cPoseAccumulator&);
//     void SetVelocity(const nlVector3&);
//     void SetDirection(const nlVector3&);
//     void GetPosition() const;
//     void SetPosition(const nlVector3&);
//     ~EmissionController();
//     void InitializeSystemsFromGroup();
//     EmissionController(EffectsGroup*, unsigned short, eGLView);

//     /* 0x00 */ u8 pad[0x34];
//     /* 0x34 */ float m_unk_0x34;
// };

#endif // _EMISSIONCONTROLLER_H_
