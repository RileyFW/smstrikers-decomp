#include "Game/AI/Powerups.h"
#include "Game/AI/Fielder.h"
#include "Game/AI/AiUtil.h"
#include "Game/Render/Bowser.h"
#include "Game/Physics/PhysicsSphere.h"
#include "Game/Effects/EmissionManager.h"
#include "Game/Effects/EffectsGroup.h"
#include "Game/Game.h"
#include "Game/Sys/audio.h"
#include "Game/Audio/WorldAudio.h"
#include "NL/nlMath.h"
#include "NL/nlSlotPool.h"

int gBobombAnticipationVoiceID = -1;
PowerupSounds powerupSounds[9]; // size: 0x120, address: 0x802B9C84
PowerupBase* g_pPowerups[25];

namespace
{
struct Pair
{
    /* 0x0 */ unsigned long hashId;
    /* 0x4 */ const PowerupBase* powerup;
}; // total size: 0x8

struct PowerupRegistry
{
    /* 0x0 */ Pair registry[25];
}; // total size: 0xC8

PowerupRegistry powerupRegistry;
PowerupModelPool powerupModelPool;

unsigned long uBOBOMB_MASTER_OBJECT;
unsigned long uBANANA_MASTER_OBJECT;
unsigned long uRED_SHELL_MASTER_OBJECT;
unsigned long uGREEN_SHELL_MASTER_OBJECT;
unsigned long uSPINY_SHELL_MASTER_OBJECT;
unsigned long uFREEZE_SHELL_MASTER_OBJECT;

} // namespace

static const nlVector3 v3Zero = { 0.0f, 0.0f, 0.0f };

// extern Audio::cWorldSFX gPowerupSFX;

// /**
//  * Offset/Address/Size: 0x190 | 0x80061D50 | size: 0x64
//  */
// void SlotPool<FreezeShell>::~SlotPool()
// {
// }

// /**
//  * Offset/Address/Size: 0x12C | 0x80061CEC | size: 0x64
//  */
// void SlotPool<GreenShell>::~SlotPool()
// {
// }

// /**
//  * Offset/Address/Size: 0xC8 | 0x80061C88 | size: 0x64
//  */
// void SlotPool<SpinyShell>::~SlotPool()
// {
// }

// /**
//  * Offset/Address/Size: 0x64 | 0x80061C24 | size: 0x64
//  */
// void SlotPool<RedShell>::~SlotPool()
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x80061BC0 | size: 0x64
//  */
// void SlotPool<Banana>::~SlotPool()
// {
// }

// /**
//  * Offset/Address/Size: 0x374 | 0x80061B5C | size: 0x64
//  */
// void SlotPool<Bobomb>::~SlotPool()
// {
// }

// /**
//  * Offset/Address/Size: 0x114 | 0x80060A74 | size: 0xD74
//  */
// void FormatImpl<BasicString<char, Detail::TempStringAllocator>>::operator%<int>(const int&)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x80060960 | size: 0x114
//  */
// void Format<BasicString<char, Detail::TempStringAllocator>, int>(const BasicString<char, Detail::TempStringAllocator>&, const int&)
// {
// }

// /**
//  * Offset/Address/Size: 0x8 | 0x80060958 | size: 0x8
//  */
// void PowerupHitPlayerEventData::GetID()
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x80060950 | size: 0x8
//  */
// void PowerupUsedEventData::GetID()
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x80060948 | size: 0x8
//  */
// void DrawableObject::Clone() const
// {
// }

/**
 * Offset/Address/Size: 0x5EBC | 0x800607A8 | size: 0x1A0
 */
cFielder* FindPowerupTarget(cFielder*, Bowser*)
{
    return nullptr;
}

/**
 * Offset/Address/Size: 0x5998 | 0x80060284 | size: 0x524
 */
void PowerupThrowPosition(int, eThrowStyle, PowerupBase*, PowerupBase*)
{
}

/**
 * Offset/Address/Size: 0x4F00 | 0x8005F7EC | size: 0xA98
 */
void PowerupCreateAndThrow(cFielder*, ePowerUpType, int, Bowser*)
{
}

/**
 * Offset/Address/Size: 0x4EB4 | 0x8005F7A0 | size: 0x4C
 */
PowerupBase* FindPowerUp(unsigned long hashOfDrawable)
{
    int i = 0;
    while (i < 25)
    {
        if (powerupRegistry.registry[i].hashId == hashOfDrawable)
        {
            return const_cast<PowerupBase*>(powerupRegistry.registry[i].powerup);
        }
        i++;
    }
    return nullptr;
}

