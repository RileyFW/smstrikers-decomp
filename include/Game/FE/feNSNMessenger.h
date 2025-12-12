#ifndef _FENSNMESSENGER_H_
#define _FENSNMESSENGER_H_

// void 0x800A1F08..0x800A1F0C | size: 0x4;
// void 0x802A9938..0x802A99C0 | size: 0x88;

#include "Game/BaseSceneHandler.h"
class NSNMessengerScene
{
public:
    void EnableScrolling(bool);
    void IsMessengerOpen() const;
    void CloseMessengerNow();
    void CloseMessenger();
    void SetDisplayMessage(const char*);
    // void SetDisplayMessage(const BasicString<unsigned short, Detail::TempStringAllocator>&);
    void ForceMessengerVisibleNow();
    void OpenMessengerNow();
    void OpenMessenger();
    void Update(float);
    void SceneCreated();
    ~NSNMessengerScene();
    NSNMessengerScene();
    // void @4@SceneCreated();
    // void @4@Update(float);
};

// class BaseSceneHandler
// {
// public:
//     void SceneCreated();
// };

// class FEFinder<TLTextInstance, 3>
// {
// public:
//     void Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher);
//     void _Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
//     void _Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
//     void Find<FEPresentation>(FEPresentation*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher);
//     void _Find<FEPresentation>(FEPresentation*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned
//     long);
// };

enum ScreenPosition
{
    POSITION_INVALID = -1,
    POSITION_TOP_LEFT = 0,
    POSITION_TOP_MIDDLE = 1,
    POSITION_TOP_RIGHT = 2,
    POSITION_MIDDLE_LEFT = 3,
    POSITION_MIDDLE_MIDDLE = 4,
    POSITION_MIDDLE_RIGHT = 5,
    POSITION_BOTTOM_LEFT = 6,
    POSITION_BOTTOM_MIDDLE = 7,
    POSITION_BOTTOM_RIGHT = 8,
    POSITION_TOP = 9,
    POSITION_MIDDLE = 10,
    POSITION_BOTTOM = 11,
    POSITION_ALL = 12,
    NUM_POSITIONS = 13,
};

class BaseOverlayHandler : public BaseSceneHandler
{
public:
    BaseOverlayHandler(u32 VisibilityMask, ScreenPosition position = POSITION_TOP)
    {
        mPosition = position;
        mVisibilityMask = VisibilityMask;
        mWasLastVisible = false;
    }
    virtual ~BaseOverlayHandler() { };

    /* 0x1C */ ScreenPosition mPosition;
    /* 0x20 */ u32 mVisibilityMask;
    /* 0x24 */ bool mWasLastVisible;
}; // total size: 0x28

#endif // _FENSNMESSENGER_H_
