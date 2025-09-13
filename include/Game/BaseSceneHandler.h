#ifndef _BASESCENEHANDLER_H_
#define _BASESCENEHANDLER_H_

#include "types.h"

#include "Game/FE/FEPresentation.h"
#include "Game/FE/FEScene.h"

// Todo Figure this out? IDK Man.
class BaseScreenHandler
{
    // total size: 0x14
public:
    virtual ~BaseScreenHandler() = 0;
    virtual u32 fnc1() = 0;          // offset 0x0, size 0x4
    virtual void fnc2() = 0;         // offset 0x0, size 0x4
    virtual void fnc3() = 0;         // offset 0x0, size 0x4
    class BaseScreenHandler* m_next; // offset 0x4, size 0x4
    class BaseScreenHandler* m_prev; // offset 0x8, size 0x4
    class TLInstance* m_pTLInstance; // offset 0xC, size 0x4
    class FEScene* m_pFEScene;       // offset 0x10, size 0x4
};

class BaseSceneHandler
{
public:
    BaseSceneHandler()
    {
        m_bVisible = true;
        m_pScreenHandlerList = NULL;
        m_pActiveScreenHandler = NULL;
        m_pFEPresentation = NULL;
        m_pFEScene = NULL;
    };
    virtual ~BaseSceneHandler() { };
    virtual void Update(float);
    virtual void InitializeSubHandlers() { };
    virtual void AddScreenHandler(BaseScreenHandler*);
    virtual void RemoveScreenHandler(BaseScreenHandler*);
    virtual void SetPresentation(FEPresentation* presentation) { m_pFEPresentation = presentation; };
    virtual void OnActivate();
    virtual void SceneCreated();
    virtual void SetVisible(bool visible) { m_bVisible = visible; };

    unsigned long m_uHashID;                         // offset 0x4, size 0x4
    bool m_bVisible;                                 // offset 0x8, size 0x1
    class BaseScreenHandler* m_pScreenHandlerList;   // offset 0xC, size 0x4
    class BaseScreenHandler* m_pActiveScreenHandler; // offset 0x10, size 0x4
    class FEPresentation* m_pFEPresentation;         // offset 0x14, size 0x4
    class FEScene* m_pFEScene;                       // offset 0x18, size 0x4
    // /* 0x1C */ s32 m_unk_0x1C;
};

#endif // _BASESCENEHANDLER_H_
