#ifndef _FESLIDEMENU_H_
#define _FESLIDEMENU_H_

#include "Game/FE/tlComponentInstance.h"
#include "NL/nlFunction.h"

enum ItemStates
{
    ON_INVALID = -1,
    ON_APPLY = 0,
    ON_HIGHLIGHT = 1,
    NUM_STATES = 2,
};

class SlideMenuItem
{
public:
    SlideMenuItem();
    virtual ~SlideMenuItem();

    /* 0x4 */ unsigned long mSlideMenuHash;
    /* 0x8 */ TLComponentInstance* mComponentInstance;
    /* 0xC */ int mUserEnumType;
}; // total size: 0x10

struct MenuItem
{
    /*  0x00 */ Function<SlideMenuItem*> mCallbacks[3];
    /*  0x18 */ SlideMenuItem* mType;
    /*  0x1C */ bool mDisabled;
    /*  0x1D */ bool mLocked;
}; // total size: 0x20

class MenuList
{
public:
    MenuList();
    virtual ~MenuList();

    /* 0x004 */ MenuItem mMenuItems[16];
    /* 0x204 */ int mCurrentIndex;
    /* 0x208 */ int mNumItemsAdded;
    /* 0x20C */ unsigned char mWrapList;
    /* 0x210 */ int mFlags;
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

    /* 0x214 */ unsigned char mInputLocked;
    /* 0x218 */ TLComponentInstance* mComponentInstance;
}; // total size: 0x21C

class FESlideMenu
{
public:
    struct MenuItem
    {
        MenuItem() { };
        ~MenuItem() { };

        /* 0x0 */ unsigned long ItemSlide;
        /* 0x4 */ Function<FESlideMenu*> ItemCBFuncs[2];
    }; // total size: 0x20

    void UpdatePresentation();
    bool PrevItem();
    bool NextItem();
    void SetSlideByIndex(unsigned char);
    void ApplyFunction();
    MenuItem* AddMenuItem(const char*);
    ~FESlideMenu();
    FESlideMenu(TLComponentInstance*);

    /* 0x0,  */ MenuItem m_menuItems[16];
    /* 0x140 */ unsigned char m_size;
    /* 0x141 */ unsigned char m_currentSlide;
    /* 0x142 */ unsigned char m_doWrapAround;
    /* 0x144 */ TLComponentInstance* m_pMenuComp;
    /* 0x148 */ unsigned char m_lockInput;
    /* 0x14C */ void* m_callbackParam;
    /* 0x150 */ long mLastChosenSlide;
    /* 0x154 */ long mLastRandomSlide;
    /* 0x158 */ long mNumCyclesRemaining;
    /* 0x15C */ float mRandDeltaTime;
}; // total size: 0x160

#endif // _FESLIDEMENU_H_
