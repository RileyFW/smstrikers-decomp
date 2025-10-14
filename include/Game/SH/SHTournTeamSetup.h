#ifndef _SHTOURNTEAMSETUP_H_
#define _SHTOURNTEAMSETUP_H_

#include "types.h"
#include "Game/DB/Cup.h"

class TournTeamSetupSceneV2
{
public:
    enum eTeamChooserState
    {
        eTeamChooserState_0 = 0
    };

    TournTeamSetupSceneV2();
    ~TournTeamSetupSceneV2();
    void SceneCreated();
    void Update(float);
    void UpdateControllerIcon(int);
    void UpdateRow(int);
    void ChangeState(TournTeamSetupSceneV2::eTeamChooserState, TournTeamSetupSceneV2::eTeamChooserState);
    void StartChooseCaptain(int);
    void UpdateCaptainName();
    void UpdateSKName();
    void Proceed();
    void FindCaptainSlideName(eTeamID);
    void FindSidekickSlideName(eSidekickID);
    void AutoFill();
    void UpdateForCurrentRow();
    void ScrollUp(bool);
    void ScrollDown(bool);
};

// class FEFinder<TLComponentInstance, 4>
// {
// public:
//     void _Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
//     void _Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
//     void Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher);
// };

// class FEFinder<TLTextInstance, 3>
// {
// public:
//     void _Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
//     void _Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
//     void Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher);
// };

// class FEFinder<TLImageInstance, 2>
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

// class Function1<void, TLComponentInstance*>
// {
// public:
//     void FunctorImpl<BindExp2<void, Detail::MemFunImpl<void, void (TournTeamSetupSceneV2::*)(int)>, TournTeamSetupSceneV2*,
//     int>>::~FunctorImpl(); void FunctorImpl<BindExp2<void, Detail::MemFunImpl<void, void (TournTeamSetupSceneV2::*)(int)>,
//     TournTeamSetupSceneV2*, int>>::operator()(TLComponentInstance*); void FunctorImpl<BindExp2<void, Detail::MemFunImpl<void, void
//     (TournTeamSetupSceneV2::*)(int)>, TournTeamSetupSceneV2*, int>>::Clone() const;
// };

// class MemFun<TournTeamSetupSceneV2, void, int>(void (TournTeamSetupSceneV2
// {
// public:
//     void *)(int));
// };

// class Bind<void, Detail
// {
// public:
//     void MemFunImpl<void, void (TournTeamSetupSceneV2::*)(int)>, TournTeamSetupSceneV2*, int>(Detail::MemFunImpl<void, void
//     (TournTeamSetupSceneV2::*)(int)>, TournTeamSetupSceneV2* const&, const int&);
// };

#endif // _SHTOURNTEAMSETUP_H_
