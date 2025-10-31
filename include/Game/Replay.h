#ifndef _REPLAY_H_
#define _REPLAY_H_

#include <string.h>
#include "NL/nlMath.h"

// Forward declarations
class DrawableCharacter;
class DrawableBall;
class DrawableExplosionFragment;
class DrawablePowerup;
class CrowdManager;
class EmissionManager;
class DrawableNetMesh;

class WriteByteStream
{
public:
    /* 0x0 */ char mCount;
    /* 0x4 */ char* mStorage;
}; // total size: 0x8

class ReadByteStream
{
public:
    /* 0x0 */ char mCount;
    /* 0x4 */ const char* mStorage;
}; // total size: 0x8

class SaveFrame
{
public:
    /* 0x0 */ int mInterval;
    /* 0x4 */ WriteByteStream mStream;
}; // total size: 0xC

enum ReplayNonBlendables
{
    REPLAY_NON_BLENDABLES = 0,
    DO_NOT_REPLAY_NON_BLENDABLES = 1,
};

class LoadFrame
{
public:
    /* 0x0 */ int mInterval;
    /* 0x4 */ ReadByteStream mStream;
    /* 0xC */ ReplayNonBlendables mReplayNonBlendables;
    /* 0x10 */ float mNonBlendableAheadOfFrame;
}; // total size: 0x14

// Forward declaration of generic template (needed before specializations)
template <int N, typename FrameType, typename T>
void Replayable(FrameType& frame, T& manager);

template <>
void Replayable<1, LoadFrame, CrowdManager>(LoadFrame& frame, CrowdManager& manager);

template <>
void Replayable<1, SaveFrame, CrowdManager>(SaveFrame& frame, CrowdManager& manager);

template <>
void Replayable<3, LoadFrame, EmissionManager>(LoadFrame& frame, EmissionManager& manager);

template <>
void Replayable<3, SaveFrame, EmissionManager>(SaveFrame& frame, EmissionManager& manager);

template <>
void Replayable<0, LoadFrame, bool>(LoadFrame& frame, bool& value);
template <>
void Replayable<1, LoadFrame, bool>(LoadFrame& frame, bool& value);
template <>
void Replayable<0, SaveFrame, bool>(SaveFrame& frame, bool& value);
template <>
void Replayable<1, SaveFrame, bool>(SaveFrame& frame, bool& value);
template <>
void Replayable<1, LoadFrame, nlVector3>(LoadFrame& frame, nlVector3& value);
template <>
void Replayable<1, SaveFrame, nlVector3>(SaveFrame& frame, nlVector3& value);

template <int N, typename FrameType, typename T>
void Replayable(FrameType& frame, T& drawable)
{
    drawable.Replay(frame);
}

enum ReplayType
{
    REPLAY_TYPE_GOAL = 6,
    REPLAY_TYPE_HIGHLIGHT = 7,
    REPLAY_TYPE_HYPER_STRIKE = 8,
    NUM_REPLAY_TYPES = 9,
};

class Replay
{
public:
    class Reel
    {
        Reel() { };
    };

    class Frame
    {
        Frame(char*, int, Frame*) { };
    };

    Replay(char*, int, int);
    ~Replay();

    void Next(Frame*, int) const;
    void TimeOfLastOccurence(unsigned int) const;
    void NewFrame();
    void IsReelValid(int) const;
    void DidOccurInLastNumSeconds(unsigned int, float) const;
    void LockReel(float, int, int);
    void BeginTime() const;
    void EndTime() const;
    void PlayReel(int);

    /* 0x00 */ Frame* mFree;            // offset 0x0, size 0x4
    /* 0x04 */ Reel mReels[4];          // offset 0x4, size 0x40
    /* 0x44 */ int mReelIdx;            // offset 0x44, size 0x4
    /* 0x48 */ int mTick;               // offset 0x48, size 0x4
    /* 0x4C */ int mMemorySize;         // offset 0x4C, size 0x4
    /* 0x50 */ int mMaxFrameSize;       // offset 0x50, size 0x4
    /* 0x54 */ int mActualMaxFrameSize; // offset 0x54, size 0x4
    /* 0x58 */ Reel* mHighlights[3];    // offset 0x58, size 0xC
}; // total size: 0x64

// class SlotPool < Replay
// {
// public:
//     void Frame > ::~SlotPool();
// };

#endif // _REPLAY_H_
