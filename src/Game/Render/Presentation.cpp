#include "Game/Render/Presentation.h"
#include "Game/FixedUpdateTask.h"
#include "Game/ParticleUpdateTask.h"
#include "Game/WorldManager.h"
#include "Game/Drawable/DrawableObj.h"
#include "NL/gl/gl.h"
#include "NL/nlFile.h"
#include "NL/nlString.h"

class NisPlayer : public InterpreterCore
{
public:
    static NisPlayer* Instance();
    void SetExtraNameFilter(const char*);
    void Reset();
};

class Wiper
{
public:
    static Wiper& Instance();
    void Reset();
};

class ReplayChoreo : public InterpreterCore
{
public:
    static ReplayChoreo& Instance();
    void Reset();
};

class ReplayManager
{
public:
    static ReplayManager* Instance();
    void Flush();
};

extern unsigned long cupTrophyHash;
static const char* idleFun = "Idle";

// /**
//  * Offset/Address/Size: 0x60 | 0x80127308 | size: 0x8
//  */
// void LexicalCast<const char*, const char*>(const char* const&)
// {
// }

// /**
//  * Offset/Address/Size: 0x48 | 0x801272F0 | size: 0x18
//  */
// void LexicalCast<const char*, bool>(const bool&)
// {
// }

// /**
//  * Offset/Address/Size: 0x24 | 0x801272CC | size: 0x24
//  */
// void LexicalCast<const char*, int>(const int&)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x801272A8 | size: 0x24
//  */
// void LexicalCast<const char*, float>(const float&)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x801272A0 | size: 0x8
//  */
// void NISData::GetID()
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x801267BC | size: 0xAE4
//  */
// void Presentation::DoFunctionCall(unsigned int)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x80126750 | size: 0x6C
//  */
// void 0x801267BC..0x801272A0 | size: 0xAE4
// {
// }

Presentation::Presentation()
    : InterpreterCore(10)
{
    mByPassWasSkipped = false;
    mSkipPressed = false;
    mInsideByPass = false;
    mByPassing = false;
    mWaitingForCharacterDirectionSince = 0.0f;
    mTimeInFunction = 0.0f;
    mDisplayLetterBox = 0.0f;
    mLetterBoxDuration = 0.0f;
    mLetterBoxEnabled = false;
    mOverlayDelay = 0.0f;
    mOverlayDisplayLength = 0.0f;
    mOverlayDisplayed = false;
    mOverlayToDisplay = SCENE_INVALID;
    mInterruptWipe = NULL;
    mUseInterruptWipe = NULL;
    mQueuedFunction = NULL;
    mGoalQuality = HIGHLIGHT_QUALITY_EMPTY;
    unsigned long fileSize = 0;
    void* bc = nlLoadEntireFile("presentation.bc", &fileSize, 0x20, AllocateStart);
    LoadByteCode(bc);
    nlStrNCpy<char>(mCurrentFunction, idleFun, 64);
    mIsAllowedToSkip[0] = true;
    mIsAllowedToSkip[1] = true;
    mIsAllowedToSkip[2] = true;
    mIsAllowedToSkip[3] = true;
}

/**
 * Offset/Address/Size: 0x1E58 | 0x8012663C | size: 0x114
 */
Presentation& Presentation::Instance()
{
    static Presentation instance;
    return instance;
}

/**
 * Offset/Address/Size: 0x1D18 | 0x801264FC | size: 0x140
 */
void ReadTrophyTexture(void* data, unsigned long size, void* userData)
{
    Presentation& inst = Presentation::Instance();
    inst.mTrophyTextureLoaded = true;
    glEndLoadTextureBundle(data, size);
}

/**
 * Offset/Address/Size: 0x1CA8 | 0x8012648C | size: 0x70
 */
void ReadTrophyModel(void* data, unsigned long size, void* userData)
{
    unsigned long localVar = 0;
    glModel* model = glEndLoadModel(data, size, &localVar);

    int localVar2 = 0;
    WorldManager::s_World->LoadGeometry(model, localVar, true, true, &cupTrophyHash, &localVar2, true);

    DrawableObject* obj = WorldManager::s_World->FindDrawableObject(cupTrophyHash);
    obj->m_uObjectFlags &= ~1;
}

/**
 * Offset/Address/Size: 0x1848 | 0x8012602C | size: 0x460
 */
void Presentation::LoadTrophyModel()
{
}

/**
 * Offset/Address/Size: 0x14EC | 0x80125CD0 | size: 0x35C
 */
void Presentation::Finish()
{
}

