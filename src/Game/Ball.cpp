#include "Game/WorldManager.h"
#include "NL/platqmath.h"
#pragma pool_data off

#include "Game/Ball.h"

#include "NL/nlDebug.h"
#include "NL/nlMath.h"
#include "NL/nlMemory.h"

#include "Game/Goalie.h"

#include "Game/Physics/PhysicsAIBall.h"
#include "Game/Physics/PhysicsObject.h"
#include "Game/Physics/RayCollider.h"
#include "Game/Physics/PhysicsFakeBall.h"

#include "Game/FixedUpdateTask.h"
#include "Game/ParticleUpdateTask.h"

#include "Game/Audio/AudioLoader.h"
#include "Game/Audio/WorldAudio.h"

extern float gfPerfectPassSFXVol;
extern bool gbCanFadeOutPerfectPassSFX;

cBall* g_pBall = NULL;

nlMatrix3 m3Ident = { 1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f };
// nlMatrix4 m4Ident = { 1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f };

/**
 * Offset/Address/Size: 0x0 | 0x800099D4 | size: 0x10C
 */
float cBall::PredictLandingSpotAndTime(nlVector3& landingSpot)
{
    float sp10;
    float spC;
    int sp8;
    float dVar9;
    float fVar5;
    float pfVar7;
    float dVar8;
    float dVar10;

    // m_unk_0x58.x = 0;
    // m_unk_0x58.y = 0;
    // m_unk_0x58.z = 0;

    dVar8 = 0.1f;
    if (m_v3Velocity.f.z > 1.0f)
    {
        SolveQuadratic(dVar8, 0.5f * m_pPhysicsBall->m_gravity, m_v3Velocity.f.z, sp8, spC, sp10);

        pfVar7 = spC;         // pfVar7 = &local_14;
        dVar8 = 100000000.0f; // dVar8 = (double)Ball::@1409;
        fVar5 = 0.f;
        dVar10 = dVar8;
        if (sp8 > 0)
        {
            do
            {
                dVar9 = pfVar7;
                dVar8 = dVar10;
                if ((0.f <= dVar9) && (dVar8 = dVar9, dVar10 <= dVar9))
                {
                    dVar8 = dVar10;
                }
                pfVar7 = pfVar7 + 1;
                sp8 -= 1;
                dVar10 = dVar8;
            } while (sp8 != 0);
        }

        landingSpot.f.x = (dVar8 * m_v3Velocity.f.x) + m_v3Position.f.x;
        landingSpot.f.y = (dVar8 * m_v3Velocity.f.y) + m_v3Position.f.y;
        // landingSpot.z = (dVar8 * m_unk_0x58.z) + m_v3Position.z;
        landingSpot.f.z = 0.f;
        return dVar8;
    }

    landingSpot = m_v3Position;

    return 0.f;
}

/**
 * Offset/Address/Size: 0x10C | 0x80009AE0 | size: 0x44
 */
void cBall::KillBlurHandler()
{
    if (m_pBlurHandler != NULL)
    {
        m_pBlurHandler->Die(0.f);
        m_pBlurHandler = NULL;
    }
}

/**
 * Offset/Address/Size: 0x150 | 0x80009B24 | size: 0x1EC
 */
void cBall::ClearPassTarget()
{
    if (mbHyperSTS)
    {
        Audio::gWorldSFX.Stop(Audio::eWorldSFX(0x57), cGameSFX::SFX_STOP_FIRST);
    }
    Audio::FadeFilterFromCurrentToZero();

    FixedUpdateTask::mTimeScale = 1.0f;
    ParticleUpdateTask::SetTimeScale(1.0f);

    if (m_pBlurHandler != 0)
    {
        m_pBlurHandler->Die(0.5f);
        m_pBlurHandler = 0;
    }

    KillBallShot("ball_shot_perfect_glow", true);
    KillBallShot("ball_pass_perfect_glow", true);
    KillBallShot("shoot_to_score_shot", false);
    KillBallShot("ball_shot_onetimer", false);

    Audio::gStadGenSFX.Stop(Audio::eWorldSFX(0xB9), cGameSFX::SFX_STOP_FIRST);
    Audio::gStadGenSFX.Stop(Audio::eWorldSFX(0xBA), cGameSFX::SFX_STOP_FIRST);
    Audio::gStadGenSFX.Stop(Audio::eWorldSFX(0xBD), cGameSFX::SFX_STOP_FIRST);

    if (mbHyperSTS)
    {
        void* data = (u8*)g_pEventManager->CreateValidEvent(0x47, 0x24) + 0x10;
        PassBallData* eventdata = new (data) PassBallData();
        eventdata->pPasser = m_pPrevOwner;
        eventdata->pTarget = NULL;

        bool pad = eventdata->pPasser->GetGlobalPad();
        eventdata->mPasserControllerID = pad ? eventdata->pPasser->GetGlobalPad()->m_padIndex : -1;
    }

    mbHyperSTS = false;
    mbIsPerfectShot = false;

    gbCanFadeOutPerfectPassSFX = true;

    if (AudioLoader::IsInited())
    {
        gfPerfectPassSFXVol = Audio::gStadGenSFX.GetSFXVol(0xBA);
    }

    if (m_pPassTarget)
    {
        m_pPassTarget = NULL;
    }

    m_v3PassIntercept.f.x = 0.f;
    m_v3PassIntercept.f.y = 0.f;
    m_v3PassIntercept.f.z = 0.f;

    m_tPassTargetTimer.m_uPackedTime = 0;

    if (m_uVoiceID)
    {
        Audio::StopSFX(m_uVoiceID);
        m_uVoiceID = 0;
    }
}

