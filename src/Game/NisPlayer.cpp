#include "Game/NisPlayer.h"

NisPlayer* NisPlayer::m_pInstance = NULL;

/**
 * Offset/Address/Size: 0x0 | 0x80114CDC | size: 0x74
 */
NisPlayer::~NisPlayer()
{
}

/**
 * Offset/Address/Size: 0x74 | 0x80114D50 | size: 0x2C
 */
void NisPlayer::SetExtraNameFilter(const char*)
{
}

/**
 * Offset/Address/Size: 0xA0 | 0x80114D7C | size: 0x24
 */
void NisPlayer::ResetEffects()
{
}

/**
 * Offset/Address/Size: 0xC4 | 0x80114DA0 | size: 0x130
 */
void NisPlayer::IsMirrored(NisTarget, const char*, NisWinnerType) const
{
}

/**
 * Offset/Address/Size: 0x1F4 | 0x80114ED0 | size: 0x17C
 */
void NisPlayer::TargetToIndex(NisTarget, int, NisWinnerType) const
{
}

/**
 * Offset/Address/Size: 0x370 | 0x8011504C | size: 0x1D8
 */
void NisPlayer::EventHandler(Event*)
{
}

/**
 * Offset/Address/Size: 0x548 | 0x80115224 | size: 0xC8
 */
void NisPlayer::PlayCharacterDirection()
{
}

/**
 * Offset/Address/Size: 0x610 | 0x801152EC | size: 0x99C
 */
void NisPlayer::Load(const char*, NisTarget, NisUseStadiumOffset, NisUseFilter, NisWinnerType)
{
}

/**
 * Offset/Address/Size: 0xFAC | 0x80115C88 | size: 0xA9C
 */
void NisPlayer::GetTargetFilter(NisTarget, NisWinnerType) const
{
}

/**
 * Offset/Address/Size: 0x1A48 | 0x80116724 | size: 0x98
 */
void NisPlayer::AsyncLoad(nlFile*, void*, unsigned int, unsigned long)
{
}

/**
 * Offset/Address/Size: 0x1AE0 | 0x801167BC | size: 0xD08
 */
void NisPlayer::LoadTriggers(Nis&)
{
}

/**
 * Offset/Address/Size: 0x27E8 | 0x801174C4 | size: 0x10C
 */
void NisPlayer::Load(char*, unsigned int, NisHeader&)
{
}

/**
 * Offset/Address/Size: 0x28F4 | 0x801175D0 | size: 0x1E0
 */
void NisPlayer::Render() const
{
}

/**
 * Offset/Address/Size: 0x2AD4 | 0x801177B0 | size: 0x1F8
 */
void NisPlayer::Play()
{
}

/**
 * Offset/Address/Size: 0x2CCC | 0x801179A8 | size: 0xD8
 */
void NisPlayer::Reset()
{
}

/**
 * Offset/Address/Size: 0x2DA4 | 0x80117A80 | size: 0x1C0
 */
void NisPlayer::Update(float)
{
}

/**
 * Offset/Address/Size: 0x2F64 | 0x80117C40 | size: 0x318
 */
void NisPlayer::HandleAsyncs()
{
}

/**
 * Offset/Address/Size: 0x327C | 0x80117F58 | size: 0xDC
 */
bool NisPlayer::WorldIsFrozen() const
{
    return false;
}

/**
 * Offset/Address/Size: 0x3358 | 0x80118034 | size: 0xB0
 */
void NisPlayer::TimeLeft() const
{
}

/**
 * Offset/Address/Size: 0x3408 | 0x801180E4 | size: 0x588
 */
NisPlayer::NisPlayer()
{
}

/**
 * Offset/Address/Size: 0x3990 | 0x8011866C | size: 0x58
 */
NisPlayer* NisPlayer::Instance()
{
    if (m_pInstance == NULL)
    {
        m_pInstance = new NisPlayer();
    }
    return m_pInstance;
}

/**
 * Offset/Address/Size: 0x0 | 0x801186C4 | size: 0x74C
 */
void NisPlayer::DoFunctionCall(unsigned int)
{
}

// /**
//  * Offset/Address/Size: 0x0 | 0x80118E10 | size: 0x54
//  */
// void nlToLower<char>(char*)
// {
// }

// /**
//  * Offset/Address/Size: 0x54 | 0x80118E64 | size: 0x20
//  */
// void nlToLower<char>(char)
// {
// }

// /**
//  * Offset/Address/Size: 0x74 | 0x80118E84 | size: 0x2C
//  */
// void nlStrLen<char>(const char*)
// {
// }
