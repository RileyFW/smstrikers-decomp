#include "Game/SH/SHMoviePlayer.h"
#include "Dolphin/dolphin.h"
#include "Game/BaseGameSceneManager.h"
#include "Game/BaseSceneHandler.h"
#include "Game/FE/FEAudio.h"
#include "Game/FE/feButtonComponent.h"
#include "Game/FE/feInput.h"
#include "Game/GameInfo.h"
#include "Game/GameSceneManager.h"
#include "Game/OverlayManager.h"
#include "NL/gl/gl.h"
#include "types.h"

extern bool g_bRenderWorld;
extern bool g_e3_Build;
extern FEInput* g_pFEInput;

// /**
//  * Offset/Address/Size: 0x2D4 | 0x800BD840 | size: 0x15C
//  */
// void FEFinder<TLImageInstance, 2>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned
// long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x250 | 0x800BD7BC | size: 0x84
//  */
// void FEFinder<TLImageInstance, 2>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long,
// unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x218 | 0x800BD784 | size: 0x38
//  */
// void FEFinder<TLImageInstance, 2>::Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher,
// InlineHasher)
// {
// }

// /**
//  * Offset/Address/Size: 0xBC | 0x800BD628 | size: 0x15C
//  */
// void FEFinder<TLComponentInstance, 4>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long,
// unsigned long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x38 | 0x800BD5A4 | size: 0x84
//  */
// void FEFinder<TLComponentInstance, 4>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned
// long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x800BD56C | size: 0x38
//  */
// void FEFinder<TLComponentInstance, 4>::Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher,
// InlineHasher)
// {
// }

/**
 * Offset/Address/Size: 0x81C | 0x800BD374 | size: 0x78
 */
MoviePlayerScene::MoviePlayerScene()
{
    mSwappedTexture = false;
    mMovieStarted = false;
    mMovieInstance = nullptr;
    mNextScene = SCENE_INVALID;
    mWithSound = false;
    mLoopMovie = false;
    mPushWithPop = true;
    mMovieFilename[0] = nullptr;
    if (nlSingleton<GameSceneManager>::s_pInstance)
    {
        mGameSceneManager = nlSingleton<GameSceneManager>::s_pInstance;
        return;
    }
    mGameSceneManager = nlSingleton<OverlayManager>::s_pInstance;
}

/**
 * Offset/Address/Size: 0x778 | 0x800BD2D0 | size: 0xA4
 */
MoviePlayerScene::~MoviePlayerScene()
{
    if (nlSingleton<GameInfoManager>::s_pInstance->mIsInStrikers101Mode)
    {
        g_bRenderWorld = true;
    }
    if (g_pFEInput->HasInputLock(this))
    {
        g_pFEInput->PopExclusiveInputLock(this);
    }
}

/**
 * Offset/Address/Size: 0x74C | 0x800BD2A4 | size: 0x2C
 */
void MoviePlayerScene::SceneCreated()
{
    OverrideMovieDimensions();
}

/**
 * Offset/Address/Size: 0x6F0 | 0x800BD248 | size: 0x5C
 */
void MoviePlayerScene::SetMovieDetails(const char* filename, bool withsound, bool loopmovie)
{
    nlStrNCpy<char>((char*)mMovieFilename, filename, 0x80);
    mMovieFilename[127] = 0;
    mWithSound = withsound;
    mLoopMovie = loopmovie;
}

/**
 * Offset/Address/Size: 0x214 | 0x800BCD6C | size: 0x4DC
 */
void MoviePlayerScene::Update(float fDeltaT)
{
    FORCE_DONT_INLINE; // Todo: Finish Implementing
    u32 moviehandle;

    BaseSceneHandler::Update(fDeltaT);
    if (g_e3_Build || (OSGetConsoleType() & 0x20000000))
    {
        if (mPushWithPop)
        {
            MoviePlayerScene* temp_r3 = (MoviePlayerScene*)mGameSceneManager->Push(mNextScene, SCREEN_NOTHING, true);
            if (mNextScene == SCENE_TITLE)
            {
                temp_r3->mNextScene = SCENE_MARIO_BACKGROUND;
            }
            PlayScreenForwardSFX();
        }
        mGameSceneManager->Pop();
        PlayScreenBackSFX();
        return;
    }
    if (!this->mMovieStarted)
    {
        // this->mMovieStarted = MovieStart()
    }
}

/**
 * Offset/Address/Size: 0x1A4 | 0x800BCCFC | size: 0x70
 */
bool MoviePlayerScene::CheckMoviePlayerAbort()
{
    bool isAbort = false;

    if (g_pFEInput->JustPressed(FE_ALL_PADS, 0x24, true, nullptr) || g_pFEInput->JustPressed(FE_ALL_PADS, 0x100, false, nullptr))
    {
        isAbort = true;
    }
    return isAbort;
}

/**
 * Offset/Address/Size: 0x178 | 0x800BCCD0 | size: 0x2C
 */
void MoviePlayerScene::PlayScreenForwardSFX()
{
    FEAudio::PlayAnimAudioEvent("sfx_screen_forward", false);
}

/**
 * Offset/Address/Size: 0x14C | 0x800BCCA4 | size: 0x2C
 */
void MoviePlayerScene::PlayScreenBackSFX()
{
    FEAudio::PlayAnimAudioEvent("sfx_screen_back", false);
}

/**
 * Offset/Address/Size: 0x148 | 0x800BCCA0 | size: 0x4
 */
void MoviePlayerScene::OverrideMovieDimensions()
{
}

/**
 * Offset/Address/Size: 0x98 | 0x800BCBF0 | size: 0xB0
 */
void LessonMoviePlayerScene::SceneCreated()
{
    OverrideMovieDimensions();
}

/**
 * Offset/Address/Size: 0x64 | 0x800BCBBC | size: 0x34
 */
bool LessonMoviePlayerScene::CheckMoviePlayerAbort()
{
    return g_pFEInput->JustPressed(FE_ALL_PADS, 0x200, false, nullptr);
}

/**
 * Offset/Address/Size: 0x4 | 0x800BCB5C | size: 0x60
 */
void LessonMoviePlayerScene::Update(float fDeltaT)
{
    MoviePlayerScene::Update(fDeltaT);
    if (mMovieStarted)
    {
        mButtonComponent.CentreButtons();
        return;
    }
    if (mButtonComponent.mButtonInstance != nullptr)
    {
        mButtonComponent.mButtonInstance->m_bVisible = false;
    }
    glDiscardFrame(2);
}

/**
 * Offset/Address/Size: 0x0 | 0x800BCB58 | size: 0x4
 */
void NLGLogoMovieScene::OverrideMovieDimensions()
{
}
