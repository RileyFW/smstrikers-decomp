#include "Game/SH/SHHealthWarning.h"

#include "Game/Audio/AudioLoader.h"
#include "Game/FE/FEAudio.h"
#include "Game/FE/feFinder.h"
#include "Game/FE/feInput.h"
#include "Game/FE/tlComponentInstance.h"
#include "NL/nlMemory.h"
#include "NL/nlString.h"
#include "NL/nlTask.h"

extern int g_Language;

// /**
//  * Offset/Address/Size: 0x2D4 | 0x8010DAA8 | size: 0x15C
//  */
// void FEFinder<TLComponentInstance, 4>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long,
// unsigned long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x250 | 0x8010DA24 | size: 0x84
//  */
// void FEFinder<TLComponentInstance, 4>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned
// long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x218 | 0x8010D9EC | size: 0x38
//  */
// void FEFinder<TLComponentInstance, 4>::Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher,
// InlineHasher)
// {
// }

// /**
//  * Offset/Address/Size: 0xBC | 0x8010D890 | size: 0x15C
//  */
// void FEFinder<TLImageInstance, 2>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned
// long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x38 | 0x8010D80C | size: 0x84
//  */
// void FEFinder<TLImageInstance, 2>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long,
// unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8010D7D4 | size: 0x38
//  */
// void FEFinder<TLImageInstance, 2>::Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher,
// InlineHasher)
// {
// }

/**
 * Offset/Address/Size: 0x5C8 | 0x8010D6F8 | size: 0xDC
 */
HealthWarningSceneV2::HealthWarningSceneV2()
    : BaseSceneHandler()
{
    const char* messageImageFilename = "art/fe/HealthSafetyUI.res";

    mMessageImage = NULL;
    mPressButtonImage = NULL;
    mElapsedTime = 0.0f;

    AsyncImage* messageImage = new (nlMalloc(0x1C, 0x20, 1)) AsyncImage(messageImageFilename, NULL);
    mMessageImage = messageImage;

    AsyncImage* pressButtonImage = new (nlMalloc(0x1C, 0x20, 1)) AsyncImage(messageImageFilename, NULL);
    mPressButtonImage = pressButtonImage;
}

/**
 * Offset/Address/Size: 0x514 | 0x8010D644 | size: 0xB4
 */
HealthWarningSceneV2::~HealthWarningSceneV2()
{
    if (mMessageImage != NULL)
    {
        delete mMessageImage;
    }

    if (mPressButtonImage != NULL)
    {
        delete mPressButtonImage;
    }
}

/**
 * Offset/Address/Size: 0x204 | 0x8010D334 | size: 0x310
 * TODO: 93.2% match - stack frame 0xA0 vs target 0x80 due InlineHasher temporary slot layout.
 */
