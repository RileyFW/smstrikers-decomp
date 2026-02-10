#include "Game/NisPlayer.h"
#include "Game/Camera/CameraMan.h"
#include "Game/Character.h"
#include "Game/Effects/EmissionManager.h"
#include "NL/nlTask.h"
#include "NL/nlString.h"
#include "string.h"

// /**
//  * Offset/Address/Size: 0x74 | 0x80118E84 | size: 0x2C
//  */
// void nlStrLen<char>(const char*)
// {
// }

// /**
//  * Offset/Address/Size: 0x54 | 0x80118E64 | size: 0x20
//  */
// void nlToLower<char>(char)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x80118E10 | size: 0x54
//  */
// void nlToLower<char>(char*)
// {
// }

/**
 * Offset/Address/Size: 0x0 | 0x801186C4 | size: 0x74C
 */
void NisPlayer::DoFunctionCall(unsigned int)
{
}

/**
 * Offset/Address/Size: 0x3990 | 0x8011866C | size: 0x58
 */
NisPlayer* NisPlayer::Instance()
{
    static NisPlayer instance;
    return &instance;
}

/**
 * Offset/Address/Size: 0x3408 | 0x801180E4 | size: 0x588
 */
NisPlayer::NisPlayer()
    : InterpreterCore(0x1000)
{
    FORCE_DONT_INLINE;
}

/**
 * Offset/Address/Size: 0x3358 | 0x80118034 | size: 0xB0
 */
float NisPlayer::TimeLeft() const
{
    if (mPlaying[0] != NULL)
    {
        if (strstr(mPlaying[0]->Name(), "trophy") != NULL)
        {
            return 1.0f;
        }
    }

    cCameraData* pCameraData = mCamera.m_pActiveCameraData;
    if (pCameraData != NULL)
    {
        float animTime = mCamera.m_fAnimationTime;
        float duration;
        if (pCameraData != NULL)
        {
            duration = (float)(pCameraData->m_uKeyCount - 1) / 30.0f;
        }
        else
        {
            duration = 0.0f;
        }

        return (1.0f - animTime) * duration;
    }

    return 0.0f;
}

/**
 * Offset/Address/Size: 0x327C | 0x80117F58 | size: 0xDC
 */
bool NisPlayer::WorldIsFrozen() const
{
    bool stateOK = (nlTaskManager::m_pInstance->m_CurrState == 0x100);
    if (stateOK)
    {
        return TimeLeft() == 0.0f;
    }
    return stateOK;
}

/**
 * Offset/Address/Size: 0x2F64 | 0x80117C40 | size: 0x318
 */
void NisPlayer::HandleAsyncs()
{
}

/**
 * Offset/Address/Size: 0x2DA4 | 0x80117A80 | size: 0x1C0
 */
void NisPlayer::Update(float)
{
}

/**
 * Offset/Address/Size: 0x2CCC | 0x801179A8 | size: 0xD8
 */
void NisPlayer::Reset()
{
    if (!mActive)
    {
        return;
    }

    for (int i = 0; i < 4; i++)
    {
        delete mPlaying[i];
        delete mLoaded[i];
        mPlaying[i] = NULL;
        mLoaded[i] = NULL;
        mLoadQueue[i] = NULL;
        mAsyncStarted[i] = false;
    }

    mActive = false;
    mLoadingFromBack = false;
    mUsedFromFront = 0;
    mUsedFromBack = 0x70800;
    mCamera.UnselectCameraAnimation();
    cCameraManager::Remove(mCamera);
}

/**
 * Offset/Address/Size: 0x2AD4 | 0x801177B0 | size: 0x1F8
 */
void NisPlayer::Play()
{
}

/**
 * Offset/Address/Size: 0x28F4 | 0x801175D0 | size: 0x1E0
 */
void NisPlayer::Render() const
{
}

/**
 * Offset/Address/Size: 0x27E8 | 0x801174C4 | size: 0x10C
 */
