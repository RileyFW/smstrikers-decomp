#include "Game/SH/SHTitleScreen.h"
#include "Game/GameSceneManager.h"
#include "Game/FE/feSceneManager.h"
#include "Game/FE/feFinder.h"
#include "Game/FE/feMusic.h"
#include "Game/Audio/AudioLoader.h"
#include "Game/FE/tlComponentInstance.h"

// /**
//  * Offset/Address/Size: 0x2D4 | 0x800AD39C | size: 0x15C
//  */
// void FEFinder<TLComponentInstance, 4>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long,
//                                                          unsigned long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x250 | 0x800AD318 | size: 0x84
//  */
// void FEFinder<TLComponentInstance, 4>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned
// long,
//                                                       unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x218 | 0x800AD2E0 | size: 0x38
//  */
// void FEFinder<TLComponentInstance, 4>::Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher,
//                                                      InlineHasher)
// {
// }

// /**
//  * Offset/Address/Size: 0xBC | 0x800AD184 | size: 0x15C
//  */
// void FEFinder<TLTextInstance, 3>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned
// long,
//                                                     unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x38 | 0x800AD100 | size: 0x84
//  */
// void FEFinder<TLTextInstance, 3>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long,
//                                                  unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x800AD0C8 | size: 0x38
//  */
// void FEFinder<TLTextInstance, 3>::Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher,
//                                                 InlineHasher)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x800AD05C | size: 0x6C
//  */
// void 0x800AD0C8..0x800AD4F8 | size : 0x430
// {
// }

/**
 * Offset/Address/Size: 0x9F8 | 0x800ACFB4 | size: 0xA8
 */
void StartMovieCB()
{
    BaseSceneHandler* handler;
    u32 sceneCount;

    if (GameSceneManager::Instance() != NULL)
    {
        sceneCount = GameSceneManager::Instance()->mCurrentStackDepth;
        if (sceneCount != 0)
        {
            handler = GameSceneManager::Instance()->mBaseSceneHandlerStack[sceneCount];
        }
        else
        {
            handler = NULL;
        }
        if ((handler != NULL) && (GameSceneManager::Instance()->GetSceneType(handler) == 2)
            && (handler->m_pFEScene->m_bValid != false))
        {
            GameSceneManager::Instance()->PopEntireStack();
            FESceneManager::Instance()->ForceImmediateStackProcessing();
            GameSceneManager::Instance()->Push((SceneList)0x35, SCREEN_NOTHING, false);
        }
    }
}

/**
 * Offset/Address/Size: 0x9F4 | 0x800ACFB0 | size: 0x4
 */
void DoNothingCallback()
{
}

/**
 * Offset/Address/Size: 0x7F0 | 0x800ACDAC | size: 0x204
 */
TitleScene::TitleScene()
{
}

/**
 * Offset/Address/Size: 0x794 | 0x800ACD50 | size: 0x5C
 */
TitleScene::~TitleScene()
{
}

static const char sPressStart[] = "pressstart";
static const char sPressStartText[] = "PressStart";

/**
 * Offset/Address/Size: 0x688 | 0x800ACC44 | size: 0x10C
 * TODO: 99.7% match - Find symbol mangling (const InlineHasher& vs InlineHasher by-value);
 *       build needs -sdata2 16 for correct SDA21 string placement
 */
void TitleScene::SceneCreated()
{
    FEMusic::StopStream();
    AudioLoader::PlayFETitleMusicWithFade();

    volatile InlineHasher hB, hA, h9, h8, h7, h6, h5, h4, h3, h2, h1, h0;
    h0.m_Hash = 0;
    h1.m_Hash = 0;
    h2.m_Hash = 0;
    h3.m_Hash = 0;
    h4.m_Hash = 0;
    h5.m_Hash = 0;
    h6.m_Hash = 0;
    h7.m_Hash = 0;
    u32 hash = nlStringLowerHash("title_screen_fe");
    h8.m_Hash = hash;
    h9.m_Hash = hash;
    hash = nlStringLowerHash(sPressStart);
    hB.m_Hash = hash;
    hA.m_Hash = hash;

    TLComponentInstance* comp = FEFinder<TLComponentInstance, 4>::Find<TLSlide>(
        m_pFEPresentation->m_currentSlide,
        (const InlineHasher&)hB,
        (const InlineHasher&)h9,
        (const InlineHasher&)h7,
        (const InlineHasher&)h5,
        (const InlineHasher&)h3,
        (const InlineHasher&)h1);

    volatile InlineHasher g7, g6, g5, g4, g3, g2, g1, g0;
    g0.m_Hash = 0;
    h1.m_Hash = 0;
    g1.m_Hash = 0;
    h3.m_Hash = 0;
    g2.m_Hash = 0;
    h5.m_Hash = 0;
    g3.m_Hash = 0;
    h7.m_Hash = 0;
    g4.m_Hash = 0;
    g5.m_Hash = 0;
    hash = nlStringLowerHash(sPressStartText);
    g6.m_Hash = hash;
    g7.m_Hash = hash;

    mTextPressStart = FEFinder<TLTextInstance, 3>::Find<TLSlide>(
        comp->GetActiveSlide(),
        (const InlineHasher&)g7,
        (const InlineHasher&)g5,
        (const InlineHasher&)h7,
        (const InlineHasher&)h5,
        (const InlineHasher&)h3,
        (const InlineHasher&)h1);
}

/**
 * Offset/Address/Size: 0x254 | 0x800AC810 | size: 0x434
 */
void TitleScene::Update(float)
{
}

/**
 * Offset/Address/Size: 0x0 | 0x800AC5BC | size: 0x254
 */
void TitleScene::StartIntroMovie()
{
}
