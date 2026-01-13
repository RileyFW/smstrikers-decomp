#include "Game/FE/feOptionsSubMenus.h"

#include "NL/platpad.h"
#include "Game/Audio/AudioLoader.h"
#include "Game/FE/feSlideMenu.h"

/**
 * Offset/Address/Size: 0x0 | 0x800B5044 | size: 0x4
 */
void OptionsSaveLoad::Revert()
{
}

/**
 * Offset/Address/Size: 0x4 | 0x800B5048 | size: 0x4
 */
void OptionsSaveLoad::Save()
{
}

/**
 * Offset/Address/Size: 0x8 | 0x800B504C | size: 0x11C
 */
void OptionsSaveLoad::Update(float)
{
}

/**
 * Offset/Address/Size: 0x124 | 0x800B5168 | size: 0xEC
 */
OptionsSaveLoad::~OptionsSaveLoad()
{
}

/**
 * Offset/Address/Size: 0x210 | 0x800B5254 | size: 0x410
 */
OptionsSaveLoad::OptionsSaveLoad(FEPresentation*, ButtonComponent::ButtonState)
{
}

/**
 * Offset/Address/Size: 0x620 | 0x800B5664 | size: 0x124
 */
void OptionsGameplayMenuV2::CloseItem(TLComponentInstance*)
{
}

/**
 * Offset/Address/Size: 0x744 | 0x800B5788 | size: 0x54
 */
void OptionsGameplayMenuV2::Revert()
{
    memcpy(&mSettings, &mBackupSettings, sizeof(GameplaySettings));
    mSettings.OnSettingsUpdated();
    cPlatPad::m_bDisableRumble = !mSettings.RumbleEnabled;
}

/**
 * Offset/Address/Size: 0x798 | 0x800B57DC | size: 0x224
 */
void OptionsGameplayMenuV2::Save()
{
    GameplaySettings localSettings;
    MenuList<SlideMenuItem>* list;
    int val;
    SlideMenuItem** pType;

    // Skill Level
    list = mSlideMenuLists[0];
    if (list != NULL)
    {
        pType = &list->mMenuItems[list->mCurrentIndex].mType;
        val = (*pType)->mUserEnumType;
    }
    else
    {
        val = -1;
    }
    localSettings.SkillLevel = (eSkillLevel)val;

    // Game Time - convert from menu index to seconds
    list = mSlideMenuLists[1];
    if (list != NULL)
    {
        pType = &list->mMenuItems[list->mCurrentIndex].mType;
        val = (*pType)->mUserEnumType;
    }
    else
    {
        val = -1;
    }
    switch (val)
    {
    case 0:
        localSettings.GameTime = 120;
        break;
    case 1:
        localSettings.GameTime = 180;
        break;
    case 2:
        localSettings.GameTime = 240;
        break;
    case 3:
        localSettings.GameTime = 300;
        break;
    case 4:
        localSettings.GameTime = 600;
        break;
    case 5:
        localSettings.GameTime = 900;
        break;
    default:
        localSettings.GameTime = 120;
        break;
    }

    // Power Ups
    list = mSlideMenuLists[2];
    if (list != NULL)
    {
        pType = &list->mMenuItems[list->mCurrentIndex].mType;
        val = (*pType)->mUserEnumType;
    }
    else
    {
        val = -1;
    }
    localSettings.PowerUps = (val == 0);

    // Shoot2Score
    list = mSlideMenuLists[3];
    if (list != NULL)
    {
        pType = &list->mMenuItems[list->mCurrentIndex].mType;
        val = (*pType)->mUserEnumType;
    }
    else
    {
        val = -1;
    }
    localSettings.Shoot2Score = (val == 0);

    // RumbleEnabled (index 4 stores to offset 0xB)
    list = mSlideMenuLists[4];
    if (list != NULL)
    {
        pType = &list->mMenuItems[list->mCurrentIndex].mType;
        val = (*pType)->mUserEnumType;
    }
    else
    {
        val = -1;
    }
    localSettings.RumbleEnabled = (val == 0);

    // BowserAttackEnabled (index 5 stores to offset 0xA)
    list = mSlideMenuLists[5];
    if (list != NULL)
    {
        pType = &list->mMenuItems[list->mCurrentIndex].mType;
        val = (*pType)->mUserEnumType;
    }
    else
    {
        val = -1;
    }
    localSettings.BowserAttackEnabled = (val == 0);

    mSettings = localSettings;
    mSettings.OnSettingsUpdated();

    cPlatPad::m_bDisableRumble = !localSettings.RumbleEnabled;
}

/**
 * Offset/Address/Size: 0x9BC | 0x800B5A00 | size: 0xEC
 */
