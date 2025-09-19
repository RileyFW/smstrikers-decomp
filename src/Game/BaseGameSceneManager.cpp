#include "Game/BaseGameSceneManager.h"

#include "Game/SH/SHBackground.h"

#include "Game/FE/FESceneManager.h"

#include "NL/nlConfig.h"

// Define the scene entry struct
struct SceneEntry
{
    u32 sceneId;
    const char* sceneName;
};

// Declare the array of scene entries
struct SceneEntry SceneEntryTable[] = {
    { 0x00, "art/fe/background.fen" },
    { 0x01, "art/fe/mariobg.fen" },
    { 0x02, "art/fe/start_screen_v2.fen" },
    { 0x03, "art/fe/main_menuv2.fen" },
    { 0x04, "art/fe/choose_sides_v3.fen" },
    { 0x05, "art/fe/choose_sides_v3.fen" },
    { 0x06, "art/fe/choose_sides_v3.fen" },
    { 0x07, "art/fe/choose_sides_v3.fen" },
    { 0x08, "/art/fe/choose_captains_v3.fen" },
    { 0x09, "art/fe/choose_stadiums_v2.fen" },
    { 0x0A, "art/fe/cup_cheater.fen" },
    { 0x0B, "art/fe/cup_background.fen" },
    { 0x0C, "art/fe/super_cup_background.fen" },
    { 0x0D, "art/fe/choose_cup_v2.fen" },
    { 0x0E, "art/fe/choose_cup_v2.fen" },
    { 0x0F, "art/fe/cup_choose_captains_v3.fen" },
    { 0x10, "art/fe/cup_choose_captains_v3.fen" },
    { 0x11, "art/fe/cup_standings_v2.fen" },
    { 0x12, "art/fe/cup_standings_v2.fen" },
    { 0x13, "art/fe/cup_standings_v2.fen" },
    { 0x14, "art/fe/cup_standings_v2.fen" },
    { 0x15, "art/fe/cup_standings_v2.fen" },
    { 0x16, "art/fe/cup_standings_v2.fen" },
    { 0x17, "art/fe/cup_standings_v2.fen" },
    { 0x18, "art/fe/cup_standings_v2.fen" },
    { 0x19, "art/fe/cup_standings_v2.fen" },
    { 0x1A, "art/fe/super_team_reveal_v3.fen" },
    { 0x1B, "art/fe/popup_menu.fen" },
    { 0x1C, "art/fe/spoils_menu_v2.fen" },
    { 0x1D, "art/fe/ticker.fen" },
    { 0x1E, "art/fe/mainstart_background.fen" },
    { 0x1F, "art/fe/saving_loading.fen" },
    { 0x20, "art/fe/saving_loading.fen" },
    { 0x21, "art/fe/saving_loading.fen" },
    { 0x22, "art/fe/saving_loading.fen" },
    { 0x23, "art/fe/saving_loading.fen" },
    { 0x24, "art/fe/custom_tournament_options_v2.fen" },
    { 0x25, "art/fe/custom_tournament_capt_chooser.fen" },
    { 0x26, "art/fe/main_options_v2.fen" },
    { 0x27, "art/fe/englegal.fen" },
    { 0x28, "art/fe/main_options_v2.fen" },
    { 0x29, "art/fe/main_options_v2.fen" },
    { 0x2A, "art/fe/main_options_v2.fen" },
    { 0x2B, "art/fe/loadingtest.fen" },
    { 0x2C, "art/fe/spoils_battles_history_v2.fen" },
    { 0x2D, "art/fe/spoils_milestone_history_v2.fen" },
    { 0x2E, "art/fe/bragging_rights.fen" },
    { 0x2F, "art/fe/player_awards_v3.fen" },
    { 0x30, "art/fe/movieplayer.fen" },
    { 0x31, "art/fe/main_options_v2.fen" },
    { 0x32, "art/fe/vs_transition.fen" },
    { 0x33, "art/fe/health_and_safety.fen" },
    { 0x34, "art/fe/movieplayer.fen" },
    { 0x35, "art/fe/movieplayer.fen" },
    { 0x36, "art/fe/credits.fen" },
    { 0x37, "art/fe/progressive_scan.fen" },
    { 0x38, "art/fe/progressive_scan.fen" },
    { 0x39, "art/fe/pausemenu_v3.fen" },
    { 0x3A, "art/fe/choose_sides_v4.fen" },
    { 0x3B, "art/fe/pause_options_v2.fen" },
    { 0x3C, "art/fe/pause_options_v2.fen" },
    { 0x3D, "art/fe/post_game_menu_v2.fen" },
    { 0x3E, "art/fe/pausemenu101_v3.fen" },
    { 0x3F, "art/fe/lesson.fen" },
    { 0x40, "art/fe/strikers_101_lessons_v3.fen" },
    { 0x41, "art/fe/lessonmovieplayer.fen" },
    { 0x42, NULL }, // 0x00000000 indicates NULL pointer
    { 0x43, "art/fe/hud.fen" },
    { 0x44, "art/fe/ingame_text.fen" },
    { 0x45, "art/fe/popup_menu.fen" },
    { 0x46, "art/fe/summary.fen" },
    { 0x47, "art/fe/summary.fen" },
    { 0x48, "art/fe/goal_overlay.fen" },
    { 0x49, "art/fe/player_awards_ig_v3.fen" },
    { 0x4A, "art/fe/demo_overlay.fen" },
    { 0x4B, "art/fe/winner.fen" },
    { 0x4C, "art/fe/igticker.fen" },
    { 0x4D, "art/fe/x2_sts.fen" },
    { 0x4E, "art/fe/loading_screen.fen" },
    { 0x4F, NULL } // 0x00000000 indicates NULL pointer
};