// /**
//  * Offset/Address/Size: 0x4C00 | 0x8005F4EC | size: 0x2B4
//  */
// void PowerupModelPool::Initialize(int, unsigned long)
// {
// }

/**
 * Offset/Address/Size: 0x4B68 | 0x8005F454 | size: 0x98
 */
void InitializePowerups()
{
    powerupModelPool.mNum = 0;
    powerupModelPool.Initialize(POWER_UP_FREEZE_SHELL, uFREEZE_SHELL_MASTER_OBJECT);
    powerupModelPool.Initialize(POWER_UP_SPINY_SHELL, uSPINY_SHELL_MASTER_OBJECT);
    powerupModelPool.Initialize(POWER_UP_GREEN_SHELL, uGREEN_SHELL_MASTER_OBJECT);
    powerupModelPool.Initialize(POWER_UP_RED_SHELL, uRED_SHELL_MASTER_OBJECT);
    powerupModelPool.Initialize(POWER_UP_BANANA, uBANANA_MASTER_OBJECT);
    powerupModelPool.Initialize(POWER_UP_BOBOMB, uBOBOMB_MASTER_OBJECT);
}

/**
 * Offset/Address/Size: 0x4AEC | 0x8005F3D8 | size: 0x7C
 */
void CompactPowerups()
{
    SlotPoolBase::BaseFreeBlocks(&GreenShell::m_GreenShellSlotPool, sizeof(GreenShell));
    SlotPoolBase::BaseFreeBlocks(&RedShell::m_RedShellSlotPool, sizeof(RedShell));
    SlotPoolBase::BaseFreeBlocks(&SpinyShell::m_SpinyShellSlotPool, sizeof(SpinyShell));
    SlotPoolBase::BaseFreeBlocks(&FreezeShell::m_FreezeShellSlotPool, sizeof(FreezeShell));
    SlotPoolBase::BaseFreeBlocks(&Banana::m_BananaSlotPool, sizeof(Banana));
    SlotPoolBase::BaseFreeBlocks(&Bobomb::m_BobombSlotPool, sizeof(Bobomb));
}

/**
 * Offset/Address/Size: 0x465C | 0x8005EF48 | size: 0x490
 */
PowerupBase::PowerupBase(cFielder*, ePowerUpType, float, ePowerupSize, bool, int)
{
}

/**
 * Offset/Address/Size: 0x4540 | 0x8005EE2C | size: 0x11C
 */
PowerupBase::~PowerupBase()
{
}

/**
 * Offset/Address/Size: 0x451C | 0x8005EE08 | size: 0x24
 */
float PowerupBase::GetRadius() const
{
    return ((PhysicsSphere*)m_pPhysicsObject)->GetRadius();
}

/**
 * Offset/Address/Size: 0x4404 | 0x8005ECF0 | size: 0x118
 */
void PowerupBase::Update(float dt)
{
    nlPolar polar;

    m_v3PrevPosition = m_v3Position;
    m_pPhysicsObject->GetPosition(&m_v3Position);
    m_pPhysicsObject->GetLinearVelocity(&m_v3Velocity);

    if (m_v3Position.f.z < ((PhysicsSphere*)m_pPhysicsObject)->GetRadius())
    {
        m_v3Position.f.z = ((PhysicsSphere*)m_pPhysicsObject)->GetRadius();
        m_pPhysicsObject->SetPosition(m_v3Position, PhysicsObject::WORLD_COORDINATES);
    }

    if (m_pBlurHandler != nullptr)
    {
        m_pBlurHandler->AddViewOrientedPoint(m_v3Position, m_v3Velocity);
    }

    mtActiveTimer.Countdown(dt, 0.0f);
    mtNoHitTimer.Countdown(dt, 0.0f);

    UpdateTransform();

    if (m_pBlurHandler != nullptr)
    {
        nlCartesianToPolar(polar, m_v3Velocity.f.x, m_v3Velocity.f.y);
        if (polar.r < 0.5f)
        {
            m_pBlurHandler->Die(0.5f);
            m_pBlurHandler = nullptr;
        }
    }
}

/**
 * Offset/Address/Size: 0x3DFC | 0x8005E6E8 | size: 0x608
 */
int PowerupBase::AwardPowerup(cTeam*)
{
    return 0;
}

/**
 * Offset/Address/Size: 0x38B4 | 0x8005E1A0 | size: 0x548
 */