OptionsGameplayMenuV2::~OptionsGameplayMenuV2()
{
}

/**
 * Offset/Address/Size: 0xAA8 | 0x800B5AEC | size: 0x438
 */
void OptionsGameplayMenuV2::BuildSkillLevelMenu(TLComponentInstance*, int, int)
{
}

/**
 * Offset/Address/Size: 0xEE0 | 0x800B5F24 | size: 0x850
 */
OptionsGameplayMenuV2::OptionsGameplayMenuV2(FEPresentation*, ButtonComponent::ButtonState, GameplaySettings& settings, int)
    : mSettings(settings)
{
}

/**
 * Offset/Address/Size: 0x1730 | 0x800B6774 | size: 0x30
 */
void OptionsVisualMenuV2::Revert()
{
    memcpy(&mSettings, &mBackupSettings, sizeof(VisualSettings));
}

/**
 * Offset/Address/Size: 0x1760 | 0x800B67A4 | size: 0xD4
 */
void OptionsVisualMenuV2::Save()
{
    MenuList<SlideMenuItem>* list;
    int val;
    SlideMenuItem** pType;

    // Auto zoom camera
    list = mSlideMenuLists[0];
    if (list != NULL)
    {
        pType = &list->mMenuItems[list->mCurrentIndex].mType;
        val = (*pType)->mUserEnumType;
    }
    else
    {
        val = -1;
    }
    mSettings.mIsAutoZoomCamera = (val == 0);

    // Camera zoom level
    list = mSlideMenuLists[1];
    if (list != NULL)
    {
        pType = &list->mMenuItems[list->mCurrentIndex].mType;
        val = (*pType)->mUserEnumType;
    }
    else
    {
        val = -1;
    }
    mSettings.mCameraZoomLevel = (float)val / 10.0f;

    // Widescreen
    list = mSlideMenuLists[2];
    if (list != NULL)
    {
        pType = &list->mMenuItems[list->mCurrentIndex].mType;
        val = (*pType)->mUserEnumType;
    }
    else
    {
        val = -1;
    }
    mSettings.mIsWidescreen = (val != 0);
}

/**
 * Offset/Address/Size: 0x1834 | 0x800B6878 | size: 0xC0
 */
void OptionsVisualMenuV2::Update(float dt)
{
    OptionsSubMenu::Update(dt);

    MenuItem<SlideMenuItem>* menuItem = &mMenuItems.mMenuItems[1];
    if (menuItem == NULL)
        return;

    int userEnumType;
    MenuList<SlideMenuItem>* list = mSlideMenuLists[0];
    if (list != NULL)
    {
        int index = list->mCurrentIndex;
        SlideMenuItem** pType = &list->mMenuItems[index].mType;
        userEnumType = (*pType)->mUserEnumType;
    }
    else
    {
        userEnumType = -1;
    }

    if (userEnumType == 0)
    {
        TLComponentInstance* compInstance = (TLComponentInstance*)menuItem->mType;
        if (compInstance->m_bVisible != false)
        {
            compInstance->m_bVisible = false;
            menuItem->mDisabled = true;

            SlideMenuList* list2 = (SlideMenuList*)mSlideMenuLists[1];
            TLComponentInstance* compInstance2 = list2->mComponentInstance;
            compInstance2->m_bVisible = false;
        }
    }
    else
    {
        TLComponentInstance* compInstance = (TLComponentInstance*)menuItem->mType;
        if (compInstance->m_bVisible == false)
        {
            compInstance->m_bVisible = true;
            menuItem->mDisabled = false;

            SlideMenuList* list2 = (SlideMenuList*)mSlideMenuLists[1];
            TLComponentInstance* compInstance2 = list2->mComponentInstance;
            compInstance2->m_bVisible = true;
        }
    }
}

/**
 * Offset/Address/Size: 0x18F4 | 0x800B6938 | size: 0xEC
 */
OptionsVisualMenuV2::~OptionsVisualMenuV2()
{
}

/**
 * Offset/Address/Size: 0x19E0 | 0x800B6A24 | size: 0x6E8
 */
OptionsVisualMenuV2::OptionsVisualMenuV2(FEPresentation*, ButtonComponent::ButtonState, VisualSettings& settings)
    : mSettings(settings)
{
}

/**
 * Offset/Address/Size: 0x20C8 | 0x800B710C | size: 0xA3C
 */
void OptionsAudioMenuV2::Update(float)
{
}

/**
 * Offset/Address/Size: 0x2B04 | 0x800B7B48 | size: 0x44
 */
