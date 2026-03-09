#include "Game/BaseGameSceneManager.h"
#include "Game/SH/SHBackground.h"
#include "Game/FE/feSceneManager.h"

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

/**
 * Offset/Address/Size: 0x142C | 0x800969E8 | size: 0xB4
 */
BaseGameSceneManager::BaseGameSceneManager()
{
    mCurrentStackDepth = 0;
    for (int i = 0; i < MAX_SCENE_COUNT; ++i)
    {
        m_sceneStack[i] = SCENE_INVALID;
        mBaseSceneHandlerStack[i] = 0;
    }
}

/**
 * Offset/Address/Size: 0x13B0 | 0x8009696C | size: 0x7C
 */
BaseGameSceneManager::~BaseGameSceneManager()
{
    while (mCurrentStackDepth != 0)
    {
        this->Pop();
    }
}

/**
 * Offset/Address/Size: 0x324 | 0x800958E0 | size: 0x108C
 */
BaseSceneHandler* BaseGameSceneManager::Push(SceneList sceneType, ScreenMovement movement, bool shouldCallVirtual)
{
    BaseSceneHandler* scene = nullptr;
    return scene;
}

/**
 * Offset/Address/Size: 0x2D8 | 0x80095894 | size: 0x4C
 */
BaseSceneHandler* BaseGameSceneManager::GetScene(SceneList scene)
{
    BaseSceneHandler* handler = NULL;

    for (u32 i = 0; i < mCurrentStackDepth; ++i)
    {
        if (m_sceneStack[i] == scene)
        {
            handler = mBaseSceneHandlerStack[i];
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
    FESceneManager::Instance()->QueueScenePop();
    mBaseSceneHandlerStack[mCurrentStackDepth] = 0;
    mCurrentStackDepth = (mCurrentStackDepth - 1);
}

/**
 * Offset/Address/Size: 0x23C | 0x800957F8 | size: 0x4C
 */
void BaseGameSceneManager::PopEntireStack()
{
    while (mCurrentStackDepth != 0)
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
    for (u32 i = 0; i < mCurrentStackDepth; ++i)
    {
        if (mBaseSceneHandlerStack[i] == handler)
        {
            return m_sceneStack[i];
        }
    }
    return -2;
}

/**
 * Offset/Address/Size: 0x1C0 | 0x8009577C | size: 0x34
 */
bool BaseGameSceneManager::IsOnStack(SceneList scene)
{
    for (u32 i = 0; i < mCurrentStackDepth; ++i)
    {
        if (m_sceneStack[i] == scene)
            return true;
    }
    return false;
}

/**
 * Offset/Address/Size: 0x68 | 0x80095624 | size: 0x158
 */
BasicString<char, Detail::TempStringAllocator> BaseGameSceneManager::GetFileName(SceneList scene)
{
    BasicString<char, Detail::TempStringAllocator> result;
    const char* src = SceneEntryTable[(u32)scene].sceneName;

    BasicStringInternal* data = (BasicStringInternal*)nlMalloc(0x10, 8, true);
    if (data != nullptr)
    {
        data->mData = nullptr;
        data->mSize = 0;
        data->mCapacity = 0;

        const char* srcPtr = src;
        while ((s8)*srcPtr++ != 0)
        {
            data->mSize++;
        }

        data->mSize++;
        data->mData = (char*)nlMalloc(data->mSize + 1, 8, true);
        data->mCapacity = data->mSize;

        s32 i = 0;
        while (i < data->mSize)
        {
            data->mData[i] = *src;
            src++;
            i++;
        }
        data->mRefCount = 1;
    }

    result.m_data = data;
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
    handler->mPlayMode = PM_STOPPED;
}
