#include "Game/OverlayHandlerHUD.h"
#include "Game/Team.h"
#include "Game/FE/tlComponentInstance.h"

extern cTeam* g_pTeams[];

/**
 * Offset/Address/Size: 0x124 | 0x800FA3BC | size: 0xCF0
 */

// void FormatImpl<BasicString<unsigned short, Detail::TempStringAllocator>>::operator%<const unsigned short*>(const unsigned short* const&)
// {
// }

/**
 * Offset/Address/Size: 0x0 | 0x800FA298 | size: 0x124
 */
// void Format<BasicString<unsigned short, Detail::TempStringAllocator>, unsigned short[8], unsigned short[8]>(const BasicString<unsigned short, Detail::TempStringAllocator>&, const unsigned short(&)[8], const unsigned short(&)[8])
// {
// }

/**
 * Offset/Address/Size: 0x0 | 0x800FA290 | size: 0x8
 */
// void PowerupAcquireEventData::GetID()
// {
// }

/**
 * Offset/Address/Size: 0x7C0 | 0x800FA20C | size: 0x84
 */
// void FEFinder<TLTextInstance, 3>::_Find<FEPresentation>(FEPresentation*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long)
// {
// }

/**
 * Offset/Address/Size: 0x788 | 0x800FA1D4 | size: 0x38
 */
// void FEFinder<TLTextInstance, 3>::Find<FEPresentation>(FEPresentation*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher)
// {
// }

/**
 * Offset/Address/Size: 0x62C | 0x800FA078 | size: 0x15C
 */
// void FEFinder<TLTextInstance, 3>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long)
// {
// }

/**
 * Offset/Address/Size: 0x5A8 | 0x800F9FF4 | size: 0x84
 */
// void FEFinder<TLTextInstance, 3>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long)
// {
// }

/**
 * Offset/Address/Size: 0x570 | 0x800F9FBC | size: 0x38
 */
// void FEFinder<TLTextInstance, 3>::Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher)
// {
// }

/**
 * Offset/Address/Size: 0x4EC | 0x800F9F38 | size: 0x84
 */
// void FEFinder<TLImageInstance, 2>::_Find<FEPresentation>(FEPresentation*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long)
// {
// }

/**
 * Offset/Address/Size: 0x4B4 | 0x800F9F00 | size: 0x38
 */
// void FEFinder<TLImageInstance, 2>::Find<FEPresentation>(FEPresentation*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher)
// {
// }

/**
 * Offset/Address/Size: 0x358 | 0x800F9DA4 | size: 0x15C
 */
// void FEFinder<TLComponentInstance, 4>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long)
// {
// }

/**
 * Offset/Address/Size: 0x2D4 | 0x800F9D20 | size: 0x84
 */
// void FEFinder<TLComponentInstance, 4>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long)
// {
// }

/**
 * Offset/Address/Size: 0x250 | 0x800F9C9C | size: 0x84
 */
// void FEFinder<TLComponentInstance, 4>::_Find<FEPresentation>(FEPresentation*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long)
// {
// }

/**
 * Offset/Address/Size: 0x218 | 0x800F9C64 | size: 0x38
 */
// void FEFinder<TLComponentInstance, 4>::Find<FEPresentation>(FEPresentation*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher)
// {
// }

/**
 * Offset/Address/Size: 0xBC | 0x800F9B08 | size: 0x15C
 */
// void FEFinder<TLImageInstance, 2>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long)
// {
// }

/**
 * Offset/Address/Size: 0x38 | 0x800F9A84 | size: 0x84
 */
// void FEFinder<TLImageInstance, 2>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long)
// {
// }

/**
 * Offset/Address/Size: 0x0 | 0x800F9A4C | size: 0x38
 */
// void FEFinder<TLImageInstance, 2>::Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher)
// {
// }

/**
 * Offset/Address/Size: 0x36B8 | 0x800F9998 | size: 0xB4
 */