void OptionsAudioMenuV2::Revert()
{
    memcpy(&mSettings, &mBackupSettings, sizeof(AudioSettings));
    mSettings.ForceApplySettings(false);
}

/**
 * Offset/Address/Size: 0x2B48 | 0x800B7B8C | size: 0x110
 */
void OptionsAudioMenuV2::Save()
{
    MenuList<SlideMenuItem>* list;
    int val;
    SlideMenuItem** pType;

    // Music Volume
    list = mSlideMenuLists[0];
    if (list != NULL)
    {
        pType = &list->mMenuItems[list->mCurrentIndex].mType;
        val = (*pType)->mUserEnumType;
    }
    else
    {
        val = -1;
    }
    mSettings.MusicVolume = val;

    // SFX Volume
    list = mSlideMenuLists[1];
    if (list != NULL)
    {
        pType = &list->mMenuItems[list->mCurrentIndex].mType;
        val = (*pType)->mUserEnumType;
    }
    else
    {
        val = -1;
    }
    mSettings.SFXVolume = val;

    // Voice Volume
    list = mSlideMenuLists[2];
    if (list != NULL)
    {
        pType = &list->mMenuItems[list->mCurrentIndex].mType;
        val = (*pType)->mUserEnumType;
    }
    else
    {
        val = -1;
    }
    mSettings.VoiceVolume = val;

    // Audio Mode
    list = mSlideMenuLists[3];
    if (list != NULL)
    {
        pType = &list->mMenuItems[list->mCurrentIndex].mType;
        val = (*pType)->mUserEnumType;
    }
    else
    {
        val = -1;
    }
    mSettings.Mode = (eAudioMode)val;

    mSettings.ApplySettings(mbUpdateMode, false);
    if (mbUpdateMode)
    {
        AudioLoader::PlayFEMenuMusic();
        mbUpdateMode = false;
    }
}

/**
 * Offset/Address/Size: 0x2C58 | 0x800B7C9C | size: 0xEC
 */
OptionsAudioMenuV2::~OptionsAudioMenuV2()
{
}

/**
 * Offset/Address/Size: 0x2D44 | 0x800B7D88 | size: 0x76C
 */
OptionsAudioMenuV2::OptionsAudioMenuV2(FEPresentation*, ButtonComponent::ButtonState, AudioSettings& settings)
    : mSettings(settings)

{
}

/**
 * Offset/Address/Size: 0x34B0 | 0x800B84F4 | size: 0x88C
 */
void OptionsCheatsMenu::BuildCustomPowerupsList(TLComponentInstance*, CustomPowerups, FEPresentation*)
{
}

/**
 * Offset/Address/Size: 0x3D3C | 0x800B8D80 | size: 0x7D4
 */
void OptionsCheatsMenu::BuildLockableSubMenuList(int, TLComponentInstance*, FEPresentation*, bool, int)
{
}

/**
 * Offset/Address/Size: 0x4510 | 0x800B9554 | size: 0x40
 */
void OptionsCheatsMenu::Revert()
{
    memcpy(&mSettings, &mBackupSettings, sizeof(CheatSettings));
    mSettings.OnSettingsUpdated();
}

/**
 * Offset/Address/Size: 0x4550 | 0x800B9594 | size: 0x170
 */
void OptionsCheatsMenu::Save()
{
}

/**
 * Offset/Address/Size: 0x46C0 | 0x800B9704 | size: 0xEC
 */
OptionsCheatsMenu::~OptionsCheatsMenu()
{
}

/**
 * Offset/Address/Size: 0x47AC | 0x800B97F0 | size: 0x720
 */
OptionsCheatsMenu::OptionsCheatsMenu(FEPresentation*, ButtonComponent::ButtonState, CheatSettings& settings)
    : mSettings(settings)
{
}

/**
 * Offset/Address/Size: 0x4ECC | 0x800B9F10 | size: 0xB8
 */
void OptionsSubMenu::SetAButtonLOC(unsigned long)
{
}

/**
 * Offset/Address/Size: 0x4F84 | 0x800B9FC8 | size: 0xC8
 */
void OptionsSubMenu::SetButtonState(ButtonComponent::ButtonState)
{
}

/**
 * Offset/Address/Size: 0x504C | 0x800BA090 | size: 0x434
 */
void OptionsSubMenu::BuildSubMenuList(int, TLComponentInstance*, bool, int)
{
}

/**
 * Offset/Address/Size: 0x5480 | 0x800BA4C4 | size: 0x124
 */
void OptionsSubMenu::GoBack()
{
}

/**
 * Offset/Address/Size: 0x55A4 | 0x800BA5E8 | size: 0xA30
 */
void OptionsSubMenu::Update(float)
{
}

