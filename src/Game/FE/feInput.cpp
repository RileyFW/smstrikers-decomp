#include "Game/FE/feInput.h"

/**
 * Offset/Address/Size: 0x0 | 0x8020EA0C | size: 0x274
 */
void FEInput::EnableAnalogToDPadMapping(eFEINPUT_PAD, bool)
{
}

/**
 * Offset/Address/Size: 0x274 | 0x8020EC80 | size: 0x220
 */
void FEInput::SetAutoRepeatParams(eFEINPUT_PAD pad, int, float, float)
{
    s32* remapArray = cPadManager::GetRemapArray();
    remapArray[pad] = 0;
}

/**
 * Offset/Address/Size: 0x494 | 0x8020EEA0 | size: 0x188
 */
void FEInput::Update(float)
{
}

/**
 * Offset/Address/Size: 0x61C | 0x8020F028 | size: 0x30
 */
void FEInput::HasInputLock(BaseSceneHandler*) const
{
}

/**
 * Offset/Address/Size: 0x64C | 0x8020F058 | size: 0x2C
 */
void FEInput::PopExclusiveInputLock(BaseSceneHandler*)
{
}

/**
 * Offset/Address/Size: 0x678 | 0x8020F084 | size: 0x2C
 */
void FEInput::PushExclusiveInputLock(BaseSceneHandler*, int)
{
}

/**
 * Offset/Address/Size: 0x6A4 | 0x8020F0B0 | size: 0x38
 */
void FEInput::EnableInputIfSceneHasFocus(BaseSceneHandler*)
{
}

/**
 * Offset/Address/Size: 0x6DC | 0x8020F0E8 | size: 0xD0
 */
void FEInput::JustReleased(eFEINPUT_PAD, int, bool, eFEINPUT_PAD*)
{
}

/**
 * Offset/Address/Size: 0x7AC | 0x8020F1B8 | size: 0xD0
 */
bool FEInput::JustPressed(eFEINPUT_PAD, int, bool, eFEINPUT_PAD*)
{
}

/**
 * Offset/Address/Size: 0x87C | 0x8020F288 | size: 0x36C
 */
void FEInput::IsAutoPressed(eFEINPUT_PAD, int, bool, eFEINPUT_PAD*)
{
}

/**
 * Offset/Address/Size: 0xBE8 | 0x8020F5F4 | size: 0x310
 */
void FEInput::IsPressed(eFEINPUT_PAD, int, bool, eFEINPUT_PAD*)
{
}

/**
 * Offset/Address/Size: 0xEF8 | 0x8020F904 | size: 0x9C
 */
void FEInput::IsConnected(eFEINPUT_PAD)
{
}

/**
 * Offset/Address/Size: 0xF94 | 0x8020F9A0 | size: 0x60
 */
void FEInput::GetGlobalPad(eFEINPUT_PAD) const
{
}

/**
 * Offset/Address/Size: 0xFF4 | 0x8020FA00 | size: 0x5C
 */
void FEInput::Reset()
{
}

/**
 * Offset/Address/Size: 0x1050 | 0x8020FA5C | size: 0x64
 */
FEInput::FEInput()
{
}

/**
 * Offset/Address/Size: 0x10B4 | 0x8020FAC0 | size: 0x40
 */
void FEInput::Initialize()
{
}

/**
 * Offset/Address/Size: 0x0 | 0x8020FB00 | size: 0xC
 */
void cGlobalPad::DisableLeftAnalogToDPadMap()
{
    m_isLeftAnalogToDPadMapEnabled = false;
}

/**
 * Offset/Address/Size: 0xC | 0x8020FB0C | size: 0xC
 */
void cGlobalPad::EnableLeftAnalogToDPadMap()
{
    m_isLeftAnalogToDPadMapEnabled = true;
}

/**
 * Offset/Address/Size: 0x18 | 0x8020FB18 | size: 0x8
 */
s32* cPadManager::GetRemapArray()
{
    return m_pRemapArray;
}

/**
 * Offset/Address/Size: 0x0 | 0x8020FB20 | size: 0x48
 */
FEInput::~FEInput()
{
    // TODO: figure out what this is
}