// /**
//  * Offset/Address/Size: 0x64 | 0x80096B94 | size: 0x4
//  */
// void IntroMovieScene::PlayScreenBackSFX()
// {
// }

// /**
//  * Offset/Address/Size: 0x60 | 0x80096B90 | size: 0x4
//  */
// void IntroMovieScene::PlayScreenForwardSFX()
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x80096B30 | size: 0x60
//  */
// IntroMovieScene::~IntroMovieScene()
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x80096AF8 | size: 0x38
//  */
// void SlideMenuList::SetSlide()
// {
// }

/**
 * Offset/Address/Size: 0x54 | 0x80096AF0 | size: 0x8
 */
// void BaseSceneHandler::SetPresentation(FEPresentation*)
// {
// }

/**
 * Offset/Address/Size: 0x50 | 0x80096AEC | size: 0x4
 */
// void BaseSceneHandler::InitializeSubHandlers()
// {
// }

/**
 * Offset/Address/Size: 0x8 | 0x80096AA4 | size: 0x48
 */
// BaseSceneHandler::~BaseSceneHandler()
// {
// }

/**
 * Offset/Address/Size: 0x0 | 0x80096A9C | size: 0x8
 */
// void BaseSceneHandler::SetVisible(bool)
// {
// }

/**
 * Offset/Address/Size: 0x142C | 0x800969E8 | size: 0xB4
 */
BaseGameSceneManager::BaseGameSceneManager()
{
    m_count = 0;
    for (int i = 0; i < MAX_SCENE_COUNT; ++i)
    {
        m_types[i] = SCENE_INVALID;
        m_handlers[i] = 0;
    }
}

/**
 * Offset/Address/Size: 0x13B0 | 0x8009696C | size: 0x7C
 */
BaseGameSceneManager::~BaseGameSceneManager()
{
    while (m_count != 0)
    {
        this->Pop();
    }
}

/**
 * Offset/Address/Size: 0x324 | 0x800958E0 | size: 0x108C
 */
