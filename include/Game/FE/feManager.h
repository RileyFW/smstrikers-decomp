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

    void ReturnToFE();
    void UpdateForGame(float);
    void Update(float);
    void ExitMenuState();
    void EnterMenuState(FrontEnd::MenuEnterType);
    void ExitWinnerScreen();
    void EnterStartScreen(bool);
    void SetControllerState();
    void Destroy();
    static bool Initialize();
    void FEEventHandler(Event*, void*);

    static int m_feStateCurrent;
};

#endif // _FEMANAGER_H_
