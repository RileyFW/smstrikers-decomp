#include "Game/FE/Overlay/OverlayHandlerSummary.h"
#include "Game/FE/feFinder.h"
#include "Game/FE/feSlideMenu.h"
#include "Game/FE/FEAudio.h"
#include "Game/FE/feManager.h"
#include "Game/Audio/CrowdMood.h"
#include "Game/GameInfo.h"
#include "Game/OverlayManager.h"
#include "Game/SH/SHPause.h"

extern bool g_e3_Build;

// /**
//  * Offset/Address/Size: 0x468 | 0x800FF898 | size: 0x84
//  */
// void FEFinder<TLComponentInstance, 4>::_Find<FEPresentation>(FEPresentation*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x430 | 0x800FF860 | size: 0x38
//  */
// void FEFinder<TLComponentInstance, 4>::Find<FEPresentation>(FEPresentation*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher)
// {
// }

// /**
//  * Offset/Address/Size: 0x2D4 | 0x800FF704 | size: 0x15C
//  */
// void FEFinder<TLTextInstance, 3>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x250 | 0x800FF680 | size: 0x84
//  */
// void FEFinder<TLTextInstance, 3>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x218 | 0x800FF648 | size: 0x38
//  */
// void FEFinder<TLTextInstance, 3>::Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher)
// {
// }

// /**
//  * Offset/Address/Size: 0xBC | 0x800FF4EC | size: 0x15C
//  */
// void FEFinder<TLComponentInstance, 4>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x38 | 0x800FF468 | size: 0x84
//  */
// void FEFinder<TLComponentInstance, 4>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x800FF430 | size: 0x38
//  */
// void FEFinder<TLComponentInstance, 4>::Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher)
// {
// }

/**
 * Offset/Address/Size: 0x1D88 | 0x800FE928 | size: 0xB08
 */
SummaryOverlay::SummaryOverlay(SummaryOverlay::eSummaryContext)
    : BaseOverlayHandler(0x00000000)
{
}

/**
 * Offset/Address/Size: 0x1CEC | 0x800FE88C | size: 0x9C
 */
SummaryOverlay::~SummaryOverlay()
{
    if (mSlideMenu != NULL)
    {
        delete mSlideMenu;
    }
}

static const char* SUMMARY_SLIDE_NAME = "SUMMARY";
static const char* TOTAL_SUMMARY_SLIDE_NAME = "TOTAL SUMMARY";
static const char* USER_SLIDE_NAME = "USER";
static const char* TOTAL_USER_SLIDE_NAME = "TOTAL USER";

/**
 * Offset/Address/Size: 0x1B00 | 0x800FE6A0 | size: 0x1EC
 * TODO: 96.56% match - second Find<TLSlide> still places zero InlineHasher
 * temporaries in low stack slots (r7/r8/r9 from 0x10/0x0C/0x08) instead of
 * reusing first-call slots at 0x40/0x38/0x30.
 */
void SummaryOverlay::SceneCreated()
{
    CrowdMood::Purge(true);

    FEPresentation* presentation = m_pFEScene->m_pFEPackage->GetPresentation();

    TLComponentInstance* pComp = FEFinder<TLComponentInstance, 4>::Find<FEPresentation>(
        presentation,
        InlineHasher(nlStringLowerHash("Slide1")),
        InlineHasher(nlStringLowerHash("layer")),
        InlineHasher(nlStringLowerHash("summary")),
        InlineHasher(0),
        InlineHasher(0),
        InlineHasher(0));

    mSlideMenu = new (nlMalloc(sizeof(FESlideMenu), 8, false)) FESlideMenu(pComp);

    mSlideMenu->AddMenuItem(SUMMARY_SLIDE_NAME);

    if (mShowCumulativeStats)
    {
        mSlideMenu->AddMenuItem(TOTAL_SUMMARY_SLIDE_NAME);
        summaryOrder[1] = SUMMARY_CUMULATIVE_MATCH;
        summaryOrder[3] = SUMMARY_CUMULATIVE_MATCH;
    }

    if (mShowUserStats)
    {
        mSlideMenu->AddMenuItem(USER_SLIDE_NAME);
        if (mShowCumulativeStats)
        {
            mSlideMenu->AddMenuItem(TOTAL_USER_SLIDE_NAME);
            summaryOrder[2] = SUMMARY_USER;
            summaryOrder[3] = SUMMARY_CUMULATIVE_USER;
        }
        else
        {
            summaryOrder[1] = SUMMARY_USER;
            summaryOrder[3] = SUMMARY_USER;
        }
    }

    mSlideMenu->m_doWrapAround = true;

    InlineHasher zero(0);

    mButtons.mButtonInstance = FEFinder<TLComponentInstance, 4>::Find<TLSlide>(
        presentation->m_currentSlide,
        InlineHasher(nlStringLowerHash("Layer")),
        InlineHasher(nlStringLowerHash("buttons")),
        InlineHasher(0),
        zero,
        zero,
        zero);

    mButtons.SetState(mButtonState);
}

