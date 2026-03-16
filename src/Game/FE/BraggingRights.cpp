#include "Game/FE/BraggingRights.h"
#include "Game/FE/FEAudio.h"
#include "Game/FE/feInput.h"
#include "Game/FE/feMusic.h"
#include "Game/GameInfo.h"
#include "Game/GameSceneManager.h"
#include "Game/SH/SHMainMenu.h"
#include "Game/SH/SHSaveLoad.h"

// /**
//  * Offset/Address/Size: 0xE10 | 0x800D6924 | size: 0x124
//  */
// void Format<BasicString<unsigned short, Detail::TempStringAllocator>, unsigned short[32], unsigned short[32]>(const BasicString<unsigned short, Detail::TempStringAllocator>&, const unsigned short(&)[32], const unsigned short(&)[32])
// {
// }

// /**
//  * Offset/Address/Size: 0x120 | 0x800D5C34 | size: 0xCF0
//  */
// void FormatImpl<BasicString<unsigned short, Detail::TempStringAllocator>>::operator%<const unsigned short*>(const unsigned short* const&)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x800D5B14 | size: 0x120
//  */
// void Format<BasicString<unsigned short, Detail::TempStringAllocator>, const unsigned short*, unsigned short[16]>(const BasicString<unsigned short, Detail::TempStringAllocator>&, const unsigned short* const&, const unsigned short(&)[16])
// {
// }

// /**
//  * Offset/Address/Size: 0x570 | 0x800D5ADC | size: 0x38
//  */
// void FEFinder<TLTextInstance, 3>::Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher)
// {
// }

// /**
//  * Offset/Address/Size: 0x538 | 0x800D5AA4 | size: 0x38
//  */
// void FEFinder<TLComponentInstance, 4>::Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher)
// {
// }

// /**
//  * Offset/Address/Size: 0x3DC | 0x800D5948 | size: 0x15C
//  */
// void FEFinder<TLTextInstance, 3>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x358 | 0x800D58C4 | size: 0x84
//  */
// void FEFinder<TLTextInstance, 3>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x2D4 | 0x800D5840 | size: 0x84
//  */
// void FEFinder<TLTextInstance, 3>::_Find<FEPresentation>(FEPresentation*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x29C | 0x800D5808 | size: 0x38
//  */
// void FEFinder<TLTextInstance, 3>::Find<FEPresentation>(FEPresentation*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher)
// {
// }

// /**
//  * Offset/Address/Size: 0x140 | 0x800D56AC | size: 0x15C
//  */
// void FEFinder<TLComponentInstance, 4>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0xBC | 0x800D5628 | size: 0x84
//  */
// void FEFinder<TLComponentInstance, 4>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x38 | 0x800D55A4 | size: 0x84
//  */
// void FEFinder<TLComponentInstance, 4>::_Find<FEPresentation>(FEPresentation*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x800D556C | size: 0x38
//  */
// void FEFinder<TLComponentInstance, 4>::Find<FEPresentation>(FEPresentation*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher)
// {
// }

/**
 * Offset/Address/Size: 0x34C8 | 0x800D54C4 | size: 0xA8
 */
BraggingRightsOverlay::BraggingRightsOverlay()
{
}

/**
 * Offset/Address/Size: 0x3368 | 0x800D5364 | size: 0x160
 */
BraggingRightsOverlay::~BraggingRightsOverlay()
{
}

/**
 * Offset/Address/Size: 0x2E3C | 0x800D4E38 | size: 0x52C
 */
void BraggingRightsOverlay::SceneCreated()
{
}

/**
 * Offset/Address/Size: 0x29A8 | 0x800D49A4 | size: 0x494
 */
void BraggingRightsOverlay::IngameSceneCreated()
{
}

/**
 * Offset/Address/Size: 0x23EC | 0x800D43E8 | size: 0x5BC
 */
void BraggingRightsOverlay::TournamentSceneCreated()
{
}

/**
 * Offset/Address/Size: 0x1EA0 | 0x800D3E9C | size: 0x54C
 */
void BraggingRightsOverlay::Update(float)
{
}

/**
 * Offset/Address/Size: 0x15A4 | 0x800D35A0 | size: 0x8FC
 */
void BraggingRightsOverlay::ChangeTicker(int)
{
}

/**
 * Offset/Address/Size: 0x153C | 0x800D3538 | size: 0x68
 */
BraggingRightsScene::BraggingRightsScene()
{
}

