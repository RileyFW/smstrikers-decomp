#include "Game/Transitions/ScriptedTransition.h"

/**
 * Offset/Address/Size: 0x84 | 0x802083C4 | size: 0x4
 */
void TransitionModifierInterface::Cleanup()
{
}

/**
 * Offset/Address/Size: 0x3C | 0x8020837C | size: 0x48
 */
TransitionModifierInterface::~TransitionModifierInterface()
{
}

/**
 * Offset/Address/Size: 0x34 | 0x80208374 | size: 0x8
 */
void ScriptedScreenTransition::GetTransitionLength()
{
}

/**
 * Offset/Address/Size: 0x24 | 0x80208364 | size: 0x10
 */
void ScriptedScreenTransition::Time() const
{
}

/**
 * Offset/Address/Size: 0x18 | 0x80208358 | size: 0xC
 */
void ScriptedScreenTransition::Reset()
{
}

/**
 * Offset/Address/Size: 0x0 | 0x80208340 | size: 0x18
 */
void ScriptedScreenTransition::IsFinished()
{
}

/**
 * Offset/Address/Size: 0x1988 | 0x802082B4 | size: 0x8C
 */
void TransitionModifiers::ScaleModel::ApplyModifier(glPoly2&, float)
{
}

/**
 * Offset/Address/Size: 0x18CC | 0x802081F8 | size: 0xBC
 */
void TransitionModifiers::ScaleModel::InitializeFromParser(SimpleParser*)
{
}

/**
 * Offset/Address/Size: 0x1870 | 0x8020819C | size: 0x5C
 */
void TransitionModifiers::ScaleModel::~ScaleModel()
{
}

/**
 * Offset/Address/Size: 0x17B0 | 0x802080DC | size: 0xC0
 */
void TransitionModifiers::ColourBlend::ApplyModifier(glPoly2&, float)
{
}

/**
 * Offset/Address/Size: 0x1694 | 0x80207FC0 | size: 0x11C
 */
void TransitionModifiers::ColourBlend::InitializeFromParser(SimpleParser*)
{
}

/**
 * Offset/Address/Size: 0x1638 | 0x80207F64 | size: 0x5C
 */
void TransitionModifiers::ColourBlend::~ColourBlend()
{
}

/**
 * Offset/Address/Size: 0x15AC | 0x80207ED8 | size: 0x8C
 */
void TransitionModifiers::ScaleTexture::ApplyModifier(glPoly2&, float)
{
}

/**
 * Offset/Address/Size: 0x14F0 | 0x80207E1C | size: 0xBC
 */
void TransitionModifiers::ScaleTexture::InitializeFromParser(SimpleParser*)
{
}

/**
 * Offset/Address/Size: 0x1494 | 0x80207DC0 | size: 0x5C
 */
void TransitionModifiers::ScaleTexture::~ScaleTexture()
{
}

/**
 * Offset/Address/Size: 0x1408 | 0x80207D34 | size: 0x8C
 */
void TransitionModifiers::TranslateModel::ApplyModifier(glPoly2&, float)
{
}

/**
 * Offset/Address/Size: 0x134C | 0x80207C78 | size: 0xBC
 */
void TransitionModifiers::TranslateModel::InitializeFromParser(SimpleParser*)
{
}

/**
 * Offset/Address/Size: 0x12F0 | 0x80207C1C | size: 0x5C
 */
void TransitionModifiers::TranslateModel::~TranslateModel()
{
}

/**
 * Offset/Address/Size: 0x1264 | 0x80207B90 | size: 0x8C
 */
void TransitionModifiers::TranslateTexture::ApplyModifier(glPoly2&, float)
{
}

/**
 * Offset/Address/Size: 0x11A8 | 0x80207AD4 | size: 0xBC
 */
void TransitionModifiers::TranslateTexture::InitializeFromParser(SimpleParser*)
{
}

/**
 * Offset/Address/Size: 0x114C | 0x80207A78 | size: 0x5C
 */
void TransitionModifiers::TranslateTexture::~TranslateTexture()
{
}

/**
 * Offset/Address/Size: 0x1064 | 0x80207990 | size: 0xE8
 */
void TransitionModifiers::RotateModel::ApplyModifier(glPoly2&, float)
{
}