/**
 * Offset/Address/Size: 0x33C | 0x80009D10 | size: 0x40
 */
void cBall::SetPassTargetTimer(float seconds)
{
    m_tPassTargetTimer.SetSeconds(seconds);
    m_fTotalPassTime = seconds;
}

/**
 * Offset/Address/Size: 0x37C | 0x80009D50 | size: 0x20
 */
void cBall::SetPassTarget(cPlayer* passTargetPlayer, const nlVector3& pos, bool)
{
    m_pPassTarget = passTargetPlayer;
    m_v3PassIntercept = pos;
}

/**
 * Offset/Address/Size: 0x39C | 0x80009D70 | size: 0x90
 */
void cBall::WarpTo(const nlVector3& toPos)
{
    m_v3Position = toPos;
    m_pPhysicsBall->SetPosition(toPos, PhysicsObject::WORLD_COORDINATES);
    m_pPhysicsBall->SetRotation(m3Ident);
    FakeBallWorld::InvalidateBallCache();
    m_bBallPathChangeCount = m_bBallPathChangeCount + 1;
    m_v3PrevPosition = toPos;
}

/**
 * Offset/Address/Size: 0x42C | 0x80009E00 | size: 0x30C
 */
void cBall::UpdateOrientation(float)
{
}

/**
 * Offset/Address/Size: 0x738 | 0x8000A10C | size: 0x308
 */
void cBall::Update(float)
{
}

/**
 * Offset/Address/Size: 0xA40 | 0x8000A414 | size: 0x100
 */
void cBall::ShootAtFast(nlVector3&, const nlVector3&, float)
{
}

/**
 * Offset/Address/Size: 0xB40 | 0x8000A514 | size: 0x1EC
 */
void cBall::ShootRelease(const nlVector3&, eSpinType)
{
}

/**
 * Offset/Address/Size: 0xD2C | 0x8000A700 | size: 0x3AC
 */
void cBall::Shoot(const nlVector3&, const nlVector3&, eSpinType, bool, bool, bool)
{
}

/**
 * Offset/Address/Size: 0x10D8 | 0x8000AAAC | size: 0x2C
 */
void cBall::SetVisible(bool visible)
{
    DrawableObject* drawable = m_pDrawableBall;
    if (visible != 0)
    {
        drawable->m_uObjectFlags = (drawable->m_uObjectFlags | 1);
        return;
    }
    drawable->m_uObjectFlags = (drawable->m_uObjectFlags & 0xFFFFFFFE);
}

/**
 * Offset/Address/Size: 0x1104 | 0x8000AAD8 | size: 0x1D4
 */
void cBall::SetVelocity(const nlVector3&, eSpinType, const nlVector3*)
{
}

/**
 * Offset/Address/Size: 0x12D8 | 0x8000ACAC | size: 0xF0
 */
void cBall::SetPerfectPass(bool bFlag, bool bNoEvent)
{
    PassBallData* eventdata;

    if ((mbHyperSTS != bFlag) && !bNoEvent)
    {
        void* data = (u8*)g_pEventManager->CreateValidEvent(bFlag ? 0x45 : 0x47, 0x24) + 0x10;
        eventdata = new (data) PassBallData();

        if (bFlag)
        {
            eventdata->pPasser = m_pPrevOwner;
            eventdata->pTarget = m_pPassTarget;
        }
        else
        {
            eventdata->pPasser = m_pPrevOwner;
            eventdata->pTarget = NULL;
        }

        bool pad = eventdata->pPasser->GetGlobalPad();
        eventdata->mPasserControllerID = (pad != NULL) ? eventdata->pPasser->GetGlobalPad()->m_padIndex : -1;
    }

    mbHyperSTS = bFlag;
}

