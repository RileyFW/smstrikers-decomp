#include "Game/SH/SHMainMenu.h"
#include "Game/GameInfo.h"
#include "Game/GameSceneManager.h"

// /**
//  * Offset/Address/Size: 0x0 | 0x800AC57C | size: 0x40
//  */
// void Bind<void, Detail::MemFunImpl<void, void (SHMainMenu::*)(TLComponentInstance*)>, SHMainMenu*, Placeholder<0>>(
//     Detail::MemFunImpl<void, void (SHMainMenu::*)(TLComponentInstance*)>, SHMainMenu* const&, const Placeholder<0>&)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x800AC560 | size: 0x1C
//  */
// void MemFun<SHMainMenu, void, TLComponentInstance*>(void (SHMainMenu::*)(TLComponentInstance*))
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x800AC504 | size: 0x5C
//  */
// void Function1<void, TLComponentInstance*>::FunctorImpl<
//     BindExp2<void, Detail::MemFunImpl<void, void (SHMainMenu::*)(TLComponentInstance*)>, SHMainMenu*, Placeholder<0>>>::~FunctorImpl()
// {
// }

// /**
//  * Offset/Address/Size: 0x3F0 | 0x800AC404 | size: 0x100
//  */
// void 0x800AC504..0x800AC560 | size : 0x5C
// {
// }

// /**
//  * Offset/Address/Size: 0x384 | 0x800AC398 | size: 0x6C
//  */
// void FEPopupMenu::Create(ePopupMenu)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x800AC014 | size: 0x4
//  */
// void FEPopupMenu::Nothing()
// {
// }

// /**
//  * Offset/Address/Size: 0x70 | 0x800ABFBC | size: 0x58
//  */
// void MenuItem<TLComponentInstance>::MenuItem()
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x800ABF4C | size: 0x70
//  */
// void MenuList<TLComponentInstance>::~MenuList()
// {
// }

// /**
//  * Offset/Address/Size: 0xD4 | 0x800ABF1C | size: 0x30
//  */
// void Function1<void, TLComponentInstance*>::FunctorImpl<BindExp2<void, Detail::MemFunImpl<void, void
// (SHMainMenu::*)(TLComponentInstance*)>,
//                                                                  SHMainMenu*, Placeholder<0>>>::operator()(TLComponentInstance*)
// {
// }

// /**
//  * Offset/Address/Size: 0x54 | 0x800ABE9C | size: 0x80
//  */
// void Function1<void, TLComponentInstance*>::FunctorImpl<
//     BindExp2<void, Detail::MemFunImpl<void, void (SHMainMenu::*)(TLComponentInstance*)>, SHMainMenu*, Placeholder<0>>>::Clone() const
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x800ABE48 | size: 0x48
//  */
// void Function1<void, TLComponentInstance*>::FunctorBase::~FunctorBase()
// {
// }

// /**
//  * Offset/Address/Size: 0x704 | 0x800ABCEC | size: 0x15C
//  */
// void FEFinder<TLInstance, 4>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long,
//                                                 unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x680 | 0x800ABC68 | size: 0x84
//  */
// void FEFinder<TLInstance, 4>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long,
//                                              unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x648 | 0x800ABC30 | size: 0x38
//  */
// void FEFinder<TLInstance, 4>::Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher)
// {
// }

// /**
//  * Offset/Address/Size: 0x4EC | 0x800ABAD4 | size: 0x15C
//  */
// void FEFinder<TLTextInstance, 3>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned
// long,
//                                                     unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x468 | 0x800ABA50 | size: 0x84
//  */
// void FEFinder<TLTextInstance, 3>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long,
//                                                  unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x430 | 0x800ABA18 | size: 0x38
//  */
// void FEFinder<TLTextInstance, 3>::Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher,
//                                                 InlineHasher)
// {
// }

