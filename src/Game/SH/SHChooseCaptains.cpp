#include "Game/SH/SHChooseCaptains.h"

// /**
//  * Offset/Address/Size: 0x0 | 0x800D8554 | size: 0x2C
//  */
// void IChooseCaptain::SetPhaseReady(int)
// {
// }

// /**
//  * Offset/Address/Size: 0xAB0 | 0x800D83F8 | size: 0x15C
//  */
// void FEFinder<TLInstance, 4>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long,
// unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0xA2C | 0x800D8374 | size: 0x84
//  */
// void FEFinder<TLInstance, 4>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long,
// unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x9F4 | 0x800D833C | size: 0x38
//  */
// void FEFinder<TLInstance, 4>::Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher)
// {
// }

// /**
//  * Offset/Address/Size: 0x898 | 0x800D81E0 | size: 0x15C
//  */
// void FEFinder<TLInstance, 5>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long,
// unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x814 | 0x800D815C | size: 0x84
//  */
// void FEFinder<TLInstance, 5>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long,
// unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x7DC | 0x800D8124 | size: 0x38
//  */
// void FEFinder<TLInstance, 5>::Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher)
// {
// }

// /**
//  * Offset/Address/Size: 0x680 | 0x800D7FC8 | size: 0x15C
//  */
// void FEFinder<TLInstance, 3>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long,
// unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x648 | 0x800D7F90 | size: 0x38
//  */
// void FEFinder<TLInstance, 3>::Find<TLInstance>(TLInstance*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher,
// InlineHasher)
// {
// }

// /**
//  * Offset/Address/Size: 0x4EC | 0x800D7E34 | size: 0x15C
//  */
// void FEFinder<TLComponentInstance, 4>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long,
// unsigned long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x468 | 0x800D7DB0 | size: 0x84
//  */
// void FEFinder<TLComponentInstance, 4>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned
// long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x430 | 0x800D7D78 | size: 0x38
//  */
// void FEFinder<TLComponentInstance, 4>::Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher,
// InlineHasher)
// {
// }

// /**
//  * Offset/Address/Size: 0x2D4 | 0x800D7C1C | size: 0x15C
//  */
// void FEFinder<TLInstance, 2>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long,
// unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x250 | 0x800D7B98 | size: 0x84
//  */
// void FEFinder<TLInstance, 2>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long,
// unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x218 | 0x800D7B60 | size: 0x38
//  */
// void FEFinder<TLInstance, 2>::Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher)
// {
// }

// /**
//  * Offset/Address/Size: 0xBC | 0x800D7A04 | size: 0x15C
//  */
// void FEFinder<TLTextInstance, 3>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned
// long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x38 | 0x800D7980 | size: 0x84
//  */
// void FEFinder<TLTextInstance, 3>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long,
// unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x800D7948 | size: 0x38
//  */
// void FEFinder<TLTextInstance, 3>::Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher,
// InlineHasher)
// {
// }

/**
 * Offset/Address/Size: 0xE64 | 0x800D78AC | size: 0x9C
 */
ChooseCaptainsSceneV2::ChooseCaptainsSceneV2(ChooseCaptainsSceneV2::SceneType)
{
}

/**
 * Offset/Address/Size: 0xD20 | 0x800D7768 | size: 0x144
 */
ChooseCaptainsSceneV2::~ChooseCaptainsSceneV2()
{
}

/**
 * Offset/Address/Size: 0xC28 | 0x800D7670 | size: 0xF8
 */
void ChooseCaptainsSceneV2::SceneCreated()
{
}

/**
 * Offset/Address/Size: 0xBE0 | 0x800D7628 | size: 0x48
 */
void ChooseCaptainsSceneV2::ChangeSceneType(ChooseCaptainsSceneV2::SceneType sceneType)
{
    mSceneType = sceneType;
    switch (mSceneType)
    {
    case 0:
        ResetForCHOOSECAPTAINS();
        break;
    case 1:
        ResetForCHOOSESIDES();
        break;
    }
}

/**
 * Offset/Address/Size: 0xA7C | 0x800D74C4 | size: 0x164
 */
void ChooseCaptainsSceneV2::ResetForCHOOSECAPTAINS()
{
    FORCE_DONT_INLINE;
}

/**
 * Offset/Address/Size: 0x930 | 0x800D7378 | size: 0x14C
 */
void ChooseCaptainsSceneV2::ResetForCHOOSESIDES()
{
    FORCE_DONT_INLINE;
}

/**
 * Offset/Address/Size: 0x560 | 0x800D6FA8 | size: 0x3D0
 */
void ChooseCaptainsSceneV2::Update(float)
{
}

/**
 * Offset/Address/Size: 0xE4 | 0x800D6B2C | size: 0x47C
 */
void ChooseCaptainsSceneV2::BindChooseSideInstances()
{
}

/**
 * Offset/Address/Size: 0x0 | 0x800D6A48 | size: 0xE4
 */
void ChooseCaptainsSceneV2::CreateTicker()
{
}
