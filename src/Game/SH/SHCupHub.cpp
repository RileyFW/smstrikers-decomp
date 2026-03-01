#include "Game/SH/SHCupHub.h"

#include "Game/GameSceneManager.h"
#include "Game/BaseGameSceneManager.h"
#include "Game/FE/feFinder.h"
#include "Game/FE/feHelpFuncs.h"
#include "Game/GameInfo.h"
#include "NL/nlMath.h"
#include "NL/nlPrint.h"

static const char* CUP_HUB_LAYER_NAME;
static nlColour HUB_COLOUR_HIGHLIGHT;
static char* HUBstandingsRowNames[10];

extern "C" eTeamID FindWinningTeam__15GameInfoManagerFv(GameInfoManager*);

// /**
//  * Offset/Address/Size: 0x0 | 0x800F1F90 | size: 0x38
//  */
// void Bind<void, Detail::MemFunImpl<void, void (CupHubScene::*)()>, CupHubScene*>(Detail::MemFunImpl<void, void (CupHubScene::*)()>,
// CupHubScene* const&)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x800F1F74 | size: 0x1C
//  */
// void MemFun<CupHubScene, void>(void (CupHubScene::*)())
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x800F1F18 | size: 0x5C
//  */
// void Function0<void>::FunctorImpl<BindExp1<void, Detail::MemFunImpl<void, void (CupHubScene::*)()>, CupHubScene*>>::~FunctorImpl()
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x800F1EB4 | size: 0x64
//  */
// TeamStats::TeamStats()
// {
// }

// /**
//  * Offset/Address/Size: 0x78 | 0x800F1E84 | size: 0x30
//  */
// void Function0<void>::FunctorImpl<BindExp1<void, Detail::MemFunImpl<void, void (CupHubScene::*)()>, CupHubScene*>>::operator()()
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x800F1E0C | size: 0x78
//  */
// void Function0<void>::FunctorImpl<BindExp1<void, Detail::MemFunImpl<void, void (CupHubScene::*)()>, CupHubScene*>>::Clone() const
// {
// }

// /**
//  * Offset/Address/Size: 0x680 | 0x800F1D88 | size: 0x84
//  */
// void FEFinder<TLComponentInstance, 4>::_Find<FEPresentation>(FEPresentation*, unsigned long, unsigned long, unsigned long, unsigned long,
// unsigned long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x648 | 0x800F1D50 | size: 0x38
//  */
// void FEFinder<TLComponentInstance, 4>::Find<FEPresentation>(FEPresentation*, InlineHasher, InlineHasher, InlineHasher, InlineHasher,
// InlineHasher, InlineHasher)
// {
// }

// /**
//  * Offset/Address/Size: 0x4EC | 0x800F1BF4 | size: 0x15C
//  */
// void FEFinder<TLComponentInstance, 4>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long,
// unsigned long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x468 | 0x800F1B70 | size: 0x84
//  */
// void FEFinder<TLComponentInstance, 4>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned
// long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x430 | 0x800F1B38 | size: 0x38
//  */
// void FEFinder<TLComponentInstance, 4>::Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher,
// InlineHasher)
// {
// }

// /**
//  * Offset/Address/Size: 0x2D4 | 0x800F19DC | size: 0x15C
//  */
// void FEFinder<TLTextInstance, 3>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned
// long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x250 | 0x800F1958 | size: 0x84
//  */
// void FEFinder<TLTextInstance, 3>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long,
// unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x218 | 0x800F1920 | size: 0x38
//  */
// void FEFinder<TLTextInstance, 3>::Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher,
// InlineHasher)
// {
// }

// /**
//  * Offset/Address/Size: 0xBC | 0x800F17C4 | size: 0x15C
//  */
// void FEFinder<TLImageInstance, 2>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned
// long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x38 | 0x800F1740 | size: 0x84
//  */
// void FEFinder<TLImageInstance, 2>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long,
// unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x800F1708 | size: 0x38
//  */
// void FEFinder<TLImageInstance, 2>::Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher,
// InlineHasher)
// {
// }

/**
 * Offset/Address/Size: 0x72C8 | 0x800F1024 | size: 0x6E4
 */
CupHubScene::CupHubScene(bool, bool)
{
}

/**
 * Offset/Address/Size: 0x7224 | 0x800F0F80 | size: 0xA4
 */
CupHubScene::~CupHubScene()
{
}

/**
 * Offset/Address/Size: 0x71C0 | 0x800F0F1C | size: 0x64
 */
