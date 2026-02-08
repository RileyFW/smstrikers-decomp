#ifndef _SHCHOOSECAPTAINS_H_
#define _SHCHOOSECAPTAINS_H_

#include "Game/BaseSceneHandler.h"
#include "Game/FE/feButtonComponent.h"
#include "Game/FE/feCaptainComponent.h"
#include "Game/FE/feChooseSideComponent.h"
#include "Game/FE/feFinder.h"
#include "Game/FE/feScrollText.h"
#include "Game/FE/tlComponentInstance.h"
#include "NL/gl/glStruct.h"
// #include "types.h"

class ChooseCaptainsSceneV2 : public BaseSceneHandler
{
public:
    enum SceneType
    {
        SceneType_0 = 0,
        SceneType_1 = 1
    };

    ChooseCaptainsSceneV2(ChooseCaptainsSceneV2::SceneType);
    ~ChooseCaptainsSceneV2();
    void SceneCreated();
    void ChangeSceneType(ChooseCaptainsSceneV2::SceneType);
    void ResetForCHOOSECAPTAINS();
    void ResetForCHOOSESIDES();
    void Update(float);
    void BindChooseSideInstances();
    void CreateTicker();

    /* 0x01C */ IChooseCaptain mChooseCaptain; // size 0xCC
    /* 0x0E8 */ IChooseSide mChooseSide;       // size 0xA0
    /* 0x188 */ TLComponentInstance* mChooseSideComponent;
    /* 0x18C */ ButtonComponent mButtons;
    /* 0x1B0 */ SceneType mSceneType;
    /* 0x1B4 */ SceneType mDesiredSceneType;
    /* 0x1B8 */ FEScrollText* mTicker;
    /* 0x1BC */ int mMoveForwardFrameDelay;
}; // total size: 0x1C0

// class FEFinder<TLTextInstance, 3>
// {
// public:
//     void _Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
//     void _Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
//     void Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher);
// };

// class FEFinder<TLInstance, 2>
// {
// public:
//     void _Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
//     void _Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
//     void Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher);
// };

// class FEFinder<TLComponentInstance, 4>
// {
// public:
//     void _Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
//     void _Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
//     void Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher);
// };

// class FEFinder<TLInstance, 3>
// {
// public:
//     void _Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
//     void Find<TLInstance>(TLInstance*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher);
// };

// class FEFinder<TLInstance, 5>
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

// class IChooseCaptain
// {
// public:
//     void SetPhaseReady(int);
// };

#endif // _SHCHOOSECAPTAINS_H_
