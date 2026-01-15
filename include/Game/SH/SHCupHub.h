#ifndef _SHCUPHUB_H_
#define _SHCUPHUB_H_

#include "types.h"
#include "Game/GameSceneManager.h"

enum eHubColour
{
    eHubColour_0 = 0
};

class CupHubScene
{
public:
    CupHubScene(bool, bool);
    ~CupHubScene();
    void SceneCreated();
    void Update(float);
    void EndCup();
    void ReturnToMainMenu();
    void UpdateDisplayedStat();
    void CreateLeague();
    void CreateBowserLeague();
    void CreateKnockout();
    void UpdateLeague(float);
    void UpdateKnockout8(float);
    void UpdateKnockout4(float);
    void UpdateKnockout2(float);
    void UpdateProgressIndicator();
    void ColourUserRow();
    void HandleButtonComponent();
    void SetRoundColours(eHubColour*, int);
    void UpdateRoundMessage(bool);
    void LoadCaptainImage();
};

// class FEFinder<TLImageInstance, 2>
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

// class FEFinder<TLComponentInstance, 4>
// {
// public:
//     void _Find<FEPresentation>(FEPresentation*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned
//     long); void Find<FEPresentation>(FEPresentation*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher,
//     InlineHasher); void _Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long,
//     unsigned long); void _Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned
//     long); void Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher);
// };

// class Function0<void>
// {
// public:
//     void FunctorImpl<BindExp1<void, Detail::MemFunImpl<void, void (CupHubScene::*)()>, CupHubScene*>>::~FunctorImpl();
//     void FunctorImpl<BindExp1<void, Detail::MemFunImpl<void, void (CupHubScene::*)()>, CupHubScene*>>::operator()();
//     void FunctorImpl<BindExp1<void, Detail::MemFunImpl<void, void (CupHubScene::*)()>, CupHubScene*>>::Clone() const;
// };

// class TeamStats
// {
// public:
//     TeamStats();
// };

// class MemFun<CupHubScene, void>(void (CupHubScene
// {
// public:
//     void *)());
// };

// class Bind<void, Detail
// {
// public:
//     void MemFunImpl<void, void (CupHubScene::*)()>, CupHubScene*>(Detail::MemFunImpl<void, void (CupHubScene::*)()>, CupHubScene*
//     const&);
// };

#endif // _SHCUPHUB_H_
