#include "Game/SH/SHCupChooseCaptain.h"

// /**
//  * Offset/Address/Size: 0x4EC | 0x800DF878 | size: 0x15C
//  */
// void FEFinder<TLTextInstance, 3>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned
// long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x468 | 0x800DF7F4 | size: 0x84
//  */
// void FEFinder<TLTextInstance, 3>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long,
// unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x430 | 0x800DF7BC | size: 0x38
//  */
// void FEFinder<TLTextInstance, 3>::Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher,
// InlineHasher)
// {
// }

// /**
//  * Offset/Address/Size: 0x2D4 | 0x800DF660 | size: 0x15C
//  */
// void FEFinder<TLComponentInstance, 4>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long,
// unsigned long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x250 | 0x800DF5DC | size: 0x84
//  */
// void FEFinder<TLComponentInstance, 4>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned
// long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x218 | 0x800DF5A4 | size: 0x38
//  */
// void FEFinder<TLComponentInstance, 4>::Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher,
// InlineHasher)
// {
// }

// /**
//  * Offset/Address/Size: 0xBC | 0x800DF448 | size: 0x15C
//  */
// void FEFinder<TLImageInstance, 2>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned
// long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x38 | 0x800DF3C4 | size: 0x84
//  */
// void FEFinder<TLImageInstance, 2>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long,
// unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x800DF38C | size: 0x38
//  */
// void FEFinder<TLImageInstance, 2>::Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher,
// InlineHasher)
// {
// }

/**
 * Offset/Address/Size: 0x237C | 0x800DF248 | size: 0x144
 */
CupChooseCaptainSceneV2::CupChooseCaptainSceneV2(bool)
{
}

/**
 * Offset/Address/Size: 0x2168 | 0x800DF034 | size: 0x214
 */
CupChooseCaptainSceneV2::~CupChooseCaptainSceneV2()
{
}

/**
 * Offset/Address/Size: 0x1654 | 0x800DE520 | size: 0xB14
 */
void CupChooseCaptainSceneV2::SceneCreated()
{
}

/**
 * Offset/Address/Size: 0x109C | 0x800DDF68 | size: 0x5B8
 */
void CupChooseCaptainSceneV2::Update(float)
{
}

/**
 * Offset/Address/Size: 0xE9C | 0x800DDD68 | size: 0x200
 */
void CupChooseCaptainSceneV2::UpdateCaptainName()
{
}

/**
 * Offset/Address/Size: 0xC20 | 0x800DDAEC | size: 0x27C
 */
void CupChooseCaptainSceneV2::UpdateSKName()
{
}

/**
 * Offset/Address/Size: 0x330 | 0x800DD1FC | size: 0x8F0
 */
void CupChooseCaptainSceneV2::ChangeState(CupChooseCaptainSceneV2::eCupCaptainState, CupChooseCaptainSceneV2::eCupCaptainState)
{
}

/**
 * Offset/Address/Size: 0x15C | 0x800DD028 | size: 0x1D4
 */
void CupChooseCaptainSceneV2::CreateLineup()
{
}

/**
 * Offset/Address/Size: 0x0 | 0x800DCECC | size: 0x15C
 * TODO: 97.6% match - remaining mismatch is the early SidekickImageNames load
 * scheduling (`lis` for the table base before `li r5, 0`) plus local symbol
 * labeling (`SidekickImageNames$3` vs `SidekickImageNames$1112`) in scratch.
 */
void CupChooseCaptainSceneV2::StartSidekickMiniHead(eSidekickID sidekickId)
{
    static const char* SidekickImageNames[] = {
        "toad_minihead",
        "koopa_minihead",
        "hammerbros_minihead",
        "birdo_minihead",
    };

    typedef TLImageInstance* (*FindImageByValue)(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher);
    typedef TLImageInstance* (*FindImageByRef)(TLSlide*, InlineHasher&, InlineHasher&, InlineHasher&, InlineHasher&, InlineHasher&, InlineHasher&);

    union
    {
        FindImageByValue byValue;
        FindImageByRef byRef;
    } findImage;

    volatile InlineHasher hB, hA;
    volatile InlineHasher h9, h8;
    volatile InlineHasher h7, h6, h5, h4, h3, h2, h1, h0;

    if (sidekickId == SK_MYSTERY)
    {
        mSidekickMiniHead->m_bVisible = false;
        return;
    }

    findImage.byValue = FEFinder<TLImageInstance, 2>::Find<TLSlide>;
    TLComponentInstance* parentComp = mSKGrid->mParentComponent;

    h0.m_Hash = 0;
    h1.m_Hash = 0;
    h2.m_Hash = 0;
    h3.m_Hash = 0;
    h4.m_Hash = 0;
    h5.m_Hash = 0;
    h6.m_Hash = 0;
    h7.m_Hash = 0;
    h8.m_Hash = 0;
    h9.m_Hash = 0;

    const char** pNames = SidekickImageNames;
    unsigned long hash = nlStringLowerHash(pNames[sidekickId]);
    hA.m_Hash = hash;
    hB.m_Hash = hash;

    FETextureResource* texRes = findImage.byRef(
                                             parentComp->GetActiveSlide(),
                                             (InlineHasher&)hB,
                                             (InlineHasher&)h9,
                                             (InlineHasher&)h7,
                                             (InlineHasher&)h5,
                                             (InlineHasher&)h3,
                                             (InlineHasher&)h1)
                                    ->m_pTextureResource;

    volatile InlineHasher g7, g6;
    volatile InlineHasher g4, g3, g2, g1, g0;

    g0.m_Hash = 0;
    h1.m_Hash = 0;
    g1.m_Hash = 0;
    h3.m_Hash = 0;
    g2.m_Hash = 0;
    h5.m_Hash = 0;
    g3.m_Hash = 0;
    h7.m_Hash = 0;
    g4.m_Hash = 0;
    h9.m_Hash = 0;

    hash = nlStringLowerHash("sidekick_minihead");
    g7.m_Hash = hash;
    g6.m_Hash = hash;

    TLImageInstance* miniHead = findImage.byRef(
        mSidekickMiniHead->GetActiveSlide(),
        (InlineHasher&)g7,
        (InlineHasher&)h9,
        (InlineHasher&)h7,
        (InlineHasher&)h5,
        (InlineHasher&)h3,
        (InlineHasher&)h1);

    miniHead->m_component->pChildren = (TLSlide*)texRes;

    TLSlide* slide = mSidekickMiniHead->GetActiveSlide();
    mSidekickMiniHead->SetActiveSlide(slide);
    mSidekickMiniHead->Update(0.0f);
    mSidekickMiniHead->m_bVisible = true;
}
