#include "Game/SH/SHCredits.h"
#include "Game/FE/tlComponentInstance.h"
#include "Game/FE/tlImageInstance.h"

// /**
//  * Offset/Address/Size: 0x570 | 0x80110374 | size: 0x15C
//  */
// void FEFinder<TLTextInstance, 3>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned
// long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x4EC | 0x801102F0 | size: 0x84
//  */
// void FEFinder<TLTextInstance, 3>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long,
// unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x468 | 0x8011026C | size: 0x84
//  */
// void FEFinder<TLTextInstance, 3>::_Find<FEPresentation>(FEPresentation*, unsigned long, unsigned long, unsigned long, unsigned long,
// unsigned long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x430 | 0x80110234 | size: 0x38
//  */
// void FEFinder<TLTextInstance, 3>::Find<FEPresentation>(FEPresentation*, InlineHasher, InlineHasher, InlineHasher, InlineHasher,
// InlineHasher, InlineHasher)
// {
// }

// /**
//  * Offset/Address/Size: 0x2D4 | 0x801100D8 | size: 0x15C
//  */
// void FEFinder<TLImageInstance, 2>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned
// long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x250 | 0x80110054 | size: 0x84
//  */
// void FEFinder<TLImageInstance, 2>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long,
// unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x218 | 0x8011001C | size: 0x38
//  */
// void FEFinder<TLImageInstance, 2>::Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher,
// InlineHasher)
// {
// }

// /**
//  * Offset/Address/Size: 0xBC | 0x8010FEC0 | size: 0x15C
//  */
// void FEFinder<TLComponentInstance, 4>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long,
// unsigned long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x38 | 0x8010FE3C | size: 0x84
//  */
// void FEFinder<TLComponentInstance, 4>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned
// long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8010FE04 | size: 0x38
//  */
// void FEFinder<TLComponentInstance, 4>::Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher,
// InlineHasher)
// {
// }

/**
 * Offset/Address/Size: 0xBCC | 0x8010FD28 | size: 0xDC
 */
CreditScene::CreditScene()
{
}

/**
 * Offset/Address/Size: 0xB40 | 0x8010FC9C | size: 0x8C
 */
CreditScene::~CreditScene()
{
}

/**
 * Offset/Address/Size: 0xB20 | 0x8010FC7C | size: 0x20
 */
void CreditScene::SceneCreated()
{
    SetupForPhase();
}

/**
 * Offset/Address/Size: 0xA80 | 0x8010FBDC | size: 0xA0
 */
void CreditScene::Update(float dt)
{
    BaseSceneHandler::Update(dt);
    switch ((s32)mCreditParser.mFileData)
    {
    case 2:
        UpdateForCredits(dt);
        break;
    case 3:
        UpdateForCopyrightMessage(dt);
        break;
    case 1:
        UpdateForNintendoLogo(dt);
        break;
    case 0:
        UpdateForNLGMovie(dt);
        break;
    default:
        break;
    }
}

/**
 * Offset/Address/Size: 0x978 | 0x8010FAD4 | size: 0x108
 */
void CreditScene::SetupForPhase()
{
    FORCE_DONT_INLINE;
    *(u8*)&mTimeElapsed = 0;
    *(f32*)&mCreditParser.mFileSize = 0.0f;

    switch ((s32)mCreditParser.mFileData)
    {
    case 0:
        SetupForNLGMovie();
        break;
    case 1:
        m_pFEPresentation->SetActiveSlide("copyright");
        m_pFEPresentation->m_currentSlide->Update(0.0f);
        break;
    case 2:
        SetupForCredits();
        break;
    case 3:
        m_pFEPresentation->SetActiveSlide("nintendologo");
        m_pFEPresentation->m_currentSlide->Update(0.0f);
        break;
    case 4:
    {
        nlSingleton<GameSceneManager>::s_pInstance->Push(mNextScene, SCREEN_NOTHING, true);
        if (mNextScene == SCENE_OPTIONS)
        {
            FEMusic::StartStreamIfDifferent(7);
        }
        else
        {
            FEMusic::StartStreamIfDifferent(0);
        }
        mNextScene = SCENE_MAIN_MENU;
        break;
    }
    }
}

/**
 * Offset/Address/Size: 0x94C | 0x8010FAA8 | size: 0x2C
 */
void CreditScene::GotoNextPhase()
{
    FORCE_DONT_INLINE;
    mCreditParser.mFileData++;
    SetupForPhase();
}

/**
 * Offset/Address/Size: 0x6E4 | 0x8010F840 | size: 0x268
 */
void CreditScene::SetupForCredits()
{
    FORCE_DONT_INLINE;
}

/**
 * Offset/Address/Size: 0x60C | 0x8010F768 | size: 0xD8
 */
