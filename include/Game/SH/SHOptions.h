#ifndef _SHOPTIONS_H_
#define _SHOPTIONS_H_

#include "Game/BaseSceneHandler.h"
#include "Game/BaseGameSceneManager.h"
#include "Game/GameSceneManager.h"
#include "Game/FE/feButtonComponent.h"
#include "Game/FE/feMenu.h"
#include "Game/FE/feOptionsSubMenus.h"
#include "Game/FE/fePopupMenu.h"
#include "Game/FE/tlComponentInstance.h"
#include "NL/nlSingleton.h"

void RevertChangesCB();
void ApplyChangesCB();

enum eMenuState
{
    MS_INVALID = -1,
    MS_MAIN = 0,
    MS_AUDIO = 1,
    MS_VISUAL = 2,
    MS_GAMEPLAY = 3,
    MS_CHEATS = 4,
    MS_SAVE_LOAD = 5,
    MS_NUMMENUSTATES = 6,
};

enum ePopupResult
{
    PR_DO_NOTHING = 0,
    PR_APPLY_CHANGES = 1,
    PR_REVERT_CHANGES = 2,
    PR_APPLY_DELAYED_AUDIO_CHANGES = 3,
};

class OptionsScene : public BaseSceneHandler
{
public:
    OptionsScene();
    ~OptionsScene();
    void SceneCreated();
    void Update(float);
    void UpdateForMain(float);
    void UpdateForSubOptionMenus(float);
    void ChangeMenuState(eMenuState);
    static s32 mLastSelectedIndex;

    /* 0x01C */ OptionsSubMenu* m_subMenu;                // size 0x4
    /* 0x020 */ eMenuState m_curMenuState;                // size 0x4
    /* 0x024 */ ButtonComponent mButtons;                 // size 0x24
    /* 0x048 */ MenuList<TLComponentInstance> mMenuItems; // size 0x214
    /* 0x25C */ ePopupResult mPopupResult;                // size 0x4
    /* 0x260 */ unsigned long mUserInfoCRC;               // size 0x4
}; // total size: 0x264

// class Function1<void, TLComponentInstance*>
// {
// public:
//     void FunctorImpl<BindExp2<void, Detail::MemFunImpl<void, void (OptionsScene::*)(eMenuState)>, OptionsScene*,
//     eMenuState>>::~FunctorImpl(); void FunctorImpl<BindExp2<void, Detail::MemFunImpl<void, void (OptionsScene::*)(eMenuState)>,
//     OptionsScene*, eMenuState>>::operator()(TLComponentInstance*); void FunctorImpl<BindExp2<void, Detail::MemFunImpl<void, void
//     (OptionsScene::*)(eMenuState)>, OptionsScene*, eMenuState>>::Clone() const;
// };

// class FEFinder<TLComponentInstance, 4>
// {
// public:
//     void _Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
//     void _Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
//     void Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher);
// };

// class FEFinder<TLInstance, 4>
// {
// public:
//     void _Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
//     void _Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
//     void Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher);
// };

// class MemFun<OptionsScene, void, eMenuState>(void (OptionsScene
// {
// public:
//     void *)(eMenuState));
// };

// class Bind<void, Detail
// {
// public:
//     void MemFunImpl<void, void (OptionsScene::*)(eMenuState)>, OptionsScene*, eMenuState>(Detail::MemFunImpl<void, void
//     (OptionsScene::*)(eMenuState)>, OptionsScene* const&, const eMenuState&);
// };

#endif // _SHOPTIONS_H_
