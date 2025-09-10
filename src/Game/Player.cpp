#include "Game/Player.h"
#include "Game/Character.h"

/**
 * Offset/Address/Size: 0x0 | 0x80057550 | size: 0x20
 */
s32 cPlayer::GetUniqueID(int arg0) const
{
    if (arg0 == -1)
    {
        arg0 = *(s32*)m_pTeam;
    }
    arg0 *= 5;
    return arg0 + m_ID;
}

/**
 * Offset/Address/Size: 0x20 | 0x80057570 | size: 0x48
 */
void cPlayer::SetNoPickUpTime(float arg0)
{
    // To add .. some bits get set (arg0 <= 0.f)...
    m_tNoPickupTimer.SetSeconds(arg0);
}

/**
 * Offset/Address/Size: 0x68 | 0x800575B8 | size: 0xAC
 */
void cPlayer::GetAIDefNetLocation(const nlVector3*)
{
}

/**
 * Offset/Address/Size: 0x114 | 0x80057664 | size: 0xE0
 */
void cPlayer::GetAIOffNetLocation(const nlVector3*)
{
}

/**
 * Offset/Address/Size: 0x1F4 | 0x80057744 | size: 0x90
 */
void cPlayer::CanPickupBallFromPass(cBall*)
{
}

/**
 * Offset/Address/Size: 0x284 | 0x800577D4 | size: 0x1B0
 */
void cPlayer::CanPickupBall(cBall*)
{
}

/**
 * Offset/Address/Size: 0x434 | 0x80057984 | size: 0x20
 */
void cPlayer::PostPhysicsUpdate()
{
    cCharacter::PostPhysicsUpdate();
}

/**
 * Offset/Address/Size: 0x454 | 0x800579A4 | size: 0x34
 */
void cPlayer::PreUpdate(float arg0)
{
    cCharacter::PreUpdate(arg0);
    m_bCanTestController = true;
}

/**
 * Offset/Address/Size: 0x488 | 0x800579D8 | size: 0x148
 */
void cPlayer::PrePhysicsUpdate(float)
{
}

/**
 * Offset/Address/Size: 0x5D0 | 0x80057B20 | size: 0x148
 */
void cPlayer::PlayerHeadTrackCallback(unsigned int, unsigned int, cPoseAccumulator*, unsigned int, int)
{
}

/**
 * Offset/Address/Size: 0x718 | 0x80057C68 | size: 0x140
 */
void cPlayer::CreateSingleAxisBlender(const int*, int, int, void (*)(unsigned int, cPN_SingleAxisBlender*), float, cPN_SAnimController*)
{
}

/**
 * Offset/Address/Size: 0x858 | 0x80057DA8 | size: 0x38
 */
void cPlayer::CollideWithWallCallback(const CollisionPlayerWallData*)
{
}

/**
 * Offset/Address/Size: 0x890 | 0x80057DE0 | size: 0xE8
 */
void cPlayer::SetPowerupAnimState(int)
{
}

/**
 * Offset/Address/Size: 0x978 | 0x80057EC8 | size: 0x18
 */
void cPlayer::ClearSwapControllerTimer()
{
    m_tSwapControllerTimer[0].m_uPackedTime = 0;
    m_tSwapControllerTimer[1].m_uPackedTime = 0;
    m_tSwapControllerTimer[2].m_uPackedTime = 0;
    m_tSwapControllerTimer[3].m_uPackedTime = 0;
}

/**
 * Offset/Address/Size: 0x990 | 0x80057EE0 | size: 0x80
 */
void cPlayer::ClearPowerupAnimState(bool)
{
}

/**
 * Offset/Address/Size: 0xA10 | 0x80057F60 | size: 0xBCC
 */
void cPlayer::DoRegularPassing(cPlayer*, bool, bool, bool, bool)
{
}

/**
 * Offset/Address/Size: 0x15DC | 0x80058B2C | size: 0x34
 */
void cPlayer::ResetUnPossessionTimer()
{
}

/**
 * Offset/Address/Size: 0x1610 | 0x80058B60 | size: 0xD4
 */
void cPlayer::ReleaseBall()
{
}

/**
 * Offset/Address/Size: 0x16E4 | 0x80058C34 | size: 0x1C
 */
cGlobalPad* cPlayer::GetGlobalPad()
{
    // temp_r3 = this->unk1C0;
    if (m_pController != NULL)
    {
        return m_pController->m_pPad;
    }
    return 0;
}

