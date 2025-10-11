#ifndef _NIS_H_
#define _NIS_H_

#include "NL/nlMath.h"
// #include "Game/Camera/animcam.h"
class cAnimCamera;

// void Bind<void, void (*)(EmissionController&, int), Placeholder<0>, int>(void (*)(EmissionController&, int), const Placeholder<0>&, const int&);

enum NisTriggerType
{
    NIS_TRIGGER_TYPE_EFFECT = 0,
    NIS_TRIGGER_TYPE_TIME_DILATION = 1,
    NIS_TRIGGER_TYPE_PLAY_SOUND = 2,
    NIS_TRIGGER_TYPE_PLAY_RANDOM_DIALOGUE = 3,
    NIS_TRIGGER_TYPE_STOP_SOUND = 4,
    NIS_TRIGGER_TYPE_PLAY_STREAM = 5,
    NIS_TRIGGER_TYPE_STOP_STREAM = 6,
    NIS_TRIGGER_TYPE_STOP_ALL_STREAMS = 7,
    NIS_TRIGGER_TYPE_SET_ACTIVE_STREAM_LOOPING = 8,
    NIS_TRIGGER_TYPE_REGISTER_GOAL_AUDIO = 9,
    NIS_TRIGGER_TYPE_RAISE_EVENT = 10,
};

enum NisCharacterClass
{
    NIS_CHAR_CLASS_INVALID = -1,
    NIS_CHAR_CLASS_BIRDO = 0,
    NIS_CHAR_CLASS_DAISY = 1,
    NIS_CHAR_CLASS_DONKEYKONG = 2,
    NIS_CHAR_CLASS_HAMMERBROS = 3,
    NIS_CHAR_CLASS_KOOPA = 4,
    NIS_CHAR_CLASS_LUIGI = 5,
    NIS_CHAR_CLASS_MARIO = 6,
    NIS_CHAR_CLASS_PEACH = 7,
    NIS_CHAR_CLASS_TOAD = 8,
    NIS_CHAR_CLASS_WALUIGI = 9,
    NIS_CHAR_CLASS_WARIO = 10,
    NIS_CHAR_CLASS_YOSHI = 11,
    NIS_CHAR_CLASS_MYSTERY = 12,
    NIS_CHAR_CLASS_HOME_GOALIE = 13,
    NIS_CHAR_CLASS_AWAY_GOALIE = 14,
    NIS_CHAR_CLASS_NUM_CLASSES = 15,
};

enum NisTarget
{
    NIS_TARGET_NONE = 0,
    NIS_TARGET_STADIUM = 1,
    NIS_TARGET_HOME_CAPTAIN = 2,
    NIS_TARGET_AWAY_CAPTAIN = 3,
    NIS_TARGET_HOME_SIDEKICK = 4,
    NIS_TARGET_AWAY_SIDEKICK = 5,
    NIS_TARGET_HOME_GOALIE = 6,
    NIS_TARGET_AWAY_GOALIE = 7,
    NIS_TARGET_LOSER_CAPTAIN = 8,
    NIS_TARGET_WINNER_CAPTAIN = 9,
    NIS_TARGET_LOSER_SIDEKICK = 10,
    NIS_TARGET_WINNER_SIDEKICK = 11,
    NIS_TARGET_LOSER_GOALIE = 12,
    NIS_TARGET_WINNER_GOALIE = 13,
    NIS_NUM_TARGETS = 14,
};

enum NisWinnerType
{
    NIS_GAME_WINNER = 0,
    NIS_GOAL_WINNER = 1,
    NIS_NUM_WINNER_TYPES = 2,
    NIS_DO_NOT_CARE = 3,
};

struct NisHeader
{
    /* 0x00 */ char name[64];
    /* 0x40 */ int size;
    /* 0x44 */ int numBalls;
    /* 0x48 */ int numAnimations;
    /* 0x4C */ int numCameras;
    /* 0x50 */ nlVector3 center;
    /* 0x5C */ nlVector3 minBounds;
    /* 0x68 */ nlVector3 maxBounds;
    /* 0x74 */ nlVector3 beginPositions[4];
    /* 0xA4 */ NisTarget target;
    /* 0xA8 */ NisWinnerType winnerType;
    /* 0xAC */ nlVector3 stadiumOffset;
}; // total size: 0xB8

class Nis
{
public:
    Nis(NisHeader&, char*, int);
    void Name() const;
    ~Nis();
    void Update(float);
    void UpdateTriggers(float, float, float);
    void SelectCamera(cAnimCamera&, int);
    void SelectRandomCamera(cAnimCamera&);
    void Render();
    void Offset() const;
    // void AddTrigger(NisTriggerType, float, const char*, const char*, Nis::TriggerParams*);
    // void Trigger::FireEffect(const Nis&) const;
    // void Trigger::Fire(Nis&) const;
    void StopAllOutstandingNisAudio();
};

// class Function1<void, EmissionController&>
// {
// public:
//     void FunctorImpl<BindExp2<void, void (*)(EmissionController&, int), Placeholder<0>, int>>::~FunctorImpl();
//     void FunctorImpl<BindExp2<void, void (*)(EmissionController&, int), Placeholder<0>, int>>::operator()(EmissionController&);
//     void FunctorImpl<BindExp2<void, void (*)(EmissionController&, int), Placeholder<0>, int>>::Clone() const;
// };

// class nlDeleteList<Nis
// {
// public:
//     void NisAudioData>(Nis::NisAudioData**);
// };

// class nlListRemoveElement<Nis
// {
// public:
//     void NisAudioData>(Nis::NisAudioData**, Nis::NisAudioData*, Nis::NisAudioData**);
// };

// class nlListAddStart<Nis
// {
// public:
//     void NisAudioData>(Nis::NisAudioData**, Nis::NisAudioData*, Nis::NisAudioData**);
// };

// class Format<BasicString<char, Detail
// {
// public:
//     void TempStringAllocator>, char[64], int>(const BasicString<char, Detail::TempStringAllocator>&, const char(&)[64], const int&);
// };

// class FormatImpl<BasicString<char, Detail
// {
// public:
//     void TempStringAllocator>>::operator%<const char*>(const char* const&);
//     void TempStringAllocator>>::operator%<int>(const int&);
// };

#endif // _NIS_H_
