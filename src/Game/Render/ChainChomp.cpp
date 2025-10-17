#include "Game/Render/ChainChomp.h"

#include "Game/Game.h"
#include "Game/Player.h"
#include "Game/ReplayManager.h"
#include "Game/Effects/EmissionController.h"
#include "Game/Effects/EmissionManager.h"
#include "Game/AI/Powerups.h"

const nlVector3 v3Zero = { 0.0f, 0.0f, 0.0f };
const nlVector3 gv3HomePosition = { 0.0f, 0.0f, 10.0f };

/**
 * Offset/Address/Size: 0x12BC | 0x8015EFC0 | size: 0x1D8
 */
ChainChomp::ChainChomp(cSHierarchy& pHierarchy, int nModelID, PhysicsNPC& mpPhysObj, cInventory<cSAnim>* pInventorySAnim)
    : SkinAnimatedMovableNPC(pHierarchy, nModelID, mpPhysObj)
{
}

/**
 * Offset/Address/Size: 0x125C | 0x8015EF60 | size: 0x60
 */
ChainChomp::~ChainChomp()
{
}

/**
 * Offset/Address/Size: 0xAA8 | 0x8015E7AC | size: 0x7B4
 */
void ChainChomp::Update(float)
{
}

/**
 * Offset/Address/Size: 0x97C | 0x8015E680 | size: 0x12C
 */
void ChainChomp::CollisionCallback(PhysicsObject*, PhysicsObject*, const nlVector3&)
{
}

/**
 * Offset/Address/Size: 0x8E8 | 0x8015E5EC | size: 0x94
 */
void UpdateChainEmitter(EmissionController& controller)
{
    if (ReplayManager::Instance()->mRender != nullptr)
    {
        {
            ReplayManager* replayManager = ReplayManager::Instance();
            controller.SetPosition(replayManager->mRender->mChainChomp.mPosition);
        }
        {
            ReplayManager* replayManager = ReplayManager::Instance();
            controller.SetVelocity(replayManager->mRender->mChainChomp.mVelocity);
        }
        nlVector3 direction = { 0.0f, 0.0f, 0.0f };
        controller.SetDirection(direction);
    }
}

/**
 * Offset/Address/Size: 0x608 | 0x8015E30C | size: 0x2E0
 */
void ChainChomp::FindTarget(cTeam*)
{
}

/**
 * Offset/Address/Size: 0x4B4 | 0x8015E1B8 | size: 0x154
 */
void ChainChomp::Fall(cFielder* pThrower, cFielder* pTarget)
{
    class nlVector3 v3StartPosition;
    class nlVector3 v3FallVelocity;

    mbIsVisible = true;
    SetAnimState(*mpDropAnim, 0.2f, PM_CYCLIC);
    mpTarget = pTarget;
    mfDesiredSpeed = g_pGame->m_pGameTweaks->fChainChompSpeed;
    PowerupBase::PlayPowerupSound(POWER_UP_CHAIN_CHOMP, PowerupBase::PWRUP_SOUND_ACTIVATE, mpPhysObj, 100.0f);
    meChainChompState = CHAIN_STATE_FALL;

    v3StartPosition = mpTarget->m_v3Position;
    v3StartPosition.f.z = 100.0f;
    SetPosition(v3StartPosition);

    nlVec3Set(v3FallVelocity, 0.0f, 0.0f, -(75.0f / g_pGame->m_pGameTweaks->fChainChompFallTime));
    mv3Velocity = v3FallVelocity;

    mtStateTimer.SetSeconds(g_pGame->m_pGameTweaks->fChainChompFallTime);
    mpThrower = pThrower;

    bool bHasGlobalPad = pThrower->GetGlobalPad() != nullptr;
    mnThrowerPadID = bHasGlobalPad ? pThrower->GetGlobalPad()->m_padIndex : -1;

    mpPhysObj->DisableCollisions();
}

/**
 * Offset/Address/Size: 0x3BC | 0x8015E0C0 | size: 0xF8
 */
void ChainChomp::Hide(bool bIsEndGame)
{
    if (mpInEffectSFX != nullptr)
    {
        PowerupBase::StopPowerupInEffectSound(mpInEffectSFX);
        mpInEffectSFX = nullptr;
    }

    EffectsGroup* pEffectsGroup = fxGetGroup("chainchomp_trail"); // Chain chomp effects group

    if (!bIsEndGame)
    {
        EmissionManager::Kill((unsigned long)this, pEffectsGroup);
    }
    else
    {
        EmissionManager::Destroy((unsigned long)this, pEffectsGroup);
    }

    meChainChompState = CHAIN_STATE_HIDDEN;
    mfDesiredSpeed = 0.0f;

    SetAnimState(*mpIdleAnim, 0.0f, PM_CYCLIC);
    SetPosition(gv3HomePosition);

    mv3Velocity = v3Zero;
    maFacingDirection = 0;

    mpPhysObj->DisableCollisions();

    mpThrower = nullptr;
    mnThrowerPadID = -1;
    mbIsVisible = false;
}

/**
 * Offset/Address/Size: 0x3AC | 0x8015E0B0 | size: 0x10
 */
bool ChainChomp::IsHidden() const
{
    return meChainChompState == CHAIN_STATE_HIDDEN;
}

/**
 * Offset/Address/Size: 0x204 | 0x8015DF08 | size: 0x1A8
 */
void ChainChomp::Move(float)
{
}

/**
 * Offset/Address/Size: 0x0 | 0x8015DD04 | size: 0x204
 */
void ChainChomp::DrawShadow(const cPoseAccumulator&, const nlMatrix4&)
{
}
