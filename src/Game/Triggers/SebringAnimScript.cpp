#include "Game/Triggers/SebringAnimScript.h"

#include "Game/CharacterTriggers.h"
#include "Game/Sys/audio.h"
#include "NL/nlDebug.h"

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
void SebringAnimTagScriptInterpreter::DoFunctionCall(unsigned int func)
{
    switch (func)
    {
    case 0: // PlayCharSfx
    {
        m_SP--;
        m_SP--;
        NisCharacterClass charClass = (NisCharacterClass)*m_SP;
        m_SP--;
        const char* name = (const char*)*m_SP;
        Audio::PlayCharSFXbyStr(name, charClass, 1.0f, 0.0f, false, false, NULL, NULL, NULL);
        break;
    }
    case 1: // PlayCharSfxWithVol
    {
        m_SP--;
        m_SP--;
        float fVol = *(float*)m_SP;
        m_SP--;
        NisCharacterClass charClass = (NisCharacterClass)*m_SP;
        m_SP--;
        const char* name = (const char*)*m_SP;
        Audio::PlayCharSFXbyStr(name, charClass, fVol, 0.0f, false, false, NULL, NULL, NULL);
        break;
    }
    case 2: // PlayWorldSfx
    {
        m_SP--;
        m_SP--;
        const char* name = (const char*)*m_SP;
        Audio::PlayWorldSFXbyStr(name, 1.0f, 0.0f, false, true, NULL, NULL, NULL);
        break;
    }
    case 3: // PlayWorldSfxWithVol
    {
        m_SP--;
        m_SP--;
        float fVol = *(float*)m_SP;
        m_SP--;
        const char* name = (const char*)*m_SP;
        Audio::PlayWorldSFXbyStr(name, fVol, 0.0f, false, true, NULL, NULL, NULL);
        break;
    }
    case 4: // StopCharSfx
    {
        m_SP--;
        m_SP--;
        NisCharacterClass charClass = (NisCharacterClass)*m_SP;
        m_SP--;
        const char* name = (const char*)*m_SP;
        Audio::StopCharSFXbyStr(name, charClass);
        break;
    }
    case 5: // StopWorldSfx
    {
        m_SP--;
        m_SP--;
        const char* name = (const char*)*m_SP;
        Audio::StopWorldSFXbyStr(name);
        break;
    }
    default:
        nlBreak();
        break;
    }
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