// /**
//  * Offset/Address/Size: 0x2D4 | 0x800AB8BC | size: 0x15C
//  */
// void FEFinder<TLComponentInstance, 4>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long,
//                                                          unsigned long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x250 | 0x800AB838 | size: 0x84
//  */
// void FEFinder<TLComponentInstance, 4>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned
// long,
//                                                       unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x218 | 0x800AB800 | size: 0x38
//  */
// void FEFinder<TLComponentInstance, 4>::Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher,
//                                                      InlineHasher)
// {
// }

// /**
//  * Offset/Address/Size: 0xBC | 0x800AB6A4 | size: 0x15C
//  */
// void FEFinder<TLImageInstance, 2>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned
// long,
//                                                      unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x38 | 0x800AB620 | size: 0x84
//  */
// void FEFinder<TLImageInstance, 2>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long,
//                                                   unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x800AB5E8 | size: 0x38
//  */
// void FEFinder<TLImageInstance, 2>::Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher,
//                                                  InlineHasher)
// {
// }

/**
 * Offset/Address/Size: 0x1B14 | 0x800AB570 | size: 0x78
 */
void onSelectFriendly(TLComponentInstance*)
{
}

/**
 * Offset/Address/Size: 0x1AD0 | 0x800AB52C | size: 0x44
 */
void onSelectCup(TLComponentInstance*)
{
}

/**
 * Offset/Address/Size: 0x1A50 | 0x800AB4AC | size: 0x80
 */
void onSelectSuperCup(TLComponentInstance*)
{
}

/**
 * Offset/Address/Size: 0x19C4 | 0x800AB420 | size: 0x8C
 */
void onSelect101(TLComponentInstance*)
{
}

/**
 * Offset/Address/Size: 0x1964 | 0x800AB3C0 | size: 0x60
 */
void newTourn()
{
}

/**
 * Offset/Address/Size: 0x1914 | 0x800AB370 | size: 0x50
 */
void continueTourn()
{
    GameInfoManager::s_pInstance->SetMode(GameInfoManager::GM_TOURNAMENT);
    GameSceneManager::s_pInstance->PopEntireStack();
    GameSceneManager::s_pInstance->Push(SCENE_TOURNAMENT_STANDINGS, SCREEN_FORWARD, false);
}

/**
 * Offset/Address/Size: 0x182C | 0x800AB288 | size: 0xE8
 */
void confirmNewTourn()
{
}

/**
 * Offset/Address/Size: 0x1680 | 0x800AB0DC | size: 0x1AC
 */
void onSelectTournament(TLComponentInstance*)
{
}

/**
 * Offset/Address/Size: 0x1634 | 0x800AB090 | size: 0x4C
 */
void onSelectTrophies(TLComponentInstance*)
{
}

/**
 * Offset/Address/Size: 0x15E8 | 0x800AB044 | size: 0x4C
 */
void onSelectOptions(TLComponentInstance*)
{
}

// /**
//  * Offset/Address/Size: 0x1538 | 0x800AAF94 | size: 0xB0
//  */
// SHMainMenu::SHMainMenu()
// {
// }

// /**
//  * Offset/Address/Size: 0x14D8 | 0x800AAF34 | size: 0x60
//  */
// void MenuItem<TLComponentInstance>::~MenuItem()
// {
// }

// /**
//  * Offset/Address/Size: 0x1380 | 0x800AADDC | size: 0x158
//  */
// SHMainMenu::~SHMainMenu()
// {
// }

// /**
//  * Offset/Address/Size: 0xA3C | 0x800AA498 | size: 0x8C0
//  */
// void SHMainMenu::SceneCreated()
// {
// }

// /**
//  * Offset/Address/Size: 0x60C | 0x800AA068 | size: 0x430
//  */
// void SHMainMenu::OpenItem(TLComponentInstance*)
// {
// }

// /**
//  * Offset/Address/Size: 0x404 | 0x800A9E60 | size: 0x208
//  */
// void SHMainMenu::CloseItem(TLComponentInstance*)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x800A9A5C | size: 0x404
//  */
// void SHMainMenu::Update(float)
// {
// }