void HealthWarningSceneV2::SceneCreated()
{
    TLImageInstance* pImage;
    TLComponentInstance* pComp;

    mMessageImage->mImageInstance = FEFinder<TLImageInstance, 2>::Find<TLSlide>(
        m_pFEPresentation->m_currentSlide,
        InlineHasher(nlStringLowerHash("Layer")),
        InlineHasher(nlStringLowerHash("health_and_safety_EU_english")),
        InlineHasher(0),
        InlineHasher(0),
        InlineHasher(0),
        InlineHasher(0));

    pImage = NULL;

    pComp = FEFinder<TLComponentInstance, 4>::Find<TLSlide>(
        m_pFEPresentation->m_currentSlide,
        InlineHasher(nlStringLowerHash("Layer")),
        InlineHasher(nlStringLowerHash("press")),
        InlineHasher(0),
        InlineHasher(0),
        InlineHasher(0),
        InlineHasher(0));

    pImage = FEFinder<TLImageInstance, 2>::Find<TLSlide>(
        pComp->GetActiveSlide(),
        InlineHasher(nlStringLowerHash("health_press")),
        InlineHasher(0),
        InlineHasher(0),
        InlineHasher(0),
        InlineHasher(0),
        InlineHasher(0));

    mPressButtonImage->mImageInstance = pImage;
    pImage->m_bVisible = false;
    mIsPressButtonVisible = false;

    switch (g_Language)
    {
    case 0:
        mMessageImage->QueueLoad("fe/health_and_safety/health_and_safety_US_english", false);
        mPressButtonImage->QueueLoad("fe/health_and_safety/health_and_safety_US_english_press", false);
        break;
    case 1:
        mMessageImage->QueueLoad("fe/health_and_safety/health_and_safety_EU_french", false);
        mPressButtonImage->QueueLoad("fe/health_and_safety/health_and_safety_EU_french_press", false);
        break;
    case 2:
        mMessageImage->QueueLoad("fe/health_and_safety/health_and_safety_EU_german", false);
        mPressButtonImage->QueueLoad("fe/health_and_safety/health_and_safety_EU_german_press", false);
        break;
    case 3:
        mMessageImage->QueueLoad("fe/health_and_safety/health_and_safety_EU_spanish", false);
        mPressButtonImage->QueueLoad("fe/health_and_safety/health_and_safety_EU_spanish_press", false);
        break;
    case 4:
        mMessageImage->QueueLoad("fe/health_and_safety/health_and_safety_EU_italian", false);
        mPressButtonImage->QueueLoad("fe/health_and_safety/health_and_safety_EU_italian_press", false);
        break;
    case 5:
        mMessageImage->QueueLoad("fe/health_and_safety/health_and_safety_EU_japan", false);
        mPressButtonImage->QueueLoad("fe/health_and_safety/health_and_safety_JP_japan_press", false);
        break;
    case 6:
        mMessageImage->QueueLoad("fe/health_and_safety/health_and_safety_EU_english", false);
        mPressButtonImage->QueueLoad("fe/health_and_safety/health_and_safety_EU_english_press", false);
        break;
    default:
        mMessageImage->QueueLoad("fe/health_and_safety/health_and_safety_US_english", false);
        mPressButtonImage->QueueLoad("fe/health_and_safety/health_and_safety_US_english_press", false);
        break;
    }
}

/**
 * Offset/Address/Size: 0x0 | 0x8010D130 | size: 0x204
 * TODO: 94.6% match - stack frame 0x90 vs target 0x80 (0x10 too large).
 * MWCC doesn't reuse InlineHasher by-value temp stack slots between the two Find calls.
 * Target interleaves re-zeroed first-Find slots with new second-Find slots; our compiler allocates fresh.
 * All diffs are stack/immediate offsets only - instructions, registers, and control flow are identical.
 */
void HealthWarningSceneV2::Update(float fDeltaT)
{
    bool proceed;
    TLComponentInstance* pComp;
    TLImageInstance* pImage;

    BaseSceneHandler::Update(fDeltaT);
    mMessageImage->Update(true);
    mPressButtonImage->Update(true);

    f32 newTime = mElapsedTime + fDeltaT;
    mElapsedTime = newTime;
    if (!(newTime >= 2.0f))
        return;

    proceed = false;

    if (!mIsPressButtonVisible)
    {
        AudioLoader::LoadFEButtonSoundGroup();

        pComp = FEFinder<TLComponentInstance, 4>::Find<TLSlide>(
            m_pFEPresentation->m_currentSlide,
            InlineHasher(nlStringLowerHash("press")),
            InlineHasher(nlStringLowerHash("Layer")),
            InlineHasher(0),
            InlineHasher(0),
            InlineHasher(0),
            InlineHasher(0));

        pComp->SetActiveSlide("Slide1");
        pComp->Update(0.0f);

        pImage = FEFinder<TLImageInstance, 2>::Find<TLSlide>(
            pComp->GetActiveSlide(),
            InlineHasher(nlStringLowerHash("health_press")),
            InlineHasher(0),
            InlineHasher(0),
            InlineHasher(0),
            InlineHasher(0),
            InlineHasher(0));

        pImage->m_bVisible = true;
        mIsPressButtonVisible = true;
    }

    if (g_pFEInput->JustPressed((eFEINPUT_PAD)8, 0x24, true, NULL) || g_pFEInput->JustPressed((eFEINPUT_PAD)8, 0xF70, false, NULL))
    {
        proceed = true;
    }

    if (mElapsedTime >= 60.0f)
    {
        proceed = true;
    }

    if (proceed)
    {
        FEAudio::PlayAnimAudioEvent("sfx_screen_forward", false);
        nlTaskManager::SetNextState(0x80000);
    }
}