void CupHubScene::SceneCreated()
{
    LoadCaptainImage();
    eHubState state = mHubState;
    switch (state)
    {
    case HUB_LEAGUE:
    case HUB_BOWSER_TRANSITION:
        CreateLeague();
        break;
    case HUB_KNOCKOUT2:
    case HUB_KNOCKOUT4:
    case HUB_KNOCKOUT8:
        CreateKnockout();
        break;
    default:
        break;
    }
}

/**
 * Offset/Address/Size: 0x69A4 | 0x800F0700 | size: 0x81C
 */
void CupHubScene::Update(float)
{
}

/**
 * Offset/Address/Size: 0x670C | 0x800F0468 | size: 0x298
 */
void CupHubScene::EndCup()
{
}

/**
 * Offset/Address/Size: 0x66C8 | 0x800F0424 | size: 0x44
 */
void CupHubScene::ReturnToMainMenu()
{
    nlSingleton<GameSceneManager>::s_pInstance->PopEntireStack();
    nlSingleton<GameSceneManager>::s_pInstance->Push(SCENE_MAIN_MENU, SCREEN_FORWARD, false);
}

/**
 * Offset/Address/Size: 0x5F08 | 0x800EFC64 | size: 0x7C0
 */
void CupHubScene::UpdateDisplayedStat()
{
}

/**
 * Offset/Address/Size: 0x4E34 | 0x800EEB90 | size: 0x10D4
 */
void CupHubScene::CreateLeague()
{
    FORCE_DONT_INLINE;
}

/**
 * Offset/Address/Size: 0x4018 | 0x800EDD74 | size: 0xE1C
 */
void CupHubScene::CreateBowserLeague()
{
}

/**
 * Offset/Address/Size: 0x32FC | 0x800ED058 | size: 0xD1C
 */
void CupHubScene::CreateKnockout()
{
    FORCE_DONT_INLINE;
}

/**
 * Offset/Address/Size: 0x2FF4 | 0x800ECD50 | size: 0x308
 */
void CupHubScene::UpdateLeague(float)
{
}

/**
 * Offset/Address/Size: 0x2A64 | 0x800EC7C0 | size: 0x590
 */
void CupHubScene::UpdateKnockout8(float)
{
}

/**
 * Offset/Address/Size: 0x2600 | 0x800EC35C | size: 0x464
 */
void CupHubScene::UpdateKnockout4(float)
{
}

/**
 * Offset/Address/Size: 0x1F6C | 0x800EBCC8 | size: 0x694
 */
void CupHubScene::UpdateKnockout2(float)
{
}

/**
 * Offset/Address/Size: 0x1860 | 0x800EB5BC | size: 0x70C
 */
void CupHubScene::UpdateProgressIndicator()
{
}

/**
 * Offset/Address/Size: 0x1698 | 0x800EB3F4 | size: 0x1C8
 * TODO: 98.2% match - r26/r28 swap (row vs pTextInstance) and remaining move instructions around HUBstandingsRowNames/GameInfoManager setup.
 */