BaseSceneHandler* BaseGameSceneManager::Push(SceneList sceneType, ScreenMovement movement, bool shouldCallVirtual)
{
    // Call virtual method if requested
    if (shouldCallVirtual)
    {
        this->Push(SCENE_FRIENDLY_BACKGROUND, SCREEN_NOTHING, false);
    }

    // Special case: SCENE_MAIN_BACKGROUND (0x1E) becomes SCENE_MARIO_BACKGROUND
    if (sceneType == SCENE_MAIN_BACKGROUND)
    {
        sceneType = SCENE_MARIO_BACKGROUND;
    }

    // Get global config and find TVP setting
    Config& config = Config::Global();
    TagValuePair& tvp = config.FindTvp("fev2");

    // Handle TVP value based on type
    if (tvp.type == 0)
    {
        config.Set("fev2", false);
    }
    else if (tvp.type == 1)
    {
        // LexicalCast<b,i>
        // config->Set("fev2", LexicalCast<bool,int>(tvp.m_unk_0x08));
    }
    else if (tvp.type == 2)
    {
        // LexicalCast<b,f>
    }
    else if (tvp.type == 3)
    {
        // LexicalCast<b,PCc>
    }

    // Special handling for SCENE_MAIN_MENU
    if (sceneType == SCENE_MAIN_MENU)
    {
        this->Push(SCENE_MARIO_BACKGROUND, SCREEN_NOTHING, false);
    }

    // // Get scene entry from table
    // SceneEntryTable* entryTable = &SceneEntryTable[sceneType];
    // const char* sceneName = entryTable->name;

    // // Get config again for second TVP lookup
    // config = Config::Global();
    // tvp = config->FindTvp("fev2");

    // // Handle TVP value again (same logic as above)
    // if (tvp->value == 0)
    // {
    //     config->Set("fev2", false);
    // }
    // else if (tvp->value == 1)
    // {
    //     // LexicalCast<b,i>
    // }
    // else if (tvp->value == 2)
    // {
    //     // LexicalCast<b,f>
    // }
    // else if (tvp->value == 3)
    // {
    //     // LexicalCast<b,PCc>
    // }

    // // Special handling for SCENE_TITLE based on build flags
    // if (sceneType == SCENE_TITLE)
    // {
    //     if (g_e3_Build || g_Europe)
    //     {
    //         sceneName = "art/fe/start_screen_v2_german.fen";
    //     }
    //     else if (g_Language == 5)
    //     {
    //         sceneName = "art/fe/start_screen_jpn.fen";
    //     }
    // }

    // // Special handling for SCENE_CHOOSE_CAPTAINS based on build flags
    // if (sceneType == SCENE_CHOOSE_CAPTAINS && g_e3_Build)
    // {
    //     sceneName = "art/fe/choose_captains_vLeeptsig.fen";
    // }

    // Create scene based on scene type using jump table
    BaseSceneHandler* scene = nullptr;

    // switch (sceneType)
    // {
    // case SCENE_FRIENDLY_BACKGROUND:
    // case SCENE_MARIO_BACKGROUND:
    //     scene = new BackgroundScene();
    //     break;

    // case SCENE_TITLE:
    //     scene = new TitleScene();
    //     break;

    // case SCENE_MAIN_MENU:
    //     scene = new SHMainMenu();
    //     break;

    // case SCENE_CHOOSE_SIDES_FRIENDLY:
    // case SCENE_CHOOSE_SIDES_CUP:
    // case SCENE_CHOOSE_SIDES_SUPER_CUP:
    // case SCENE_CHOOSE_SIDES_TOURNAMENT:
    //     scene = new SHChooseSides2(static_cast<SHChooseSides2::eCSContext>(sceneType - SCENE_CHOOSE_SIDES_FRIENDLY));
    //     break;

    // case SCENE_CHOOSE_CAPTAINS:
    //     scene = new ChooseCaptainsSceneV2(ChooseCaptainsSceneV2::SceneType_0);
    //     break;

    // case SCENE_STADIUM_SELECT:
    //     scene = new StadiumSelectSceneV2();
    //     break;

    // case SCENE_CUP_CHEATER:
    //     scene = new CupCheaterScene();
    //     break;

    // case SCENE_CUP_BACKGROUND:
    // case SCENE_SUPER_CUP_BACKGROUND:
    //     scene = new BackgroundScene();
    //     break;

    // case SCENE_CUP_CHOOSE_CUP:
    // case SCENE_SUPER_CUP_CHOOSE_CUP:
    //     scene = new ChooseCupSceneV2(sceneType == SCENE_SUPER_CUP_CHOOSE_CUP);
    //     break;

    // case SCENE_CUP_CHOOSE_CAPTAIN:
    // case SCENE_SUPER_CUP_CHOOSE_CAPTAIN:
    //     scene = new CupChooseCaptainSceneV2(sceneType == SCENE_SUPER_CUP_CHOOSE_CAPTAIN);
    //     break;

    // case SCENE_CUP_STANDINGS:
    // case SCENE_CUP_STANDINGS_ANIM:
    // case SCENE_CUP_STANDINGS_FINAL_ANIM:
    // case SCENE_SUPER_CUP_STANDINGS:
    // case SCENE_SUPER_CUP_STANDINGS_ANIM:
    // case SCENE_SUPER_CUP_STANDINGS_FINAL_ANIM:
    // case SCENE_TOURNAMENT_STANDINGS :
    // case SCENE_TOURNAMENT_STANDINGS_ANIM:
    //     scene = new CupHubScene(sceneType >= SCENE_CUP_STANDINGS_FINAL_ANIM, sceneType >= SCENE_SUPER_CUP_STANDINGS_ANIM);
    //     break;

    // case SCENE_TOURNAMENT_STANDINGS_FINAL_ANIM:
    //     scene = new SuperTeamScene();
    //     break;

    // case SCENE_CUP_SUPER_TEAM:
    //     scene = new FEPopupMenu();
    //     break;

    // case SCENE_POPUP_MENU:
    //     scene = new SpoilsScene();
    //     break;

    // case SCENE_TROPHY_ROOM:
    //     scene = new ScrollingTickerScene();
    //     break;

    // case SCENE_SCROLLING_TICKER:
    //     scene = new BackgroundScene();
    //     break;

    // case SCENE_MAIN_BACKGROUND:
    //     scene = new SaveLoadScene(SaveLoadScene::eSaveLoadMode_0);
    //     break;

    // case SCENE_SAVE:
    //     scene = new SaveLoadScene(SaveLoadScene::eSaveLoadMode_3);
    //     break;

    // case SceneList_32:
    //     scene = new SaveLoadScene(SaveLoadScene::eSaveLoadMode_2);
    //     break;

    // case SceneList_33:
    //     scene = new SaveLoadScene(SaveLoadScene::eSaveLoadMode_4);
    //     break;

    // case SceneList_34:
    //     scene = new SaveLoadScene(SaveLoadScene::eSaveLoadMode_0);
    //     break;

    // case SceneList_35:
    //     scene = new TournSetParamsScene();
    //     break;

    // case SceneList_36:
    //     scene = new TournTeamSetupSceneV2();
    //     break;

    // case SceneList_37:
    //     scene = new OptionsScene();
    //     break;

    // case SceneList_38:
    //     scene = new CrossFaderScene();
    //     break;

    // case SceneList_39:
    //     scene = new CupOptionsScene(SCENE_CUP_CHOOSE_CAPTAIN, SCENE_CUP_CHOOSE_CUP);
    //     break;

    // case SceneList_40:
    //     scene = new CupOptionsScene(SCENE_SUPER_CUP_CHOOSE_CAPTAIN, SCENE_SUPER_CUP_CHOOSE_CUP);
    //     break;

    // case SceneList_41:
    //     scene = new CupOptionsScene(SCENE_TOURNAMENT_STANDINGS_FINAL_ANIM, SCENE_TOURNAMENT_STANDINGS_ANIM);
    //     break;

    // case SceneList_42:
    //     scene = new SuperLoadingScene();
    //     break;

    // case SceneList_43:
    //     scene = new CupTrophyScene();
    //     break;

    // case SceneList_44:
    //     scene = new MilestoneTrophyScene();
    //     break;

    // case SceneList_45:
    //     scene = new BraggingRightsScene();
    //     break;

    // case SceneList_46:
    //     scene = new BraggingRightsOverlay();
    //     break;

    // case SceneList_47:
    //     scene = new MoviePlayerScene();
    //     break;

    // case SceneList_48:
    //     scene = new QuickGameplayOptionsScene();
    //     break;

    // case SceneList_49:
    //     scene = new LoadingTransitionScene();
    //     break;

    // case SceneList_50:
    //     scene = new HealthWarningSceneV2();
    //     break;

    // case SceneList_51:
    //     // Special NLG logo movie scene
    //     scene = new NLGLogoMovieScene();
    //     // Set movie details based on build flags
    //     if (GameInfoManager::GetInstance()->GetSomeFlag())
    //     {
    //         scene->SetMovieDetails("movies/nlgintrowide.thp", true, false);
    //     }
    //     else
    //     {
    //         scene->SetMovieDetails("movies/nlgintrofull.thp", true, false);
    //     }
    //     break;

    // case SceneList_52:
    //     // Special intro movie scene
    //     scene = new IntroMovieScene();
    //     scene->SetMovieDetails("intromovie.thp", true, false);
    //     break;

    // case SceneList_53:
    //     scene = new CreditScene();
    //     break;

    // case SceneList_54:
    //     scene = new ProgressiveScanScene(false);
    //     break;

    // case SceneList_55:
    //     scene = new ProgressiveScanScene(true);
    //     break;

    // case SceneList_56:
    //     scene = new PauseMenuScene(PauseMenuScene::eScreenContext_0);
    //     break;

    // case SceneList_57:
    //     scene = new SHChooseSides2(SHChooseSides2::eCSContext_4);
    //     break;

    // case SceneList_58:
    //     scene = new PauseOptionsScene(PauseOptionsScene::Mode_0);
    //     break;

    // case SceneList_59:
    //     scene = new PauseOptionsScene(PauseOptionsScene::Mode_1);
    //     break;

    // case SceneList_60:
    //     scene = new PausePostGameScene();
    //     break;

    // case SceneList_61:
    //     scene = new PauseMenuScene(PauseMenuScene::eScreenContext_1);
    //     break;

    // case SceneList_62:
    //     scene = new LessonScene();
    //     break;

    // case SceneList_63:
    //     scene = new LessonSelectScene();
    //     break;

    // case SceneList_64:
    //     scene = new LessonMoviePlayerScene();
    //     break;

    // case SceneList_65:
    //     scene = new HUDOverlay();
    //     break;

    // case SceneList_66:
    //     scene = new InGameTextOverlay();
    //     break;

    // case SceneList_67:
    //     scene = new FEPopupMenu();
    //     break;

    // case SceneList_68:
    //     scene = new SummaryOverlay(SummaryOverlay::eSummaryContext_0);
    //     break;

    // case SceneList_69:
    //     scene = new SummaryOverlay(SummaryOverlay::eSummaryContext_1);
    //     break;

    // case SceneList_70:
    //     scene = new GoalOverlay();
    //     break;

    // case SceneList_71:
    //     scene = new BraggingRightsOverlay();
    //     break;

    // case SceneList_72:
    //     scene = new DemoOverlay();
    //     break;

    // case SceneList_73:
    //     scene = new WinnerOverlay();
    //     break;

    // case SceneList_74:
    //     scene = new NSNMessengerScene();
    //     break;

    // case SceneList_75:
    //     scene = new STSX2Overlay();
    //     break;

    // case SceneList_76:
    //     scene = new BaseSceneHandler();
    //     break;

    // default:
    //     break;
    // }

    // // Queue the scene push with FESceneManager
    // FESceneManager* feManager = FESceneManager::GetInstance();
    // feManager->QueueScenePush(scene, sceneName);

    // // Store scene type and handler in arrays
    // m_types[m_count] = sceneType;
    // m_handlers[m_count] = scene;
    // m_count++;

    // // Play audio based on movement type
    // if (movement == SCREEN_FORWARD)
    // {
    //     FEAudio::PlayAnimAudioEvent("sfx_screen_forward", false);
    // }
    // else if (movement == SCREEN_BACK)
    // {
    //     FEAudio::PlayAnimAudioEvent("sfx_screen_back", false);
    // }

    return scene;
}

