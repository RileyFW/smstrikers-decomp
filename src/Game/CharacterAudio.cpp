#include "Game/CharacterAudio.h"

namespace Audio
{

/**
 * Offset/Address/Size: 0x0 | 0x8014C3A4 | size: 0x14
 */
bool cCharacterSFX::IsMovementLoopStarted()
{
    // return m_movementLoopStarted != 0;
    return m_movementLoopEmitter != NULL;
}

/**
 * Offset/Address/Size: 0x14 | 0x8014C3B8 | size: 0x24
 */
bool cCharacterSFX::IsMovementLoopPlaying()
{
    return Audio::IsEmitterActive(m_movementLoopEmitter);
}

/**
 * Offset/Address/Size: 0x38 | 0x8014C3DC | size: 0x48
 */
void cCharacterSFX::StopMovementLoop()
{
    if (m_movementLoopEmitter)
    {
        // Stop emitter with stop flag 0
        cGameSFX::StopEmitter(m_movementLoopEmitter, 0);
        m_movementLoopEmitter = nullptr;
        m_unk_0x33A0 = false;
    }
}

/**
 * Offset/Address/Size: 0x80 | 0x8014C424 | size: 0x164
 */
void cCharacterSFX::StartMovementLoop()
{
}

/**
 * Offset/Address/Size: 0x1E4 | 0x8014C588 | size: 0x10C
 */
// void cCharacterSFX::GetCharacterFromNisCharClass(NisCharacterClass)
// {
// }

/**
 * Offset/Address/Size: 0x2F0 | 0x8014C694 | size: 0x1C8
 */
// void cCharacterSFX::PlayNISRandomCharDialogue(CharDialogueType, NisCharacterClass, float, float, bool, const nlVector3*, const
// nlVector3*, unsigned long*)
// {
// }

/**
 * Offset/Address/Size: 0x4B8 | 0x8014C85C | size: 0x148
 */
void cCharacterSFX::PlayRandomWalkFootstep(float, bool)
{
}

/**
 * Offset/Address/Size: 0x600 | 0x8014C9A4 | size: 0x98
 */
void cCharacterSFX::StopPlayingAllRandomCharDialogue()
{
}

/**
 * Offset/Address/Size: 0x698 | 0x8014CA3C | size: 0x98
 */
// void cCharacterSFX::StopPlayingRandomCharDialogue(CharDialogueType)
// {
// }

/**
 * Offset/Address/Size: 0x730 | 0x8014CAD4 | size: 0x94
 */
// void cCharacterSFX::IsPlayingRandomCharDialogue(CharDialogueType)
// {
// }

/**
 * Offset/Address/Size: 0x7C4 | 0x8014CB68 | size: 0x498
 */
// void cCharacterSFX::PlayRandomCharDialogue(CharDialogueType, SoundAttributes&, bool, unsigned long*)
// {
// }

/**
 * Offset/Address/Size: 0xC5C | 0x8014D000 | size: 0x4D0
 */
// void cCharacterSFX::PlayRandomCharDialogue(CharDialogueType, PosUpdateMethod, float, float, bool)
// {
// }

/**
 * Offset/Address/Size: 0x112C | 0x8014D4D0 | size: 0x20
 */
void cCharacterSFX::Stop(eCharSFX sfxType, cGameSFX::StopFlag flag)
{
    cGameSFX::Stop(sfxType, flag);
}

/**
 * Offset/Address/Size: 0x114C | 0x8014D4F0 | size: 0x7C
 */
int cCharacterSFX::Play(SoundAttributes& attrs)
{
    attrs.m_unk_0x00 = 1;
    attrs.m_unk_0x70 = m_unk_0x3390;

    if (attrs.m_unk_0x5C == 1)
    {
        attrs.UsePhysObj(m_physicsCharacter);
    }

    if (attrs.m_soundType == 0U)
    {
        return Audio::GetSndIDError();
    }

    return cGameSFX::Play(attrs);
}

/**
 * Offset/Address/Size: 0x11C8 | 0x8014D56C | size: 0xCC
 */
void cCharacterSFX::Init()
{
    cGameSFX::Init();
}

/**
 * Offset/Address/Size: 0x1294 | 0x8014D638 | size: 0x7C
 */
cCharacterSFX::~cCharacterSFX()
{
    m_physicsCharacter = NULL;
    m_unk_0x3390 = 0;
    m_movementLoopEmitter = NULL;
    m_unk_0x339C = 100.0f;
    m_unk_0x33A0 = false;
}

/**
 * Offset/Address/Size: 0x1310 | 0x8014D6B4 | size: 0x60
 */
cCharacterSFX::cCharacterSFX()
{
    m_unk_0x3390 = 0;
    m_physicsCharacter = NULL;
    m_movementLoopEmitter = NULL;
    m_unk_0x339C = 100.0f;
    m_unk_0x33A0 = false;
    m_classType = 1;
}

} // namespace Audio
