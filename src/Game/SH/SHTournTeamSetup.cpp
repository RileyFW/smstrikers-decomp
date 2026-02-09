#include "Game/SH/SHTournTeamSetup.h"
#include "types.h"

// Temporary dummy object for reference member initialization
static CustomTournament s_dummyTourn;

// /**
//  * Offset/Address/Size: 0x0 | 0x800E7710 | size: 0x40
//  */
// void Bind<void, Detail::MemFunImpl<void, void (TournTeamSetupSceneV2::*)(int)>, TournTeamSetupSceneV2*, int>(Detail::MemFunImpl<void,
// void (TournTeamSetupSceneV2::*)(int)>, TournTeamSetupSceneV2* const&, const int&)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x800E76F4 | size: 0x1C
//  */
// void MemFun<TournTeamSetupSceneV2, void, int>(void (TournTeamSetupSceneV2::*)(int))
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x800E7698 | size: 0x5C
//  */
// void Function1<void, TLComponentInstance*>::FunctorImpl<BindExp2<void, Detail::MemFunImpl<void, void (TournTeamSetupSceneV2::*)(int)>,
// TournTeamSetupSceneV2*, int>>::~FunctorImpl()
// {
// }

// /**
//  * Offset/Address/Size: 0x80 | 0x800E7664 | size: 0x34
//  */
// void Function1<void, TLComponentInstance*>::FunctorImpl<BindExp2<void, Detail::MemFunImpl<void, void (TournTeamSetupSceneV2::*)(int)>,
// TournTeamSetupSceneV2*, int>>::operator()(TLComponentInstance*)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x800E75E4 | size: 0x80
//  */
// void Function1<void, TLComponentInstance*>::FunctorImpl<BindExp2<void, Detail::MemFunImpl<void, void (TournTeamSetupSceneV2::*)(int)>,
// TournTeamSetupSceneV2*, int>>::Clone() const
// {
// }

// /**
//  * Offset/Address/Size: 0x704 | 0x800E7488 | size: 0x15C
//  */
// void FEFinder<TLInstance, 4>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long,
// unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x680 | 0x800E7404 | size: 0x84
//  */
// void FEFinder<TLInstance, 4>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long,
// unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x648 | 0x800E73CC | size: 0x38
//  */
// void FEFinder<TLInstance, 4>::Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher)
// {
// }

// /**
//  * Offset/Address/Size: 0x4EC | 0x800E7270 | size: 0x15C
//  */
// void FEFinder<TLImageInstance, 2>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned
// long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x468 | 0x800E71EC | size: 0x84
//  */
// void FEFinder<TLImageInstance, 2>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long,
// unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x430 | 0x800E71B4 | size: 0x38
//  */
// void FEFinder<TLImageInstance, 2>::Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher,
// InlineHasher)
// {
// }

// /**
//  * Offset/Address/Size: 0x2D4 | 0x800E7058 | size: 0x15C
//  */
// void FEFinder<TLTextInstance, 3>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned
// long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x250 | 0x800E6FD4 | size: 0x84
//  */
// void FEFinder<TLTextInstance, 3>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long,
// unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x218 | 0x800E6F9C | size: 0x38
//  */
// void FEFinder<TLTextInstance, 3>::Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher,
// InlineHasher)
// {
// }

// /**
//  * Offset/Address/Size: 0xBC | 0x800E6E40 | size: 0x15C
//  */
// void FEFinder<TLComponentInstance, 4>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long,
// unsigned long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x38 | 0x800E6DBC | size: 0x84
//  */
// void FEFinder<TLComponentInstance, 4>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned
// long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x800E6D84 | size: 0x38
//  */
// void FEFinder<TLComponentInstance, 4>::Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher,
// InlineHasher)
// {
// }

/**
 * Offset/Address/Size: 0x4DBC | 0x800E6C60 | size: 0x124
 */
TournTeamSetupSceneV2::TournTeamSetupSceneV2()
    : mTournInfo(s_dummyTourn)
{
}

/**
 * Offset/Address/Size: 0x4C18 | 0x800E6ABC | size: 0x1A4
 */
