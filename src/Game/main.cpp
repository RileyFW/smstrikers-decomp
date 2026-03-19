#include "types.h"
#include "Game/main.h"
#include "NL/gl/glView.h"
#include "NL/gl/glTexture.h"
#include "NL/gl/glState.h"
#include "Game/Effects/ParticleSystem.h"
#include "Game/Transitions/ModelTransition.h"
#include "NL/nlConfig.h"
#include "Game/ProfileTask.h"
#include "Game/Sys/FloatingPointExceptions.h"
#include "Game/Sys/CallStackDumper.h"
#include "dolphin/os/OSThread.h"

extern u8 g_DoStackWatermarkTests;
extern u8 g_StackWatermarkFiller;

static bool g_bProfiling = false;
static bool g_bTweaking = false;
bool g_e3_Build = false;
bool g_Europe = false;
static bool g_bFranticPausing = false;
int g_Language = 0;
static void* g_pTheLoadingManagerTask = nullptr;

ClockUpdateTask clockUpdateTask;
AudioUpdateTask audioUpdateTask;

static void Initialize();

int main(void)
{
    if (g_DoStackWatermarkTests)
    {
        OSClearStack(g_StackWatermarkFiller);
    }

    Initialize();

    fopen("flushfile.txt", "r");

    Config& config = Config::Global();
    bool skipfe = GetConfigBool(config, "skipfe", false);
    nlTaskManager::SetNextState(skipfe ? 2 : 4);

    Config& config2 = Config::Global();
    bool enableFPE = GetConfigBool(config2, "enableFloatingPointExceptions", false);
    if (enableFPE)
    {
        InstallFloatingPointExceptionHandler();
    }

    Config& config3 = Config::Global();
    bool enableCSD = GetConfigBool(config3, "callStackDumper", false);
    if (enableCSD)
    {
        InstallCallStackDumper();
    }

    for (;;)
    {
        nlTaskManager::RunAllTasks();
        UpdateProfile();
    }
}

static void SetupViews()
{
    static eGLView sort_none[] = {
        GLV_Shadow0, GLV_Shadow1, GLV_UnsortedPerspective, GLV_InvisiblePlane, GLV_ElectricFence, GLV_UnsortedOrtho, GLV_ShadowBlend0, GLV_ShadowBlend1, GLV_Debug, GLV_Transitions, GLV_CoPlanar0, GLV_CoPlanar
    };

    static eGLView disabled_views[] = {
        GLV_ShadowBlend0, GLV_ShadowBlend1, GLV_ScreenBlur, GLV_ScreenBlur2
    };

    s32 i;

    for (i = 0; i < GLV_Num; i++)
    {
        glViewSetTarget((eGLView)i, GLTG_Main);
    }

    glViewSetSortMode(GLV_FrontEnd, GLVSort_TransformedDepth);
    glViewSetSortMode(GLV_Anark, GLVSort_Reverse);

    {
        u32 j;
        for (j = 0; j < 12; j++)
        {
            glViewSetSortMode(sort_none[j], GLVSort_None);
        }
    }

    {
        u32 j;
        for (j = 0; j < 4; j++)
        {
            glViewSetEnable(disabled_views[j], false);
        }
    }

    if (!glTextureLoad(glGetTexture("target/warble")))
    {
        glViewSetEnable(GLV_Warble, false);
        glViewSetEnable(GLV_WarbleBlend, false);
    }

    glViewSetDepthClear(GLV_CameraSpace, true);
    glViewSetDepthClear(GLV_Transitions, true);
    glViewSetDepthClear(GLV_Transitions3D, true);
    glViewSetDepthClear(GLV_Anark3D_BG, true);
    glViewSetDepthClear(GLV_Anark3D_FG, true);

    ParticleSystem::ClearViews();
    ParticleSystem::AddView(GLV_Particles);

    ModeledScreenTransition::s_3DView = GLV_Transitions3D;
}

static void Initialize()
{
    nlTaskManager::AddTask(&clockUpdateTask, 0, -1);
    nlTaskManager::AddTask(&audioUpdateTask, 0, -1);
    return;
}

int GetRegion()
{
    static const int g_Region = 1;
    return (int)&g_Region;
}
