#ifndef _FEMANAGER_H_
#define _FEMANAGER_H_

class Event;

class FrontEnd
{
public:
    enum MenuEnterType
    {
        MET_INVALID = -1,
        MET_PAUSE = 0,
        MET_CHOOSESIDES = 1,
        MET_END = 2,
    };

    static void ReturnToFE();
    static void UpdateForGame(float);
    static void Update(float);
    static void ExitMenuState();
    static void EnterMenuState(FrontEnd::MenuEnterType);
    static void ExitWinnerScreen();
    static void EnterStartScreen(bool);
    static void SetControllerState();
    static void Destroy();
    static bool Initialize();
    static void FEEventHandler(Event*, void*);

    static int m_feStateCurrent;
    static int m_feStatePending;
    static int m_feStatePrevious;
    static int m_lastTaskState;
    static void* m_pPauseMenuCamera;
    static int m_hitStartPad;
    static int m_menuType;
    static unsigned char m_bGameOver;
    static unsigned char m_bInPauseMenuState;
    static float m_fDemoTimeElapsed;
    static float m_pauseDelay;
    static unsigned char m_ctrlConnectedState[4];
};

#endif // _FEMANAGER_H_
