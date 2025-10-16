#ifndef _FESLIDEMENU_H_
#define _FESLIDEMENU_H_

#include "Game/FE/tlComponentInstance.h"

enum ItemStates
{
    ON_INVALID = -1,
    ON_APPLY = 0,
    ON_HIGHLIGHT = 1,
    NUM_STATES = 2,
};

enum Tag
{
    EMPTY = 0,
    FREE_FUNCTION = 1,
    FUNCTOR = 2,
};

template <typename T>
class Function1
{
    enum Tag mTag; // offset 0x0, size 0x4
    union
    {                                 // inferred
        void (*mFreeFunction)(T*);    // offset 0x4, size 0x4
        struct FunctorBase* mFunctor; // offset 0x4, size 0x4
    };
}; // total size: 0x8

template <typename T>
class Function : public Function1<T>
{
}; // total size: 0x8

class SlideMenuItem
{
public:
    SlideMenuItem();
    virtual ~SlideMenuItem();

    /* 0x4 */ unsigned long mSlideMenuHash;            // offset 0x4, size 0x4
    /* 0x8 */ TLComponentInstance* mComponentInstance; // offset 0x8, size 0x4
    /* 0xC */ int mUserEnumType;                       // offset 0xC, size 0x4
}; // total size: 0x10

struct MenuItem
{
    Function<SlideMenuItem*> mCallbacks[3]; // offset 0x0, size 0x18
    SlideMenuItem* mType;                   // offset 0x18, size 0x4
    bool mDisabled;                         // offset 0x1C, size 0x1
    bool mLocked;                           // offset 0x1D, size 0x1
}; // total size: 0x20

class MenuList
{
public:
    MenuList();
    virtual ~MenuList();

    MenuItem mMenuItems[16]; // offset 0x4, size 0x200
    int mCurrentIndex;       // offset 0x204, size 0x4
    int mNumItemsAdded;      // offset 0x208, size 0x4
    unsigned char mWrapList; // offset 0x20C, size 0x1
    int mFlags;              // offset 0x210, size 0x4
}; // total size: 0x214

class SlideMenuList : public MenuList
{
public:
    SlideMenuList();
    virtual ~SlideMenuList();

    void SetSlide()
    {
        unsigned long mSlideMenuHash = mMenuItems[mCurrentIndex].mType->mSlideMenuHash;
        mComponentInstance->SetActiveSlide(mSlideMenuHash);
    }

    unsigned char mInputLocked;              // offset 0x214, size 0x1
    TLComponentInstance* mComponentInstance; // offset 0x218, size 0x4
}; // total size: 0x21C

class FESlideMenu
{
public:
    struct MenuItem
    {
        MenuItem() { };
        ~MenuItem() { };

        unsigned long ItemSlide;                     // offset 0x0, size 0x4
        class Function<FESlideMenu*> ItemCBFuncs[2]; // offset 0x4, size 0x10
    }; // total size: 0x14

    void UpdatePresentation();
    void PrevItem();
    void NextItem();
    void SetSlideByIndex(unsigned char);
    void ApplyFunction();
    void AddMenuItem(const char*);
    ~FESlideMenu();
    FESlideMenu(TLComponentInstance*);

    /* 0x0,  */ MenuItem m_menuItems[16];         // offset 0x0, size 0x140
    /* 0x140 */ unsigned char m_size;             // offset 0x140, size 0x1
    /* 0x141 */ unsigned char m_currentSlide;     // offset 0x141, size 0x1
    /* 0x142 */ unsigned char m_doWrapAround;     // offset 0x142, size 0x1
    /* 0x144 */ TLComponentInstance* m_pMenuComp; // offset 0x144, size 0x4
    /* 0x148 */ unsigned char m_lockInput;        // offset 0x148, size 0x1
    /* 0x14C */ void* m_callbackParam;            // offset 0x14C, size 0x4
    /* 0x150 */ long mLastChosenSlide;            // offset 0x150, size 0x4
    /* 0x154 */ long mLastRandomSlide;            // offset 0x154, size 0x4
    /* 0x158 */ long mNumCyclesRemaining;         // offset 0x158, size 0x4
    /* 0x15C */ float mRandDeltaTime;             // offset 0x15C, size 0x4
}; // total size: 0x160

#endif // _FESLIDEMENU_H_