HUDOverlay::HUDOverlay()
    : BaseOverlayHandler(2)
{
    mSeconds = -1;
    mTenths = 0;
    mClockColourChanged = false;
    mOvertimeSFXPlayed = false;
    mStartScoreAnimation = false;
    mNumFlareCycles[0][0] = -1;
    mScore[0] = 0;
    mNewScore[0] = 0;
    mScoreUpdateDelay[0] = 0.0f;
    mNumFlareCycles[0][1] = -1;
    mScore[0] = 0;
    mNewScore[0] = 0;
    mScoreUpdateDelay[0] = 0.0f;
    mNumFlareCycles[0][2] = -1;
    mScore[1] = 0;
    mNewScore[1] = 0;
    mScoreUpdateDelay[1] = 0.0f;
    mNumFlareCycles[0][3] = -1;
    mScore[1] = 0;
    mNewScore[1] = 0;
    mScoreUpdateDelay[1] = 0.0f;
}

/**
 * Offset/Address/Size: 0x35FC | 0x800F98DC | size: 0xBC
 */
HUDOverlay::~HUDOverlay()
{
    delete this->mAsyncImage[0];
    delete this->mAsyncImage[1];
}

/**
 * Offset/Address/Size: 0x2A1C | 0x800F8CFC | size: 0xBE0
 */
void HUDOverlay::Update(float)
{
}

/**
 * Offset/Address/Size: 0x2120 | 0x800F8400 | size: 0x8FC
 */
void HUDOverlay::SceneCreated()
{
}

/**
 * Offset/Address/Size: 0x20DC | 0x800F83BC | size: 0x44
 */
void HUDOverlay::SetSlideIn()
{
    FEPresentation* presentation;
    presentation = m_pFEScene->m_pFEPackage->GetPresentation();
    presentation->SetActiveSlide("IN");
    mIsHUDSlideIn = true;
}

/**
 * Offset/Address/Size: 0x2098 | 0x800F8378 | size: 0x44
 */
void HUDOverlay::SetSlideOut()
{
    FEPresentation* presentation;
    presentation = m_pFEScene->m_pFEPackage->GetPresentation();
    presentation->SetActiveSlide("OUT");
    mIsHUDSlideIn = false;
}

/**
 * Offset/Address/Size: 0x14BC | 0x800F779C | size: 0xBDC
 */
void HUDOverlay::LoadHUDTextures()
{
}

/**
 * Offset/Address/Size: 0x1168 | 0x800F7448 | size: 0x354
 */
void HUDOverlay::DisplayPowerUps()
{
}

/**
 * Offset/Address/Size: 0x3C0 | 0x800F66A0 | size: 0xDA8
 */
void HUDOverlay::SetTeamIcons()
{
}

/**
 * Offset/Address/Size: 0x39C | 0x800F667C | size: 0x24
 */
void HUDOverlay::UpdateScore()
{
    mNewScore[0] = g_pTeams[0]->m_nScore;
    mNewScore[1] = g_pTeams[1]->m_nScore;
}

/**
 * Offset/Address/Size: 0x2F0 | 0x800F65D0 | size: 0xAC
 */
void HUDOverlay::DisplayNewScore()
{
    for (int team = 0; team < 2; team++)
    {
        if (mNewScore[team] != mScore[team])
        {
            mScoreUpdateDelay[team] = 0.0f;
            mStartScoreAnimation = true;
        }

        for (int flare = 0; flare < 2; flare++)
        {
            if (mNumFlareCycles[team][flare] != -1)
            {
                mNumFlareCycles[team][flare] = 20;
                m_pComponentFlares[team][flare]->SetActiveSlide("Slide1");
                m_pComponentFlares[team][flare]->Update(0.0f);
            }
        }
    }
}

/**
 * Offset/Address/Size: 0x188 | 0x800F6468 | size: 0x168
 */
void HUDOverlay::ResetScores()
{
}

/**
 * Offset/Address/Size: 0x0 | 0x800F62E0 | size: 0x188
 */
void HUDOverlay::SwapPowerUps(int)
{
}