/**
 * Offset/Address/Size: 0x2D8 | 0x80095894 | size: 0x4C
 */
BaseSceneHandler* BaseGameSceneManager::GetScene(SceneList scene)
{
    BaseSceneHandler* handler = NULL;

    for (u32 i = 0; i < m_count; ++i)
    {
        if (m_types[i] == scene)
        {
            handler = m_handlers[i];
            break;
        }
    }

    return handler;
}

/**
 * Offset/Address/Size: 0x288 | 0x80095844 | size: 0x50
 */
void BaseGameSceneManager::Pop()
{
    // FESceneManager* sceneManager = FESceneManager::s_pInstance->s_pInstance;
    // sceneManager->QueueScenePop();
    FESceneManager::s_pInstance.Instance()->QueueScenePop();

    m_handlers[m_count] = 0;
    m_count = (m_count - 1);
}

/**
 * Offset/Address/Size: 0x23C | 0x800957F8 | size: 0x4C
 */
void BaseGameSceneManager::PopEntireStack()
{
    while (m_count != 0)
    {
        this->Pop();
    }
}

/**
 * Offset/Address/Size: 0x1F4 | 0x800957B0 | size: 0x48
 */
int BaseGameSceneManager::GetSceneType(BaseSceneHandler* handler)
{
    // Iterate rows; when mHandlers[i] == handler, return mTypes[i], else -2. :contentReference[oaicite:10]{index=10}
    for (u32 i = 0; i < m_count; ++i)
    {
        if (m_handlers[i] == handler)
        {
            return m_types[i];
        }
    }
    return -2;
}

