#include "Game/SH/SHCupTrophy.h"

#include "Game/FE/feFinder.h"
#include "Game/FE/tlComponentInstance.h"

// /**
//  * Offset/Address/Size: 0x0 | 0x800CDAC8 | size: 0x38
//  */
// void Bind<void, Detail::MemFunImpl<void, void (CupTrophyScene::*)()>, CupTrophyScene*>(Detail::MemFunImpl<void, void
// (CupTrophyScene::*)()>,
//                                                                                        CupTrophyScene* const&)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x800CDAAC | size: 0x1C
//  */
// void MemFun<CupTrophyScene, void>(void (CupTrophyScene::*)())
// {
// }

// /**
//  * Offset/Address/Size: 0xFB4 | 0x800CD994 | size: 0x118
//  */
// void Format<BasicString<unsigned short, Detail::TempStringAllocator>, unsigned short[32]>(
//     const BasicString<unsigned short, Detail::TempStringAllocator>&, const unsigned short (&)[32])
// {
// }

// /**
//  * Offset/Address/Size: 0xE5C | 0x800CD83C | size: 0x158
//  */
// void Format<BasicString<unsigned short, Detail::TempStringAllocator>, unsigned short[16], unsigned short[16], unsigned short[16],
//             const unsigned short*, const unsigned short*>(const BasicString<unsigned short, Detail::TempStringAllocator>&,
//                                                           const unsigned short (&)[16], const unsigned short (&)[16],
//                                                           const unsigned short (&)[16], const unsigned short* const&,
//                                                           const unsigned short* const&)
// {
// }

// /**
//  * Offset/Address/Size: 0x16C | 0x800CCB4C | size: 0xCF0
//  */
// void FormatImpl<BasicString<unsigned short, Detail::TempStringAllocator>>::operator% <const unsigned short*>(const unsigned short*
// const&)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x800CC9E0 | size: 0x16C
//  */
// void Format<BasicString<unsigned short, Detail::TempStringAllocator>, unsigned short[16], unsigned short[16], unsigned short[16],
//             const unsigned short*, const unsigned short*, const unsigned short*>(
//     const BasicString<unsigned short, Detail::TempStringAllocator>&, const unsigned short (&)[16], const unsigned short (&)[16],
//     const unsigned short (&)[16], const unsigned short* const&, const unsigned short* const&, const unsigned short* const&)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x800CC984 | size: 0x5C
//  */
// void Function0<void>::FunctorImpl<BindExp1<void, Detail::MemFunImpl<void, void (CupTrophyScene::*)()>, CupTrophyScene*>>::~FunctorImpl()
// {
// }

// /**
//  * Offset/Address/Size: 0x78 | 0x800CC954 | size: 0x30
//  */
// void Function0<void>::FunctorImpl<BindExp1<void, Detail::MemFunImpl<void, void (CupTrophyScene::*)()>, CupTrophyScene*>>::operator()()
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x800CC8DC | size: 0x78
//  */
// void Function0<void>::FunctorImpl<BindExp1<void, Detail::MemFunImpl<void, void (CupTrophyScene::*)()>, CupTrophyScene*>>::Clone() const
// {
// }

// /**
//  * Offset/Address/Size: 0xBC | 0x800CC6F8 | size: 0x1E4
//  */
// void BasicString<char, Detail::TempStringAllocator>::AppendInPlace<Detail::TempStringAllocator>(
//     const BasicString<char, Detail::TempStringAllocator>&)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x800CC63C | size: 0xBC
//  */
// void BasicString<char, Detail::TempStringAllocator>::Append<Detail::TempStringAllocator>(
//     const BasicString<char, Detail::TempStringAllocator>&) const
// {
// }

// /**
//  * Offset/Address/Size: 0x680 | 0x800CC5B8 | size: 0x84
//  */
// void FEFinder<TLComponentInstance, 4>::_Find<FEPresentation>(FEPresentation*, unsigned long, unsigned long, unsigned long, unsigned long,
//                                                              unsigned long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x648 | 0x800CC580 | size: 0x38
//  */
// void FEFinder<TLComponentInstance, 4>::Find<FEPresentation>(FEPresentation*, InlineHasher, InlineHasher, InlineHasher, InlineHasher,
//                                                             InlineHasher, InlineHasher)
// {
// }

// /**
//  * Offset/Address/Size: 0x4EC | 0x800CC424 | size: 0x15C
//  */
// void FEFinder<TLTextInstance, 3>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned
// long,
//                                                     unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x468 | 0x800CC3A0 | size: 0x84
//  */
// void FEFinder<TLTextInstance, 3>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long,
//                                                  unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x430 | 0x800CC368 | size: 0x38
//  */
// void FEFinder<TLTextInstance, 3>::Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher,
//                                                 InlineHasher)
// {
// }

// /**
//  * Offset/Address/Size: 0x2D4 | 0x800CC20C | size: 0x15C
//  */
// void FEFinder<TLImageInstance, 2>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned
// long,
//                                                      unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x250 | 0x800CC188 | size: 0x84
//  */
// void FEFinder<TLImageInstance, 2>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long,
//                                                   unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x218 | 0x800CC150 | size: 0x38
//  */
// void FEFinder<TLImageInstance, 2>::Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher,
//                                                  InlineHasher)
// {
// }

// /**
//  * Offset/Address/Size: 0xBC | 0x800CBFF4 | size: 0x15C
//  */
// void FEFinder<TLComponentInstance, 4>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long,
//                                                          unsigned long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x38 | 0x800CBF70 | size: 0x84
//  */
// void FEFinder<TLComponentInstance, 4>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned
// long,
//                                                       unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x800CBF38 | size: 0x38
//  */
// void FEFinder<TLComponentInstance, 4>::Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher,
//                                                      InlineHasher)
// {
// }

