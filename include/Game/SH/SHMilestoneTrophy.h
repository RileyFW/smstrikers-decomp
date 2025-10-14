#ifndef _SHMILESTONETROPHY_H_
#define _SHMILESTONETROPHY_H_

#include "types.h"

#include "Game/TrophyInfo.h"
#include "Game/FE/feButtonComponent.h"

class MilestoneTrophyScene
{
public:
    MilestoneTrophyScene();
    ~MilestoneTrophyScene();
    void SceneCreated();
    void Update(float);
    void CreateTrophyScene(eTrophyType, ButtonComponent::ButtonState, bool);
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