/**
 * Offset/Address/Size: 0x5FD4 | 0x800BB018 | size: 0xDC
 */
OptionsSubMenu::~OptionsSubMenu()
{
}

// /**
//  * Offset/Address/Size: 0x0 | 0x800BB21C | size: 0x48
//  */
// void Function1<void, SlideMenuItem*>::FunctorBase::~FunctorBase()
// {
// }

// /**
//  * Offset/Address/Size: 0x54 | 0x800BB270 | size: 0x78
//  */
// void Function1<void, SlideMenuItem*>::FunctorImpl<BindExp1<void, Detail::MemFunImpl<void, void (SlideMenuList::*)()>,
// SlideMenuList*>>::Clone() const
// {
// }

// /**
//  * Offset/Address/Size: 0xCC | 0x800BB2E8 | size: 0x30
//  */
// void Function1<void, SlideMenuItem*>::FunctorImpl<BindExp1<void, Detail::MemFunImpl<void, void (SlideMenuList::*)()>,
// SlideMenuList*>>::operator()(SlideMenuItem*)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x800BB318 | size: 0xE4
//  */
// SlideMenuList::~SlideMenuList()
// {
// }

// /**
//  * Offset/Address/Size: 0xE4 | 0x800BB3FC | size: 0x60
//  */
// void MenuItem<SlideMenuItem>::~MenuItem()
// {
// }

// /**
//  * Offset/Address/Size: 0x1C8 | 0x800BB4E0 | size: 0x48
//  */
// SlideMenuItem::~SlideMenuItem()
// {
// }

// /**
//  * Offset/Address/Size: 0x210 | 0x800BB528 | size: 0x5C
//  */
// void Function1<void, SlideMenuItem*>::FunctorImpl<BindExp1<void, Detail::MemFunImpl<void, void (SlideMenuList::*)()>,
// SlideMenuList*>>::~FunctorImpl()
// {
// }

// /**
//  * Offset/Address/Size: 0x26C | 0x800BB584 | size: 0x4
//  */
// void SlideMenuList::Update(float)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x800BB588 | size: 0x38
//  */
// void FEFinder<TLComponentInstance, 4>::Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher,
// InlineHasher)
// {
// }

// /**
//  * Offset/Address/Size: 0x38 | 0x800BB5C0 | size: 0x84
//  */
// void FEFinder<TLComponentInstance, 4>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned
// long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0xBC | 0x800BB644 | size: 0x15C
//  */
// void FEFinder<TLComponentInstance, 4>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long,
// unsigned long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x218 | 0x800BB7A0 | size: 0x38
//  */
// void FEFinder<TLImageInstance, 2>::Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher,
// InlineHasher)
// {
// }

// /**
//  * Offset/Address/Size: 0x250 | 0x800BB7D8 | size: 0x84
//  */
// void FEFinder<TLImageInstance, 2>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long,
// unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x2D4 | 0x800BB85C | size: 0x15C
//  */
// void FEFinder<TLImageInstance, 2>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned
// long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x430 | 0x800BB9B8 | size: 0x38
//  */
// void FEFinder<TLTextInstance, 3>::Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher,
// InlineHasher)
// {
// }

// /**
//  * Offset/Address/Size: 0x468 | 0x800BB9F0 | size: 0x84
//  */
// void FEFinder<TLTextInstance, 3>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long,
// unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x4EC | 0x800BBA74 | size: 0x15C
//  */
// void FEFinder<TLTextInstance, 3>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned
// long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x648 | 0x800BBBD0 | size: 0x38
//  */
// void FEFinder<TLInstance, 4>::Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher)
// {
// }

// /**
//  * Offset/Address/Size: 0x680 | 0x800BBC08 | size: 0x84
//  */
// void FEFinder<TLInstance, 4>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long,
// unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x704 | 0x800BBC8C | size: 0x15C
//  */
// void FEFinder<TLInstance, 4>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long,
// unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x800BBDE8 | size: 0x70
//  */
// void MenuList<SlideMenuItem>::~MenuList()
// {
// }

// /**
//  * Offset/Address/Size: 0x70 | 0x800BBE58 | size: 0x58
//  */
// void MenuItem<SlideMenuItem>::MenuItem()
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x800BBEB0 | size: 0x1C
//  */
// void MemFun<SlideMenuList, void>(void (SlideMenuList::*)())
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x800BBECC | size: 0x38
//  */
// void Bind<void, Detail::MemFunImpl<void, void (SlideMenuList::*)()>, SlideMenuList*>(Detail::MemFunImpl<void, void (SlideMenuList::*)()>,
// SlideMenuList* const&)
// {
// }