void CupHubScene::ColourUserRow()
{
    typedef TLComponentInstance* (*FindCompByValue)(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher);
    typedef TLComponentInstance* (*FindCompByRef)(TLSlide*, InlineHasher&, InlineHasher&, InlineHasher&, InlineHasher&, InlineHasher&, InlineHasher&);
    typedef TLTextInstance* (*FindTextByValue)(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher);
    typedef TLTextInstance* (*FindTextByRef)(TLSlide*, InlineHasher&, InlineHasher&, InlineHasher&, InlineHasher&, InlineHasher&, InlineHasher&);

    extern int GetNumHumanTeams__15GameInfoManagerFv(GameInfoManager*);

    FEPresentation* pres = m_pFEPresentation;
    int standingsIndices[8];
    char** pRowName;
    int* pStandingsIndices;
    int row;
    int numTeams = nlSingleton<GameInfoManager>::s_pInstance->GetNumPlayingTeams();
    GameInfoManager* gameInfo;
    eTeamID userTeam;

    nlSingleton<StatsTracker>::s_pInstance->GetSortedTeamStats(mAllTeamStats, numTeams, standingsIndices, numTeams);

    pStandingsIndices = standingsIndices;
    pRowName = HUBstandingsRowNames;

    for (row = 0; row < numTeams; row++)
    {
        volatile InlineHasher hB, hA, h9, h8, h7, h6, h5, h4, h3, h2, h1, h0;
        TLTextInstance* pTextInstance;

        h0.m_Hash = 0;
        h1.m_Hash = 0;
        h2.m_Hash = 0;
        h3.m_Hash = 0;
        h4.m_Hash = 0;
        h5.m_Hash = 0;
        h6.m_Hash = 0;
        h7.m_Hash = 0;

        unsigned long hash = nlStringLowerHash("@4212");
        h8.m_Hash = hash;
        h9.m_Hash = hash;

        hash = nlStringLowerHash(CUP_HUB_LAYER_NAME);
        hB.m_Hash = hash;
        hA.m_Hash = hash;

        TLComponentInstance* pComp;
        {
            union
            {
                FindCompByValue byValue;
                FindCompByRef byRef;
            } findComp;

            findComp.byValue = FEFinder<TLComponentInstance, 4>::Find<TLSlide>;
            pComp = findComp.byRef(
                pres->m_currentSlide,
                (InlineHasher&)hB,
                (InlineHasher&)h9,
                (InlineHasher&)h7,
                (InlineHasher&)h5,
                (InlineHasher&)h3,
                (InlineHasher&)h1);
        }

        TLSlide* pSlide = pComp->GetActiveSlide();

        volatile InlineHasher g7, g6, g5, g4, g3, g2, g1, g0;

        g0.m_Hash = 0;
        h1.m_Hash = 0;
        g1.m_Hash = 0;
        h3.m_Hash = 0;
        g2.m_Hash = 0;
        h5.m_Hash = 0;
        g3.m_Hash = 0;
        h7.m_Hash = 0;
        g4.m_Hash = 0;
        g5.m_Hash = 0;

        hash = nlStringLowerHash(*pRowName);
        g6.m_Hash = hash;
        g7.m_Hash = hash;

        {
            union
            {
                FindTextByValue byValue;
                FindTextByRef byRef;
            } findText;

            findText.byValue = FEFinder<TLTextInstance, 3>::Find<TLSlide>;
            pTextInstance = findText.byRef(
                pSlide,
                (InlineHasher&)g7,
                (InlineHasher&)g5,
                (InlineHasher&)h7,
                (InlineHasher&)h5,
                (InlineHasher&)h3,
                (InlineHasher&)h1);
        }

        if (row < numTeams)
        {
            eTeamID currentTeam = mAllTeamStats[*pStandingsIndices].mTeamIndex;
            userTeam = (gameInfo = nlSingleton<GameInfoManager>::s_pInstance)->GetUserSelectedCupTeam();
            unsigned long teamMask = 1 << currentTeam;
            int isUserRow;

            if ((gameInfo->mCurrentCup->mHumanTeams & teamMask) == 0)
            {
                isUserRow = 0;
            }
            else
            {
                if ((GetNumHumanTeams__15GameInfoManagerFv(gameInfo) == 1) && (currentTeam == userTeam))
                {
                    isUserRow = 1;
                }
                else
                {
                    isUserRow = 0;
                }
            }

            if ((unsigned char)isUserRow != 0)
            {
                pTextInstance->SetAssetColour(HUB_COLOUR_HIGHLIGHT);
                break;
            }
        }

        pRowName++;
        pStandingsIndices++;
    }
}

/**
 * Offset/Address/Size: 0x15C4 | 0x800EB320 | size: 0xD4
 */
void CupHubScene::HandleButtonComponent()
{
    typedef TLComponentInstance* (*FindByValue)(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher);
    typedef TLComponentInstance* (*FindByRef)(TLSlide*, InlineHasher&, InlineHasher&, InlineHasher&, InlineHasher&, InlineHasher&, InlineHasher&);

    union {
        FindByValue byValue;
        FindByRef byRef;
    } findComp;

    findComp.byValue = FEFinder<TLComponentInstance, 4>::Find<TLSlide>;

    FEPresentation* pres = m_pFEPresentation;

    volatile InlineHasher hB, hA, h9, h8, h7, h6, h5, h4, h3, h2, h1, h0;

    h0.m_Hash = 0;
    h1.m_Hash = 0;
    h2.m_Hash = 0;
    h3.m_Hash = 0;
    h4.m_Hash = 0;
    h5.m_Hash = 0;
    h6.m_Hash = 0;
    h7.m_Hash = 0;

    unsigned long buttonHash = nlStringLowerHash("@4158");
    h8.m_Hash = buttonHash;
    h9.m_Hash = buttonHash;

    unsigned long layerHash = nlStringLowerHash(CUP_HUB_LAYER_NAME);
    hB.m_Hash = layerHash;
    hA.m_Hash = layerHash;

    TLComponentInstance* inst = findComp.byRef(
        pres->m_currentSlide,
        (InlineHasher&)hB,
        (InlineHasher&)h9,
        (InlineHasher&)h7,
        (InlineHasher&)h5,
        (InlineHasher&)h3,
        (InlineHasher&)h1);

    mButtons.mButtonInstance = inst;
    inst->m_bVisible = false;

    s16 roundNum = nlSingleton<GameInfoManager>::s_pInstance->GetCurrentRoundNumber();
    if (roundNum == -5)
    {
        mButtons.SetState(ButtonComponent::BS_A_ONLY);
    }
    else
    {
        mButtons.SetState(ButtonComponent::BS_A_AND_B);
    }
}

