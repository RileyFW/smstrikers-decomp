#include "Game/SH/SHMilestoneTrophy.h"

// /**
//  * Offset/Address/Size: 0x1058 | 0x800D0DD8 | size: 0x118
//  */
// void Format<BasicString<unsigned short, Detail::TempStringAllocator>, unsigned short[128]>(const BasicString<unsigned short,
// Detail::TempStringAllocator>&, const unsigned short(&)[128])
// {
// }

// /**
//  * Offset/Address/Size: 0xF44 | 0x800D0CC4 | size: 0x114
//  */
// void Format<BasicString<unsigned short, Detail::TempStringAllocator>, const unsigned short*>(const BasicString<unsigned short,
// Detail::TempStringAllocator>&, const unsigned short* const&)
// {
// }

// /**
//  * Offset/Address/Size: 0xE20 | 0x800D0BA0 | size: 0x124
//  */
// void Format<BasicString<unsigned short, Detail::TempStringAllocator>, unsigned short[128], unsigned short[128]>(const
// BasicString<unsigned short, Detail::TempStringAllocator>&, const unsigned short(&)[128], const unsigned short(&)[128])
// {
// }

// /**
//  * Offset/Address/Size: 0x130 | 0x800CFEB0 | size: 0xCF0
//  */
// void FormatImpl<BasicString<unsigned short, Detail::TempStringAllocator>>::operator%<const unsigned short*>(const unsigned short* const&)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x800CFD80 | size: 0x130
//  */
// void Format<BasicString<unsigned short, Detail::TempStringAllocator>, unsigned short[16], unsigned short[16], unsigned short[16]>(const
// BasicString<unsigned short, Detail::TempStringAllocator>&, const unsigned short(&)[16], const unsigned short(&)[16], const unsigned
// short(&)[16])
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x800CFCC4 | size: 0xBC
//  */
// void BasicString<char, Detail::TempStringAllocator>::Append(const char*) const
// {
// }

// /**
//  * Offset/Address/Size: 0x5A8 | 0x800CFB68 | size: 0x15C
//  */
// void FEFinder<TLTextInstance, 3>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned
// long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x524 | 0x800CFAE4 | size: 0x84
//  */
// void FEFinder<TLTextInstance, 3>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long,
// unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x4EC | 0x800CFAAC | size: 0x38
//  */
// void FEFinder<TLTextInstance, 3>::Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher,
// InlineHasher)
// {
// }

// /**
//  * Offset/Address/Size: 0x390 | 0x800CF950 | size: 0x15C
//  */
// void FEFinder<TLImageInstance, 2>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned
// long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x30C | 0x800CF8CC | size: 0x84
//  */
// void FEFinder<TLImageInstance, 2>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long,
// unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x2D4 | 0x800CF894 | size: 0x38
//  */
// void FEFinder<TLImageInstance, 2>::Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher,
// InlineHasher)
// {
// }

// /**
//  * Offset/Address/Size: 0x250 | 0x800CF810 | size: 0x84
//  */
// void FEFinder<TLComponentInstance, 4>::_Find<FEPresentation>(FEPresentation*, unsigned long, unsigned long, unsigned long, unsigned long,
// unsigned long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x218 | 0x800CF7D8 | size: 0x38
//  */
// void FEFinder<TLComponentInstance, 4>::Find<FEPresentation>(FEPresentation*, InlineHasher, InlineHasher, InlineHasher, InlineHasher,
// InlineHasher, InlineHasher)
// {
// }

// /**
//  * Offset/Address/Size: 0xBC | 0x800CF67C | size: 0x15C
//  */
// void FEFinder<TLComponentInstance, 4>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long,
// unsigned long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x38 | 0x800CF5F8 | size: 0x84
//  */
// void FEFinder<TLComponentInstance, 4>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned
// long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x800CF5C0 | size: 0x38
//  */
// void FEFinder<TLComponentInstance, 4>::Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher,
// InlineHasher)
// {
// }

/**
 * Offset/Address/Size: 0x19F4 | 0x800CF4F4 | size: 0xCC
 */
MilestoneTrophyScene::MilestoneTrophyScene()
{
}

/**
 * Offset/Address/Size: 0x1950 | 0x800CF450 | size: 0xA4
 */
MilestoneTrophyScene::~MilestoneTrophyScene()
{
}

/**
 * Offset/Address/Size: 0x3CC | 0x800CDECC | size: 0x1584
 */
void MilestoneTrophyScene::SceneCreated()
{
}

/**
 * Offset/Address/Size: 0x188 | 0x800CDC88 | size: 0x244
 */
void MilestoneTrophyScene::Update(float)
{
}

/**
 * Offset/Address/Size: 0x170 | 0x800CDC70 | size: 0x18
 */
void MilestoneTrophyScene::CreateTrophyScene(eTrophyType trophy, ButtonComponent::ButtonState state, bool isNew)
{
    mTrophy = trophy;
    mIsNew = isNew;
    mCreated = true;
    mButtonState = state;
}

/**
 * Offset/Address/Size: 0x0 | 0x800CDB00 | size: 0x170
 */
void MilestoneTrophyScene::ChangeSlides()
{
}
