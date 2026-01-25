#include "Game/Triggers/SebringAnimScript.h"

#include "Game/CharacterTriggers.h"

class AnimTriggerCallbackInfo
{
public:
    /* 0x0 */ unsigned long m_uEventID;
    /* 0x4 */ float m_fIntensity;
}; // total size: 0x8

// extern void CharacterTriggerHandler(TriggerData*);

/**
 * Offset/Address/Size: 0x0 | 0x801A40B4 | size: 0x1FC
 */
void SebringAnimTagScriptInterpreter::DoFunctionCall(unsigned int)
{
}

/**
 * Offset/Address/Size: 0x0 | 0x801A4078 | size: 0x3C
 */
void SebringAnimTagScriptInterpreter::TriggerFired(unsigned long triggerId)
{
    if (m_FireTriggers)
    {
        AnimTriggerCallbackInfo data;
        data.m_uEventID = triggerId;
        data.m_fIntensity = 1.0f;
        CharacterTriggerHandler((unsigned int)&data);
    }
}