/**
 * Offset/Address/Size: 0x27B0 | 0x800CBE64 | size: 0xD4
 */
CupTrophyScene::CupTrophyScene()
{
}

/**
 * Offset/Address/Size: 0x270C | 0x800CBDC0 | size: 0xA4
 */
CupTrophyScene::~CupTrophyScene()
{
}

/**
 * Offset/Address/Size: 0x1F54 | 0x800CB608 | size: 0x7B8
 */
void CupTrophyScene::SceneCreated()
{
}

/**
 * Offset/Address/Size: 0x1D70 | 0x800CB424 | size: 0x1E4
 */
void CupTrophyScene::HandleUnlockedTriggers()
{
}

/**
 * Offset/Address/Size: 0x1970 | 0x800CB024 | size: 0x400
 */
void CupTrophyScene::Update(float)
{
}

/**
 * Offset/Address/Size: 0x191C | 0x800CAFD0 | size: 0x54
 */
void CupTrophyScene::CreateTrophyScene(eTrophyType trophy, ButtonComponent::ButtonState buttonState, bool isNew)
{
    mTrophy = trophy;
    mIsNew = isNew;
    mCreated = 1;

    if (!mIsNew)
    {
        if (mTrophy < 4)
        {
            mFirstTrophy = TROPHY_MUSHROOM_CUP;
            mLastTrophy = TROPHY_BOWSER_CUP;
        }
        else
        {
            mFirstTrophy = TROPHY_SUPER_MUSHROOM_CUP;
            mLastTrophy = TROPHY_SUPER_BOWSER_CUP;
        }
    }

    mButtonState = buttonState;
}

/**
 * Offset/Address/Size: 0x1524 | 0x800CABD8 | size: 0x3F8
 */
void CupTrophyScene::SetWinRecord(Spoil&)
{
}

/**
 * Offset/Address/Size: 0x112C | 0x800CA7E0 | size: 0x3F8
 */
void CupTrophyScene::SetLossRecord(Spoil&)
{
}

/**
 * Offset/Address/Size: 0x170 | 0x800C9824 | size: 0xFBC
 */
void CupTrophyScene::SetHistory(Spoil&)
{
}

/**
 * Offset/Address/Size: 0x0 | 0x800C96B4 | size: 0x170
 */
void CupTrophyScene::ChangeSlides()
{
    typedef TLComponentInstance* (*FindCompByValue)(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher);
    typedef TLComponentInstance* (*FindCompByRef)(TLSlide*, InlineHasher&, InlineHasher&, InlineHasher&, InlineHasher&, InlineHasher&, InlineHasher&);

    FEPresentation* pres = m_pFEPresentation;
    float starTime;
    unsigned long hash;
    volatile InlineHasher hB, hA;
    volatile InlineHasher h9, h8;
    volatile InlineHasher h7, h6, h5, h4, h3, h2, h1, h0;

    if (mFirstSlideChange)
    {
        union
        {
            FindCompByValue byValue;
            FindCompByRef byRef;
        } findComp;

        findComp.byValue = FEFinder<TLComponentInstance, 4>::Find<TLSlide>;

        h0.m_Hash = 0;
        h1.m_Hash = 0;
        h2.m_Hash = 0;
        h3.m_Hash = 0;
        h4.m_Hash = 0;
        h5.m_Hash = 0;
        h6.m_Hash = 0;
        h7.m_Hash = 0;

        hash = nlStringLowerHash("star rotation");
        h8.m_Hash = hash;
        h9.m_Hash = hash;

        hash = nlStringLowerHash("Layer");
        hB.m_Hash = hash;
        hA.m_Hash = hash;

        TLComponentInstance* starComp = findComp.byRef(
            pres->m_currentSlide,
            (InlineHasher&)hB,
            (InlineHasher&)h9,
            (InlineHasher&)h7,
            (InlineHasher&)h5,
            (InlineHasher&)h3,
            (InlineHasher&)h1);
        starTime = starComp->GetActiveSlide()->m_time;
    }

    pres->SetActiveSlide("IN2");
    pres->Update(0.0f);

    if (mFirstSlideChange)
    {
        union
        {
            FindCompByValue byValue;
            FindCompByRef byRef;
        } findComp;
        volatile InlineHasher g7, g6;
        volatile InlineHasher g5, g4, g3, g2, g1, g0;

        findComp.byValue = FEFinder<TLComponentInstance, 4>::Find<TLSlide>;

        g0.m_Hash = 0;
        h1.m_Hash = 0;
        g1.m_Hash = 0;
        h3.m_Hash = 0;
        g2.m_Hash = 0;
        h5.m_Hash = 0;
        g3.m_Hash = 0;
        h7.m_Hash = 0;

        hash = nlStringLowerHash("star rotation");
        g4.m_Hash = hash;
        g5.m_Hash = hash;

        hash = nlStringLowerHash("Layer");
        g7.m_Hash = hash;
        g6.m_Hash = hash;

        TLComponentInstance* starComp = findComp.byRef(
            pres->m_currentSlide,
            (InlineHasher&)g7,
            (InlineHasher&)g5,
            (InlineHasher&)h7,
            (InlineHasher&)h5,
            (InlineHasher&)h3,
            (InlineHasher&)h1);
        starComp->Update(starTime);
        mFirstSlideChange = false;
    }

    SceneCreated();
}