/**
 * Offset/Address/Size: 0xE70 | 0x80125654 | size: 0x67C
 */
void Presentation::Update(float)
{
}

/**
 * Offset/Address/Size: 0xDBC | 0x801255A0 | size: 0xB4
 */
bool Presentation::DuringEndOfGamePresentation() const
{
    if (nlStrCmp<char>(mCurrentFunction, "ImplGameEnd") == 0)
        return true;
    if (nlStrCmp<char>(mCurrentFunction, "GameEndNoSuddenDeath") == 0)
        return true;
    if (nlStrCmp<char>(mCurrentFunction, "GoalSuddenDeath") == 0)
        return true;
    if (nlStrCmp<char>(mCurrentFunction, "PlayHighlight") == 0)
        return true;
    if (nlStrCmp<char>(mCurrentFunction, "PlayCupThrophy") == 0)
        return true;
    return false;
}

/**
 * Offset/Address/Size: 0xCF0 | 0x801254D4 | size: 0xCC
 */
void Presentation::Call(const char* functionName, const char* nisFilter)
{
    FixedUpdateTask::mTimeScale = 1.0f;
    ParticleUpdateTask::SetTimeScale(1.0f);

    if (nlStrCmp<char>(idleFun, mCurrentFunction) != 0 && nlStrCmp<char>(idleFun, functionName) != 0)
    {
        mQueuedFunction = functionName;
        return;
    }

    nlStrNCpy<char>(mCurrentFunction, functionName, 64);
    mSkipPressed = false;
    mInsideByPass = false;
    mByPassing = false;
    mInterruptWipe = 0;
    mUseInterruptWipe = 0;
    mTimeInFunction = 0.0f;

    NisPlayer::Instance()->SetExtraNameFilter(nisFilter);
    CallFunction(nlStringHash(functionName));
}
/**
 * Offset/Address/Size: 0x57C | 0x80124D60 | size: 0x774
 */
void Presentation::EventHandler(Event*)
{
}

/**
 * Offset/Address/Size: 0x3D0 | 0x80124BB4 | size: 0x1AC
 */
void Presentation::PlayOverlay(const char*, float, float)
{
}

/**
 * Offset/Address/Size: 0x36C | 0x80124B50 | size: 0x64
 */
void Presentation::StopOverlay()
{
    if (mOverlayDisplayed)
    {
        nlSingleton<OverlayManager>::s_pInstance->SetVisible(mOverlayToDisplay, false, false);
    }
    mOverlayDisplayed = false;
    mOverlayToDisplay = SCENE_INVALID;
    mOverlayDisplayLength = 0.0f;
    mOverlayDelay = 0.0f;
}

/**
 * Offset/Address/Size: 0x19C | 0x80124980 | size: 0x1D0
 */
void CupWinStingerDone()
{
}

/**
 * Offset/Address/Size: 0x60 | 0x80124844 | size: 0x13C
 */
void Presentation::Reset()
{
    mIsAllowedToSkip[0] = true;
    mIsAllowedToSkip[1] = true;
    mIsAllowedToSkip[2] = true;
    mIsAllowedToSkip[3] = true;

    FixedUpdateTask::mTimeScale = 1.0f;
    const char* functionName = idleFun;
    ParticleUpdateTask::SetTimeScale(1.0f);

    if (nlStrCmp<char>(idleFun, mCurrentFunction) != 0 && nlStrCmp<char>(idleFun, functionName) != 0)
    {
        mQueuedFunction = functionName;
    }
    else
    {
        nlStrNCpy<char>(mCurrentFunction, functionName, 64);
        mSkipPressed = false;
        mInsideByPass = false;
        mByPassing = false;
        mInterruptWipe = 0;
        mUseInterruptWipe = 0;
        mTimeInFunction = 0.0f;

        NisPlayer::Instance()->SetExtraNameFilter("");
        CallFunction(nlStringHash(functionName));
    }

    mQueuedFunction = 0;
    mOverlayDisplayed = false;
    if (mOverlayDisplayed)
    {
        nlSingleton<OverlayManager>::s_pInstance->SetVisible(mOverlayToDisplay, false, false);
    }
    mOverlayDisplayed = false;
    mOverlayToDisplay = SCENE_INVALID;
    mOverlayDisplayLength = 0.0f;
    mOverlayDelay = 0.0f;

    Wiper::Instance().Reset();
    NisPlayer::Instance()->Reset();
    ReplayChoreo::Instance().Reset();
    ReplayManager::Instance()->Flush();
}