/**
 * Offset/Address/Size: 0x12EC | 0x800EB048 | size: 0x2D8
 */
void CupHubScene::SetRoundColours(eHubColour*, int)
{
}

/**
 * Offset/Address/Size: 0x1DC | 0x800E9F38 | size: 0x1110
 */
void CupHubScene::UpdateRoundMessage(bool)
{
}

/**
 * Offset/Address/Size: 0x0 | 0x800E9D5C | size: 0x1DC
 * TODO: 99.5% match - one early instruction reorder remains (stw 0xC(r1) emitted before
 *       singleton load), with an additional fixed +0x14 instruction lead-in in current asm.
 */
void CupHubScene::LoadCaptainImage()
{
    typedef TLImageInstance* (*FindImageByValue)(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher);
    typedef TLImageInstance* (*FindImageByRef)(TLSlide*, InlineHasher&, InlineHasher&, InlineHasher&, InlineHasher&, InlineHasher&, InlineHasher&);

    volatile InlineHasher hB, hA, h9, h8, h7, h6, h5, h4, h3, h2, h1, h0;

    h0.m_Hash = 0;
    h2.m_Hash = 0;
    h4.m_Hash = 0;
    h6.m_Hash = 0;

    GameInfoManager* gameInfoMgr = *(GameInfoManager* volatile*)&nlSingleton<GameInfoManager>::s_pInstance;

    h1.m_Hash = 0;
    h3.m_Hash = 0;
    h5.m_Hash = 0;
    h7.m_Hash = 0;

    unsigned long imageHash = nlStringLowerHash("WALUIGI_L");
    h8.m_Hash = imageHash;
    h9.m_Hash = imageHash;

    unsigned long layerHash = nlStringLowerHash(CUP_HUB_LAYER_NAME);
    hB.m_Hash = layerHash;
    hA.m_Hash = layerHash;

    union {
        FindImageByValue byValue;
        FindImageByRef byRef;
    } findImage;
    findImage.byValue = FEFinder<TLImageInstance, 2>::Find<TLSlide>;
    TLImageInstance* imageInst = findImage.byRef(
        m_pFEPresentation->m_currentSlide,
        (InlineHasher&)hB, (InlineHasher&)h9, (InlineHasher&)h7,
        (InlineHasher&)h5, (InlineHasher&)h3, (InlineHasher&)h1);

    eTeamID teamId;
    if (gameInfoMgr->IsInCupMode() || gameInfoMgr->GetNumHumanTeams() == 1)
    {
        teamId = gameInfoMgr->GetUserSelectedCupTeam();
    }
    else
    {
        s16 roundNum = gameInfoMgr->GetCurrentRoundNumber();
        if (roundNum != -5)
        {
            u16 numTeams = gameInfoMgr->GetNumPlayingTeams();
            u32 randomResult = nlRandom(numTeams, &nlDefaultSeed);
            u16 randomIndex = (u16)randomResult;
            TeamStats stats;
            stats = gameInfoMgr->GetTeamStatsByIndex(randomIndex);
            teamId = stats.mTeamIndex;
        }
        else
        {
            teamId = FindWinningTeam__15GameInfoManagerFv(gameInfoMgr);
        }
    }

    const char* teamName = GetTeamName(teamId);
    char buffer[0x80];
    nlSNPrintf(buffer, 0x80, "fe/cup_loadingscreens/%s_l", teamName);

    mCaptainImage->mImageInstance = imageInst;
    mCaptainImage->QueueLoad(buffer, true);
}