/**
 * Offset/Address/Size: 0x1C0 | 0x8009577C | size: 0x34
 */
bool BaseGameSceneManager::IsOnStack(SceneList scene)
{
    for (u32 i = 0; i < m_count; ++i)
    {
        // if (m_types[i].m_type == scene.m_type)
        // if (*(int*)&m_types[i] == *(int*)&scene)
        if (m_types[i] == scene)
            return true;
    }
    return false;
}

/**
 * Offset/Address/Size: 0x68 | 0x80095624 | size: 0x158
 */
BasicString<char, Detail::TempStringAllocator> BaseGameSceneManager::GetFileName(SceneList scene)
{
    const char* src = SceneEntryTable[(u32)scene].sceneName;

    // Create BasicString using the template
    BasicString<char, Detail::TempStringAllocator> result;

    // Calculate string length
    u32 length = 0;
    const char* p = src;
    while (*p != '\0')
    {
        ++p;
        ++length;
    }

    // Allocate memory for the string (including null terminator)
    result.m_capacity = length + 1;
    result.m_data = (char*)Detail::TempStringAllocator::allocate(result.m_capacity);
    result.m_size = length;
    result.m_refCount = 1;

    // Copy the string data
    for (u32 i = 0; i < length; i++)
    {
        result.m_data[i] = src[i];
    }
    result.m_data[length] = '\0';

    return result;
}

/**
 * Offset/Address/Size: 0x0 | 0x800955BC | size: 0x68
 */
void BaseGameSceneManager::PushLoadingScene(bool clearStack)
{
    if (clearStack)
    {
        this->Pop();
    }

    BackgroundScene* handler = (BackgroundScene*)Push((SceneList)0x2B, SCREEN_FORWARD, false);
    handler->m_unk_0x1C = 0; // ??
}
