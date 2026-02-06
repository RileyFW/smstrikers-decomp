#include "Game/FE/fePopupMenu.h"

#include "Game/FE/feFinder.h"
#include "Game/FE/tlTextInstance.h"
#include "Game/FE/feTemplates.h"

extern char* optionNames[4];

/**
 * Offset/Address/Size: 0xA8 | 0x80098354 | size: 0xBC
 * TODO: 95.47% match - zero-store scheduling differs before optionNames lookup.
 */
void FEPopupMenu::SetOptionTextColourOnCurrent(bool)
{
    FEPresentation* presentation = m_pFEScene->m_pFEPackage->GetPresentation();
    volatile InlineHasher hashers[12];

    hashers[1].m_Hash = 0;
    hashers[3].m_Hash = 0;
    hashers[5].m_Hash = 0;

    int index = mHighlightedOption;

    hashers[0].m_Hash = 0;
    index = index << 2;
    hashers[2].m_Hash = 0;

    char* selected = *(char**)((unsigned char*)optionNames + index);

    hashers[4].m_Hash = 0;

    unsigned long hash = nlStringLowerHash(selected);
    hashers[6].m_Hash = hash;
    hashers[7].m_Hash = hash;

    hash = nlStringLowerHash("Layer");
    hashers[8].m_Hash = hash;
    hashers[9].m_Hash = hash;

    hash = nlStringLowerHash("Slide1");
    hashers[10].m_Hash = hash;
    hashers[11].m_Hash = hash;

    FEFinder<TLTextInstance, 3>::Find<FEPresentation>(
        presentation, (InlineHasher&)hashers[11], (InlineHasher&)hashers[9], (InlineHasher&)hashers[7], (InlineHasher&)hashers[5], (InlineHasher&)hashers[3], (InlineHasher&)hashers[1]);
}

/**
 * Offset/Address/Size: 0x164 | 0x80098410 | size: 0x2FC
 */
void FEPopupMenu::ResizeHighlight()
{
}

/**
 * Offset/Address/Size: 0x460 | 0x8009870C | size: 0x1C0
 */
void FEPopupMenu::CentrePopup(float, float)
{
}

/**
 * Offset/Address/Size: 0x620 | 0x800988CC | size: 0x8A0
 */
void FEPopupMenu::SetPositions()
{
}

/**
 * Offset/Address/Size: 0x2B24 | 0x8009ADD0 | size: 0x400
 */
void FEPopupMenu::Update(float)
{
}

/**
 * Offset/Address/Size: 0x2F24 | 0x8009B1D0 | size: 0x6B8
 */
void FEPopupMenu::SceneCreated()
{
}

/**
 * Offset/Address/Size: 0x35DC | 0x8009B888 | size: 0x258
 */
FEPopupMenu::~FEPopupMenu()
{
}

/**
 * Offset/Address/Size: 0x3834 | 0x8009BAE0 | size: 0xFC
 */
FEPopupMenu::FEPopupMenu()
{
}

// /**
//  * Offset/Address/Size: 0x0 | 0x8009BBDC | size: 0x38
//  */
// void FEFinder<TLTextInstance, 3>::Find<FEPresentation>(FEPresentation*, InlineHasher, InlineHasher, InlineHasher, InlineHasher,
// InlineHasher, InlineHasher)
// {
// }

// /**
//  * Offset/Address/Size: 0x38 | 0x8009BC14 | size: 0x84
//  */
// void FEFinder<TLTextInstance, 3>::_Find<FEPresentation>(FEPresentation*, unsigned long, unsigned long, unsigned long, unsigned long,
// unsigned long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0xBC | 0x8009BC98 | size: 0x84
//  */
// void FEFinder<TLTextInstance, 3>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long,
// unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x140 | 0x8009BD1C | size: 0x15C
//  */
// void FEFinder<TLTextInstance, 3>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned
// long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x29C | 0x8009BE78 | size: 0x38
//  */
// void FEFinder<TLImageInstance, 2>::Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher,
// InlineHasher)
// {
// }

// /**
//  * Offset/Address/Size: 0x2D4 | 0x8009BEB0 | size: 0x84
//  */
// void FEFinder<TLImageInstance, 2>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long,
// unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x358 | 0x8009BF34 | size: 0x15C
//  */
// void FEFinder<TLImageInstance, 2>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned
// long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x4B4 | 0x8009C090 | size: 0x38
//  */
// void FEFinder<TLComponentInstance, 4>::Find<FEPresentation>(FEPresentation*, InlineHasher, InlineHasher, InlineHasher, InlineHasher,
// InlineHasher, InlineHasher)
// {
// }

// /**
//  * Offset/Address/Size: 0x4EC | 0x8009C0C8 | size: 0x84
//  */
// void FEFinder<TLComponentInstance, 4>::_Find<FEPresentation>(FEPresentation*, unsigned long, unsigned long, unsigned long, unsigned long,
// unsigned long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x570 | 0x8009C14C | size: 0x84
//  */
// void FEFinder<TLComponentInstance, 4>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned
// long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x5F4 | 0x8009C1D0 | size: 0x15C
//  */
// void FEFinder<TLComponentInstance, 4>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long,
// unsigned long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x750 | 0x8009C32C | size: 0x38
//  */
// void FEFinder<TLComponentInstance, 4>::Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher,
// InlineHasher)
// {
// }

