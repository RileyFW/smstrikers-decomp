#include "Game/Render/Bowser.h"
#include "Game/AI/HeadTrack.h"
#include "Game/AI/Powerups.h"
#include "Game/AI/Fielder.h"
#include "Game/Ball.h"

/**
 * Offset/Address/Size: 0x4BBC | 0x8015D930 | size: 0x2C
 */
void AnimSoundCallback(unsigned int)
{
}

/**
 * Offset/Address/Size: 0x4638 | 0x8015D3AC | size: 0x584
 */
Bowser::Bowser(cSHierarchy& pHierarchy, int nModelID, PhysicsNPC& mpPhysObj, cInventory<cSAnim>* pInventorySAnim)
    : SkinAnimatedMovableNPC(pHierarchy, nModelID, mpPhysObj)
{
}

/**
 * Offset/Address/Size: 0x44F0 | 0x8015D264 | size: 0x148
 */
Bowser::~Bowser()
{
}

/**
 * Offset/Address/Size: 0x325C | 0x8015BFD0 | size: 0x1294
 */
void Bowser::Update(float)
{
}

/**
 * Offset/Address/Size: 0x3054 | 0x8015BDC8 | size: 0x208
 */
void Bowser::CollisionCallback(PhysicsObject*, PhysicsObject*, const nlVector3&)
{
}

/**
 * Offset/Address/Size: 0x2B64 | 0x8015B8D8 | size: 0x4F0
 */
void Bowser::ActionInit()
{
}

/**
 * Offset/Address/Size: 0x28A4 | 0x8015B618 | size: 0x2C0
 */
void Bowser::ActionThrow()
{
}

/**
 * Offset/Address/Size: 0x26DC | 0x8015B450 | size: 0x1C8
 */
void Bowser::ActionRoll()
{
}

/**
 * Offset/Address/Size: 0x24B4 | 0x8015B228 | size: 0x228
 */
void Bowser::ActionStomp()
{
}

/**
 * Offset/Address/Size: 0x2314 | 0x8015B088 | size: 0x1A0
 */
void Bowser::ActionDescend(float)
{
}

/**
 * Offset/Address/Size: 0x2080 | 0x8015ADF4 | size: 0x294
 */
void Bowser::ActionFall()
{
}

/**
 * Offset/Address/Size: 0x1CE4 | 0x8015AA58 | size: 0x39C
 */
void Bowser::ActionJump()
{
}

/**
 * Offset/Address/Size: 0x1A90 | 0x8015A804 | size: 0x254
 */
void Bowser::ActionHide()
{
}

/**
 * Offset/Address/Size: 0x177C | 0x8015A4F0 | size: 0x314
 */
void Bowser::ActionReset()
{
}

/**
 * Offset/Address/Size: 0x1534 | 0x8015A2A8 | size: 0x248
 */
void Bowser::ActionLeave()
{
}

/**
 * Offset/Address/Size: 0x1384 | 0x8015A0F8 | size: 0x1B0
 */
void Bowser::Move(float)
{
}

/**
 * Offset/Address/Size: 0x1114 | 0x80159E88 | size: 0x270
 */
void Bowser::ActionIdle()
{
}

/**
 * Offset/Address/Size: 0x1044 | 0x80159DB8 | size: 0xD0
 */
void Bowser::SetTiltParameters(float)
{
}

/**
 * Offset/Address/Size: 0x954 | 0x801596C8 | size: 0x6F0
 */
void Bowser::CheckForAbort()
{
}

/**
 * Offset/Address/Size: 0x888 | 0x801595FC | size: 0xCC
 */
void Bowser::UpdateFireEmitter(EmissionController&)
{
}

/**
 * Offset/Address/Size: 0x810 | 0x80159584 | size: 0x78
 */
void Bowser::UpdateBowserLandEmitter(EmissionController&)
{
}

/**
 * Offset/Address/Size: 0x7A4 | 0x80159518 | size: 0x6C
 */
void Bowser::FindTarget()
{
    if (g_pBall->GetOwnerFielder() != NULL && !g_pBall->GetOwnerFielder()->IsInvincible())
    {
        mpTarget = g_pBall->GetOwnerFielder(); // at 0x0EC
    }
    else
    {
        mpTarget = FindPowerupTarget((cFielder*)NULL, this);
    }
}

/**
 * Offset/Address/Size: 0x334 | 0x801590A8 | size: 0x470
 */
void Bowser::SetupBaseSFX()
{
}

/**
 * Offset/Address/Size: 0x290 | 0x80159004 | size: 0xA4
 */
// void Bowser::PlaySFX(Audio::eCharSFX, PosUpdateMethod, float, bool)
// {
// }

/**
 * Offset/Address/Size: 0x9C | 0x80158E10 | size: 0x1F4
 */
void Bowser::CheckFootSteps()
{
}

/**
 * Offset/Address/Size: 0x60 | 0x80158DD4 | size: 0x3C
 */
float Bowser::GetHeadSpin() const
{
    return (float)(unsigned short)(int)this->mpHeadTrack->m_fHeadSpin;
}

/**
 * Offset/Address/Size: 0x24 | 0x80158D98 | size: 0x3C
 */
float Bowser::GetHeadTilt() const
{
    return (float)(unsigned short)(int)this->mpHeadTrack->m_fHeadTilt;
}

/**
 * Offset/Address/Size: 0x0 | 0x80158D74 | size: 0x24
 */
void Bowser::DrawShadow(const cPoseAccumulator& poseAccumulator, const nlMatrix4& matrix)
{
    SkinAnimatedNPC::DrawShadow(mpLastModel, matrix);
}
