#include "Game/Audio/SoundEventScript.h"

#include "Game/AudioLoader.h"

/**
 * Offset/Address/Size: 0x0 | 0x80153FD8 | size: 0x96C
 */
void SoundEventScript::DoFunctionCall(unsigned int)
{
}

/**
 * Offset/Address/Size: 0x118 | 0x80153F50 | size: 0x88
 */
void SoundEventScript::CreateInstance()
{
    pInstance = new (nlMalloc(0x68, 8, 0)) SoundEventScript();
}

/**
 * Offset/Address/Size: 0xC8 | 0x80153F00 | size: 0x50
 */
void SoundEventScript::DestroyInstance()
{
    delete[] pInstance->pByteCode;
    delete pInstance;
    pInstance = NULL;
}

/**
 * Offset/Address/Size: 0xC0 | 0x80153EF8 | size: 0x8
 */
SoundEventScript& SoundEventScript::Instance()
{
    return *pInstance;
}

/**
 * Offset/Address/Size: 0x60 | 0x80153E98 | size: 0x60
 */
void SoundEventScript::Call(const char* functionName)
{
    if (AudioLoader::gbDisableAudio == false)
    {
        nlStrNCpy<char>(mCurrentFunction, functionName, 0x40);
        InterpreterCore::CallFunction(nlStringHash(functionName));
    }
}

/**
 * Offset/Address/Size: 0x0 | 0x80153E38 | size: 0x60
 */
SoundEventScript::~SoundEventScript()
{
}
