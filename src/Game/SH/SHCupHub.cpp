#include "Game/SH/SHCupHub.h"

#include "Game/GameSceneManager.h"
#include "Game/BaseGameSceneManager.h"

// /**
//  * Offset/Address/Size: 0x0 | 0x800F1F90 | size: 0x38
//  */
// void Bind<void, Detail::MemFunImpl<void, void (CupHubScene::*)()>, CupHubScene*>(Detail::MemFunImpl<void, void (CupHubScene::*)()>,
// CupHubScene* const&)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x800F1F74 | size: 0x1C
//  */
// void MemFun<CupHubScene, void>(void (CupHubScene::*)())
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x800F1F18 | size: 0x5C
//  */
// void Function0<void>::FunctorImpl<BindExp1<void, Detail::MemFunImpl<void, void (CupHubScene::*)()>, CupHubScene*>>::~FunctorImpl()
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x800F1EB4 | size: 0x64
//  */
// TeamStats::TeamStats()
// {
// }

// /**
//  * Offset/Address/Size: 0x78 | 0x800F1E84 | size: 0x30
//  */
// void Function0<void>::FunctorImpl<BindExp1<void, Detail::MemFunImpl<void, void (CupHubScene::*)()>, CupHubScene*>>::operator()()
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x800F1E0C | size: 0x78
//  */
// void Function0<void>::FunctorImpl<BindExp1<void, Detail::MemFunImpl<void, void (CupHubScene::*)()>, CupHubScene*>>::Clone() const
// {
// }

// /**
//  * Offset/Address/Size: 0x680 | 0x800F1D88 | size: 0x84
//  */
// void FEFinder<TLComponentInstance, 4>::_Find<FEPresentation>(FEPresentation*, unsigned long, unsigned long, unsigned long, unsigned long,
// unsigned long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x648 | 0x800F1D50 | size: 0x38
//  */
// void FEFinder<TLComponentInstance, 4>::Find<FEPresentation>(FEPresentation*, InlineHasher, InlineHasher, InlineHasher, InlineHasher,
// InlineHasher, InlineHasher)
// {
// }

// /**
//  * Offset/Address/Size: 0x4EC | 0x800F1BF4 | size: 0x15C
//  */
// void FEFinder<TLComponentInstance, 4>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long,
// unsigned long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x468 | 0x800F1B70 | size: 0x84
//  */
// void FEFinder<TLComponentInstance, 4>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned
// long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x430 | 0x800F1B38 | size: 0x38
//  */
// void FEFinder<TLComponentInstance, 4>::Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher,
// InlineHasher)
// {
// }

// /**
//  * Offset/Address/Size: 0x2D4 | 0x800F19DC | size: 0x15C
//  */
// void FEFinder<TLTextInstance, 3>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned
// long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x250 | 0x800F1958 | size: 0x84
//  */
// void FEFinder<TLTextInstance, 3>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long,
// unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x218 | 0x800F1920 | size: 0x38
//  */
// void FEFinder<TLTextInstance, 3>::Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher,
// InlineHasher)
// {
// }

// /**
//  * Offset/Address/Size: 0xBC | 0x800F17C4 | size: 0x15C
//  */
// void FEFinder<TLImageInstance, 2>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned
// long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x38 | 0x800F1740 | size: 0x84
//  */
// void FEFinder<TLImageInstance, 2>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long,
// unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x800F1708 | size: 0x38
//  */
// void FEFinder<TLImageInstance, 2>::Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher,
// InlineHasher)
// {
// }

/**
 * Offset/Address/Size: 0x72C8 | 0x800F1024 | size: 0x6E4
 */
CupHubScene::CupHubScene(bool, bool)
{
}

/**
 * Offset/Address/Size: 0x7224 | 0x800F0F80 | size: 0xA4
 */
CupHubScene::~CupHubScene()
{
}

/**
 * Offset/Address/Size: 0x71C0 | 0x800F0F1C | size: 0x64
 */
void CupHubScene::SceneCreated()
{
    LoadCaptainImage();
    eHubState state = mHubState;
    switch (state)
    {
    case HUB_LEAGUE:
    case HUB_BOWSER_TRANSITION:
        CreateLeague();
        break;
    case HUB_KNOCKOUT2:
    case HUB_KNOCKOUT4:
    case HUB_KNOCKOUT8:
        CreateKnockout();
        break;
    default:
        break;
    }
}

/**
 * Offset/Address/Size: 0x69A4 | 0x800F0700 | size: 0x81C
 */
void CupHubScene::Update(float)
{
}

/**
 * Offset/Address/Size: 0x670C | 0x800F0468 | size: 0x298
 */
void CupHubScene::EndCup()
{
}

/**
 * Offset/Address/Size: 0x66C8 | 0x800F0424 | size: 0x44
 */
void CupHubScene::ReturnToMainMenu()
{
    nlSingleton<GameSceneManager>::s_pInstance->PopEntireStack();
    nlSingleton<GameSceneManager>::s_pInstance->Push(SCENE_MAIN_MENU, SCREEN_FORWARD, false);
}

/**
 * Offset/Address/Size: 0x5F08 | 0x800EFC64 | size: 0x7C0
 */
void CupHubScene::UpdateDisplayedStat()
{
}

/**
 * Offset/Address/Size: 0x4E34 | 0x800EEB90 | size: 0x10D4
 */
void CupHubScene::CreateLeague()
{
    FORCE_DONT_INLINE;
}

/**
 * Offset/Address/Size: 0x4018 | 0x800EDD74 | size: 0xE1C
 */
void CupHubScene::CreateBowserLeague()
{
}

/**
 * Offset/Address/Size: 0x32FC | 0x800ED058 | size: 0xD1C
 */
void CupHubScene::CreateKnockout()
{
    FORCE_DONT_INLINE;
}

/**
 * Offset/Address/Size: 0x2FF4 | 0x800ECD50 | size: 0x308
 */
void CupHubScene::UpdateLeague(float)
{
}

/**
 * Offset/Address/Size: 0x2A64 | 0x800EC7C0 | size: 0x590
 */
void CupHubScene::UpdateKnockout8(float)
{
}

/**
 * Offset/Address/Size: 0x2600 | 0x800EC35C | size: 0x464
 */
void CupHubScene::UpdateKnockout4(float)
{
}

/**
 * Offset/Address/Size: 0x1F6C | 0x800EBCC8 | size: 0x694
 */
void CupHubScene::UpdateKnockout2(float)
{
}

/**
 * Offset/Address/Size: 0x1860 | 0x800EB5BC | size: 0x70C
 */
void CupHubScene::UpdateProgressIndicator()
{
}

/**
 * Offset/Address/Size: 0x1698 | 0x800EB3F4 | size: 0x1C8
 */
void CupHubScene::ColourUserRow()
{
}

/**
 * Offset/Address/Size: 0x15C4 | 0x800EB320 | size: 0xD4
 */
void CupHubScene::HandleButtonComponent()
{
}

/**
 * Offset/Address/Size: 0x12EC | 0x800EB048 | size: 0x2D8
 */
void CupHubScene::SetRoundColours(eHubColour*, int)
{
}

/**
 * Offset/Address/Size: 0x1DC | 0x800E9F38 | size: 0x1110
 */
void CupHubScene::UpdateRoundMessage(bool)
{
}

/**
 * Offset/Address/Size: 0x0 | 0x800E9D5C | size: 0x1DC
 */
void CupHubScene::LoadCaptainImage()
{
    FORCE_DONT_INLINE;
}
