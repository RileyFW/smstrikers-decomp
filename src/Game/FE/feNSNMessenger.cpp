#include "Game/FE/feNSNMessenger.h"

/**
 * Offset/Address/Size: 0x0 | 0x800A131C | size: 0x1C0
 */
void NSNMessengerScene::EnableScrolling(bool)
{
}

/**
 * Offset/Address/Size: 0x1C0 | 0x800A14DC | size: 0x8
 */
bool NSNMessengerScene::IsMessengerOpen() const
{
    return m_bVisible;
}

/**
 * Offset/Address/Size: 0x1C8 | 0x800A14E4 | size: 0x48
 */
void NSNMessengerScene::CloseMessengerNow()
{
    SetVisible(false);
    m_curState = MS_CLOSED;
}

/**
 * Offset/Address/Size: 0x210 | 0x800A152C | size: 0x64
 */
void NSNMessengerScene::CloseMessenger()
{
    FEPresentation* presentation = m_pFEScene->m_pFEPackage->GetPresentation();

    presentation->SetActiveSlide("Outro");
    presentation->m_currentSlide->m_time = 0.0f;
    presentation->m_currentSlide->Update(0.0f);

    m_curState = MS_CLOSING;
}

/**
 * Offset/Address/Size: 0x274 | 0x800A1590 | size: 0x1A4
 */
void NSNMessengerScene::SetDisplayMessage(const char*)
{
}

/**
 * Offset/Address/Size: 0x418 | 0x800A1734 | size: 0x220
 */
// void NSNMessengerScene::SetDisplayMessage(const BasicString<unsigned short, Detail::TempStringAllocator>&)
// {
// }

/**
 * Offset/Address/Size: 0x638 | 0x800A1954 | size: 0x70
 */
void NSNMessengerScene::ForceMessengerVisibleNow()
{
}

/**
 * Offset/Address/Size: 0x6A8 | 0x800A19C4 | size: 0x80
 */
void NSNMessengerScene::OpenMessengerNow()
{
}

/**
 * Offset/Address/Size: 0x728 | 0x800A1A44 | size: 0x8C
 */
void NSNMessengerScene::OpenMessenger()
{
}

/**
 * Offset/Address/Size: 0x7B4 | 0x800A1AD0 | size: 0x160
 */
void NSNMessengerScene::Update(float)
{
}

/**
 * Offset/Address/Size: 0x914 | 0x800A1C30 | size: 0x2C
 */
void NSNMessengerScene::SceneCreated()
{
}

/**
 * Offset/Address/Size: 0x940 | 0x800A1C5C | size: 0x180
 */
NSNMessengerScene::~NSNMessengerScene()
{
}

/**
 * Offset/Address/Size: 0xAC0 | 0x800A1DDC | size: 0x84
 */
NSNMessengerScene::NSNMessengerScene()
    : BaseOverlayHandler(0, POSITION_TOP)
{
}

// /**
//  * Offset/Address/Size: 0x0 | 0x800A1E60 | size: 0xA8
//  */
// void 0x800A1F08..0x800A1F0C | size: 0x4
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x800A1F08 | size: 0x4
//  */
// void BaseSceneHandler::SceneCreated()
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x800A1F0C | size: 0x38
//  */
// void FEFinder<TLTextInstance, 3>::Find<TLSlide>(TLSlide*, InlineHasher, InlineHasher, InlineHasher, InlineHasher, InlineHasher,
// InlineHasher)
// {
// }

// /**
//  * Offset/Address/Size: 0x38 | 0x800A1F44 | size: 0x84
//  */
// void FEFinder<TLTextInstance, 3>::_Find<TLSlide>(TLSlide*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long,
// unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0xBC | 0x800A1FC8 | size: 0x15C
//  */
// void FEFinder<TLTextInstance, 3>::_Find<TLInstance>(TLInstance*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned
// long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x218 | 0x800A2124 | size: 0x38
//  */
// void FEFinder<TLTextInstance, 3>::Find<FEPresentation>(FEPresentation*, InlineHasher, InlineHasher, InlineHasher, InlineHasher,
// InlineHasher, InlineHasher)
// {
// }

// /**
//  * Offset/Address/Size: 0x250 | 0x800A215C | size: 0x84
//  */
// void FEFinder<TLTextInstance, 3>::_Find<FEPresentation>(FEPresentation*, unsigned long, unsigned long, unsigned long, unsigned long,
// unsigned long, unsigned long)
// {
// }

// /**
//  * Offset/Address/Size: 0x0 | 0x800A223C | size: 0x8
//  */
// void NSNMessengerScene::@4@SceneCreated()
// {
// }

// /**
//  * Offset/Address/Size: 0x8 | 0x800A2244 | size: 0x8
//  */
// void NSNMessengerScene::@4@Update(float)
// {
// }

// /**
//  * Offset/Address/Size: 0x10 | 0x800A224C | size: 0x8
//  */
// void 0x802A9938..0x802A99C0 | size: 0x88
// {
// }