/**
 * Offset/Address/Size: 0x13C8 | 0x8000AD9C | size: 0x6C
 */
void cBall::SetPosition(const nlVector3& pos)
{
    m_v3Position = pos;
    m_pPhysicsBall->SetPosition(pos, PhysicsObject::WORLD_COORDINATES);
    m_pPhysicsBall->SetRotation(m3Ident);
    FakeBallWorld::InvalidateBallCache();
    m_bBallPathChangeCount++;
}

/**
 * Offset/Address/Size: 0x1434 | 0x8000AE08 | size: 0x230
 */
void cBall::SetOwner(cPlayer*)
{
}

/**
 * Offset/Address/Size: 0x1664 | 0x8000B038 | size: 0x50
 */
bool cBall::IsBuzzerBeaterSet() const
{

    bool res = false;
    if (m_tBuzzerBeaterTimer.m_uPackedTime != 0)
    {
        return true;
    }

    if (g_pBall->m_tShotTimer.m_uPackedTime != 0)
    {
        return true;
    }

    if ((Goalie::mbPosGoalieNetCheck != 0) || (Goalie::mbNegGoalieNetCheck != 0))
    {
        res = true;
    }

    return res;
}

/**
 * Offset/Address/Size: 0x16B4 | 0x8000B088 | size: 0x48
 */
void cBall::HandleBuzzerBeater(float seconds)
{
    if (seconds < 0.0f)
    {
        m_tBuzzerBeaterTimer.m_uPackedTime = 0;
        return;
    }
    if (m_tBuzzerBeaterTimer.m_uPackedTime == 0)
    {
        m_tBuzzerBeaterTimer.SetSeconds(seconds);
    }
}

/**
 * Offset/Address/Size: 0x16FC | 0x8000B0D0 | size: 0x44
 */
void cBall::ClearBallBlur()
{
    if (m_pBlurHandler != NULL)
    {
        m_pBlurHandler->Die(0.5f);
        m_pBlurHandler = NULL;
    }
}

/**
 * Offset/Address/Size: 0x1740 | 0x8000B114 | size: 0x20C
 */
void cBall::ClearShotInProgress()
{
}

/**
 * Offset/Address/Size: 0x194C | 0x8000B320 | size: 0x370
 */
void cBall::InitiateBallBlur(eBallShotEffectType, cPlayer*)
{
}

/**
 * Offset/Address/Size: 0x1CBC | 0x8000B690 | size: 0xF4
 */
void cBall::GetInNet(int&)
{
}

/**
 * Offset/Address/Size: 0x1DB0 | 0x8000B784 | size: 0x20
 */
cPlayer* cBall::GetPassTargetFielder() const
{
    cPlayer* player = m_pPassTarget;
    if ((player == NULL) || (player->m_eClassType != FIELDER))
    {
        return NULL;
    }
    return player;
}

/**
 * Offset/Address/Size: 0x1DD0 | 0x8000B7A4 | size: 0x20
 */
cPlayer* cBall::GetOwnerGoalie()
{
    cPlayer* player = m_pOwner;
    if ((player == NULL) || (player->m_eClassType != GOALIE))
    {
        return NULL;
    }
    return player;
}

/**
 * Offset/Address/Size: 0x1DF0 | 0x8000B7C4 | size: 0x20
 */
cFielder* cBall::GetOwnerFielder()
{
    cPlayer* player = m_pOwner;
    if ((player == NULL) || (player->m_eClassType != FIELDER))
    {
        return NULL;
    }
    return (cFielder*)player;
}

/**
 * Offset/Address/Size: 0x1E10 | 0x8000B7E4 | size: 0x28
 */
nlVector3* cBall::GetDrawablePosition() const
{
    nlMatrix4 mtx = m_pDrawableBall->GetWorldMatrix();
    return (nlVector3*)&(mtx.m[3][0]);
}

/**
 * Offset/Address/Size: 0x1E38 | 0x8000B80C | size: 0x1C
 */
nlVector3* cBall::GetAIVelocity() const
{
    cPlayer* temp_r4 = m_pOwner;
    if (temp_r4 != NULL)
    {
        return &(temp_r4->m_v3Velocity);
    }
    return (nlVector3*)&(m_v3Velocity);
}