/**
 * Offset/Address/Size: 0xF9C | 0x802078C8 | size: 0xC8
 */
void TransitionModifiers::RotateModel::InitializeFromParser(SimpleParser*)
{
}

/**
 * Offset/Address/Size: 0xF40 | 0x8020786C | size: 0x5C
 */
void TransitionModifiers::RotateModel::~RotateModel()
{
}

/**
 * Offset/Address/Size: 0xE58 | 0x80207784 | size: 0xE8
 */
void TransitionModifiers::RotateTexture::ApplyModifier(glPoly2&, float)
{
}

/**
 * Offset/Address/Size: 0xD90 | 0x802076BC | size: 0xC8
 */
void TransitionModifiers::RotateTexture::InitializeFromParser(SimpleParser*)
{
}

/**
 * Offset/Address/Size: 0xD34 | 0x80207660 | size: 0x5C
 */
void TransitionModifiers::RotateTexture::~RotateTexture()
{
}

/**
 * Offset/Address/Size: 0xCE8 | 0x80207614 | size: 0x4C
 */
void TransitionModifiers::ScreenBlur::Cleanup()
{
}

/**
 * Offset/Address/Size: 0xCE4 | 0x80207610 | size: 0x4
 */
void TransitionModifiers::ScreenBlur::ApplyModifier(glPoly2&, float)
{
}

/**
 * Offset/Address/Size: 0xC60 | 0x8020758C | size: 0x84
 */
void TransitionModifiers::ScreenBlur::InitializeFromParser(SimpleParser*)
{
}

/**
 * Offset/Address/Size: 0xC04 | 0x80207530 | size: 0x5C
 */
void TransitionModifiers::ScreenBlur::~ScreenBlur()
{
}

/**
 * Offset/Address/Size: 0xBC8 | 0x802074F4 | size: 0x3C
 */
void TransitionModifiers::ScreenGrab::Cleanup()
{
}

/**
 * Offset/Address/Size: 0xB64 | 0x80207490 | size: 0x64
 */
void TransitionModifiers::ScreenGrab::ApplyModifier(glPoly2&, float)
{
}

/**
 * Offset/Address/Size: 0xB60 | 0x8020748C | size: 0x4
 */
void TransitionModifiers::ScreenGrab::InitializeFromParser(SimpleParser*)
{
}

/**
 * Offset/Address/Size: 0xB04 | 0x80207430 | size: 0x5C
 */
void TransitionModifiers::ScreenGrab::~ScreenGrab()
{
}

/**
 * Offset/Address/Size: 0xA74 | 0x802073A0 | size: 0x90
 */
void TransitionModifiers::ToScreenCoordinates::ApplyModifier(glPoly2&, float)
{
}

/**
 * Offset/Address/Size: 0xA70 | 0x8020739C | size: 0x4
 */
void TransitionModifiers::ToScreenCoordinates::InitializeFromParser(SimpleParser*)
{
}

/**
 * Offset/Address/Size: 0xA14 | 0x80207340 | size: 0x5C
 */
void TransitionModifiers::ToScreenCoordinates::~ToScreenCoordinates()
{
}

/**
 * Offset/Address/Size: 0x9A0 | 0x802072CC | size: 0x74
 */
ScriptedScreenTransition::ScriptedScreenTransition()
{
}

/**
 * Offset/Address/Size: 0x8D0 | 0x802071FC | size: 0xD0
 */
ScriptedScreenTransition::~ScriptedScreenTransition()
{
}

/**
 * Offset/Address/Size: 0x8C0 | 0x802071EC | size: 0x10
 */
void ScriptedScreenTransition::Update(float)
{
}

/**
 * Offset/Address/Size: 0x708 | 0x80207034 | size: 0x1B8
 */
void ScriptedScreenTransition::Render(eGLView)
{
}

/**
 * Offset/Address/Size: 0x698 | 0x80206FC4 | size: 0x70
 */
void ScriptedScreenTransition::Cancel()
{
}

/**
 * Offset/Address/Size: 0x3B8 | 0x80206CE4 | size: 0x2E0
 */
void ScriptedScreenTransition::InitializeFromParser(SimpleParser*)
{
}

/**
 * Offset/Address/Size: 0x0 | 0x8020692C | size: 0x3B8
 */
void ScriptedScreenTransition::GetModifierFromName(char*)
{
}
