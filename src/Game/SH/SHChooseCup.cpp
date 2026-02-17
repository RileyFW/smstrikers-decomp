#include "Game/SH/SHChooseCup.h"
#include "Game/GameInfo.h"
#include "Game/GameSceneManager.h"
#include "Game/FE/fePopupMenu.h"

// /**
//  * Offset/Address/Size: 0x2C4 | 0x800DCE10 | size: 0xBC
//  */
// void BasicString<unsigned short, Detail::TempStringAllocator>::Append(const unsigned short*) const
// {
// }

// /**
//  * Offset/Address/Size: 0xBC | 0x800DCC08 | size: 0x208
//  */
// void BasicString<unsigned short, Detail::TempStringAllocator>::AppendInPlace<Detail::TempStringAllocator>(const BasicString<unsigned
// short, Detail::TempStringAllocator>&)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x800DCB4C | size: 0xBC
//  */
// void BasicString<unsigned short, Detail::TempStringAllocator>::Append<Detail::TempStringAllocator>(const BasicString<unsigned short,
// Detail::TempStringAllocator>&) const
// {
// }

// /**
//  * Offset/Address/Size: 0x680 | 0x800DCAC8 | size: 0x84
//  */
// void FEFinder<TLComponentInstance, 4>::_Find<FEPresentation>(FEPresentation*, unsigned long, unsigned long, unsigned long, unsigned long,
// unsigned long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x648 | 0x800DCA90 | size: 0x38
//  */
// void FEFinder<TLComponentInstance, 4>::Find<FEPresentation>(FEPresentation*, InlineHasher, InlineHasher, InlineHasher, InlineHasher,
// InlineHasher, InlineHasher)
// {
// }

// /**
//  * Offset/Address/Size: 0x4EC | 0x800DC934 | size: 0x15C
//  */
// void FEFinder<TLImageInstance, 2>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned
// long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x468 | 0x800DC8B0 | size: 0x84
//  */
// void FEFinder<TLImageInstance, 2>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long,
// unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x430 | 0x800DC878 | size: 0x38
//  */
// void FEFinder<TLImageInstance, 2>::Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher,
// InlineHasher)
// {
// }

// /**
//  * Offset/Address/Size: 0x2D4 | 0x800DC71C | size: 0x15C
//  */
// void FEFinder<TLTextInstance, 3>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned
// long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x250 | 0x800DC698 | size: 0x84
//  */
// void FEFinder<TLTextInstance, 3>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long,
// unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x218 | 0x800DC660 | size: 0x38
//  */
// void FEFinder<TLTextInstance, 3>::Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher,
// InlineHasher)
// {
// }

// /**
//  * Offset/Address/Size: 0xBC | 0x800DC504 | size: 0x15C
//  */
// void FEFinder<TLComponentInstance, 4>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long,
// unsigned long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x38 | 0x800DC480 | size: 0x84
//  */
// void FEFinder<TLComponentInstance, 4>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned
// long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x800DC448 | size: 0x38
//  */
// void FEFinder<TLComponentInstance, 4>::Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher,
// InlineHasher)
// {
// }

/**
 * Offset/Address/Size: 0x20B8 | 0x800DC33C | size: 0x10C
 */
void confirmedNewCup(bool isSuperCup)
{
    GameInfoManager* gim = nlSingleton<GameInfoManager>::s_pInstance;

    if (gim->mCurrentMode == GameInfoManager::GM_BOWSER_CUP)
    {
        gim->mCurrentCup = (BaseCup*)&gim->mBowserCupSeries;
        gim->mDoingKnockout = false;
        gim->mBowserCupKnockout.mRoundNumber = -5;
    }
    else if (gim->mCurrentMode == GameInfoManager::GM_SUPER_BOWSER_CUP)
    {
        gim->mCurrentCup = (BaseCup*)&gim->mSuperBowserCupSeries;
        gim->mDoingKnockout = false;
        gim->mSuperBowserCupKnockout.mRoundNumber = -5;
    }

    BaseCup* cup = nlSingleton<GameInfoManager>::s_pInstance->mCurrentCup;
    cup->mCupStarted = false;

    GameInfoManager* gim2 = nlSingleton<GameInfoManager>::s_pInstance;
    cup->mCupSettings.SkillLevel = gim2->mUserInfo.mGameplayOptions.SkillLevel;
    cup->mCupSettings.GameTime = gim2->mUserInfo.mGameplayOptions.GameTime;
    cup->mCupSettings.PowerUps = gim2->mUserInfo.mGameplayOptions.PowerUps;
    cup->mCupSettings.Shoot2Score = gim2->mUserInfo.mGameplayOptions.Shoot2Score;
    cup->mCupSettings.BowserAttackEnabled = gim2->mUserInfo.mGameplayOptions.BowserAttackEnabled;
    cup->mCupSettings.RumbleEnabled = gim2->mUserInfo.mGameplayOptions.RumbleEnabled;

    if (!isSuperCup)
    {
        nlSingleton<GameSceneManager>::s_pInstance->Push(SCENE_CUP_OPTIONS_INITIAL_CUP, SCREEN_NOTHING, true);
    }
    else
    {
        if (cup->mCupSettings.SkillLevel == GameplaySettings::ROOKIE)
        {
            cup->mCupSettings.SkillLevel = GameplaySettings::PROFESSIONAL;
        }
        nlSingleton<GameSceneManager>::s_pInstance->Push(SCENE_CUP_OPTIONS_INITIAL_SUPER, SCREEN_NOTHING, true);
    }
}