void PowerupBase::CollisionCallback(PhysicsObject*, PhysicsObject*, const nlVector3&, void*)
{
}

/**
 * Offset/Address/Size: 0x3374 | 0x8005DC60 | size: 0x540
 */
void PowerupBase::ThrowAt(cFielder*, Bowser*)
{
}

/**
 * Offset/Address/Size: 0x28DC | 0x8005D1C8 | size: 0xA98
 */
void PowerupBase::Destroy(bool)
{
    FORCE_DONT_INLINE;
}

/**
 * Offset/Address/Size: 0x27C0 | 0x8005D0AC | size: 0x11C
 */
void PowerupBase::PreThrow(cFielder* pFielder, Bowser* pBowser)
{
    nlVector3 pos;

    if (pFielder != NULL)
    {
        if (pFielder->m_nPowerupAnimID == 0x5F || pFielder->m_nPowerupAnimID == 0x61)
        {
            pos = pFielder->GetJointPosition(pFielder->m_nLeftHandJointIndex);
        }
        else
        {
            pos = pFielder->GetJointPosition(pFielder->m_nRightHandJointIndex);
        }
    }
    else
    {
        nlVector3 localPt = { 0.0f, 0.0f, 0.0f };
        GetWorldPoint(pos, localPt, pBowser->mv3Position, pBowser->maFacingDirection);
    }

    m_v3Position = pos;
    m_pPhysicsObject->SetPosition(m_v3Position, PhysicsObject::WORLD_COORDINATES);
    m_v3Velocity = v3Zero;
    m_pPhysicsObject->SetLinearVelocity(v3Zero);
}

/**
 * Offset/Address/Size: 0x24CC | 0x8005CDB8 | size: 0x2F4
 */
void PowerupBase::UpdateTransform()
{
    FORCE_DONT_INLINE;
}

/**
 * Offset/Address/Size: 0x2360 | 0x8005CC4C | size: 0x16C
 */
void PowerupBase::Init(cFielder*, Bowser*)
{
}

// /**
//  * Offset/Address/Size: 0x22F0 | 0x8005CBDC | size: 0x70
//  */
// PhysicsShell::~PhysicsShell()
// {
// }

/**
 * Offset/Address/Size: 0x2050 | 0x8005C93C | size: 0x2A0
 */
void PowerupBase::PlayPowerupSound(ePowerUpType, PowerupBase::PowerupSound, const nlVector3&, float)
{
}

/**
 * Offset/Address/Size: 0x1E00 | 0x8005C6EC | size: 0x250
 */
void PowerupBase::PlayPowerupSound(ePowerUpType, PowerupBase::PowerupSound, PhysicsObject*, float)
{
}

/**
 * Offset/Address/Size: 0x1DD0 | 0x8005C6BC | size: 0x30
 */
void PowerupBase::StopPowerupInEffectSound(SFXEmitter* pSFXEmitter)
{
    Audio::gPowerupSFX.StopEmitter(pSFXEmitter, 0);
}

/**
 * Offset/Address/Size: 0x1C98 | 0x8005C584 | size: 0x138
 */
GreenShell::~GreenShell()
{
}

/**
 * Offset/Address/Size: 0x1A80 | 0x8005C36C | size: 0x218
 */