void CreditScene::SetupForNLGMovie()
{
    BaseSceneHandler* pScene = nlSingleton<GameSceneManager>::s_pInstance->Push(SCENE_NLG_MOVIE, SCREEN_NOTHING, false);
    ((u8*)pScene)[0xAA] = 0;

    nlSingleton<FESceneManager>::s_pInstance->ForceImmediateStackProcessing();

    m_pFEPresentation->SetActiveSlide("nlg");

    typedef TLImageInstance* (*FindByValue)(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher);
    typedef TLImageInstance* (*FindByRef)(TLSlide*, InlineHasher&, InlineHasher&, InlineHasher&, InlineHasher&, InlineHasher&, InlineHasher&);
    union
    {
        FindByValue byValue;
        FindByRef byRef;
    } findImg;
    findImg.byValue = FEFinder<TLImageInstance, 2>::Find<TLSlide>;

    volatile InlineHasher lRef, lLocal;
    volatile InlineHasher nRef, nLocal;
    volatile InlineHasher h, g, f, e, d, c, b, a;
    a.m_Hash = 0;
    b.m_Hash = 0;
    c.m_Hash = 0;
    d.m_Hash = 0;
    e.m_Hash = 0;
    f.m_Hash = 0;
    g.m_Hash = 0;
    h.m_Hash = 0;
    u32 hash1 = nlStringLowerHash("NLG Logo");
    nLocal.m_Hash = hash1;
    nRef.m_Hash = hash1;
    u32 hash2 = nlStringLowerHash("Layer");
    lRef.m_Hash = hash2;
    lLocal.m_Hash = hash2;
    TLImageInstance* pImage = findImg.byRef(
        m_pFEPresentation->m_currentSlide, (InlineHasher&)lRef, (InlineHasher&)nRef, (InlineHasher&)h, (InlineHasher&)f, (InlineHasher&)d, (InlineHasher&)b);
    pImage->m_bVisible = false;
}

/**
 * Offset/Address/Size: 0x554 | 0x8010F6B0 | size: 0xB8
 */
void CreditScene::UpdateForCopyrightMessage(float dt)
{
    TLComponentInstance* pWhiteFade = GetWhiteFadeComponent();
    f32 timeElapsed = *(f32*)&mCreditParser.mFileSize;
    timeElapsed += dt;
    *(f32*)&mCreditParser.mFileSize = timeElapsed;
    if (timeElapsed < 1.0f)
    {
        return;
    }
    TLSlide* pSlide = pWhiteFade->GetActiveSlide();
    f32 slideEnd = pSlide->m_start + pSlide->m_duration;
    TLSlide* pSlide2 = pWhiteFade->GetActiveSlide();
    if (pSlide2->m_time >= slideEnd)
    {
        if (!*(u8*)&mTimeElapsed)
        {
            pWhiteFade->SetActiveSlide("credits");
            *(u8*)&mTimeElapsed = 1;
        }
        else
        {
            GotoNextPhase();
        }
    }
}

/**
 * Offset/Address/Size: 0x1BC | 0x8010F318 | size: 0x398
 */
void CreditScene::UpdateForCredits(float)
{
    FORCE_DONT_INLINE;
}

/**
 * Offset/Address/Size: 0x104 | 0x8010F260 | size: 0xB8
 */
void CreditScene::UpdateForNintendoLogo(float dt)
{
    TLComponentInstance* pWhiteFade = GetWhiteFadeComponent();
    f32 timeElapsed = *(f32*)&mCreditParser.mFileSize;
    timeElapsed += dt;
    *(f32*)&mCreditParser.mFileSize = timeElapsed;
    if (timeElapsed < 1.0f)
    {
        return;
    }
    TLSlide* pSlide = pWhiteFade->GetActiveSlide();
    f32 slideEnd = pSlide->m_start + pSlide->m_duration;
    TLSlide* pSlide2 = pWhiteFade->GetActiveSlide();
    if (pSlide2->m_time >= slideEnd)
    {
        if (!*(u8*)&mTimeElapsed)
        {
            pWhiteFade->SetActiveSlide("FADEIN");
            *(u8*)&mTimeElapsed = 1;
        }
        else
        {
            GotoNextPhase();
        }
    }
}

/**
 * Offset/Address/Size: 0x98 | 0x8010F1F4 | size: 0x6C
 */
void CreditScene::UpdateForNLGMovie(float)
{
    FORCE_DONT_INLINE;
    if (FESceneManager::GetInstance()->AreAllScenesValid())
    {
        GameSceneManager* pGameSceneMgr = GameSceneManager::GetInstance();
        BaseSceneHandler* pCurrentScene;
        if (pGameSceneMgr->mCurrentStackDepth != 0)
        {
            pCurrentScene = pGameSceneMgr->mBaseSceneHandlerStack[pGameSceneMgr->mCurrentStackDepth - 1];
        }
        else
        {
            pCurrentScene = NULL;
        }
        if (pCurrentScene == this)
        {
            GotoNextPhase();
        }
    }
}

/**
 * Offset/Address/Size: 0x0 | 0x8010F15C | size: 0x98
 */
TLComponentInstance* CreditScene::GetWhiteFadeComponent()
{
    typedef TLComponentInstance* (*FindByValue)(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher);
    typedef TLComponentInstance* (*FindByRef)(TLSlide*, InlineHasher&, InlineHasher&, InlineHasher&, InlineHasher&, InlineHasher&, InlineHasher&);
    union
    {
        FindByValue byValue;
        FindByRef byRef;
    } findComp;
    findComp.byValue = FEFinder<TLComponentInstance, 4>::Find<TLSlide>;

    volatile InlineHasher lRef, lLocal;
    volatile InlineHasher wRef, wLocal;
    volatile InlineHasher h, g, f, e, d, c, b, a;
    a.m_Hash = 0;
    b.m_Hash = 0;
    c.m_Hash = 0;
    d.m_Hash = 0;
    e.m_Hash = 0;
    f.m_Hash = 0;
    g.m_Hash = 0;
    h.m_Hash = 0;
    u32 hash1 = nlStringLowerHash("WHITE FADE");
    wLocal.m_Hash = hash1;
    wRef.m_Hash = hash1;
    u32 hash2 = nlStringLowerHash("Layer");
    lRef.m_Hash = hash2;
    lLocal.m_Hash = hash2;
    return findComp.byRef(
        m_pFEPresentation->m_currentSlide, (InlineHasher&)lRef, (InlineHasher&)wRef, (InlineHasher&)h, (InlineHasher&)f, (InlineHasher&)d, (InlineHasher&)b);
}