void NisPlayer::Load(char* buffer, unsigned int size, NisHeader& nisHeader)
{
    if (!mActive)
        return;

    for (int i = 0; i < 4; i++)
    {
        if (mLoaded[i] != NULL)
            continue;

        int j;
        for (j = 0; j < 4; j++)
        {
            if (&nisHeader == mLoadQueue[j])
            {
                mLoadQueue[j] = NULL;
                mAsyncStarted[j] = false;
                break;
            }
        }

        if (j >= 4)
            continue;

        Nis* nis = new (nlMalloc(0x740, 8, false)) Nis(nisHeader, buffer, size);
        mLoaded[i] = nis;
        LoadTriggers(*mLoaded[i]);
        return;
    }
}

/**
 * Offset/Address/Size: 0x1AE0 | 0x801167BC | size: 0xD08
 */
void NisPlayer::LoadTriggers(Nis&)
{
    FORCE_DONT_INLINE;
}

/**
 * Offset/Address/Size: 0x1A48 | 0x80116724 | size: 0x98
 * TODO: 99.21% match - remaining `i` diffs are the local-static `instance` / `init$` relocation immediates.
 */
void NisPlayer::AsyncLoad(nlFile* file, void* buffer, unsigned int size, unsigned long param)
{
    if (file != NULL)
    {
        nlClose(file);
    }

    static NisPlayer instance;
    instance.Load((char*)buffer - size, size, *(NisHeader*)param);
}

/**
 * Offset/Address/Size: 0xFAC | 0x80115C88 | size: 0xA9C
 */
void NisPlayer::GetTargetFilter(NisTarget, NisWinnerType) const
{
}

/**
 * Offset/Address/Size: 0x610 | 0x801152EC | size: 0x99C
 */
void NisPlayer::Load(const char*, NisTarget, NisUseStadiumOffset, NisUseFilter, NisWinnerType)
{
}

/**
 * Offset/Address/Size: 0x548 | 0x80115224 | size: 0xC8
 */
void NisPlayer::PlayCharacterDirection()
{
    Event* event = g_pEventManager->CreateValidEvent(7, 0x20);
    CharacterDirectionData* pData = new (&event->m_data) CharacterDirectionData();
    pData->home = &mCharDirections[0];
    pData->away = &mCharDirections[4];
    for (int i = 0; i < 10; i++)
    {
        mCharDirections[i].f.x = nlRandomf(-20.0f, 20.0f, &nlDefaultSeed);
        mCharDirections[i].f.y = nlRandomf(-50.0f, 10.0f, &nlDefaultSeed);
        mCharDirections[i].f.z = 0.0f;
    }
}

/**
 * Offset/Address/Size: 0x370 | 0x8011504C | size: 0x1D8
 */
void NisPlayer::EventHandler(Event*)
{
}

/**
 * Offset/Address/Size: 0x1F4 | 0x80114ED0 | size: 0x17C
 */
void NisPlayer::TargetToIndex(NisTarget, int, NisWinnerType) const
{
}

/**
 * Offset/Address/Size: 0xC4 | 0x80114DA0 | size: 0x130
 */
void NisPlayer::IsMirrored(NisTarget, const char*, NisWinnerType) const
{
}

/**
 * Offset/Address/Size: 0xA0 | 0x80114D7C | size: 0x24
 */
void NisPlayer::ResetEffects()
{
    EmissionManager::Destroy(reinterpret_cast<unsigned long>(this), nullptr);
}

/**
 * Offset/Address/Size: 0x74 | 0x80114D50 | size: 0x2C
 */
void NisPlayer::SetExtraNameFilter(const char* filter)
{
    nlStrNCpy(mExtraNameFilter, filter, 128);
}

/**
 * Offset/Address/Size: 0x0 | 0x80114CDC | size: 0x74
 */
NisPlayer::~NisPlayer()
{
}
