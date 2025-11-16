#include "Game/SH/SHLesson.h"
#include "Game/BaseGameSceneManager.h"
#include "Game/FE/FEAudio.h"
#include "Game/FE/feInput.h"
#include "Game/FE/feManager.h"
#include "Game/FE/tlComponentInstance.h"
#include "Game/FE/tlTextInstance.h"
#include "Game/OverlayManager.h"
#include "Game/SH/SHMoviePlayer.h"
#include "NL/nlPrint.h"
#include "NL/nlSingleton.h"
#include "types.h"

extern FEInput* g_pFEInput;

int LessonScene::mLessonIndex = -1;
// /**
//  * Offset/Address/Size: 0x2D4 | 0x8010ACF4 | size: 0x15C
//  */
// void FEFinder<TLTextInstance, 3>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned
// long,
//                                                     unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x250 | 0x8010AC70 | size: 0x84
//  */
// void FEFinder<TLTextInstance, 3>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long,
//                                                  unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x218 | 0x8010AC38 | size: 0x38
//  */
// void FEFinder<TLTextInstance, 3>::Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher,
//                                                 InlineHasher)
// {
// }

// /**
//  * Offset/Address/Size: 0xBC | 0x8010AADC | size: 0x15C
//  */
// void FEFinder<TLComponentInstance, 4>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long,
//                                                          unsigned long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x38 | 0x8010AA58 | size: 0x84
//  */
// void FEFinder<TLComponentInstance, 4>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned
// long,
//                                                       unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8010AA20 | size: 0x38
//  */
// void FEFinder<TLComponentInstance, 4>::Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher,
//                                                      InlineHasher)
// {
// }

/**
 * Offset/Address/Size: 0x508 | 0x8010A9B4 | size: 0x6C
 */
LessonScene::LessonScene()
    : mHudScene(nullptr)
{
}

/**
 * Offset/Address/Size: 0x490 | 0x8010A93C | size: 0x78
 */
LessonScene::~LessonScene()
{
}

/**
 * Offset/Address/Size: 0x8 | 0x8010A4B4 | size: 0x1D4
 */
void LessonScene::Update(float fDeltaT)
{
    MoviePlayerScene* scene; // r31
    char filename[128];      // r1+0x8

    BaseSceneHandler::Update(fDeltaT);
    this->mButtons.CentreButtons();
    if (nlSingleton<OverlayManager>::s_pInstance->mCurrentStackDepth != 0)
    {
        scene = (MoviePlayerScene*)nlSingleton<OverlayManager>::s_pInstance->mBaseSceneHandlerStack[nlSingleton<OverlayManager>::s_pInstance->mCurrentStackDepth - 1];
    }
    else
    {
        scene = nullptr;
    }

    if (scene == (MoviePlayerScene*)this)
    {
        if (this->mButtons.mButtonInstance)
        {
            this->mButtons.mButtonInstance->m_bVisible = true;
        }
    }
    else
    {
        if (this->mButtons.mButtonInstance)
        {
            this->mButtons.mButtonInstance->m_bVisible = false;
        }
    }
    if (g_pFEInput->JustPressed(FE_ALL_PADS, 0x100, false, nullptr))
    {
        scene = (MoviePlayerScene*)nlSingleton<OverlayManager>::s_pInstance->Push(IGSCENE_LESSON_MOVIE_PLAYER, SCREEN_FORWARD, false);
        nlSNPrintf(filename, 0x80, "movies/lesson%d.thp", mLessonIndex);
        scene->SetMovieDetails(filename, true, false);
        scene->mNextScene = IGSCENE_LESSON;
        scene->mPushWithPop = false;
        g_pFEInput->PushExclusiveInputLock(scene, -1);
        FEAudio::PlayAnimAudioEvent("sfx_accept", NULL);
        return;
    }
    if (g_pFEInput->JustPressed(FE_ALL_PADS, 0x200, false, nullptr))
    {
        scene = (MoviePlayerScene*)nlSingleton<OverlayManager>::s_pInstance->Push(IGSCENE_LESSON_SELECT, SCREEN_BACK, true);
        scene->m_bVisible = true; // Todo: Find offset 0x2b2 :pray:
        FEAudio::PlayAnimAudioEvent("sfx_back", NULL);
        return;
    }
    if (g_pFEInput->JustPressed(FE_ALL_PADS, 0x800, false, nullptr))
    {
        FrontEnd::ExitMenuState();
        FEAudio::PlayAnimAudioEvent("sfx_back", NULL);
        FEAudio::PlayAnimAudioEvent("sfx_screen_back", NULL);
    }
}

/**
 * Offset/Address/Size: 0x1DC | 0x8010A688 | size: 0x2B4
 */
void LessonScene::SceneCreated()
{
    char title[64];                       // r1+0xC0
    char body[64];                        // r1+0x80
    TLTextInstance* titletextinstance;    // r28
    TLTextInstance* bodytextinstance;     // r31
    TLComponentInstance* buttonComponent; // r0
    nlSNPrintf("LOC_TUTORIAL_INSTRUCTION_TITLE_%d", mLessonIndex, title, 0x40);
    nlSNPrintf("LOC_TUTORIAL_INSTRUCTION_BODY_%d", mLessonIndex, body, 0x40);
}

/**
 * Offset/Address/Size: 0x0 | 0x8010A4AC | size: 0x8
 */
void LessonScene::SetLesson(int index)
{
    LessonScene::mLessonIndex = index;
}