typedef BindExp1<void, void (*)(bool), bool> BindExp1_vfb;
typedef Function0<void>::FunctorImpl<BindExp1_vfb> FunctorImpl_vfb;

/**
 * Offset/Address/Size: 0x1F64 | 0x800DC1E8 | size: 0x154
 * TODO: 86.6% match - -inline deferred file, scratch uses -inline auto.
 * Bind hidden struct return pointer not generated; placement new duplicate beq;
 * Create by-value vs by-ref mangling difference. All caused by compiler flag mismatch.
 */
void startNewCup(bool isSuperCup)
{
    FEPopupMenu* pPopup = (FEPopupMenu*)nlSingleton<GameSceneManager>::s_pInstance->Push(SCENE_POPUP_MENU, SCREEN_NOTHING, false);

    {
        BindExp1_vfb bindResult = Bind<void, void (*)(bool), bool>(confirmedNewCup, isSuperCup);

        Function<FnVoidVoid> yes;
        yes.mTag = FUNCTOR;
        FunctorImpl_vfb* functor = (FunctorImpl_vfb*)nlMalloc(sizeof(FunctorImpl_vfb), 8, false);
        if (functor != NULL)
        {
            functor = new (functor) FunctorImpl_vfb();
            functor->mBind.mFuncPtr = bindResult.mFuncPtr;
            functor->mBind.mArg = bindResult.mArg;
        }
        yes.mFunctor = functor;

        Function<FnVoidVoid> no;
        no.mTag = FREE_FUNCTION;
        no.mFreeFunction = FEPopupMenu::Nothing;

        pPopup->Create(POPUP_REALLY_OVERWRITE, yes, no);
    }
    *(u8*)((u8*)pPopup + 0xAA4) = 0;
}

/**
 * Offset/Address/Size: 0x1EFC | 0x800DC180 | size: 0x68
 */
class BaseGameSceneManagerCont
{
public:
    virtual ~BaseGameSceneManagerCont();
    virtual void* Push(int, int, bool);
};

extern BaseGameSceneManagerCont* g_pGameSceneManager;

void continueCup(bool isSuperCup)
{
    if (isSuperCup)
    {
        g_pGameSceneManager->Push(20, 0, true); // SCENE_SUPER_CUP_STANDINGS
    }
    else
    {
        g_pGameSceneManager->Push(17, 0, true); // SCENE_CUP_STANDINGS
    }
}

/**
 * Offset/Address/Size: 0x1DF8 | 0x800DC07C | size: 0x104
 */
ChooseCupSceneV2::ChooseCupSceneV2(bool)
{
}

/**
 * Offset/Address/Size: 0x1CA0 | 0x800DBF24 | size: 0x158
 */
ChooseCupSceneV2::~ChooseCupSceneV2()
{
}

/**
 * Offset/Address/Size: 0x1A2C | 0x800DBCB0 | size: 0x274
 */
void ChooseCupSceneV2::SceneCreated()
{
}

/**
 * Offset/Address/Size: 0x132C | 0x800DB5B0 | size: 0x700
 */
void ChooseCupSceneV2::Update(float)
{
}

/**
 * Offset/Address/Size: 0x7AC | 0x800DAA30 | size: 0xB80
 */
void ChooseCupSceneV2::DisplayCup()
{
}

/**
 * Offset/Address/Size: 0x438 | 0x800DA6BC | size: 0x374
 */
void ChooseCupSceneV2::SetCurrentChamp(eTeamID, bool, TLComponentInstance*)
{
}

/**
 * Offset/Address/Size: 0x0 | 0x800DA284 | size: 0x438
 */
void ChooseCupSceneV2::Proceed()
{
}
