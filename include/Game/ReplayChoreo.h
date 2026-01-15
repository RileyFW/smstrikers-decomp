#ifndef _REPLAYCHOREO_H_
#define _REPLAYCHOREO_H_

#include "types.h"
#include "Game/InterpreterCore.h"
#include "Game/Replay.h"
#include "Game/ReplayManager.h"
#include "Game/Camera/ReplayCamera.h"
#include "Game/Goalie.h"
#include "Game/Sys/eventman.h"

class ReplayChoreo : public InterpreterCore
{
public:
    enum HighlightQuality
    {
        HIGHLIGHT_QUALITY_EMPTY = 0,
        HIGHLIGHT_QUALITY_SAVE = 1,
        HIGHLIGHT_QUALITY_GOAL_DECREASE_DIFF = 2,
        HIGHLIGHT_QUALITY_GOAL_EQUALIZER = 3,
        HIGHLIGHT_QUALITY_GOAL_INCREASE_DIFF = 4,
        NUM_QUALITY_LEVELS = 5,
    };

    class Highlight
    {
        Highlight() { };
    };

    void DoFunctionCall(unsigned int);
    void Instance();
    void LoadScript();
    void EventHandler(Event*);
    void Reset();
    void CalcAutoReplayScriptName(ReplayType) const;
    void StartAutoReplay(ReplayType);
    void FlushHighlights();
    void Update(float);
    bool Done() const;
    void SaveHighlight(ReplayChoreo::HighlightQuality);
    void NumHighlights() const;
    ~ReplayChoreo();

    int mNumScripts[3][3][9];       // offset 0x24, size 0x144
    ReplayManager* mReplayManager;  // offset 0x168, size 0x4
    Replay* mReplay;                // offset 0x16C, size 0x4
    ReplayCamera mCamera;           // offset 0x170, size 0x8C
    float mRunForTimeLeft;          // offset 0x1FC, size 0x4
    unsigned char mRunningFor;      // offset 0x200, size 0x1
    void* mByteCode;                // offset 0x204, size 0x4
    GoalScoredData mGoalScoredData; // offset 0x208, size 0x24
    Highlight mHighlights[4];       // offset 0x22C, size 0xA0
    int mHighlightIndex;            // offset 0x2CC, size 0x4
}; // total size: 0x2D0

#endif // _REPLAYCHOREO_H_
