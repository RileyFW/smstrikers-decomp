#include "Game/SH/SHProgressiveScan.h"

// /**
//  * Offset/Address/Size: 0x3DC | 0x80111B3C | size: 0x15C
//  */
// void FEFinder<TLComponentInstance, 4>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long,
//                                                          unsigned long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x358 | 0x80111AB8 | size: 0x84
//  */
// void FEFinder<TLComponentInstance, 4>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned
// long,
//                                                       unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x2D4 | 0x80111A34 | size: 0x84
//  */
// void FEFinder<TLComponentInstance, 4>::_Find<FEPresentation>(FEPresentation*, unsigned long, unsigned long, unsigned long, unsigned long,
//                                                              unsigned long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x29C | 0x801119FC | size: 0x38
//  */
// void FEFinder<TLComponentInstance, 4>::Find<FEPresentation>(FEPresentation*, InlineHasher, InlineHasher, InlineHasher, InlineHasher,
//                                                             InlineHasher, InlineHasher)
// {
// }

// /**
//  * Offset/Address/Size: 0x140 | 0x801118A0 | size: 0x15C
//  */
// void FEFinder<TLImageInstance, 2>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned
// long,
//                                                      unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0xBC | 0x8011181C | size: 0x84
//  */
// void FEFinder<TLImageInstance, 2>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long,
//                                                   unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x38 | 0x80111798 | size: 0x84
//  */
// void FEFinder<TLImageInstance, 2>::_Find<FEPresentation>(FEPresentation*, unsigned long, unsigned long, unsigned long, unsigned long,
//                                                          unsigned long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x80111760 | size: 0x38
//  */
// void FEFinder<TLImageInstance, 2>::Find<FEPresentation>(FEPresentation*, InlineHasher, InlineHasher, InlineHasher, InlineHasher,
//                                                         InlineHasher, InlineHasher)
// {
// }

/**
 * Offset/Address/Size: 0x1148 | 0x80111618 | size: 0x148
 */
ProgressiveScanScene::ProgressiveScanScene(bool)
{
}

/**
 * Offset/Address/Size: 0x107C | 0x8011154C | size: 0xCC
 */
ProgressiveScanScene::~ProgressiveScanScene()
{
    delete mUseProgressiveImage[0];
    delete mUseProgressiveImage[1];
    delete mConfirmationImage;
}

/**
 * Offset/Address/Size: 0xD08 | 0x801111D8 | size: 0x374
 */
void ProgressiveScanScene::SceneCreated()
{
}

/**
 * Offset/Address/Size: 0x940 | 0x80110E10 | size: 0x3C8
 */
void ProgressiveScanScene::Update(float)
{
}

/**
 * Offset/Address/Size: 0x0 | 0x801104D0 | size: 0x940
 */
void ProgressiveScanScene::SwitchMessageImage()
{
}
