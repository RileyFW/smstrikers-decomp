#include "Game/SH/SHHealthWarning.h"

#include "NL/nlMemory.h"

// /**
//  * Offset/Address/Size: 0x2D4 | 0x8010DAA8 | size: 0x15C
//  */
// void FEFinder<TLComponentInstance, 4>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long,
// unsigned long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x250 | 0x8010DA24 | size: 0x84
//  */
// void FEFinder<TLComponentInstance, 4>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned
// long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x218 | 0x8010D9EC | size: 0x38
//  */
// void FEFinder<TLComponentInstance, 4>::Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher,
// InlineHasher)
// {
// }

// /**
//  * Offset/Address/Size: 0xBC | 0x8010D890 | size: 0x15C
//  */
// void FEFinder<TLImageInstance, 2>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned
// long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x38 | 0x8010D80C | size: 0x84
//  */
// void FEFinder<TLImageInstance, 2>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long,
// unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x8010D7D4 | size: 0x38
//  */
// void FEFinder<TLImageInstance, 2>::Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher,
// InlineHasher)
// {
// }

/**
 * Offset/Address/Size: 0x5C8 | 0x8010D6F8 | size: 0xDC
 */
HealthWarningSceneV2::HealthWarningSceneV2()
    : BaseSceneHandler()
{
    const char* messageImageFilename = "art/fe/HealthSafetyUI.res";

    mMessageImage = NULL;
    mPressButtonImage = NULL;
    mElapsedTime = 0.0f;

    AsyncImage* messageImage = new (nlMalloc(0x1C, 0x20, 1)) AsyncImage(messageImageFilename, NULL);
    mMessageImage = messageImage;

    AsyncImage* pressButtonImage = new (nlMalloc(0x1C, 0x20, 1)) AsyncImage(messageImageFilename, NULL);
    mPressButtonImage = pressButtonImage;
}

/**
 * Offset/Address/Size: 0x514 | 0x8010D644 | size: 0xB4
 */
HealthWarningSceneV2::~HealthWarningSceneV2()
{
    if (mMessageImage != NULL)
    {
        delete mMessageImage;
    }

    if (mPressButtonImage != NULL)
    {
        delete mPressButtonImage;
    }
}

/**
 * Offset/Address/Size: 0x204 | 0x8010D334 | size: 0x310
 */
void HealthWarningSceneV2::SceneCreated()
{
}

/**
 * Offset/Address/Size: 0x0 | 0x8010D130 | size: 0x204
 */
void HealthWarningSceneV2::Update(float)
{
}