void GreenShell::Update(float dt)
{
    nlVector2 vel;
    nlPolar polar;
    // float radius;
    // float velLenSq;
    nlVector3 newVel;
    // float recipSqrt;

    m_v3PrevPosition = m_v3Position;
    m_pPhysicsObject->GetPosition(&m_v3Position);
    m_pPhysicsObject->GetLinearVelocity(&m_v3Velocity);

    if (m_v3Position.f.z < ((PhysicsSphere*)m_pPhysicsObject)->GetRadius())
    {
        m_v3Position.f.z = ((PhysicsSphere*)m_pPhysicsObject)->GetRadius();
        m_pPhysicsObject->SetPosition(m_v3Position, PhysicsObject::WORLD_COORDINATES);
    }

    if (m_pBlurHandler != nullptr)
    {
        m_pBlurHandler->AddViewOrientedPoint(m_v3Position, m_v3Velocity);
    }

    mtActiveTimer.Countdown(dt, 0.0f);
    mtNoHitTimer.Countdown(dt, 0.0f);

    UpdateTransform();

    if (m_pBlurHandler != nullptr)
    {
        nlCartesianToPolar(polar, m_v3Velocity.f.x, m_v3Velocity.f.y);
        if (polar.r < 0.5f)
        {
            m_pBlurHandler->Die(0.5f);
            m_pBlurHandler = nullptr;
        }
    }

    if (mtNoHitTimer.m_uPackedTime == 0)
    {
        nlCartesianToPolar(polar, m_v3Velocity.f.x, m_v3Velocity.f.y);

        if (polar.r < 3.0f)
        {
            m_bShouldDestroy = true;
        }
        else if (polar.r > 20.0f)
        {
            nlVector2 vel = (*(nlVector2*)&m_v3Velocity);
            float xx = vel.f.x * vel.f.x;
            float yy = vel.f.y * vel.f.y;
            // float velLenSq = xx + yy;
            // velLenSq = m_v3Velocity.f.x * m_v3Velocity.f.x + m_v3Velocity.f.y * m_v3Velocity.f.y;
            // newVel = m_v3Velocity;
            // // float velLenSq = vel.f.x * vel.f.x + vel.f.y * vel.f.y;
            float recipSqrt = nlRecipSqrt(xx + yy, true);

            // nlVec3Set(newVel, 19.0f * (recipSqrt * m_v3Velocity.f.x), 19.0f * (recipSqrt * m_v3Velocity.f.y), m_v3Velocity.f.z);

            newVel.f.x = 19.0f * (recipSqrt * m_v3Velocity.f.x);
            newVel.f.y = 19.0f * (recipSqrt * m_v3Velocity.f.y);
            newVel.f.z = m_v3Velocity.f.z;
            m_v3Velocity = newVel;

            m_pPhysicsObject->SetLinearVelocity(m_v3Velocity);
        }
    }

    if (m_bShouldDestroy)
    {
        m_pDrawableObj->m_uObjectFlags &= ~1;
        Destroy(false);
    }
}

/**
 * Offset/Address/Size: 0x19AC | 0x8005C298 | size: 0xD4
 */
void GreenShell::Destroy(bool bSilent)
{
    if (!bSilent && !g_pGame->mbCaptainShotToScoreOn)
    {
        EffectsGroup* pEffectsGroup;
        switch (meSize)
        {
        case POWERUPSIZE_LARGE:
            pEffectsGroup = fxGetGroup("greenshell_explode_big");
            break;
        case POWERUPSIZE_MEDIUM:
            pEffectsGroup = fxGetGroup("greenshell_explode_med");
            break;
        case POWERUPSIZE_SMALL:
            pEffectsGroup = fxGetGroup("greenshell_explode");
            break;
        }

        EmissionController* pController = EmissionManager::Create(pEffectsGroup, 0);
        pController->SetPosition(m_pPhysicsObject->GetPosition());
    }

    PowerupBase::Destroy(bSilent);
}

/**
 * Offset/Address/Size: 0x1874 | 0x8005C160 | size: 0x138
 */
RedShell::~RedShell()
{
}

/**
 * Offset/Address/Size: 0x1628 | 0x8005BF14 | size: 0x24C
 */
void RedShell::Update(float)
{
}

/**
 * Offset/Address/Size: 0x1554 | 0x8005BE40 | size: 0xD4
 */
void RedShell::Destroy(bool bSilent)
{
    if (!bSilent && !g_pGame->mbCaptainShotToScoreOn)
    {
        EffectsGroup* pEffectsGroup;
        switch (meSize)
        {
        case POWERUPSIZE_LARGE:
            pEffectsGroup = fxGetGroup("redshell_explode_big");
            break;
        case POWERUPSIZE_MEDIUM:
            pEffectsGroup = fxGetGroup("redshell_explode_med");
            break;
        case POWERUPSIZE_SMALL:
            pEffectsGroup = fxGetGroup("redshell_explode");
            break;
        }

        EmissionController* pController = EmissionManager::Create(pEffectsGroup, 0);
        pController->SetPosition(m_pPhysicsObject->GetPosition());
    }

    PowerupBase::Destroy(bSilent);
}

/**
 * Offset/Address/Size: 0x13C8 | 0x8005BCB4 | size: 0x18C
 */
void RedShell::SeekTarget()
{
}

/**
 * Offset/Address/Size: 0x1290 | 0x8005BB7C | size: 0x138
 */
Banana::~Banana()
{
}

/**
 * Offset/Address/Size: 0x1130 | 0x8005BA1C | size: 0x160
 */
