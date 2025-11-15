#include "Game/SH/SHTitleScreen.h"
#include "Game/GameSceneManager.h"
#include "Game/FE/FESceneManager.h"

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

/**
 * Offset/Address/Size: 0x688 | 0x800ACC44 | size: 0x10C
 */
void TitleScene::SceneCreated()
{
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
