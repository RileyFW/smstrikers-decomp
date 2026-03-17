#include "Game/SH/SHOptions.h"
#include "Game/FE/feMusic.h"
#include "Game/GameInfo.h"
#include "Game/SH/SHCredits.h"

// /**
//  * Offset/Address/Size: 0x0 | 0x800B5004 | size: 0x40
//  */
// void Bind<void, Detail::MemFunImpl<void, void (OptionsScene::*)(eMenuState)>, OptionsScene*, eMenuState>(
//     Detail::MemFunImpl<void, void (OptionsScene::*)(eMenuState)>, OptionsScene* const&, const eMenuState&)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x800B4FE8 | size: 0x1C
//  */
// void MemFun<OptionsScene, void, eMenuState>(void (OptionsScene::*)(eMenuState))
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x800B4F8C | size: 0x5C
//  */
// void Function1<void, TLComponentInstance*>::FunctorImpl<
//     BindExp2<void, Detail::MemFunImpl<void, void (OptionsScene::*)(eMenuState)>, OptionsScene*, eMenuState>>::~FunctorImpl()
// {
// }

// /**
//  * Offset/Address/Size: 0x2D4 | 0x800B4E30 | size: 0x15C
//  */
// void FEFinder<TLInstance, 4>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long,
//                                                 unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x250 | 0x800B4DAC | size: 0x84
//  */
// void FEFinder<TLInstance, 4>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long,
//                                              unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x218 | 0x800B4D74 | size: 0x38
//  */
// void FEFinder<TLInstance, 4>::Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher)
// {
// }

// /**
//  * Offset/Address/Size: 0xBC | 0x800B4C18 | size: 0x15C
//  */
// void FEFinder<TLComponentInstance, 4>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long,
//                                                          unsigned long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x38 | 0x800B4B94 | size: 0x84
//  */
// void FEFinder<TLComponentInstance, 4>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned
// long,
//                                                       unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x800B4B5C | size: 0x38
//  */
// void FEFinder<TLComponentInstance, 4>::Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher,
//                                                      InlineHasher)
// {
// }

// /**
//  * Offset/Address/Size: 0x80 | 0x800B4B28 | size: 0x34
//  */
// void Function1<void, TLComponentInstance*>::FunctorImpl<BindExp2<void, Detail::MemFunImpl<void, void (OptionsScene::*)(eMenuState)>,
//                                                                  OptionsScene*, eMenuState>>::operator()(TLComponentInstance*)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x800B4AA8 | size: 0x80
//  */
// void Function1<void, TLComponentInstance*>::FunctorImpl<
//     BindExp2<void, Detail::MemFunImpl<void, void (OptionsScene::*)(eMenuState)>, OptionsScene*, eMenuState>>::Clone() const
// {
// }

s32 OptionsScene::mLastSelectedIndex;

/**
 * Offset/Address/Size: 0x1460 | 0x800B4A1C | size: 0x8C
 */
void ApplyChangesCB()
{
    OptionsScene* scene = (OptionsScene*)nlSingleton<GameSceneManager>::s_pInstance->GetScene(SCENE_OPTIONS);

    if (scene->m_curMenuState == MS_AUDIO)
    {
        OptionsAudioMenuV2* subMenuBytes = (OptionsAudioMenuV2*)scene->m_subMenu;
        if (subMenuBytes->mbUpdateMode)
        {
            FEPopupMenu* popup = (FEPopupMenu*)nlSingleton<GameSceneManager>::s_pInstance->Push(SCENE_POPUP_MENU, SCREEN_NOTHING, false);
            popup->Create(POPUP_APPLYING_AUDIO);
            scene->mPopupResult = PR_APPLY_DELAYED_AUDIO_CHANGES;
            return;
        }
    }

    scene->mPopupResult = PR_APPLY_CHANGES;
}

/**
 * Offset/Address/Size: 0x1430 | 0x800B49EC | size: 0x30
 */
void RevertChangesCB()
{
    OptionsScene* scene = (OptionsScene*)nlSingleton<GameSceneManager>::s_pInstance->GetScene(SCENE_OPTIONS);
    scene->mPopupResult = PR_REVERT_CHANGES;
}

/**
 * Offset/Address/Size: 0x1304 | 0x800B48C0 | size: 0x12C
 */
OptionsScene::OptionsScene()
{
}

/**
 * Offset/Address/Size: 0x123C | 0x800B47F8 | size: 0xC8
 */
OptionsScene::~OptionsScene()
{
    if (m_subMenu != NULL)
    {
        delete m_subMenu;
    }
}