// /**
//  * Offset/Address/Size: 0x788 | 0x8009C364 | size: 0x8
//  */
// void CastToSomeType<TLInstance>(TLInstance*, void*)
// {
// }

// /**
//  * Offset/Address/Size: 0x790 | 0x8009C36C | size: 0x8
//  */
// void CastToSomeType<TLSlide>(TLSlide*, void*)
// {
// }

// /**
//  * Offset/Address/Size: 0x798 | 0x8009C374 | size: 0x44
//  */
// void FindItemByHashID<TLInstance>(TLInstance*, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x7DC | 0x8009C3B8 | size: 0x44
//  */
// void FindItemByHashID<TLSlide>(TLSlide*, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8009C3FC | size: 0x14
//  */
// void BasicString<unsigned short, Detail::TempStringAllocator>::operator=(BasicString<unsigned short, Detail::TempStringAllocator>)
// {
// }

// /**
//  * Offset/Address/Size: 0x14 | 0x8009C410 | size: 0x94
//  */
// void BasicString<unsigned short, Detail::TempStringAllocator>::~BasicString()
// {
// }

// /**
//  * Offset/Address/Size: 0xA8 | 0x8009C4A4 | size: 0xF8
//  */
// void BasicString<unsigned short, Detail::TempStringAllocator>::BasicString(const unsigned short*)
// {
// }

// /**
//  * Offset/Address/Size: 0x1A0 | 0x8009C59C | size: 0x6B4
//  */
// void BasicString<unsigned short, Detail::TempStringAllocator>::insert(unsigned short*, const unsigned short*, const unsigned short*)
// {
// }

// /**
//  * Offset/Address/Size: 0x854 | 0x8009CC50 | size: 0x1EC
//  */
// void BasicString<unsigned short, Detail::TempStringAllocator>::erase(const unsigned short*, const unsigned short*)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8009CE3C | size: 0x8C
//  */
// void nlBSearch<nlLocalization::StringLookup, unsigned long>(const unsigned long&, nlLocalization::StringLookup*, int)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8009CEC8 | size: 0x2C
//  */
// void LexicalCast<BasicString<unsigned short, Detail::TempStringAllocator>, BasicString<unsigned short,
// Detail::TempStringAllocator>>(const BasicString<unsigned short, Detail::TempStringAllocator>&)
// {
// }

// /**
//  * Offset/Address/Size: 0x2C | 0x8009CEF4 | size: 0x28
//  */
// void Detail::LexicalCastImpl<BasicString<unsigned short, Detail::TempStringAllocator>, BasicString<unsigned short,
// Detail::TempStringAllocator>>::Do(const BasicString<unsigned short, Detail::TempStringAllocator>&)
// {
// }

// /**
//  * Offset/Address/Size: 0x54 | 0x8009CF1C | size: 0x2C
//  */
// void LexicalCast<BasicString<unsigned short, Detail::TempStringAllocator>, const unsigned short*>(const unsigned short* const&)
// {
// }

// /**
//  * Offset/Address/Size: 0x80 | 0x8009CF48 | size: 0xF4
//  */
// void Detail::LexicalCastImpl<BasicString<unsigned short, Detail::TempStringAllocator>, const unsigned short*>::Do(const unsigned short*
// const&)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8009D03C | size: 0x13C
//  */
// void Format<BasicString<unsigned short, Detail::TempStringAllocator>, BasicString<unsigned short, Detail::TempStringAllocator>,
// BasicString<unsigned short, Detail::TempStringAllocator>, BasicString<unsigned short, Detail::TempStringAllocator>>(const
// BasicString<unsigned short, Detail::TempStringAllocator>&, const BasicString<unsigned short, Detail::TempStringAllocator>&, const
// BasicString<unsigned short, Detail::TempStringAllocator>&, const BasicString<unsigned short, Detail::TempStringAllocator>&)
// {
// }

// /**
//  * Offset/Address/Size: 0x13C | 0x8009D178 | size: 0x28
//  */
// void FormatImpl<BasicString<unsigned short, Detail::TempStringAllocator>>::operator BasicString<unsigned short,
// Detail::TempStringAllocator>() const
// {
// }

// /**
//  * Offset/Address/Size: 0x164 | 0x8009D1A0 | size: 0xCF0
//  */
// void FormatImpl<BasicString<unsigned short, Detail::TempStringAllocator>>::operator%<BasicString<unsigned short,
// Detail::TempStringAllocator>>(const BasicString<unsigned short, Detail::TempStringAllocator>&)
// {
// }

// /**
//  * Offset/Address/Size: 0xE54 | 0x8009DE90 | size: 0x114
//  */
// void Format<BasicString<unsigned short, Detail::TempStringAllocator>, BasicString<unsigned short, Detail::TempStringAllocator>>(const
// BasicString<unsigned short, Detail::TempStringAllocator>&, const BasicString<unsigned short, Detail::TempStringAllocator>&)
// {
// }

// /**
//  * Offset/Address/Size: 0xF68 | 0x8009DFA4 | size: 0x118
//  */
// void Format<BasicString<unsigned short, Detail::TempStringAllocator>, unsigned short[4]>(const BasicString<unsigned short,
// Detail::TempStringAllocator>&, const unsigned short(&)[4])
// {
// }

// /**
//  * Offset/Address/Size: 0x1080 | 0x8009E0BC | size: 0xCF0
//  */
// void FormatImpl<BasicString<unsigned short, Detail::TempStringAllocator>>::operator%<const unsigned short*>(const unsigned short* const&)
// {
// }