/**
 * Offset/Address/Size: 0x14C4 | 0x800D34C0 | size: 0x78
 */
BraggingRightsScene::~BraggingRightsScene()
{
}

/**
 * Offset/Address/Size: 0x2E4 | 0x800D22E0 | size: 0x11E0
 */
void BraggingRightsScene::SceneCreated()
{
}

/**
 * Offset/Address/Size: 0x0 | 0x800D1FFC | size: 0x2E4
 */
void BraggingRightsScene::Update(float fDeltaT)
{
    FEPresentation* presentation;
    GameInfoManager* info;
    SaveLoadScene* scene;
    float fadeEndTime;

    BaseSceneHandler::Update(fDeltaT);
    mButtons.CentreButtons();

    presentation = m_pFEScene->m_pFEPackage->GetPresentation();
    fadeEndTime = presentation->m_currentSlide->m_start + presentation->m_currentSlide->m_duration;

    if (presentation->m_currentSlide->m_time < fadeEndTime)
    {
        if (g_pFEInput->JustPressed(FE_ALL_PADS, 0x100, false, NULL)
            || g_pFEInput->JustPressed(FE_ALL_PADS, 0x200, false, NULL))
        {
            presentation->m_fadeDuration = fadeEndTime;
        }
    }
    else if (g_pFEInput->JustPressed(FE_ALL_PADS, 0x100, false, NULL))
    {
        SceneList nextScene = SCENE_MAIN_MENU;
        GameInfoManager::eGameModes mode;

        nlSingleton<GameSceneManager>::s_pInstance->PopEntireStack();

        info = nlSingleton<GameInfoManager>::s_pInstance;
        mode = info->mCurrentMode;
        if (mode == GameInfoManager::GM_BOWSER_CUP || mode == GameInfoManager::GM_SUPER_BOWSER_CUP)
        {
            if (mUserPlace == 0)
            {
                nextScene = SCENE_CREDITS;
                FEMusic::StopStream();
            }
        }

        if (SaveLoadScene::IsIOEnabled())
        {
            scene = (SaveLoadScene*)nlSingleton<GameSceneManager>::s_pInstance->Push(SCENE_SAVE, SCREEN_FORWARD, false);
            scene->mNextScene = nextScene;
        }
        else
        {
            nlSingleton<GameSceneManager>::s_pInstance->Push(nextScene, SCREEN_FORWARD, false);
        }

        SHMainMenu::mSnapMenuIntoPosition = false;
        SHMainMenu::mLastMenuItem = 0;
        FEAudio::PlayAnimAudioEvent("sfx_accept", false);
    }
    else if (g_pFEInput->JustPressed(FE_ALL_PADS, 0x200, false, NULL))
    {
        GameInfoManager::eGameModes mode;

        info = nlSingleton<GameInfoManager>::s_pInstance;
        mode = info->mCurrentMode;
        if (mode == GameInfoManager::GM_BOWSER_CUP)
        {
            nlSingleton<GameSceneManager>::s_pInstance->Push(SCENE_CUP_STANDINGS_FINAL_ANIM, SCREEN_BACK, true);
        }
        else if (mode == GameInfoManager::GM_SUPER_BOWSER_CUP)
        {
            nlSingleton<GameSceneManager>::s_pInstance->Push(SCENE_SUPER_CUP_STANDINGS_FINAL_ANIM, SCREEN_BACK, true);
        }
        else if (info->IsInTournamentMode() && info->mCustomTournamentInfo.m_tournMode == TM_KNOCKOUT)
        {
            nlSingleton<GameSceneManager>::s_pInstance->Push(SCENE_TOURNAMENT_STANDINGS_FINAL_ANIM, SCREEN_BACK, true);
        }
        else if (info->IsInRegularCupMode())
        {
            nlSingleton<GameSceneManager>::s_pInstance->Push(SCENE_CUP_STANDINGS, SCREEN_BACK, true);
        }
        else if (info->IsInSuperCupMode())
        {
            nlSingleton<GameSceneManager>::s_pInstance->Push(SCENE_SUPER_CUP_STANDINGS, SCREEN_BACK, true);
        }
        else
        {
            nlSingleton<GameSceneManager>::s_pInstance->Push(SCENE_TOURNAMENT_STANDINGS, SCREEN_BACK, true);
        }

        FEAudio::PlayAnimAudioEvent("sfx_back", false);
    }
}
