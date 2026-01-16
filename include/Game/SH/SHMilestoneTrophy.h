#ifndef _SHMILESTONETROPHY_H_
#define _SHMILESTONETROPHY_H_

#include "types.h"

#include "Game/BaseSceneHandler.h"
#include "Game/TrophyInfo.h"
#include "Game/FE/feAsyncImage.h"
#include "Game/FE/feButtonComponent.h"

class MilestoneTrophyScene : public BaseSceneHandler
{
public:
    MilestoneTrophyScene();
    ~MilestoneTrophyScene();
    void SceneCreated();
    void Update(float);
    void CreateTrophyScene(eTrophyType, ButtonComponent::ButtonState, bool);
    void ChangeSlides();

    /* 0x01C */ eTrophyType mTrophy;                       // size 0x4
    /* 0x020 */ bool mCreated;                             // size 0x1
    /* 0x021 */ bool mIsNew;                               // size 0x1
    /* 0x022 */ bool mFirstSlideChange;                    // size 0x1
    /* 0x024 */ unsigned short mTotalBuffer[128];          // size 0x100
    /* 0x124 */ unsigned short mStatBuffer[128];           // size 0x100
    /* 0x224 */ unsigned short mDescriptionBuffer[128];    // size 0x100
    /* 0x324 */ AsyncImage* mAsyncTrophy;                  // size 0x4
    /* 0x328 */ bool mDoBlockLoad;                         // size 0x1
    /* 0x32C */ ButtonComponent::ButtonState mButtonState; // size 0x4
    /* 0x330 */ ButtonComponent mButtons;                  // size 0x24
    /* 0x354 */ ButtonComponent mButtons2;                 // size 0x24
}; // total size: 0x378

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
//     void TempStringAllocator>::Append(const char*) const;
// };

// class Format<BasicString<unsigned short, Detail
// {
// public:
//     void TempStringAllocator>, unsigned short[128]>(const BasicString<unsigned short, Detail::TempStringAllocator>&, const unsigned
//     short(&)[128]); void TempStringAllocator>, const unsigned short*>(const BasicString<unsigned short, Detail::TempStringAllocator>&,
//     const unsigned short* const&); void TempStringAllocator>, unsigned short[128], unsigned short[128]>(const BasicString<unsigned short,
//     Detail::TempStringAllocator>&, const unsigned short(&)[128], const unsigned short(&)[128]); void TempStringAllocator>, unsigned
//     short[16], unsigned short[16], unsigned short[16]>(const BasicString<unsigned short, Detail::TempStringAllocator>&, const unsigned
//     short(&)[16], const unsigned short(&)[16], const unsigned short(&)[16]);
// };

// class FormatImpl<BasicString<unsigned short, Detail
// {
// public:
//     void TempStringAllocator>>::operator%<const unsigned short*>(const unsigned short* const&);
// };

#endif // _SHMILESTONETROPHY_H_