/**
 * Offset/Address/Size: 0x1834 | 0x800FE3D4 | size: 0x2CC
 */
void SummaryOverlay::Update(float fDeltaT)
{
    BaseSceneHandler::Update(fDeltaT);
    mButtons.CentreButtons();

    if (!mSummaryDisplayed)
    {
        DisplayMatchSummary(SUMMARY_MATCH);
        mSummaryDisplayed = true;
    }

    if (g_pFEInput->JustPressed(m_controllingInput, PAD_TRIGGER_L, false, NULL)
        && (FrontEnd::m_feStateCurrent != FE_ALL_PADS || mContext == PAUSE))
    {
        if (mSlideMenu->PrevItem())
        {
            mCurrentSummaryIndex--;
            if (mCurrentSummaryIndex < 0)
            {
                mCurrentSummaryIndex = NUM_SUMMARIES - 1;
            }

            eSummaryType summaryType = summaryOrder[mCurrentSummaryIndex];
            if (summaryType == SUMMARY_MATCH || summaryType == SUMMARY_CUMULATIVE_MATCH)
            {
                DisplayMatchSummary(summaryType);
            }
            else
            {
                DisplayUserSummary(summaryType);
            }
        }
    }
    else if (g_pFEInput->JustPressed(m_controllingInput, PAD_TRIGGER_R, false, NULL)
             && (FrontEnd::m_feStateCurrent != FE_ALL_PADS || mContext == PAUSE))
    {
        if (mSlideMenu->NextItem())
        {
            mCurrentSummaryIndex++;
            if (mCurrentSummaryIndex == NUM_SUMMARIES)
            {
                mCurrentSummaryIndex = 0;
            }

            eSummaryType summaryType = summaryOrder[mCurrentSummaryIndex];
            if (summaryType == SUMMARY_MATCH || summaryType == SUMMARY_CUMULATIVE_MATCH)
            {
                DisplayMatchSummary(summaryType);
            }
            else
            {
                DisplayUserSummary(summaryType);
            }
        }
    }

    bool showAButton = mButtonState == ButtonComponent::BS_A_AND_B || mButtonState == ButtonComponent::BS_A_ONLY;
    bool showBButton = mButtonState == ButtonComponent::BS_A_AND_B || mButtonState == ButtonComponent::BS_B_ONLY;

    if (mContext == PAUSE)
    {
        if (showBButton && g_pFEInput->JustPressed(m_controllingInput, PAD_BUTTON_B, false, NULL))
        {
            PauseMenuScene* pauseScene = (PauseMenuScene*)nlSingleton<OverlayManager>::s_pInstance->Push(IGSCENE_PAUSE, SCREEN_BACK, true);
            pauseScene->mStartAnimAtEnd = true;
            FEAudio::PlayAnimAudioEvent("sfx_back", false);
        }
    }
    else if (mContext == ENDGAME)
    {
        if (showAButton && g_pFEInput->JustPressed(FE_ALL_PADS, PAD_BUTTON_A, false, NULL))
        {
            if (FrontEnd::m_feStateCurrent != FE_ALL_PADS)
            {
                if (nlSingleton<GameInfoManager>::s_pInstance->mCurrentMode == GameInfoManager::GM_FRIENDLY)
                {
                    if (g_e3_Build)
                    {
                        FrontEnd::ReturnToFE();
                    }
                    else
                    {
                        nlSingleton<OverlayManager>::s_pInstance->Push(IGSCENE_PAUSE_POST_GAME, SCREEN_FORWARD, true);
                    }
                }
                else
                {
                    FrontEnd::ReturnToFE();
                }

                FEAudio::PlayAnimAudioEvent("sfx_accept", false);
            }
        }
    }
}

/**
 * Offset/Address/Size: 0xA74 | 0x800FD614 | size: 0xDC0
 */
void SummaryOverlay::DisplayMatchSummary(eSummaryType)
{
    FORCE_DONT_INLINE;
}

/**
 * Offset/Address/Size: 0x0 | 0x800FCBA0 | size: 0xA74
 */
void SummaryOverlay::DisplayUserSummary(eSummaryType)
{
    FORCE_DONT_INLINE;
}
