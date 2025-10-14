#ifndef _SHCUPTROPHY_H_
#define _SHCUPTROPHY_H_

#include "types.h"

#include "Game/TrophyInfo.h"
#include "Game/FE/feButtonComponent.h"

class Spoil
{
public:
    Spoil();
    ~Spoil();
};

class CupTrophyScene
{
public:
    CupTrophyScene();
    ~CupTrophyScene();
    void SceneCreated();
    void HandleUnlockedTriggers();
    void Update(float);
    void CreateTrophyScene(eTrophyType, ButtonComponent::ButtonState, bool);
    void SetWinRecord(Spoil&);
    void SetLossRecord(Spoil&);
    void SetHistory(Spoil&);
    void ChangeSlides();
};

// class FEFinder<TLComponentInstance, 4>
// {
// public:
//     void _Find<FEPresentation>(FEPresentation*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned
//     long); void Find<FEPresentation>(FEPresentation*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher,
//     InlineHasher); void _Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long,
//     unsigned long); void _Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned
//     long); void Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher);
// };

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

// class BasicString<char, Detail
// {
// public:
//     void TempStringAllocator>::AppendInPlace<Detail::TempStringAllocator>(const BasicString<char, Detail::TempStringAllocator>&);
//     void TempStringAllocator>::Append<Detail::TempStringAllocator>(const BasicString<char, Detail::TempStringAllocator>&) const;
// };

// class Function0<void>
// {
// public:
//     void FunctorImpl<BindExp1<void, Detail::MemFunImpl<void, void (CupTrophyScene::*)()>, CupTrophyScene*>>::~FunctorImpl();
//     void FunctorImpl<BindExp1<void, Detail::MemFunImpl<void, void (CupTrophyScene::*)()>, CupTrophyScene*>>::operator()();
//     void FunctorImpl<BindExp1<void, Detail::MemFunImpl<void, void (CupTrophyScene::*)()>, CupTrophyScene*>>::Clone() const;
// };

// class Format<BasicString<unsigned short, Detail
// {
// public:
//     void TempStringAllocator>, unsigned short[32]>(const BasicString<unsigned short, Detail::TempStringAllocator>&, const unsigned
//     short(&)[32]); void TempStringAllocator>, unsigned short[16], unsigned short[16], unsigned short[16], const unsigned short*, const
//     unsigned short*>(const BasicString<unsigned short, Detail::TempStringAllocator>&, const unsigned short(&)[16], const unsigned
//     short(&)[16], const unsigned short(&)[16], const unsigned short* const&, const unsigned short* const&); void TempStringAllocator>,
//     unsigned short[16], unsigned short[16], unsigned short[16], const unsigned short*, const unsigned short*, const unsigned
//     short*>(const BasicString<unsigned short, Detail::TempStringAllocator>&, const unsigned short(&)[16], const unsigned short(&)[16],
//     const unsigned short(&)[16], const unsigned short* const&, const unsigned short* const&, const unsigned short* const&);
// };

// class FormatImpl<BasicString<unsigned short, Detail
// {
// public:
//     void TempStringAllocator>>::operator%<const unsigned short*>(const unsigned short* const&);
// };

// class MemFun<CupTrophyScene, void>(void (CupTrophyScene
// {
// public:
//     void *)());
// };

// class Bind<void, Detail
// {
// public:
//     void MemFunImpl<void, void (CupTrophyScene::*)()>, CupTrophyScene*>(Detail::MemFunImpl<void, void (CupTrophyScene::*)()>,
//     CupTrophyScene* const&);
// };

#endif // _SHCUPTROPHY_H_
