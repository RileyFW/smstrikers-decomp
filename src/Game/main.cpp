#include "types.h"
#include "Game/main.h"
#include "NL/gl/glView.h"
#include "NL/gl/glTexture.h"
#include "NL/gl/glState.h"
#include "Game/Effects/ParticleSystem.h"
#include "Game/Transitions/ModelTransition.h"

// static int g_Region __attribute__((section(".sdata2"))) = 1;
static int const g_Region = 1;

static bool g_bProfiling = false;
static bool g_bTweaking = false;
static bool g_e3_Build = false;
static bool g_Europe = false;
static bool g_bFranticPausing = false;
static int g_Language = 0;
static void* g_pTheLoadingManagerTask = nullptr;

ClockUpdateTask clockUpdateTask;
AudioUpdateTask audioUpdateTask;

int main(void)
{
    return 0;
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
    return g_Region;
}