/**
 * Offset/Address/Size: 0x1700 | 0x80058C50 | size: 0x230
 */
void cPlayer::DoFindBestPassTarget(bool, bool)
{
}

/**
 * Offset/Address/Size: 0x1930 | 0x80058E80 | size: 0x24
 */
void cPlayer::IsCaptain() const
{
}

/**
 * Offset/Address/Size: 0x1954 | 0x80058EA4 | size: 0x28
 */
void cPlayer::IsOnSameTeam(cPlayer*)
{
}

/**
 * Offset/Address/Size: 0x197C | 0x80058ECC | size: 0x4A4
 */
void cPlayer::SetAIPad(cAIPad*)
{
}

/**
 * Offset/Address/Size: 0x1E20 | 0x80059370 | size: 0x18C
 */
void cPlayer::PlayAttackReactionSounds(float)
{
}

/**
 * Offset/Address/Size: 0x1FAC | 0x800594FC | size: 0x2EC
 */
void cPlayer::PickupBall(cBall*)
{
}

/**
 * Offset/Address/Size: 0x2298 | 0x800597E8 | size: 0x138
 */
void cPlayer::GetClosestOpponentFielder(nlVector3*)
{
}

/**
 * Offset/Address/Size: 0x23D0 | 0x80059920 | size: 0x4
 */
void cPlayer::CollideWithCharacterCallback(CollisionPlayerPlayerData*)
{
}

/**
 * Offset/Address/Size: 0x23D4 | 0x80059924 | size: 0x64
 */
void cPlayer::CollideWithBallCallback(cBall*)
{
}

/**
 * Offset/Address/Size: 0x2438 | 0x80059988 | size: 0x134
 */
void cPlayer::DoFlashLight(const nlVector3&, unsigned short, float, float, float)
{
}

/**
 * Offset/Address/Size: 0x256C | 0x80059ABC | size: 0x134
 */
void cPlayer::DoFlashLight(const nlVector3&, const nlVector3&, unsigned short, float, float, float)
{
}

/**
 * Offset/Address/Size: 0x26A0 | 0x80059BF0 | size: 0x5C
 */
void cPlayer::SetAnimID(int)
{
}

/**
 * Offset/Address/Size: 0x26FC | 0x80059C4C | size: 0x190
 */
void cPlayer::GetAnimatedBallOrientation(nlQuaternion&)
{
}

/**
 * Offset/Address/Size: 0x288C | 0x80059DDC | size: 0x1C4
 */
void cPlayer::Update(float)
{
}

/**
 * Offset/Address/Size: 0x2A50 | 0x80059FA0 | size: 0x27C
 */
void cPlayer::SwapController()
{
}

/**
 * Offset/Address/Size: 0x2CCC | 0x8005A21C | size: 0x114
 */
void cPlayer::SetDesiredFacingDirection()
{
}

/**
 * Offset/Address/Size: 0x2DE0 | 0x8005A330 | size: 0x10
 */
void cPlayer::ResetDesiredDirections(unsigned short)
{
}

/**
 * Offset/Address/Size: 0x2DF0 | 0x8005A340 | size: 0x5C
 */
void cPlayer::SetSpaceSearch(SpaceSearch*)
{
}

/**
 * Offset/Address/Size: 0x2E4C | 0x8005A39C | size: 0x160
 */
cPlayer::~cPlayer()
{
}

/**
 * Offset/Address/Size: 0x2FAC | 0x8005A4FC | size: 0x380
 */
cPlayer::cPlayer(int arg0, eCharacterClass characterClass, const int* arg2, cSHierarchy* hierarchy, cAnimInventory* animInventory, const CharacterPhysicsData* physData, PlayerTweaks* playerTweaks, AnimRetargetList* animRetargetList, eClassTypes classType)
    : cCharacter(characterClass, arg2, hierarchy, animInventory, physData, playerTweaks->fPhysCapsuleHeight, playerTweaks->fPhysCapsuleRadius, animRetargetList, classType)
{
}

/**
 * Offset/Address/Size: 0x332C | 0x8005A87C | size: 0x34
 */
// void Timer::__defctor()
// {
// }

/**
 * Offset/Address/Size: 0x0 | 0x8005A8B0 | size: 0x4
 */
void cPlayer::InitActionPostWhistle()
{
}