void Banana::Update(float dt)
{
    nlPolar polar;

    m_v3PrevPosition = m_v3Position;
    m_pPhysicsObject->GetPosition(&m_v3Position);
    m_pPhysicsObject->GetLinearVelocity(&m_v3Velocity);

    if (m_v3Position.f.z < ((PhysicsSphere*)m_pPhysicsObject)->GetRadius())
    {
        m_v3Position.f.z = ((PhysicsSphere*)m_pPhysicsObject)->GetRadius();
        m_pPhysicsObject->SetPosition(m_v3Position, PhysicsObject::WORLD_COORDINATES);
    }

    if (m_pBlurHandler != nullptr)
    {
        m_pBlurHandler->AddViewOrientedPoint(m_v3Position, m_v3Velocity);
    }

    mtActiveTimer.Countdown(dt, 0.0f);
    mtNoHitTimer.Countdown(dt, 0.0f);

    UpdateTransform();

    if (m_pBlurHandler != nullptr)
    {
        nlCartesianToPolar(polar, m_v3Velocity.f.x, m_v3Velocity.f.y);
        if (polar.r < 0.5f)
        {
            m_pBlurHandler->Die(0.5f);
            m_pBlurHandler = nullptr;
        }
    }

    if (mtActiveTimer.m_uPackedTime == 0)
    {
        m_bShouldDestroy = true;
    }

    if (m_bShouldDestroy)
    {
        m_pDrawableObj->m_uObjectFlags &= ~1;
        Destroy(false);
    }
}

/**
 * Offset/Address/Size: 0x105C | 0x8005B948 | size: 0xD4
 */
void Banana::Destroy(bool bSilent)
{
    if (!bSilent && !g_pGame->mbCaptainShotToScoreOn)
    {
        EffectsGroup* pEffectsGroup;
        switch (meSize)
        {
        case POWERUPSIZE_LARGE:
            pEffectsGroup = fxGetGroup("banana_explode_big");
            break;
        case POWERUPSIZE_MEDIUM:
            pEffectsGroup = fxGetGroup("banana_explode_med");
            break;
        case POWERUPSIZE_SMALL:
            pEffectsGroup = fxGetGroup("banana_explode");
            break;
        }

        EmissionController* pController = EmissionManager::Create(pEffectsGroup, 0);
        pController->SetPosition(m_pPhysicsObject->GetPosition());
    }

    PowerupBase::Destroy(bSilent);
}

/**
 * Offset/Address/Size: 0xF24 | 0x8005B810 | size: 0x138
 */
SpinyShell::~SpinyShell()
{
}

/**
 * Offset/Address/Size: 0xD0C | 0x8005B5F8 | size: 0x218
 */
void SpinyShell::Update(float)
{
}

/**
 * Offset/Address/Size: 0xC38 | 0x8005B524 | size: 0xD4
 */
void SpinyShell::Destroy(bool bSilent)
{
    if (!bSilent && !g_pGame->mbCaptainShotToScoreOn)
    {
        EffectsGroup* pEffectsGroup;
        switch (meSize)
        {
        case POWERUPSIZE_LARGE:
            pEffectsGroup = fxGetGroup("spiny_shell_explode_big");
            break;
        case POWERUPSIZE_MEDIUM:
            pEffectsGroup = fxGetGroup("spiny_shell_explode_med");
            break;
        case POWERUPSIZE_SMALL:
            pEffectsGroup = fxGetGroup("spiny_shell_explode");
            break;
        }

        EmissionController* pController = EmissionManager::Create(pEffectsGroup, 0);
        pController->SetPosition(m_pPhysicsObject->GetPosition());
    }

    PowerupBase::Destroy(bSilent);
}

/**
 * Offset/Address/Size: 0xB00 | 0x8005B3EC | size: 0x138
 */
FreezeShell::~FreezeShell()
{
}

/**
 * Offset/Address/Size: 0x8E8 | 0x8005B1D4 | size: 0x218
 */
void FreezeShell::Update(float)
{
}

/**
 * Offset/Address/Size: 0x814 | 0x8005B100 | size: 0xD4
 */
void FreezeShell::Destroy(bool bSilent)
{
    if (!bSilent && !g_pGame->mbCaptainShotToScoreOn)
    {
        EffectsGroup* pEffectsGroup;
        switch (meSize)
        {
        case POWERUPSIZE_LARGE:
            pEffectsGroup = fxGetGroup("freeze_shell_explode_big");
            break;
        case POWERUPSIZE_MEDIUM:
            pEffectsGroup = fxGetGroup("freeze_shell_explode_med");
            break;
        case POWERUPSIZE_SMALL:
            pEffectsGroup = fxGetGroup("freeze_shell_explode");
            break;
        }

        EmissionController* pController = EmissionManager::Create(pEffectsGroup, 0);
        pController->SetPosition(m_pPhysicsObject->GetPosition());
    }

    PowerupBase::Destroy(bSilent);
}

