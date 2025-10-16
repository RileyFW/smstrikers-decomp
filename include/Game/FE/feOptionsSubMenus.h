#ifndef _FEOPTIONSSUBMENUS_H_
#define _FEOPTIONSSUBMENUS_H_

#include "Game/DB/UserOptions.h"
#include "Game/FE/feButtonComponent.h"

class FEPresentation;
class TLComponentInstance;
class TLImageInstance;
class TLTextInstance;
class TLInstance;
class GameplaySettings;
class VisualSettings;
class AudioSettings;
class CheatSettings;

class OptionsSaveLoad
{
public:
    void Revert();
    void Save();
    void Update(float);
    ~OptionsSaveLoad();
    OptionsSaveLoad(FEPresentation*, ButtonComponent::ButtonState);
    void ChangesMade();
};

class OptionsGameplayMenuV2
{
public:
    void CloseItem(TLComponentInstance*);
    void Revert();
    void Save();
    ~OptionsGameplayMenuV2();
    void BuildSkillLevelMenu(TLComponentInstance*, int, int);
    OptionsGameplayMenuV2(FEPresentation*, ButtonComponent::ButtonState, GameplaySettings&, int);
    void ChangesMade();
};

class OptionsVisualMenuV2
{
public:
    void Revert();
    void Save();
    void Update(float);
    ~OptionsVisualMenuV2();
    OptionsVisualMenuV2(FEPresentation*, ButtonComponent::ButtonState, VisualSettings&);
    void ChangesMade();
};

class OptionsAudioMenuV2
{
public:
    void Update(float);
    void Revert();
    void Save();
    ~OptionsAudioMenuV2();
    OptionsAudioMenuV2(FEPresentation*, ButtonComponent::ButtonState, AudioSettings&);
    void ChangesMade();
};

class OptionsCheatsMenu
{
public:
    // void BuildCustomPowerupsList(TLComponentInstance*, CheatSettings::CustomPowerups, FEPresentation*);
    void BuildLockableSubMenuList(int, TLComponentInstance*, FEPresentation*, bool, int);
    void Revert();
    void Save();
    ~OptionsCheatsMenu();
    OptionsCheatsMenu(FEPresentation*, ButtonComponent::ButtonState, CheatSettings&);
    void ChangesMade();
};

class OptionsSubMenu
{
public:
    void SetAButtonLOC(unsigned long);
    void SetButtonState(ButtonComponent::ButtonState);
    void BuildSubMenuList(int, TLComponentInstance*, bool, int);
    void GoBack();
    void Update(float);
    ~OptionsSubMenu();
};

// class Function1<void, SlideMenuItem*>
// {
// public:
//     void FunctorBase::~FunctorBase();
//     void FunctorImpl<BindExp1<void, Detail::MemFunImpl<void, void (SlideMenuList::*)()>, SlideMenuList*>>::Clone() const;
//     void FunctorImpl<BindExp1<void, Detail::MemFunImpl<void, void (SlideMenuList::*)()>, SlideMenuList*>>::operator()(SlideMenuItem*);
//     void FunctorImpl<BindExp1<void, Detail::MemFunImpl<void, void (SlideMenuList::*)()>, SlideMenuList*>>::~FunctorImpl();
// };

// class SlideMenuList
// {
// public:
//     ~SlideMenuList();
//     void Update(float);
// };

// class MenuItem<SlideMenuItem>
// {
// public:
//     void ~MenuItem();
//     void MenuItem();
// };

// class SlideMenuItem
// {
// public:
//     ~SlideMenuItem();
// };

// class FEFinder<TLComponentInstance, 4>
// {
// public:
//     void Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher);
//     void _Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
//     void _Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
// };

// class FEFinder<TLImageInstance, 2>
// {
// public:
//     void Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher);
//     void _Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
//     void _Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
// };

// class FEFinder<TLTextInstance, 3>
// {
// public:
//     void Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher);
//     void _Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
//     void _Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
// };

// class FEFinder<TLInstance, 4>
// {
// public:
//     void Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher);
//     void _Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
//     void _Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
// };

// class MenuList<SlideMenuItem>
// {
// public:
//     void ~MenuList();
// };

// class MemFun<SlideMenuList, void>(void (SlideMenuList
// {
// public:
//     void *)());
// };

// class Bind < void, Detail
// {
// public:
//     void MemFunImpl<void, void (SlideMenuList::*)()>,
//         SlideMenuList * > (Detail::MemFunImpl<void, void (SlideMenuList::*)()>, SlideMenuList* const&);
// };

#endif // _FEOPTIONSSUBMENUS_H_