/**
 * Offset/Address/Size: 0x1E54 | 0x8000B828 | size: 0x400
 */
void cBall::PostPhysicsUpdate(float)
{
}

/**
 * Offset/Address/Size: 0x2254 | 0x8000BC28 | size: 0x5BC
 */
void cBall::CollideWithWallCallback()
{
}

/**
 * Offset/Address/Size: 0x2810 | 0x8000C1E4 | size: 0x3C4
 */
void cBall::CollideWithGroundCallback()
{
}

/**
 * Offset/Address/Size: 0x2BD4 | 0x8000C5A8 | size: 0xA18
 */
void cBall::CollideWithCharacterCallback(cPlayer*, const nlVector3&)
{
}

/**
 * Offset/Address/Size: 0x35EC | 0x8000CFC0 | size: 0x1A8
 */
void cBall::ClearBallEffects()
{
    if (mbHyperSTS)
    {
        Audio::gWorldSFX.Stop(Audio::eWorldSFX(0x57), cGameSFX::SFX_STOP_FIRST);
    }
    Audio::FadeFilterFromCurrentToZero();

    FixedUpdateTask::mTimeScale = 1.0f;
    ParticleUpdateTask::SetTimeScale(1.0f);

    if (m_pBlurHandler != 0)
    {
        m_pBlurHandler->Die(0.5f);
        m_pBlurHandler = 0;
    }

    KillBallShot("ball_shot_perfect_glow", true);
    KillBallShot("ball_pass_perfect_glow", true);
    KillBallShot("shoot_to_score_shot", false);
    KillBallShot("ball_shot_onetimer", false);

    Audio::gStadGenSFX.Stop(Audio::eWorldSFX(0xB9), cGameSFX::SFX_STOP_FIRST);
    Audio::gStadGenSFX.Stop(Audio::eWorldSFX(0xBA), cGameSFX::SFX_STOP_FIRST);
    Audio::gStadGenSFX.Stop(Audio::eWorldSFX(0xBD), cGameSFX::SFX_STOP_FIRST);

    if (mbHyperSTS)
    {
        void* data = (u8*)g_pEventManager->CreateValidEvent(0x47, 0x24) + 0x10;
        PassBallData* eventdata = new (data) PassBallData();
        eventdata->pPasser = m_pPrevOwner;
        eventdata->pTarget = NULL;

        bool pad = eventdata->pPasser->GetGlobalPad();
        eventdata->mPasserControllerID = pad ? eventdata->pPasser->GetGlobalPad()->m_padIndex : -1;
    }

    mbHyperSTS = false;
    mbIsPerfectShot = false;

    gbCanFadeOutPerfectPassSFX = true;

    if (AudioLoader::IsInited())
    {
        gfPerfectPassSFXVol = Audio::gStadGenSFX.GetSFXVol(0xBA);
    }
}

/**
 * Offset/Address/Size: 0x3794 | 0x8000D168 | size: 0x7C
 */
void cBall::ClearOwner()
{
    m_pPrevOwner = m_pOwner;
    m_pOwner = NULL;
    m_pPhysicsBall->EnableCollisions();

    m_v3PrevPosition = m_v3Position;
    m_pPhysicsBall->GetPosition(&m_v3Position);

    m_pPhysicsBall->GetLinearVelocity(&m_v3Velocity);

    m_bBallPathChangeCount++;
}

/**
 * Offset/Address/Size: 0x3810 | 0x8000D1E4 | size: 0x78
 */
cBall::~cBall()
{
    delete m_pPhysicsBall;
    delete m_pBallPosCollider;
}

static nlVector3 v3Zero = { 0.f, 0.f, 0.f };
static nlQuaternion qIdentity = { 0.f, 0.f, 0.f, 1.f };

/**
 * Offset/Address/Size: 0x3908 | 0x8000D2DC | size: 0x260
 * TODO: 96.22% match - todo: inline setter for quaternions seems to be missing
 */
