#include "Game/SH/SHCredits.h"

// /**
//  * Offset/Address/Size: 0x570 | 0x80110374 | size: 0x15C
//  */
// void FEFinder<TLTextInstance, 3>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned
// long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x4EC | 0x801102F0 | size: 0x84
//  */
// void FEFinder<TLTextInstance, 3>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long,
// unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x468 | 0x8011026C | size: 0x84
//  */
// void FEFinder<TLTextInstance, 3>::_Find<FEPresentation>(FEPresentation*, unsigned long, unsigned long, unsigned long, unsigned long,
// unsigned long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x430 | 0x80110234 | size: 0x38
//  */
// void FEFinder<TLTextInstance, 3>::Find<FEPresentation>(FEPresentation*, InlineHasher, InlineHasher, InlineHasher, InlineHasher,
// InlineHasher, InlineHasher)
// {
// }

// /**
//  * Offset/Address/Size: 0x2D4 | 0x801100D8 | size: 0x15C
//  */
// void FEFinder<TLImageInstance, 2>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned
// long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x250 | 0x80110054 | size: 0x84
//  */
// void FEFinder<TLImageInstance, 2>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long,
// unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x218 | 0x8011001C | size: 0x38
//  */
// void FEFinder<TLImageInstance, 2>::Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher,
// InlineHasher)
// {
// }

// /**
//  * Offset/Address/Size: 0xBC | 0x8010FEC0 | size: 0x15C
//  */
// void FEFinder<TLComponentInstance, 4>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long,
// unsigned long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x38 | 0x8010FE3C | size: 0x84
//  */
// void FEFinder<TLComponentInstance, 4>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned
// long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8010FE04 | size: 0x38
//  */
// void FEFinder<TLComponentInstance, 4>::Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher,
// InlineHasher)
// {
// }

/**
 * Offset/Address/Size: 0xBCC | 0x8010FD28 | size: 0xDC
 */
CreditScene::CreditScene()
{
}

/**
 * Offset/Address/Size: 0xB40 | 0x8010FC9C | size: 0x8C
 */
CreditScene::~CreditScene()
{
}

/**
 * Offset/Address/Size: 0xB20 | 0x8010FC7C | size: 0x20
 */
void CreditScene::SceneCreated()
{
}

/**
 * Offset/Address/Size: 0xA80 | 0x8010FBDC | size: 0xA0
 */
void CreditScene::Update(float)
{
}

/**
 * Offset/Address/Size: 0x978 | 0x8010FAD4 | size: 0x108
 */
void CreditScene::SetupForPhase()
{
}

/**
 * Offset/Address/Size: 0x94C | 0x8010FAA8 | size: 0x2C
 */
void CreditScene::GotoNextPhase()
{
    FORCE_DONT_INLINE;
    mCreditParser.mFileData++;
    SetupForPhase();
}

/**
 * Offset/Address/Size: 0x6E4 | 0x8010F840 | size: 0x268
 */
void CreditScene::SetupForCredits()
{
    FORCE_DONT_INLINE;
}

/**
 * Offset/Address/Size: 0x60C | 0x8010F768 | size: 0xD8
 */
void CreditScene::SetupForNLGMovie()
{
}

/**
 * Offset/Address/Size: 0x554 | 0x8010F6B0 | size: 0xB8
 */
void CreditScene::UpdateForCopyrightMessage(float)
{
}

/**
 * Offset/Address/Size: 0x1BC | 0x8010F318 | size: 0x398
 */
void CreditScene::UpdateForCredits(float)
{
}

/**
 * Offset/Address/Size: 0x104 | 0x8010F260 | size: 0xB8
 */
void CreditScene::UpdateForNintendoLogo(float)
{
}

/**
 * Offset/Address/Size: 0x98 | 0x8010F1F4 | size: 0x6C
 */
void CreditScene::UpdateForNLGMovie(float)
{
    if (FESceneManager::GetInstance()->AreAllScenesValid())
    {
        GameSceneManager* pGameSceneMgr = GameSceneManager::GetInstance();
        BaseSceneHandler* pCurrentScene;
        if (pGameSceneMgr->mCurrentStackDepth != 0)
        {
            pCurrentScene = pGameSceneMgr->mBaseSceneHandlerStack[pGameSceneMgr->mCurrentStackDepth - 1];
        }
        else
        {
            pCurrentScene = NULL;
        }
        if (pCurrentScene == this)
        {
            GotoNextPhase();
        }
    }
}

/**
 * Offset/Address/Size: 0x0 | 0x8010F15C | size: 0x98
 */
void CreditScene::GetWhiteFadeComponent()
{
}
