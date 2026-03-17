#include "Game/SH/SHCrossFader.h"

// /**
//  * Offset/Address/Size: 0x0 | 0x800BCB38 | size: 0x20
//  */
// void FEResourceManager::Run(float)
// {
// }

// /**
//  * Offset/Address/Size: 0x140 | 0x800BC9DC | size: 0x15C
//  */
// void FEFinder<TLImageInstance, 2>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned
// long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0xBC | 0x800BC958 | size: 0x84
//  */
// void FEFinder<TLImageInstance, 2>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long,
// unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x38 | 0x800BC8D4 | size: 0x84
//  */
// void FEFinder<TLImageInstance, 2>::_Find<FEPresentation>(FEPresentation*, unsigned long, unsigned long, unsigned long, unsigned long,
// unsigned long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x800BC89C | size: 0x38
//  */
// void FEFinder<TLImageInstance, 2>::Find<FEPresentation>(FEPresentation*, InlineHasher, InlineHasher, InlineHasher, InlineHasher,
// InlineHasher, InlineHasher)
// {
// }

/**
 * Offset/Address/Size: 0x93C | 0x800BC840 | size: 0x5C
 */
CrossFaderScene::CrossFaderScene()
{
    mNumImages = 0;
    mCurrentImage = 0;
    mImageInstances = NULL;
    mTimer = 0.0f;
    mAlpha = 0.0f;
    mFadeState = FS_INVALID;
    mFadeToBlackTimer = 0.0f;
}

/**
 * Offset/Address/Size: 0x8B8 | 0x800BC7BC | size: 0x84
 */
CrossFaderScene::~CrossFaderScene()
{
}

/**
 * Offset/Address/Size: 0x510 | 0x800BC414 | size: 0x3A8
 */
void CrossFaderScene::SceneCreated()
{
}

/**
 * Offset/Address/Size: 0x0 | 0x800BBF04 | size: 0x510
 */
void CrossFaderScene::Update(float)
{
}
