#include "Game/SH/SHLessonSelect.h"
#include "Game/OverlayManager.h"
#include "Game/SH/SHLesson.h"

// /**
//  * Offset/Address/Size: 0x0 | 0x8010CE0C | size: 0x38
//  */
// void Bind<void, Detail::MemFunImpl<void, void (LessonSelectScene::*)()>, LessonSelectScene*>(
//     Detail::MemFunImpl<void, void (LessonSelectScene::*)()>, LessonSelectScene* const&)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8010CDF0 | size: 0x1C
//  */
// void MemFun<LessonSelectScene, void>(void (LessonSelectScene::*)())
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8010CD94 | size: 0x5C
//  */
// void Function1<void, TLComponentInstance*>::FunctorImpl<
//     BindExp1<void, Detail::MemFunImpl<void, void (LessonSelectScene::*)()>, LessonSelectScene*>>::~FunctorImpl()
// {
// }

// /**
//  * Offset/Address/Size: 0x4EC | 0x8010CC38 | size: 0x15C
//  */
// void FEFinder<TLImageInstance, 2>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned
// long,
//                                                      unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x468 | 0x8010CBB4 | size: 0x84
//  */
// void FEFinder<TLImageInstance, 2>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long,
//                                                   unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x430 | 0x8010CB7C | size: 0x38
//  */
// void FEFinder<TLImageInstance, 2>::Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher,
//                                                  InlineHasher)
// {
// }

// /**
//  * Offset/Address/Size: 0x2D4 | 0x8010CA20 | size: 0x15C
//  */
// void FEFinder<TLComponentInstance, 4>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long,
//                                                          unsigned long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x250 | 0x8010C99C | size: 0x84
//  */
// void FEFinder<TLComponentInstance, 4>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned
// long,
//                                                       unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x218 | 0x8010C964 | size: 0x38
//  */
// void FEFinder<TLComponentInstance, 4>::Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher,
//                                                      InlineHasher)
// {
// }

// /**
//  * Offset/Address/Size: 0xBC | 0x8010C808 | size: 0x15C
//  */
// void FEFinder<TLTextInstance, 3>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned
// long,
//                                                     unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x38 | 0x8010C784 | size: 0x84
//  */
// void FEFinder<TLTextInstance, 3>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long,
//                                                  unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8010C74C | size: 0x38
//  */
// void FEFinder<TLTextInstance, 3>::Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher,
//                                                 InlineHasher)
// {
// }

// /**
//  * Offset/Address/Size: 0x78 | 0x8010C71C | size: 0x30
//  */
// void Function1<void, TLComponentInstance*>::FunctorImpl<
//     BindExp1<void, Detail::MemFunImpl<void, void (LessonSelectScene::*)()>, LessonSelectScene*>>::operator()(TLComponentInstance*)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8010C6A4 | size: 0x78
//  */
// void Function1<void, TLComponentInstance*>::FunctorImpl<
//     BindExp1<void, Detail::MemFunImpl<void, void (LessonSelectScene::*)()>, LessonSelectScene*>>::Clone() const
// {
// }

/**
 * Offset/Address/Size: 0x1830 | 0x8010C680 | size: 0x24
 */
void LessonTickerDoneCB()
{
    SetTickerLesson(-1);
}

/**
 * Offset/Address/Size: 0x1774 | 0x8010C5C4 | size: 0xBC
 */
LessonSelectScene::LessonSelectScene()
{
}

/**
 * Offset/Address/Size: 0x16D0 | 0x8010C520 | size: 0xA4
 */
LessonSelectScene::~LessonSelectScene()
{
}

/**
 * Offset/Address/Size: 0xE98 | 0x8010BCE8 | size: 0x838
 */
void LessonSelectScene::SceneCreated()
{
}

/**
 * Offset/Address/Size: 0x7E0 | 0x8010B630 | size: 0x6B8
 */
void LessonSelectScene::Update(float)
{
}

/**
 * Offset/Address/Size: 0x334 | 0x8010B184 | size: 0x4AC
 */
void LessonSelectScene::UpdateRow(int, bool)
{
}

extern int sCurrentRow;

/**
 * Offset/Address/Size: 0x2E4 | 0x8010B134 | size: 0x50
 */
void LessonSelectScene::StartLesson()
{
    OverlayManager::Instance()->Push(IGSCENE_LESSON, SCREEN_FORWARD, true);
    LessonScene::SetLesson(sCurrentRow + 1);
    SetTickerLesson(sCurrentRow);
}

/**
 * Offset/Address/Size: 0x0 | 0x8010AE50 | size: 0x2E4
 */
void SetTickerLesson(int)
{
    FORCE_DONT_INLINE;
}