TournTeamSetupSceneV2::~TournTeamSetupSceneV2()
{
}

/**
 * Offset/Address/Size: 0x3ED4 | 0x800E5D78 | size: 0xD44
 */
void TournTeamSetupSceneV2::SceneCreated()
{
}

/**
 * Offset/Address/Size: 0x32F4 | 0x800E5198 | size: 0xBE0
 */
void TournTeamSetupSceneV2::Update(float)
{
}

/**
 * Offset/Address/Size: 0x2FB4 | 0x800E4E58 | size: 0x340
 */
void TournTeamSetupSceneV2::UpdateControllerIcon(int)
{
}

/**
 * Offset/Address/Size: 0x2500 | 0x800E43A4 | size: 0xAB4
 */
void TournTeamSetupSceneV2::UpdateRow(int)
{
    FORCE_DONT_INLINE;
}

/**
 * Offset/Address/Size: 0x1F30 | 0x800E3DD4 | size: 0x5D0
 */
void TournTeamSetupSceneV2::ChangeState(TournTeamSetupSceneV2::eTeamChooserState, TournTeamSetupSceneV2::eTeamChooserState)
{
    FORCE_DONT_INLINE;
}

/**
 * Offset/Address/Size: 0x1EC4 | 0x800E3D68 | size: 0x6C
 */
void TournTeamSetupSceneV2::StartChooseCaptain(int arg)
{
    mCurrentRow = arg + mRowOffset;

    if (!mTeamData[mCurrentRow].isEmpty)
    {
        mCaptainGrid->SetValid(mTeamData[mCurrentRow].captain, true);
    }

    ChangeState(STATE_SCROLLING, STATE_CAPTAIN);
}

/**
 * Offset/Address/Size: 0x1CC4 | 0x800E3B68 | size: 0x200
 */
void TournTeamSetupSceneV2::UpdateCaptainName()
{
    FORCE_DONT_INLINE;
}

/**
 * Offset/Address/Size: 0x1A48 | 0x800E38EC | size: 0x27C
 */
void TournTeamSetupSceneV2::UpdateSKName()
{
}

/**
 * Offset/Address/Size: 0x15F4 | 0x800E3498 | size: 0x454
 */
void TournTeamSetupSceneV2::Proceed()
{
}

/**
 * Offset/Address/Size: 0xC34 | 0x800E2AD8 | size: 0x9C0
 */
void TournTeamSetupSceneV2::FindCaptainSlideName(eTeamID)
{
}

/**
 * Offset/Address/Size: 0x76C | 0x800E2610 | size: 0x4C8
 */
void TournTeamSetupSceneV2::FindSidekickSlideName(eSidekickID)
{
}

/**
 * Offset/Address/Size: 0x4B0 | 0x800E2354 | size: 0x2BC
 */
void TournTeamSetupSceneV2::AutoFill()
{
}

/**
 * Offset/Address/Size: 0x3E4 | 0x800E2288 | size: 0xCC
 */
void TournTeamSetupSceneV2::UpdateForCurrentRow()
{
    int numRows;
    int i = 0;
    numRows = ((u32)(3 - (u32)mTournInfo.m_numTeams) >> 31) + 3;

    for (; i < numRows; i++)
    {
        UpdateRow(i);
    }

    mCurrentCaptain = mTeamData[mCurrentRow].captain;
    mCurrentSK = mTeamData[mCurrentRow].sidekick;

    mCaptainGrid->MoveHighlightToTarget(mCurrentCaptain);
    ((IGridComponent*)mSKGrid)->MoveHighlightToTarget((eTeamID)mCurrentSK);
    UpdateCaptainName();
}

/**
 * Offset/Address/Size: 0x1FC | 0x800E20A0 | size: 0x1E8
 */
void TournTeamSetupSceneV2::ScrollUp(bool)
{
}

/**
 * Offset/Address/Size: 0x0 | 0x800E1EA4 | size: 0x1FC
 */
void TournTeamSetupSceneV2::ScrollDown(bool)
{
}
