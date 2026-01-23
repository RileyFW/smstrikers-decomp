#include "Game/FE/feManager.h"

#include "Game/Camera/CameraMan.h"
#include "Game/FE/feInput.h"
#include "Game/FE/feSceneManager.h"
#include "Game/Game.h"
#include "Game/GameInfo.h"
#include "Game/OverlayManager.h"
#include "Game/Sys/eventman.h"
#include "NL/glx/glxSwap.h"
#include "NL/nlTask.h"

// Global variables
static unsigned char AlreadyStartedStrikers101Menu;
static unsigned char DontCheckForControllerRemovalHack;
extern float g_AllActorsHidden;
extern unsigned char g_JaapAndJacksNastyHackBecauseWeDoNotKnowDifferenceBetweenPausePauseAndPostGamePause;

/**
 * Offset/Address/Size: 0x0 | 0x80094C84 | size: 0x44
 */
void FrontEnd::ReturnToFE()
{
    glxSwapSetBlack(true);
    if (nlTaskManager::m_pInstance->m_CurrState == 1)
    {
        nlTaskManager::m_pInstance->m_Locked = false;
    }
    nlTaskManager::SetNextState(4);
}

/**
 * Offset/Address/Size: 0x44 | 0x80094CC8 | size: 0x1A0
 */
void FrontEnd::UpdateForGame(float)
{
}

/**
 * Offset/Address/Size: 0x1E4 | 0x80094E68 | size: 0x33C
 */
void FrontEnd::Update(float)
{
}

/**
 * Offset/Address/Size: 0x520 | 0x800951A4 | size: 0x90
 */
void FrontEnd::ExitMenuState()
{
    if (!FESceneManager::s_pInstance->AreAllScenesValid())
        return;

    m_bInPauseMenuState = false;
    m_menuType = -1;
    m_feStatePending = m_feStatePrevious;
    nlTaskManager::m_pInstance->m_Locked = false;
    nlTaskManager::SetNextState(m_lastTaskState);
    OverlayManager::s_pInstance->Pop();
    g_pEventManager->CreateValidEvent(1, 0x14);
    g_pFEInput->EnableAnalogToDPadMapping(FE_ALL_PADS, false);
    m_pauseDelay = 1.5f;
}

/**
 * Offset/Address/Size: 0x5B0 | 0x80095234 | size: 0x188
 */
void FrontEnd::EnterMenuState(FrontEnd::MenuEnterType)
{
}

// Helper class to work around MWCC codegen for virtual destructor calls
class CameraDeleter {
public:
    virtual void DestroyWith(int);
};

/**
 * Offset/Address/Size: 0x738 | 0x800953BC | size: 0x70
 */
void FrontEnd::ExitWinnerScreen()
{
    CameraDeleter* cam;
    cCameraManager::PopCameraWithTransition(1.0f, eCT_EASE_IN, 0);
    cam = (CameraDeleter*)m_pPauseMenuCamera;
    if (cam) {
        cam->DestroyWith(1);
    }
    m_pPauseMenuCamera = 0;
    g_AllActorsHidden = 0.5f;
    g_JaapAndJacksNastyHackBecauseWeDoNotKnowDifferenceBetweenPausePauseAndPostGamePause = 1;
    DontCheckForControllerRemovalHack = 0;
    nlTaskManager::SetNextState(2);
}

/**
 * Offset/Address/Size: 0x7A8 | 0x8009542C | size: 0x48
 */
void FrontEnd::EnterStartScreen(bool)
{
    bool isInStrikers101 = false;
    if (GameInfoManager::s_pInstance->mIsInStrikers101Mode) {
        isInStrikers101 = true;
    }
    g_pGame->BeginGame(false, isInStrikers101);
    m_feStatePending = 6;
}

/**
 * Offset/Address/Size: 0x7F0 | 0x80095474 | size: 0x54
 */
void FrontEnd::SetControllerState()
{
    for (int i = 0; i < 4; i++)
    {
        m_ctrlConnectedState[i] = g_pFEInput->IsConnected((eFEINPUT_PAD)i);
    }
}

/**
 * Offset/Address/Size: 0x844 | 0x800954C8 | size: 0x10
 */
void FrontEnd::Destroy()
{
    m_feStateCurrent = -1;
    m_feStatePending = -1;
}

/**
 * Offset/Address/Size: 0x854 | 0x800954D8 | size: 0x48
 */
bool FrontEnd::Initialize()
{
    m_feStateCurrent = -1;
    m_feStatePending = -1;
    m_pPauseMenuCamera = 0;
    m_hitStartPad = 8;
    m_menuType = -1;
    m_bGameOver = 0;
    m_bInPauseMenuState = 0;
    m_fDemoTimeElapsed = 0.0f;
    m_pauseDelay = 1.5f;
    AlreadyStartedStrikers101Menu = 0;
    DontCheckForControllerRemovalHack = 0;
    return true;
}

/**
 * Offset/Address/Size: 0x89C | 0x80095520 | size: 0x9C
 */
void FrontEnd::FEEventHandler(Event*, void*)
{
}