/**
 * Offset/Address/Size: 0xB5C | 0x800B4118 | size: 0x6E0
 */
void OptionsScene::SceneCreated()
{
    FORCE_DONT_INLINE;
}

/**
 * Offset/Address/Size: 0xAF4 | 0x800B40B0 | size: 0x68
 */
void OptionsScene::Update(float dt)
{
    BaseSceneHandler::Update(dt);
    mButtons.CentreButtons();

    if (m_curMenuState == MS_MAIN)
    {
        UpdateForMain(dt);
    }
    else
    {
        UpdateForSubOptionMenus(dt);
    }
}

/**
 * Offset/Address/Size: 0x6EC | 0x800B3CA8 | size: 0x408
 */
void OptionsScene::UpdateForMain(float)
{
    FORCE_DONT_INLINE;
}

/**
 * Offset/Address/Size: 0x268 | 0x800B3824 | size: 0x484
 */
void OptionsScene::UpdateForSubOptionMenus(float)
{
    FORCE_DONT_INLINE;
}

/**
 * Offset/Address/Size: 0x0 | 0x800B35BC | size: 0x268
 */
void OptionsScene::ChangeMenuState(eMenuState newState)
{
    FEPresentation* pres = m_pFEScene->m_pFEPackage->GetPresentation();

    if (m_subMenu != NULL)
    {
        delete m_subMenu;
        m_subMenu = NULL;
    }

    switch (newState)
    {
    case MS_MAIN:
    {
        mMenuItems.mCurrentIndex = mLastSelectedIndex;

        int idx = mMenuItems.mCurrentIndex;
        Tag tag = mMenuItems.mMenuItems[idx].mCallbacks[1].mTag;

        if (((u32)((-((s32)tag)) | tag) >> 31) != 0)
        {
            TLComponentInstance* item = mMenuItems.mMenuItems[idx].mType;

            if (tag == FREE_FUNCTION)
            {
                mMenuItems.mMenuItems[idx].mCallbacks[1].mFreeFunction(item);
            }
            else
            {
                (*mMenuItems.mMenuItems[idx].mCallbacks[1].mFunctor)(item);
            }
        }
        break;
    }
    case MS_AUDIO:
        m_subMenu = new ((OptionsAudioMenuV2*)nlMalloc(sizeof(OptionsAudioMenuV2), 8, false))
            OptionsAudioMenuV2(pres, ButtonComponent::BS_B_ONLY, nlSingleton<GameInfoManager>::s_pInstance->mUserInfo.mAudioOptions);
        break;
    case MS_VISUAL:
        m_subMenu = new ((OptionsVisualMenuV2*)nlMalloc(sizeof(OptionsVisualMenuV2), 8, false))
            OptionsVisualMenuV2(pres, ButtonComponent::BS_B_ONLY, nlSingleton<GameInfoManager>::s_pInstance->mUserInfo.mVisualOptions);
        break;
    case MS_GAMEPLAY:
    {
        bool showLegend = nlSingleton<GameInfoManager>::s_pInstance->IsLegendSkillUnlocked();
        m_subMenu = new ((OptionsGameplayMenuV2*)nlMalloc(sizeof(OptionsGameplayMenuV2), 8, false))
            OptionsGameplayMenuV2(pres,
                ButtonComponent::BS_B_ONLY,
                nlSingleton<GameInfoManager>::s_pInstance->mUserInfo.mGameplayOptions,
                !showLegend ? 4 : -1);
        break;
    }
    case MS_CHEATS:
        m_subMenu = new ((OptionsCheatsMenu*)nlMalloc(sizeof(OptionsCheatsMenu), 8, false))
            OptionsCheatsMenu(pres, ButtonComponent::BS_B_ONLY, nlSingleton<GameInfoManager>::s_pInstance->mUserInfo.mCheatOptions);
        break;
    case MS_SAVE_LOAD:
        m_subMenu = new ((OptionsSaveLoad*)nlMalloc(sizeof(OptionsSaveLoad), 8, false))
            OptionsSaveLoad(pres, ButtonComponent::BS_A_AND_B);
        break;
    case MS_NUMMENUSTATES:
        nlSingleton<GameSceneManager>::s_pInstance->PopEntireStack();
        nlSingleton<GameSceneManager>::s_pInstance->Push(SCENE_CREDITS, SCREEN_NOTHING, false);
        CreditScene::mNextScene = SCENE_OPTIONS;
        FEMusic::StopStream();
        break;
    default:
        break;
    }

    m_curMenuState = newState;
}
