#include "types.h"
#include "Game/main.h"

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
    return;
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
