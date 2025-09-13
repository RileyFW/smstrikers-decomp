#ifndef _FECAPTAINCOMPONENT_H_
#define _FECAPTAINCOMPONENT_H_
#include "Game/FE/feInput.h"

class TLComponentInstance;
class TLInstance;
class TLSlide;
class InlineHasher;
class FEPresentation;

enum eSidekickID
{
    SIDEKICK_ID_0 = 0,
};

class IChooseCaptain
{
public:
    void SetupNameComponentToCurrentCaptain(int);
    void MoveHighlightToCurrentCaptain(int);
    void PushPlayerWithGameInfoDB();
    void ResetPushPlayerData();
    void PopPlayer(eFEINPUT_PAD);
    void PushPlayer(eFEINPUT_PAD, int);
    void SetupForLastPhase(eFEINPUT_PAD);
    void FindAliveHumanPlayers();
    void CheckForDisconnectedHumanPlayers();
    void StartSidekickMiniHead(int, eSidekickID);
    void SetupCaptainComponent(TLComponentInstance*, int);
    void SceneCreated(FEPresentation*);
    void UpdateAsyncImages();
    void Update(float);
    void UpdateSound(float);
    void Initialize(const char*, const char*);
    ~IChooseCaptain();
    IChooseCaptain();
    // void NameComponent::SetCaptainLogo(const char*);
    // void NameComponent::SetCaptainName(unsigned long);
    // void NameComponent::SetTextName(const char*, unsigned long);
    // void ComponentState::SetCurrentPhase(IChooseCaptain::ComponentState::Phase);
    // void NameComponent::SetSidekickName(unsigned long);
    // void ComponentState::GotoPreviousPhase();
    // void ComponentState::GotoNextPhase();
};

// class FEFinder<TLComponentInstance, 4>
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

// class FEFinder<TLImageInstance, 2>
// {
// public:
//     void Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher);
//     void _Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
//     void _Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
// };

// class IGridComponent<eSidekickID>
// {
// public:
//     void RebindHighliteComponent(const char*);
// };

// class IGridComponent<eTeamID>
// {
// public:
//     void RebindHighliteComponent(const char*);
// };

#endif // _FECAPTAINCOMPONENT_H_