/**
 * Offset/Address/Size: 0x6DC | 0x8005AFC8 | size: 0x138
 */
Bobomb::~Bobomb()
{
}

/**
 * Offset/Address/Size: 0x428 | 0x8005AD14 | size: 0x2B4
 */
void Bobomb::Update(float dt)
{
    // s32 soundID;
    bool bShouldPlaySound;
    nlPolar polar;
    nlVector3 pos;
    EmissionController* pController;
    Audio::SoundAttributes attributes;
    // PhysicsObject* pPhysObj;

    m_v3PrevPosition = m_v3Position;
    m_pPhysicsObject->GetPosition(&m_v3Position);
    m_pPhysicsObject->GetLinearVelocity(&m_v3Velocity);

    if (m_v3Position.f.z < ((PhysicsSphere*)m_pPhysicsObject)->GetRadius())
    {
        m_v3Position.f.z = ((PhysicsSphere*)m_pPhysicsObject)->GetRadius();
        m_pPhysicsObject->SetPosition(m_v3Position, PhysicsObject::WORLD_COORDINATES);
    }

    if (m_pBlurHandler != nullptr)
    {
        m_pBlurHandler->AddViewOrientedPoint(m_v3Position, m_v3Velocity);
    }

    mtActiveTimer.Countdown(dt, 0.0f);
    mtNoHitTimer.Countdown(dt, 0.0f);

    UpdateTransform();

    if (m_pBlurHandler != nullptr)
    {
        nlCartesianToPolar(polar, m_v3Velocity.f.x, m_v3Velocity.f.y);
        if (polar.r < 0.5f)
        {
            m_pBlurHandler->Die(0.5f);
            m_pBlurHandler = nullptr;
        }
    }

    if ((m_uVoiceID == 0) && (!g_pGame->mbCaptainShotToScoreOn))
    {
        u32 errorCode;
        PhysicsObject* pPhysObj = m_pPhysicsObject;
        if (m_eType >= NUM_POWER_UPS)
        {
            errorCode = Audio::GetSndIDError();
        }
        else
        {
            if (!Audio::IsInited())
            {
                errorCode = Audio::GetSndIDError();
            }
            else
            {
                attributes.Init();
                u32 soundID = powerupSounds[m_eType].sndInEffect;

                if (soundID == 0xFFFFFFFF)
                {
                    errorCode = -1;
                }
                else
                {
                    attributes.SetSoundType(soundID, true);
                    if (m_eType == POWER_UP_BOBOMB)
                    {
                        attributes.UsePhysObj(pPhysObj);
                        m_bShouldDestroy = true;
                    }
                    else
                    {
                        attributes.UsePhysObj(pPhysObj);
                        m_bShouldDestroy = true;
                    }

                    Audio::gPowerupSFX.GetSFXVol(soundID);
                    errorCode = Audio::gPowerupSFX.Play(attributes);
                }
            }
        }
        m_uVoiceID = errorCode;
    }

    pController = EmissionManager::Create(fxGetGroup("bobomb_tick"), 0);
    pos = m_pPhysicsObject->GetPosition();
    pos.f.z += ((PhysicsSphere*)m_pPhysicsObject)->GetRadius();
    pController->SetPosition(pos);

    if (mtActiveTimer.m_uPackedTime == 0)
    {
        m_bShouldDestroy = true;
    }

    if (m_bShouldDestroy)
    {
        m_pDrawableObj->m_uObjectFlags &= ~1;
        Destroy(false);
    }
}

/**
 * Offset/Address/Size: 0x80 | 0x8005A96C | size: 0x3A8
 */
void Bobomb::ThrowAt(cFielder*, Bowser*)
{
}

/**
 * Offset/Address/Size: 0x0 | 0x8005A8EC | size: 0x80
 */
void Bobomb::Destroy(bool bSilent)
{
    if (gBobombAnticipationVoiceID != -1)
    {
        Audio::StopSFX(gBobombAnticipationVoiceID);
        gBobombAnticipationVoiceID = -1;
    }

    if (pMovementEmitter != nullptr)
    {
        Audio::gPowerupSFX.StopEmitter(pMovementEmitter, 0);
        pMovementEmitter = nullptr;
    }

    PowerupBase::Destroy(bSilent);
}
