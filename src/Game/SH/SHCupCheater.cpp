#include "Game/SH/SHCupCheater.h"

// /**
//  * Offset/Address/Size: 0x0 | 0x800E9970 | size: 0x38
//  */
// void Bind<void, Detail::MemFunImpl<void, void (CupCheaterScene::*)()>, CupCheaterScene*>(Detail::MemFunImpl<void, void
// (CupCheaterScene::*)()>, CupCheaterScene* const&)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x800E9954 | size: 0x1C
//  */
// void MemFun<CupCheaterScene, void>(void (CupCheaterScene::*)())
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x800E98F8 | size: 0x5C
//  */
// void Function0<void>::FunctorImpl<BindExp1<void, Detail::MemFunImpl<void, void (CupCheaterScene::*)()>,
// CupCheaterScene*>>::~FunctorImpl()
// {
// }

// /**
//  * Offset/Address/Size: 0x78 | 0x800E98C8 | size: 0x30
//  */
// void Function0<void>::FunctorImpl<BindExp1<void, Detail::MemFunImpl<void, void (CupCheaterScene::*)()>, CupCheaterScene*>>::operator()()
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x800E9850 | size: 0x78
//  */
// void Function0<void>::FunctorImpl<BindExp1<void, Detail::MemFunImpl<void, void (CupCheaterScene::*)()>, CupCheaterScene*>>::Clone() const
// {
// }

// /**
//  * Offset/Address/Size: 0x358 | 0x800E96F4 | size: 0x15C
//  */
// void FEFinder<TLComponentInstance, 4>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long,
// unsigned long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x2D4 | 0x800E9670 | size: 0x84
//  */
// void FEFinder<TLComponentInstance, 4>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned
// long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x250 | 0x800E95EC | size: 0x84
//  */
// void FEFinder<TLComponentInstance, 4>::_Find<FEPresentation>(FEPresentation*, unsigned long, unsigned long, unsigned long, unsigned long,
// unsigned long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x218 | 0x800E95B4 | size: 0x38
//  */
// void FEFinder<TLComponentInstance, 4>::Find<FEPresentation>(FEPresentation*, InlineHasher, InlineHasher, InlineHasher, InlineHasher,
// InlineHasher, InlineHasher)
// {
// }

// /**
//  * Offset/Address/Size: 0xBC | 0x800E9458 | size: 0x15C
//  */
// void FEFinder<TLTextInstance, 3>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned
// long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x38 | 0x800E93D4 | size: 0x84
//  */
// void FEFinder<TLTextInstance, 3>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long,
// unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x800E939C | size: 0x38
//  */
// void FEFinder<TLTextInstance, 3>::Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher,
// InlineHasher)
// {
// }

/**
 * Offset/Address/Size: 0x1C00 | 0x800E9350 | size: 0x4C
 */
CupCheaterScene::CupCheaterScene()
{
}

/**
 * Offset/Address/Size: 0x1B80 | 0x800E92D0 | size: 0x80
 */
CupCheaterScene::~CupCheaterScene()
{
}

/**
 * Offset/Address/Size: 0x14D4 | 0x800E8C24 | size: 0x6AC
 */
void CupCheaterScene::SceneCreated()
{
}

/**
 * Offset/Address/Size: 0x1140 | 0x800E8890 | size: 0x394
 */
void CupCheaterScene::Update(float)
{
}

/**
 * Offset/Address/Size: 0x10FC | 0x800E884C | size: 0x44
 */
void CupCheaterScene::OnSelectGameplay()
{
    // TODO: Check if this is correct, could also be another interface
    CupCheaterScene* scene = (CupCheaterScene*)nlSingleton<GameSceneManager>::s_pInstance->Push(SCENE_SUPER_LOADING, SCREEN_NOTHING, true);
    scene->m_SlideMenu = NULL;
}

/**
 * Offset/Address/Size: 0xE90 | 0x800E85E0 | size: 0x26C
 */
void CupCheaterScene::OnSelectHomeWin()
{
}

/**
 * Offset/Address/Size: 0xC24 | 0x800E8374 | size: 0x26C
 */
void CupCheaterScene::OnSelectAwayWin()
{
}

/**
 * Offset/Address/Size: 0x9B8 | 0x800E8108 | size: 0x26C
 */
void CupCheaterScene::OnSelectHomeOTWin()
{
}

/**
 * Offset/Address/Size: 0x74C | 0x800E7E9C | size: 0x26C
 */
void CupCheaterScene::OnSelectAwayOTWin()
{
}

/**
 * Offset/Address/Size: 0x0 | 0x800E7750 | size: 0x74C
 */
void CupCheaterScene::UpdateSlides()
{
}
