#include "Game/FE/feScrollingTicker.h"

/**
 * Offset/Address/Size: 0x0 | 0x8009FC58 | size: 0x8
 */
void ScrollingTickerScene::IsMessengerOpen() const
{
}

/**
 * Offset/Address/Size: 0x8 | 0x8009FC60 | size: 0x15C
 */
void ScrollingTickerScene::CloseMessengerNow()
{
}

/**
 * Offset/Address/Size: 0x164 | 0x8009FDBC | size: 0xF4
 */
void ScrollingTickerScene::CloseMessenger()
{
}

/**
 * Offset/Address/Size: 0x258 | 0x8009FEB0 | size: 0x16C
 */
void ScrollingTickerScene::OpenMessengerNow()
{
}

/**
 * Offset/Address/Size: 0x3C4 | 0x800A001C | size: 0x20C
 */
void ScrollingTickerScene::OpenMessenger()
{
}

/**
 * Offset/Address/Size: 0x5D0 | 0x800A0228 | size: 0x60
 */
void ScrollingTickerScene::Update(float fDeltaT)
{
    BaseSceneHandler::Update(fDeltaT);
    m_pFETweenManager.Update(fDeltaT);
    if (m_active)
    {
        m_textScroller->Update(fDeltaT);
    }
}

/**
 * Offset/Address/Size: 0x630 | 0x800A0288 | size: 0x24
 */
// void ScrollingTickerScene::SetDisplayMessage(const BasicString<unsigned short, Detail::TempStringAllocator>&)
// {
// }

/**
 * Offset/Address/Size: 0x654 | 0x800A02AC | size: 0x634
 */
void ScrollingTickerScene::SceneCreated()
{
}

/**
 * Offset/Address/Size: 0xC88 | 0x800A08E0 | size: 0x178
 */
ScrollingTickerScene::~ScrollingTickerScene()
{
}

/**
 * Offset/Address/Size: 0xE00 | 0x800A0A58 | size: 0x88
 */
ScrollingTickerScene::ScrollingTickerScene()
{
}

/**
 * Offset/Address/Size: 0xE88 | 0x800A0AE0 | size: 0x30
 */
void ScrollingTickerScene::tickerClosed(void*)
{
    SetVisible(false);
}

/**
 * Offset/Address/Size: 0xEB8 | 0x800A0B10 | size: 0x18
 */
void ScrollingTickerScene::tickerOpened(void*)
{
}

/**
 * Offset/Address/Size: 0xED0 | 0x800A0B28 | size: 0xCC
 */
void ScrollingTickerScene::setScaleTweenCallback(void*, const float*)
{
}

/**
 * Offset/Address/Size: 0xF9C | 0x800A0BF4 | size: 0xB0
 */
void ScrollingTickerScene::setSizeTweenCallback(void*, const float*)
{
}

// /**
//  * Offset/Address/Size: 0x0 | 0x800A0CA4 | size: 0x128
//  */
// void 0x800A0DCC..0x800A1304 | size: 0x538
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x800A0DCC | size: 0x38
//  */
// void FEFinder<TLInstance, 3>::Find<FEPresentation>(FEPresentation*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher,
// InlineHasher)
// {
// }

// /**
//  * Offset/Address/Size: 0x38 | 0x800A0E04 | size: 0x84
//  */
// void FEFinder<TLInstance, 3>::_Find<FEPresentation>(FEPresentation*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned
// long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0xBC | 0x800A0E88 | size: 0x84
//  */
// void FEFinder<TLInstance, 3>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long,
// unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x140 | 0x800A0F0C | size: 0x15C
//  */
// void FEFinder<TLInstance, 3>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long,
// unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x29C | 0x800A1068 | size: 0x38
//  */
// void FEFinder<TLInstance, 2>::Find<FEPresentation>(FEPresentation*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher,
// InlineHasher)
// {
// }

// /**
//  * Offset/Address/Size: 0x2D4 | 0x800A10A0 | size: 0x84
//  */
// void FEFinder<TLInstance, 2>::_Find<FEPresentation>(FEPresentation*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned
// long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x358 | 0x800A1124 | size: 0x84
//  */
// void FEFinder<TLInstance, 2>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long,
// unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x3DC | 0x800A11A8 | size: 0x15C
//  */
// void FEFinder<TLInstance, 2>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long,
// unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x800A1304 | size: 0x8
//  */
// void ScrollingTickerScene::@4@SceneCreated()
// {
// }

// /**
//  * Offset/Address/Size: 0x8 | 0x800A130C | size: 0x8
//  */
// void ScrollingTickerScene::@4@Update(float)
// {
// }

// /**
//  * Offset/Address/Size: 0x10 | 0x800A1314 | size: 0x8
//  */
// void 0x802A9880..0x802A9938 | size: 0xB8
// {
// }
