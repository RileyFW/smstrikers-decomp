#include "Game/FE/feInput.h"

#include "NL/nlMemory.h"
#include "NL/platpad.h"
#include "types.h"
#include <string.h>
#include <math.h>

FEInput* g_pFEInput = nullptr;
// s32* FEInput::m_pRemapArray = nullptr;

static inline bool test1(const float& diff)
{
    return (diff > 0.0001f) ? true : ((float)fabs(diff) <= 0.0001f);
}

struct FEPadData
{
    /* 0x00 */ float fButtonInitialDelay[12];
    /* 0x30 */ float fButtonRepeatRate[12];
    /* 0x60 */ float fButtonTimeSinceLastRepeat[12];
    /* 0x90 */ bool bIsPressed[12];
}; // total size: 0x9C

FEPadData g_aFEPadData[4];

/**
 * Offset/Address/Size: 0x0 | 0x8020EA0C | size: 0x274
 */
void FEInput::EnableAnalogToDPadMapping(eFEINPUT_PAD, bool)
{
    FORCE_DONT_INLINE;
}

/**
 * Offset/Address/Size: 0x274 | 0x8020EC80 | size: 0x220
 * TODO: Recursion still has some reg issues
 */
void FEInput::SetAutoRepeatParams(eFEINPUT_PAD pad, int button, float initialdelay, float repeatrate)
{
    u32 buttonIndex = GetButtonIndex(cPadManager::GetRemapArray()[button]);

    if (pad == FE_ALL_PADS)
    {
        for (int i = 0; i < 4; i++)
        {
            SetAutoRepeatParams((eFEINPUT_PAD)i, button, initialdelay, repeatrate);
        }
    }
    else
    {
        g_aFEPadData[pad].fButtonInitialDelay[buttonIndex] = initialdelay;
        g_aFEPadData[pad].fButtonRepeatRate[buttonIndex] = repeatrate;
    }
}

/**
 * Offset/Address/Size: 0x494 | 0x8020EEA0 | size: 0x188
 * TODO: work in progress
 */
void FEInput::Update(float dt)
{
    for (int padIndex = 0; padIndex < 4; padIndex++)
    {
        FEPadData* padData = g_aFEPadData;
        FEPadData* padDataAlt = padData;
        int buttonMask = 1;

        for (int buttonIndex = 0; buttonIndex < 12; buttonIndex++)
        {
            padData->bIsPressed[buttonIndex] = false;

            if (cPadManager::GetPad(padIndex)->IsPressed(buttonMask, false))
            {
                if (padDataAlt->fButtonTimeSinceLastRepeat[buttonIndex] != 0.0f)
                {
                    float buttonStateTime = cPadManager::GetPad(padIndex)->GetButtonStateTime(buttonMask, false);
                    float diff = buttonStateTime - padDataAlt->fButtonInitialDelay[buttonIndex];
                    bool bShouldRepeat = true;
                    float timeSinceRepeat = padDataAlt->fButtonTimeSinceLastRepeat[buttonIndex];
                    float repeatRate = padDataAlt->fButtonRepeatRate[buttonIndex];

                    if (diff > 0.0001f)
                    {
                    }
                    else if ((float)fabs(diff) <= 0.0001f)
                    {
                    }
                    else
                    {
                        bShouldRepeat = false;
                    }

                    if (bShouldRepeat)
                    {
                        bool bShouldRepeat2 = true;
                        float diff2 = buttonStateTime - timeSinceRepeat - repeatRate;

                        if (!(diff2 > 0.0001f))
                        {
                            if ((float)fabs(diff2) <= 0.0001f)
                            {
                                bShouldRepeat2 = false;
                            }
                        }

                        if (bShouldRepeat2)
                        {
                            padDataAlt->fButtonTimeSinceLastRepeat[buttonIndex] = buttonStateTime;
                            padDataAlt->bIsPressed[buttonIndex] = true;
                        }
                    }
                }
                else
                {
                    padDataAlt->fButtonTimeSinceLastRepeat[buttonIndex] = cPadManager::GetPad(padIndex)->GetButtonStateTime(buttonMask, false);
                    padDataAlt->bIsPressed[buttonIndex] = true;
                }
            }
            else
            {
                padDataAlt->fButtonTimeSinceLastRepeat[buttonIndex] = 0.0f;
            }

            buttonMask <<= 1;
        }
        padData++;
    }
}

/**
 * Offset/Address/Size: 0x61C | 0x8020F028 | size: 0x30
 */
bool FEInput::HasInputLock(BaseSceneHandler* pRequestingSceneHandler) const
{
    int depth = m_InputLockDepth;
    if (depth == 0)
    {
        return false;
    }

    return m_nExclusiveInputSceneHashIDStack[depth - 1].m_pBaseSceneHandler == pRequestingSceneHandler;
}

/**
 * Offset/Address/Size: 0x64C | 0x8020F058 | size: 0x2C
 */
