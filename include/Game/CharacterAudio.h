#ifndef _CHARACTERAUDIO_H_
#define _CHARACTERAUDIO_H_

#include "types.h"
#include "NL/nlMath.h"

#include "Game/GameAudio.h"
#include "Game/Physics/PhysicsCharacter.h"

namespace Audio
{
enum eCharSFX
{
    eCharSFX_0 = 0
};

class cCharacterSFX : public cGameSFX
{
public:
    cCharacterSFX();
    virtual ~cCharacterSFX();

    virtual void Init();
    virtual int Play(Audio::SoundAttributes&);
    void Stop(Audio::eCharSFX, cGameSFX::StopFlag);
    // void PlayRandomCharDialogue(CharDialogueType, PosUpdateMethod, float, float, bool);
    // void PlayRandomCharDialogue(CharDialogueType, Audio::SoundAttributes&, bool, unsigned long*);
    // void IsPlayingRandomCharDialogue(CharDialogueType);
    // void StopPlayingRandomCharDialogue(CharDialogueType);
    void StopPlayingAllRandomCharDialogue();
    void PlayRandomWalkFootstep(float, bool);
    // void PlayNISRandomCharDialogue(CharDialogueType, NisCharacterClass, float, float, bool, const nlVector3*, const nlVector3*, unsigned long*);
    // void GetCharacterFromNisCharClass(NisCharacterClass);
    void StartMovementLoop();
    void StopMovementLoop();
    bool IsMovementLoopPlaying();
    bool IsMovementLoopStarted();

    /* 0x3390 */ s32 m_unk_0x3390;
    /* 0x3394 */ PhysicsCharacter* m_physicsCharacter;
    /* 0x3398 */ SFXEmitter* m_movementLoopEmitter;
    /* 0x339C */ f32 m_unk_0x339C;
    /* 0x33A0 */ bool m_unk_0x33A0;
};

} // namespace Audio

#endif // _CHARACTERAUDIO_H_
