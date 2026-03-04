#include "Game/TransitionTask.h"
#include "Game/Font/fontmanager.h"

struct LocalizationObj
{
    void* m_pFile;
    void* m_LookupTable;
    void* m_FirstString;
    unsigned long m_Language;
};

extern LocalizationObj* g_pLocalization;

int nlSNPrintf(char*, unsigned long, const char*, ...);

// /**
//  * Offset/Address/Size: 0x0 | 0x801731FC | size: 0x10
//  */
// void 0x8028D338..0x8028D33C | size : 0x4
// {
// }

/**
 * Offset/Address/Size: 0xC | 0x801731F8 | size: 0x4
 */
void TransitionTask::Run(float)
{
}

// /**
//  * Offset/Address/Size: 0x0 | 0x801731EC | size: 0xC
//  */
// void TransitionTask::GetName()
// {
// }

// /**
//  * Offset/Address/Size: 0x1BF4 | 0x801731C4 | size: 0x28
//  */
// void Detail::SwitchToStartScreenLoader::StartLoad(LoadingManager*)
// {
// }

/**
 * Offset/Address/Size: 0x1A10 | 0x80172FE0 | size: 0x1E4
 */
void LoadFonts()
{
    const char* fontFileName1 = "game_font.fnt";
    const char* fontFileName2 = "fe_font.fnt";
    char langCode[4] = "eng";

    unsigned long lang = g_pLocalization->m_Language;
    switch (lang)
    {
    case 0:
        langCode[0] = 'f';
        langCode[1] = 'r';
        langCode[2] = 'e';
        break;
    case 1:
        langCode[0] = 'd';
        langCode[1] = 'e';
        langCode[2] = 'u';
        break;
    case 2:
        langCode[0] = 'i';
        langCode[1] = 't';
        langCode[2] = 'a';
        break;
    case 3:
        langCode[0] = 'j';
        langCode[1] = 'p';
        langCode[2] = 'n';
        break;
    case 4:
        langCode[0] = 's';
        langCode[1] = 'p';
        langCode[2] = 'a';
        break;
    case 5:
        langCode[0] = 'u';
        langCode[1] = 'k';
        langCode[2] = 'e';
        break;
    case 6:
        langCode[0] = 'b';
        langCode[1] = 'o';
        langCode[2] = 'b';
        break;
    case 7:
        langCode[0] = 'l';
        langCode[1] = 'n';
        langCode[2] = 'g';
        break;
    case 8:
        break;
    }

    char bundlePath1[64];
    char fontName1[64];
    char bundlePath2[64];
    char fontName2[64];

    nlSNPrintf(bundlePath1, 64, "fonts/%s/game_font.bnl", langCode);
    nlSNPrintf(fontName1, 64, "fonts/%s/game_font", langCode);
    nlSNPrintf(bundlePath2, 64, "fonts/%s/fe_font.bnl", langCode);
    nlSNPrintf(fontName2, 64, "fonts/%s/fe_font", langCode);

    nlSingleton<FontManager>::s_pInstance->LoadFont(bundlePath1, fontName1, fontFileName1);
    nlSingleton<FontManager>::s_pInstance->LoadFont(bundlePath2, fontName2, fontFileName2);
}

/**
 * Offset/Address/Size: 0x19E0 | 0x80172FB0 | size: 0x30
 */
TransitionTask::TransitionTask()
{
    m_pAIHandler = nullptr;
    m_pGoalieHandler = nullptr;
    m_pLoadingManager = nullptr;
    m_TransitionState = eTS_Unknown;
}

/**
 * Offset/Address/Size: 0x19D8 | 0x80172FA8 | size: 0x8
 */
void TransitionTask::Initialize(LoadingManager& loadingManager)
{
    m_pLoadingManager = &loadingManager;
}

/**
 * Offset/Address/Size: 0x10B8 | 0x80172688 | size: 0x920
 */
void TransitionTask::StateTransition(unsigned int, unsigned int)
{
}

/**
 * Offset/Address/Size: 0x888 | 0x80171E58 | size: 0x830
 */
void TransitionTask::InitializeGameState()
{
}

/**
 * Offset/Address/Size: 0x4BC | 0x80171A8C | size: 0x3CC
 */
void TransitionTask::DestroyGameState()
{
}

/**
 * Offset/Address/Size: 0x0 | 0x801715D0 | size: 0x4BC
 */
void TransitionTask::InitializeFEState()
{
}