void FEInput::PopExclusiveInputLock(BaseSceneHandler* pRequestingSceneHandler)
{
    m_InputLockDepth -= 1;
    InputLockEntry& entry = m_nExclusiveInputSceneHashIDStack[m_InputLockDepth];
    entry.m_pBaseSceneHandler = nullptr;
    entry.m_customID = -1;
}

/**
 * Offset/Address/Size: 0x678 | 0x8020F084 | size: 0x2C
 */
void FEInput::PushExclusiveInputLock(BaseSceneHandler* pRequestingSceneHandler, int customID)
{
    m_nExclusiveInputSceneHashIDStack[m_InputLockDepth].m_pBaseSceneHandler = pRequestingSceneHandler;
    m_nExclusiveInputSceneHashIDStack[m_InputLockDepth].m_customID = customID;
    m_InputLockDepth++;
}

/**
 * Offset/Address/Size: 0x6A4 | 0x8020F0B0 | size: 0x38
 */
void FEInput::EnableInputIfSceneHasFocus(BaseSceneHandler* pSceneHandler)
{
    int depth = m_InputLockDepth;
    if (depth == 0 || m_nExclusiveInputSceneHashIDStack[depth - 1].m_pBaseSceneHandler == pSceneHandler)
    {
        m_bInputAllowed = true;
        return;
    }

    m_bInputAllowed = false;
}

/**
 * Offset/Address/Size: 0x6DC | 0x8020F0E8 | size: 0xD0
 */
bool FEInput::JustReleased(eFEINPUT_PAD pad, int button, bool remap, eFEINPUT_PAD* pOutPad)
{
    if (m_bInputAllowed)
    {
        if (pad != FE_ALL_PADS)
        {
            if (m_bEnableInput[pad])
            {
                cGlobalPad* pPad = cPadManager::GetPad(pad);
                return pPad->JustReleased(button, remap);
            }
            else
            {
                return false;
            }
        }

        for (int i = 0; i < 4; i++)
        {
            cGlobalPad* pPad = cPadManager::GetPad(i);
            if (pPad->JustReleased(button, remap))
            {
                if (pOutPad != nullptr)
                {
                    *pOutPad = (eFEINPUT_PAD)i;
                }
                return true;
            }
        }
    }
    return false;
}

/**
 * Offset/Address/Size: 0x7AC | 0x8020F1B8 | size: 0xD0
 */
bool FEInput::JustPressed(eFEINPUT_PAD pad, int button, bool remap, eFEINPUT_PAD* pOutPad)
{
    if (m_bInputAllowed)
    {
        if (pad != FE_ALL_PADS)
        {
            if (m_bEnableInput[pad])
            {
                cGlobalPad* pPad = cPadManager::GetPad(pad);
                return pPad->JustPressed(button, remap);
            }
            else
            {
                return false;
            }
        }

        for (int i = 0; i < 4; i++)
        {
            cGlobalPad* pPad = cPadManager::GetPad(i);
            if (pPad->JustPressed(button, remap))
            {
                if (pOutPad != nullptr)
                {
                    *pOutPad = (eFEINPUT_PAD)i;
                }
                return true;
            }
        }
    }
    return false;
}

/**
 * Offset/Address/Size: 0x87C | 0x8020F288 | size: 0x36C
 */
bool FEInput::IsAutoPressed(eFEINPUT_PAD, int, bool, eFEINPUT_PAD*)
{
    return false;
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
bool FEInput::IsConnected(eFEINPUT_PAD pad)
{
    if (pad != FE_ALL_PADS)
    {
        if (m_bEnableInput[pad])
        {
            cGlobalPad* pPad = cPadManager::GetPad(pad);
            return pPad->IsConnected();
        }
        else
        {
            return false;
        }
    }

    for (int i = 0; i < 4; i++)
    {
        cGlobalPad* pPad = cPadManager::GetPad(i);
        if (pPad->IsConnected())
        {
            return true;
        }
    }

    return false;
}

/**
 * Offset/Address/Size: 0xF94 | 0x8020F9A0 | size: 0x60
 */
cGlobalPad* FEInput::GetGlobalPad(eFEINPUT_PAD pad) const
{
    if (pad >= 4)
    {
        return nullptr;
    }

    if (!m_bInputAllowed)
    {
        return nullptr;
    }

    if (!m_bEnableInput[pad])
    {
        return nullptr;
    }

    return cPadManager::GetPad(pad);
}

/**
 * Offset/Address/Size: 0xFF4 | 0x8020FA00 | size: 0x5C
 */
void FEInput::Reset()
{
    m_bEnableInput[0] = true;
    m_bEnableInput[1] = true;
    m_bEnableInput[2] = true;
    m_bEnableInput[3] = true;
    m_InputLockDepth = 0;
    m_bInputAllowed = true;
    EnableAnalogToDPadMapping(FE_ALL_PADS, false);
    memset(g_aFEPadData, 0, 0x270);
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
    g_pFEInput = new ((u8*)nlMalloc(0x30, 8, false)) FEInput();
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
