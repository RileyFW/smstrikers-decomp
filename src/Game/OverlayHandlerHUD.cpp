#include "Game/OverlayHandlerHUD.h"
#include "Game/Team.h"
#include "Game/Sys/eventman.h"
#include "Game/FE/tlComponentInstance.h"
#include "NL/nlLexicalCast.h"

extern cTeam* g_pTeams[];

struct PowerupAcquireEventData : public EventData
{
    virtual u32 GetID();

    int mHomeAway;
};

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
// u32 PowerupAcquireEventData::GetID()
// {
//     return 0x1C3;
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
    FETextureResource* texture[2];

    for (int homeAway = 0; homeAway < 2; homeAway++)
    {
        for (int i = 0; i < 2; i++)
        {
            int numPowerups = g_pTeams[homeAway]->GetPowerUpByIndex(i).nnumOfPowerups;

            switch (g_pTeams[homeAway]->GetPowerUpByIndex(i).eType)
            {
            case POWER_UP_NONE:
                texture[i] = NULL;
                break;
            case POWER_UP_GREEN_SHELL:
                texture[i] = m_pShellGreen;
                break;
            case POWER_UP_SPINY_SHELL:
                texture[i] = m_pShellSpike;
                break;
            case POWER_UP_FREEZE_SHELL:
                texture[i] = m_pShellBlue;
                break;
            case POWER_UP_RED_SHELL:
                texture[i] = m_pShellRed;
                break;
            case POWER_UP_MUSHROOM:
                texture[i] = m_pMushroom;
                break;
            case POWER_UP_BANANA:
                texture[i] = m_pBanana;
                break;
            case POWER_UP_BOBOMB:
                texture[i] = m_pBobomb;
                break;
            case POWER_UP_STAR:
                texture[i] = m_pStar;
                break;
            case POWER_UP_CHAIN_CHOMP:
                texture[i] = m_pChomp;
                break;
            }

            if (texture[i] == NULL)
            {
                m_pImagePowerUps[0][homeAway][i]->m_bVisible = false;
                m_pImagePowerUps[1][homeAway][i]->m_bVisible = false;
                if (mNumFlareCycles[homeAway][i] >= 0)
                {
                    mNumFlareCycles[homeAway][i] = -1;
                    m_pImageFlares[0][homeAway][i]->m_bVisible = false;
                }
                m_pPowerupTextComponents[0][homeAway][i]->SetActiveSlide("1");
                m_pPowerupTextComponents[1][homeAway][i]->SetActiveSlide("1");
            }
            else
            {
                if (g_pTeams[homeAway]->GetPowerUpByIndex(i).bIsNew && mNumFlareCycles[homeAway][i] == -1)
                {
                    m_pImageFlares[0][homeAway][i]->m_bVisible = true;
                    m_pComponentFlares[homeAway][i]->SetActiveSlide("Slide1");
                    m_pComponentFlares[homeAway][i]->Update(0.0f);
                    mNumFlareCycles[homeAway][i] = 20;
                }
                else if (mNumFlareCycles[homeAway][i] != -1)
                {
                    TLSlide* activeSlide = m_pComponentFlares[homeAway][i]->GetActiveSlide();
                    if (activeSlide->m_time >= activeSlide->m_start + activeSlide->m_duration - 0.1f)
                    {
                        m_pImagePowerUps[0][homeAway][i]->m_bVisible = true;
                        m_pImagePowerUps[1][homeAway][i]->m_bVisible = true;
                        m_pImageFlares[0][homeAway][i]->m_bVisible = false;
                        m_pImageFlares[1][homeAway][i]->m_bVisible = false;
                        g_pTeams[homeAway]->SetIsPowerUpNew(i, false);
                        mNumFlareCycles[homeAway][i] = -1;

                        if (mIsHUDSlideIn)
                        {
                            PowerupAcquireEventData* data = new ((u8*)g_pEventManager->CreateValidEvent(0x69, 0x1C) + 0x10) PowerupAcquireEventData();
                            data->mHomeAway = homeAway;
                        }
                    }
                }
            }

            m_pImagePowerUps[0][homeAway][i]->m_component->pChildren = (TLSlide*)texture[i];
            m_pImagePowerUps[1][homeAway][i]->m_component->pChildren = (TLSlide*)texture[i];

            if (mNumFlareCycles[homeAway][i] == -1 && texture[i] != NULL)
            {
                m_pImagePowerUps[0][homeAway][i]->m_bVisible = true;
                m_pImagePowerUps[1][homeAway][i]->m_bVisible = true;
            }

            if (mNumFlareCycles[homeAway][i] != -1 || numPowerups == 1 || numPowerups == 0)
            {
                m_pPowerupTextComponents[0][homeAway][i]->SetActiveSlide("1");
                m_pPowerupTextComponents[1][homeAway][i]->SetActiveSlide("1");
            }
            else if (numPowerups == 3)
            {
                m_pPowerupTextComponents[0][homeAway][i]->SetActiveSlide("X3");
                m_pPowerupTextComponents[1][homeAway][i]->SetActiveSlide("X3");
            }
            else if (numPowerups == 5)
            {
                m_pPowerupTextComponents[0][homeAway][i]->SetActiveSlide("X5");
                m_pPowerupTextComponents[1][homeAway][i]->SetActiveSlide("X5");
            }
        }
    }
}

u32 PowerupAcquireEventData::GetID()
{
    return 0x1C3;
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
    for (int i = 0; i < 2; i++)
    {
        mScore[i] = 0;
        mNewScore[i] = 0;
        BasicString<char, Detail::TempStringAllocator> scoreStr = LexicalCast<BasicString<char, Detail::TempStringAllocator>, int>(mScore[i]);
        nlStrToWcs(scoreStr.c_str(), mScoreBuffer[i], 0x20);
        m_pTextInstanceScore[0][i]->SetString(mScoreBuffer[i]);
        m_pTextInstanceScore[1][i]->SetString(mScoreBuffer[i]);
    }
    mStartScoreAnimation = false;
}

/**
 * Offset/Address/Size: 0x0 | 0x800F62E0 | size: 0x188
 */
void HUDOverlay::SwapPowerUps(int homeAway)
{
    int temp = mNumFlareCycles[homeAway][0];
    mNumFlareCycles[homeAway][0] = mNumFlareCycles[homeAway][1];
    mNumFlareCycles[homeAway][1] = temp;

    f32 time0 = m_pComponentFlares[homeAway][0]->GetActiveSlide()->m_time;
    f32 time1 = m_pComponentFlares[homeAway][1]->GetActiveSlide()->m_time;

    m_pComponentFlares[homeAway][0]->SetActiveSlide("Slide1");
    m_pComponentFlares[homeAway][0]->Update(time1);
    m_pComponentFlares[homeAway][1]->SetActiveSlide("Slide1");
    m_pComponentFlares[homeAway][1]->Update(time0);

    for (int i = 0; i < 2; i++)
    {
        if (mNumFlareCycles[homeAway][i] == -1)
        {
            m_pImageFlares[0][homeAway][i]->m_bVisible = false;
            m_pImageFlares[1][homeAway][i]->m_bVisible = false;
            m_pImagePowerUps[0][homeAway][i]->m_bVisible = true;
            m_pImagePowerUps[1][homeAway][i]->m_bVisible = true;
        }
        else
        {
            m_pImageFlares[0][homeAway][i]->m_bVisible = true;
            m_pImageFlares[1][homeAway][i]->m_bVisible = true;
            m_pImagePowerUps[0][homeAway][i]->m_bVisible = false;
            m_pImagePowerUps[1][homeAway][i]->m_bVisible = false;
        }
    }
}
