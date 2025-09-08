#ifndef _BALL_H_
#define _BALL_H_

#include <types.h>
#include "NL/nlMath.h"
#include "NL/nlTimer.h"

#include "Game/Player.h"

// Physics
#include "Game/Physics/PhysicsAIBall.h"
#include "Game/Physics/RayCollider.h"

// GFX
#include "Game/Drawable/DrawableObj.h"

// FX
#include "Game/ObjectBlur.h"

// void nlStrNCpy<char>(char*, const char*, unsigned long);
// void 0x8028D270..0x8028D274 | size: 0x4;

enum eSpinType
{
    eSpinType_0 = 0
};

enum eBallShotEffectType
{
    eBallShotEffectType_0 = 0
};

class cBall
{
public:
    float PredictLandingSpotAndTime(nlVector3&);
    void KillBlurHandler();
    void ClearPassTarget();
    void SetPassTargetTimer(float);
    void SetPassTarget(cPlayer*, const nlVector3&, bool);
    void WarpTo(const nlVector3&);
    void UpdateOrientation(float);
    void Update(float);
    void ShootAtFast(nlVector3&, const nlVector3&, float);
    void ShootRelease(const nlVector3&, eSpinType);
    void Shoot(const nlVector3&, const nlVector3&, eSpinType, bool, bool, bool);
    void SetVisible(bool);
    void SetVelocity(const nlVector3&, eSpinType, const nlVector3*);
    void SetPerfectPass(bool, bool);
    void SetPosition(const nlVector3&);
    void SetOwner(cPlayer*);
    bool IsBuzzerBeaterSet() const;
    void HandleBuzzerBeater(float);
    void ClearBallBlur();
    void ClearShotInProgress();
    void InitiateBallBlur(eBallShotEffectType, cPlayer*);
    void GetInNet(int&);
    cPlayer* GetPassTargetFielder() const;
    cPlayer* GetOwnerGoalie();
    cPlayer* GetOwnerFielder() const;
    nlVector3* GetDrawablePosition() const;
    nlVector3* GetAIVelocity() const;
    void PostPhysicsUpdate(float);
    void CollideWithWallCallback();
    void CollideWithGroundCallback();
    void CollideWithCharacterCallback(cPlayer*, const nlVector3&);
    void ClearBallEffects();
    void ClearOwner();

    ~cBall();
    cBall();

    /* 0x00 */ u32 m_bBallPathChangeCount;
    /* 0x04 */ u32 m_bBallDeflectCount;
    /* 0x08 */ Timer m_tShotTimer;
    /* 0x0C */ Timer m_tNoPickupTimer;
    /* 0x10 */ Timer m_tPassTargetTimer;
    /* 0x14 */ Timer m_tBuzzerBeaterTimer;
    /* 0x14 */ float m_fTotalPassTime;

    /* 0x18 */ BlurHandler* m_pBlurHandler;
    /* 0x1C */ DrawableObject* m_pDrawableBall;
    /* 0x20 */ cPlayer* m_pOwner;
    /* 0x24 */ cPlayer* m_pPrevOwner;
    /* 0x28 */ cPlayer* m_pLastTouch;
    /* 0x2C */ cPlayer* m_pPassTarget;
    /* 0x30 */ cPlayer* m_pShooter;
    /* 0x34 */ PhysicsAIBall* m_pPhysicsBall;
    /* 0x38 */ RayCollider* m_pBallPosCollider;
    /* 0x3C */ nlVector3 m_v3Position;
    /* 0x48 */ nlVector3 m_v3PrevPosition;
    /* 0x54 */ nlVector3 m_v3Velocity;
    /* 0x60 */ nlVector3 m_v3PassIntercept;
    /* 0x6C */ nlQuaternion m_qOrientation;
    /* 0x7C */ nlVector3 m_v3ShotTarget;
    /* 0x88 */ nlVector3 m_v3ShotOrigin;
    /* 0x94 */ u32 m_uGoalType;
    /* 0x98 */ u32 m_uVoiceID;
    /* 0x9C */ bool mbIsVolleyPass;
    /* 0x9D */ bool mbIsPerfectPass;
    /* 0x9E */ bool mbIsShootToScoreShot;
    /* 0x9F */ bool mbIsChipShot;
    /* 0xA0 */ bool mbIsPerfectShot;
    /* 0xA1 */ bool mbHyperSTS;
    /* 0xA2 */ bool mbCanDamage;
    /* 0xA4 */ cPlayer* mpDamageTarget;

    // /* 0x00 */ u32 m_unk_0x00;
    // /* 0x04 */ u32 m_unk_0x04;

    // /* 0x08 */ Timer* m_timer_0x08;
    // /* 0x0C */ Timer* m_timer_0x0C;
    // /* 0x10 */ Timer* m_passTargetTimer; // passTargetTimer
    // /* 0x14 */ Timer* m_timer_0x14;
    // /* 0x18 */ float m_passTimeSeconds; // m_unk_0x18;

    // /* 0x1C */ BlurHandler* m_blurHandler;

    // /* 0x20 */ DrawableObject* m_drawableObject;
    // /* 0x24 */ cPlayer* m_playerOwner;
    // /* 0x28 */ cPlayer* m_playerPrevOwner;
    // /* 0x2C */ u8 m_unk_0x2C[0x4];
    // /* 0x30 */ cPlayer* m_passTargetPlayer;
    // /* 0x34 */ u8 m_unk_0x34[0x4];
    // /* 0x38 */ PhysicsAIBall* m_aiBall;
    // /* 0x3C */ RayCollider* m_rayCollider;
    // /* 0x40 */ nlVector3 m_rayPosition;
    // /* 0x4C */ nlVector3 m_unk_0x4C;
    // /* 0x58 */ nlVector3 m_unk_0x58; // playerVelocity?
    // /* 0x64 */ nlVector3 m_unk_0x64; // passTargetPosition?
    // /* 0x70 */ u8 m_unk_0x70[0x32];
    // /* 0xA2 */ u8 m_unk_0xA2;
    // /* 0xA3 */ u8 m_unk_0xA3;
    // /* 0xA4 */ u8 m_unk_0xA4;
    // /* 0xA5 */ u8 m_unk_0xA5;
    // /* 0xA6 */ u8 m_unk_0xA6;
    // /* 0xA7 */ u8 m_unk_0xA7;
    // /* 0xA8 */ u8 m_unk_0xA8;
}; // total size: 0xA8

extern cBall* g_pBall;

// class BasicString<char, Detail
// {
// public:
//     void TempStringAllocator>::AppendInPlace(const char*);
//     void TempStringAllocator>::insert(char*, const char*, const char*);
//     void TempStringAllocator>::~BasicString();
// };

// class FuzzyVariant
// {
// public:
//     void Reset();
// };

// class Variant
// {
// public:
//     void Reset();
// };

// class PassBallData
// {
// public:
//     void GetID();
// };

// class EventData
// {
// public:
//     void GetID();
// };

#endif // _BALL_H_
