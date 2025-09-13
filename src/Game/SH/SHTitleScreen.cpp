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
    BaseSceneHandler* var_r31;
    u32 temp_r0;

    if (GameSceneManager::s_pInstance.Instance() != NULL)
    {
        // if (s_pInstance__31nlSingleton<16GameSceneManager>.unk0 != NULL)
        // {
        temp_r0 = GameSceneManager::s_pInstance.Instance()->m_count;
        if (temp_r0 != 0)
        {
            var_r31 = *GameSceneManager::s_pInstance.Instance()->m_handlers + temp_r0;
            // = (s_pInstance__31nlSingleton<16GameSceneManager>.unk0 + (temp_r0 * 4))->unk84;
        }
        else
        {
            var_r31 = NULL;
        }
        if ((var_r31 != NULL) && (GameSceneManager::s_pInstance.Instance()->GetSceneType(var_r31) == 2)
            && (var_r31->m_pFEScene->m_unk_0x08 != false))
        {
            GameSceneManager::s_pInstance.Instance()->PopEntireStack();
            FESceneManager::s_pInstance.Instance()->ForceImmediateStackProcessing();
            GameSceneManager::s_pInstance.Instance()->Push((SceneList)0x35, SCREEN_NOTHING, false);

            // PopEntireStack__20BaseGameSceneManagerFv(s_pInstance__31nlSingleton<16GameSceneManager>.unk0);
            // ForceImmediateStackProcessing__14FESceneManagerFv(s_pInstance__29nlSingleton<14FESceneManager>.unk0);
            // s_pInstance__31nlSingleton<16GameSceneManager>.unk0->unk0->unkC(s_pInstance__31nlSingleton<16GameSceneManager>.unk0, 0x35, 0,
            //                                                                 0);
        }
        // }
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