cBall::cBall()
{
    u32 t0, t1, t2;
    nlVector3* pz;

    m_bBallPathChangeCount = 0;
    m_bBallDeflectCount = 0;

    m_tShotTimer.SetSeconds(0.f);
    m_tNoPickupTimer.SetSeconds(0.f);
    m_tPassTargetTimer.SetSeconds(0.f);
    m_tBuzzerBeaterTimer.SetSeconds(0.f);

    m_pBlurHandler = NULL;
    m_pOwner = NULL;
    m_pPrevOwner = NULL;
    m_pLastTouch = NULL;
    m_pPassTarget = NULL;
    m_pShooter = NULL;

    m_uGoalType = 4;
    m_uVoiceID = 0;

    mbIsPerfectShot = false;
    mbHyperSTS = false;
    mbCanDamage = false;
    m_unk_0xA3 = false;
    m_unk_0xA4 = false;
    m_unk_0xA6 = false;
    mpDamageTarget = NULL;

    m_pDrawableBall = WorldManager::s_World->FindDrawableObject(nlStringHash("gameplay/ball"));

    m_pDrawableBall->m_uObjectFlags |= 0x4;
    m_pDrawableBall->m_uObjectFlags |= 0x10;
    m_pDrawableBall->m_uObjectFlags |= 0x100;

    m_pPhysicsBall = new (nlMalloc(0x5c, 8, FALSE)) PhysicsAIBall(0.18f);
    m_pPhysicsBall->m_pAIBall = this;

    m_v3Position.f.x = 0.f;
    m_v3Position.f.y = 2.f;
    m_v3Position.f.z = 0.18f;

    m_v3PrevPosition = m_v3Position;

    m_v3PassIntercept.f.x = 0.f;
    m_v3PassIntercept.f.y = 0.f;
    m_v3PassIntercept.f.z = 0.f;

    m_pPhysicsBall->SetPosition(m_v3Position, PhysicsObject::WORLD_COORDINATES);

    // m_qOrientation.Identity();
    // nlQuatIdentity(m_qOrientation);

    // nlQuatSet2(m_qOrientation, 0.f, 0.f, 0.f, 1.f);

    pz = &v3Zero;

    m_qOrientation.f.z = 0.f;
    t0 = pz->as_u32[0];
    m_qOrientation.f.y = 0.f;
    t1 = pz->as_u32[1];
    m_qOrientation.f.x = 0.f;
    t2 = pz->as_u32[2];
    m_qOrientation.f.w = 1.f;

    m_v3ShotOrigin = m_v3Position;

    m_v3Velocity.as_u32[0] = t0;
    m_v3Velocity.as_u32[1] = t1;
    m_v3Velocity.as_u32[2] = t2;

    m_pPhysicsBall->SetLinearVelocity(m_v3Velocity);
    m_pPhysicsBall->SetAngularVelocity(*pz);

    m_fTotalPassTime = 0.f;
    m_tBuzzerBeaterTimer.SetSeconds(0.f);

    nlVector3 rayDir = { 0.f, 0.f, -1.f };

    m_pBallPosCollider = new (nlMalloc(0x2C, 8, FALSE)) RayCollider(1.f, m_v3Position, rayDir);

    if (AudioLoader::IsInited())
    {
        gfPerfectPassSFXVol = Audio::gStadGenSFX.GetSFXVol(0xBA);
    }
}

// /**
//  * Offset/Address/Size: 0x0 | 0x8000D53C | size: 0x1B4
//  */
// void BasicString<char, Detail::TempStringAllocator>::AppendInPlace(const char*)
// {
// }

// /**
//  * Offset/Address/Size: 0x1B4 | 0x8000D6F0 | size: 0x67C
//  */
// void BasicString<char, Detail::TempStringAllocator>::insert(char*, const char*, const char*)
// {
// }

// /**
//  * Offset/Address/Size: 0x830 | 0x8000DD6C | size: 0x94
//  */
// void BasicString<char, Detail::TempStringAllocator>::~BasicString()
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8000DE00 | size: 0x64
//  */
// void FuzzyVariant::Reset()
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8000DE64 | size: 0x1C
//  */
// void Variant::Reset()
// {
// }

// // /**
// //  * Offset/Address/Size: 0x0 | 0x8000DE80 | size: 0x8
// //  */
// int PhysicsSphere::GetObjectType() const
// {
//     return 0x0A;
// }

// // /**
// //  * Offset/Address/Size: 0x8 | 0x8000DE88 | size: 0x60
// //  */
// PhysicsSphere::~PhysicsSphere()
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8000DEE8 | size: 0x4
//  */
// int PhysicsObject::PreCollide()
// {
//     return 0;
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8000DEEC | size: 0x8
//  */
// void PassBallData::GetID()
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8000DEF4 | size: 0x8
//  */
// void EventData::GetID()
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8000DEFC | size: 0x40
//  */
// void nlStrNCpy<char>(char*, const char*, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x40 | 0x8000DF3C | size: 0x10
//  */
// void 0x8028D270..0x8028D274 | size: 0x4
// {
// }
