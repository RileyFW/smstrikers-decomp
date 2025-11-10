#include "Game/NisPlayer.h"
#include "Game/Effects/EmissionManager.h"
#include "NL/nlTask.h"
#include "NL/nlString.h"
#include "string.h"

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
void NisPlayer::SetExtraNameFilter(const char* filter)
{
    nlStrNCpy(mExtraNameFilter, filter, 128);
}

/**
 * Offset/Address/Size: 0xA0 | 0x80114D7C | size: 0x24
 */
void NisPlayer::ResetEffects()
{
    EmissionManager::Destroy(reinterpret_cast<unsigned long>(this), nullptr);
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
    // Check if task manager is in state 0x100 (256)
    // If so, world is not frozen
    if (nlTaskManager::m_pInstance != nullptr)
    {
        if (nlTaskManager::m_pInstance->m_CurrState == 0x100)
        {
            return false;
        }
    }

    // Check if there's a playing NIS with "trophy" in the name
    // Access mPlaying[0] at offset 0xBC34 (calculated as 0x10000 - 0x43cc)
    Nis* pPlaying = *(Nis**)((char*)this + 0xBC34);
    if (pPlaying != nullptr)
    {
        const char* name = pPlaying->Name();
        if (strstr(name, "trophy") != nullptr)
        {
            return true; // World is frozen for trophy NIS
        }
    }

    // Check mLoadQueue[0] at offset 0xBCFC (calculated as 0x10000 - 0x4304)
    NisHeader* pLoadQueue = *(NisHeader**)((char*)this + 0xBCFC);
    if (pLoadQueue == nullptr)
    {
        return false;
    }

    // Access current time at offset 0xBCF0 (calculated as 0x10000 - 0x4310)
    float currentTime = *(float*)((char*)this + 0xBCF0);
    float timeRemaining = 1.0f - currentTime;

    float duration = 0.0f;
    if (pLoadQueue != nullptr)
    {
        int numAnimations = pLoadQueue->numAnimations;
        if (numAnimations > 0)
        {
            duration = (float)(numAnimations - 1) / 30.0f;
        }
    }

    float frozenTime = timeRemaining * duration;

    // Return true if frozenTime > 0.0f, false otherwise
    return frozenTime > 0.0f;
}

/**
 * Offset/Address/Size: 0x3358 | 0x80118034 | size: 0xB0
 */
float NisPlayer::TimeLeft() const
{
}

/**
 * Offset/Address/Size: 0x3408 | 0x801180E4 | size: 0x588
 */
NisPlayer::NisPlayer()
    : InterpreterCore(0x1000)
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
